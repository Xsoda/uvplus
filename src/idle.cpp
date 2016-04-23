#include "uvplus.hpp"

uvplus_idle::uvplus_idle() {
}

int uvplus_idle::init(uvplus_loop *loop) {
  this->uvplus_handle::init();
  auto handle = (uv_idle_t *)context_ptr();
  return uv_idle_init(loop->context_ptr(), handle);
}

int uvplus_idle::start(std::function<void()> idle_callback) {
  auto handle = (uv_idle_t *)context_ptr();
  this->idle_callback = idle_callback;
  return uv_idle_start(handle, idle_cb);
}

int uvplus_idle::stop() {
  auto handle = (uv_idle_t *)context_ptr();
  return uv_idle_stop(handle);
}

void uvplus_idle::idle_cb(uv_idle_t *handle) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_idle *>(base);
  if (self->idle_callback) {
    self->idle_callback();
  }
}

