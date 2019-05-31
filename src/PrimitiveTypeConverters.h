#include "AbstractConverter.h"
#include "UnwrapperBase.h"

#ifndef __FF_PRIMITIVE_TYPE_CONVERTERS_H__
#define __FF_PRIMITIVE_TYPE_CONVERTERS_H__

namespace FF {

	template<class ConverterImpl, class T>
	class PrimitiveTypeConverter : public UnwrapperBase<ConverterImpl, T> {
	public:
		static v8::Local<v8::Value> wrap(T val) {
			return Nan::New(val);
		}
	};

	class IntConverterImpl : public PrimitiveTypeConverter<IntConverterImpl, int> {
	public:
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

	class UintConverterImpl : public PrimitiveTypeConverter<UintConverterImpl, uint> {
	public:
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

	class UlongConverterImpl : public PrimitiveTypeConverter<UlongConverterImpl, unsigned long> {
	public:
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

	class BoolConverterImpl : public PrimitiveTypeConverter<BoolConverterImpl, bool> {
	public:
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

	class DoubleConverterImpl : public PrimitiveTypeConverter<DoubleConverterImpl, double> {
	public:
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

	class FloatConverterImpl : public PrimitiveTypeConverter<FloatConverterImpl, float> {
	public:
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

	class StringConverterImpl : public UnwrapperBase<StringConverterImpl, std::string> {
	public:
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