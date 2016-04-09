#include "uvplus.h"

uvplus_udp::uvplus_udp() {
  ptr = static_cast<uv_udp_t *>(get_handle_ptr());
}

int uvplus_udp::init(uvplus_loop *loop) {
  return uv_udp_init(loop->ptr, ptr);
}

int uvplus_udp::init_ex(uvplus_loop *loop, unsigned int flags) {
  return uv_udp_init_ex(loop->ptr, ptr, flags);
}

int uvplus_udp::open(uv_os_sock_t sock) {
  return uv_udp_open(ptr, sock);
}

int uvplus_udp::bind(const struct sockaddr *addr, unsigned int flags) {
  return uv_udp_bind(ptr, addr, flags);
}

int uvplus_udp::getsockname(struct sockaddr *name, int *namelen) {
  return uv_udp_getsockname(ptr, name, namelen);
}

int uvplus_udp::set_membership(const char *multicast_addr, const char *interface_addr, uv_membership membership) {
  return uv_udp_set_membership(ptr, multicast_addr, interface_addr, membership);
}

int uvplus_udp::set_multicast_loop(int on) {
  return uv_udp_set_multicast_loop(ptr, on);
}

int uvplus_udp::set_multicast_ttl(int ttl) {
  return uv_udp_set_multicast_ttl(ptr, ttl);
}

int uvplus_udp::set_multicast_interface(const char *interface_addr) {
  return uv_udp_set_multicast_interface(ptr, interface_addr);
}

int uvplus_udp::set_broadcast(int on) {
  return uv_udp_set_broadcast(ptr, on);
}

int uvplus_udp::set_ttl(int ttl) {
  return uv_udp_set_ttl(ptr, ttl);
}

int uvplus_udp::send(const uv_buf_t bufs[], unsigned int nbufs, const struct sockaddr *addr, std::function<void(int status)> send_callback) {
  auto req = new uv_udp_send_t;
  auto send_callback_ptr = new std::function<void(int status)>(send_callback);
  req->data = static_cast<void *>(send_callback_ptr);
  return uv_udp_send(req, ptr, bufs, nbufs, addr, send_cb);
}
int uvplus_udp::try_send(const uv_buf_t bufs[], unsigned int nbufs, const struct sockaddr *addr) {
  return uv_udp_try_send(ptr, bufs, nbufs, addr);
}

int uvplus_udp::recv_start(std::function<void(size_t suggested_size, uv_buf_t *buf)> alloc_callback,
                           std::function<void(ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags)> recv_callback) {
  this->alloc_callback = alloc_callback;
  this->recv_callback = recv_callback;
  return uv_udp_recv_start(ptr, alloc_cb, recv_cb);
}
int uvplus_udp::recv_stop() {
  return uv_udp_recv_stop(ptr);
}

void uvplus_udp::send_cb(uv_udp_send_t *req, int status) {
  auto udp = req->handle;
  auto send_callback = static_cast<std::function<void(int status)> *>(req->data);
  auto handle = static_cast<uvplus_handle *>(udp->data);
  auto self = static_cast<uvplus_udp *>(handle);
  if (*send_callback) {
    (*send_callback)(status);
  }
  delete send_callback;
  delete req;
}

void uvplus_udp::alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_udp *>(base);
  if (self->alloc_callback) {
    self->alloc_callback(suggested_size, buf);
  }
}

void uvplus_udp::recv_cb(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_udp *>(base);
  if (self->recv_callback) {
    self->recv_callback(nread, buf, addr, flags);
  }
}

