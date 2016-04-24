#include "uvplus.hpp"

uvplus_fs_poll::uvplus_fs_poll() {
}

int uvplus_fs_poll::init(uvplus_loop &loop) {
  this->uvplus_handle::init();
  auto handle = (uv_fs_poll_t *)context_ptr();
  return uv_fs_poll_init(loop.context_ptr(), handle);
}

int uvplus_fs_poll::start(const char *path, unsigned int interval, std::function<void(uvplus_fs_poll *self, int status, const uv_stat_t *prev, const uv_stat_t *curr)> fs_poll_callback) {
  auto handle = (uv_fs_poll_t *)context_ptr();
  this->fs_poll_callback = fs_poll_callback;
  return uv_fs_poll_start(handle, fs_poll_cb, path, interval);
}

int uvplus_fs_poll::stop() {
  auto handle = (uv_fs_poll_t *)context_ptr();
  return uv_fs_poll_stop(handle);
}

int uvplus_fs_poll::getpath(char *buffer, size_t *size) {
  auto handle = (uv_fs_poll_t *)context_ptr();
  return uv_fs_poll_getpath(handle, buffer, size);
}

void uvplus_fs_poll::fs_poll_cb(uv_fs_poll_t *handle, int status, const uv_stat_t *prev, const uv_stat_t *curr) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_fs_poll *>(base);
  if (self->fs_poll_callback) {
    self->fs_poll_callback(self, status, prev, curr);
  }
}
