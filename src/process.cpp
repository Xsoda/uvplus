#include "uvplus.h"
#include <cstring>

uvplus_process::uvplus_process() {
  ptr = static_cast<uv_process_t *>(get_handle_ptr());
  options.exit_cb = exit_cb;
  options.stdio_count = 3;
  options.stdio = stdio_container;
  for (int i = 0; i < 3; i++) {
    stdio_container[i].flags = UV_IGNORE;
    stdio_container[i].data.stream = (uv_stream_t *)stdio_stream[i].ptr;
  }
}

uvplus_process::~uvplus_process() {
  if (options.cwd)
    delete [] options.cwd;
  char **args = options.args;
  while (*args) {
    delete [] *args;
    args++;
  }
  delete [] options.args;
}

void uvplus_process::enable_stdin_stream() {
  options.stdio[0].flags = static_cast<uv_stdio_flags>(UV_CREATE_PIPE | UV_WRITABLE_PIPE);
}

void uvplus_process::enable_stdout_stream() {
  options.stdio[1].flags = static_cast<uv_stdio_flags>(UV_CREATE_PIPE | UV_READABLE_PIPE);
}

void uvplus_process::enable_stderr_stream() {
  options.stdio[2].flags = static_cast<uv_stdio_flags>(UV_CREATE_PIPE | UV_READABLE_PIPE);
}

uvplus_stream &uvplus_process::get_stdin_stream() {
  return stdio_stream[0];
}

uvplus_stream &uvplus_process::get_stdout_stream() {
  return stdio_stream[1];
}

uvplus_stream &uvplus_process::get_stderr_stream() {
  return stdio_stream[2];
}

void uvplus_process::set_cwd(std::string &cwd) {
  options.cwd = new char[cwd.length() + 1];
  strcpy((char *)options.cwd, cwd.c_str());
}

void uvplus_process::set_exit_callback(std::function<void(int64_t exit_status, int term_signal)> exit_callback) {
  this->exit_callback = exit_callback;
}

int uvplus_process::kill(int signum) {
  return uv_process_kill(ptr, signum);
}

int uvplus_process::spawn(uvplus_loop *loop, std::initializer_list<std::string> &args) {
  int i = 0;
  options.args = new char*[args.size() + 1];
  for (auto arg : args) {
    options.args[i] = new char[arg.length() + 1];
    strcpy(options.args[i], arg.c_str());
    i++;
  }
  options.args[i] = NULL;
  options.file = options.args[0];

  for (i = 0; i < 3; i++) {
    if (stdio_container[i].flags) {
      stdio_stream[i].init(loop, 0);
    }
  }

  return uv_spawn(loop->ptr, ptr, &options);
}

void uvplus_process::exit_cb(uv_process_t *proc, int64_t exit_status, int term_signal) {
  auto handle = static_cast<uvplus_handle *>(proc->data);
  auto self = static_cast<uvplus_process *>(handle);
  for (int i = 0; i < 3; i++) {
    if (self->stdio_container[i].flags) {
      if (self->stdio_stream[i].is_active()) {
        self->stdio_stream[i].shutdown([&] (int status) {
            self->stdio_stream[i].close();
          });
      }
    }
  }
  if (self->exit_callback) {
    self->exit_callback(exit_status, term_signal);
  }
}
