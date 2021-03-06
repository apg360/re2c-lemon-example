#pragma once

#include <assert.h>
#include <stdio.h>   // output on screen
#include <stdlib.h>  // os access: open file, read/write file, delete file etc...
#include <stddef.h>  // size_t
#include <string.h>  // strlen
#include <stdbool.h> // bool

typedef enum { FAIL, OK } Result; //typedef enum { false, true } bool; // 0, 1

char* dynamic_fgets (void);
char* substr(const char *src, int m, int n);
char** str_split(char* a_str, const char a_delim);
void removeChar(char *str, char garbage);
int removechars(char *str, size_t pos, size_t cnt);
void println(const char *str);
