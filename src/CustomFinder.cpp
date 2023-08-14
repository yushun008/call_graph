#include "CustomFinder.h"

FuncCallGraphFinder::FuncCallGraphFinder(){
    functiondecl_matcher_name = "func_decl";
    callExpr_mater_name = "call_expr";
    auto functiondecl_mather = functionDecl(hasBody(compoundStmt())).bind(functiondecl_matcher_name);
    auto call_matcher = callExpr(forEachDescendant(declRefExpr(to(functionDecl(hasBody(compoundStmt())))).bind(callExpr_mater_name)));
    finder.addMatcher(functiondecl_mather,&callback);
    finder.addMatcher(call_matcher,&callback);
}