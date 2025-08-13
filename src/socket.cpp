#include "sockpp/socket.h"
#include "sockpp/error.h"
#include <algorithm>
#include <cstring>
#include <fcntl.h>
#include <signal.h>
namespace sockpp {
socket_initializer::socket_initializer() { ::signal(SIGPIPE, SIG_IGN); }
socket_initializer::~socket_initializer() {}
// in namespace sockpp
// in namespace sockpp
// in namespace sockpp
void initialize() { socket_initializer::initialize(); }
} // namespace sockpp
