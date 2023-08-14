#include "CallGraphBuilder.h"
#include "CallGraph.h"

void CallGraphBuilder::run(const MatchFinder::MatchResult &Result)
{
    clang::ASTContext *Context = Result.Context;
    clang::SourceManager &SM = Result.Context->getSourceManager();
    if (auto *FD = Result.Nodes.getNodeAs<clang::FunctionDecl>("func_decl"))
    {
        string matcher_name = "func_decl";
        string decl_name = FD->getNameInfo().getAsString();
        get_AST_location(FD, SM, matcher_name, decl_name);
    }
    else if (auto *MD = Result.Nodes.getNodeAs<clang::DeclRefExpr>("call_ref"))
    {
        string matcher_name = "call_ref";
        string decl_name = MD->getNameInfo().getAsString();
        get_AST_location(MD, SM, matcher_name, decl_name);
    }
}

template<class T>
string CallGraphBuilder::get_AST_location(T* ASTNode,clang::SourceManager &SM,std::string &matcher_name,std::string &function_name){
    clang::SourceLocation source_location = ASTNode->getBeginLoc();
    string filename = SM.getFilename(source_location).str();
    string location_string = source_location.printToString(SM);
    llvm::outs()<<"file name is "<<filename <<"  "<< location_string << "   "<<matcher_name <<"  "<<function_name<<"\n";
    return filename;
}