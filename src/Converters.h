#include "PrimitiveTypeConverters.h"
#include "ArrayConverter.h"

#ifndef __FF_CONVERTERS_H__
#define __FF_CONVERTERS_H__

namespace FF {
	// TODO: this could simply be typedefs

	class IntConverter : public AbstractConverter<IntConverterImpl> {};
	class UintConverter : public AbstractConverter<UintConverterImpl> {};
	class UlongConverter : public AbstractConverter<UlongConverterImpl> {};
	class BoolConverter : public AbstractConverter<BoolConverterImpl> {};
	class DoubleConverter : public AbstractConverter<DoubleConverterImpl> {};
	class FloatConverter : public AbstractConverter<FloatConverterImpl> {};
	class StringConverter : public AbstractConverter<StringConverterImpl> {};

	class IntArrayConverter : public AbstractConverter<ArrayConverterImpl<IntConverter>> {};
	class UintArrayConverter : public AbstractConverter<ArrayConverterImpl<UintConverter>> {};
	class UlongArrayConverter : public AbstractConverter<ArrayConverterImpl<UlongConverter>> {};
	class BoolArrayConverter : public AbstractConverter<ArrayConverterImpl<BoolConverterImpl>> {};
	class DoubleArrayConverter : public AbstractConverter<ArrayConverterImpl<DoubleConverterImpl>> {};
	class FloatArrayConverter : public AbstractConverter<ArrayConverterImpl<FloatConverterImpl>> {};
	class StringArrayConverter : public AbstractConverter<ArrayConverterImpl<StringConverterImpl>> {};
}

#endif