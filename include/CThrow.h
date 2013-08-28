#ifndef CTHROW_H
#define CTHROW_H

#define CThrowMgrInst CThrowMgr::getInstance()

#define CTHROW(m) CThrowMgrInst->doThrow((m),__FILE__,__LINE__)
#define CITHROW(i) CThrowMgrInst->doThrow(i)

#define CTHROW_IF(t,m) if (t) CThrowMgrInst->doThrow((m),__FILE__,__LINE__)
#define CITHROW_IF(t,i) if (t) CThrowMgrInst->doThrow(i)

#include <signal.h>
#include <stdlib.h>

#include <iostream>

enum CThrowType {
  CTHROW_THROW,
  CTHROW_SEGV,
  CTHROW_EXIT,
  CTHROW_PRINT
};

struct CThrow {
  std::string message;
  std::string file;
  int         line;

  CThrow(const std::string &message1, const std::string &file1, int line1) :
    message(message1), file(file1), line(line1) {
  }
};

class CThrowMgr {
 private:
  CThrowType type_;

 public:
  static CThrowMgr *getInstance() {
    static CThrowMgr *instance;

    if (instance == NULL)
      instance = new CThrowMgr;

    return instance;
  }

  void setType(CThrowType type) { type_ = type; }

  CThrowType getType() { return type_; }

  void doThrow(const std::string &message, const std::string &file, int line) {
    if      (type_ == CTHROW_THROW)
      throw new CThrow(message, file, line);
    else if (type_ == CTHROW_SEGV) {
      std::cerr << file << ":" << line << ":" << message << std::endl;
      raise(SIGSEGV);
    }
    else if (type_ == CTHROW_PRINT) {
      std::cerr << file << ":" << line << ":" << message << std::endl;
    }
    else {
      std::cerr << file << ":" << line << ":" << message << std::endl;
    }

    if (type_ == CTHROW_EXIT)
      exit(1);
  }

  void doThrow(int id) {
    if      (type_ == CTHROW_THROW)
      throw id;
    else if (type_ == CTHROW_SEGV) {
      std::cerr << "throw:" << id << std::endl;
      raise(SIGSEGV);
    }
    else if (type_ == CTHROW_PRINT) {
      std::cerr << "throw:" << id << std::endl;
    }
    else {
      std::cerr << "throw:" << id << std::endl;
    }

    if (type_ == CTHROW_EXIT)
      exit(1);
  }

 private:
  CThrowMgr() :
   type_(CTHROW_THROW) {
    if      (getenv("CTHROW_THROW") != NULL)
      type_ = CTHROW_THROW;
    else if (getenv("CTHROW_SEGV" ) != NULL)
      type_ = CTHROW_SEGV;
    else if (getenv("CTHROW_EXIT" ) != NULL)
      type_ = CTHROW_EXIT;
    else if (getenv("CTHROW_PRINT") != NULL)
      type_ = CTHROW_PRINT;
  }

 ~CThrowMgr() {
  }
};

#endif
