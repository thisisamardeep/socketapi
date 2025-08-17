#ifndef __sockpp_socket_h
#define __sockpp_socket_h
#include "result.h"
#include "sock_address.h"
namespace sockpp {
    typedef int socket_t;
    const socket_t INVALID_SOCKET = -1;
    class socket_initializer {
    private:
        socket_initializer();
        socket_initializer(const socket_initializer &) = delete;
        socket_initializer &operator=(const socket_initializer &) = delete;
        friend class socket;

    public:
        static void initialize() { static socket_initializer sock_init; }
        ~socket_initializer();
    };
    void initialize();
    class socket {
    private:
        socket_t handle_{INVALID_SOCKET};
        result<> close(socket_t h) noexcept;
        socket(const socket &) = delete;
        socket &operator=(const socket &) = delete;

    public:
        socket() = default;
        explicit socket(socket_t h) noexcept : handle_{h} {}
        socket_t handle() const { return handle_; }
        explicit operator bool() const { return handle_ != INVALID_SOCKET; }
        bool is_open() const { return handle_ != INVALID_SOCKET; }
        static result<socket_t> create_handle(int domain, int type, int protocol = 0) noexcept {
            return check_socket(socket_t(::socket(domain, type, protocol)));
        }
        virtual result<> close();
        socket(socket&& sock) noexcept : handle_{std::move(sock.handle_)} {
            sock.handle_ = INVALID_SOCKET;
        }

        static result<socket_t> check_socket(socket_t s) {
            if (s == INVALID_SOCKET) {
                return result<socket_t>::from_last_error();
            } else {
                return result<socket_t>{s};
            }
        }
        void reset(socket_t h = INVALID_SOCKET) noexcept;
        result<> bind(const sockpp::sock_address &addr, int reuse = 0) noexcept;
        result<> set_option(int level, int optname, const void *optval, socklen_t optlen) noexcept;

        template<typename T>
        result<> set_option(int level, int optname, const T &val) noexcept {
            return set_option(level, optname, &val, sizeof(T));
        }

        result<> set_option(int level, int optname, const bool &val) noexcept {
            return set_option(level, optname, int(val));
        }
        template<typename T>
        static result<> check_res_none(T ret) {
            return (ret < 0) ? result<>::from_last_error() : result<>{none{}};
        }
        virtual ~socket() { close(); }
        socket_t release() noexcept {
            socket_t h = handle_;
            handle_ = INVALID_SOCKET;
            return h;
        }
    };
} // namespace sockpp
#endif // __sockpp_socket_h
