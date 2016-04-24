#ifndef __UVPLUS__ASYNC_HPP__
#define __UVPLUS__ASYNC_HPP__

class uvplus_async : public uvplus_handle {
 public:
  uvplus_async();
  int init(uvplus_loop &loop, std::function<void(uvplus_async *self)> async_callback);
  int send();
 private:
  std::function<void(uvplus_async *self)> async_callback;

  static void async_cb(uv_async_t *handle);
  
};

#endif  // !__UVPLUS__ASYNC_HPP__
