#ifndef __UVPLUS__LOOP_H__
#define __UVPLUS__LOOP_H__

class uvplus_loop {
  friend class uvplus_tcp;
  friend class uvplus_udp;
  friend class uvplus_timer;
  friend class uvplus_prepare;
  friend class uvplus_check;
  friend class uvplus_idle;
  friend class uvplus_async;
  friend class uvplus_poll;
public:
  uvplus_loop();
  int init();
  int close();
  int run(uv_run_mode mode);
  int alive();
  void stop();
  int backend_fd();
  int backend_timeout();
  uint64_t now();
  void update_time();
  void walk(std::function<void(uvplus_handle *handle, void *arg)> walk_callback, void *arg);
private:
  uv_loop_t *ptr;
  uv_loop_t loop;

  std::function<void(uvplus_handle *handle, void *arg)> walk_callback;

  static void walk_cb(uv_handle_t *handle, void *arg);
};

#endif  /* !__UVPLUS__LOOP_H__ */
