#include "metal_definition.h"
#include <vector>
#include <array>
#include "metal_allocator.h"
#include "metal.h"
#include <memory>
#include <iostream>

#include "normal.h"

template<typename CONTAINER> requires containers::is_container_t<std::remove_reference_t<CONTAINER>>
auto testVectorAddition(CONTAINER&& vector_one, CONTAINER&& vector_two, typename std::remove_reference_t<CONTAINER>& result, auto add_vectors) noexcept
{
    add_vectors(vector_one, vector_two, result);
    auto vector_one_iterator = vector_one.cbegin();
    auto vector_two_iterator = vector_two.cbegin();
    auto result_iterator = result.cbegin();
    while(result_iterator != result.cend())
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

int main(int argc, char *argv[])
{//1073741824    536870912

    constexpr auto size = std::size_t{536870912};

    auto vectorOne = [size](){
        auto vectorOne = std::vector<int, metal::metal_allocator<int>>(size);
        std::for_each(std::begin(vectorOne), std::end(vectorOne), [i = 0](auto& x) mutable {
            x = i++ + 39;
        });
        return vectorOne;
    }();

    auto vectorTwo = [size](){
        auto vectorTwo = std::vector<int, metal::metal_allocator<int>>(size);
        std::for_each(std::begin(vectorTwo), std::end(vectorTwo), [i = 0](auto& x) mutable {
            x = i++ + 30;
        });
        return vectorTwo;
    }();

    // Test 1
    std::vector<int> result_x(5);
    normal_math::Math::add_two_vectors<std::vector<int>>({1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, result_x);

    // Test 2
    std::array<int, 5> y1 = {1, 2, 3, 4, 5};
    std::array<int, 5> y2 = {1, 2, 3, 4, 5};
    std::array<int, 5> result_y = {0};
    std::cout << "sanity check: " << testVectorAddition(y1, y2, result_y, [](auto&& arg_one, auto&& arg_two, auto& result){
        normal_math::Math::add_two_vectors(std::forward<decltype(arg_one)>(arg_one), std::forward<decltype(arg_two)>(arg_two), result);
    }) << "\n";

    // Test 3
    std::vector<int> y1V = {1, 2, 3, 4, 5};
    std::vector<int> y2V = {1, 2, 3, 4, 5};
    std::vector<int> result_yV = {0, 0, 0, 0, 0};
    std::cout << "sanity check vector: " << testVectorAddition(y1V, y2V, result_yV, [](auto&& arg_one, auto&& arg_two, auto& result){
        normal_math::Math::add_two_vectors(std::forward<decltype(arg_one)>(arg_one), std::forward<decltype(arg_two)>(arg_two), result);
    }) << "\n";

    // Test 4

    /*try
    {
        std::cout << "starting first test\n";
        const auto result = metal::Math::add_two_vectors(vectorOne, vectorTwo);
        if (result[5559] != vectorOne[5559] + vectorTwo[5559])
        {
            std::cout << "Error: " << "results not as expected\n";
        }
        std::cout << "result[5559] " << result[5559] << " should equal " << vectorOne[5559] + vectorTwo[5559] << std::endl;
        std::cout << "finished first test\n";
    }
    catch(const std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what();
    }*/

    /*std::cout << "starting first test\n";
    const auto result = metal::Math::add_two_vectors(vectorOne, vectorTwo);
    if(!(static_cast<int>(vectorOne[10] * vectorTwo[10] + vectorTwo[10] * vectorTwo[10] / 2 + 334 / vectorOne[10] * vectorTwo[10] + vectorTwo[10] * vectorTwo[10] / 2 + 334) == result[10]))
    {
        std::cout << "RIGHT\n";
    }
    else
    {
        std::cout << "WRONG\n";
    }
    std::cout << "finished first test\n";
    std::cout << "starting second test\n";
    auto second_result = [&vectorOne, &vectorTwo, index = 0](){
        auto result = decltype(vectorOne)(vectorOne.size());
        for(int i = 0; i < vectorOne.size(); i++)
        {
            result[i] = vectorOne[i] * vectorTwo[i] + vectorTwo[i] * vectorTwo[i] / 2 + 334 / vectorOne[i] * vectorTwo[i] + vectorTwo[i] * vectorTwo[i] / 2 + 334;
        }
        return result;
    }();
    std::cout << "finished second test\n";


    auto matrixOne = std::vector<int, metal::metal_allocator<int>>(12); // 4x3
    matrixOne[0] = 1;
    matrixOne[1] = 1;
    matrixOne[2] = 1;
    matrixOne[3] = 1;
    matrixOne[4] = 1;
    matrixOne[5] = 1;
    matrixOne[6] = 1;
    matrixOne[7] = 1;
    matrixOne[8] = 1;
    matrixOne[9] = 1;
    matrixOne[10] = 1;
    matrixOne[11] = 1;
    auto matrixTwo = std::vector<int, metal::metal_allocator<int>>(6); // 3x5
    matrixTwo[0] = 1;
    matrixTwo[1] = 1;
    matrixTwo[2] = 1;
    matrixTwo[3] = 1;
    matrixTwo[4] = 1;
    matrixTwo[5] = 1;
    matrixTwo[6] = 1;
    matrixTwo[7] = 1;
    matrixTwo[8] = 1;
    matrixTwo[9] = 1;
    matrixTwo[10] = 1;
    matrixTwo[11] = 1;
    matrixTwo[12] = 1;
    matrixTwo[13] = 1;
    matrixTwo[14] = 1;

    // result = 4x5
    auto matrixResult = metal::Math::multiply_two_matrices(matrixOne, matrixTwo, 4, 3, 5);
    if(matrixResult[19] == 233)
    {
        std::cout << "RIGHT\n";
    }
    else
    {
        for(int i = 0; i < 20; i++) {
            std::cout << "WRONG with: " << matrixResult[i] <<  "\n";
        }
    }
*/
    //static auto multiply_two_matrices(CONTAINER&& matrix_one, CONTAINER&& matrix_two, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two)



    return 0;
}

