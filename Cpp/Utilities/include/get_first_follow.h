#ifndef __CPLUSPLUS__Utilities__GET_FIRST_FOLLOW_H_
#define __CPLUSPLUS__Utilities__GET_FIRST_FOLLOW_H_ 
#include "STL.h"
namespace Toyscode 
{
    namespace Utilities
    {
        class Expr 
        { 
            public:
                using Pstring = std::shared_ptr<std::string>;
                using ExprVec = std::vector<Expr>;
                Expr():left_production_(""),p_right_production_(nullptr){}

                Expr(std::string left_production,std::string right_production)
                                                        :left_production_(left_production),
                                                        p_right_production_(std::make_shared<std::string>(right_production))
                {
                
                }

                Expr(const  Expr &rhs)
                {
                    left_production_ = rhs.get_left_production();
                    p_right_production_ = std::make_shared<std::string>(rhs.get_right_production());

                }

                std::string get_left_production() const
                {
                    return left_production_;
                }

                std::string get_right_production() const
                {
                    return *p_right_production_;
                }
                
            private:
                    std::string left_production_;
                    Pstring p_right_production_; 
        
        };

        //struct for follow set and first set
        struct Set
        {
            using StringVec = std::vector<std::string>;
            std::string symbol_name;
            StringVec first_or_follow_set;
        };

        class Productions 
        {

            public:
                using StringVec = std::vector<std::string>; 
                Productions() = default;
            
                Productions(Expr::ExprVec &expressions):expressions_(expressions)
                                                        ,num_of_expression_(expressions_.size()),is_first_set_filled_flag(false)
                {
                    //init the nullable_set_;
                    //which can be derived as epsilon
                    for(const auto &elem : expressions_)
                    {
                        // can be derived as epsilon
                        if(elem.get_right_production() == "")
                        {
                            nullable_set_.push_back(elem.get_left_production());
                        }
                        
                        auto left_symbol = elem.get_left_production();

                        auto begin = non_terminal_.cbegin();
                        auto end = non_terminal_.cend();

                        if(find(begin,end,left_symbol) == end)
                        {
                            non_terminal_.push_back(left_symbol);

                        }

                    
                    }
                
                }

                int get_expr_num()
                {
                    return num_of_expression_;  
                }
            
                // print all the productions    
                void print_production() const;

                // add terminals 
                void set_terminal_symbol(Productions::StringVec& terminals); 

                //show all the terminal symbol
                void show_terminal_symbol()const ;
                void show_non_terminal_symbol()const;
                void show_nullable_set()const;
                void get_nullable_set();
                void get_first_set(); 
                void get_follow_set();
                void show_first_set(const std::string& non_terminal);
                void show_first_set()const; 
                bool is_a_terminal(const std::string& sym);
                bool is_in_null_sets(const std::string& sym) const ;
                bool is_first_set_filled();


            private:
                Expr::ExprVec expressions_;
                int num_of_expression_;
                bool is_first_set_filled_flag;
                StringVec terminal_; 
                StringVec nullable_set_; 
                StringVec non_terminal_;
                std::vector<Set> first_set_;
                std::vector<Set> follow_set_; 
                void find_begin_with_spec_symbol_expr(const string &left_symbol,std::vector<int>& location);
                void add_to_first_set(const string& left_symbol,const string& terminal);
                int find_first_nullable_sym(const string&right_production) const ;
                bool determin_symbol_null(const string& left_symbol,unsigned int pos, bool is_left);
                bool is_belonged_to_first_set(const string& symbol,StringVec& set);
                int get_left_sym_pos_in_set(const string& sym) const;
                void get_follow_set_helper(const Expr& expr,Set& follow_set);
                void get_first_set_helper(const string& left_symbol,std::vector<std::string>& first_set);
        
        };

        

    }

}

#endif
