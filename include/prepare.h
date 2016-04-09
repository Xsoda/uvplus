#ifndef __UVPLUS__PREPARE_H__
#define __UVPLUS__PREPARE_H__

class uvplus_prepare : public uvplus_handle {
public:
  uvplus_prepare();
  int init(uvplus_loop *loop);
  int start(std::function<void()> prepare_callback);
  int stop();
private:
  uv_prepare_t *ptr;

  std::function<void()> prepare_callback;

  static void prepare_cb(uv_prepare_t *handle);
};

#endif  /* !__UVPLUS__PREPARE_H__ */
