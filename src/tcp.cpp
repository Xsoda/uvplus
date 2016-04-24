#include "uvplus.hpp"

uvplus_tcp::uvplus_tcp() {
}

int uvplus_tcp::init(uvplus_loop &loop) {
  this->uvplus_handle::init();
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_init(loop.context_ptr(), tcp);
}

int uvplus_tcp::init_ex(uvplus_loop &loop, int flags) {
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_init_ex(loop.context_ptr(), tcp, flags);
}

int uvplus_tcp::open(uv_os_sock_t sock) {
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_open(tcp, sock);
}

int uvplus_tcp::nodelay(int enable) {
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_nodelay(tcp, enable);
}

int uvplus_tcp::keepalive(int enable, unsigned int delay) {
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_keepalive(tcp, enable, delay);
}

int uvplus_tcp::simultaneous_accepts(int enable) {
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_simultaneous_accepts(tcp, enable);
}

int uvplus_tcp::bind4(const char *ipv4, int port) {
   struct sockaddr_in addr;
   int r = uv_ip4_addr(ipv4, port, &addr);
   if (r < 0)
      return r;
   return bind((const sockaddr *)&addr, 0);
}

int uvplus_tcp::bind6(const char *ipv6, int port) {
   struct sockaddr_in6 addr;
   int r = uv_ip6_addr(ipv6, port, &addr);
   if (r < 0)
      return r;
   return bind((const sockaddr *)&addr, 0);
}

int uvplus_tcp::bind(const sockaddr *addr, unsigned int flags) {
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_bind(tcp, addr, flags);
}

int uvplus_tcp::getsockname(struct sockaddr *name, int *namelen) {
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_getsockname(tcp, name, namelen);
}

int uvplus_tcp::getpeername(struct sockaddr *name, int *namelen) {
  auto tcp = (uv_tcp_t *)context_ptr();
  return uv_tcp_getpeername(tcp, name, namelen);
}

int uvplus_tcp::connect4(const char *ipv4, int port, std::function<void(uvplus_tcp *self, int status)> connect_callback) {
   struct sockaddr_in addr;
   int r = uv_ip4_addr(ipv4, port, &addr);
   if (r < 0)
      return r;
   return connect((const struct sockaddr *)&addr, connect_callback);
}

int uvplus_tcp::connect6(const char *ipv6, int port, std::function<void(uvplus_tcp *self, int status)> connect_callback) {
   struct sockaddr_in6 addr;
   int r = uv_ip6_addr(ipv6, port, &addr);
   if (r < 0)
      return r;
   return connect((const struct sockaddr *)&addr, connect_callback);
}

int uvplus_tcp::connect(const struct sockaddr *addr, std::function<void(uvplus_tcp *self, int status)> connect_callback) {
  uv_connect_t *req = new uv_connect_t;
  auto connect_callback_ptr = new std::function<void(uvplus_tcp *self, int status)>(connect_callback);
  auto tcp = (uv_tcp_t *)context_ptr();
  req->data = static_cast<void *>(connect_callback_ptr);
  return uv_tcp_connect(req, tcp, addr, connect_cb);
}

void uvplus_tcp::connect_cb(uv_connect_t *req, int status) {
  uv_stream_t *stream = req->handle;
  auto connect_callback = static_cast<std::function<void(uvplus_tcp *self, int status)> *>(req->data);
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_tcp *>(handle);
  if (*connect_callback) {
    (*connect_callback)(self, status);
  }
  delete connect_callback;
  delete req;
}
  
