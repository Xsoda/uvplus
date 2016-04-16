#include "uvplus.hpp"

uvplus_prepare::uvplus_prepare() {
  ptr = static_cast<uv_prepare_t *>(get_handle_ptr());
}

int uvplus_prepare::init(uvplus_loop *loop) {
  return uv_prepare_init(loop->ptr, ptr);
}

int uvplus_prepare::start(std::function<void()> prepare_callback) {
  this->prepare_callback = prepare_callback;
  return uv_prepare_start(ptr, prepare_cb);
}

int uvplus_prepare::stop() {
  return uv_prepare_stop(ptr);
}

void uvplus_prepare::prepare_cb(uv_prepare_t *handle) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_prepare *>(base);
  if (self->prepare_callback) {
    self->prepare_callback();
  }
}
