#ifndef __sockpp_sock_address_h
#define __sockpp_sock_address_h
namespace sockpp {
    class sock_address {
    public:
        virtual ~sock_address() noexcept {};
        virtual sockaddr *sockaddr_ptr() = 0;
        virtual const sockaddr *sockaddr_ptr() const = 0;
        virtual sa_family_t family() const {
            auto p = sockaddr_ptr();
            return p ? p->sa_family : AF_UNSPEC;
        }
        virtual socklen_t size() const = 0;
    };
} // namespace sockpp
#endif // __sockpp_sock_address_h
