//
// Created by Samuel Whitton on 19/7/22.
//

#ifndef MYMETAL_METAL_ALLOCATOR_H
#define MYMETAL_METAL_ALLOCATOR_H

#include "metal_definition.h"

#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <limits>
#include <unordered_map>
#include <iostream>

#include "container_traits.h"

namespace MTL {
    class Buffer;
}

namespace metal {

    [[nodiscard]] auto allocate_metal_buffer(std::size_t sizeInBytes) noexcept  -> void*;

    auto deallocate_metal_buffer(std::size_t sizeInBytes, void* rawMetalBuffer) noexcept -> void;

    [[nodiscard]] auto to_metal_buffer(void* address) noexcept -> MTL::Buffer*;

    template <class T>
    class [[nodiscard]] metal_allocator
    {

    public:

        using value_type = T;

        [[nodiscard]] constexpr metal_allocator() noexcept = default;

        template <class U> [[nodiscard]] constexpr metal_allocator(const metal_allocator<U>&) noexcept {}

        [[nodiscard]] auto allocate(auto size) const -> T *const
        {
            if (size > std::numeric_limits<std::size_t>::max() / sizeof(T))
            {
                throw std::bad_array_new_length();
            }

            if (auto p = reinterpret_cast<T*>(allocate_metal_buffer(size*sizeof(T))))
            {
                return p;
            }

            throw std::bad_alloc();
        }

        auto deallocate(auto address, auto size) const -> void
        {
            deallocate_metal_buffer(size*sizeof(T), address);
        }

        [[nodiscard]] constexpr auto as_metal_buffer(auto address) const noexcept
        {
            return to_metal_buffer(address);
        }

    };

    template <class T, class U>
    bool operator==(const metal_allocator <T>&, const metal_allocator <U>&) { return true; }

    template <class T, class U>
    bool operator!=(const metal_allocator <T>&, const metal_allocator <U>&) { return false; }

    template<typename CONTAINER, typename VALUE_TYPE>
    concept is_base_container_t =
    requires {
        typename std::remove_reference_t<CONTAINER>::value_type;
        typename std::remove_reference_t<CONTAINER>::allocator_type;
        typename std::remove_reference_t<CONTAINER>::const_iterator;
    }
    && std::is_same_v<typename std::remove_reference_t<CONTAINER>::value_type, VALUE_TYPE>;

    template<typename CONTAINER, typename VALUE_TYPE>
    concept metal_container =
    requires {
        is_base_container_t<VALUE_TYPE, typename std::remove_reference_t<CONTAINER>>;
    }
    &&
    requires(CONTAINER container) {
        { std::remove_reference_t<CONTAINER>{5} };
    }
    && std::is_same_v<typename std::remove_reference_t<CONTAINER>::allocator_type, metal_allocator<typename std::remove_reference_t<CONTAINER>::value_type>>
    && std::is_contiguous_container_t<typename std::remove_reference_t<CONTAINER>>::value;

    template<typename CONTAINER, typename VALUE_TYPE>
    concept non_metal_container =
    requires {
        is_base_container_t<VALUE_TYPE, typename std::remove_reference_t<CONTAINER>>;
    }
    &&
    requires(CONTAINER container) {
        { std::remove_reference_t<CONTAINER>{std::begin(container), std::end(container)} }; // TODO fixup
    }
    && !(std::is_same_v<typename std::remove_reference_t<CONTAINER>::allocator_type, metal_allocator<typename std::remove_reference_t<CONTAINER>::value_type>>
         && std::is_contiguous_container_t<typename std::remove_reference_t<CONTAINER>>::value);

} // metal

#endif //MYMETAL_METAL_ALLOCATOR_H

/*
 *     template<typename CONTAINER, typename BUFFER_TYPE>
    concept metal_container =
        requires {
            typename CONTAINER::value_type;
            typename CONTAINER::allocator_type;
            typename CONTAINER::const_iterator;
        }
        && std::is_convertible_v<typename CONTAINER::value_type, BUFFER_TYPE>
        && std::is_same_v<typename CONTAINER::allocator_type, metal_allocator<BUFFER_TYPE>>;


            template<typename CONTAINER, typename VALUE_TYPE>
    concept metal_container_old =
    requires {
        typename std::remove_reference_t<CONTAINER>::value_type;
        typename std::remove_reference_t<CONTAINER>::allocator_type;
        typename std::remove_reference_t<CONTAINER>::const_iterator;
    }
    && std::is_same_v<typename std::remove_reference_t<CONTAINER>::allocator_type, metal_allocator<typename std::remove_reference_t<CONTAINER>::value_type>>
    && std::is_same_v<typename std::remove_reference_t<CONTAINER>::value_type, VALUE_TYPE>;


    template<typename CONTAINER, typename VALUE_TYPE>
    concept metal_container =
    requires {
        typename std::remove_reference_t<CONTAINER>::value_type;
        typename std::remove_reference_t<CONTAINER>::allocator_type;
        typename std::remove_reference_t<CONTAINER>::const_iterator;
    }
    && std::is_same_v<typename std::remove_reference_t<CONTAINER>::allocator_type, metal_allocator<typename std::remove_reference_t<CONTAINER>::value_type>>
    && std::is_same_v<typename std::remove_reference_t<CONTAINER>::value_type, VALUE_TYPE>;


 * */
