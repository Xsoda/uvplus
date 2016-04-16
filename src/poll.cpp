#include "uvplus.hpp"

uvplus_poll::uvplus_poll() {
  ptr = static_cast<uv_poll_t *>(get_handle_ptr());
}

int uvplus_poll::init(uvplus_loop *loop, int fd) {
  return uv_poll_init(loop->ptr, ptr, fd);
}

int uvplus_poll::init_socket(uvplus_loop *loop, uv_os_sock_t socket) {
  return uv_poll_init_socket(loop->ptr, ptr, socket);
}

int uvplus_poll::start(int events, std::function<void(int status, int events)> poll_callback) {
  this->poll_callback = poll_callback;
  return uv_poll_start(ptr, events, poll_cb);
}

int uvplus_poll::stop() {
  return uv_poll_stop(ptr);
}

void uvplus_poll::poll_cb(uv_poll_t *handle, int status, int events) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_poll *>(base);
  if (self->poll_callback) {
    self->poll_callback(status, events);
  }
}
