#include "uvplus.hpp"

uvplus_handle::uvplus_handle() {
  context = nullptr;
}

uvplus_handle::~uvplus_handle() {
  if (context) {
    if (is_active()) {
      close();
      uv_run(context->handle.loop, UV_RUN_DEFAULT);
    }
    delete context;
  }
}

uvplus_handle::uvplus_handle(uvplus_handle &&other) {
  context = other.context;
  other.context = nullptr;
}

uvplus_handle &uvplus_handle::operator=(uvplus_handle &&other) {
  context = other.context;
  other.context = nullptr;
  return *this;
}

void uvplus_handle::init() {
  context = new uv_any_handle;
  context->handle.data = static_cast<void *>(this);
}

uv_handle_t *uvplus_handle::context_ptr() {
  if (context)
    return &context->handle;
  return nullptr;
}

int uvplus_handle::is_active() {
  return uv_is_active(&context->handle);
}

int uvplus_handle::is_closing() {
  return uv_is_closing(&context->handle);
}

void uvplus_handle::close(std::function<void()> close_callback) {
  this->close_callback = close_callback;
  uv_close(&context->handle, close_cb);
}

void uvplus_handle::ref() {
  uv_ref(&context->handle);
}

void uvplus_handle::unref() {
  uv_unref(&context->handle);
}

int uvplus_handle::has_ref() {
  return uv_has_ref(&context->handle);
}

int uvplus_handle::send_buffer_size(int *value) {
  return uv_send_buffer_size(&context->handle, value);
}

int uvplus_handle::recv_buffer_size(int *value) {
  return uv_recv_buffer_size(&context->handle, value);
}

int uvplus_handle::fileno(uv_os_fd_t *fd) {
  return uv_fileno(&context->handle, fd);
}

void uvplus_handle::close_cb(uv_handle_t *handle) {
  uvplus_handle *self = static_cast<uvplus_handle *>(handle->data);
  if (self->close_callback) {
    self->close_callback();
  }
}
