#ifndef CArgv_H
#define CArgv_H

#include <string>
#include <functional>
#include <iostream>

namespace CArgv {

class State {
 public:
  State(int argc, char **argv) :
   argc_(argc), argv_(argv) {
  }

  bool atEnd() const { return i_ >= argc_; }

  bool hasNext() const { return (i_ < argc_ - 1); }
  std::string next() { return std::string(argv_[++i_]); }
  void skip() { ++i_; }

  std::string arg() const { return std::string(argv_[i_]); }
  std::string opt() const { return std::string(&argv_[i_][1]); }
  std::string eopt() const { return std::string(&argv_[i_][2]); }

  bool isOpt() const { return (argv_[i_][0] == '-'); }
  bool isEOpt() const { return (isOpt() && argv_[i_][1] == '-'); }
  bool isOptTerm() const { return (isOpt() && argv_[i_][2] == '\0'); }

  void unhandled() {
    if (isOpt())
      std::cerr << "Unhandled option '" << argv_[i_] << "\n";
    else
      std::cerr << "Unhandled arg '" << argv_[i_] << "\n";
  }

 private:
  int    argc_ { 0 };
  char** argv_ { nullptr };
  int    i_    { 1 };
};

using ArgFn = std::function<void (const std::string &, State &)>;

void visit(int argc, char **argv, ArgFn &&visitOpt, ArgFn &&visitEOpt, ArgFn &&visitArg) {
  bool allowArgs = true;

  State state(argc, argv);

  while (! state.atEnd()) {
    if (allowArgs && state.isOpt()) {
      if (state.isEOpt()) {
        if (state.isOptTerm()) {
          allowArgs = false;
        }
        else {
          auto eopt = state.eopt();

          visitEOpt(eopt, state);
        }
      }
      else {
        auto opt = state.opt();

        visitOpt(opt, state);
      }
    }
    else {
      auto arg = state.arg();

      visitArg(arg, state);
    }

    state.skip();
  }
}

void visit(int argc, char **argv, ArgFn &&visitOpt, ArgFn &&visitArg) {
  visit(argc, argv, std::forward<ArgFn>(visitOpt), std::forward<ArgFn>(visitOpt),
        std::forward<ArgFn>(visitArg));
}

}

#endif
