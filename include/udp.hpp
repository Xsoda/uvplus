#ifndef __UVPLUS__UDP_HPP__
#define __UVPLUS__UDP_HPP__

class uvplus_udp : public uvplus_handle {
public:
  uvplus_udp();
  int init(uvplus_loop *loop);
  int init_ex(uvplus_loop *loop, unsigned int flags);
  int open(uv_os_sock_t sock);
  int bind(const struct sockaddr *addr, unsigned int flags);
  int getsockname(struct sockaddr *name, int *namelen);
  int set_membership(const char *multicast_addr, const char *interface_addr, uv_membership membership);
  int set_multicast_loop(int on);
  int set_multicast_ttl(int ttl);
  int set_multicast_interface(const char *interface_addr);
  int set_broadcast(int on);
  int set_ttl(int ttl);
  int send(const uv_buf_t bufs[], unsigned int nbufs, const struct sockaddr *addr, std::function<void(int status)> send_callback);
  int try_send(const uv_buf_t bufs[], unsigned int nbufs, const struct sockaddr *addr);
  int recv_start(std::function<void(size_t suggested_size, uv_buf_t *buf)> alloc_callback,
                 std::function<void(ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags)> recv_callback);
  int recv_stop();
private:
  uv_udp_t *ptr;
  std::function<void(size_t suggested_size, uv_buf_t *buf)> alloc_callback;
  std::function<void(ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags)> recv_callback;

  static void send_cb(uv_udp_send_t *req, int status);
  static void alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
  static void recv_cb(uv_udp_t *udp, ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags);
};

#endif  // !__UVPLUS__UDP_HPP__
