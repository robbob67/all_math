//
// Created by Samuel Whitton on 26/7/22.
//

#include "device.h"
#include <iostream>

namespace metal {

    namespace GPU {

        [[nodiscard]] auto device() noexcept -> MTL::Device*
        {
            static auto device = MTL::CreateSystemDefaultDevice();
            std::cout << "sadfsd:" << device->name()->utf8String() << "\n";
            return device;
        }

    }

} // metal