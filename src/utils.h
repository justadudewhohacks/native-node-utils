#include <memory>
#include <iostream>
#include <nan.h>

#ifndef __FF_UTILS_H__
#define __FF_UTILS_H__

typedef unsigned int uint;

namespace FF {

	class Utils {
	public:
		static std::string formatError(std::string methodName, std::string err) {
			return std::string(methodName) + std::string(" - ") + err;
		}
	};

	static inline v8::Local<v8::Function> getFunction(v8::Local<v8::FunctionTemplate> fnTempl) {
		return Nan::GetFunction(fnTempl).ToLocalChecked();
	}

	static inline v8::Local<v8::Object> newInstance(v8::Local<v8::FunctionTemplate> ctor) {
		return Nan::NewInstance(FF::getFunction(ctor)).ToLocalChecked();
	}

	static inline bool hasArg(Nan::NAN_METHOD_ARGS_TYPE info, int argN) {
		return argN < info.Length();
	}

	static inline bool isArgObject(Nan::NAN_METHOD_ARGS_TYPE info, int argN) {
		return FF::hasArg(info, argN) && info[argN]->IsObject() && !info[argN]->IsArray() && !info[argN]->IsFunction();
	}

	static inline v8::Local<v8::String> newString(std::string str) {
		return Nan::New(str).ToLocalChecked();
	}

	static inline bool hasOwnProperty(v8::Local<v8::Object> obj, char* prop) {
		return Nan::HasOwnProperty(obj, FF::newString(prop)).FromJust();
	}

	template<class TClass>
	static inline TClass* unwrapNanObjectWrap(v8::Local<v8::Object> jsObj) {
		return Nan::ObjectWrap::Unwrap<TClass>(jsObj);
	}

	template<class TClass>
	static inline TClass* unwrapNanObjectWrap(v8::Local<v8::Value> jsVal) {
		return unwrapNanObjectWrap<TClass>(jsVal->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
	}

	class TryCatch : public Nan::TryCatch {
	public:
		v8::Local<v8::String> formatCatchedError(std::string methodName) {
			return Nan::New(
				Utils::formatError(
					std::string(methodName),
					*Nan::Utf8String(Exception()->ToString(Nan::GetCurrentContext()).ToLocalChecked())
				)
			).ToLocalChecked();
		}

		void throwNew(v8::Local<v8::Value> err) {
			Reset();
			Nan::ThrowError(err);
			ReThrow();
		}
	};

}

#endif
