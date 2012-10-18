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

#include "INIConfig.h"

namespace cppiniparser {

bool INIConfig::HasSection(const std::string& sectionName) {
    // TODO: implement this
    return false;
}

bool INIConfig::HasOption(const std::string& sectionName, const std::string& optionName) {
    // TODO: implement this
    return false;
}

std::string INIConfig::GetOption(const std::string& sectionName, const std::string& optionName) {
    // TODO: implement this
    return "";
}

std::vector<std::string> INIConfig::Sections() {
    // TODO: implement this
    return std::vector<std::string>();
}

std::vector<std::string> INIConfig::Options(const std::string& sectionName) {
    // TODO: implement this
    return std::vector<std::string>();
}

void INIConfig::SetOption(const std::string& sectionName, const std::string& optionName,
    const std::string& optionValue) {
    // TODO: implement this
}

void INIConfig::RemoveSection(const std::string& sectionName) {
    // TODO: implement this
}

void INIConfig::RemoveOption(const std::string& sectionName, const std::string& optionName) {
    // TODO: implement this
}

void INIConfig::AddSection(const std::string& sectionName) {
    // TODO: implement this
}

void INIConfig::AddOption(const std::string& sectionName, const std::string& optionName,
    const std::string& optionValue) {
    // TODO: implement this
}

}
