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

#include <fstream>
#include <iostream>
#include "INIParser.h"
#include "INIReaderException.h"
#include "INIWriterException.h"
#include "Utilities.h"

namespace cppiniparser {

INIConfig INIParser::Read(const std::string& filename) {
    std::ifstream is;
    is.open(filename.c_str());
    if (!is.is_open()) {
        std::string msg = "Unable to read " + filename;
        throw INIReaderException(msg.c_str());
    }

    INIConfig config;
    std::string section = "";
    try {
        std::string line;
        while (getline(is, line)) {
            if (utils::IsEmptyLine(line) || utils::IsComment(line)) {
                // ignore it
            } else if (utils::IsSection(line)) {
                section = utils::ParseSection(line);
                config.AddSection(section);
            } else if (utils::IsOption(line)) {
                std::pair<std::string, std::string> option = utils::ParseOption(line);
                config.AddOption(section, option.first, option.second);
            } else {
                std::string msg = "Invalid line: " + line;
                throw INIReaderException(msg.c_str());
            }
        }
        is.close();
    } catch (...) {
        // don't forget to close the ifstream
        is.close();
        throw;
    }
    return config;
}

void INIParser::Write(INIConfig& config, const std::string& filename) {
    std::ofstream os;
    os.open(filename.c_str());
    if (!os.is_open()) {
        std::string msg = "Unable to write " + filename;
        throw INIWriterException(msg.c_str());
    }

    try {
        const std::vector<std::string>& sections = config.Sections();
        std::vector<std::string>::const_iterator s = sections.begin();
        for (; s != sections.end(); ++s) {
            os << utils::CreateSection(*s) << std::endl;
            const std::vector<std::string>& opts = config.Options(*s);
            for (std::vector<std::string>::const_iterator o = opts.begin();
                o != opts.end(); ++o) {
                std::string value = config.GetOption(*s, *o);
                os << utils::CreateOption(*o, value) << std::endl;
            }
            os << std::endl;
        }
        os.close();
    } catch (...) {
        // don't forget to close the ofstream
        os.close();
        throw;
    }
}

}
