//
// Created by Samuel Whitton on 26/7/22.
//

#include "library.h"

#include "device.h"

namespace metal {

    namespace GPU {

        [[nodiscard]] auto library() noexcept -> MTL::Library*
        {
            static auto library = device()->newDefaultLibrary();
            return library;
        }

    }

} // metal