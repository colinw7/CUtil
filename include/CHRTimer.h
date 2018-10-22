#ifndef CHRTimer_H
#define CHRTimer_H

#include <CHRTime.h>

#include <map>
#include <string>
#include <cstring>
#include <cassert>

#define CHRTimerMgrInst CHRTimerMgr::getInstance()

class CHRTimerMgr {
 public:
  static CHRTimerMgr *getInstance() {
    static CHRTimerMgr *instance;

    if (! instance)
      instance = new CHRTimerMgr;

    return instance;
  }

  static bool getBoolEnv(const char *envname) {
    char *env = getenv(envname);
    if (! env) return false;

    uint len = strlen(env);

    if (len > 4) return false;

    char str[5];

    uint i = 0;

    for ( ; env[i] != '\0'; ++i) str[i] = tolower(env[i]);
    for ( ; i < 5         ; ++i) str[i] = '\0';

    if (strcmp(str, "yes" ) == 0 || strcmp(str, "on") == 0 ||
        strcmp(str, "true") == 0 || strcmp(str, "1" ) == 0)
      return true;

    return false;
  }

  static double getRealEnv(const char *envname, double def=0.0) {
    char *env = getenv(envname);
    if (! env) return def;

    return atof(env);
  }

  bool isActive() const {
    if (! active_)
      return getBoolEnv("HRTIMER_ACTIVE");

    return active_;
  }

  void setActive(bool active=true) {
    active_ = active;
  }

  bool start(int *ind, const char *msg=nullptr, bool elapsed=false) {
    HRTimer &timer = timers_[ind_];

    if (timer.active) {
      std::cerr << "No timer slots remaining" << std::endl;
      return false;
    }

    *ind = ind_;

    timer.time   = CHRTime::getTime();
    timer.active = true;

    ++num_active_;

    //---

    // Find Next Timer Slot

    ++ind_;

    int count = 1;

    if (ind_ >= MAX_TIMERS)
      ind_ = 0;

    while (timers_[ind_].active && count < MAX_TIMERS) {
      ++ind_;
      ++count;

      if (ind_ >= MAX_TIMERS)
        ind_ = 0;
    }

    if (msg) {
      if (! elapsed) {
        std::cout << ">" << padStr() << msg;

        timeStamp(timer);

        std::cout << std::endl;
      }
    }

    return true;
  }

  bool end(int ind, long *secs=nullptr, long *usecs=nullptr,
           const char *msg=nullptr, bool elapsed=false) {
    HRTimer &timer = timers_[ind];

    assert(timer.active);

    CHRTime now = CHRTime::getTime();

    CHRTime d = CHRTime::diffTime(timer.time, now);

    if (secs ) *secs  = d.secs;
    if (usecs) *usecs = d.usecs;

    timer.active = false;

    --num_active_;

    if (msg) {
      double t = d.getSecs();

      if (! elapsed) {
        std::cout << "<" << padStr() << msg << " " << t;

        timeStamp(timer);

        std::cout << std::endl;
      }
      else {
        double tol = getRealEnv("HRTIMER_TOL");

        if (tol < 0.0 || t >= tol)
          std::cout << padStr() << msg << " " << t << std::endl;
      }
    }

    return true;
  }

  CHRTime elapsed(int ind) {
    HRTimer &timer = timers_[ind];

    assert(timer.active);

    return timer.time;
  }

 private:
  CHRTimerMgr() {
   startTime_ = CHRTime::getTime();
  }

  const std::string &padStr() const {
    static std::string str;

    if (int(str.size()) != num_active_) {
      str = "";

      for (int i = 0; i < num_active_; ++i)
        str += " ";
    }

    return str;
  }

 private:
  enum { MAX_TIMERS = 50 };

 private:
  struct HRTimer {
    bool    active { false };
    CHRTime time;

    HRTimer() { }
  };

 private:
  void timeStamp(const HRTimer &timer) const {
    if (getBoolEnv("HRTIMER_STAMP")) {
      CHRTime now = CHRTime::getTime();

      CHRTime d = CHRTime::diffTime(timer.time, now);

      double t = d.getSecs();

      std::cout << " [" << t << "]";
    }
  }

 private:
  int     ind_        { 0 };
  int     num_active_ { 0 };
  HRTimer timers_[MAX_TIMERS];
  bool    active_     { false };
  CHRTime startTime_;
};

//------

class CScopeTimer {
 public:
  CScopeTimer(const std::string &id) :
   id_(id) {
    if (! CHRTimerMgrInst->isActive()) return;

    if (! CHRTimerMgrInst->start(&timer_id_, id_.c_str(), /*elapsed*/false))
      timer_id_ = -1;
  }

 ~CScopeTimer() {
    if (timer_id_ < 0) return;

    long secs, usecs;

    CHRTimerMgrInst->end(timer_id_, &secs, &usecs, id_.c_str(), /*elapsed*/false);
  }

 private:
  std::string id_;
  int         timer_id_ { -1 };
};

//-----

class CElapsedTimer {
 public:
  CElapsedTimer(const std::string &id) :
   id_(id) {
    if (! CHRTimerMgrInst->isActive()) return;

    if (! CHRTimerMgrInst->start(&timer_id_, id_.c_str(), /*elapsed*/true))
      timer_id_ = -1;
  }

 ~CElapsedTimer() {
    if (timer_id_ < 0) return;

    long secs, usecs;

    CHRTimerMgrInst->end(timer_id_, &secs, &usecs, id_.c_str(), /*elapsed*/true);
  }

 private:
  std::string id_;
  int         timer_id_ { -1 };
};

//-----

class CIncrementalTimer {
 public:
  CIncrementalTimer(const std::string &id) :
   id_(id) {
    active_ = CHRTimerMgrInst->isActive();
  }

 ~CIncrementalTimer() {
    report();
  }

  void reset() {
    active_ = CHRTimerMgrInst->isActive();

    elapsed_ = CHRTime();
  }

  void start() {
    if (! active_) return;

    ++count_;

    if (! CHRTimerMgrInst->start(&timer_id_, nullptr, /*elapsed*/false))
      timer_id_ = -1;
  }

  void stop() {
    if (! active_) return;

    if (timer_id_ < 0) return;

    long secs, usecs;

    CHRTimerMgrInst->end(timer_id_, &secs, &usecs, nullptr, /*elapsed*/false);

    elapsed_ += CHRTime(secs, usecs);
  }

  void report() {
    if (! active_) return;

    if (! count_) return;

    double elapsed  = elapsed_.getSecs();
    double interval = elapsed/count_;

    std::cout << id_ << ": total=" << elapsed << " calls=" << count_ <<
                 " interval=" << interval << std::endl;
  }

 private:
  std::string id_;
  bool        active_   { false };
  int         timer_id_ { -1 };
  CHRTime     elapsed_  { 0 };
  long        count_    { 0 };
};

//------

#define CIncrementalTimerMgrInst CIncrementalTimerMgr::instance()

class CIncrementalTimerMgr {
 public:
  static CIncrementalTimerMgr *instance() {
    static CIncrementalTimerMgr *inst;

    if (! inst)
      inst = new CIncrementalTimerMgr;

    return inst;
  }

 ~CIncrementalTimerMgr() {
    clear();
  }

  CIncrementalTimer *get(const std::string &id) {
    auto p = timers_.find(id);

    if (p == timers_.end())
      p = timers_.insert(p, Timers::value_type(id, new CIncrementalTimer(id)));

    return (*p).second;
  }

  void clear() {
    for (const auto &timer : timers_)
      delete timer.second;

    timers_.clear();
  }

 private:
  CIncrementalTimerMgr() { }

 private:
  using Timers = std::map<std::string,CIncrementalTimer *>;

  Timers timers_;
};

//------

class CIncrementalTimerScope {
 public:
  CIncrementalTimerScope(const std::string &id) :
   timer_(CIncrementalTimerMgrInst->get(id)) {
    timer_->start();
  }

  CIncrementalTimerScope(CIncrementalTimer *timer) :
   timer_(timer) {
    timer_->start();
  }

 ~CIncrementalTimerScope() {
    timer_->stop();
  }

 private:
  CIncrementalTimer *timer_ { nullptr };
};

#endif
