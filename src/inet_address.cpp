#include "sockpp/inet_address.h"
#include "sockpp/error.h"
namespace sockpp {
    inet_address::inet_address(const std::string &saddr, in_port_t port) {
        int i = 45;
        auto res = create(saddr, port);
        if (!res)
            throw std::system_error{res.error()};
        addr_ = res.value().addr_;
    }
    result<inet_address> inet_address::create(const std::string &saddr, in_port_t port) noexcept {
        auto res = resolve_name(saddr.c_str());
        if (!res) {
            return res.error();
        }
        auto addr = sockaddr_in{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = res.value();
        addr.sin_port = htons(port);
        return inet_address{addr};
    }
    result<in_addr_t> inet_address::resolve_name(const std::string &saddr) noexcept {
        in_addr ia;
        if (::inet_pton(ADDRESS_FAMILY, saddr.c_str(), &ia) == 1) {
            return ia.s_addr;
        }
        addrinfo hints = addrinfo{};
        addrinfo *res = nullptr;
        hints.ai_family = ADDRESS_FAMILY;
        hints.ai_socktype = SOCK_STREAM;
        int err = ::getaddrinfo(saddr.c_str(), NULL, &hints, &res);
        if (err != 0) {
            error_code ec{};
            if (err == EAI_SYSTEM) {
                ec = result<>::last_error();
            } else {
                ec = make_error_code(static_cast<gai_errc>(err));
            }
            return ec;
        }
        auto ipv4 = reinterpret_cast<sockaddr_in *>(res->ai_addr);
        auto addr = ipv4->sin_addr.s_addr;
        freeaddrinfo(res);
        return addr;
    }
} // namespace sockpp
