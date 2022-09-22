//
// Created by Samuel Whitton on 15/7/22.
//

#ifndef MYMETAL_METAL_H
#define MYMETAL_METAL_H

#include "metal_allocator.h"
#include "metal_container_conversions.h"

#include "create_function.h"

namespace metal {

    class Math
    {

    public:

        template<typename CONTAINER> requires is_base_container_t<std::remove_reference_t<CONTAINER>, int>
        [[nodiscard]] static auto add_two_vectors(CONTAINER&& vector_one, CONTAINER&& vector_two)
        {
            return add_two_vectors("add_two_int_vectors", std::forward<CONTAINER>(vector_one), std::forward<CONTAINER>(vector_two));
        }

        template<typename CONTAINER> requires is_base_container_t<std::remove_reference_t<CONTAINER>, int>
        static auto add_two_vectors(CONTAINER&& vector_one, CONTAINER&& vector_two, typename std::remove_reference_t<CONTAINER>& result)
        {
            add_two_vectors("add_two_int_vectors", std::forward<CONTAINER>(vector_one), std::forward<CONTAINER>(vector_two), result);
        }

        //matrix a is m (rows) x n (columns)
        //matrix b is n (rows) x b (columns)
        //matrix r is m (rows) x b (columns)
        template<typename CONTAINER> requires is_base_container_t<std::remove_reference_t<CONTAINER>, int>
        [[nodiscard]] static auto multiply_two_matrices(CONTAINER&& matrix_one, CONTAINER&& matrix_two, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two)
        {
            return multiply_two_matrices("multiply_two_int_matrices", std::forward<CONTAINER>(matrix_one), std::forward<CONTAINER>(matrix_two), number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two);
        }

        template<typename CONTAINER> requires is_base_container_t<std::remove_reference_t<CONTAINER>, int>
        static auto multiply_two_matrices(CONTAINER&& matrix_one, CONTAINER&& matrix_two, typename std::remove_reference_t<CONTAINER>& result, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two)
        {
             multiply_two_matrices("multiply_two_int_matrices", std::forward<CONTAINER>(matrix_one), std::forward<CONTAINER>(matrix_two), result, number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two);
        }

    private:

        template<typename CONTAINER> requires metal_container<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
        static auto multiply_two_matrices(auto functionName, CONTAINER&& matrix_one, CONTAINER&& matrix_two, typename std::remove_reference_t<CONTAINER>& result, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two) {
            auto function = metal::GPU::create_function(functionName);
            auto numberOfRowsVectorOne = std::vector<int, metal_allocator<int>>{static_cast<int>(number_of_rows_vector_one)};
            auto numberOfRowsVectorTwo = std::vector<int, metal_allocator<int>>{static_cast<int>(number_of_rows_vector_two)};
            auto numberOfColumnsVectorTwo = std::vector<int, metal_allocator<int>>{static_cast<int>(number_of_columns_vector_two)};

            function.addParameter(matrix_one);
            function.addParameter(matrix_two);
            function.addParameter(numberOfRowsVectorOne);
            function.addParameter(numberOfRowsVectorTwo);
            function.addParameter(numberOfColumnsVectorTwo);
            function.addParameter(result);
            function.setGridSize(MTL::Size::Make(number_of_columns_vector_two, number_of_rows_vector_one, 1));
            function.execute();
        }

        template<typename CONTAINER> requires metal_container<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
        static auto multiply_two_matrices(auto functionName, CONTAINER&& matrix_one, CONTAINER&& matrix_two, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two) {
            auto function = metal::GPU::create_function(functionName);
            auto metal_buffer = std::remove_reference_t<CONTAINER>(number_of_rows_vector_one * number_of_columns_vector_two);
            auto numberOfRowsVectorOne = std::vector<int, metal_allocator<int>>{static_cast<int>(number_of_rows_vector_one)};
            auto numberOfRowsVectorTwo = std::vector<int, metal_allocator<int>>{static_cast<int>(number_of_rows_vector_two)};
            auto numberOfColumnsVectorTwo = std::vector<int, metal_allocator<int>>{static_cast<int>(number_of_columns_vector_two)};

            function.addParameter(matrix_one);
            function.addParameter(matrix_two);
            function.addParameter(numberOfRowsVectorOne);
            function.addParameter(numberOfRowsVectorTwo);
            function.addParameter(numberOfColumnsVectorTwo);
            function.addParameter(metal_buffer);
            function.setGridSize(MTL::Size::Make(number_of_columns_vector_two, number_of_rows_vector_one, 1));
            function.execute();
            return metal_buffer;
        }

        template<typename CONTAINER> requires non_metal_container<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
        static auto multiply_two_matrices(auto functionName, CONTAINER&& matrix_one, CONTAINER&& matrix_two, std::size_t number_of_rows_vector_one, std::size_t number_of_rows_vector_two, std::size_t number_of_columns_vector_two) {
            auto metal_matrix_one = convert_to_metal_container(std::forward<decltype(matrix_one)>(matrix_one));
            auto metal_matrix_two = convert_to_metal_container(std::forward<decltype(matrix_two)>(matrix_two));
            return convert_to_non_metal_container<std::remove_reference_t<CONTAINER>>(multiply_two_matrices(functionName, metal_matrix_one, metal_matrix_two, number_of_rows_vector_one, number_of_rows_vector_two, number_of_columns_vector_two));
        }

        template<typename CONTAINER> requires metal_container<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
        static auto add_two_vectors(auto functionName, CONTAINER&& vector_one, CONTAINER&& vector_two) {
            auto function = metal::GPU::create_function(functionName);
            auto metal_buffer = std::remove_reference_t<CONTAINER>(vector_one.size());
            function.addParameter(vector_one);
            function.addParameter(vector_two);
            function.addParameter(metal_buffer);
            function.setGridSize(MTL::Size::Make(vector_one.size(), 1, 1));
            function.execute();
            return metal_buffer;
        }

        template<typename CONTAINER> requires metal_container<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
        static auto add_two_vectors(auto functionName, CONTAINER&& vector_one, CONTAINER&& vector_two, typename std::remove_reference_t<CONTAINER>& result) {
            auto function = metal::GPU::create_function(functionName);
            function.addParameter(vector_one);
            function.addParameter(vector_two);
            function.addParameter(result);
            function.setGridSize(MTL::Size::Make(vector_one.size(), 1, 1));
            function.execute();
        }

        template<typename CONTAINER> requires non_metal_container<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
        static auto add_two_vectors(auto functionName, CONTAINER&& vector_one, CONTAINER&& vector_two) {
            auto metal_vector_one = convert_to_metal_container(std::forward<decltype(vector_one)>(vector_one));
            auto metal_vector_two = convert_to_metal_container(std::forward<decltype(vector_two)>(vector_two));
            return convert_to_non_metal_container<std::remove_reference_t<CONTAINER>>(add_two_vectors(functionName, metal_vector_one, metal_vector_two));
        }

    };

} // metal

#endif //MYMETAL_METAL_H


/*template<typename CONTAINER> requires is_base_container_t<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
[[nodiscard]] static auto add_two_vectors(auto functionName, CONTAINER&& vector_one, CONTAINER&& vector_two)
{
    using PossibleResult = std::pair<std::optional<std::remove_reference_t<CONTAINER>>, std::optional<std::string>>;

    auto resultPromise = std::promise<PossibleResult>{};
    auto resultFuture = resultPromise.get_future();
    add_two_vectors(functionName, std::forward<CONTAINER>(vector_one), std::forward<CONTAINER>(vector_two), [&resultPromise](auto result){
        resultPromise.set_value(std::make_pair(std::move(*result), std::nullopt));
    }, [&resultPromise](auto error_message){
        resultPromise.set_value(std::make_pair(std::nullopt, error_message));
    });

    const auto result = resultFuture.get();
    if(result.first)
    {
        return result.first.value();
    }
    else
    {
        throw std::runtime_error("add_two_int_vectors: operation failed " + result.second.value());
    }
}*/