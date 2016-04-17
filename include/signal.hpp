#ifndef __UVPLUS__SIGNAL_HPP__
#define __UVPLUS__SIGNAL_HPP__

class uvplus_signal : public uvplus_handle {
public:
  uvplus_signal();
  int init(uvplus_loop *loop);
  int start(int signum, std::function<void(int signum)> signal_callback);
  int stop();
private:
  std::function<void(int signum)> signal_callback;

  static void signal_cb(uv_signal_t *signal, int signum);
};
#endif  // !__UVPLUS__SIGNAL_HPP__
