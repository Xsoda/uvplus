#ifndef __UVPLUS__PROCESS_HPP__
#define __UVPLUS__PROCESS_HPP__

class uvplus_process : public uvplus_handle {
public:
  uvplus_process();
  ~uvplus_process();
  void set_exec_file(std::string &file);
  const uvplus_stream &enable_stdin_stream();
  const uvplus_stream &enable_stdout_stream();
  const uvplus_stream &enable_stderr_stream();
  void set_cwd(std::string &cwd);
  void set_exit_callback(std::function<void(int64_t exit_status, int term_signal)> exit_callback);
  int kill(int signum);
  int spawn(uvplus_loop *loop, std::initializer_list<std::string> &args);
private:
  uv_process_options_t options;
  uv_stdio_container_t stdio_container[3];
  uvplus_pipe stdio_stream[3];

  std::function<void(int64_t exit_status, int term_signal)> exit_callback;
  static void exit_cb(uv_process_t *proc, int64_t exit_status, int term_signal);
};

#endif  // !__UVPLUS__PROCESS_HPP__
