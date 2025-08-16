#include <iostream>
#include <netinet/in.h>
#include <thread>

#include "sockpp/result.h"
#include "sockpp/socket.h"
#include "sockpp/udp6_socket.h"
#include "sockpp/udp_socket.h"
#include "sockpp/version.h"

int main(int argc, char *argv[]) {
    std::cout << "Sample UDP echo server for 'sockpp' " << sockpp::SOCKPP_VERSION << '\n' << std::endl;
    in_port_t port = static_cast<in_port_t>(std::strtoul("12345", nullptr, 10));
    sockpp::initialize();
    sockpp::udp_socket udpsock;

    return 0;
}
