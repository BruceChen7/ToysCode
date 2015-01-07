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
			ID,
			STRING,
			INT,
			COMMA,
			COLON,     //
			SEMICOLON, // ;
			LPAREN,    //(
			RPAREN,    // )
			LBRACK,    //[
			RBRACK,	   //]
		    DOT,
			PLUS,
			MINUS,
			TIMES,
			DIVIDE,
			EQ,
			NEQ,	
			LT,
			LE,
			GT
			GE,
			AND,
			OR ,
			ASSIGN,
			ARRAY,
			IF,   
			THEN,
			ELSE,
			WHILE, 
			FOR,
			LET, 
			TYPE,
			IN,
			END,
			OF,
			BREAK,
			NIL,
			FUNCTION,
			VAR,
			UNKNOWN //default token type
		};

		struct code_token 
		{
		
			using List = std::vector<code_token>;

			//code_token position
			int row;   
			int column; 

			//token's value 	
			std::string value;

			//default token's type
			code_token_type type = code_token_type::UNKNOWN;
		
		};
		
		struct code_line 
		{
			using Ptr =  std::shared_ptr<code_line>;
			using List = std::vector<Ptr>; 
		
		
		};

		struct code_file
		{
			using  Ptr = std::shared_ptr<code_file> ;
			using  List = std::vector<Ptr>;

			code_file::Ptr parse(const string &code);
		
		};

	}

	



}

#endif

