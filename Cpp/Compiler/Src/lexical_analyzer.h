#ifndef __CPP_COMPILER_LEXICAL_ANALYZER_H_
#define __CPP_COMPILER_LEXICAL_ANALYZER_H_

#include <vector>
#include <string>
#include <memory> 
using std::string;

namespace ToysCode
{
	namespace Compiler
	{
		enum class Code_token_type
		{
			#define TSYM(tk,s) tk,
			#include "token.h"
			#undef TSYM
			#define NONTSYM(tk,s) tk,
			#include "nontoken.h" 
			#undef NONTSYM 
			UNKNOWN //default token type
		};

		struct Code_token 
		{
		
			using List = std::vector<Code_token>;

			//code_token position
			int row;   
			int column; 

			//token's value 	
			std::string value;

			//default token's type
			Code_token_type type = Code_token_type::UNKNOWN;
		
		};
		
		struct Code_line 
		{
			using Ptr =  std::shared_ptr<Code_line>;
			using Vec = std::vector<Ptr>; 
		
		
		};

		struct Code_file
		{
			using  Ptr = std::shared_ptr<Code_file> ;
			using  Vec = std::vector<Ptr>;

			// Code_file::Ptr parse(const string &code);
		
		};

	} 
}

#endif

