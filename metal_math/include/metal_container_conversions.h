//
// Created by Samuel Whitton on 8/8/22.
//

#ifndef MYMETAL_METAL_CONTAINER_CONVERSIONS_H
#define MYMETAL_METAL_CONTAINER_CONVERSIONS_H

#include "metal_allocator.h"

namespace metal {

    template<typename CONTAINER> requires non_metal_container<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
    [[nodiscard]] auto convert_to_metal_container(CONTAINER&& vector)
    {
        auto metal_vector = std::vector<typename std::remove_reference_t<CONTAINER>::value_type, metal_allocator<typename std::remove_reference_t<CONTAINER>::value_type>>(vector.size());
        std::for_each(std::begin(vector), std::end(vector), [index = 0, &metal_vector](auto element) mutable {
            metal_vector[index++] = element;
        });
        return metal_vector;
    }

    template<typename CONTAINER> requires non_metal_container<std::remove_reference_t<CONTAINER>, typename std::remove_reference_t<CONTAINER>::value_type>
    [[nodiscard]] auto convert_to_non_metal_container(auto&& vector)
    {
        return CONTAINER{std::begin(vector), std::end(vector)};
    }

} // namespace metal

#endif //MYMETAL_METAL_CONTAINER_CONVERSIONS_H
