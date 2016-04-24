#include "uvplus.hpp"

uvplus_fs_event::uvplus_fs_event() {
}

int uvplus_fs_event::init(uvplus_loop &loop) {
  this->uvplus_handle::init();
  auto event = (uv_fs_event_t *)context_ptr();
  return uv_fs_event_init(loop.context_ptr(), event);
}

int uvplus_fs_event::start(const char *path, unsigned int flags, std::function<void(uvplus_fs_event *self, const char *filename, int events, int status)> fs_event_callback) {
  auto event = (uv_fs_event_t *)context_ptr();
  this->fs_event_callback = fs_event_callback;
  return uv_fs_event_start(event, fs_event_cb, path, flags);
}

int uvplus_fs_event::stop() {
  auto event = (uv_fs_event_t *)context_ptr();
  return uv_fs_event_stop(event);
}

int uvplus_fs_event::getpath(char *buffer, size_t *size) {
  auto event = (uv_fs_event_t *)context_ptr();
  return uv_fs_event_getpath(event, buffer, size);
}

void uvplus_fs_event::fs_event_cb(uv_fs_event_t *handle, const char *filename, int events, int status) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_fs_event *>(base);
  if (self->fs_event_callback) {
    self->fs_event_callback(self, filename, events, status);
  }
}
