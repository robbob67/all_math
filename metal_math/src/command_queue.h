//
// Created by Samuel Whitton on 26/7/22.
//

#ifndef MYMETAL_COMMAND_QUEUE_H
#define MYMETAL_COMMAND_QUEUE_H

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "QuartzCore/QuartzCore.hpp"

namespace metal {

    namespace GPU {

        [[nodiscard]] auto command_queue() noexcept -> MTL::CommandQueue*;

    };

} // metal

#endif //MYMETAL_COMMAND_QUEUE_H
