#include "uvplus.hpp"

uvplus_prepare::uvplus_prepare() {
}

int uvplus_prepare::init(uvplus_loop &loop) {
  this->uvplus_handle::init();
  auto handle = (uv_prepare_t *)context_ptr();
  return uv_prepare_init(loop.context_ptr(), handle);
}

int uvplus_prepare::start(std::function<void(uvplus_prepare *self)> prepare_callback) {
  auto handle = (uv_prepare_t *)context_ptr();
  this->prepare_callback = prepare_callback;
  return uv_prepare_start(handle, prepare_cb);
}

int uvplus_prepare::stop() {
  auto handle = (uv_prepare_t *)context_ptr();
  return uv_prepare_stop(handle);
}

void uvplus_prepare::prepare_cb(uv_prepare_t *handle) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_prepare *>(base);
  if (self->prepare_callback) {
    self->prepare_callback(self);
  }
}
