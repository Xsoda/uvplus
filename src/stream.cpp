#include "uvplus.hpp"

uvplus_stream::uvplus_stream() {
  ptr = static_cast<uv_stream_t *>(get_handle_ptr());
}

int uvplus_stream::shutdown(std::function<void(int status)> shutdown_callback) {
  auto req = new uv_shutdown_t;
  auto shutdown_callback_ptr = new std::function<void(int status)>(shutdown_callback);
  req->data = static_cast<void *>(shutdown_callback_ptr);
  return uv_shutdown(req, ptr, shutdown_cb);
}

int uvplus_stream::listen(int backlog, std::function<void(int status)> connection_callback) {
  this->connection_callback = connection_callback;
  return uv_listen(ptr, backlog, connection_cb);
}

int uvplus_stream::accept(uvplus_stream *client) {
  return uv_accept(ptr, client->ptr);
}

int uvplus_stream::read_start(std::function<void(size_t suggested_size, uv_buf_t *buf)> alloc_callback,
                              std::function<void(ssize_t nread, const uv_buf_t *buf)> read_callback) {
  this->alloc_callback = alloc_callback;
  this->read_callback = read_callback;
  return uv_read_start(ptr, alloc_cb, read_cb);
}

int uvplus_stream::read_stop() {
  return uv_read_stop(ptr);
}

int uvplus_stream::write(const uv_buf_t bufs[], unsigned int nbufs, std::function<void(int status)> write_callback) {
  uv_write_t *req = new uv_write_t;
  auto write_callback_ptr = new std::function<void(int status)>(write_callback);
  req->data = static_cast<void *>(write_callback_ptr);
  return uv_write(req, ptr, bufs, nbufs, write_cb);
}

int uvplus_stream::write2(const uv_buf_t bufs[], unsigned int nbufs, uvplus_stream *send_handle, std::function<void(int status)> write_callback) {
  uv_write_t *req = new uv_write_t;
  auto write_callback_ptr = new std::function<void(int status)>(write_callback);
  req->data = static_cast<void *>(write_callback_ptr);
  return uv_write2(req, ptr, bufs, nbufs, send_handle->ptr, write_cb);
}

int uvplus_stream::try_write(const uv_buf_t bufs[], unsigned int nbufs) {
  return uv_try_write(ptr, bufs, nbufs);
}

int uvplus_stream::set_blocking(int blocking) {
  return uv_stream_set_blocking(ptr, blocking);
}
      
int uvplus_stream::is_readable() {
  return uv_is_readable(ptr);
}

int uvplus_stream::is_writeable() {
  return uv_is_writable(ptr);
}

void uvplus_stream::shutdown_cb(uv_shutdown_t *req, int status) {
  uv_stream_t *stream = req->handle;
  auto shutdown_callback = static_cast<std::function<void(int status)> *>(req->data);
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_stream *>(handle);
  if (*shutdown_callback) {
    (*shutdown_callback)(status);
  }
  delete shutdown_callback;
  delete req;
}

void uvplus_stream::connection_cb(uv_stream_t *stream, int status) {
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_stream *>(handle);
  self->connection_callback(status);
}

void uvplus_stream::alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_stream *>(base);
  self->alloc_callback(suggested_size, buf);
}
void uvplus_stream::read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_stream *>(handle);
  self->read_callback(nread, buf);
}

void uvplus_stream::write_cb(uv_write_t *req, int status) {
  uv_stream_t *stream = req->handle;
  auto write_callback = static_cast<std::function<void(int status)> *>(req->data);
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_stream *>(handle);
  if (*write_callback)
    (*write_callback)(status);
  delete write_callback;
  delete req;
}
