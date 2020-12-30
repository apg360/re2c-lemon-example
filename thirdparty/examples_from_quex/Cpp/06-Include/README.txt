 Including files during lexical analysis.
------------------------------------------------------------------------------

Lexical analysis may be interrupted at a particular position in the input 
stream and another input stream may be processed. Quex provides the feature
of an 'input-stack' to deal with these situations.

Include-ing may be done in the following ways:

(1) 'lexer-1': From within the reception loop

    The lexer sends a token that contains the file name to be included.
    When such a token is received an inclusion is initiated. End of stream
    pops the earlier lexer state.

(2) 'lexer-2': From inside the lexer (FASTER and MUCH easier)

    Inclusion is done upon the match of an include file name. End of stream
    pops earlier state.

 ABSOLUTELY NO WARRANTY
 (C) 2006-2018 Frank-Rene Schaefer
------------------------------------------------------------------------------
