
#include <string>
#include "catch2_version.h"
#include "sockpp/acceptor.h"
#include "sockpp/inet_address.h"
#include "sockpp/platform.h"
#include "sockpp/socket.h"
using namespace std;
TEST_CASE("acceptor handle constructor", "[acceptor]") {
    constexpr auto HANDLE = sockpp::socket_t(3);
    SECTION("valid handle") {
        sockpp::acceptor sock(HANDLE);
        REQUIRE(sock);
        REQUIRE(HANDLE == sock.handle());
    }
    SECTION("invalid handle") {
        sockpp::acceptor sock(sockpp::INVALID_SOCKET);
        REQUIRE(!sock);
    }
}
TEST_CASE("acceptor address constructor", "[acceptor]") {
    SECTION("valid address") {
        const auto ADDR = sockpp::inet_address("localhost", sockpp::TEST_PORT);
        sockpp::acceptor sock{ADDR, 4, sockpp::acceptor::REUSE};
    }
}
