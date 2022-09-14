//
// Created by Samuel Whitton on 26/7/22.
//

#include "create_function.h"

#include <unordered_map>
#include <algorithm>
#include <string>

// DEBUG ONLY
#include <iostream>

#include "library.h"
#include "device.h"

namespace {

    constexpr static auto METAL_FUNCTIONS = std::array{"add_two_int_vectors", "multiply_two_int_matrices"};

    static auto metalFunctionMapping = ([](){
        auto metalFunctionMapping = std::unordered_map<std::string, MTL::ComputePipelineState*>{};

        std::for_each(std::begin(METAL_FUNCTIONS), std::end(METAL_FUNCTIONS), [&metalFunctionMapping](const auto& metalFunction){
            auto metalFunctionNSString = NS::String::string(metalFunction, NS::ASCIIStringEncoding);
            auto function = metal::GPU::library()->newFunction(metalFunctionNSString);
            if(function == nullptr) {
                std::cout << "could not load function" << std::endl;
                // TODO: Proper error handling here
            } else {
                std::cout << "did load function " << function->name()->utf8String() << std::endl;
            }
            metalFunctionNSString->release();
            NS::Error* error = nullptr;
            metalFunctionMapping[metalFunction] = metal::GPU::device()->newComputePipelineState(function, &error);
            function->release();
            if (error != nullptr)
            {
                error->release();
            }
        });

        return metalFunctionMapping;
    })();

}

namespace metal {

    namespace GPU {

        [[nodiscard]] auto create_function(std::string_view functionName) noexcept -> function
        {
            return function{metalFunctionMapping[std::string{functionName}]};
        }

    }

} // metal