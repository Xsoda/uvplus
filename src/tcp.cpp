#include "uvplus.hpp"

uvplus_tcp::uvplus_tcp() {
  ptr = static_cast<uv_tcp_t *>(get_handle_ptr());
}

int uvplus_tcp::init(uvplus_loop *loop) {
  return uv_tcp_init(loop->ptr, ptr);
}

int uvplus_tcp::init_ex(uvplus_loop *loop, int flags) {
  return uv_tcp_init_ex(loop->ptr, ptr, flags);
}

int uvplus_tcp::open(uv_os_sock_t sock) {
  return uv_tcp_open(ptr, sock);
}

int uvplus_tcp::nodelay(int enable) {
  return uv_tcp_nodelay(ptr, enable);
}

int uvplus_tcp::keepalive(int enable, unsigned int delay) {
  return uv_tcp_keepalive(ptr, enable, delay);
}

int uvplus_tcp::simultaneous_accepts(int enable) {
  return uv_tcp_simultaneous_accepts(ptr, enable);
}

int uvplus_tcp::bind(const sockaddr *addr, unsigned int flags) {
  return uv_tcp_bind(ptr, addr, flags);
}

int uvplus_tcp::getsockname(struct sockaddr *name, int *namelen) {
  return uv_tcp_getsockname(ptr, name, namelen);
}

int uvplus_tcp::getpeername(struct sockaddr *name, int *namelen) {
  return uv_tcp_getpeername(ptr, name, namelen);
}

int uvplus_tcp::connect(const struct sockaddr *addr, std::function<void(int status)> connect_callback) {
  uv_connect_t *req = new uv_connect_t;
  auto connect_callback_ptr = new std::function<void(int status)>(connect_callback);
  req->data = static_cast<void *>(connect_callback_ptr);
  return uv_tcp_connect(req, ptr, addr, connect_cb);
}

void uvplus_tcp::connect_cb(uv_connect_t *req, int status) {
  uv_stream_t *stream = req->handle;
  auto connect_callback = static_cast<std::function<void(int status)> *>(req->data);
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_tcp *>(handle);
  if (*connect_callback) {
    (*connect_callback)(status);
  }
  delete connect_callback;
  delete req;
}
  
