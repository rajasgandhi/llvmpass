#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include <iostream>
#include <fstream>

using namespace llvm;
//using namespace std;

namespace
{
  struct Hello : public FunctionPass
  {
    static char ID;
    Hello() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override
    {
      errs() << F.getName() << ": " << F.getInstructionCount() << "\n";
      /*for (BasicBlock *BB : F)
      {
        errs() << "BB has name" << BB->getName() << "\n";
      }*/
      for (Function::iterator bb = F.begin(), e = F.end(); bb != e; ++bb)
      {
        errs() << "BB has name" << bb->getName() << "\n";

      }
      return false;
    }
  }; // end of struct Hello
} // end of anonymous namespace

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM)
    { PM.add(new Hello()); });
