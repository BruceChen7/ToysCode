#ifndef __CPPLUSPLUS_UTILITIES_LOG_H
#define __CPPLUSPLUS_UTILITIES_LOG_H
#include "Utilities/include/STL.h"

#include <ostream>

namespace Toyscode {
namespace Utilities {

class Logging {
 public:
  enum class Loglevel {
    TRACE,
    DEBUG,
    MSG,
    WARN,
    ERR,
    FATAL,
  };

  // used for LOG_MSG
  Logging(const char* file, int line_num);

  // used for LOG_WARN
  Logging(const char* file, int line_num, Logging::Loglevel level);

  // used for LOG_TRACE,LOG_DEBUG
  Logging(const char* file, int line, Loglevel level, const char* func);

  Logging(const char* file, int line, bool to_abort);
  static void set_log_level(Loglevel severity);
  static Loglevel get_log_level();
  std::ostream& stream();
  ~Logging();

 private:
  class LoggingImp;
  std::unique_ptr<LoggingImp> impl_;
};

#define LOG_TRACE                                           \
  if (Logging::get_log_level() <= Logging::Loglevel::TRACE) \
  Logging(__FILE__, __LINE__, Logging::Loglevel::TRACE, __func__).stream()
#define LOG_DEBUG                                           \
  if (Logging::get_log_level() <= Logging::Loglevel::DEBUG) \
  Logging(__FILE__, __LINE__, Logging::Loglevel::DEBUG, __func__).stream()
#define LOG_MSG                                           \
  if (Logging::get_log_level() <= Logging::Loglevel::MSG) \
  Logging(__FILE__, __LINE__).stream()
#define LOG_WARN Logging(__FILE__, __LINE__, Logging::Loglevel::WARN).stream()
#define LOG_ERR Logging(__FILE__, __LINE__, Logging::Loglevel::ERR).stream()
#define LOG_FATAL Logging(__FILE__, __LINE__, Logging::Loglevel::FATAL).stream()
#define LOG_SYSERR Logging(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL Logging(__FILE__, __LINE__, true).stream()

}  // namespace Utilities
}  // namespace Toyscode
#endif
