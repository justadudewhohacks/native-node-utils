#include <nan.h>

#ifndef __FF_UTILS_H__
#define __FF_UTILS_H__

namespace FF {

	class Utils {
	public:
		static std::string formatError(std::string methodName, std::string err) {
			return std::string(methodName) + std::string(" - ") + err;
		}
	};

	static v8::Local<v8::Function> getFunction(v8::Local<v8::FunctionTemplate> fnTempl) {
		return Nan::GetFunction(fnTempl).ToLocalChecked();
	}

	static v8::Local<v8::Object> newInstance(v8::Local<v8::FunctionTemplate> ctor) {
		return Nan::NewInstance(FF::getFunction(ctor)).ToLocalChecked();
	}

}

#endif
