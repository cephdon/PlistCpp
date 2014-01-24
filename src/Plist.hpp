//
//   PlistCpp Property List (plist) serialization and parsing library.
//
//   https://github.com/animetrics/PlistCpp
//   
//   Copyright (c) 2011 Animetrics Inc. (marc@animetrics.com)
//   
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//   
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//   
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.

#ifndef __PLIST_H__
#define __PLIST_H__

#include <boost/any.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "PlistDate.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include <stdint.h>
#endif

namespace Plist
{

		// Public read methods.  Plist type (binary or xml) automatically detected.

		void readPlist(const char* byteArrayTemp, int64_t size, boost::any& message);
		void readPlist(std::istream& stream, boost::any& message);
		template<typename T>
		void readPlist(const char* byteArray, int64_t size, T& message);
		template<typename T>
		void readPlist(std::istream& stream, T& message);
		template<typename T>
		void readPlist(const std::string& filename, T& message);
#if defined(_MSC_VER)
		template<typename T>
		void readPlist(const std::wstring& filename, T& message);
#endif

		// Public binary write methods.

		void writePlistBinary(std::ostream& stream, const boost::any& message);
		void writePlistBinary(std::vector<char>& plist, const boost::any& message);
		void writePlistBinary(const std::string& filename, const boost::any& message);
#if defined(_MSC_VER)
		void writePlistBinary(const std::wstring& filename, const boost::any& message);
#endif

		// Public XML write methods.

		void writePlistXML(std::ostream& stream, const boost::any& message);
		void writePlistXML(std::vector<char>& plist, const boost::any& message);
		void writePlistXML(const std::string& filename, const boost::any& message);
#if defined(_MSC_VER)
		void writePlistXML(const std::wstring& filename, const boost::any& message);
#endif

};

#if defined(_MSC_VER)
template <typename T>
void Plist::readPlist(const std::wstring& filename, T& message)
{
	std::ifstream stream(filename.c_str(), std::ios::binary);
	if(!stream)
		throw std::runtime_error("Can't open file.");
	readPlist(stream, message);
}
#endif

template <typename T>
void Plist::readPlist(const std::string& filename, T& message)
{
	std::ifstream stream(filename.c_str(), std::ios::binary);
	if(!stream)
		throw std::runtime_error("Can't open file.");
	readPlist(stream, message);
}

template <typename T>
void Plist::readPlist(const char* byteArrayTemp, int64_t size, T& message)
{
	boost::any tmp_message;
	readPlist(byteArrayTemp, size, tmp_message);
	message = boost::any_cast<T>(tmp_message);
}

template <typename T>
void Plist::readPlist(std::istream& stream, T& message)
{
	boost::any tmp_message;
	readPlist(stream, tmp_message);
	message = boost::any_cast<T>(tmp_message);
}

#endif
