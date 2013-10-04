//===- unittests/Frontend/AnalyzerOptionsTest.cpp - AnalyzerOptions tests ---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/StaticAnalyzer/Core/AnalyzerOptions.h"
#include "gtest/gtest.h"

using namespace llvm;
using namespace clang;

namespace {

TEST(AnalyzerOptionsTest, EmptyBlacklist) {
  AnalyzerOptions options;
  ASSERT_FALSE(options.headerIsBlacklisted("C:\\abc\\hello.h"));
  ASSERT_FALSE(options.headerIsBlacklisted("bla.h"));
}

TEST(AnalyzerOptionsTest, Simple) {
  AnalyzerOptions options;
  options.HeaderBlacklist.push_back("C:\\abc\\");
  options.HeaderBlacklist.push_back("/system/include");
  std::sort(options.HeaderBlacklist.begin(), options.HeaderBlacklist.end());
  ASSERT_TRUE(options.headerIsBlacklisted("C:\\abc\\hello.h"));
  ASSERT_FALSE(options.headerIsBlacklisted("/system/hello.h"));
}

TEST(AnalyzerOptionsTest, LongerList) {
  AnalyzerOptions options;
  options.HeaderBlacklist.push_back("D:\\abc\\");
  options.HeaderBlacklist.push_back("C:\\abc\\");
  options.HeaderBlacklist.push_back("/var/log/system");
  options.HeaderBlacklist.push_back("/system/include");
  options.HeaderBlacklist.push_back("/home/tmp/");
  options.HeaderBlacklist.push_back("../things/");
  std::sort(options.HeaderBlacklist.begin(), options.HeaderBlacklist.end());
  ASSERT_TRUE(options.headerIsBlacklisted("C:\\abc\\hello.h"));
  ASSERT_TRUE(options.headerIsBlacklisted("/var/log/system/../hello"));
  ASSERT_TRUE(options.headerIsBlacklisted("../things/foo.c"));
  ASSERT_FALSE(options.headerIsBlacklisted("D:\\ab\\"));
}

TEST(AnalyzerOptionsTest, CaseSensitive) {
  AnalyzerOptions options;
  options.HeaderBlacklist.push_back("C:\\abc\\");
  options.HeaderBlacklist.push_back("/system/include");
  std::sort(options.HeaderBlacklist.begin(), options.HeaderBlacklist.end());
  ASSERT_FALSE(options.headerIsBlacklisted("c:\\abc\\hello.h"));
  ASSERT_FALSE(options.headerIsBlacklisted("/system/Include/hello.h"));
}

} // anonymous namespace
