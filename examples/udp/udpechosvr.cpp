#include <iostream>
#include <netinet/in.h>
#include <thread>

#include "sockpp/result.h"
#include "sockpp/socket.h"
#include "sockpp/udp6_socket.h"
#include "sockpp/udp_socket.h"
#include "sockpp/version.h"


template<typename UDPSOCK>
void run_echo(UDPSOCK sock) {
    char buf[512];

}

int main(int argc, char *argv[]) {
    std::cout << "Sample UDP echo server for 'sockpp' " << sockpp::SOCKPP_VERSION << '\n' << std::endl;
    in_port_t port = static_cast<in_port_t>(std::strtoul("12345", nullptr, 10));
    sockpp::initialize();
    sockpp::udp_socket udpsock;
    if (auto res = udpsock.bind(sockpp::inet_address("localhost", port)); !res) {
        std::cerr << "Error binding the UDP v4 socket: " << std::endl;
        return 1;
    }
    std::thread thr(run_echo<sockpp::udp_socket>, std::move(udpsock));
    thr.join();

    return 0;

    return 0;
}
