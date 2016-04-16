#include "uvplus.hpp"

uvplus_pipe::uvplus_pipe() {
  ptr = static_cast<uv_pipe_t *>(get_handle_ptr());
}

int uvplus_pipe::init(uvplus_loop *loop, int ipc) {
  return uv_pipe_init(loop->ptr, ptr, ipc);
}

int uvplus_pipe::open(uv_file file) {
  return uv_pipe_open(ptr, file);
}

int uvplus_pipe::bind(const char *name) {
  return uv_pipe_bind(ptr, name);
}

void uvplus_pipe::connect(const char *name, std::function<void(int status)> connect_callback) {
  auto req = new uv_connect_t;
  req->data = new std::function<void(int status)>(connect_callback);
  uv_pipe_connect(req, ptr, name, connect_cb);
}

int uvplus_pipe::getsockname(char *buffer, size_t *size) {
  return uv_pipe_getsockname(ptr, buffer, size);
}

int uvplus_pipe::getpeername(char *buffer, size_t *size) {
  return uv_pipe_getpeername(ptr, buffer, size);
}

void uvplus_pipe::pending_instances(int count) {
  uv_pipe_pending_instances(ptr, count);
}

int uvplus_pipe::pending_count() {
  return uv_pipe_pending_count(ptr);
}

void uvplus_pipe::connect_cb(uv_connect_t *req, int status) {
  auto stream = req->handle;
  auto base = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_pipe *>(base);
  auto connect_callback = static_cast<std::function<void(int status)> *>(req->data);
  if (*connect_callback) {
    (*connect_callback)(status);
  }
  delete connect_callback;
  delete req;
}

