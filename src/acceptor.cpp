#include "sockpp/acceptor.h"
#include <cstring>
using namespace std;
namespace sockpp {
    result<> acceptor::open(const sock_address &addr, int queSize /*=DFLT_QUE_SIZE*/, int reuse /*=0*/
                            ) noexcept {
        if (is_open()) {
            return result<>{none{}};
        }
        if (auto res = create_handle(addr.family()); !res) {
            return res.error();
        } else {
            reset(res.value());
        }
        if (auto res = bind(addr, reuse); !res) {
            close();
            return res;
        }
        if (auto res = listen(queSize); !res) {
            close();
            return res;
        }
        return none{};

    };
} // namespace sockpp
