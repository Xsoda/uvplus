#ifndef __UVPLUS__FS_POLL_HPP__
#define __UVPLUS__FS_POLL_HPP__

class uvplus_fs_poll : public uvplus_handle {
 public:
  uvplus_fs_poll();
  int init(uvplus_loop &loop);
  int start(const char *path, unsigned int interval, std::function<void(uvplus_fs_poll *self, int status, const uv_stat_t *prev, const uv_stat_t *curr)> fs_poll_callback);
  int stop();
  int getpath(char *buffer, size_t *size);

 private:
  std::function<void(uvplus_fs_poll *self, int status, const uv_stat_t *prev, const uv_stat_t *curr)> fs_poll_callback;

  static void fs_poll_cb(uv_fs_poll_t *handle, int status, const uv_stat_t *prev, const uv_stat_t *curr);
};

#endif  // !__UVPLUS_FS_POLL_HPP__
