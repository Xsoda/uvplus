#ifndef __UVPLUS__PREPARE_HPP__
#define __UVPLUS__PREPARE_HPP__

class uvplus_prepare : public uvplus_handle {
public:
  uvplus_prepare();
  int init(uvplus_loop *loop);
  int start(std::function<void()> prepare_callback);
  int stop();
private:
  std::function<void()> prepare_callback;

  static void prepare_cb(uv_prepare_t *handle);
};

#endif  // !__UVPLUS__PREPARE_HPP__
