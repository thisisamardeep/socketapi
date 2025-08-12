#ifndef __sockpp_acceptor_h
#define __sockpp_acceptor_h
#include <asm-generic/socket.h>
#include "sockpp/socket.h"
namespace sockpp {
class acceptor : public socket {
  using base = socket;
public:
  static constexpr int DFLT_QUE_SIZE = 4;
  static constexpr int REUSE = SO_REUSEPORT;
  acceptor() {}
  explicit acceptor(socket_t handle) noexcept : base(handle) {}
};
} // namespace sockpp
#endif // __sockpp_acceptor_h
