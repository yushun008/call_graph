#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceLocation.h"
#include "llvm/Support/Signals.h"
#include <string>
#include <unordered_set>
#include "CallGraph.h"
#include "CallGraphBuilder.h"
#include "CustomFinder.h"


using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

static cl::extrahelp common_help(CommonOptionsParser::HelpMessage);

static cl::extrahelp MoreHelp("\n more help text...\n");
static unordered_set<string> file_name_buffer;
static unordered_set<string> source_location_buffer;
static unordered_set<string> function_name_buffer;

int main(int argc, char const *argv[])
{
    llvm::sys::PrintStackTraceOnErrorSignal(argv[0]);
    auto ExpectedParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
    if(!ExpectedParser){
        llvm::errs() << ExpectedParser.takeError();
    }
    CommonOptionsParser &OptionParser = ExpectedParser.get();
    FuncCallGraphFinder finder;

    ClangTool Tool(OptionParser.getCompilations(), OptionParser.getSourcePathList());
    return Tool.run(newFrontendActionFactory(&finder.finder).get());
}
