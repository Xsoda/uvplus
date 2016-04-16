#include "uvplus.hpp"

uvplus_timer::uvplus_timer() {
  ptr = static_cast<uv_timer_t *>(get_handle_ptr());
}

int uvplus_timer::init(uvplus_loop *loop) {
  return uv_timer_init(loop->ptr, ptr);
}

int uvplus_timer::start(uint64_t timeout, uint64_t repeat, std::function<void()> timer_callback) {
  this->timer_callback = timer_callback;
  return uv_timer_start(ptr, timer_cb, timeout, repeat);
}

int uvplus_timer::stop() {
  return uv_timer_stop(ptr);
}

int uvplus_timer::again() {
  return uv_timer_again(ptr);
}

void uvplus_timer::set_repeat(uint64_t repeat) {
  uv_timer_set_repeat(ptr, repeat);
}

uint64_t uvplus_timer::get_repeat() {
  return uv_timer_get_repeat(ptr);
}

void uvplus_timer::timer_cb(uv_timer_t *timer) {
  auto handle = static_cast<uvplus_handle *>(timer->data);
  auto self = static_cast<uvplus_timer *>(handle);
  if (self->timer_callback) {
    self->timer_callback();
  }
}
