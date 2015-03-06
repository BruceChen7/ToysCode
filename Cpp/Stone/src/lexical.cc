#include "lexical.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#define kBufferSize (16 * 1024)
using namespace Stone;

File::File(const char* file_name):fp_(fopen(file_name,"r")),line_num_(0)
{ 
	buffer_.reserve(kBufferSize);

	if(fp_ == NULL)
	{ 
		::fprintf(stderr,"can't open the source code for read\n");
		::printf("hello world \n");
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


Lexical::Lexical(File* source_code_file):source_code_file_(source_code_file)
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

void Lexical::determin_token_type(const char *token)
{

	::fprintf(stdout,"%s\n",token); 
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
			::fprintf(stderr,"%s\n","The Identifier or the Number name or the string literals name must be shorter than 64 ");
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

	for(auto i = 0 ; i < total_line_num; i++)
	{
		std::shared_ptr<std::string> line = source_code_file_->get_line(i); 
		auto src = (*line).data();
		
		::memset(tokens,'\0',sizeof(tokens)); 
		
		while(get_next_token(&src,tokens,sizeof(tokens))> 0)
		{ 
			determin_token_type(tokens);
			::memset(tokens,'\0',sizeof(tokens)); 
		}
	
	}

}

