#ifndef __UVPLUS__TCP_HPP__
#define __UVPLUS__TCP_HPP__

class uvplus_tcp : public uvplus_stream {
public:
  uvplus_tcp();
  int init(uvplus_loop &loop);
  int init_ex(uvplus_loop &loop, int flags);
  int open(int fd);
  int nodelay(int enable);
  int keepalive(int enable, unsigned int delay);
  int simultaneous_accepts(int enable);
  int bind4(const char *ipv4, int port);
  int bind6(const char *ipv6, int port);
  int bind(const sockaddr *addr, unsigned int flags);
  int getsockname(struct sockaddr *name, int *namelen);
  int getpeername(struct sockaddr *name, int *namelen);
  int connect4(const char *ipv4, int prot, std::function<void(uvplus_tcp *self, int status)> connect_callback);
  int connect6(const char *ipv6, int port, std::function<void(uvplus_tcp *self, int status)> connect_callback);
  int connect(const struct sockaddr *addr, std::function<void(uvplus_tcp *self, int status)> connect_callback);
private:
  static void connect_cb(uv_connect_t *req, int status);
  std::function<void(uvplus_tcp *self, int status)> connect_callback;
};

#endif  // !__UVPLUS__TCP_HPP__
