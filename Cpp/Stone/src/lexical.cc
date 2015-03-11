#include "lexical.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#define kBufferSize (16 * 1024)
using namespace Stone;

//global variables;
const char * g_err_buf[32] = {
	"All is well",
	"The Token Is Too Long",
	"I Do Not know What The Symbol Is,May Be, You Should Use blank Character To Separate Them"
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


File::File(const File* another_file)
{ 
	line_num_ = another_file->line_num_;
	fp_ = another_file->fp_;
	buffer_ = another_file->buffer_;
}

File::~File()
{
}


Lexical::Lexical(File* source_code_file):source_code_file_(std::make_shared<File>(source_code_file)),err_code_(0)
{ 
}

bool Lexical::is_interger(const std::string& word) const 
{
	auto ptr = word.data(); 

	//skip '-' or space  or '+'
	if(*ptr == '-' || ::isspace(*ptr) || *ptr == '+' )
		ptr++; 

	while(*ptr != '\0')
	{
		if(*ptr >='0' && *ptr <= '9')
			ptr++;
		else 
			return false; 
	} 
	return true;

}
bool Lexical::is_string(const std::string& word) const
{
	auto ptr = word.data(); 
	auto len = word.length();

	
	if(ptr[0] == '"' && ptr[len-1] == '"')
		return true;
	else
		return false; 
}

bool Lexical::is_identifier(const std::string& word)
{
	auto ptr = word.data();

	if(word.length() > MAX_TOKEN_LEN)
	{
		err_code_ = 1;
		return false;
	}


	if(::isalpha(*ptr) || *ptr == '_')
		ptr++;

	while(*ptr != '\0')
	{
		if(::isalnum(*ptr) || *ptr == '_')
		{
			ptr++;
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
			} 
			else
				goto ERR;
			break;

		case '-':
			if(::strcmp(ptr,"-") == 0)
			{
				tokens.type = Code_Token_Type::Sub;
			}
			else
				goto ERR;
			break;

		case '*': 
			if(::strcmp(ptr,"*") == 0)
			{
				tokens.type = Code_Token_Type::Mul;
			}
			else
				goto ERR;
			break;

		case '/':
			if(::strcmp(ptr,"/") == 0)
			{ 
				tokens.type = Code_Token_Type::Div;
			}
			else
				goto ERR;
			break;

		case '%':
			if(::strcmp(ptr,"%")==0)
			{ 
				tokens.type = Code_Token_Type::Div;
			}
			else 
				goto ERR;
			break;

		case '=':

			if(::strcmp(ptr,"=") == 0)
			{
				tokens.type = Code_Token_Type::Assgin;
			}
			else if(::strcmp(ptr,"==") == 0)
			{
				tokens.type = Code_Token_Type::EQ;
			}
			else 
				goto ERR;
			break; 

		case '<':
			if(::strcmp(ptr,"<") == 0)
			{
				tokens.type = Code_Token_Type::LT;
				break;
			}
			else if(::strcmp(ptr,"<=") == 0)
			{
				tokens.type = Code_Token_Type::LE;
				break;
			}
			else 
				goto ERR;
			break;

		case '>':
			if(::strcmp(ptr,">") == 0)
			{
				tokens.type = Code_Token_Type::GT;
			}
			else if(::strcmp(ptr,">=") == 0)
			{
				tokens.type = Code_Token_Type::GE;
			} 
			else 
				goto ERR;
			break;

		case '{':
			if(::strcmp(ptr,"{") == 0)
			{
				tokens.type = Code_Token_Type::LBRACE;
			}
			else 
				goto ERR;
			break;

		case '}':
			if(::strcmp(ptr,"}") == 0)
			{
				tokens.type = Code_Token_Type::RBRACE;
			}
			else 
				goto ERR;
			break; 
		case 'w':
			if(::strcmp(ptr,"while")  == 0)
			{
				tokens.type = Code_Token_Type::While;
				break;
				
			}
		case 'i':
			if(::strcmp(ptr,"if") == 0)
			{
				tokens.type = Code_Token_Type::If;
				break;
			} 
		default:
			if(::isalpha(*ptr) || *ptr == '_')
			{
				if(is_identifier(str))
				{
					tokens.type = Code_Token_Type::Identifier;
				}
				else 
					goto ERR; 
				break;
			}
			else if(::isdigit(*ptr))
			{	
				if(is_interger(str))
				{
					tokens.type = Code_Token_Type::Integer;
				}
				else 
					goto ERR;
				break; 
			} 
			else if(*ptr == '"')
			{
				if(is_string(str))
				{
					tokens.type = Code_Token_Type::String;
				}
				else 
					goto ERR;
				break;
			}
			else
				goto ERR;
			break;
		ERR:
			err_code_ = (err_code_ == 1 ? 1 : 2);
			ADD_ERROR_LIST(err_code_,err_vec_,line_num,ptr) ; 
	}
	token_list_.push_back(tokens); 
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

	//Fix Me 
	// deal with a string with space 
	while(!isspace(**src) && (**src) != '\0')
	{
		*dest = **src;
		dest++;
		(*src)++; 
		cnt++; 
	} 
	//delete '\n'
	if(dest[cnt-1] == '\n')
		dest[cnt-1] = '\0';

	dest[cnt] = '\0';
	return cnt; 
}

struct Token* Lexical::get_token_info(int pos)
{ 
	return &(token_list_.at(pos));
}
void Lexical::parse()
{	
	auto total_line_num = source_code_file_->get_file_line_num();

	char tokens[MAX_TOKEN_LEN * 2];
	auto dest = tokens;

	for(auto i = 1 ; i <= total_line_num; i++)
	{
		auto line = source_code_file_->get_line(i-1); 
		auto src = (*line).data();
		
		::memset(tokens,'\0',sizeof(tokens)); 
		
		while(get_next_token(&src,tokens,sizeof(tokens)) > 0)
		{ 
			//skip the comment
			if(::strncmp(tokens,"//",2) == 0)
				break; 
			determin_token_type(tokens,i); 
			::memset(tokens,'\0',sizeof(tokens)); 
		} 
	}
	
	//add Eof Token to represent the end of file
	struct Token eof_token;
	eof_token.type = Code_Token_Type::Eof;
	eof_token.line_num = total_line_num; 
	eof_token.value = std::string("");
	token_list_.push_back(eof_token);



	// if there is something wrong 
	// there will show something about error information
	for(const auto& err_msg : err_vec_)
		::fprintf(stderr,"%s",err_msg.data()); 
}

size_t Lexical::get_token_num()
{
	return token_list_.size(); 
}

Lexical::~Lexical()
{ 
}
