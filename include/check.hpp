#ifndef __UVPLUS__CHECK_HPP__
#define __UVPLUS__CHECK_HPP__

class uvplus_check : public uvplus_handle {
 public:
  uvplus_check();
  int init(uvplus_loop *loop);
  int start(std::function<void()> check_callback);
  int stop();
 private:
  std::function<void()> check_callback;

  static void check_cb(uv_check_t *handle);
};

#endif  // !__UVPLUS__CHECK_HPP__
