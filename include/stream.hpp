#ifndef __UVPLUS__STREAM_HPP__
#define __UVPLUS__STREAM_HPP__

class uvplus_stream : public uvplus_handle {
 protected:
  uvplus_stream();

 public:
  int shutdown(std::function<void(int status)> shutdown_callback);
  int listen(std::function<void(int status)> connection_callback);
  int accept(uvplus_stream *client);
  int read_start(std::function<void(size_t suggested_size, uv_buf_t *buf)> alloc_callback,
                 std::function<void(ssize_t nread, const uv_buf_t *buf)> read_callback);
  int read_stop();
  int write(const char *buf, size_t length, std::function<void(int status)> write_ccallback=nullptr);
  int write(const uv_buf_t bufs[], unsigned int nbufs, std::function<void(int status)> write_callback=nullptr);
  int write2(const uv_buf_t bufs[], unsigned int nbufs, uvplus_stream *send_handle, std::function<void(int status)> write_callback=nullptr);
  int try_write(const char *buf, size_t length);
  int try_write(const uv_buf_t bufs[], unsigned int nbufs);
  int set_blocking(int blocking);
  int is_readable();
  int is_writeable();

 private:
  std::function<void(int status)> connection_callback;
  std::function<void(size_t suggested_size, uv_buf_t *buf)> alloc_callback;
  std::function<void(ssize_t nread, const uv_buf_t *buf)> read_callback;

  static void shutdown_cb(uv_shutdown_t *req, int status);
  static void connection_cb(uv_stream_t *stream, int status);
  static void alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
  static void read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf);
  static void write_cb(uv_write_t *req, int status);
};

#endif  // !__UVPLUS__STREAM_HPP__
