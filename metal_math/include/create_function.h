//
// Created by Samuel Whitton on 26/7/22.
//

#ifndef MYMETAL_CREATE_FUNCTION_H
#define MYMETAL_CREATE_FUNCTION_H

#include "function.h"

namespace metal {

    namespace GPU {

        [[nodiscard]] auto create_function(std::string_view functionName) noexcept -> function;

    };

} // metal

#endif //MYMETAL_CREATE_FUNCTION_H
