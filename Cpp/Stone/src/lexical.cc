#include "lexical.h"
#include <stdlib.h>
#include <assert.h>
#define kBufferSize (64 * 1024)
using namespace Stone;

File::File(const char* file_name):fd_(::fileno(fopen(file_name,"r")))
{ 
	buffer.reserve(kBufferSize);

	if(fd_ == -1)
	{ 
		::fprintf(stderr,"can't open the source code for read");
		exit(0); 
	}

}

int File::read_to_string()
{
	::assert(fd != -1); 


}

