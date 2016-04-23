#include "uvplus.hpp"

uvplus_udp::uvplus_udp() {
}

int uvplus_udp::init(uvplus_loop *loop) {
  this->uvplus_handle::init();
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_init(loop->context_ptr(), udp);
}

int uvplus_udp::init_ex(uvplus_loop *loop, unsigned int flags) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_init_ex(loop->context_ptr(), udp, flags);
}

int uvplus_udp::open(uv_os_sock_t sock) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_open(udp, sock);
}

int uvplus_udp::bind(const struct sockaddr *addr, unsigned int flags) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_bind(udp, addr, flags);
}

int uvplus_udp::getsockname(struct sockaddr *name, int *namelen) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_getsockname(udp, name, namelen);
}

int uvplus_udp::set_membership(const char *multicast_addr, const char *interface_addr, uv_membership membership) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_set_membership(udp, multicast_addr, interface_addr, membership);
}

int uvplus_udp::set_multicast_loop(int on) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_set_multicast_loop(udp, on);
}

int uvplus_udp::set_multicast_ttl(int ttl) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_set_multicast_ttl(udp, ttl);
}

int uvplus_udp::set_multicast_interface(const char *interface_addr) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_set_multicast_interface(udp, interface_addr);
}

int uvplus_udp::set_broadcast(int on) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_set_broadcast(udp, on);
}

int uvplus_udp::set_ttl(int ttl) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_set_ttl(udp, ttl);
}

int uvplus_udp::send(const uv_buf_t bufs[], unsigned int nbufs, const struct sockaddr *addr, std::function<void(int status)> send_callback) {
  auto req = new uv_udp_send_t;
  auto send_callback_ptr = new std::function<void(int status)>(send_callback);
  auto udp = (uv_udp_t *)context_ptr();
  req->data = static_cast<void *>(send_callback_ptr);
  return uv_udp_send(req, udp, bufs, nbufs, addr, send_cb);
}

int uvplus_udp::try_send(const uv_buf_t bufs[], unsigned int nbufs, const struct sockaddr *addr) {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_try_send(udp, bufs, nbufs, addr);
}

int uvplus_udp::recv_start(std::function<void(size_t suggested_size, uv_buf_t *buf)> alloc_callback,
                           std::function<void(ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags)> recv_callback) {
  auto udp = (uv_udp_t *)context_ptr();
  this->alloc_callback = alloc_callback;
  this->recv_callback = recv_callback;
  return uv_udp_recv_start(udp, alloc_cb, recv_cb);
}
int uvplus_udp::recv_stop() {
  auto udp = (uv_udp_t *)context_ptr();
  return uv_udp_recv_stop(udp);
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

