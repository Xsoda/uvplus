#include "uvplus.hpp"

uvplus_signal::uvplus_signal() {
}

int uvplus_signal::init(uvplus_loop *loop) {
  auto signal = (uv_signal_t *)context_ptr();
  return uv_signal_init(loop->context_ptr(), signal);
}

int uvplus_signal::start(int signum, std::function<void(int signum)> signal_callback) {
  auto signal = (uv_signal_t *)context_ptr();
  this->signal_callback = signal_callback;
  return uv_signal_start(signal, signal_cb, signum);
}

int uvplus_signal::stop() {
  auto signal = (uv_signal_t *)context_ptr();
  return uv_signal_stop(signal);
}

void uvplus_signal::signal_cb(uv_signal_t *signal, int signum) {
  auto handle = static_cast<uvplus_handle *>(signal->data);
  auto self = static_cast<uvplus_signal *>(handle);
  if (self->signal_callback) {
    self->signal_callback(signum);
  }
}
