```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```


## STEP1 Lexical Analysis (tokenizer, scanner)
#### Letters >>to words/token

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


## STEP2 Syntactic Analysis
#### Tokens >>to Parser tree

Tokens are organized into a hierarchical structure, a parse tree :
![parsetree](parsetree.png)


Parse tree is like figuring out what the grammar is.
Then parse tree is refined to become an Abstract Syntax Tree


## STEP3 Semantic Analysis
#### Symbol Table

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

