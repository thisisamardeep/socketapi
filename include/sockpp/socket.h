#ifndef __sockpp_socket_h
#define __sockpp_socket_h

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
  socket_t handle_{INVALID_SOCKET};

public:
  socket() = default;

  explicit socket(socket_t h) noexcept : handle_{h} {}
  socket_t handle() const { return handle_; }

  explicit operator bool() const { return handle_ != INVALID_SOCKET; }
};
} // namespace sockpp

#endif // __sockpp_socket_h
