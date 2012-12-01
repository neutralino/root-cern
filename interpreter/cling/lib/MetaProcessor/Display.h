#ifndef CLING_DISPLAY_H
#define CLING_DISPLAY_H

#include <string>

namespace llvm {
  class raw_ostream;
}

namespace cling {

void DisplayClasses(llvm::raw_ostream &stream,
                    const class Interpreter *interpreter, bool verbose);
void DisplayClass(llvm::raw_ostream &stream, 
                  const Interpreter *interpreter, const char *className, 
                  bool verbose);

void DisplayGlobals(llvm::raw_ostream &stream, const Interpreter *interpreter);
void DisplayGlobal(llvm::raw_ostream &stream, const Interpreter *interpreter, 
                   const std::string &name);

}

#endif