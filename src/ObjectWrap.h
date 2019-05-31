#include "utils.h"
#include "InstanceConverter.h"
#include "ArrayConverter.h"
#include "ArrayOfArraysConverter.h"

#ifndef __FF_OBJECT_WRAP_H__
#define __FF_OBJECT_WRAP_H__

namespace FF {

	template<class TClass, class T>
	class ObjectWrap : public Nan::ObjectWrap {
	public:
		T self;

		T* getNativeObjectPtr() { return &self; }
		T getNativeObject() { return self; }
		void setNativeObject(T obj) { self = obj; }

		typedef InstanceConverterImpl<TClass, T> ConverterImpl;
		typedef AbstractConverter<ConverterImpl, T> Converter;

		template<class ElementCastType>
		class ArrayWithCastConverter : public ArrayConverterTemplate<ConverterImpl, ElementCastType> {};

		template<class ElementCastType>
		class ArrayOfArraysWithCastConverter : public ArrayOfArraysConverterTemplate<ConverterImpl, ElementCastType> {};

		typedef ArrayWithCastConverter<T> ArrayConverter;
		typedef ArrayOfArraysWithCastConverter<T> ArrayOfArraysConverter;

		static TClass* unwrap(v8::Local<v8::Value> obj) {
			return Nan::ObjectWrap::Unwrap<TClass>(obj->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
		}

		static T unwrapSelf(Nan::NAN_METHOD_ARGS_TYPE info) {
			return unwrapSelf(info.This());
		}

		static T unwrapSelf(Nan::NAN_GETTER_ARGS_TYPE info) {
			return unwrapSelf(info.This());
		}

		static bool hasInstance(v8::Local<v8::Value> jsVal) {
			return TClass::ConverterImpl::assertType(jsVal);
		}

	private:
		static T unwrapSelf(v8::Local<v8::Object> This) {
			return TClass::ConverterImpl::unwrapUnchecked(This);
		}
	};

}

#endif
