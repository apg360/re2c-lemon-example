/**

	Parser-Template -- Boilerplate parser example using re2c lexer and lemon parser.

	@file token.c

	@brief Structure and functions to manage tokens representing portions of a
	text string.


	@author	Fletcher T. Penney
	@bug	

**/

/*

	Copyright © 2016 Fletcher T. Penney.


	The `c-template` project is released under the MIT License.
	
	GLibFacade.c and GLibFacade.h are from the MultiMarkdown v4 project:
	
		https://github.com/fletcher/MultiMarkdown-4/
	
	MMD 4 is released under both the MIT License and GPL.
	
	
	CuTest is released under the zlib/libpng license. See CuTest.c for the text
	of the license.
	
	
	## The MIT License ##
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

*/

#include <stdio.h>
#include <stdlib.h>

#include "token.h"


/// Get pointer to a new token
token * token_new(unsigned short type, size_t start, size_t len, token * prev) {
	token * t = malloc(sizeof(token));

	t->type = type;
	t->start = start;
	t->len = len;

	t->next = NULL;
	t->prev = prev;
	t->child = NULL;

	t->tail = t;

	return t;
}


/// Create a parent for a chain of tokens
token * token_new_parent(token * child, unsigned short type, token * prev) {
	token * t = token_new(type, child->start, 0, prev);
	t->child = child;
	child->prev = NULL;

	// Ensure that parent length correctly includes children
	if (child == NULL) {
		t->len = 0;
	} else if (child->next == NULL) {
		t->len = child->len;
	} else {
		while (child->next != NULL)
			child = child->next;

		t->len = child->start + child->len - t->start;
	}

	return t;
}


/// Add a new token to the end of a token chain.  The new token
/// may or may not also be the start of a chain
void token_chain_append(token * chain_start, token * t) {
	if (chain_start == NULL)
		return;

	// Append t
	chain_start->tail->next = t;
	t->prev = chain_start->tail;

	// Adjust tail marker
	chain_start->tail = t->tail;
}


/// Add a new token to the end of a parent's child
/// token chain.  The new token may or may not be
/// the start of a chain.
void token_append_child(token * parent, token * t) {
	if (parent == NULL)
		return;

	if (parent->child == NULL) {
		// Parent has no children
		parent->child = t;
	} else {
		// Append to to existing child chain
		token_chain_append(parent->child, t);
	}
}


/// Free token
void token_free(token * t) {
	if (t == NULL)
		return;

	token_tree_free(t->child);

	free(t);
}


/// Free token chain
void token_tree_free(token * t) {
	token * n;

	while (t != NULL) {
		n = t->next;
		token_free(t);

		t = n;
	}
}


/// Forward declaration
void print_token_tree(token * t, unsigned short depth, const char * string);


/// Print contents of the token based on specified string
void print_token(token * t, unsigned short depth, const char * string) {
	if (t != NULL) {
		for (int i = 0; i < depth; ++i)
		{
			fprintf(stderr, "\t");
		}
		if (string == NULL) {
			fprintf(stderr, "* (%d) %lu:%lu\n", t->type, t->start, t->len);
		} else {
			fprintf(stderr, "* (%d) %lu:%lu\t'%.*s'\n", t->type, t->start, t->len, (int)t->len, &string[t->start]);
		}

		if (t->child != NULL)
			print_token_tree(t->child, depth + 1, string);
	}
}


/// Print contents of the token tree based on specified string
void print_token_tree(token * t, unsigned short depth, const char * string) {
	while (t != NULL) {
		print_token(t, depth, string);

		t = t->next;
	}
}


/// Print a description of the token based on specified string
void token_describe(token * t, const char * string) {
	print_token(t, 0, string);
}



/// Print a description of the token tree based on specified string
void token_tree_describe(token * t, char * string) {
	fprintf(stderr, "=====>\n");
	while (t != NULL) {
		print_token(t, 0, string);

		t = t->next;
	}
	fprintf(stderr, "<=====\n");
}

