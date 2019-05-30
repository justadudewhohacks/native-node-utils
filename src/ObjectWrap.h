#include "utils.h"
#include "InstanceConverter.h"
#include "ArrayConverter.h"
#include "ArrayOfArraysConverter.h"

#ifndef __FF_OBJECT_WRAP_H__
#define __FF_OBJECT_WRAP_H__

namespace FF {

	template<class TClass>
	class ObjectWrap : public Nan::ObjectWrap {
	public:
		TClass::Type self;

		TClass::Type* getNativeObjectPtr() { return &self; }
		TClass::Type getNativeObject() { return self; }
		void setNativeObject(TClass::Type obj) { self = obj; }

		typedef InstanceConverterImpl<TClass> ConverterImpl;
		typedef AbstractConverter<ConverterImpl> Converter;

		template<class ElementCastType>
		class ArrayWithCastConverter : public AbstractConverter<ArrayConverterImpl<TClass::ConverterImpl, ElementCastType>> {};

		template<class ElementCastType>
		class ArrayOfArraysWithCastConverter : public AbstractConverter<ArrayOfArraysConverterImpl<TClass::ConverterImpl, ElementCastType>> {};

		class ArrayConverter : public ArrayWithCastConverter<TClass::Type> {};
		class ArrayOfArraysConverter : public ArrayOfArraysWithCastConverter<TClass::Type> {};

		static TClass* unwrap(v8::Local<v8::Value> obj) {
			return Nan::ObjectWrap::Unwrap<TClass>(obj->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
		}

		static TClass::Type unwrapSelf(Nan::NAN_METHOD_ARGS_TYPE info) {
			return TClass::ConverterImpl::unwrapUnchecked(info.This());
		}

		static bool hasInstance(v8::Local<v8::Value> jsVal) {
			return TClass::ConverterImpl::assertType(jsVal);
		}
	};

}

#endif
