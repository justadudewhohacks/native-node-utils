#include "PrimitiveTypeConverters.h"
#include "ArrayConverter.h"

#ifndef __FF_CONVERTERS_H__
#define __FF_CONVERTERS_H__

namespace FF {
	template<class ConverterImpl, class ElementType>
	class ArrayConverterTemplate : public AbstractConverter<ArrayConverterImpl<ConverterImpl, ElementType>, std::vector<ElementType>> {};
	
	template<class ConverterImpl, class ElementType>
	class ArrayOfArraysConverterTemplate : public AbstractConverter<ArrayOfArraysConverterImpl<ConverterImpl, ElementType>, std::vector<std::vector<ElementType>>> {};

	typedef AbstractConverter<IntConverterImpl, int> IntConverter;
	typedef AbstractConverter<UintConverterImpl, uint> UintConverter;
	typedef AbstractConverter<UlongConverterImpl, unsigned long> UlongConverter;
	typedef AbstractConverter<BoolConverterImpl, bool> BoolConverter;
	typedef AbstractConverter<DoubleConverterImpl, double> DoubleConverter;
	typedef AbstractConverter<FloatConverterImpl, float> FloatConverter;
	typedef AbstractConverter<StringConverterImpl, std::string> StringConverter;

	typedef ArrayConverterTemplate<IntConverterImpl, int> IntArrayConverter;
	typedef ArrayConverterTemplate<UintConverterImpl, uint> UintArrayConverter;
	typedef ArrayConverterTemplate<UlongConverterImpl, unsigned long> UlongArrayConverter;
	typedef ArrayConverterTemplate<BoolConverterImpl, bool> BoolArrayConverter;
	typedef ArrayConverterTemplate<DoubleConverterImpl, double> DoubleArrayConverter;
	typedef ArrayConverterTemplate<FloatConverterImpl, float> FloatArrayConverter;
	typedef ArrayConverterTemplate<StringConverterImpl, std::string> StringArrayConverter;

	typedef ArrayOfArraysConverterTemplate<IntConverterImpl, int> IntArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<UintConverterImpl, uint> UintArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<UlongConverterImpl, unsigned long> UlongArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<BoolConverterImpl, bool> BoolArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<DoubleConverterImpl, double> DoubleArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<FloatConverterImpl, float> FloatArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<StringConverterImpl, std::string> StringArrayOfArraysConverter;
}

#endif