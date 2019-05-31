#include "utils.h"
#include "InstanceConverter.h"
#include "ArrayConverter.h"
#include "ArrayOfArraysConverter.h"

#ifndef __FF_OBJECT_WRAP_H__
#define __FF_OBJECT_WRAP_H__

namespace FF {

	template<class TClass>
	class ObjectWrapBase : public Nan::ObjectWrap {
	public:
		static TClass* unwrapClassPtrUnchecked(v8::Local<v8::Value> jsVal) {
			return unwrapNanObjectWrap<TClass>(jsVal);
		}

		static TClass* unwrapThis(Nan::NAN_METHOD_ARGS_TYPE info) {
			return unwrapClassPtrUnchecked(info.This());
		}

		static TClass* unwrapThis(Nan::NAN_GETTER_ARGS_TYPE info) {
			return unwrapClassPtrUnchecked(info.This());
		}

		static TClass* unwrapThis(Nan::NAN_SETTER_ARGS_TYPE info) {
			return unwrapClassPtrUnchecked(info.This());
		}
	};

	template<class Base, class TClass, class T>
	class ObjectWrapTemplate : public Base {
	public:
		T self;

		void setNativeObject(T obj) { self = obj; }

		typedef InstanceConverterImpl<TClass, T> ConverterImpl;
		typedef AbstractConverter<ConverterImpl, T> Converter;

		template<class ElementCastType>
		class ArrayWithCastConverter : public ArrayConverterTemplate<ConverterImpl, ElementCastType> {};

		template<class ElementCastType>
		class ArrayOfArraysWithCastConverter : public ArrayOfArraysConverterTemplate<ConverterImpl, ElementCastType> {};

		typedef ArrayWithCastConverter<T> ArrayConverter;
		typedef ArrayOfArraysWithCastConverter<T> ArrayOfArraysConverter;

		static bool hasInstance(v8::Local<v8::Value> jsVal) {
			return TClass::ConverterImpl::assertType(jsVal);
		}

		static T unwrapSelf(Nan::NAN_METHOD_ARGS_TYPE info) {
			return unwrapSelf(info.This());
		}

		static T unwrapSelf(Nan::NAN_GETTER_ARGS_TYPE info) {
			return unwrapSelf(info.This());
		}

		static T unwrapSelf(Nan::NAN_SETTER_ARGS_TYPE info) {
			return unwrapSelf(info.This());
		}

	private:
		static T unwrapSelf(v8::Local<v8::Object> thisObj) {
			return unwrapClassPtrUnchecked(thisObj)->self;
		}
	};

	template<class TClass, class T>
	class ObjectWrap : public ObjectWrapTemplate<ObjectWrapBase<TClass>, TClass, T> {};

}

#endif
