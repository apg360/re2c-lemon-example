/* Generated by re2c 2.0.3 on Sun Dec 20 14:49:24 2020 */
#pragma once

#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>

//#include <vector>
//#include <sstream>
//#include <iostream>
//#include <cstdlib>
//#include <cassert>

typedef union {
    int int_value;
} YYSTYPE;

struct ParserState {
    int result;
    ParserState() :result(0) {
    }
};

#include "parser.h"

//private
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
 
//public

    void increment_line_number() {
        m_lineno++;
    }

    void SCANNER_INIT( std::istream *ifs_, int init_size=1024 ){
        m_buffer=0;
        m_cursor=0;
        m_limit=0;
        m_token=0;
        m_marker=0;
        m_buffer_size = init_size;
        m_lineno=1;
        
        m_buffer = new char[m_buffer_size];
        m_cursor = m_limit = m_token = m_marker = m_buffer;
        ifs = ifs_;
    }
 
    void SCANNER_DELETE() {
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
 
    int length() {
        return (m_cursor-m_token);
    }
    std::string text() {
        return std::string( m_token, m_token+length() );
    }
    int lineno() {
        return m_lineno;
    }
 
    int SCAN(YYSTYPE& yylval) {
std:
        m_token = m_cursor;
 
    
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
            {
            printf("unexpected character: '%c(%d)'\n", *m_token, *m_token);
            goto std;
        }
yy4:
            ++m_cursor;
            {
            goto std;
        }
yy6:
            ++m_cursor;
            { return TOKEN_MUL; }
yy8:
            ++m_cursor;
            { return TOKEN_ADD; }
yy10:
            ++m_cursor;
            { return TOKEN_SUB; }
yy12:
            ++m_cursor;
            { return TOKEN_DIV; }
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
            {
            yylval.int_value = atoi(text().c_str());
            return TOKEN_INT;
        }
        }


    }

