#pragma once

#ifndef CONVERSION_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define CONVERSION_H_62B23520_7C8E_11DE_8A39_0800200C9A66


#include "null.h"
#include <string>
#include <sstream>

namespace LOCAL_YAML
{
	inline bool Convert(const std::string& input, std::string& output) {
		output = input;
		return true;
	}

	bool Convert(const std::string& input, bool& output);
	bool Convert(const std::string& input, _Null& output);

#define LOCAL_YAML_MAKE_STREAM_CONVERT(type) \
	inline bool Convert(const std::string& input, type& output) { \
		std::stringstream stream(input); \
		stream >> output; \
		return !stream.fail(); \
	}

	LOCAL_YAML_MAKE_STREAM_CONVERT(char)
	LOCAL_YAML_MAKE_STREAM_CONVERT(unsigned char)
	LOCAL_YAML_MAKE_STREAM_CONVERT(int)
	LOCAL_YAML_MAKE_STREAM_CONVERT(unsigned int)
	LOCAL_YAML_MAKE_STREAM_CONVERT(short)
	LOCAL_YAML_MAKE_STREAM_CONVERT(unsigned short)
	LOCAL_YAML_MAKE_STREAM_CONVERT(long)
	LOCAL_YAML_MAKE_STREAM_CONVERT(unsigned long)
	LOCAL_YAML_MAKE_STREAM_CONVERT(float)
	LOCAL_YAML_MAKE_STREAM_CONVERT(double)
	LOCAL_YAML_MAKE_STREAM_CONVERT(long double)

#undef LOCAL_YAML_MAKE_STREAM_CONVERT
}

#endif // CONVERSION_H_62B23520_7C8E_11DE_8A39_0800200C9A66
