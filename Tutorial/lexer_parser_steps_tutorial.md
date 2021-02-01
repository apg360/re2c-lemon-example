```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```


1.Lexical Analysis (split the input up into tokens or lexical units)
2.Syntax Analysis or Parsing (Parse Tree : syntax tree of the tokens)
3.Semantic Analysis (check correctness of Parse tree/Syntax tree)
4.Intermediate Code Generation (abstract syntax tree with important nodes only)
5.Optimization (Optimize the AST by doing some operations)
6.Machine code generation (Generate Assembly code for some CPU) : use [C--](https://en.wikipedia.org/wiki/C--) instead or transpile to C



For Golang, Javascript, Typescript, C#
 -   1. input   => lexer       => tokens
 -   2. tokens  => parser      => Parse/Syntax Tree and Symbol Table
 -   3. PT & ST => semantics   => AST (abstract syntax tree)
 
For C
 -   4. AST    => transformer => output (C source code)
 
For ANTLRv4 
 -   3. AST    => transformer => Universal Ast to be used in ANTLRv4
 -   4. UAST   => ANTLRv4     => output (Golang, Javascript, Typescript, C#, Haxe, Rust)


## STEP1 Lexical Analyzer (tokenizer, scanner)
#### Letters >>to words/tokens

```javascript
int main() {
    int x;
    x = 3;
}
```

For the computer it's just a meaningless sequence of letters/characters :
```javascript
int•main()•{\n\tint•x;\n\tx•=•3;\n}\n
```

First step divides the text up into individual "tokens".
Characters/letters become words/tokens :

```diff
-   int
-   main
-   (
-   )
-   {
-   int
-   x
-   ;
-   x
-   =
-   3
-   ;
-   }
```


## STEP2 Syntax Analyzer
#### Parse/Syntax tree (syntactic structure) and Symbol Table

[Difference between parse tree and AST](https://stackoverflow.com/questions/5026517/whats-the-difference-between-parse-tree-and-ast)

Tokens are organized into a hierarchical structure, a parse tree :
![parsetree](parsetree.png)


Parse tree is like figuring out what the grammar is.
Parse tree have no representation of semantics.
Later then parse tree is refined to become an Abstract Syntax Tree


## STEP3 Semantic Analyzer
#### Parse Tree and Symbol Table >>to Abstract Syntax Tree

[Difference between parse tree and AST](https://stackoverflow.com/questions/5026517/whats-the-difference-between-parse-tree-and-ast)

AST is built from the parse tree and represents the behavior of the source code.

> The parser cannot check for semantics, example it cannot know if the WORD indicating the color actually represents a valid color.
> That is to say, it doesn’t know that it’s wrong to use “dog” and right to use “red”.
> This must be checked by the logic of the program, that can access which colors are available.
> 
> The parser should only check the syntax. So the rule of thumb is that when in doubt you let the parser pass the content up to your program.
> Then, in your program, you check the semantics and make sure that the rule actually have a proper meaning.
> 
> Abstract syntax tree traversed several times during semantic analysis.

Symbol Table is used by various phases of compiler as follows :
- Lexical Analysis: Creates new table entries in the table, example like entries about token.
- Syntax Analysis: Adds information regarding attribute type, scope, dimension, line of reference, use, etc in the table.
- Semantic Analysis: Uses available information in the table to check for semantics i.e. to verify that expressions and assignments are semantically correct(type checking) and update it accordingly.
- Intermediate Code generation: Refers symbol table for knowing how much and what type of run-time is allocated and table helps in adding temporary variable information.
- Code Optimization: Uses information present in symbol table for machine dependent optimization.
- Target Code generation: Generates code by using address information of identifier present in the table.

[Symbol Table](http://hjemmesider.diku.dk/~torbenm/Basics/basics_lulu2.pdf#page=126)

Records context about the program : variable, function names
Symbol table often implemented as a hash table.

Operatation  , Function for Symbol Table.
Allocate     , To allocate a new empty symbol table
free         , To remove all entries and free storage of symbol table
lookup       , To search for a name and return pointer to its entry
insert       , To insert a name in a symbol table and return a pointer to its entry
set_attribute, To associate an attribute with a given entry
get_attribute, To get       an attribute associated with a given entry


> * lookup() operation is used to search a name in the symbol table to determine:
>    - if the symbol exists in the table.
>    - if it is declared before it is being used.
>    - if the name is used in the scope.
>    - if the symbol is initialized.
>    - if the symbol declared multiple times.
>
> ```no-highlight
> lookup(symbol)
> This method returns 0 (zero) if the symbol does not exist in the symbol table.
> If the symbol exists in the symbol table, it returns its attributes stored in the table.

> This symbol table data structure hierarchy is stored in the semantic analyzer and whenever a name needs to be searched in a symbol table.
> It is searched using the following algorithm:
>  1.  first a symbol will be searched in the current scope, i.e. current symbol table.
>  2.  if a name is found, then search is completed, else it will be searched in the parent symbol table until,
>  3.  either the name is found or global symbol table has been searched for the name.
>  A compiler maintains two types of symbol tables: a global symbol table which can be accessed by all the procedures and scope symbol tables that are created for each scope in the program.
> ```
> For example, if a symbol table has to store information about the following variable declaration:
> ```javascript
> static int interest;
> Then it should store the entry such as : <symbol name,  type,  attribute>
> insert(interest, int, static);
> 
> int a;
> Then it should be :
> insert(a,int);
> ```


Symbol Table Example :

1) C only have two scope, global and local. Cscript only have one scope, global no matter where it is declared.

 Name or identifier | TypeMarker | TextValue | Scope
--------------------|------------|-----------|------
main                | func int   |           | global
x                   | int        | 1652      | local

2)

 Lexeme     | Token Class         | Type | Address location
------------|---------------------|------|-----------------
if          | Keyword             |      |
x           | Identifier          |      | 0x00000000 (pointer address)
<=          | Relational_operator |      |
0           | Constant            |      |
Then        | Keyword             |      |
Description | Identifier          |      | 0x00000000 (pointer address)
=           | Assignment_operator |      |
"           | Quote               |      |
Freezing    | Literal             |      |
"           | Quote               |      |
End If      | Keyword             |      |


Spot problems like :
- Undeclared variables
- Multiple declarations within the same scope
- Misuse of reserved identifiers
- Attempting to access a variable that is out of scope
- Type mismatches
- Parameter type mismatches when calling functions and procedures
- Function return value must match the specified return type
- Arithmetic operators must operate on numeric types
- The condition in an if statement must evaluate to true or false
- The exit condition of a loop must evaluate to true or false

Items stored in Symbol table:
- Variable names and constants
- Procedure and function names
- Literal constants and strings
- Compiler generated temporaries
- Labels in source languages

Information used by compiler from Symbol table:
- Data type and name
- Declaring procedures
- Offset in storage
- If structure or record then, pointer to structure table.
- For parameters, whether parameter passing by value or by reference
- Number and type of arguments passed to function
- Base Address
