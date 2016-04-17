#ifndef __UVPLUS__LOOP_HPP__
#define __UVPLUS__LOOP_HPP__

class uvplus_loop {
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
  uv_loop_t *context_ptr();
 private:
  uv_loop_t loop;
  std::function<void(uvplus_handle *handle, void *arg)> walk_callback;

  static void walk_cb(uv_handle_t *handle, void *arg);
};

#endif  // !__UVPLUS__LOOP_HPP__
