 An Demonstration of Modes, Mode Inheritance, and Mode Transitions.
------------------------------------------------------------------------------

The file "simple.qx" defines a set of modes. Some modes inherit from each
other. Some modes transit to each other. Some modes restrict entry and exit
from other modes. The handlers 'on_entry' and 'on_exit' react on mode
transitions. 

When 'make' finished its job, there is an executable './lexer'. This can 
be run like

    > ./lexer  example.txt

Producing a display of the analyzed data.

------------------------------------------------------------------------------
ABSOLUTELY NO WARRANTY
(C) Frank-Rene Schaefer
