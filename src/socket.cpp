#include "sockpp/socket.h"
#include <algorithm>
#include <cstring>
#include <fcntl.h>
#include <signal.h>
#include "sockpp/error.h"
namespace sockpp {
    socket_initializer::socket_initializer() { ::signal(SIGPIPE, SIG_IGN); }
    socket_initializer::~socket_initializer() {}
    void initialize() { socket_initializer::initialize(); }
    void socket::reset(socket_t h /*=INVALID_SOCKET*/) noexcept {
        if (h != handle_) {
            std::swap(h, handle_);
            if (h != INVALID_SOCKET)
                close(h);
        }
    }

    result<> socket::close(socket_t h) noexcept { return check_res_none(::close(h)); }
    result<> socket::close() {
        if (handle_ != INVALID_SOCKET) {
            return close(release());
        }
        return error_code{};
    }


    result<> socket::set_option(int level, int optname, const void *optval, socklen_t optlen) noexcept {
        ::setsockopt(handle_, level, optname, optval, optlen);
        return check_res_none(::setsockopt(handle_, level, optname, optval, optlen));
    }
    result<> socket::bind(const sock_address &addr, int reuse) noexcept {
        if (reuse) {
            if (reuse != SO_REUSEADDR && reuse != SO_REUSEPORT) {
                return errc::invalid_argument;
            }
            if (auto res = set_option(SOL_SOCKET, reuse, true); !res) {
                return res;
            }
        }
        return check_res_none(::bind(handle_, addr.sockaddr_ptr(), addr.size()));
    }
} // namespace sockpp
