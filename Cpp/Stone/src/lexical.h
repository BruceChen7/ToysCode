#ifndef __STONE__SRC_LEXICAL__
#define __STONE__SRC_LEXICAL__
#include <string>
#include <vector>

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
			int read_to_string(int max_size,std::string* content);
			File(const File& another_file) = delete;

			static int kBuferSize = 64 * 1024;
		private:
			int fd_;
			char buf[kBuferSize]; 
	
	};

	class Lexical { 
		
	
		private:
			std::vector<Token> token_list_;
			bool has_more_
	
	};


}

#endif
