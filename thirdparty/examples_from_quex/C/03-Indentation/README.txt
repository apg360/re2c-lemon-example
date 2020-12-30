 An Demonstration of Indentation Based Analysis
------------------------------------------------------------------------------

An indentation based analyzer produces tokens that indicate scope implicitly:

  INDENT: When a line is more indented than its predecessor.
  DEDENT: When a line is less indented.
  NODENT: When a line has the same indentation level as the predecessor.

This directory contains two examples of lexical analyzers:

  "simple.qx" defines a lexical analyzer that enables indentation scoping 
              by the "<indentation>" tag, but does not customize it 
              further.

  "simple2.qx" demonstrates an example where 'whitespace', 'newline suppresser'
               and 'comment' are user defined.

The two resulting analyzers are './lexer' and 'lexer2'. They are run on the 
command line like
                    > ./lexer  example.txt

and
                    > ./lexer2  example2.txt

Producing a display of the analyzed data.

------------------------------------------------------------------------------
ABSOLUTELY NO WARRANTY
(C) Frank-Rene Schaefer
