/*Configurations section*/
%{
    #include "shellparser.hpp"
%}

%option reentrant
%option noyywrap

/* Define the two states
  one state for quoted parameters + one state for double quoted parameters 
Other shells behave differently when presented with single-quoted versus double-quoted parameters (e.g. double-quoted parameters honor escaping, but single-quoted parameters don’t)
*/
%x SINGLE_QUOTED
%x DOUBLE_QUOTED

%% /* SECTION END, now start Rules section */

"|"                     {return PIPE;}/* If we see the pipe character, we return the PIPE token */
"$("                    {return COMMAND_SUBSTITUTION_START;}
")"                     {return COMMAND_SUBSTITUTION_END;}
[ \t\r\n]               {} /* ignore any whitespace that shows up in our command line */
[a-zA-Z0-9\-\._/]+      {return FILENAME;} /* UNIX shell commands character = alphanumeric characters and underscores, periods, and dashes.
                                                Note that we had to escape the period and the dash, as both have special meanings in regular expressions. */

[']                     {BEGIN(SINGLE_QUOTED);} /* next rules will handle quoted arguments. To start, we enter the QUOTED state any time we encounter a single quote character. */
<SINGLE_QUOTED>[^']+    {} /* Once we’re in the SINGLE_QUOTED state, we want to ignore keep reading characters until we hit the closing quote, at which point we are can go back to the normal INITIAL scanning state. */
<SINGLE_QUOTED>[']      {BEGIN(INITIAL); return ARGUMENT;}
<SINGLE_QUOTED><<EOF>>  {return -1;} /* One final note is that if we start quoting an argument but never find the closing quote, we need to signal an error. */

["]                     {BEGIN(DOUBLE_QUOTED);} /* double quoted arguments will be similar */
<DOUBLE_QUOTED>[^"]     {}
<DOUBLE_QUOTED>["]      {BEGIN(INITIAL); return ARGUMENT;}
<DOUBLE_QUOTED><<EOF>>  {return -1;}

[^ \t\r\n|'"]+          {return ARGUMENT;} /*  we just want to match any string consisting of not whitespace and quotes.
                                                such as --color=auto 
                                                The only thing we have left to match is other arguments */

.           {return -1;} /* Flex is smart enough to recognize if a rule can’t be matched and will print a warning, so you can test that everything is being matched by adding this rule at the end: */

%%

