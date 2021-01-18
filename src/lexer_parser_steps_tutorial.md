```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```


## Lexical Analysis

int main() {
    int x;
    x = 3;
}

For the computer it's just a meaningless sequence of letters/characters :
int•main()•{\n\tint•x;\n\tx•=•3;\n}\n

First step divides the text up into individual "tokens".
Characters/letters become tokens/words :

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



