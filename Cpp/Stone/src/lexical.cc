#include <Stone/src/lexical.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <iostream>
#define kBufferSize (64)
using namespace Stone;

//global variables;
const char * g_err_buf[32] = {
    "All is well",
    "The Token Is Too Long",
    "I Do Not know What The Symbol Is,May Be,You Should Use Blank Character To Separate Them"
}; 


char g_status[1024];

File::File(const char* file_name):line_num_(0)
{ 
    buffer_.reserve(kBufferSize);
    
    //user-defined deleter
    auto close_file = [](FILE *fp) { 
        ::fclose(fp); 
    };

           
    fp_ = std::shared_ptr<FILE>(::fopen(file_name,"r"),close_file);

    if(fp_.get() == nullptr)
    { 
        ::fprintf(stderr,"can't open the source code for read\n");
        exit(0); 
    } 
}

void File::read2buffer()
{

    assert(fp_ != nullptr); 
    //a buffer to store source code per line 
    char buffer[1024]; 

    while(::fgets(buffer,sizeof(buffer)-1,fp_.get()))
    { 
        auto tokens_per_line = std::string(buffer);
        buffer_.push_back(tokens_per_line); 
        line_num_++;
    } 
}

int File::get_file_line_num() const 
{
    return line_num_;
}


std::string* File::get_line(int pos)
{ 
    if(pos < buffer_.size()) 
        return &buffer_[pos];
    else 
        return nullptr;
}



Lexical::Lexical(const char *file_name):source_code_file_(std::unique_ptr<File>(new File(file_name))),err_code_(0) 
{ 
    source_code_file_->read2buffer(); 
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

    
    if(len != 1 && ptr[0] == '"' && ptr[len-1] == '"')
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
                tokens.type  =  Code_Token_Type::Add;
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
                tokens.type = Code_Token_Type::Mod;
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
        case '(':
            if(::strcmp(ptr,"(") == 0)
            {
                tokens.type = Code_Token_Type::LBrackets;
            }
            break;
        case ')':
            if(::strcmp(ptr,")") == 0)
            {
                tokens.type = Code_Token_Type::RBrackets;
            }
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
                break;
            }
            else if(::strcmp(ptr,">=") == 0)
            {
                tokens.type = Code_Token_Type::GE;
                break;
            } 
            else 
                goto ERR;
            break;

        case '{':
            if(::strcmp(ptr,"{") == 0)
            {
                tokens.type = Code_Token_Type::LBRACE;
                break;
            }
            else 
                goto ERR;
            break;

        case '}':
            if(::strcmp(ptr,"}") == 0)
            {
                tokens.type = Code_Token_Type::RBRACE;
                break;
            }
            else 
                goto ERR;
            break; 
        case 'w':
            if(::strcmp(ptr,"while")== 0)
            {
                tokens.type = Code_Token_Type::While;
                break; 
            }
            else 
            {
                if(is_identifier(str))
                {
                    tokens.type = Code_Token_Type::Identifier;
                }
                else 
                    goto ERR; 
                break;
            } 
        case 'i':
            if(::strcmp(ptr,"if") == 0)
            {
                tokens.type = Code_Token_Type::If;
                break;
            } 
            else 
            {
                if(is_identifier(str))
                {
                    tokens.type = Code_Token_Type::Identifier;
                }
                else 
                    goto ERR; 
                break;
            }
        case ';':
            tokens.type = Code_Token_Type::Semicolon;
            break;

        default:
            if(::isalpha(*ptr) || *ptr == '_')
            {

                if(is_identifier(str))
                {
                    // fprintf(stderr,"%s\n",ptr);
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

//which is used by get_next_token
void Lexical::creat_char_string(char ch,char *dest)
{
    dest[0] = ch;
    dest[1] = '\0'; 
}

//Be careful: the (*src) has been changed
//(*src) point to next token in the next turn  which will be get
int Lexical::get_a_string(const char **src,char *dest)
{
    //**ptr begin with "
    assert(**src=='"');

     const char  *ptr = (*src)+1;

    //find the next '"'
    while(*ptr != '\n')
    {
        if(*ptr == '"')
            break;
        else 
            ptr++; 
    }

    if(*ptr != '\n')
    {
        auto len = ptr-(*src)+1;
        ::memcpy(dest,(*src),len);
        dest[len] = '\0';
        *src  =  ptr+1;
        return len;
    }
    else 
    {
        creat_char_string('"',dest);
        (*src)++;
        return 1;
    }

}

//FixMe:: refactor the code 
//and add Minus parsing
int Lexical::get_next_token(const char **src, char *dest,int token_length)
{
    assert(dest != nullptr);
    assert(token_length > MAX_TOKEN_LEN);
    
    if(**src == '\n')
        return 0;

    while(isspace(**src))
        (*src)++;

    switch(**src)
    {
        //deal with a Semicolon
        case ';':
            creat_char_string(';',dest);
            (*src)++;
            return 1;
        //deal with a left bracket
        case '(':
            creat_char_string('(',dest);
            (*src)++;
            return 1;
        //deal with a right bracket
        case ')' :
            creat_char_string(')',dest);
            (*src)++;
            return 1;
        case '"': 
            return get_a_string(src,dest); 

        default:
            break;
    }
                

    // deal with a  string with space 
    auto cnt = 0;

    while(!isspace(**src) && (**src) != '\0' && (**src) != ';')
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

//return a pointer to the token
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
        add_eol_to_tail(i); 
    }
    
    //add Eof Token to represent the end of file
    add_eof_to_tail();

    // if there is something wrong 
    // there will show something about error information
    for(const auto& err_msg : err_vec_)
        ::fprintf(stderr,"%s",err_msg.data()); 
}

void Lexical::add_eol_to_tail(int line_num)
{
    struct Token eol_token;
    eol_token.type = Code_Token_Type::Eol;
    eol_token.value = std::string("eol");
    eol_token.line_num =  line_num;
    token_list_.push_back(eol_token);
}

void Lexical::add_eof_to_tail()
{
    auto total_line_num = source_code_file_->get_file_line_num();

    struct Token eof_token;
    eof_token.type = Code_Token_Type::Eof;
    eof_token.line_num = total_line_num; 
    eof_token.value = std::string("eof");
    token_list_.push_back(eof_token); 
}

size_t Lexical::get_token_num()
{
    return token_list_.size(); 
}

Lexical::~Lexical()
{


}
