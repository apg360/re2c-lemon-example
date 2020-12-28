/* 
 *  Copyright (c) June 2014 Mark Bucciarelli <mkbucc@gmail.com>. Amherst, MA.
 *  All rights reserved. 
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	char		*buf, *p;
	int		token;
	size_t	tokensz, bufsz;
	int		first;

	/* Convert stdin to a string. */
	buf = calloc( 1024, sizeof(char) );
	if (buf == NULL)
		errx(1, "Failed to allocate buf");
	fscanf(stdin, "%1023[^\n]", buf);

	lc(&buf);

	bufsz = strlen(buf);
	first = 1;
	p = buf;

	while ( (token = tok(&p, &bufsz, &tokensz )) > 0 ) { 

		if (!first)
			printf(" ");
		first = 0;
		printf("%s", tokentos(token));
 		bufsz -= tokensz;
		p += tokensz;
	}

	free(buf);

	return 0;
}