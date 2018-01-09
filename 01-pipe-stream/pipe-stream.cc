#include <assert.h>

#include "pipe-stream.h"

napi_ref StreamWritable::constructor;

StreamWritable::StreamWritable()
    : env_(nullptr), wrapper_(nullptr) {}

StreamWritable::~StreamWritable() { napi_delete_reference(env_, wrapper_); }

void StreamWritable::Destructor(
  napi_env env, void* nativeObject, void*) {
  StreamWritable* obj = static_cast<StreamWritable*>(nativeObject);
  delete obj;
}

napi_value StreamWritable::New(napi_env env, napi_callback_info info) {
  napi_value self;

  {
    napi_value new_target;
    napi_status status = napi_get_new_target(env, info, &new_target);
    NAPI_CALL(env, status);
    bool is_constructor = (new_target != nullptr);

    // Enforce constructor invocation: `new StreamWritable()`
    assert(is_constructor && "Need to invoke via 'new', i.e. 'new StreamWritable()'");
  }

  {
    // Passing no constructor parameters at this point
    size_t argc = 0;
    napi_value args = nullptr;

    napi_status status = napi_get_cb_info(env, info, &argc, &args, &self, nullptr);
    NAPI_CALL(env, status);
  }

  {
    StreamWritable* writable = new StreamWritable();
    writable->env_ = env;

    // https://nodejs.org/api/n-api.html#n_api_napi_wrap
    napi_status status = napi_wrap(
      env,
      self,
      writable,
      StreamWritable::Destructor,
      nullptr,
      &writable->wrapper_
    );
    NAPI_CALL(env, status);
  }

  return self;
}

napi_value StreamWritable::Write(napi_env env, napi_callback_info info) {
  //
  // Validate and extract buffer arg and get hold of Object Instance
  //
  napi_value self;
  napi_value buffer;
  {
    size_t argc = 1;
    napi_value args[1];
    napi_status status = napi_get_cb_info(env, info, &argc, args, &self, nullptr);
    NAPI_CALL(env, status);
    buffer = args[0];
  }
  {
    bool isBuffer;
    napi_status status = napi_is_buffer(env, buffer, &isBuffer);
    NAPI_CALL(env, status);
    assert(isBuffer && "Argument needs to be a Buffer");
  }

  //
  // Unwrap StreamWritable from instance
  //
  StreamWritable* writable;
  {
    napi_status status = napi_unwrap(env, self, reinterpret_cast<void**>(&writable));
    NAPI_CALL(env, status);
  }

  //
  // Extract char* from Buffer
  //

  // https://nodejs.org/api/n-api.html#n_api_napi_is_buffer
  // https://nodejs.org/api/n-api.html#n_api_napi_get_buffer_info
  char *chunk;
  size_t chunkSize;
  {
    napi_status status = 
      napi_get_buffer_info(env, buffer, (void**)(&chunk), &chunkSize);
    NAPI_CALL(env, status);
  }

  writable->Write(chunk, chunkSize);

  return nullptr;
}

void StreamWritable::Write(const char* chunk, const size_t chunkSize) {
  fprintf(stderr, "writing chunk '%s' of size %ld\n", chunk, chunkSize);
}

void StreamWritable::Init(napi_env env, napi_value exports) {
  napi_value cons;

  // https://nodejs.org/api/n-api.html#n_api_napi_define_class
  // https://nodejs.org/api/n-api.html#n_api_napi_property_descriptor
  { // define class

    napi_property_descriptor properties[] = {
      DECLARE_NAPI_PROPERTY("write", Write)
    };

    napi_status status = napi_define_class(
        env, "StreamWritable", -1, New, nullptr, 3, properties, &cons);

    NAPI_CALL_RETURN_VOID(env, status);
  }

  // https://nodejs.org/api/n-api.html#n_api_napi_create_reference
  { // create reference
    napi_status status = napi_create_reference(env, cons, 1, &constructor);
    NAPI_CALL_RETURN_VOID(env, status);
  }

  // https://nodejs.org/api/n-api.html#n_api_napi_set_named_property
  { // add to exports
    napi_status status = napi_set_named_property(env, exports, "StreamWritable", cons);
    NAPI_CALL_RETURN_VOID(env, status);
  }
}

napi_value Init(napi_env env, napi_value exports) {
  StreamWritable::Init(env, exports);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
