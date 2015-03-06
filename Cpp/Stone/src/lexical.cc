#include "lexical.h"
#include <stdlib.h>
#include <assert.h>
#define kBufferSize (16 * 1024)
using namespace Stone;

File::File(const char* file_name):fp_(fopen(file_name,"r"))
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
	} 
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

Lexical::is_number(std::string word)
{
	auto  len = word.length();
	auto i = 0;

	while(i < len)
	{
		if(word[i]>="0" && word[i] <= "9")
			continue;
		else
			return false;
	}
	return true;
	
}
void Lexical::parse()
{	
}

