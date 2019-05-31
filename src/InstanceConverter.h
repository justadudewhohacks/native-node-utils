#include "AbstractConverter.h"
#include "UnwrapperBase.h"
#include "utils.h"

#ifndef __FF_INSTANCE_CONVERTER_H__
#define __FF_INSTANCE_CONVERTER_H__

namespace FF {

	template <class Clazz, class T>
	class InstanceConverterImpl : public UnwrapperBase<InstanceConverterImpl<Clazz, T>, T> {
	public:
		static const char* getTypeName() {
			return Clazz::getClassName();
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return !jsVal->IsNull() && !jsVal->IsUndefined() && Nan::New(Clazz::constructor)->HasInstance(jsVal);
		}

		static T unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::ObjectWrap::Unwrap<Clazz>(jsVal->ToObject(Nan::GetCurrentContext()).ToLocalChecked())->getNativeObject();
		}

		static v8::Local<v8::Value> wrap(T val) {
			v8::Local<v8::Object> jsObj = FF::newInstance(Nan::New(Clazz::constructor));
			*Nan::ObjectWrap::Unwrap<Clazz>(jsObj)->getNativeObjectPtr() = val;
			return jsObj;
		}
	};

}

#endif