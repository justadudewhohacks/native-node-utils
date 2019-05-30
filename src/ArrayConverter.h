#include <nan.h>

#ifndef __FF_ARRAY_CONVERTER_H__
#define __FF_ARRAY_CONVERTER_H__

template <class ElementConverterImpl, class ElementCastType = ElementConverterImpl::Type>
class ArrayConverterImpl {
public:
	typedef std::vector<ElementCastType> Type;

	static const char* getTypeName() {
		return "array";
	}

	static bool unwrap(std::vector<ElementCastType>* vec, v8::Local<v8::Value> jsVal) {
		if (!jsVal->IsArray()) {
			return true;
		}

		v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(jsVal);
		for (int i = 0; i < (int)jsArr->Length(); i++) {
			if (!ElementConverterImpl::assertType(Nan::Get(jsArr, i).ToLocalChecked())) {
				Nan::ThrowError(
					Nan::New(
						std::string("expected array element at index ")
						+ std::to_string(i)
						+ std::string(" to be of type ")
						+ std::string(ElementConverterImpl::getTypeName())
					).ToLocalChecked()
				);
				return true;
			}
	  
			ElementCastType obj = (ElementCastType)ElementConverterImpl::unwrap(Nan::Get(jsArr, i).ToLocalChecked());
			vec->push_back(obj);
		}

		return false;
	}

	static v8::Local<v8::Value> wrap(std::vector<ElementCastType> vec) {
		v8::Local<v8::Array> jsArr = Nan::New<v8::Array>(vec.size());
		for (int i = 0; i < (int)jsArr->Length(); i++) {
			Nan::Set(jsArr, i, ElementConverterImpl::wrap(vec.at(i)));
		}
		return jsArr;
	}
};

#endif
