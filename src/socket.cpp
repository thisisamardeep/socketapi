#include "sockpp/socket.h"
#include <fcntl.h>
#include <signal.h>

#include <algorithm>
#include <cstring>

#include "sockpp/error.h"

namespace sockpp {
socket_initializer::socket_initializer() { ::signal(SIGPIPE, SIG_IGN); }

socket_initializer::~socket_initializer() {}

void initialize() { socket_initializer::initialize(); }
} // namespace sockpp
