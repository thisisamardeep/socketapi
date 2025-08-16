#ifndef __sockpp_stream_socket_h
#define __sockpp_stream_socket_h
#include <vector>
#include "result.h"
#include "sockpp/socket.h"
#include "types.h"
namespace sockpp {
    class stream_socket : public socket {
        using base = socket;

    protected:
        friend class acceptor;

        static result<socket_t> create_handle(int domain, int protocol = 0) {
            return base::create_handle(domain, COMM_TYPE, protocol);
        }

    public:
        static constexpr int COMM_TYPE = SOCK_STREAM;
    };
} // namespace sockpp
#endif // __sockpp_socket_h
