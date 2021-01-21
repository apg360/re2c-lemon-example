```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```

For Golang, Javascript, Typescript, C#
 -   1. input   => lexer       => tokens
 -   2. tokens  => parser      => Syntax Tree(Parse Tree) and Symbol Table
 -   3. ST & ST => semantics   => AST (abstract syntax tree)
 
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
#### Syntax tree and Symbol Table

Tokens are organized into a hierarchical structure, a parse tree :
![parsetree](parsetree.png)


Parse tree is like figuring out what the grammar is.
Then parse tree is refined to become an Abstract Syntax Tree



## STEP3 Semantic Analyzer
#### Syntax tree and Symbol Table >>to Abstract Syntax Tree

> The parser cannot check for semantics, example it cannot know if the WORD indicating the color actually represents a valid color.
> That is to say, it doesn’t know that it’s wrong to use “dog” and right to use “red”.
> This must be checked by the logic of the program, that can access which colors are available.
> 
> The parser should only check the syntax. So the rule of thumb is that when in doubt you let the parser pass the content up to your program.
> Then, in your program, you check the semantics and make sure that the rule actually have a proper meaning.
> 
> Abstract syntax tree traversed several times during semantic analysis.

Records context about the program : variable, function names
Symbol table often implemented as a hash table.

Operatation  , Function for Symbol Table.
Allocate     , To allocate a new empty symbol table
free         , To remove all entries and free storage of symbol table
lookup       , To search for a name and return pointer to its entry
insert       , To insert a name in a symbol table and return a pointer to its entry
set_attribute, To associate an attribute with a given entry
get_attribute, To get       an attribute associated with a given entry


> - lookup() operation is used to search a name in the symbol table to determine:
>    1. if the symbol exists in the table.
>    2. if it is declared before it is being used.
>    3. if the name is used in the scope.
>    4. if the symbol is initialized.
>    5. if the symbol declared multiple times.
>
> ```javascript
> lookup(symbol)
> This method returns 0 (zero) if the symbol does not exist in the symbol table. If the symbol exists in the symbol table, it returns its attributes stored in the table.
> ```


Symbol Table Example :

1)
 Name | Type     | Scope
------|----------|------
main  | func int | global
x     | int      | local

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

