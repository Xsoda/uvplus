#ifndef __UVPLUS__IDLE_HPP__
#define __UVPLUS__IDLE_HPP__

class uvplus_idle : public uvplus_handle {
 public:
  uvplus_idle();
  int init(uvplus_loop *loop);
  int start(std::function<void()> idle_callback);
  int stop();
 private:
  uv_idle_t *ptr;

  std::function<void()> idle_callback;

  static void idle_cb(uv_idle_t *handle);
};

#endif  // !__UVPLUS__IDLE_H__
