#ifndef __sockpp_error_h
#define __sockpp_error_h
#include <string>
#include <system_error>
#include "sockpp/platform.h"
namespace sockpp {
    using error_code = std::error_code;
    using error_category = std::error_category;
    using errc = std::errc;
    enum class gai_errc {
        host_not_found_try_again = EAI_AGAIN,
        invalid_argument = EAI_BADFLAGS,
        no_recovery = EAI_FAIL,
        address_family_not_supported = EAI_FAMILY,
        no_memory = EAI_MEMORY,
        host_not_found = EAI_NONAME,
        addr_family_not_supported = EAI_FAMILY,
        no_addr_in_family = EAI_ADDRFAMILY,
        no_network_add = EAI_NODATA,
        service_not_found = EAI_SERVICE,
        socket_type_not_supported = EAI_SOCKTYPE,
        system_error = EAI_SYSTEM,
    };
} // namespace sockpp
namespace std {
    template<>
    struct is_error_code_enum<::sockpp::gai_errc> : true_type {};
} // namespace std
namespace detail {
    class gai_errc_category : public std::error_category {
    public:
        std::string message(int c) const override final {
            const char *s = gai_strerror(c);
            return s ? std::string(s) : std::string();
        }
        const char *name() const noexcept override final { return "GetAddrInfoError"; }
    };
} // namespace detail
namespace sockpp {

    const ::detail::gai_errc_category &gai_errc_category();
    inline ::std::error_code make_error_code(gai_errc e) {
        if (e == gai_errc::system_error)
            return {errno, std::system_category()};
        return {static_cast<int>(e), gai_errc_category()};
    }
} // namespace sockpp
#endif // __sockpp_exception_h
