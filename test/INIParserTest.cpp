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

#include <gtest/gtest.h>
#include <cstdio>
#include <algorithm>
#include "INIParser.h"
#include "INIReaderException.h"

using namespace testing;
using namespace cppiniparser;

TEST(INIParserTest, TestRead) {
    INIConfig config = INIParser::Read("../test/test1.ini");
    EXPECT_EQ("foo", config.GetOption("foo", "name"));
    EXPECT_EQ("hello", config.GetOption("foo", "msg"));

    EXPECT_EQ("bar", config.GetOption("bar", "name"));
    EXPECT_EQ("bye", config.GetOption("bar", "msg"));
}

TEST(INIParserTest, TestReadInvalidFile) {
    EXPECT_THROW(INIParser::Read("../test/test2.ini"), INIReaderException);
}

TEST(INIParserTest, TestReadFileNotFound) {
    EXPECT_THROW(INIParser::Read("somewhere"), INIReaderException);
}

TEST(INIParserTest, TestWrite) {
    INIConfig inConfig;
    inConfig.AddSection("foo");
    inConfig.AddOption("foo", "key1", "value1");
    inConfig.AddOption("foo", "key2", "value2");
    inConfig.AddOption("foo", "key3", "value3");

    inConfig.AddSection("bar");
    inConfig.AddOption("bar", "key4", "value4");
    inConfig.AddOption("bar", "key5", "value5");

    INIParser::Write(inConfig, "../test/out.ini");

    INIConfig outConfig = INIParser::Read("../test/out.ini");

    std::vector<std::string> opts = outConfig.Options("foo");
    EXPECT_EQ(3, opts.size());
    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key1") != opts.end());
    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key2") != opts.end());
    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key3") != opts.end());

    opts = outConfig.Options("bar");
    EXPECT_EQ(2, opts.size());
    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key4") != opts.end());
    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key5") != opts.end());

    // delete the file at the end
    std::remove("../test/out.ini");
}
