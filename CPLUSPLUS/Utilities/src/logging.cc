#include "logging.h"
#include <sstream>
#include <stdio.h>
using namespace Toyscode;
using namespace Utilities;

namespace Toyscode
{
	namespace Utilities
	{	
		class Logging::LoggingImp 
		{ 
			public:
				using Loglevel = Logging::Loglevel; 
				LoggingImp(Loglevel level,int old_errno,const char *file ,int line); 
				//members
				Loglevel level_;
				int line_num_; 
				std::ostringstream stream_;
				int old_errno_;
				const char* file_name_;
				static  const char* log_level_name[];

		};

		const char* Logging::LoggingImp::log_level_name[] = 
		{
			"TRACE",
			"DEBUG",
			"MSG",
			"WARN",
			"ERR",
			"FATA", 
		};
        
		//
		Logging::LoggingImp::LoggingImp(Loglevel level,int old_errno,const char* file ,int line_num):level_(level),line_num_(line_num),stream_(),old_errno_(old_errno)
		{
			char message_head[512];
			snprintf(message_head,sizeof(message_head),"%s %5d %s","time","thread id",log_level_name[level_]);
			stream_ << message_head;
		}



		//Logging implementation
		Logging::Logging(const char *file, int line_num):impl_(new LoggingImp(Loglevel::LOG_TRACE,0,file,0)) 
		{
		}
		
		void Logging::set_log_level(Logging::Loglevel level)
		{

				impl_->level_ = level;

		}

		Logging::Loglevel Logging::get_log_level()
		{
			return impl_->level_;
		}
		
		
		Logging::~Logging()
		{
		
		
		}
		
		


	}

}

