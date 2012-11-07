// Copyright 2012 Fredy Wijaya
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "Utilities.h"

namespace cppiniparser {

namespace utils {
    const std::string TRIM_DELIMITERS = " \f\n\r\t\v";
    std::string RightTrim(const std::string& str) {
        std::string::size_type s = str.find_last_not_of(TRIM_DELIMITERS);
        if (s == std::string::npos) {
            return "";
        }
        return str.substr(0, s+1);
    }

    std::string LeftTrim(const std::string& str) {
        std::string::size_type s = str.find_first_not_of(TRIM_DELIMITERS);
        if (s == std::string::npos) {
            return "";
        }
        return str.substr(s);
    }

    std::string Trim(const std::string& str) {
        return RightTrim(LeftTrim(str));
    }

    bool IsSection(const std::string& str) {
        // Only perform a right trim
        std::string trimmedStr = Trim(str);
        if (trimmedStr[0] == '[' && trimmedStr[trimmedStr.size()-1] == ']') {
            return true;
        }
        return false;
    }

    std::string ParseSection(const std::string& str) {
        std::string trimmedStr = Trim(str);
        return trimmedStr.substr(1, trimmedStr.size()-2);
    }

    bool IsOption(const std::string& str) {
        std::string trimmedStr = Trim(str);
        std::string::size_type s = trimmedStr.find_first_of("=");
        if (s == std::string::npos) {
            return false;
        }
        std::string key = Trim(trimmedStr.substr(0, s));
        // key can't be empty
        if (key == "") {
            return false;
        }
        return true;
    }

    std::pair<std::string, std::string> ParseOption(const std::string& str) {
        std::string trimmedStr = Trim(str);
        std::string::size_type s = trimmedStr.find_first_of("=");
        std::string key = Trim(trimmedStr.substr(0, s));
        std::string value = Trim(trimmedStr.substr(s+1));

        return std::pair<std::string, std::string>(key, value);
    }

    bool IsComment(const std::string& str) {
        std::string trimmedStr = LeftTrim(str);
        if (trimmedStr[0] == ';') {
            return true;
        }
        return false;
    }

    bool IsEmptyLine(const std::string& str) {
        std::string trimmedStr = LeftTrim(str);
        if (trimmedStr == "") {
            return true;
        }
        return false;
    }

    std::string CreateSection(const std::string& section) {
        return "[" + section + "]";
    }

    std::string CreateOption(const std::string& optionName, const std::string& optionValue) {
        return optionName + "=" + optionValue;
    }
}

}
