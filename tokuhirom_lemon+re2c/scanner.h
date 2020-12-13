/* Generated by re2c 2.0.3 on Sun Dec 13 11:23:48 2020 */
#line 1 "scanner.re"
#ifndef CALC_SCANNER_H_
#define CALC_SCANNER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include "scanner.def.h"
#include "parser.h"

class Scanner {
private:
    // iostream sucks. very slow.
    std::istream *ifs;
 
    // buffer memory
    char* m_buffer;
    // current position
    char* m_cursor;
    char* m_limit;
    char* m_token;
    char* m_marker;
    int m_buffer_size;
    int m_lineno;
 
public:

    void increment_line_number() {
        m_lineno++;
    }

    Scanner( std::istream *ifs_, int init_size=1024 )
        : m_buffer(0)
        , m_cursor(0)
        , m_limit(0)
        , m_token(0)
        , m_marker(0)
        , m_buffer_size(init_size)
        , m_lineno(1)
    {
        m_buffer = new char[m_buffer_size];
        m_cursor = m_limit = m_token = m_marker = m_buffer;
        ifs = ifs_;
    }
 
    ~Scanner() {
        delete [] m_buffer;
    }
 
    bool fill(int n) {
 
        // is eof?
        if (ifs->eof()) {
            if ((m_limit-m_cursor) <= 0) {
                return false;
            }
        }
 
        int restSize = m_limit-m_token;
        if (restSize+n >= m_buffer_size) {
            // extend buffer
            m_buffer_size *= 2;
            char* newBuffer = new char[m_buffer_size];
            for (int i=0; i<restSize; ++i) { // memcpy
                *(newBuffer+i) = *(m_token+i);
            }
            m_cursor = newBuffer + (m_cursor-m_token);
            m_token = newBuffer;
            m_limit = newBuffer + restSize;
 
            delete [] m_buffer;
            m_buffer = newBuffer;
        } else {
            // move remained data to head.
            for (int i=0; i<restSize; ++i) { //memmove( m_buffer, m_token, (restSize)*sizeof(char) );
                *(m_buffer+i) = *(m_token+i);
            }
            m_cursor = m_buffer + (m_cursor-m_token);
            m_token = m_buffer;
            m_limit = m_buffer+restSize;
        }
 
        // fill to buffer
        int read_size = m_buffer_size - restSize;
        ifs->read( m_limit, read_size );
        m_limit += ifs->gcount();
 
        return true;
    }
 
    std::string text() {
        return std::string( m_token, m_token+length() );
    }
    int length() {
        return (m_cursor-m_token);
    }
    int lineno() {
        return m_lineno;
    }
 
    int scan(YYSTYPE& yylval) {
std:
        m_token = m_cursor;
 
    
#line 112 "<stdout>"
        {
            char yych;
            if (m_limit <= m_cursor) if (!fill(1)) { return 0; }
            yych = *m_cursor;
            switch (yych) {
            case '\t':
            case '\n':
            case '\f':
            case '\r':
            case ' ':    goto yy4;
            case '*':    goto yy6;
            case '+':    goto yy8;
            case '-':    goto yy10;
            case '/':    goto yy12;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':    goto yy14;
            default:    goto yy2;
            }
yy2:
            ++m_cursor;
#line 135 "scanner.re"
            {
            printf("unexpected character: '%c(%d)'\n", *m_token, *m_token);
            goto std;
        }
#line 145 "<stdout>"
yy4:
            ++m_cursor;
#line 132 "scanner.re"
            {
            goto std;
        }
#line 152 "<stdout>"
yy6:
            ++m_cursor;
#line 130 "scanner.re"
            { return TOKEN_MUL; }
#line 157 "<stdout>"
yy8:
            ++m_cursor;
#line 128 "scanner.re"
            { return TOKEN_ADD; }
#line 162 "<stdout>"
yy10:
            ++m_cursor;
#line 129 "scanner.re"
            { return TOKEN_SUB; }
#line 167 "<stdout>"
yy12:
            ++m_cursor;
#line 131 "scanner.re"
            { return TOKEN_DIV; }
#line 172 "<stdout>"
yy14:
            ++m_cursor;
            if (m_limit <= m_cursor) if (!fill(1)) { return 0; }
            yych = *m_cursor;
            switch (yych) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':    goto yy14;
            default:    goto yy16;
            }
yy16:
#line 124 "scanner.re"
            {
            yylval.int_value = atoi(this->text().c_str());
            return TOKEN_INT;
        }
#line 196 "<stdout>"
        }
#line 140 "scanner.re"


    }
};

#endif // CALC_SCANNER_H_
