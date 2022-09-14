//
// Created by Samuel Whitton on 4/8/22.
//

#ifndef CONTAINER_TRAITS_H
#define CONTAINER_TRAITS_H

#include <vector>
#include <array>
#include <memory>

namespace std {

    template<typename T>
    struct is_contiguous_container_t
    {
        static constexpr bool value = false;
    };

    template<typename U, typename P>
    struct is_contiguous_container_t<vector<U, P>>
    {
        static constexpr bool value = true;
    };

    template<typename U, int SIZE>
    struct is_contiguous_container_t<array<U, SIZE>>
    {
        static constexpr bool value = true;
    };

} // namespace std

#endif //CONTAINER_TRAITS_H
