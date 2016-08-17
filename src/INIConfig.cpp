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
#include "DuplicateSectionException.h"
#include "DuplicateOptionException.h"
#include "InvalidSectionException.h"
#include "InvalidOptionException.h"

namespace cppiniparser {

bool INIConfig::HasSection(const std::string& sectionName) const {
    if (config.find(sectionName) == config.end()) {
        return false;
    }
    return true;
}

bool INIConfig::HasOption(const std::string& sectionName, const std::string& optionName) const {
    if (!HasSection(sectionName)) {
        return false;
    }
    const std::map<std::string, std::string>& options = config.at(sectionName);
    if (options.find(optionName) == options.end()) {
        return false;
    }
    return true;
}

std::string INIConfig::GetOption(const std::string& sectionName, const std::string& optionName) const {
    ValidateOption(sectionName, optionName);

    const std::map<std::string, std::string>& options = config.at(sectionName);
    return options.at(optionName);
}

std::vector<std::string> INIConfig::Sections() const {
    std::vector<std::string> sections;
    std::map<std::string, std::map<std::string, std::string> >::const_iterator i = config.begin();
    for (; i != config.end(); ++i) {
        sections.push_back(i->first);
    }
    return sections;
}

std::vector<std::string> INIConfig::Options(const std::string& sectionName) const {
    ValidateSection(sectionName);

    const std::map<std::string, std::string>& opts = config.at(sectionName);
    std::vector<std::string> options;
    std::map<std::string, std::string>::const_iterator i = opts.begin();
    for (; i != opts.end(); ++i) {
        options.push_back(i->first);
    }
    return options;
}

void INIConfig::SetOption(const std::string& sectionName, const std::string& optionName,
    const std::string& optionValue) {
    ValidateOption(sectionName, optionName);

    std::map<std::string, std::string>& options = config[sectionName];
    options[optionName] = optionValue;
}

void INIConfig::RemoveSection(const std::string& sectionName) {
    ValidateSection(sectionName);

    config.erase(sectionName);
}

void INIConfig::RemoveOption(const std::string& sectionName, const std::string& optionName) {
    ValidateOption(sectionName, optionName);

    config[sectionName].erase(optionName);
}

void INIConfig::AddSection(const std::string& sectionName) {
    if (HasSection(sectionName)) {
        std::string msg = "Duplicate section (" + sectionName + ") found";
        throw DuplicateSectionException(msg.c_str());
    }
    std::map<std::string, std::string> emptyMap;
    config[sectionName] = emptyMap;
}

void INIConfig::AddOption(const std::string& sectionName, const std::string& optionName,
    const std::string& optionValue) {
    ValidateSection(sectionName);

    std::map<std::string, std::string>& options = config[sectionName];
    if (HasOption(sectionName, optionName)) {
        std::string msg = "Duplicate option (" + optionName + ") found";
        throw DuplicateOptionException(msg.c_str());
    }
    options[optionName] = optionValue;
}

void INIConfig::ValidateSection(const std::string& sectionName) const {
    if (!HasSection(sectionName)) {
        std::string msg = "Section (" + sectionName + ") not found";
        throw InvalidSectionException(msg.c_str());
    }
}

void INIConfig::ValidateOption(const std::string& sectionName, const std::string& optionName) const {
    if (!HasOption(sectionName, optionName)) {
        std::string msg = "Section (" + sectionName + "), Option (" + optionName + ") not found";
        throw InvalidOptionException(msg.c_str());
    }
}

}
