#include "metal_definition.h"
#include <vector>
#include "metal_allocator.h"
#include "metal.h"
#include <memory>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <benchmark/benchmark.h>

#include "normal.h"

constexpr auto VECTOR_SIZE = std::size_t{536870912};
//constexpr auto VECTOR_SIZE = std::size_t{536870912};

constexpr auto MATRIX_ROWS_VECTOR_ONE = std::size_t{1000};
constexpr auto MATRIX_ROWS_VECTOR_TWO = std::size_t{1000};
constexpr auto MATRIX_COLUMNS_VECTOR_ONE = MATRIX_ROWS_VECTOR_TWO;
constexpr auto MATRIX_COLUMNS_VECTOR_TWO = std::size_t{1000};

auto matrix_one = []() {
    auto matrix_one = std::vector<int>(MATRIX_ROWS_VECTOR_ONE * MATRIX_COLUMNS_VECTOR_ONE);
    for(std::size_t index = 0; index < matrix_one.capacity(); index++)
    {
        matrix_one[index] = index;
    }
    return matrix_one;
}();

auto matrix_two = []() {
    auto matrix_two = std::vector<int>(MATRIX_ROWS_VECTOR_TWO * MATRIX_COLUMNS_VECTOR_TWO);
    for(std::size_t index = 0; index < matrix_two.capacity(); index++)
    {
        matrix_two[index] = index;
    }
    return matrix_two;
}();

auto metal_matrix_one = []() {
    auto matrix_one = std::vector<int, metal::metal_allocator<int>>(MATRIX_ROWS_VECTOR_ONE * MATRIX_COLUMNS_VECTOR_ONE);
    for(std::size_t index = 0; index < matrix_one.capacity(); index++)
    {
        matrix_one[index] = index;
    }
    return matrix_one;
}();

auto metal_matrix_two = []() {
    auto matrix_two = std::vector<int, metal::metal_allocator<int>>(MATRIX_ROWS_VECTOR_TWO * MATRIX_COLUMNS_VECTOR_TWO);
    for(std::size_t index = 0; index < matrix_two.capacity(); index++)
    {
        matrix_two[index] = index;
    }
    return matrix_two;
}();

auto metal_result_matrix = []() {
    return std::vector<int, metal::metal_allocator<int>>(MATRIX_ROWS_VECTOR_ONE * MATRIX_COLUMNS_VECTOR_TWO);
}();

auto result_matrix = []() {
    return std::vector<int>(MATRIX_ROWS_VECTOR_ONE * MATRIX_COLUMNS_VECTOR_TWO);
}();

auto vector_one = []() {
    auto vector_one = std::vector<int>(VECTOR_SIZE);
    for(std::size_t index = 0; index < vector_one.capacity(); index++)
    {
        vector_one[index] = index;
    }
    return vector_one;
}();

auto vector_two = []() {
    auto vector_two = std::vector<int>(VECTOR_SIZE);
    for(std::size_t index = 0; index < vector_two.capacity(); index++)
    {
        vector_two[index] = index;
    }
    return vector_two;
}();

auto result_vector = []() {
    return std::vector<int>(VECTOR_SIZE);
}();

auto metal_vector_one = []() {
    auto vector_one = std::vector<int, metal::metal_allocator<int>>(VECTOR_SIZE);
    for(std::size_t index = 0; index < vector_one.capacity(); index++)
    {
        vector_one[index] = index;
    }
    return vector_one;
}();

auto metal_vector_two = []() {
    auto vector_two = std::vector<int, metal::metal_allocator<int>>(VECTOR_SIZE);
    for(std::size_t index = 0; index < vector_two.capacity(); index++)
    {
        vector_two[index] = index;
    }
    return vector_two;
}();

auto metal_result_vector = []() {
    return std::vector<int, metal::metal_allocator<int>>(VECTOR_SIZE);
}();

static void BM_normal_vector_addition(benchmark::State& state) {
    for (auto _ : state) {
        const auto result = normal_math::Math::add_two_vectors(vector_one, vector_two);
    }
}

static void BM_normal_vector_addition_with_result(benchmark::State& state) {
    for (auto _ : state) {
        normal_math::Math::add_two_vectors(vector_one, vector_two, result_vector);
    }
}

static void BM_metal_vector_addition(benchmark::State& state) {
    for (auto _ : state) {
        const auto result = metal::Math::add_two_vectors(metal_vector_one, metal_vector_two);
    }
}

static void BM_metal_vector_addition_with_result(benchmark::State& state) {
    for (auto _ : state) {
        metal::Math::add_two_vectors<std::vector<int, metal::metal_allocator<int>>>(std::forward<decltype(metal_vector_one)>(metal_vector_one), std::forward<decltype(metal_vector_two)>(metal_vector_two), metal_result_vector);
        //metal::Math::add_two_vectors<std::vector<int, metal::metal_allocator<int>>&>(metal_vector_one, metal_vector_two, metal_result_vector);

    }
}

static void BM_normal_matrix_multiplication(benchmark::State& state) {
    for (auto _ : state) {
        const auto result = normal_math::Math::multiply_two_matrices(matrix_one, matrix_two, MATRIX_ROWS_VECTOR_ONE, MATRIX_ROWS_VECTOR_TWO, MATRIX_COLUMNS_VECTOR_TWO);
    }
}

static void BM_metal_matrix_multiplication(benchmark::State& state) {
    for (auto _ : state) {
        const auto result = metal::Math::multiply_two_matrices(matrix_one, matrix_two, MATRIX_ROWS_VECTOR_ONE, MATRIX_ROWS_VECTOR_TWO, MATRIX_COLUMNS_VECTOR_TWO);
    }
}

static void BM_metal_matrix_multiplication_with_result(benchmark::State& state) {
    for (auto _ : state) {
        metal::Math::multiply_two_matrices<std::vector<int, metal::metal_allocator<int>>>(std::forward<decltype(metal_matrix_one)>(metal_matrix_one), std::forward<decltype(metal_matrix_two)>(metal_matrix_two), metal_result_matrix, MATRIX_ROWS_VECTOR_ONE, MATRIX_ROWS_VECTOR_TWO, MATRIX_COLUMNS_VECTOR_TWO);
    }
}

static void BM_normal_matrix_multiplication_with_result(benchmark::State& state) {
    for (auto _ : state) {
        normal_math::Math::multiply_two_matrices(matrix_one, matrix_two, result_matrix, MATRIX_ROWS_VECTOR_ONE, MATRIX_ROWS_VECTOR_TWO, MATRIX_COLUMNS_VECTOR_TWO);
    }
}

//BENCHMARK(BM_normal_vector_addition_with_result);
//BENCHMARK(BM_metal_vector_addition_with_result);
BENCHMARK(BM_normal_matrix_multiplication);
BENCHMARK(BM_metal_matrix_multiplication);
BENCHMARK(BM_normal_matrix_multiplication_with_result);
BENCHMARK(BM_metal_matrix_multiplication_with_result);

BENCHMARK_MAIN();