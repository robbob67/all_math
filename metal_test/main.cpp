#include "metal_definition.h"
#include <vector>
#include <array>
#include "metal_allocator.h"
#include "metal.h"
#include <memory>
#include <iostream>
#include <stdexcept>
#include <exception>

#include "normal.h"

template<typename  T, typename A>
class Vector: public std::vector<T, A>
{
public:
    using std::vector<T, A>::vector;

    Vector& operator=(const Vector& other)
    {
        std::cout << "copy assignment \n";
        return std::vector<T, A>(std::forward<Vector>(other));
    }


    Vector& operator=(Vector&& other)
    {
        std::cout << "move assignment \n";
        return std::vector<T, A>(std::forward<Vector>(other));
    }

    Vector(const Vector& other)
            : std::vector<T, A>(other)
    {
        std::cout << "copy constructor \n";
    }

    Vector(Vector&& other)
    : std::vector<T, A>(std::forward<Vector>(other))
    {
        std::cout << "move constructor \n";

    }
};

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


    std::vector<int> result_x(5);
    normal_math::Math::add_two_vectors<std::vector<int>>({1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, result_x);

    constexpr std::array<int, 5> y1 = {1, 2, 3, 4, 5};
    constexpr std::array<int, 5> y2 = {1, 2, 3, 4, 5};
    constexpr std::array<int, 5> result_y = {0};
    normal_math::Math::add_two_vectors(y1, y2, result_y);


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

    std::cout << "starting first test\n";
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

    //static auto multiply_two_matrices(CONTAINER&& matrix_one, CONTAINER&& matrix_two, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two)



    return 0;
}

