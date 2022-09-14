//
// Created by Samuel Whitton on 22/7/22.
//

#ifndef MYMETAL_FUNCTION_H
#define MYMETAL_FUNCTION_H

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#include "metal_allocator.h"

namespace metal {

    class function {

    private:

        MTL::ComputePipelineState* _metalPipelineFunction{nullptr};
        MTL::CommandBuffer* _commandBuffer{nullptr};
        MTL::ComputeCommandEncoder* _commandEncoder{nullptr};
        std::size_t _numberOfParameters{0};

    public:

        [[nodiscard]] constexpr function() noexcept = default;

        [[nodiscard]] function(const function&) = delete;

        [[nodiscard]] function& operator=(const function&) = delete;

        [[nodiscard]] function(function&& other) noexcept;

        [[nodiscard]] function& operator=(function&& other) noexcept;

        ~function() noexcept;

        [[nodiscard]] function(MTL::ComputePipelineState* metalPipelineFunction) noexcept;

        template<typename CONTAINER> requires metal_container<CONTAINER, typename std::remove_reference_t<CONTAINER>::value_type>
        [[nodiscard]] auto addParameter(CONTAINER& parameter) noexcept
        {
            _commandEncoder->setBuffer(metal::to_metal_buffer(parameter.data()), 0, _numberOfParameters++);
        }

        [[nodiscard]] auto execute()
        {
            _commandEncoder->endEncoding();
            _commandBuffer->commit();
            _commandBuffer->waitUntilCompleted();
            const auto error = _commandBuffer->error();
            if (error)
            {
                const auto errorDescription = error->localizedDescription();
                const auto errorString = std::string{"Error: " + std::string{errorDescription->utf8String()} + "\n"};
                //std::cout << "Problem is: " << errorString << std::endl;
                throw std::runtime_error(errorString);
            }
        }

        [[nodiscard]] constexpr auto setGridSize(auto gridSize) noexcept
        {
            auto width = _metalPipelineFunction->threadExecutionWidth();
            auto height = _metalPipelineFunction->maxTotalThreadsPerThreadgroup() / width;
            _commandEncoder->dispatchThreads(gridSize, MTL::Size::Make(width, height, 1));
        }

    };

} // metal

#endif //MYMETAL_FUNCTION_H





/*_commandBuffer->addCompletedHandler([callback, fail_callback](MTL::CommandBuffer* command_buffer) mutable {
    const auto error = command_buffer->error();
    if (error)
    {
        const auto errorDescription = error->localizedDescription();
        const auto errorString = std::string{"Error: " + std::string{errorDescription->utf8String()} + "\n"};
        std::cout << "Problem is: " << errorString << std::endl;
        fail_callback(errorString);
    }
    else
    {
        callback();
    }
});*/
