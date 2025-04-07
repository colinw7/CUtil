#ifndef CInterval_H
#define CInterval_H

#include <iostream>
#include <optional>

class CInterval {
 public:
  enum class TimeType {
    NONE,
    YEARS,
    MONTHS,
    WEEKS,
    DAYS,
    HOURS,
    MINUTES,
    SECONDS
  };

  struct TimeData {
    double year   { 0.0 }; // year
    double month  { 0.0 }; // month
    double day    { 0.0 }; // day
    double hour   { 0.0 }; // hour
    double minute { 0.0 }; // minute
    double second { 0.0 }; // second
  };

  using OptInt  = std::optional<int>;
  using OptUInt = std::optional<uint>;
  using OptReal = std::optional<double>;

 public:
  CInterval(double min=0.0, double max=1.0);

  //! get/set ideal interval start
  double start() const { return data_.start; }
  void setStart(double r) { data_.start = r; invalidate(); }

  //! get/set ideal interval end
  double end() const { return data_.end; }
  void setEnd(double r) { data_.end = r; invalidate(); }

  //! get/set ideal number of major ticks
  uint numMajor() const { return data_.numMajor; }
  void setNumMajor(uint i) { data_.numMajor = i; invalidate(); }
  void resetNumMajor() { data_.numMajor = 0; invalidate(); }

  //! get/set values are integral
  bool isIntegral() const { return integral_; }
  void setIntegral(bool b) { integral_ = b; invalidate(); }

  //! get/set values are dates
  bool isDate() const { return date_; }
  void setDate(bool b) { date_ = b; invalidate(); }

  //! get/set values are times
  bool isTime() const { return time_; }
  void setTime(bool b) { time_ = b; invalidate(); }

  //! get/set use log scaling
  bool isLog() const { return log_; }
  void setLog(bool b) { log_ = b; invalidate(); }

  //! get/set required major increment
  bool hasMajorIncrement() const { return !!majorIncrement_; }
  double majorIncrement() const { return majorIncrement_.value_or(0.0); }
  void setMajorIncrement(double r) { majorIncrement_ = r; invalidate(); }
  void resetMajorIncrement() { majorIncrement_.reset(); invalidate(); }

  //! get/set required increment multiplier
  uint tickIncrement() const { return tickIncrement_.value_or(0); }
  void setTickIncrement(uint r) { tickIncrement_ = r; invalidate(); }
  void resetTickIncrement() { tickIncrement_.reset(); invalidate(); }

  //! get/set required origin
  double origin() const { return origin_.value_or(0.0); }
  void setOrigin(double r) { origin_ = r; }

  //---

  double interval(int i) const;
  double minorInterval(int i, int j) const;

  //---

  // get calculated start/end/increment/num major/num minor
  double calcStart    () const { constInit(); return calcData_.start    ; }
  double calcEnd      () const { constInit(); return calcData_.end      ; }
  double calcIncrement() const { constInit(); return calcData_.increment; }
  uint   calcNumMajor () const { constInit(); return calcData_.numMajor ; }
  uint   calcNumMinor () const { constInit(); return calcData_.numMinor ; }

  // get interval for value
  int valueInterval(double r) const;

  // get range of interval
  void intervalValues(int i, double &min, double &max) const;

  //---

 private:
  struct GapData;

  void constInit() const;

  void init();

  double initIncrement(double imin, double imax, bool integral) const;

  bool testAxisGaps(double start, double end, double testIncrement, uint testNumGapTicks,
                    GapData &axisGapData);

  void invalidate() { calcValid_ = false; originValid_ = false; }

  double valueStart() const;

 private:
  struct GapData {
    double start     { 0.0 };
    double end       { 0.0 };
    double increment { 0.0 };
    uint   numMajor  { 0 };
    uint   numMinor  { 0 };

    GapData() { }

    GapData(double start1, double end1, double increment1=0.0, uint numMajor1=0, uint numMinor1=0) :
     start(start1), end(end1), increment(increment1), numMajor(numMajor1), numMinor(numMinor1) {
    }

    bool isSet() const { return (start != 0.0 || end != 0.0); }

    void print(const std::string &prefix="") {
      std::cerr << prefix << "Start: " << start << " End: " << end << " Incr: " << increment <<
                   " NumMajor: " << numMajor << " NumMinor: " << numMinor << "\n";
    }
  };

  struct GoodTicks {
    uint min {  4 };
    uint max { 12 };
    uint opt { 10 };

    bool isGood(uint n) const {
      return (n >= min && n <= max);
    }

    bool isMoreOpt(uint n1, uint n2) const {
      return (std::abs(int(n1) - int(opt)) < std::abs(int(n2) - int(opt)));
    }
  };

  GapData   data_;                              //!< axis preferred data
  bool      integral_       { false };          //!< is integral
  bool      date_           { false };          //!< is date
  bool      time_           { false };          //!< is time
  bool      log_            { false };          //!< is log
  OptReal   majorIncrement_;                    //!< required major increment (must be > 0.0)
  OptUInt   tickIncrement_;                     //!< required tick increment (must be > 0)
  GoodTicks goodTicks_;                         //!< ideal tick data
  GapData   calcData_;                          //!< calculated tick data
  bool      calcValid_      { false };          //!< are calculated values valid
  OptReal   origin_;                            //!< required origin
  bool      originValid_    { false };          //!< is calculated origin valid
  double    originStart_      { 0.0};           //!< calculated start for explicit origin
  TimeType  timeType_       { TimeType::NONE }; //!< time type
  TimeData  startTime_;                         //!< start year
};

#endif
