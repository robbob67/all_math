//
// Created by Samuel Whitton on 4/8/22.
//

#ifndef NORMAL_CONTAINER_TRAITS_H
#define NORMAL_CONTAINER_TRAITS_H

#include <vector>
#include <array>
#include <memory>

namespace containers {

    template<typename T>
    struct is_contiguous_container_t
    {
        static constexpr bool value = false;
    };

    template<typename U, typename P>
    struct is_contiguous_container_t<std::vector<U, P>>
    {
        static constexpr bool value = true;
    };

    template<typename U, int SIZE>
    struct is_contiguous_container_t<std::array<U, SIZE>>
    {
        static constexpr bool value = true;
    };

    template<typename CONTAINER>
    concept is_container_t =
    requires {
        typename std::remove_reference_t<CONTAINER>::value_type;
        typename std::remove_reference_t<CONTAINER>::const_iterator;
    }
    &&
    requires(CONTAINER container) {
        { container.size() }; // TODO fixup
    };

} // namespace normal_math

#endif //NORMAL_CONTAINER_TRAITS_H
