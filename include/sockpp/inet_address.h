#ifndef __sockpp_inet_addr_h
#define __sockpp_inet_addr_h
#include <algorithm>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include "result.h"
#include "sock_address.h"
namespace sockpp {
class inet_address : public sock_address {
private:
  sockaddr_in addr_{};
  static constexpr size_t SZ = sizeof(sockaddr_in);
public:
  static constexpr sa_family_t ADDRESS_FAMILY = AF_INET;
  inet_address() = default;
  inet_address(const std::string &saddr, in_port_t port);
  inet_address(const sockaddr_in &addr) : addr_{addr} {}
  result<inet_address> create(const std::string &saddr,
                              in_port_t port) noexcept;
  result<in_addr_t> resolve_name(const std::string &saddr) noexcept;
};
} // namespace sockpp
#endif // __sockpp_inet_addr_h
