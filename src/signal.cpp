#include "uvplus.hpp"

uvplus_signal::uvplus_signal() {
  ptr = static_cast<uv_signal_t *>(get_handle_ptr());
}

int uvplus_signal::init(uvplus_loop *loop) {
  return uv_signal_init(loop->ptr, ptr);
}

int uvplus_signal::start(int signum, std::function<void(int signum)> signal_callback) {
  this->signal_callback = signal_callback;
  return uv_signal_start(ptr, signal_cb, signum);
}

int uvplus_signal::stop() {
  return uv_signal_stop(ptr);
}

void uvplus_signal::signal_cb(uv_signal_t *signal, int signum) {
  auto handle = static_cast<uvplus_handle *>(signal->data);
  auto self = static_cast<uvplus_signal *>(handle);
  if (self->signal_callback) {
    self->signal_callback(signum);
  }
}
