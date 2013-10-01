set(LLVM_LINK_COMPONENTS
  Support
  )

add_clang_unittest(FrontendTests
  FrontendActionTest.cpp
  AnalyzerOptionsTest.cpp
  )
target_link_libraries(FrontendTests
  clangAST
  clangFrontend
  )
