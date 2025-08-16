#ifndef __sockpp_udp_socket_h
#define __sockpp_udp_socket_h
#include "datagram_socket.h"
#include "inet_address.h"


namespace sockpp {

using udp_socket = datagram_socket_tmpl<inet_address>;
}

#endif  // __sockpp_udp_socket_h



