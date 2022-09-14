//
// Created by Samuel Whitton on 26/7/22.
//

#ifndef MYMETAL_DEVICE_H
#define MYMETAL_DEVICE_H

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "QuartzCore/QuartzCore.hpp"

namespace metal {

    namespace GPU {

        [[nodiscard]] auto device() noexcept -> MTL::Device*;

    };

} // metal

#endif //MYMETAL_DEVICE_H
