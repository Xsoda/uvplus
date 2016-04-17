#include "uvplus.hpp"

uvplus_tty::uvplus_tty() {
}

int uvplus_tty::init(uvplus_loop *loop, uv_file fd, int readable) {
  auto tty = (uv_tty_t *)context_ptr();
  return uv_tty_init(loop->context_ptr(), tty, fd, readable);
}

int uvplus_tty::set_mode(uv_tty_mode_t mode) {
  auto tty = (uv_tty_t *)context_ptr();
  return uv_tty_set_mode(tty, mode);
}

int uvplus_tty::reset_mode(void) {
  return uv_tty_reset_mode();
}

int uvplus_tty::get_winsize(int *width, int *height) {
  auto tty = (uv_tty_t *)context_ptr();
  return uv_tty_get_winsize(tty, width, height);
}
