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
#include "Utilities.h"

using namespace testing;
using namespace cppiniparser;

TEST(Utilities, TestTrim) {
    EXPECT_EQ("foo", utils::Trim("foo"));
    EXPECT_EQ("foo", utils::Trim("    foo     "));
    EXPECT_EQ("foo", utils::Trim("\n  foo   \r\n"));
    EXPECT_EQ("", utils::Trim("      \n"));
}

TEST(Utilities, TestIsSection) {
    EXPECT_TRUE(utils::IsSection("[foo]"));
    EXPECT_TRUE(utils::IsSection("   [foo]  "));
    EXPECT_FALSE(utils::IsSection("whatever"));
}

TEST(Utilities, TestParseSection) {
    EXPECT_EQ("foo", utils::ParseSection("[foo]"));
    EXPECT_EQ(" foo ", utils::ParseSection("[ foo ]"));
    EXPECT_EQ("foo", utils::ParseSection("   [foo]  "));
}

TEST(Utilities, TestIsOption) {
    EXPECT_TRUE(utils::IsOption("key=value"));
    EXPECT_TRUE(utils::IsOption("    key   =     value   "));
    EXPECT_TRUE(utils::IsOption("    key   ="));
    EXPECT_FALSE(utils::IsOption("=value"));
}

TEST(Utilities, TestParseOption) {
    std::pair<std::string, std::string> p = utils::ParseOption("key=value");
    EXPECT_EQ("key", p.first);
    EXPECT_EQ("value", p.second);

    p = utils::ParseOption(" key = value ");
    EXPECT_EQ("key", p.first);
    EXPECT_EQ("value", p.second);

    p = utils::ParseOption(" key =  ");
    EXPECT_EQ("key", p.first);
    EXPECT_EQ("", p.second);
}

TEST(Utilities, TestIsComment) {
    EXPECT_TRUE(utils::IsComment("; comment"));
    EXPECT_TRUE(utils::IsComment("   ; comment"));
}

TEST(Utilities, TestIsEmpty) {
    EXPECT_TRUE(utils::IsEmpty("      \r\n"));
}
