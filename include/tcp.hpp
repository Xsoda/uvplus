#ifndef __UVPLUS__TCP_HPP__
#define __UVPLUS__TCP_HPP__

class uvplus_tcp : public uvplus_stream {
public:
  uvplus_tcp();
  int init(uvplus_loop *loop);
  int init_ex(uvplus_loop *loop, int flags);
  int open(int fd);
  int nodelay(int enable);
  int keepalive(int enable, unsigned int delay);
  int simultaneous_accepts(int enable);
  int bind(const sockaddr *addr, unsigned int flags);
  int getsockname(struct sockaddr *name, int *namelen);
  int getpeername(struct sockaddr *name, int *namelen);
  int connect(const struct sockaddr *addr, std::function<void(int status)> connect_callback);
private:
  uv_tcp_t *ptr;

  static void connect_cb(uv_connect_t *req, int status);
  std::function<void(int status)> connect_callback;
};

#endif  // !__UVPLUS__TCP_HPP__
