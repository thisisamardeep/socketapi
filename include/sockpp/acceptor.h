#ifndef __sockpp_acceptor_h
#define __sockpp_acceptor_h
#include <asm-generic/socket.h>
#include "result.h"
#include "sock_address.h"
#include "sockpp/socket.h"
#include "stream_socket.h"
namespace sockpp {
    class acceptor : public socket {
        using base = socket;

    public:
        static constexpr int DFLT_QUE_SIZE = 4;
        static constexpr int REUSE = SO_REUSEPORT;
        acceptor() {}
        explicit acceptor(socket_t handle) noexcept : base(handle) {}
        acceptor(const sockpp::sock_address &addr, int queSize = DFLT_QUE_SIZE, int reuse = 0) {
            if (auto res = open(addr, queSize, reuse); !res) {
            }
        }
        result<> open(const sock_address &addr, int queSize = DFLT_QUE_SIZE, int reuse = 0) noexcept;
        static result<socket_t> create_handle(int domain) { return stream_socket::create_handle(domain); }
        result<> listen(int queSize = DFLT_QUE_SIZE) { return check_res_none(::listen(handle(), queSize)); }
    };
} // namespace sockpp
#endif // __sockpp_acceptor_h
