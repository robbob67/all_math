//
// Created by Samuel Whitton on 26/7/22.
//

#ifndef MYMETAL_LIBRARY_H
#define MYMETAL_LIBRARY_H

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "QuartzCore/QuartzCore.hpp"

namespace metal {

    namespace GPU {

        [[nodiscard]] auto library() noexcept -> MTL::Library*;

    };

} // metal

#endif //MYMETAL_LIBRARY_H
