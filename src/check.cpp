#include "uvplus.hpp"

uvplus_check::uvplus_check() {
}

int uvplus_check::init(uvplus_loop *loop) {
  auto check = (uv_check_t *)context_ptr();
  return uv_check_init(loop->context_ptr(), check);
}

int uvplus_check::start(std::function<void()> check_callback) {
  auto check = (uv_check_t *)context_ptr();
  this->check_callback = check_callback;
  return uv_check_start(check, check_cb);
}

int uvplus_check::stop() {
  auto check = (uv_check_t *)context_ptr();
  return uv_check_stop(check);
}

void uvplus_check::check_cb(uv_check_t *handle) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_check *>(base);
  if (self->check_callback) {
    self->check_callback();
  }
}
