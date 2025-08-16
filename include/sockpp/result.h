#ifndef __sockpp_result_h
#define __sockpp_result_h
#include <iostream>
#include "sockpp/error.h"
#include "sockpp/platform.h"
#include "sockpp/types.h"
namespace sockpp {
    struct none {};
    template<typename T = none>
    class result {
    private:
        T val_{};
        error_code err_{};

    public:
        result() = default;
        result(const T &val) : val_{val} { std::cout << 45; }
        result(T &&val) : val_{std::move(val)} {}
        const T &value() const { return val_; };
        explicit operator bool() const { return !bool(err_); }
        const error_code &error() const { return err_; }
        result(const error_code &err) : err_{err} {}
        result(errc err) {}
        result(error_code &&err) : err_{std::move(err)} {}
        static int get_last_errno() {
            int err = errno;
            return err;
        }
        const T &value_or_throw() const {
            if (err_)
                throw std::system_error{err_};
            return val_;
        }
        static error_code last_error() {
            int err = get_last_errno();
            return error_code{err, std::system_category()};
        }
        static result from_last_error() { return result{last_error()}; }
    };
} // namespace sockpp
#endif // __sockpp_result_h
