#include "uvplus.hpp"

uvplus_stream::uvplus_stream() {
}

int uvplus_stream::shutdown(std::function<void(uvplus_stream *self, int status)> shutdown_callback) {
  auto req = new uv_shutdown_t;
  auto shutdown_callback_ptr = new std::function<void(uvplus_stream *self, int status)>(shutdown_callback);
  auto stream = (uv_stream_t *)context_ptr();
  req->data = static_cast<void *>(shutdown_callback_ptr);
  return uv_shutdown(req, stream, shutdown_cb);
}

int uvplus_stream::listen(std::function<void(uvplus_stream *self, int status)> connection_callback) {
  auto stream = (uv_stream_t *)context_ptr();
  this->connection_callback = connection_callback;
  return uv_listen(stream, SOMAXCONN, connection_cb);
}

int uvplus_stream::accept(uvplus_stream &client) {
  auto stream = (uv_stream_t *)context_ptr();
  return uv_accept(stream, (uv_stream_t *)client.context_ptr());
}

int uvplus_stream::read_start(std::function<void(uvplus_stream *self, size_t suggested_size, uv_buf_t *buf)> alloc_callback,
                              std::function<void(uvplus_stream *self, ssize_t nread, const uv_buf_t *buf)> read_callback) {
  auto stream = (uv_stream_t *)context_ptr();
  this->alloc_callback = alloc_callback;
  this->read_callback = read_callback;
  return uv_read_start(stream, alloc_cb, read_cb);
}

int uvplus_stream::read_stop() {
  auto stream = (uv_stream_t *)context_ptr();
  return uv_read_stop(stream);
}

int uvplus_stream::write(const char *buf, size_t length, std::function<void(uvplus_stream *self, int status)> write_callback) {
   uv_buf_t wbuf = uv_buf_init((char *)buf, length);
   return write(&wbuf, 1, write_callback);
}

int uvplus_stream::write(const uv_buf_t bufs[], unsigned int nbufs, std::function<void(uvplus_stream *self, int status)> write_callback) {
  uv_write_t *req = new uv_write_t;
  auto write_callback_ptr = new std::function<void(uvplus_stream *self, int status)>(write_callback);
  auto stream = (uv_stream_t *)context_ptr();
  req->data = static_cast<void *>(write_callback_ptr);
  return uv_write(req, stream, bufs, nbufs, write_cb);
}

int uvplus_stream::write2(const uv_buf_t bufs[], unsigned int nbufs, uvplus_stream *send_handle, std::function<void(uvplus_stream *self, int status)> write_callback) {
  uv_write_t *req = new uv_write_t;
  auto write_callback_ptr = new std::function<void(uvplus_stream *self, int status)>(write_callback);
  auto stream = (uv_stream_t *)context_ptr();
  req->data = static_cast<void *>(write_callback_ptr);
  return uv_write2(req, stream, bufs, nbufs, (uv_stream_t *)send_handle->context_ptr(), write_cb);
}

int uvplus_stream::try_write(const char *buf, size_t length) {
   uv_buf_t wbuf = uv_buf_init((char *)buf, length);
   return try_write(&wbuf, 1);
}

int uvplus_stream::try_write(const uv_buf_t bufs[], unsigned int nbufs) {
  auto stream = (uv_stream_t *)context_ptr();
  return uv_try_write(stream, bufs, nbufs);
}

int uvplus_stream::set_blocking(int blocking) {
  auto stream = (uv_stream_t *)context_ptr();
  return uv_stream_set_blocking(stream, blocking);
}
      
int uvplus_stream::is_readable() {
  auto stream = (uv_stream_t *)context_ptr();
  return uv_is_readable(stream);
}

int uvplus_stream::is_writeable() {
  auto stream = (uv_stream_t *)context_ptr();
  return uv_is_writable(stream);
}

void uvplus_stream::shutdown_cb(uv_shutdown_t *req, int status) {
  uv_stream_t *stream = req->handle;
  auto shutdown_callback = static_cast<std::function<void(uvplus_stream *self, int status)> *>(req->data);
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_stream *>(handle);
  if (*shutdown_callback) {
    (*shutdown_callback)(self, status);
  }
  delete shutdown_callback;
  delete req;
}

void uvplus_stream::connection_cb(uv_stream_t *stream, int status) {
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_stream *>(handle);
  self->connection_callback(self, status);
}

void uvplus_stream::alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  auto base = static_cast<uvplus_handle *>(handle->data);
  auto self = static_cast<uvplus_stream *>(base);
  self->alloc_callback(self, suggested_size, buf);
}
void uvplus_stream::read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_stream *>(handle);
  self->read_callback(self, nread, buf);
}

void uvplus_stream::write_cb(uv_write_t *req, int status) {
  uv_stream_t *stream = req->handle;
  auto write_callback = static_cast<std::function<void(uvplus_stream *self, int status)> *>(req->data);
  auto handle = static_cast<uvplus_handle *>(stream->data);
  auto self = static_cast<uvplus_stream *>(handle);
  if (*write_callback)
    (*write_callback)(self, status);
  delete write_callback;
  delete req;
}
