#include "utils.h"

#ifndef __FF_ABSTRACT_CONVERTER_H__
#define __FF_ABSTRACT_CONVERTER_H__

namespace FF {

	/*
	ConverterImpl<ConverterImpl, T> implements:
		static const char* getTypeName()
		static v8::Local<v8::Value> wrap(T val)
		static bool unwrap(T* pVal, v8::Local<v8::Value> jsVal)
	*/
	template <class ConverterImpl, class T>
	class AbstractConverter {
	public:
		static v8::Local<v8::Value> wrap(T val) {
			return ConverterImpl::wrap(val);
		}

		static T unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			T val;
			unwrap(&val, jsVal);
			return val;
		}

		static bool arg(int argN, T* val, Nan::NAN_METHOD_ARGS_TYPE info) {
			Nan::TryCatch tryCatch;
			if (!hasArg(info, argN) || ConverterImpl::unwrap(val, info[argN])) {
				if (tryCatch.HasCaught()) {
					tryCatch.ReThrow();
				}
				else {
					Nan::ThrowError(
						Nan::New(
							std::string("expected argument ")
							+ std::to_string(argN)
							+ std::string(" to be of type ")
							+ std::string(ConverterImpl::getTypeName())
						).ToLocalChecked()
					);
					tryCatch.ReThrow();
				}
				return true;
			}
			return false;
		}

		static bool optArg(int argN, T* val, Nan::NAN_METHOD_ARGS_TYPE info) {
			if (hasArg(info, argN) && info[argN]->IsFunction()) {
				return false;
			}

			Nan::TryCatch tryCatch;
			if (hasArg(info, argN) && ConverterImpl::unwrap(val, info[argN])) {
				if (tryCatch.HasCaught()) {
					tryCatch.ReThrow();
				}
				else {
					Nan::ThrowError(
						Nan::New(
							std::string("expected argument ")
							+ std::to_string(argN)
							+ std::string(" to be of type ")
							+ std::string(ConverterImpl::getTypeName())
						).ToLocalChecked()
					);
					tryCatch.ReThrow();
				}
				return true;
			}
			return false;
		}

		static bool prop(T* val, const char* prop, v8::Local<v8::Object> opts) {
			if (!Nan::HasOwnProperty(opts, Nan::New(prop).ToLocalChecked()).FromJust()) {
				Nan::ThrowError(
					Nan::New(
						std::string("expected object to have property: ") + std::string(prop)
					).ToLocalChecked()
				);
				return true;
			}

			return AbstractConverterImpl::optProp(val, prop, opts);
		}

		static bool optProp(T* val, const char* prop, v8::Local<v8::Object> opts) {
			Nan::TryCatch tryCatch;
			if (
				Nan::HasOwnProperty(opts, Nan::New(prop).ToLocalChecked()).FromJust()
				&& ConverterImpl::unwrap(val, Nan::Get(opts, Nan::New(prop).ToLocalChecked()).ToLocalChecked())
				) {
				if (tryCatch.HasCaught()) {
					tryCatch.ReThrow();
				}
				else {
					Nan::ThrowError(
						Nan::New(
							std::string("expected property ")
							+ std::string(prop)
							+ std::string(" to be of type ")
							+ std::string(ConverterImpl::getTypeName())
						).ToLocalChecked()
					);
					tryCatch.ReThrow();
				}
				return true;
			}
			return false;
		}
	};
}


#endif