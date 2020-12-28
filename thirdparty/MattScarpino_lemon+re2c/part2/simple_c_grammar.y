%token_type { char* }

%include {
#include <assert.h>

typedef struct ParserCount {
  int numFunctionDefinitions;
  int numVariableDeclarations;
} ParserCount;
}

%extra_argument { ParserCount *pCount }

%parse_accept { printf("The parser has completed successfully.\n"); }

%syntax_error { fprintf(stderr, "Error\n"); }

%parse_failure { fprintf(stderr, "Parse failure\n"); }

%start_symbol program

// UNARY OPERATOR
unary_operator ::= AND.
unary_operator ::= STAR.
unary_operator ::= ADD.
unary_operator ::= SUB.
unary_operator ::= TILDE.
unary_operator ::= NOT.

// ASSIGNMENT OPERATOR
assignment_operator ::= EQ.
assignment_operator ::= MULEQ.
assignment_operator ::= DIVEQ.
assignment_operator ::= MODEQ.
assignment_operator ::= ADDEQ.
assignment_operator ::= SUBEQ.
assignment_operator ::= SLEQ.
assignment_operator ::= SREQ.
assignment_operator ::= ANDEQ.
assignment_operator ::= XOREQ.
assignment_operator ::= OREQ.

// ENUMERATOR
enumerator ::= NAME.
enumerator ::= NAME EQ constant_expression.

// ENUMERATOR LIST
enumerator_list ::= enumerator.
enumerator_list ::= enumerator_list COMMA enumerator.

// ENUM SPECIFIER
enum_specifier ::= ENUM NAME LBRACE enumerator_list RBRACE.
enum_specifier ::= ENUM LBRACE enumerator_list RBRACE.
enum_specifier ::= ENUM NAME.

// STRUCT OR UNION
struct_or_union ::= STRUCT.
struct_or_union ::= UNION.

// CONSTANT EXPRESSION
constant_expression ::= conditional_expression.

// STRUCT DECLARATOR
struct_declarator ::= declarator.
struct_declarator ::= COLON constant_expression.
struct_declarator ::= declarator COLON constant_expression.

// STRUCT DECLARATOR LIST
struct_declarator_list ::= struct_declarator.
struct_declarator_list ::= struct_declarator_list COMMA struct_declarator.

// STRUCT DECLARATION
struct_declaration ::= specifier_qualifier_list struct_declarator_list SEMICOLON.

// STRUCT DECLARATION LIST
struct_declaration_list ::= struct_declaration.
struct_declaration_list ::= struct_declaration_list struct_declaration.

// STRUCT OR UNION SPECIFIER
struct_or_union_specifier ::= struct_or_union NAME LBRACE struct_declaration_list RBRACE.
struct_or_union_specifier ::= struct_or_union LBRACE struct_declaration_list RBRACE.
struct_or_union_specifier ::= struct_or_union NAME.

// TYPE SPECIFIER
type_specifier ::= VOID.
type_specifier ::= CHAR.
type_specifier ::= SHORT.
type_specifier ::= INT.
type_specifier ::= LONG.
type_specifier ::= SIGNED.
type_specifier ::= UNSIGNED.
type_specifier ::= FLOAT.
type_specifier ::= DOUBLE.
type_specifier ::= struct_or_union_specifier.
type_specifier ::= enum_specifier.
type_specifier ::= TYPEDEF_NAME.

// TYPE QUALIFIER
type_qualifier ::= CONST.
type_qualifier ::= VOLATILE.

// TYPE QUALIFIER LIST
type_qualifier_list ::= type_qualifier.
type_qualifier_list ::= type_qualifier_list type_qualifier.

// POINTER
pointer ::= STAR type_qualifier_list.
pointer ::= STAR.
pointer ::= STAR type_qualifier_list pointer.
pointer ::= STAR pointer.

// SPECIFIER QUALIFIER LIST
specifier_qualifier_list ::= type_specifier.
specifier_qualifier_list ::= specifier_qualifier_list type_specifier.
specifier_qualifier_list ::= type_qualifier.
specifier_qualifier_list ::= specifier_qualifier_list type_qualifier.

// TYPE NAME
type_name ::= specifier_qualifier_list.
type_name ::= specifier_qualifier_list abstract_declarator.

// ARGUMENT EXPRESSION LIST
argument_expression_list ::= assignment_expression.
argument_expression_list ::= argument_expression_list COMMA assignment_expression.

// PRIMARY EXPRESSION
primary_expression ::= NAME.
primary_expression ::= INT_LITERAL.
//primary_expression ::= CHARACTER.
//primary_expression ::= FLOATING.
primary_expression ::= STRING_LITERAL.
primary_expression ::= LPAREN expression RPAREN.

// POSTFIX EXPRESSION
postfix_expression ::= primary_expression.
postfix_expression ::= postfix_expression LBRACKET expression RBRACKET.
postfix_expression ::= postfix_expression LPAREN argument_expression_list RPAREN.
postfix_expression ::= postfix_expression LPAREN RPAREN.
postfix_expression ::= postfix_expression DOT NAME.
postfix_expression ::= postfix_expression ARROW NAME.
postfix_expression ::= postfix_expression ADDADD.
postfix_expression ::= postfix_expression SUBSUB.

// UNARY EXPRESSION
unary_expression ::= postfix_expression.
unary_expression ::= ADDADD unary_expression.
unary_expression ::= SUBSUB unary_expression.
unary_expression ::= unary_operator cast_expression.
unary_expression ::= SIZEOF unary_expression.
unary_expression ::= SIZEOF LPAREN type_name RPAREN.

// CAST EXPRESSION
cast_expression ::= unary_expression.
cast_expression ::= LPAREN type_name RPAREN cast_expression.

// MULTIPLICATIVE EXPRESSION
multiplicative_expression ::= cast_expression.
multiplicative_expression ::= multiplicative_expression STAR cast_expression.
multiplicative_expression ::= multiplicative_expression DIV cast_expression.
multiplicative_expression ::= multiplicative_expression MOD cast_expression.

// ADDITIVE EXPRESSION
additive_expression ::= multiplicative_expression.
additive_expression ::= additive_expression ADD multiplicative_expression.
additive_expression ::= additive_expression SUB multiplicative_expression.

// SHIFT EXPRESSION
shift_expression ::= additive_expression.
shift_expression ::= shift_expression SL additive_expression.
shift_expression ::= shift_expression SR additive_expression.

// RELATIONAL EXPRESSION
relational_expression ::= shift_expression.
relational_expression ::= relational_expression LT shift_expression.
relational_expression ::= relational_expression GT shift_expression.
relational_expression ::= relational_expression LTEQ shift_expression.
relational_expression ::= relational_expression GTEQ shift_expression.

// EQUALITY EXPRESSION
equality_expression ::= relational_expression.
equality_expression ::= equality_expression EQEQ relational_expression.
equality_expression ::= equality_expression NOTEQ relational_expression.

// AND EXPRESSION
and_expression ::= equality_expression.
and_expression ::= and_expression AND equality_expression.

// EXCLUSIVE OR EXPRESSION
exclusive_or_expression ::= and_expression.
exclusive_or_expression ::= exclusive_or_expression XOR and_expression.

// INCLUSIVE OR EXPRESSION
inclusive_or_expression ::= exclusive_or_expression.
inclusive_or_expression ::= inclusive_or_expression OR exclusive_or_expression.

// LOGICAL AND EXPRESSION
logical_and_expression ::= inclusive_or_expression.
logical_and_expression ::= logical_and_expression ANDAND inclusive_or_expression.

// LOGICAL OR EXPRESSION
logical_or_expression ::= logical_and_expression.
logical_or_expression ::= logical_or_expression OROR logical_and_expression.

// CONDITIONAL EXPRESSION
conditional_expression ::=	logical_or_expression.
conditional_expression ::=	logical_or_expression QUESTION expression COLON conditional_expression.

// ASSIGNMENT EXPRESSION
assignment_expression ::= conditional_expression.
assignment_expression ::= unary_expression assignment_operator assignment_expression.

// EXPRESSION
expression ::= assignment_expression.
expression ::= expression COMMA assignment_expression.

// JUMP STATEMENT
jump_statement ::= GOTO NAME SEMICOLON.
jump_statement ::= CONTINUE SEMICOLON.
jump_statement ::= BREAK SEMICOLON.
jump_statement ::= RETURN SEMICOLON.
jump_statement ::= RETURN expression SEMICOLON.

// ITERATION STATEMENT
iteration_statement ::= WHILE LPAREN expression RPAREN statement.
iteration_statement ::= DO statement WHILE LPAREN expression RPAREN SEMICOLON.
iteration_statement ::= FOR LPAREN SEMICOLON SEMICOLON RPAREN statement.
iteration_statement ::= FOR LPAREN expression SEMICOLON SEMICOLON RPAREN statement.
iteration_statement ::= FOR LPAREN SEMICOLON expression SEMICOLON RPAREN statement.
iteration_statement ::= FOR LPAREN expression SEMICOLON expression SEMICOLON RPAREN statement.
iteration_statement ::= FOR LPAREN SEMICOLON SEMICOLON expression RPAREN statement.
iteration_statement ::= FOR LPAREN expression SEMICOLON SEMICOLON expression RPAREN statement.
iteration_statement ::= FOR LPAREN SEMICOLON expression SEMICOLON expression RPAREN statement.
iteration_statement ::= FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN statement.

// SELECTION STATEMENT
selection_statement ::= IF LPAREN expression RPAREN statement.
//selection_statement ::= IF LPAREN expression RPAREN statement ELSE statement.
selection_statement ::= SWITCH LPAREN expression RPAREN statement.

// EXPRESSION STATEMENT
expression_statement ::= expression SEMICOLON.
expression_statement ::= SEMICOLON.
  
// LABELED STATEMENT
labeled_statement ::= NAME COLON statement.
labeled_statement ::= CASE constant_expression COLON statement.
labeled_statement ::= DEFAULT COLON statement.

// STATEMENT
statement ::= labeled_statement.
statement ::= code_block.
statement ::= expression_statement.
statement ::= selection_statement.
statement ::= iteration_statement.
statement ::= jump_statement.

// STATEMENT LIST
statement_list ::= statement.
statement_list ::= statement_list statement.

// DECLARATION LIST
declaration_list ::= declaration.
declaration_list ::= declaration_list declaration.

// CODE BLOCK
code_block ::= LBRACE RBRACE.
code_block ::= LBRACE statement_list RBRACE.
code_block ::= LBRACE declaration_list RBRACE.
code_block ::= LBRACE declaration_list statement_list RBRACE.

// IDENTIFIER LIST
identifier_list ::= NAME.
identifier_list ::= identifier_list COMMA NAME.
  
// STORAGE CLASS SPECIFIER
storage_class_specifier ::= TYPEDEF.
storage_class_specifier ::= EXTERN.
storage_class_specifier ::= STATIC.
storage_class_specifier ::= AUTO.
storage_class_specifier ::= REGISTER.

// DECLARATION SPECIFIERS
declaration_specifiers ::= storage_class_specifier.
declaration_specifiers ::= storage_class_specifier declaration_specifiers.
declaration_specifiers ::= type_specifier.
declaration_specifiers ::= type_specifier declaration_specifiers.
declaration_specifiers ::= type_qualifier.
declaration_specifiers ::= type_qualifier declaration_specifiers.

// PARAMETER DECLARATION
parameter_declaration ::= declaration_specifiers.
parameter_declaration ::= declaration_specifiers declarator.
parameter_declaration ::= declaration_specifiers abstract_declarator.

// PARAMETER LIST
parameter_list ::= parameter_declaration.
parameter_list ::= parameter_list COMMA parameter_declaration.

// PARAMETER TYPE LIST
parameter_type_list ::= parameter_list.
parameter_type_list ::= parameter_list COMMA ELLIPSIS.

// INITIALIZER
initializer ::= assignment_expression.
initializer ::= LBRACE initializer_list RBRACE.
initializer ::= LBRACE initializer_list COMMA RBRACE.

// INITIALIZER LIST
initializer_list ::= initializer.
initializer_list ::= initializer_list COMMA initializer.

// DIRECT ABSTRACT DECLARATOR
direct_abstract_declarator ::= LPAREN abstract_declarator RPAREN.
direct_abstract_declarator ::= LBRACKET RBRACKET.
direct_abstract_declarator ::= LBRACKET constant_expression RBRACKET.
direct_abstract_declarator ::= direct_abstract_declarator LBRACKET RBRACKET.
direct_abstract_declarator ::= direct_abstract_declarator LBRACKET constant_expression RBRACKET.
direct_abstract_declarator ::= LPAREN RPAREN.
direct_abstract_declarator ::= LPAREN parameter_type_list RPAREN.
direct_abstract_declarator ::= direct_abstract_declarator LPAREN RPAREN.
direct_abstract_declarator ::= direct_abstract_declarator LPAREN parameter_type_list RPAREN.

// ABSTRACT DECLARATOR
abstract_declarator ::= pointer.
abstract_declarator ::= direct_abstract_declarator.
abstract_declarator ::= pointer direct_abstract_declarator.

// DIRECT DECLARATOR
direct_declarator(strB) ::= NAME(strA). { strB = strA; }
direct_declarator ::= LPAREN declarator RPAREN.
direct_declarator ::= direct_declarator LBRACKET constant_expression RBRACKET. 
direct_declarator ::= direct_declarator LBRACKET RBRACKET. 
direct_declarator ::= direct_declarator LPAREN parameter_type_list RPAREN. 
direct_declarator ::= direct_declarator LPAREN identifier_list RPAREN.
direct_declarator ::= direct_declarator(str) LPAREN RPAREN. { printf("The function's name is %s.\n", str); }

// DECLARATOR
declarator ::= direct_declarator.
declarator ::= pointer direct_declarator.

// INIT DECLARATOR
init_declarator ::= declarator.
init_declarator ::= declarator EQ initializer.

// INIT DECLARATOR LIST
init_declarator_list ::= init_declarator.
init_declarator_list ::= init_declarator_list COMMA init_declarator.

// DECLARATION
declaration ::= declaration_specifiers SEMICOLON.
declaration ::= declaration_specifiers init_declarator_list SEMICOLON.

// FUNCTION DEFINITION
function_definition ::= declaration_specifiers declarator declaration_list code_block.
function_definition ::= declaration_specifiers declarator code_block.
function_definition ::= declarator declaration_list code_block.
function_definition ::= declarator code_block.

// EXTERNAL DECLARATION
external_declaration ::= function_definition. { pCount->numFunctionDefinitions++; }
external_declaration ::= declaration. { pCount->numVariableDeclarations++; }

// EXTERNAL DECLARATION LIST
external_declaration_list ::= external_declaration.
external_declaration_list ::= external_declaration_list external_declaration.

// PROGRAM
program ::= external_declaration_list END_TOKEN. { printf("Constructed the program symbol.\n"); }
