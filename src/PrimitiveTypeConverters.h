#include "AbstractConverter.h"
#include "UnwrapperBase.h"

#ifndef __FF_PRIMITIVE_TYPE_CONVERTERS_H__
#define __FF_PRIMITIVE_TYPE_CONVERTERS_H__

namespace FF {

	template<typename ConverterImpl>
	class PrimitiveTypeConverter : public UnwrapperBase<ConverterImpl> {
	public:
		static v8::Local<v8::Value> wrap(ConverterImpl::Type val) {
			return Nan::New(val);
		}
	};

	class IntConverterImpl : public PrimitiveTypeConverter<IntConverterImpl> {
	public:
		typedef int Type;

		static const char* getTypeName() {
			return "int";
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsInt32();
		}

		static int unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::To<int>(jsVal).ToChecked();
		}
	};

	class UintConverterImpl : public PrimitiveTypeConverter<UintConverterImpl> {
	public:
		typedef uint Type;

		static const char* getTypeName() {
			return "uint";
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsUint32();
		}

		static uint unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::To<uint>(jsVal).ToChecked();
		}
	};

	class UlongConverterImpl : public PrimitiveTypeConverter<UlongConverterImpl> {
	public:
		typedef unsigned long Type;

		static const char* getTypeName() {
			return "ulong";
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static unsigned long unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return (unsigned long)Nan::To<uint>(jsVal).ToChecked();
		}
	};

	class BoolConverterImpl : public PrimitiveTypeConverter<BoolConverterImpl> {
	public:
		typedef bool Type;

		static const char* getTypeName() {
			return "bool";
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsBoolean();
		}

		static bool unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::To<bool>(jsVal).ToChecked();
		}
	};

	class DoubleConverterImpl : public PrimitiveTypeConverter<DoubleConverterImpl> {
	public:
		typedef double Type;

		static const char* getTypeName() {
			return "double";
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static double unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return Nan::To<double>(jsVal).ToChecked();
		}
	};

	class FloatConverterImpl : public PrimitiveTypeConverter<FloatConverterImpl> {
	public:
		typedef float Type;

		static const char* getTypeName() {
			return "float";
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsNumber();
		}

		static float unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return (float)Nan::To<double>(jsVal).ToChecked();
		}
	};

	class StringConverterImpl : public PrimitiveTypeUnwrapper<StringConverterImpl> {
	public:
		typedef std::string Type;

		static const char* getTypeName() {
			return "string";
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return jsVal->IsString();
		}

		static std::string unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			return std::string(*Nan::Utf8String(jsVal->ToString(Nan::GetCurrentContext()).ToLocalChecked()));
		}

		static v8::Local<v8::Value> wrap(std::string val) {
			return Nan::New(val).ToLocalChecked();
		}
	};

}

#endif