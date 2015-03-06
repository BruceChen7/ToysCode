#ifndef __STONE__SRC_LEXICAL__
#define __STONE__SRC_LEXICAL__
#include <string>
#include <vector>
#include <stdio.h>
#include <memory>
#define MAX_TOKEN_LEN 64

namespace Stone
{

	enum class Code_Token_Type
	{
		Identifier,
		Integer,
		String 
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
			void determin_token_type(const char *dest);
			void parse();
			bool is_string(const std::string& word) const;
		   	bool is_number(const std::string& word) const;
			bool is_interger(const std::string& word) const ;
			bool is_annotation(const std::string& word) const ;
		private:
			std::vector<Token> token_list_;
			File* source_code_file_; 
	};


}

#endif
