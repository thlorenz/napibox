#ifndef PIPE_STREAM_H
#define PIPE_STREAM_H

#include <stdio.h>
#include <node_api.h>
#include "../napi-helpers.h"

class StreamWritable {
 public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

 private:
  explicit StreamWritable();
  ~StreamWritable();

  static napi_value New(napi_env env, napi_callback_info info);
  static napi_value Write(napi_env env, napi_callback_info info);
  void Write(const char* chunk, const size_t chunkSize);

  static napi_ref constructor;
  napi_env env_;
  napi_ref wrapper_;
};

#endif
