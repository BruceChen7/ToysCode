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
					TRACE,
					DEBUG,
					MSG,
					WARN,
					ERR,
					FATAL,
				}; 

				Logging(const char* file,int line_num);
				// Logging(const char* file ,int line,Loglevel level,const char* func); 
				// Logging(const char* file, int line,bool to_abort);
				static void set_log_level(Loglevel severity);
				static Loglevel get_log_level();
				std::ostream& stream();
				~Logging();
			private: 
				class LoggingImp; 
				std::unique_ptr<LoggingImp> impl_;


		};

		#define LOG_TRACE  \
			if(Logging::get_log_level() <= Logging::Loglevel::TRACE) \
						Logging(__FILE__,__LINE__).stream() 
	}
}
#endif
