#include "uvplus.h"

uvplus_handle::uvplus_handle() {
  ptr = &context.handle;
  ptr->data = this;
}

int uvplus_handle::is_active() {
  return uv_is_active(ptr);
}

int uvplus_handle::is_closing() {
  return uv_is_closing(ptr);
}

void uvplus_handle::close(std::function<void()> close_callback) {
  this->close_callback = close_callback;
  uv_close(ptr, close_cb);
}

void uvplus_handle::ref() {
  uv_ref(ptr);
}

void uvplus_handle::unref() {
  uv_unref(ptr);
}

int uvplus_handle::has_ref() {
  return uv_has_ref(ptr);
}

int uvplus_handle::send_buffer_size(int *value) {
  return uv_send_buffer_size(ptr, value);
}

int uvplus_handle::recv_buffer_size(int *value) {
  return uv_recv_buffer_size(ptr, value);
}

int uvplus_handle::fileno(uv_os_fd_t *fd) {
  return uv_fileno(ptr, fd);
}

void uvplus_handle::close_cb(uv_handle_t *handle) {
  uvplus_handle *self = static_cast<uvplus_handle *>(handle->data);
  if (self->close_callback) {
    self->close_callback();
  }
}
