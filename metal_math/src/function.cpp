//
// Created by Samuel Whitton on 22/7/22.
//

#include "include/function.h"

#include "command_queue.h"

namespace {

    [[nodiscard]] auto createCommandBuffer() noexcept
    {
        return metal::GPU::command_queue()->commandBuffer();
    }

    [[nodiscard]] constexpr auto createCommandEncoder(auto commandBuffer, auto metalPipelineFunction) noexcept
    {
        auto computeEncoder = commandBuffer->computeCommandEncoder();
        computeEncoder->setComputePipelineState(metalPipelineFunction);
        return computeEncoder;
    }
}

namespace metal {

    [[nodiscard]] function::function(function&& other) noexcept
            : _commandBuffer{other._commandBuffer},
              _commandEncoder{other._commandEncoder},
              _numberOfParameters{other._numberOfParameters}
    {
        other._commandBuffer = nullptr;
        other._commandEncoder = nullptr;
        other._numberOfParameters = 0;
    }

    [[nodiscard]] function& function::operator=(function&& other) noexcept
    {
        this->~function();
        _commandBuffer = other._commandBuffer;
        _commandEncoder = other._commandEncoder;
        _numberOfParameters = other._numberOfParameters;
        other._commandBuffer = nullptr;
        other._commandEncoder = nullptr;
        other._numberOfParameters = 0;
        return *this;
    }

    function::~function() noexcept
    {
        if (_commandEncoder != nullptr)
        {
            _commandEncoder->release();
        }
        if (_commandBuffer != nullptr)
        {
            _commandBuffer->release();
        }
        _numberOfParameters = 0;
        _commandBuffer = nullptr;
        _commandEncoder = nullptr;
    }

    [[nodiscard]] function::function(MTL::ComputePipelineState* metalPipelineFunction) noexcept
            : _metalPipelineFunction{metalPipelineFunction},
              _commandBuffer{createCommandBuffer()},
              _commandEncoder{createCommandEncoder(_commandBuffer, metalPipelineFunction)}
    {}

} // metal