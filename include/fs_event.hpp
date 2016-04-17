#ifndef __UVPLUS__FS_EVENT_HPP__
#define __UVPLUS__FS_EVENT_HPP__

class uvplus_fs_event : public uvplus_handle {
 public:
  uvplus_fs_event();
  int init(uvplus_loop *loop);
  int start(const char *path, unsigned int flags, std::function<void(const char *filename, int events, int status)> fs_event_callback);
  int stop();
  int getpath(char *buffer, size_t *size);

 private:
  std::function<void(const char *filename, int events, int status)> fs_event_callback;
  
  static void fs_event_cb(uv_fs_event_t *handle, const char *filename, int events, int status);
};

#endif  // !__UVPLUS__FS_EVENT_HPP__
