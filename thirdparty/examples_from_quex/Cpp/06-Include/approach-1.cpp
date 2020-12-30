#include<fstream>    
#include<iostream> 

#include "approach-1/Easy"
#include "approach-1/Easy-token_ids"


static void  space(size_t N);
static void  print_token(Easy* qlex, Easy_Token* token_p); 
static void  my_print(Easy* qlex, const char* Str1, 
                      const char* Str2 = 0, const char* Str3 = 0);

int 
main(int argc, char** argv) 
{        
    using namespace std;

    int         number_of_tokens = 0;
    bool        continue_lexing_f = true;
    Easy        qlex(argc == 1 ? "example-shallow.txt" : argv[1], NULL);
    Easy_Token* token_p;

    do {
        qlex.receive(&token_p);

        print_token(&qlex, token_p);

        if( token_p->id == QUEX_TKN_INCLUDE ) { 
            qlex.receive(&token_p);

            print_token(&qlex, token_p);

            if( token_p->id != QUEX_TKN_IDENTIFIER ) {
                continue_lexing_f = false;
                my_print(&qlex, "Found 'include' without a subsequent filename: '%s' hm?\n",
                         (char*)Easy_map_token_id_to_name(token_p->id));
                break;
            }
            my_print(&qlex, ">> including: ", (const char*)token_p->get_text());
            qlex.include_push_file_name((const char*)token_p->get_text(), NULL);
        }
        else if( token_p->id == QUEX_TKN_TERMINATION ) {
            space(qlex.include_depth);
            printf("Per File Letter Count = %i\n", (int)qlex.letter_count);
            if( qlex.include_pop() == false ) 
                continue_lexing_f = false;
            else {
                my_print(&qlex, "<< return from include");
            }
        }

        ++number_of_tokens;

    } while( continue_lexing_f );

    printf("| [END] number of tokens = %i\n", number_of_tokens);

    return 0;
}

static void  
space(size_t N)
{ size_t i = 0; for(i=0; i<N; ++i) printf("    "); }

static void  
print_token(Easy* qlex, Easy_Token* token_p)
{ 

    space(qlex->include_depth);
    printf("(%02i, %02i) ", (int)token_p->line_n, (int)token_p->column_n);

    switch( token_p->id ) {
    case QUEX_TKN_TERMINATION: 
        std::cout << token_p->id_name() << std::endl;
        break;
    case QUEX_TKN_NUMBER: 
        std::cout << token_p->id_name() << ": " << token_p->number << std::endl;
        break;
    default:
        std::cout << std::string(*token_p) << std::endl;
        break;
    }
}

static void 
my_print(Easy* qlex, const char* Str1, 
         const char* Str2 /* = 0x0 */, const char* Str3 /* = 0x0*/)
{
    space(qlex->include_depth);
    if( Str1 ) printf("%s", Str1);
    if( Str2 ) printf("%s", Str2);
    if( Str3 ) printf("%s", Str3);
    printf("\n");
}
