#include "uvplus.hpp"

uvplus_tty::uvplus_tty() {
  ptr = static_cast<uv_tty_t *>(get_handle_ptr());
}

int uvplus_tty::init(uvplus_loop *loop, uv_file fd, int readable) {
  return uv_tty_init(loop->ptr, ptr, fd, readable);
}

int uvplus_tty::set_mode(uv_tty_mode_t mode) {
  return uv_tty_set_mode(ptr, mode);
}

int uvplus_tty::reset_mode(void) {
  return uv_tty_reset_mode();
}

int uvplus_tty::get_winsize(int *width, int *height) {
  return uv_tty_get_winsize(ptr, width, height);
}
