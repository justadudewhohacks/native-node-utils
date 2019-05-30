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

	class IntArrayConverter : public AbstractConverter<ArrayConverterImpl<IntConverterImpl>> {};
	class UintArrayConverter : public AbstractConverter<ArrayConverterImpl<UintConverterImpl>> {};
	class UlongArrayConverter : public AbstractConverter<ArrayConverterImpl<UlongConverterImpl>> {};
	class BoolArrayConverter : public AbstractConverter<ArrayConverterImpl<BoolConverterImpl>> {};
	class DoubleArrayConverter : public AbstractConverter<ArrayConverterImpl<DoubleConverterImpl>> {};
	class FloatArrayConverter : public AbstractConverter<ArrayConverterImpl<FloatConverterImpl>> {};
	class StringArrayConverter : public AbstractConverter<ArrayConverterImpl<StringConverterImpl>> {};

	class IntArrayOfArraysConverter : public AbstractConverter<ArrayOfArraysConverterImpl<IntConverterImpl>> {};
	class UintArrayOfArraysConverter : public AbstractConverter<ArrayOfArraysConverterImpl<UintConverterImpl>> {};
	class UlongArrayOfArraysConverter : public AbstractConverter<ArrayOfArraysConverterImpl<UlongConverterImpl>> {};
	class BoolArrayOfArraysConverter : public AbstractConverter<ArrayOfArraysConverterImpl<BoolConverterImpl>> {};
	class DoubleArrayOfArraysConverter : public AbstractConverter<ArrayOfArraysConverterImpl<DoubleConverterImpl>> {};
	class FloatArrayOfArraysConverter : public AbstractConverter<ArrayOfArraysConverterImpl<FloatConverterImpl>> {};
	class StringArrayOfArraysConverter : public AbstractConverter<ArrayOfArraysConverterImpl<StringConverterImpl>> {};
}

#endif