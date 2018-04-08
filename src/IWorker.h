#include <nan.h>
#include <iostream>

#ifndef __FF_IWORKER_H__
#define __FF_IWORKER_H__

namespace FF {

	class IWorker {
	public:
		virtual std::string execute() = 0;
		virtual v8::Local<v8::Value> getReturnValue() = 0;
		virtual bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) = 0;
		virtual bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) = 0;
		virtual bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) = 0;
		virtual bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) = 0;

		bool applyUnwrappers(Nan::NAN_METHOD_ARGS_TYPE info) {
			return unwrapRequiredArgs(info)
				|| (!hasOptArgsObject(info) && unwrapOptionalArgs(info))
				|| (hasOptArgsObject(info) && unwrapOptionalArgsFromOpts(info));
		}
	};

}

#endif