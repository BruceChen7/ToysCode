#ifndef __CPPLUSPLUS_UTILITIES_LOG_H
#define __CPPLUSPLUS_UTILITIES_LOG_H
#include "STL.h"
#include <ostream>


namespace Toyscode
{
	namespace Utilities
	{

		class Logging 
		{
			public :
				enum class Loglevel
				{
					LOG_TRACE,
					LOG_DEBUG,
					LOG_MSG,
					LOG_WARN,
					LOG_ERR,
					LOG_FATAL,
				}; 

				Logging(const char* file,int line_num);
				// Logging(const char* file ,int line,Loglevel level,const char* func); 
				// Logging(const char* file, int line,bool to_abort);
				void set_log_level(Loglevel severity);
				Loglevel get_log_level();
				std::ostream& stream();
				~Logging();
			private: 
				class LoggingImp; 
				std::unique_ptr<LoggingImp> impl_;


		};

		#define TRACE  Logging(__FILE__,__LINE__).stream()

	}
}
#endif
