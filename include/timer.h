#ifndef __UVPLUS__TIMER_H__
#define __UVPLUS__TIMER_H__

class uvplus_timer : public uvplus_handle {
public:
  uvplus_timer();
  int init(uvplus_loop *loop);
  int start(uint64_t timeout, uint64_t repeat, std::function<void()> timer_callback);
  int stop();
  int again();
  void set_repeat(uint64_t repeat);
  uint64_t get_repeat();
private:
  uv_timer_t *ptr;

  std::function<void()> timer_callback;

  static void timer_cb(uv_timer_t *timer);
};
#endif  /* !__UVPLUS__TIMER_H__ */
