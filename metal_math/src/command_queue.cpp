//
// Created by Samuel Whitton on 26/7/22.
//

#include "command_queue.h"

#include "device.h"

namespace metal {

    namespace GPU {

        [[nodiscard]] auto command_queue() noexcept -> MTL::CommandQueue*
        {
            static auto commandQueue = device()->newCommandQueue();
            return commandQueue;
        }

    }

} // metal