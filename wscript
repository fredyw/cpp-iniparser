#!/usr/bin/env python

import os, shutil, subprocess, platform
from waflib.Task import Task
from waflib import Context

APPNAME = 'cppiniparser'
VERSION = '0.1'

top = '.'
out = 'build'

cxxflags = ['-g', '-Wall']

source_files = ['src/INIConfig.cpp',
                'src/INIParser.cpp',
                'src/Utilities.cpp']
target_file = 'cppiniparser'
include_dir = ['include']

test_files = ['test/INIConfigTest.cpp',
              'test/INIParserTest.cpp',
              'test/UtilitiesTest.cpp']
test_libs = ['pthread', 'gtest_main']
test_libs_dir = [os.path.join(os.getcwd(), out)]
test_output = 'test_output'

def options(ctx):
    ctx.load('compiler_cxx')
    ctx.add_option('--shared', action='store_true', default=False, help='build shared library')
    ctx.add_option('--static', action='store_true', default=False, help='build static library')
    ctx.add_option('--test', action='store_true', help='build and execute unit tests')
    ctx.add_option('--gtest_include', action='store', help='gtest include directory')
    ctx.add_option('--gtest_lib', action='store', help='gtest lib directory')
     
def configure(ctx):
    ctx.load('compiler_cxx')

def dist(ctx):
    ctx.excl = ['**/.*pyc', '**/*.swp', 'build', '.*']
    
def build(ctx):
    def build_static(ctx):
        ctx.stlib(source=source_files, target=target_file, includes=include_dir,
                  cxxflags=cxxflags)

    def build_shared(ctx):
        ctx.shlib(source=source_files, target=target_file, includes=include_dir,
                  cxxflags=cxxflags)

    def get_unit_test():
        for test_file in test_files:
            test_file_basename = os.path.basename(test_file)
            test_target_name = 'test_' + test_file_basename[0:test_file_basename.index('.')]
            test_target = os.path.join(test_output, test_target_name)
            yield (test_file, test_target)
            
    def build_unit_tests(ctx):
        includes = include_dir
        libpath = test_libs_dir
        if ctx.options.gtest_include:
            gtest_include = os.path.abspath(ctx.options.gtest_include)
            ctx.to_log('GoogleTest include : %s\n' % gtest_include)
            includes += [gtest_include] 
        if ctx.options.gtest_lib:
            gtest_lib = os.path.abspath(ctx.options.gtest_lib)
            ctx.to_log('GoogleTest library : %s\n' % gtest_lib)
            libpath += [gtest_lib]
        
        for (test_file, test_target) in get_unit_test():
            ctx.program(source=test_file, target=test_target,
                        includes=includes,
                        libpath=libpath,
                        lib=test_libs + [target_file])
            
    def exec_unit_tests(ctx):
        if ctx.options.shared:
            lib_dir = os.path.join(os.getcwd(), out)
            if platform.system().lower().startswith('win'):
                os.environ['PATH'] = (lib_dir + os.pathsep + os.environ['PATH']
                                      if os.environ.has_key('PATH')
                                      else lib_dir) 
            else:
                os.environ['LD_LIBRARY_PATH'] = (lib_dir + os.pathsep + os.environ['LD_LIBRARY_PATH']
                                                 if os.environ.has_key('LD_LIBRARY_PATH')
                                                 else lib_dir)
                
        for (test_file, test_target) in get_unit_test():
            if platform.system().lower().startswith('win'):
                test_target += '.exe'
            ctx(rule=test_target, source=test_target)
    
    if ctx.options.shared:
        build_shared(ctx)
    elif ctx.options.static:
        build_static(ctx)
    else:
        ctx.options.shared = True
        build_shared(ctx)

    if ctx.options.test:
        build_unit_tests(ctx)
        exec_unit_tests(ctx)
