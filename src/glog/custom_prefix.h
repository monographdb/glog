#pragma once
#include <glog/logging.h>

#include <iomanip>

inline void CustomPrefix(std::ostream& s, const google::LogMessageInfo& l,
                         void*) {
  s << "[time "                              //
    << std::setw(4) << 1900 + l.time.year()  // YY
    << "-"                                   // -
    << std::setw(2) << 1 + l.time.month()    // MM
    << "-"                                   // -
    << std::setw(2) << l.time.day()          // DD
    << "T"                                   // T
    << std::setw(2) << l.time.hour()         // hh
    << ":"                                   // :
    << std::setw(2) << l.time.min()          // mm
    << ":"                                   // :
    << std::setw(2) << l.time.sec()          // ss
    << "."                                   // .
    << std::setfill('0') << std::setw(6)     //
    << l.time.usec()                         // usec
    << "] "
    << "[level " << l.severity << "] "
    << "[thread " << l.thread_id << "] "
    << "[" << l.filename << ":" << l.line_number << "]";
};

inline void InitGoogleLogging(char** argv) {
  auto logtostderr = std::getenv("GLOG_logtostderr");
  if (!logtostderr) {
    FLAGS_logtostderr = true;
  }

  if (FLAGS_logtostdout || FLAGS_logtostderr) {
    FLAGS_logtostdout = false;
    FLAGS_logtostderr = true;
  }
  google::InitGoogleLogging(argv[0], &CustomPrefix);
}
