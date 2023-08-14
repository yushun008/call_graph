#pragma once
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <string>
using namespace clang::ast_matchers;
using namespace std;

class CallGraphBuilder : public MatchFinder::MatchCallback
{
public:
    virtual void run(const MatchFinder::MatchResult &Result);
private:
    template <class T>
    string get_AST_location(T *ASTNode, clang::SourceManager &SM, std::string &matcher_name, std::string &function_name);
};
