#ifndef __sockpp_platform_h
#define __sockpp_platform_h
#include <netdb.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/tcp.h> // TCP_NODELAY, etc
#include <signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <unistd.h>
namespace sockpp {
/** Port used for example apps and unit tests */
constexpr in_port_t TEST_PORT = 12346;
} // namespace sockpp
#endif
