#ifndef __CPLUSPLUS_ALGORITHM_LEXICAL_ANALYZER_H_
#define __CPLUSPLUS_ALGORITHM_LEXICAL_ANALYZER_H_

#include "../STL.h"
#include <memory>
namespace ToysCode
{
	namespace Token
	{
		enum class code_token_type
		{
			Identifier,
			Float,
			String,
		   	Reserved,	
			Unknown
		};

		struct code_token 
		{
		
			using code_token_list = std::vector<code_token>;
			int row;
			std::string value;
			code_token_type type = code_token_type::Unknown;
			int column; 
		
		};
		
		struct code_line 
		{
			using std::shared_ptr<code_line> =  Ptr;

		
		
		};

		struct code_file
		{
			using std::shared_ptr<code_file> = Ptr ;

			code_file::Ptr parse(const string &code);
		
		};

	}

	



}

#endif

