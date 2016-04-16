#ifndef __UVPLUS__POLL_HPP__
#define __UVPLUS__POLL_HPP__

class uvplus_poll : public uvplus_handle {
public:
  uvplus_poll();
  int init(uvplus_loop *loop, int fd);
  int init_socket(uvplus_loop *loop, uv_os_sock_t socket);
  int start(int events, std::function<void(int status, int events)> poll_callback);
  int stop();
private:
  uv_poll_t *ptr;

  std::function<void(int status, int events)> poll_callback;

  static void poll_cb(uv_poll_t *handle, int status, int events);
};

#endif  // !__UVPLUS__POLL_HPP__
