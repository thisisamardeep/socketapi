#ifndef __sockpp_datagram_socket_h
#define __sockpp_datagram_socket_h
#include "sockpp/socket.h"

namespace sockpp {

    class datagram_socket : public socket {
        using base = socket;
        // Non-copyable
        datagram_socket(const datagram_socket &) = delete;
        datagram_socket &operator=(const datagram_socket &) = delete;

    protected:
        static result<socket_t> create_handle(int domain, int protocol = 0) {
            return check_socket(socket_t(::socket(domain, COMM_TYPE, protocol)));
        }

    public:
        static constexpr int COMM_TYPE = SOCK_DGRAM;
        datagram_socket() noexcept {};
        explicit datagram_socket(socket_t handle) : base(handle) { std::cout << 56; }
    };
    template<typename ADDR>
    class datagram_socket_tmpl : public datagram_socket {
        using base = datagram_socket;

    public:
        static constexpr sa_family_t ADDRESS_FAMILY = ADDR::ADDRESS_FAMILY;
        datagram_socket_tmpl() : base(create_handle(ADDRESS_FAMILY).value_or_throw()) {};
        result<> bind(const ADDR &addr) { return base::bind(addr); }
    };

} // namespace sockpp

#endif // __sockpp_datagram_socket_h
