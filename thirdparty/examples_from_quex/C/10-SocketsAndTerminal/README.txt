 Lexical Analysis in Non-File Environments
------------------------------------------------------------------------------

This directory contains examples that show how lexical analyzers may be used
easily in environments where there is no file that can be directly accessed,
namely:

  * lexer-command-line, lexer-command-line-utf8:   

    A command line application that analyzes upon input from a user's command 
    line.

  * lexer-stdin, lexer-stdin-utf8:          

    Example where the input comes from the standard input as a pipe.

  * lexer-socket, lexer-socket-utf8:

    A lexical analyzer that directly listens on a socket. The program 
    'feed-socket' made by this Makefile may be used to feed the socket lexer.

 All lexer's exist in two forms: ASCII and UTF8. This is to show that the
 application may be applied with and without converters.

 ABSOLUTELY NO WARRANTY
 (C) Frank-Rene Schaefer
