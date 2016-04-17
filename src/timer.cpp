#include "uvplus.hpp"

uvplus_timer::uvplus_timer() {
}

int uvplus_timer::init(uvplus_loop *loop) {
  auto timer = (uv_timer_t *)context_ptr();
  return uv_timer_init(loop->context_ptr(), timer);
}

int uvplus_timer::start(uint64_t timeout, uint64_t repeat, std::function<void()> timer_callback) {
  auto timer = (uv_timer_t *)context_ptr();
  this->timer_callback = timer_callback;
  return uv_timer_start(timer, timer_cb, timeout, repeat);
}

int uvplus_timer::stop() {
  auto timer = (uv_timer_t *)context_ptr();
  return uv_timer_stop(timer);
}

int uvplus_timer::again() {
  auto timer = (uv_timer_t *)context_ptr();
  return uv_timer_again(timer);
}

void uvplus_timer::set_repeat(uint64_t repeat) {
  auto timer = (uv_timer_t *)context_ptr();
  uv_timer_set_repeat(timer, repeat);
}

uint64_t uvplus_timer::get_repeat() {
  auto timer = (uv_timer_t *)context_ptr();
  return uv_timer_get_repeat(timer);
}

void uvplus_timer::timer_cb(uv_timer_t *timer) {
  auto handle = static_cast<uvplus_handle *>(timer->data);
  auto self = static_cast<uvplus_timer *>(handle);
  if (self->timer_callback) {
    self->timer_callback();
  }
}
