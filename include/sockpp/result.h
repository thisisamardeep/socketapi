#ifndef __sockpp_result_h
#define __sockpp_result_h
#include "sockpp/error.h"
#include "sockpp/platform.h"
#include "sockpp/types.h"
#include <iostream>
namespace sockpp {
struct none {};
template <typename T = none> class result {
private:
  T val_{};
  error_code err_{};
public:
  result() = default;
  result(const T &val) {}
  result(T &&val) : val_{std::move(val)} {}
  // in namespace sockpp
  // in namespace sockpp
  // in namespace sockpp
  const T &value() const { return val_; };
  explicit operator bool() const { return !bool(err_); }
  // in namespace sockpp
  // in namespace sockpp
  // in namespace sockpp
  const error_code &error() const { return err_; }
  result(const error_code &err) : err_{err} {}
  result(error_code &&err) : err_{std::move(err)} {}
  // in namespace sockpp
  // in namespace sockpp
  // in namespace sockpp
  static int get_last_errno() {
    int err = errno;
    return err;
  }
  // in namespace sockpp
  // in namespace sockpp
  // in namespace sockpp
  static error_code last_error() {
    int err = get_last_errno();
    return error_code{err, std::system_category()};
  }
};
} // namespace sockpp
#endif // __sockpp_result_h
