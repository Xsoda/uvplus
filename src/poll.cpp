#include "uvplus.hpp"

uvplus_poll::uvplus_poll() {
}

int uvplus_poll::init(uvplus_loop *loop, int fd) {
  this->uvplus_handle::init();
  auto handle = (uv_poll_t *)context_ptr();
  return uv_poll_init(loop->context_ptr(), handle, fd);
}

int uvplus_poll::init_socket(uvplus_loop *loop, uv_os_sock_t socket) {
  auto handle = (uv_poll_t *)context_ptr();
  return uv_poll_init_socket(loop->context_ptr(), handle, socket);
}

int uvplus_poll::start(int events, std::function<void(int status, int events)> poll_callback) {
  auto handle = (uv_poll_t *)context_ptr();
  this->poll_callback = poll_callback;
  return uv_poll_start(handle, events, poll_cb);
}

int uvplus_poll::stop() {
  auto handle = (uv_poll_t *)context_ptr();
  return uv_poll_stop(handle);
}

void uvplus_poll::poll_cb(uv_poll_t *handle, int status, int events) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_poll *>(base);
  if (self->poll_callback) {
    self->poll_callback(status, events);
  }
}
