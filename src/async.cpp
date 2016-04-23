#include "uvplus.hpp"

uvplus_async::uvplus_async() {
}

int uvplus_async::init(uvplus_loop *loop, std::function<void()> async_callback) {
  this->uvplus_handle::init();
  auto async = (uv_async_t *)context_ptr();
  this->async_callback = async_callback;
  return uv_async_init(loop->context_ptr(), async, async_cb);
}

int uvplus_async::send() {
  auto async = (uv_async_t *)context_ptr();
  return uv_async_send(async);
}

void uvplus_async::async_cb(uv_async_t *handle) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_async *>(base);
  if (self->async_callback) {
    self->async_callback();
  }
}
