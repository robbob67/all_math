#include "metal_definition.h"
#include <vector>
#include <array>
#include "metal_allocator.h"
#include "metal.h"
#include <memory>
#include <iostream>

#include "normal.h"

template<typename CONTAINER> requires containers::is_container_t<std::remove_reference_t<CONTAINER>>
auto testVectorAddition(CONTAINER&& vector_one, CONTAINER&& vector_two, auto add_vectors) noexcept
{
    const auto result = add_vectors(vector_one, vector_two);
    auto vector_one_iterator = vector_one.cbegin();
    auto vector_two_iterator = vector_two.cbegin();
    auto result_iterator = result.cbegin();
    while (result_iterator != result.cend())
    {
        if ((*(result_iterator++)) != (*(vector_one_iterator++)) + (*(vector_two_iterator++)))
            return false;
    }
    if (vector_one_iterator != vector_one.cend() || vector_two_iterator != vector_two.cend())
    {
        return false;
    }
    return true;
}

template<typename CONTAINER> requires containers::is_container_t<std::remove_reference_t<CONTAINER>>
auto testMatrixMultiplication(CONTAINER&& matrix_one, CONTAINER&& matrix_two, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two, auto multiply_matricies) noexcept
{
    const auto result = multiply_matricies(matrix_one, matrix_two);
    if (    matrix_one.size() != (number_of_rows_vector_one * number_of_rows_vector_two)
        ||  matrix_two.size() != (number_of_columns_vector_two * number_of_rows_vector_two)
        ||  result.size() != (number_of_rows_vector_one * number_of_columns_vector_two))
    {
        return false;
    }
    for(std::size_t b = 0; b < number_of_columns_vector_two; b++)
    {
        for(std::size_t m = 0; m < number_of_rows_vector_one; m++)
        {
            auto value = typename std::remove_reference_t<CONTAINER>::value_type{0};
            for(std::size_t n = 0; n < number_of_rows_vector_two; n++)
            {
                value += matrix_one.at(m * number_of_rows_vector_two + n) * matrix_two.at(n * number_of_columns_vector_two + b);
            }
            if (result.at(m * number_of_columns_vector_two + b) != value) {
                return false;
            }
        }
    }
    return true;
}


int main(int argc, char *argv[])
{
    const auto vector_one = std::vector<int>{1, 2, 3, 4, 5};
    const auto vector_two = std::vector<int>{1, 2, 3, 4, 5};

    const auto vector_normal_result = testVectorAddition(vector_one, vector_two, [](auto&& vector_one, auto&& vector_two) -> std::remove_reference_t<decltype(vector_one)> {
        return normal_math::Math::add_two_vectors(std::forward<decltype(vector_one)>(vector_one), std::forward<decltype(vector_two)>(vector_two));
    });

    const auto vector_metal_result = testVectorAddition(vector_one, vector_two, [](auto&& vector_one, auto&& vector_two) -> std::remove_reference_t<decltype(vector_one)> {
        return metal::Math::add_two_vectors(std::forward<decltype(vector_one)>(vector_one), std::forward<decltype(vector_two)>(vector_two));
    });

    std::cout << "result of [normal] test = " << vector_normal_result << "\n";
    std::cout << "result of [metal] test = " << vector_metal_result << "\n";

    const auto matrix_one = std::vector<int>{1, 2, 3, 4, 5, 6};
    const auto matrix_two = std::vector<int>{1, 2, 3, 4, 5, 6};
    const auto number_of_rows_vector_one = std::size_t{3};
    const auto number_of_rows_vector_two = std::size_t{2};
    const auto number_of_columns_vector_two = std::size_t{3};

    const auto matrix_normal_result = testMatrixMultiplication(matrix_one, matrix_two, number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two, [number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two](auto&& matrix_one, auto&& matrix_two) -> std::remove_reference_t<decltype(matrix_two)> {
        return normal_math::Math::multiply_two_matrices(std::forward<decltype(matrix_one)>(matrix_one), std::forward<decltype(matrix_two)>(matrix_two), number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two);
    });

    const auto matrix_metal_result = testMatrixMultiplication(matrix_one, matrix_two, number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two, [number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two](auto&& matrix_one, auto&& matrix_two) -> std::remove_reference_t<decltype(matrix_two)> {
        return metal::Math::multiply_two_matrices(std::forward<decltype(matrix_one)>(matrix_one), std::forward<decltype(matrix_two)>(matrix_two), number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two);
    });

    std::cout << "matrix multiplication result of [normal] test = " << matrix_normal_result << "\n";
    std::cout << "matrix multiplication result of [metal] test = " << matrix_metal_result << "\n";

    return 0;
}

