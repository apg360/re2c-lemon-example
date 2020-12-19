/*

	main.c -- Template main()

	Copyright © 2015-2016 Fletcher T. Penney.


	This program is free software you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation either version 2 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "d_string.h"
#include "lexer.h"
#include "token.h"

#define kBUFFERSIZE 4096	// How many bytes to read at a time

// Base parser function declarations
#include "parser.h"

void *ParseAlloc();
void Parse();
void ParseFree();
void ParseTrace();


DString * stdin_buffer() {
	/* Read from stdin and return a GString *
		`buffer` will need to be freed elsewhere */

	char chunk[kBUFFERSIZE];
	size_t bytes;

	DString * buffer = d_string_new("");

	while ((bytes = fread(chunk, 1, kBUFFERSIZE, stdin)) > 0) {
		d_string_append_c_array(buffer, chunk, bytes);
	}

	fclose(stdin);

	return buffer;
}


DString * scan_file(char * fname) {
	/* Read from a file and return a GString *
		`buffer` will need to be freed elsewhere */

	char chunk[kBUFFERSIZE];
	size_t bytes;

	FILE * file;

	if ((file = fopen(fname, "r")) == NULL ) {
		return NULL;
	}

	DString * buffer = d_string_new("");

	while ((bytes = fread(chunk, 1, kBUFFERSIZE, file)) > 0) {
		d_string_append_c_array(buffer, chunk, bytes);
	}

	fclose(file);

	return buffer;
}


int main(int argc, char** argv) {
	DString * buffer = NULL;

	if (argc > 1) {
		// Read file into buffer
		buffer = scan_file(argv[1]);
	} else {
		// Default string if no file to parse
		buffer = d_string_new("foo-ball:bar bat\n a : b \n\tc     :\td\n");

		// Read from stdin into buffer
		// buffer = stdin_buffer();
	}

	if (buffer == NULL) {
		fprintf(stderr, "Error reading input.\n");
		exit(0);
	}

	// Create a parser (for lemon)
	void* pParser = ParseAlloc (malloc);

#ifndef NDEBUG
	ParseTrace(stderr, "parse:");
#endif

	// Create a scanner (for re2c)
	Scanner s;
	s.start = buffer->str;
	s.cur = s.start;

	// Where do we stop parsing?
	char * stop = buffer->str + buffer->currentStringLength;

	int type;				// TOKEN type
	token * t;				// Create tokens for incorporation

	token * root;			// Store the final parse tree here

	const char * last_stop = buffer->str;	// Remember where last token ended

	do {
		// Scan for next token (type of 0 means there is nothing left);
		type = scan(&s, stop);

		if (type && s.start != last_stop) {
			// We skipped characters (and type != 0)

			// Create a default token for the skipped characters
			t = token_new(TEXT_PLAIN, (size_t)(last_stop - buffer->str), (size_t)(s.start - last_stop), NULL);
			// fprintf(stderr, "token %d (%lu:%lu)\n", t->type,  t->start, t->len);

			// Send token to lemon for parsing
#ifndef NDEBUG
			token_describe(t, buffer->str);
#endif
			Parse(pParser, TEXT_PLAIN, t, &root);
		}

		switch (type) {
			case TEXT_PLAIN:
				// Create token and parse it -- these will be incorporated into the final token tree
				t = token_new(type, (size_t)(s.start - buffer->str), (size_t)(s.cur - s.start), NULL);
				// fprintf(stderr, "token %d (%lu:%lu)\n", t->type,  t->start, t->len);
				break;
			default:
				// No tokens needed by parser for these types -- only interested in the text values for the final tree
#ifndef NDEBUG
				fprintf(stderr, "* (%d) %lu:%lu\n", type, s.start - buffer->str, s.cur - s.start);
#endif
				t = NULL;
				// fprintf(stderr, "token %d (%lu:%lu)\n", type, (size_t)(s.start - buffer->str), (size_t)(s.cur - s.start));
				break;
		}

		// Send token to lemon for parsing
#ifndef NDEBUG
		token_describe(t, buffer->str);
#endif

		Parse(pParser, type, t, &root);

		// Remember where we left off to detect skipped characters
		last_stop = s.cur;
	} while (type != 0);	// 0 means we have finished with the input

	if (root == NULL) {
		fprintf(stderr, "No result.\n");
	} else {
		token_tree_describe(root, buffer->str);
	}

	// Clean up
	ParseFree(pParser, free);
	d_string_free(buffer, true);
	token_tree_free(root);
}
