#include "lexical.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#define kBufferSize (16 * 1024)
using namespace Stone;

//global variables;
const char * g_err_buf[1024] = {
	"All is well",
	"The Token Is Too Long",
}; 

char g_status[1024];

File::File(const char* file_name):fp_(fopen(file_name,"r")),line_num_(0)
{ 
	buffer_.reserve(kBufferSize);

	if(fp_ == NULL)
	{ 
		::fprintf(stderr,"can't open the source code for read\n");
		exit(0); 
	}

}

void File::read2buffer()
{

	assert(fp_ != NULL); 
	//a buffer to store source code per line 
	char buffer[1024]; 

	while(::fgets(buffer,sizeof(buffer)-1,fp_))
	{ 
		auto tokens_per_line = std::make_shared<std::string>(buffer); 
		buffer_.push_back(tokens_per_line); 
		line_num_++;
	} 
}

int File::get_file_line_num() const 
{
	return line_num_;
}

std::shared_ptr<std::string> File::get_line(int pos)
{
	return buffer_[pos];
}


File::~File()
{
	::fclose(fp_);
}


Lexical::Lexical(File* source_code_file):source_code_file_(source_code_file),err_code_(0)
{ 
}

bool Lexical::is_number(const std::string& word) const 
{
	auto  len = word.length();
	auto i = 0;
	auto ptr = word.data(); 

	while(i < len)
	{
		if(::isspace(*ptr))
		{
			ptr++;
			continue;
		}
		else if(*ptr>='0' && *ptr <= '9')
		{
			ptr++;
			continue;
		}
		else
			return false;
	}
	return true; 
}

void Lexical::determin_token_type(const char *token,int line_num)
{ 
	assert(token != nullptr); 
	auto str  =  std::string(token); 
	
	struct Token tokens;
	tokens.value = str;
	tokens.line_num = line_num;	

	auto ptr = str.data();
	
	switch(*ptr)
	{
		case '+':
			if(::strcmp(ptr,"+") == 0)
			{
				tokens.type	 =  Code_Token_Type::Add;
				break; 
			}
			else 

		case '-':
			if(::strcmp(ptr,"-") == 0)
			{
				tokens.type = Code_Token_Type::Sub;
				break;
			}
		case '*': 
			if(::strcmp(ptr,"*") == 0)
			{
				tokens.type = Code_Token_Type::Mul;
				break;
			}
		case '/':
			if(::strcmp(ptr,"/") == 0)
			{ 
				tokens.type = Code_Token_Type::Div;
				break; 
			}
		case '=':
			if(::strcmp(ptr,"=") == 0)
			{
				tokens.type = Code_Token_Type::Assgin;
				break;
			}
			else if(::strcmp(ptr,"==") == 0)
			{
				tokens.type = Code_Token_Type::EQ;
			}
			
		case '<':
			if(::strcmp(ptr,"<") == 0)
			{
				tokens.type = Code_Token_Type::LT;
				break;
			}
			else if(::strcmp(ptr,"<=") == 0)
			{
				tokens.type = Code_Token_Type::LE;
			}
		case '>':
			if(::strcmp(ptr,">") == 0)
			{
				tokens.type = Code_Token_Type::Assgin;
				break;
			}
			else if(::strcmp(ptr,">=") == 0)
			{
				tokens.type = Code_Token_Type::EQ;
			} 

	}


}

int Lexical::get_next_token(const char **src, char *dest,int token_length)
{
	assert(dest != nullptr);
	assert(token_length > MAX_TOKEN_LEN);
	
	if(**src == '\n')
		return 0;

	while(isspace(**src))
		(*src)++;

	auto cnt = 0;

	while(!isspace(**src) && (**src) != '\0')
	{
		*dest = **src;
		dest++;
		(*src)++; 
		cnt++; 
		
		if(cnt > MAX_TOKEN_LEN)	
		{
			//there is something wrong with the token
			err_code_ = 1;
			return -1;
		}

	}
	
	//delete '\n'
	if(dest[cnt-1] == '\n')
		dest[cnt-1] = '\0';

	dest[cnt] = '\0';
	return cnt;

	
}

void Lexical::parse()
{	
	source_code_file_->read2buffer();
	auto total_line_num = source_code_file_->get_file_line_num();
	char tokens[MAX_TOKEN_LEN + 1];
	auto dest = tokens;

	for(int i = 0 ; i < total_line_num; i++)
	{
		std::shared_ptr<std::string> line = source_code_file_->get_line(i); 
		auto src = (*line).data();
		
		::memset(tokens,'\0',sizeof(tokens)); 
		
		while(get_next_token(&src,tokens,sizeof(tokens)) > 0)
		{ 
			ADD_ERROR_LIST(err_code_,err_vec_,i);

			//skip the comment
			if(::strncmp(tokens,"//",2) == 0)
				break;

			determin_token_type(tokens,i);
			ADD_ERROR_LIST(err_code_,err_vec_,i);

			::memset(tokens,'\0',sizeof(tokens)); 
		}
		
	
	}

}
