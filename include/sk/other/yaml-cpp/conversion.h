#pragma once

#ifndef CONVERSION_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define CONVERSION_H_62B23520_7C8E_11DE_8A39_0800200C9A66


#include "null.h"
#include <string>
#include <sstream>

namespace SK_YAML
{
	inline bool Convert(const std::string& input, std::string& output) {
		output = input;
		return true;
	}

	bool Convert(const std::string& input, bool& output);
	bool Convert(const std::string& input, _Null& output);

#define SK_YAML_MAKE_STREAM_CONVERT(type) \
	inline bool Convert(const std::string& input, type& output) { \
		std::stringstream stream(input); \
		stream >> output; \
		return !stream.fail(); \
	}

	SK_YAML_MAKE_STREAM_CONVERT(char)
	SK_YAML_MAKE_STREAM_CONVERT(unsigned char)
	SK_YAML_MAKE_STREAM_CONVERT(int)
	SK_YAML_MAKE_STREAM_CONVERT(unsigned int)
	SK_YAML_MAKE_STREAM_CONVERT(short)
	SK_YAML_MAKE_STREAM_CONVERT(unsigned short)
	SK_YAML_MAKE_STREAM_CONVERT(long)
	SK_YAML_MAKE_STREAM_CONVERT(unsigned long)
	SK_YAML_MAKE_STREAM_CONVERT(float)
	SK_YAML_MAKE_STREAM_CONVERT(double)
	SK_YAML_MAKE_STREAM_CONVERT(long double)

#undef SK_YAML_MAKE_STREAM_CONVERT
}

#endif // CONVERSION_H_62B23520_7C8E_11DE_8A39_0800200C9A66
