#include <nan.h>
#include "IWorker.h"

#ifndef __FF_SIMPLEWORKER_H__
#define __FF_SIMPLEWORKER_H__

namespace FF {

  struct SimpleWorker : public IWorker {
  public:
    std::string execute() {
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Nan::Undefined();
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return false;
    }

    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return false;
    }

    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      return false;
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return false;
    }
  };

}

#endif