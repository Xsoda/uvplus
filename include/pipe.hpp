#ifndef __UVPLUS__PIPE_HPP__
#define __UVPLUS__PIPE_HPP__

class uvplus_pipe : public uvplus_stream {
  friend class uvplus_process;
public:
  uvplus_pipe();
  int init(uvplus_loop *loop, int ipc);
  int open(uv_file file);
  int bind(const char *name);
  void connect(const char *name, std::function<void(int status)> connect_callback);
  int getsockname(char *buffer, size_t *size);
  int getpeername(char *buffer, size_t *size);
  void pending_instances(int count);
  int pending_count();
private:
  uv_pipe_t *ptr;

  static void connect_cb(uv_connect_t *req, int status);
};

#endif  // !__UVPLUS__PIPE_HPP__
