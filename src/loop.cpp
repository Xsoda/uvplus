#include "uvplus.hpp"

uvplus_loop::uvplus_loop() {
  ptr = &loop;
  ptr->data = this;
}

int uvplus_loop::init() {
  return uv_loop_init(ptr);
}

int uvplus_loop::close() {
  return uv_loop_close(ptr);
}

int uvplus_loop::run(uv_run_mode mode) {
  return uv_run(ptr, mode);
}

int uvplus_loop::alive() {
  return uv_loop_alive(ptr);
}

void uvplus_loop::stop() {
  uv_stop(ptr);
}

int uvplus_loop::backend_fd() {
  return uv_backend_fd(ptr);
}

int uvplus_loop::backend_timeout() {
  return uv_backend_timeout(ptr);
}

uint64_t uvplus_loop::now() {
  return uv_now(ptr);
}

void uvplus_loop::update_time() {
  uv_update_time(ptr);
}

void uvplus_loop::walk(std::function<void(uvplus_handle *handle, void *arg)> walk_callback, void *arg) {
  this->walk_callback = walk_callback;
  uv_walk(ptr, walk_cb, arg);
}

void uvplus_loop::walk_cb(uv_handle_t *handle, void *arg) {
  uv_loop_t *loop = handle->loop;
  auto self = static_cast<uvplus_loop *>(loop->data);
  if (self->walk_callback) {
    self->walk_callback(static_cast<uvplus_handle *>(handle->data), arg);
  }
}
