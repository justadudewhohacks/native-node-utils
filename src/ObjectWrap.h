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

		typedef AbstractConverter<InstanceConverterImpl<TClass>> Converter;

		template<class ElementCastType>
		class ArrayWithCastConverter : public AbstractConverter<ArrayConverterImpl<TClass::Converter, ElementCastType>> {};

		template<class ElementCastType>
		class ArrayOfArraysWithCastConverter : public AbstractConverter<ArrayOfArraysConverterImpl<TClass::Converter, ElementCastType>> {};

		class ArrayConverter : public ArrayWithCastConverter<TClass::Type> {};
		class ArrayOfArraysConverter : public ArrayOfArraysWithCastConverter<TClass::Type> {};

		static TClass* unwrap(v8::Local<v8::Value> obj) {
			return Nan::ObjectWrap::Unwrap<TClass>(obj->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
		}
	};

}

#endif
