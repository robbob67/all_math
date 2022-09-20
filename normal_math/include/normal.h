//
// Created by Samuel Whitton on 13/9/22.
//

#ifndef METAL_PROJECT_NORMAL_H
#define METAL_PROJECT_NORMAL_H

#include "normal_container_traits.h"

namespace normal_math {

    namespace Math
    {
        template<typename CONTAINER> requires containers::is_container_t<std::remove_reference_t<CONTAINER>>
        constexpr auto add_two_vectors(CONTAINER&& vector_one, CONTAINER&& vector_two, typename std::remove_reference_t<CONTAINER>& result) noexcept
        {
            for(std::size_t index = 0; index < vector_one.size(); index++)
            {
                result.at(index) = vector_one.at(index) + vector_two.at(index);
            }
        }

        //matrix a is m (rows) x n (columns)
        //matrix b is n (rows) x b (columns)
        //matrix r is m (rows) x b (columns)
        template<typename CONTAINER> requires containers::is_container_t<std::remove_reference_t<CONTAINER>>
        auto multiply_two_matrices(CONTAINER&& matrix_one, CONTAINER&& matrix_two, typename std::remove_reference_t<CONTAINER>& result, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two) noexcept
        {
            result.reserve(number_of_rows_vector_one * number_of_columns_vector_two);
            for(std::size_t b = 0; b < number_of_columns_vector_two; b++)
            {
                for(std::size_t m = 0; m < number_of_rows_vector_one; m++)
                {
                    auto value = typename std::remove_reference_t<CONTAINER>::value_type{0};
                    for(std::size_t n = 0; n < number_of_rows_vector_two; n++)
                    {
                        value += matrix_one[m * number_of_rows_vector_one + n] * matrix_two[n * number_of_columns_vector_two + b];
                    }
                    result[m * number_of_columns_vector_two + b] = value;
                }
            }
        }
    };

} // normal

#endif //METAL_PROJECT_NORMAL_H
