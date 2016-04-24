#ifndef __UVPLUS__HANDLE_HPP__
#define __UVPLUS__HANDLE_HPP__

class uvplus_handle {
 protected:
  uvplus_handle();
  uvplus_handle(uvplus_handle &&);
  uvplus_handle &operator=(uvplus_handle &&);
  ~uvplus_handle();
  void init();

 public:
  int is_active();
  int is_closing();
  void close(std::function<void(uvplus_handle *self)> close_callback=nullptr);
  void ref();
  void unref();
  int has_ref();
  int send_buffer_size(int *value);
  int recv_buffer_size(int *value);
  int fileno(uv_os_fd_t *fd);
  uv_handle_t *context_ptr();

 private:
  uvplus_handle(const uvplus_handle &that) = delete;
  uvplus_handle &operator=(const uvplus_handle &that) = delete;

 private:
  static void close_cb(uv_handle_t *handle);
  uv_any_handle *context;
  std::function<void(uvplus_handle *self)> close_callback;
};
#endif  // !__UVPLUS__HANDLE_HPP__
