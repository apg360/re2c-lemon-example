
%include
{
    #include <assert.h>
    #include <stdio.h>
}

%syntax_error
{
    printf("Error parsing command\n");
}

%token_type {const char*}

start ::= commandList .
{
}
commandList ::= command PIPE commandList .
{
}
commandList ::= command .
{
}

command ::= FILENAME argumentList .
{
}
command ::= FILENAME .
{
}
command ::= COMMAND_SUBSTITUTION_START commandList COMMAND_SUBSTITUTION_END .
{
}

argumentList ::= argument argumentList .
{
}
argumentList ::= argument .
{
}
argument ::= ARGUMENT .
{
}
argument ::= FILENAME .
{
}
argument ::= COMMAND_SUBSTITUTION_START commandList COMMAND_SUBSTITUTION_END .
{
}

