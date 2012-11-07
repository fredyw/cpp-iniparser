cpp-iniparser
=============

A small C++ INI parser library

How to build
------------
cpp-iniparser uses Waf build system (http://code.google.com/p/waf/)

### Building a static library ###
    waf configure
    waf build --static

### Building a shared library ###
    waf configure
    waf build --shared

### Running unit tests ###
cpp-iniparses uses GoogleTest (http://code.google.com/p/googletest/)

    waf build --test

Alternatively, we can also explicitly tell where the gtest header files and libraries are
    
    waf build --test --gtest_include=/gtest/include --gtest_lib=/gtest/lib

Examples
--------
input.ini
        [foo]
        key1=value1
        key2=value2
        
        [bar]
        key3=value3
        key4=value4

output.ini
        [bar]
        key4=value4
        key5=value5

        [foo]
        key1=value1
        key2=value2
        key3=value3

        #include &lt;iostream&gt;
        #include &#34;INIParser.h&#34;
        using namespace std;
        using namespace cppiniparser;
        
        void TestRead() {
            INIConfig config = INIParser::Read(&#34;input.ini&#34;);
            vector&lt;string&gt; sections = config.Sections();
            vector&lt;string&gt;::const_iterator s = sections.begin();
            for (; s != sections.end(); ++s) {
                cout &lt;&lt; &#34;Section: &#34; &lt;&lt; *s &lt;&lt; endl;
                vector&lt;string&gt; opts = config.Options(*s);
                vector&lt;string&gt;::const_iterator o = opts.begin();
                for (; o != opts.end(); ++o) {
                    string value = config.GetOption(*s, *o);
                    cout &lt;&lt; &#34;   - &#34; &lt;&lt; *o &lt;&lt; &#34;=&#34; &lt;&lt; value &lt;&lt; endl;
                }
                cout &lt;&lt; endl;
            }
        }
        
        void TestWrite() {
            INIConfig config;
            config.AddSection(&#34;foo&#34;);
            config.AddOption(&#34;foo&#34;, &#34;key1&#34;, &#34;value1&#34;);
            config.AddOption(&#34;foo&#34;, &#34;key2&#34;, &#34;value2&#34;);
            config.AddOption(&#34;foo&#34;, &#34;key3&#34;, &#34;value3&#34;);
        
            config.AddSection(&#34;bar&#34;);
            config.AddOption(&#34;bar&#34;, &#34;key4&#34;, &#34;value4&#34;);
            config.AddOption(&#34;bar&#34;, &#34;key5&#34;, &#34;value5&#34;);
        
            INIParser::Write(config, &#34;output.ini&#34;);
        }
        
        int main() {
            TestRead();
            TestWrite();
        
            return 0;
        }