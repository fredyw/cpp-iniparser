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
#include <algorithm>
#include "INIConfig.h"
#include "DuplicateSectionException.h"
#include "DuplicateOptionException.h"
#include "InvalidSectionException.h"
#include "InvalidOptionException.h"

using namespace testing;
using namespace cppiniparser;

TEST(INIConfigTest, TestAddSection) {
    INIConfig config;
    config.AddSection("foo");
    EXPECT_TRUE(config.HasSection("foo"));
}

TEST(INIConfigTest, TestAddSectionDuplicateSection) {
    INIConfig config;
    config.AddSection("foo");
    EXPECT_THROW(config.AddSection("foo"), DuplicateSectionException);
}

TEST(INIConfigTest, TestAddOption) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key", "value");
    EXPECT_TRUE(config.HasOption("foo", "key"));
    EXPECT_EQ("value", config.GetOption("foo", "key"));
}

TEST(INIConfigTest, TestAddOptionOptionNotFound) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key", "value");
    EXPECT_FALSE(config.HasOption("foo", "bar"));
    EXPECT_THROW(config.GetOption("foo", "bar"), InvalidOptionException);
}

TEST(INIConfigTest, TestAddOptionInvalidSection) {
    INIConfig config;
    EXPECT_THROW(config.AddOption("foo", "key", "value"), InvalidSectionException);
}

TEST(INIConfigTest, TestSetOption) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key", "value");
    config.SetOption("foo", "key", "newvalue");
    EXPECT_EQ("newvalue", config.GetOption("foo", "key"));
}

TEST(INIConfigTest, TestSetOptionInvalidSection) {
    INIConfig config;
    EXPECT_THROW(config.SetOption("foo", "key", "newvalue"), InvalidOptionException);
}

TEST(INIConfigTest, TestSetOptionInvalidOption) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key", "value");
    EXPECT_THROW(config.SetOption("foo", "bar", "newvalue"), InvalidOptionException);
}

TEST(INIConfigTest, TestSections) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");
    config.AddOption("foo", "key3", "value3");

    config.AddSection("bar");
    config.AddOption("bar", "key4", "value4");
    config.AddOption("bar", "key5", "value5");

    std::vector<std::string> sections = config.Sections();
    EXPECT_TRUE(std::find(sections.begin(), sections.end(), "foo") != sections.end());
    EXPECT_TRUE(std::find(sections.begin(), sections.end(), "bar") != sections.end());
    EXPECT_FALSE(std::find(sections.begin(), sections.end(), "foobar") != sections.end());
}

TEST(INIConfigTest, TestOptions) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");

    config.AddSection("bar");
    config.AddOption("bar", "key3", "value3");
    config.AddOption("bar", "key4", "value4");

    std::vector<std::string> opts = config.Options("foo");

    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key1") != opts.end());
    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key2") != opts.end());
    EXPECT_FALSE(std::find(opts.begin(), opts.end(), "key3") != opts.end());

    opts = config.Options("bar");

    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key3") != opts.end());
    EXPECT_TRUE(std::find(opts.begin(), opts.end(), "key4") != opts.end());
    EXPECT_FALSE(std::find(opts.begin(), opts.end(), "key5") != opts.end());
}

TEST(INIConfigTest, TestOptionsInvalidOption) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");

    EXPECT_THROW(config.Options("bar"), InvalidSectionException);
}

TEST(INIConfigTest, TestRemoveSection) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");

    config.RemoveSection("foo");
    EXPECT_FALSE(config.HasSection("foo"));
}

TEST(INIConfigTest, TestRemoveSectionInvalidSection) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");

    EXPECT_THROW(config.RemoveSection("bar"), InvalidSectionException);
}

TEST(INIConfigTest, TestRemoveOption) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");

    config.RemoveOption("foo", "key2");

    EXPECT_FALSE(config.HasOption("foo", "key2"));
}

TEST(INIConfigTest, TestRemoveOptionInvalidOption) {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");

    EXPECT_THROW(config.RemoveOption("foo", "key3"), InvalidOptionException);
}
