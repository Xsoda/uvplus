#include "uvplus.hpp"

uvplus_pipe::uvplus_pipe() {
}

int uvplus_pipe::init(uvplus_loop &loop, int ipc) {
  this->uvplus_handle::init();
  auto pipe = (uv_pipe_t *)context_ptr();
  return uv_pipe_init(loop.context_ptr(), pipe, ipc);
}

int uvplus_pipe::open(uv_file file) {
  auto pipe = (uv_pipe_t *)context_ptr();
  return uv_pipe_open(pipe, file);
}

int uvplus_pipe::bind(const char *name) {
  auto pipe = (uv_pipe_t *)context_ptr();
  return uv_pipe_bind(pipe, name);
}

void uvplus_pipe::connect(const char *name, std::function<void(uvplus_pipe *self, int status)> connect_callback) {
  auto pipe = (uv_pipe_t *)context_ptr();
  auto req = new uv_connect_t;
  req->data = new std::function<void(uvplus_pipe *self, int status)>(connect_callback);
  uv_pipe_connect(req, pipe, name, connect_cb);
}

int uvplus_pipe::getsockname(char *buffer, size_t *size) {
  auto pipe = (uv_pipe_t *)context_ptr();
  return uv_pipe_getsockname(pipe, buffer, size);
}

int uvplus_pipe::getpeername(char *buffer, size_t *size) {
  auto pipe = (uv_pipe_t *)context_ptr();
  return uv_pipe_getpeername(pipe, buffer, size);
}

void uvplus_pipe::pending_instances(int count) {
  auto pipe = (uv_pipe_t *)context_ptr();
  uv_pipe_pending_instances(pipe, count);
}

int uvplus_pipe::pending_count() {
  auto pipe = (uv_pipe_t *)context_ptr();
  return uv_pipe_pending_count(pipe);
}

void uvplus_pipe::connect_cb(uv_connect_t *req, int status) {
  auto stream = req->handle;
  auto base = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_pipe *>(base);
  auto connect_callback = static_cast<std::function<void(uvplus_pipe *self, int status)> *>(req->data);
  if (*connect_callback) {
    (*connect_callback)(self, status);
  }
  delete connect_callback;
  delete req;
}

