#include "uvplus.h"

uvplus_check::uvplus_check() {
  ptr = static_cast<uv_check_t *>(get_handle_ptr());
}

int uvplus_check::init(uvplus_loop *loop) {
  return uv_check_init(loop->ptr, ptr);
}

int uvplus_check::start(std::function<void()> check_callback) {
  this->check_callback = check_callback;
  return uv_check_start(ptr, check_cb);
}

int uvplus_check::stop() {
  return uv_check_stop(ptr);
}

void uvplus_check::check_cb(uv_check_t *handle) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_check *>(base);
  if (self->check_callback) {
    self->check_callback();
  }
}
