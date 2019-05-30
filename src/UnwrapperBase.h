#include <nan.h>

#ifndef __FF_UNWRAPPER_BASE_H__
#define __FF_UNWRAPPER_BASE_H__

namespace FF {

	template<typename UnwrapperImpl>
	class UnwrapperBase {
	public:
		static bool unwrap(UnwrapperImpl::Type* pVal, v8::Local<v8::Value> jsVal) {
			if (!UnwrapperImpl::assertType(jsVal)) {
				return true;
			}
			*pVal = UnwrapperImpl::unwrapUnchecked(jsVal);
			return false;
		}
	};

}

#endif