#ifndef __UVPLUS__HANDLE_HPP__
#define __UVPLUS__HANDLE_HPP__

class uvplus_handle {
 protected:
  uvplus_handle();

 public:
  int is_active();
  int is_closing();
  void close(std::function<void()> close_callback=nullptr);
  void ref();
  void unref();
  int has_ref();
  int send_buffer_size(int *value);
  int recv_buffer_size(int *value);
  int fileno(uv_os_fd_t *fd);
  uv_handle_t *context_ptr();

 private:
  static void close_cb(uv_handle_t *handle);
  uv_any_handle context;
  std::function<void()> close_callback;
};
#endif  // !__UVPLUS__HANDLE_HPP__
