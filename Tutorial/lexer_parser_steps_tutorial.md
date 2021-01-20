```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```

For Golang, Javascript, Typescript, C#
 -   1. input   => lexer       => tokens
 -   2. tokens  => parser      => Syntax Tree and Symbol Table
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

Records context about the program : variable, function names
Symbol table often implemented as a hash table.

 Name | Type     | Scope
------|----------|------
main  | func int | global
x     | int      | local

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

Abstract syntax tree traversed several times during semantic analysis.
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

