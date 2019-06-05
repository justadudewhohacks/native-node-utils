#include "utils.h"
#include "ArrayConverter.h"
#include "ArrayOfArraysConverter.h"
#include "InstanceConverter.h"
#include "TryCatch.h"

#ifndef __FF_OBJECT_WRAP_H__
#define __FF_OBJECT_WRAP_H__

namespace FF {

	template<class TClass>
	class ObjectWrapBase {
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

	template<class TClass, class T>
	class ObjectWrapTemplate : public ObjectWrapBase<TClass> {
	public:
		typedef ObjectWrapBase<TClass> super;

		T self;

		void setNativeObject(T obj) { self = obj; }

		typedef InstanceConverterImpl<TClass, T> ConverterImpl;
		typedef AbstractConverter<ConverterImpl> Converter;

		template<class CastType>
		class WithCastConverter : public AbstractConverter<InstanceConverterImpl<TClass, CastType>> {};

		template<class ElementCastType>
		class ArrayWithCastConverter : public ArrayConverterTemplate<ConverterImpl, ElementCastType> {};

		template<class ElementCastType>
		class ArrayOfArraysWithCastConverter : public ArrayOfArraysConverterTemplate<ConverterImpl, ElementCastType> {};

		typedef ArrayWithCastConverter<T> ArrayConverter;
		typedef ArrayOfArraysWithCastConverter<T> ArrayOfArraysConverter;

		template<class WorkerImpl>
		class SyncBinding : public FF::SyncBindingBase {
		public:
			SyncBinding(std::string name, Nan::NAN_METHOD_ARGS_TYPE info) : FF::SyncBindingBase(
				std::make_shared<WorkerImpl>(unwrapSelf(info)),
				std::string(TClass::getClassName()) + "::" + name,
				info
			) {};
		};

		template<class WorkerImpl>
		class AsyncBinding : public FF::AsyncBindingBase {
		public:
			AsyncBinding(std::string name, Nan::NAN_METHOD_ARGS_TYPE info) : FF::AsyncBindingBase(
				std::make_shared<WorkerImpl>(unwrapSelf(info)),
				std::string(TClass::getClassName()) + "::" + name + "Async",
				info
			) {};
		};

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

	protected:
		typedef TClass ClassType;

		template<class TPropertyConverter>
		static void setter(
			const char* setterName,
			Nan::NAN_SETTER_ARGS_TYPE info,
			v8::Local<v8::Value> value,
			void(*setProperty)(TClass*, typename TPropertyConverter::Type)
		) {
			FF::TryCatch tryCatch(setterName);
			typename TPropertyConverter::Type val;
			if (TPropertyConverter::unwrapTo(&val, value)) {
				return tryCatch.reThrow();
			}
			setProperty(super::unwrapThis(info), val);
		}

		template<class TPropertyConverter>
		static void getter(
			Nan::NAN_GETTER_ARGS_TYPE info,
			typename TPropertyConverter::Type(*getProperty)(TClass*)
		) {
			info.GetReturnValue().Set(TPropertyConverter::wrap(getProperty(super::unwrapThis(info))));
		}

	private:
		static T unwrapSelf(v8::Local<v8::Object> thisObj) {
			return super::unwrapClassPtrUnchecked(thisObj)->self;
		}
	};

	template<class TClass, class T>
	class ObjectWrap : public ObjectWrapTemplate<TClass, T>, public Nan::ObjectWrap {};

}

#endif
