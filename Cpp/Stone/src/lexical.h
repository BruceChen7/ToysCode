#ifndef __STONE__SRC_LEXICAL__
#define __STONE__SRC_LEXICAL__
#include <string>
#include <vector>
#include <stdio.h>
#include <memory>
#include <stdio.h>


//macros
#define MAX_TOKEN_LEN 128
#define ADD_ERROR_LIST(_err_code,_err_vec,_line_num,_token) do \
{														\
	if(err_code_) {                                    \
				::snprintf(g_status,sizeof(g_status),"Something Wrong With Your Code In Line : %d  :: %s :: %s\n",_line_num,g_err_buf[_err_code],_token);\
				err_vec_.push_back(g_status);\
				err_code_ = 0;\
	}\
}while(0)

namespace Stone
{

	enum class Code_Token_Type
	{
		Identifier,
		Integer,
		String,
		While, 				// while
		If,  				// if				
		Add,				// + 
		Sub,  				// -
		Mul,				// *
		Div,				// /
		Mod,				// %
		LT,					// <
		GT,					// >
		LE,					// <=
		GE,					// >=
		EQ,					// == 
		Assgin,              // =
		LBRACE,             // {
		RBRACE,             // }
	};

	struct Token{
		int line_num; 
	 	Code_Token_Type type; 
		std::string value;
	};
	
	class File {
		public:
			File(const char *filename);
			File(const File& another_file) = delete; 
			File& operator=(const File&) = delete;
			void read2buffer();
			int get_file_line_num() const;
			std::shared_ptr<std::string >get_line(int pos);
			~File();
		private:
			FILE *fp_;
			std::vector<std::shared_ptr<std::string>> buffer_; 
			int line_num_;
	};

	class Lexical { 
		public:
			Lexical(File* source_code);
			//ensure dest has enough space to contain tokens
			//each time get a token ,the 'src' points to next tokens to be get 
			//and tokens is stored into dest
			int get_next_token(const char **src, char *dest,int token_len);
			void determin_token_type(const char *dest,int line);
			void parse();
			bool is_string(const std::string& word) const;
			bool is_interger(const std::string& word) const ;
			bool is_identifier(const std::string& word) const;
			std::shared_ptr<struct Token> get_token_info(int pos);
		private:
			std::vector<Token> token_list_;
			File* source_code_file_; 
			std::vector<std::string> err_vec_;
			int err_code_; 
	};

}

#endif
