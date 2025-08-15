#include "sockpp/error.h"
namespace sockpp {
    // in namespace sockpp
    const ::detail::gai_errc_category &gai_errc_category() {
        static ::detail::gai_errc_category c;
        return c;
    }
} // namespace sockpp
