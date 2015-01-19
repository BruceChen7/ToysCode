#include "logging.h"

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
				LoggingImp(Loglevel level,int old_errno,int line); 
				//members
				Loglevel severity_;
				int line_num_; 
				// std::ostream stream_;
				int old_errno_;
				// const char* file_;

		};

        //
		Logging::LoggingImp::LoggingImp(Loglevel level,int old_errno,int line):severity_(level),line_num_(line),old_errno_(old_errno)
		{
		}



		//Logging implementation
		Logging::Logging(const char *file, int line_num):impl_(new LoggingImp(Loglevel::LOG_TRACE,__LINE__,0)) {}
		
		void Logging::set_log_level(Logging::Loglevel severity)
		{

				impl_->severity_ = severity;

		}

		Logging::Loglevel Logging::get_log_level()
		{
			return impl_->severity_;
		}
		
		
		Logging::~Logging() = default;
		
		


	}

}

