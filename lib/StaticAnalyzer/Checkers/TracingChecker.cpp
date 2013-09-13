//== TraversalChecker.cpp -------------------------------------- -*- C++ -*--=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// These checkers trace various aspects of the ExprEngine's traversal of the CFG
// as it builds the ExplodedGraph.
//
//===----------------------------------------------------------------------===//
#include "ClangSACheckers.h"
#include "clang/AST/ParentMap.h"
#include "clang/AST/StmtObjC.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;
using namespace ento;

namespace {
  class TracingChecker : public Checker<check::PreStmt<DeclStmt>,
                                        check::PostStmt<DeclStmt> > {
public:

    void checkPreStmt(const DeclStmt *s, CheckerContext &C) const {
      llvm::outs() << "checkPreStmt<DeclStmt> ";
      s->dump();
      llvm::outs() << "\n\n";
    }

    void checkPostStmt(const DeclStmt *s, CheckerContext &C) const {
      llvm::outs() << "checkPreStmt<DeclStmt> ";
      s->dump();
      llvm::outs() << "\n";
    }

};
}

void ento::registerTracingChecker(CheckerManager &mgr) {
  mgr.registerChecker<TracingChecker>();
}

