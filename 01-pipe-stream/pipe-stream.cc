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

void StreamWritable::Init(napi_env env, napi_value exports) {
  napi_value cons;

  { // define class

    // TODO: add methods/properties
    napi_property_descriptor properties[] = {};
    napi_status status = napi_define_class(
        env, "StreamWritable", -1, New, nullptr, 3, properties, &cons);

    NAPI_CALL_RETURN_VOID(env, status);
  }

  { // create reference
    napi_status status = napi_create_reference(env, cons, 1, &constructor);
    NAPI_CALL_RETURN_VOID(env, status);
  }

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
