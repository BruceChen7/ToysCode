#ifndef __STONE__SRC_LEXICAL__
#define __STONE__SRC_LEXICAL__
#include <string>
#include <vector>
#include <stdio.h>
#include <memory>


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
			std::shared_ptr<std::string >get_line(int pos);
			~File();
		private:
			FILE *fp_;
			std::vector<std::shared_ptr<std::string>> buffer_; 
	};

	class Lexical { 
		public:
			Lexical(File* source_code);
			void parse();
			bool is_string(std::string word) const;
		   	bool is_number(std::string word) const;
			bool is_interger(std::string word) const ;
		private:
			std::vector<Token> token_list_;
			File* source_code_file_; 
	};


}

#endif
