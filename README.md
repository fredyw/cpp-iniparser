# cpp-iniparser
A small C++ INI parser library

## How to build
cpp-iniparser uses [Waf](https://github.com/waf-project/waf) build system. On Windows, you need to install MinGW.

### Preparing the build
    On Linux:
    waf configure

    On Windows:
    waf configure --check-cxx-compiler=g++

### Building a static library
    waf build --static

### Building a shared library
    waf build --shared

### Running unit tests
    ./run_tests.sh

### Installing cppiniparser
    waf install

## Examples
__input.ini__
```
[foo]
key1=value1
key2=value2

[bar]
key3=value3
key4=value4
```
__output.ini__
```
[bar]
key4=value4
key5=value5

[foo]
key1=value1
key2=value2
key3=value3
```
__Main.cpp__
```c++
#include <iostream>
#include "INIParser.h"
using namespace std;
using namespace cppiniparser;

void TestRead() {
    INIConfig config = INIParser::Read("input.ini");
    vector<string> sections = config.Sections();
    vector<string>::const_iterator s = sections.begin();
    for (; s != sections.end(); ++s) {
        cout << "Section: " << *s << endl;
        vector<string> opts = config.Options(*s);
        vector<string>::const_iterator o = opts.begin();
        for (; o != opts.end(); ++o) {
            string value = config.GetOption(*s, *o);
            cout << "   - " << *o << "=" << value << endl;
        }
        cout << endl;
    }
}

void TestWrite() {
    INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");
    config.AddOption("foo", "key3", "value3");

    config.AddSection("bar");
    config.AddOption("bar", "key4", "value4");
    config.AddOption("bar", "key5", "value5");

    INIParser::Write(config, "output.ini");
}

int main() {
    TestRead();
    TestWrite();

    return 0;
}
```
