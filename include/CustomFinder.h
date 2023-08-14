#pragma once
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "CallGraphBuilder.h"

using namespace clang::ast_matchers;
template<class T>
class CustomFinderBase
{
public:
    MatchFinder finder;
    T callback;
};

class FuncCallGraphFinder:public CustomFinderBase<CallGraphBuilder>{
    public:
        FuncCallGraphFinder();
    private:
        string functiondecl_matcher_name;
        string callExpr_mater_name;
};
