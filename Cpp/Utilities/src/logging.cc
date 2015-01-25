#include "logging.h"
#include <sstream> //used for ostringstream
#include <stdio.h>
#include <unistd.h> //write
#include <string.h> //used for strerror_r,errno
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

				//method
				LoggingImp(Loglevel level,int old_errno,const char *file ,int line); 
				void finish();

				//data members
				Loglevel level_;
				int line_num_; 
				std::ostringstream stream_;
				const char* file_name_;
				const char* base_name_;
				const char* function_;
				int old_errno_;
				static  const char* log_level_name[];

		};

		const char* Logging::LoggingImp::log_level_name[6] = 
		{
			"TRACE",
			"DEBUG",
			"MSG",
			"WARN",
			"ERR",
			"FATA", 
		};
       	
	   	//global LogLevel  variable 	
		Logging::Loglevel g_log_level = Logging::Loglevel::TRACE;
		//global error buffer 
		char g_err_buf[512];


		//Todo: write the current time and thread id in the message_head 
		Logging::LoggingImp::LoggingImp(Loglevel level,int old_errno,const char* file ,int line_num) \
																		:level_(level),line_num_(line_num),\
																		stream_(),old_errno_(old_errno),\
																		file_name_(file),base_name_(NULL),\
																		function_(NULL)
		{
			auto path_sep_pos = strrchr(file_name_,'/'); 
			base_name_ = (path_sep_pos != NULL) ? path_sep_pos+1:file_name_;

			char message_head[512];
			snprintf(message_head,sizeof(message_head),"%s : ",log_level_name[(int)level]); 
			stream_ << message_head;

			if(old_errno != 0)
			{
				stream_ << strerror_r(old_errno,g_err_buf,sizeof(g_err_buf)) << "(errno=" << old_errno << ") : "; 
				
			}
		}

		void Logging::LoggingImp::finish()
		{
			stream_ << " : " << base_name_ << " : " << line_num_ << "\n";
		}


		//used for Logging msg 
		Logging::Logging(const char *file, int line_num):impl_(new LoggingImp(Loglevel::MSG,0,file,line_num)) 
		{
		}
		
		//used for Logging Trace and logging debug 
		Logging::Logging(const char *file,int line_num,Logging::Loglevel level,const char* func_name):impl_(new LoggingImp(level,0,file,line_num))
		{
			impl_->stream_ << func_name << " : " ; 
		
		}

		//used for Logging WARN
		Logging::Logging(const char* file,int line_num,Logging::Loglevel level):impl_(new LoggingImp(level,0,file,line_num))
		{
		}

		Logging::Logging(const char* file,int line_num,bool to_abort)\
			:impl_(new LoggingImp(to_abort?Logging::Loglevel::FATAL:Logging::Loglevel::ERR,errno,file,line_num))
		{
		
		}

		void Logging::set_log_level(Logging::Loglevel level)
		{
			g_log_level = level;

		}

		Logging::Loglevel Logging::get_log_level()
		{
			return g_log_level ;
		}
		
		
		std::ostream& Logging::stream()
		{
			return impl_->stream_;
		}

		Logging::~Logging()
		{
			impl_->finish();
			std::string buf(impl_->stream_.str()); 
			ssize_t n = ::write(1,buf.data(),buf.size());

			if(impl_->level_ == Loglevel::FATAL)
			{
				abort();
			}

		
		} 

	}

}

