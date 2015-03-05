#ifndef __STONE__SRC_LEXICAL__
#define __STONE__SRC_LEXICAL__
#include <string>
#include <vector>
#include <stdio.h>
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
			void read_to_string();
		private:
			FILE *fd_;
			std::vector<std::string> buffer; 
	};

	class Lexical { 
		public:
			Lei 
	
		private:
			std::vector<Token> token_list_;
			bool has_more_
	
	};


}

#endif
