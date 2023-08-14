#pragma once
#include "clang/ASTMatchers/ASTMatchers.h"
using namespace clang::ast_matchers;


auto functiondecl_mather = functionDecl(hasBody(compoundStmt())).bind("func_decl");
auto call_matcher = callExpr(forEachDescendant(declRefExpr(to(functionDecl(hasBody(compoundStmt())))).bind("call_ref")));
