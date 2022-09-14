//
// Created by Samuel Whitton on 19/7/22.
//

#include "include/metal_allocator.h"

#include "src/device.h"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace {

    constexpr auto MINIMUM_BUCKET_BYTE_SIZE_ALLOCATION = std::size_t{8};

    auto bucketSizeToRaw = std::unordered_map<std::size_t,std::vector<void*>>{};;
    auto rawToMetalBuffer = std::unordered_map<void*,MTL::Buffer*>{};;

    constexpr auto bucket_size_from_actual_size(std::size_t size) noexcept
    {
        return static_cast<std::size_t>(std::pow(2, std::ceil(std::log2(std::max(size, MINIMUM_BUCKET_BYTE_SIZE_ALLOCATION)))));
    }

}

namespace metal {

    [[nodiscard]] auto to_metal_buffer(void* address) noexcept -> MTL::Buffer*
    {

        return rawToMetalBuffer[address];
    }

    [[nodiscard]] auto allocate_metal_buffer(std::size_t sizeInBytes) noexcept  -> void*
    {
        {
            const auto bucketSize = bucket_size_from_actual_size(sizeInBytes);

            if (!bucketSizeToRaw.contains(bucketSize))
            {
                bucketSizeToRaw[bucketSize] = std::vector<void*>{};
            }

            if (bucketSizeToRaw[bucketSize].empty())
            {
                auto newMetalBuffer = metal::GPU::device()->newBuffer(bucketSize, MTL::ResourceStorageModeShared);
                rawToMetalBuffer[newMetalBuffer->contents()] = newMetalBuffer;
                bucketSizeToRaw[bucketSize].emplace_back(newMetalBuffer->contents());
            }

            auto returnValue = bucketSizeToRaw[bucketSize].back();
            bucketSizeToRaw[bucketSize].pop_back();
            return returnValue;
        }
    }

    auto deallocate_metal_buffer(std::size_t sizeInBytes, void* rawMetalBuffer) noexcept -> void
    {
        bucketSizeToRaw[bucket_size_from_actual_size(sizeInBytes)].emplace_back(rawMetalBuffer);
    }

} // metal