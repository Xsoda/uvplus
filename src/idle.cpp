#include "uvplus.hpp"

uvplus_idle::uvplus_idle() {
  ptr = static_cast<uv_idle_t *>(get_handle_ptr());
}

int uvplus_idle::init(uvplus_loop *loop) {
  return uv_idle_init(loop->ptr, ptr);
}

int uvplus_idle::start(std::function<void()> idle_callback) {
  this->idle_callback = idle_callback;
  return uv_idle_start(ptr, idle_cb);
}

int uvplus_idle::stop() {
  return uv_idle_stop(ptr);
}

void uvplus_idle::idle_cb(uv_idle_t *handle) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_idle *>(base);
  if (self->idle_callback) {
    self->idle_callback();
  }
}

