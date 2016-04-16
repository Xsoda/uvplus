#include "uvplus.hpp"

uvplus_async::uvplus_async() {
  ptr = static_cast<uv_async_t *>(get_handle_ptr());
}

int uvplus_async::init(uvplus_loop *loop, std::function<void()> async_callback) {
  this->async_callback = async_callback;
  return uv_async_init(loop->ptr, ptr, async_cb);
}

int uvplus_async::send() {
  return uv_async_send(ptr);
}

void uvplus_async::async_cb(uv_async_t *handle) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_async *>(base);
  if (self->async_callback) {
    self->async_callback();
  }
}
