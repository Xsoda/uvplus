#ifndef __UVPLUS__TTY_HPP__
#define __UVPLUS__TTY_HPP__

class uvplus_tty : public uvplus_stream {
 public:
  uvplus_tty();
  int init(uvplus_loop &loop, uv_file fd, int readable);
  int set_mode(uv_tty_mode_t mode);
  static int reset_mode(void);
  int get_winsize(int *width, int *height);
};

#endif  // !__UVPLUS__TTY_HPP__
