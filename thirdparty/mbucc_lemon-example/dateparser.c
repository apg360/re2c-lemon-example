/* 
 *
 * The tok method is Copyright (c) Troy D Hanson <tdh@tkhanson.net>
 *
 * The modifications to that method and the other code is:
 * 
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

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "dategrammar.h"

struct token {
	char		*str;
	size_t	len;
	int		id; };

#define MAX_YEAR		2050

#define JAN1	"january"
#define JAN2	"jan."
#define JAN3	"jan"
#define FEB1	"february"
#define FEB2	"feb."
#define FEB3	"feb"
#define MAR1	"march"
#define MAR2	"mar."
#define MAR3	"mar"
#define APR1	"april"
#define APR2	"apr."
#define APR3	"apr"
#define MAY1	"may"
#define JUN1	"june"
#define JUN2	"jun."
#define JUN3	"jun"
#define JUL1	"july"
#define JUL2	"jul."
#define JUL3	"jul"
#define AUG1	"august"
#define AUG2	"aug."
#define AUG3	"aug"
#define SEP1	"september"
#define SEP2	"sep."
#define SEP3	"sep"
#define OCT1	"october"
#define OCT2	"oct."
#define OCT3	"oct"
#define NOV1	"november"
#define NOV2	"nov."
#define NOV3	"nov"
#define DEC1	"december"
#define DEC2	"dec."
#define DEC3	"dec"


static const char *months1[12] = { 
	JAN1,FEB1,MAR1,APR1,MAY1,JUN1,JUL1,AUG1,SEP1,OCT1,NOV1,DEC1 };

static const char *months2[12] = { 
	JAN2,FEB2,MAR2,APR2,MAY1,JUN2,JUL2,AUG2,SEP2,OCT2,NOV2,DEC2 };

static const char *months3[12] = {
	JAN3,FEB3,MAR3,APR3,MAY1,JUN3,JUL3,AUG3,SEP3,OCT3,NOV3,DEC3 };

static const struct token tokens[] = {
	{ JAN1, strlen(JAN1), TOK_MONTH },
	{ JAN2, strlen(JAN2), TOK_MONTH },
	{ JAN3, strlen(JAN3), TOK_MONTH },
	{ FEB1, strlen(FEB1), TOK_MONTH },
	{ FEB2, strlen(FEB2), TOK_MONTH },
	{ FEB3, strlen(FEB3), TOK_MONTH },
	{ MAR1, strlen(MAR1), TOK_MONTH },
	{ MAR2, strlen(MAR2), TOK_MONTH },
	{ MAR3, strlen(MAR3), TOK_MONTH },
	{ APR1, strlen(APR1), TOK_MONTH },
	{ APR2, strlen(APR2), TOK_MONTH },
	{ APR3, strlen(APR3), TOK_MONTH },
	{ MAY1, strlen(MAY1), TOK_MONTH },
	{ JUN1, strlen(JUN1), TOK_MONTH },
	{ JUN2, strlen(JUN2), TOK_MONTH },
	{ JUN3, strlen(JUN3), TOK_MONTH },
	{ JUL1, strlen(JUL1), TOK_MONTH },
	{ JUL2, strlen(JUL2), TOK_MONTH },
	{ JUL3, strlen(JUL3), TOK_MONTH },
	{ AUG1, strlen(AUG1), TOK_MONTH },
	{ AUG2, strlen(AUG2), TOK_MONTH },
	{ AUG3, strlen(AUG3), TOK_MONTH },
	{ SEP1, strlen(SEP1), TOK_MONTH },
	{ SEP2, strlen(SEP2), TOK_MONTH },
	{ SEP3, strlen(SEP3), TOK_MONTH },
	{ OCT1, strlen(OCT1), TOK_MONTH },
	{ OCT2, strlen(OCT2), TOK_MONTH },
	{ OCT3, strlen(OCT3), TOK_MONTH },
	{ NOV1, strlen(NOV1), TOK_MONTH },
	{ NOV2, strlen(NOV2), TOK_MONTH },
	{ NOV3, strlen(NOV3), TOK_MONTH },
	{ DEC1, strlen(DEC1), TOK_MONTH },
	{ DEC2, strlen(DEC2), TOK_MONTH },
	{ DEC3, strlen(DEC3), TOK_MONTH },

	{"and", 3, TOK_AND},
	{"at", 2, TOK_AT},
	
	{"a.m.", 4, TOK_AM},
	{"am", 2, TOK_AM},
	{"a", 1, TOK_AM},
	{"p.m.", 4, TOK_PM},
	{"pm", 2, TOK_PM},
	{"p", 1, TOK_PM},
	
	{"midnight", 8, TOK_MIDNIGHT},
	{"noon", 4, TOK_NOON},
	{"through", 7, TOK_TO},
	{"thru", 4, TOK_TO},
	{"to", 2, TOK_TO},
	
	{"@", 1, TOK_AT},
	{"-", 1, TOK_DASH},
	{"/", 1, TOK_SLASH},
	{",", 1, TOK_COMMA},
	{":", 1, TOK_COLON} };


static const int whitespace[256] = { 
	['\r']=1,
	['\n']=1,
	['\t']=1,
	[' ']=1 };


static const int digit[256] = { 
	['0']=1,
	['1']=1,
	['2']=1,
	['3']=1,
	['4']=1,
	['5']=1,
	['6']=1,
	['7']=1,
	['8']=1,
	['9']=1 };

#include "dategrammar.c"


// Inplace lower case.
void
lc(char **buf)
{
	char 			*p;

	p = *buf;
	for ( ; *p; ++p)
		*p = tolower(*p);
}


// Check dates for validity.
int
thisyear()
{
	char		*rval = 0;
    	time_t 	tm;
    	struct tm	*p;

	rval = calloc(5, sizeof(char));
	if (!rval)
		errx(1, "calloc failed in thisyear()");

	if (time( &tm ) == (time_t)-1)
		errx(1, "time failed in thisyear()");

	p = localtime ( &tm );
	if (!p)
		errx(1, "localtime failed in thisyear()");

	return p->tm_year + 1900;
}

int
monthnametoi(const char *monthname)
{
	const char		**a[] = {months1, months2, months3};
	char		*buf;
	int		i, j;

	buf = strdup(monthname);
	if (!buf)
		errx(1, "strdup failed");
	lc(&buf);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 12; j++) {
			if (!strcmp(buf, a[i][j])) {
				free(buf);
				return j + 1;
			}
		}

	free(buf);
	errx(1, "logic error: can't match month name '%s'", monthname);
}

int
stoi(const char *buf)
{
	char	*ep;
	int		ival;
	long	lval;
	
	errno = 0;
	lval = strtol(buf, &ep, 10);
	if (buf[0] == '\0' || *ep != '\0')
		goto not_a_number;
	if ((errno == ERANGE && (lval == LONG_MAX || lval == LONG_MIN)) ||
		(lval > INT_MAX || lval < INT_MIN))
		goto out_of_range;

	ival = lval;

	return ival;

out_of_range:
not_a_number:
	return -1;
}

void
chkdt(int month, int day, int year, struct emsg *emsg)
{	
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ( year % 400 == 0 || (year % 100 != 0 && year % 4 == 0) )
		days[1] = 29;
	
	if (!emsg->s && (month < 1 || month > 13) ) {
		emsg->s = strdup("invalid month");
		if (!emsg->s)
			errx(1, "strdup failed in chkdt");
	}

	if (!emsg->s && (day > days[month - 1] || day < 1)) {
		emsg->s = strdup("invalid day");
		if (!emsg->s)
			errx(1, "strdup failed in chkdt");
	}

	if (!emsg->s && (year < thisyear() - 2 || year > MAX_YEAR) ) {
		emsg->s = strdup("invalid year");
		if (!emsg->s)
			errx(1, "strdup failed in chkdt");
	}
}



void
chkdt1(const char *monthname, const char *day, struct emsg *emsg)
{
	chkdt(monthnametoi(monthname), stoi(day), thisyear(), emsg);
}

void
chkdt2(const char *monthname, const char *day, const char *year, struct emsg *emsg)
{
	chkdt(monthnametoi(monthname), stoi(day), stoi(year), emsg);
}

void
chkdt3(const char *monthint, const char *day, const char *year, struct emsg *emsg)
{
	chkdt(stoi(monthint), stoi(day), stoi(year), emsg);
}

void
chktm(int hour, int min, int am, struct emsg *emsg)
{
	if (!emsg->s && (hour < 0 || (am && hour > 12) || (!am && hour > 24) ) ) {
		emsg->s = strdup("invalid hour");
		if (!emsg->s)
			errx(1, "strdup failed in chktm");
	}

	if (!emsg->s && (min < 0 || min > 59) ) {
		emsg->s = strdup("invalid minute");
		if (!emsg->s)
			errx(1, "strdup failed in chktm");
	}
}

int
isam(const char *s)
{
	return s[0] == 'a';
}

void
chktm1(const char *hour, const char *min, const char* meridian, struct emsg *emsg)
{
	chktm(stoi(hour), (min ? stoi(min): 0), isam(meridian), emsg);
}


// Read next token.
int 
tok( char **c, size_t *bsz, size_t *toksz ) {
	int			i;

	/* Skip leading whitespace. */
	while( *bsz && whitespace[ (int) **c] ) {
		(*bsz)--; 
		(*c)++; 
	}
	if (*bsz == 0) 
		return 0; // end of input

	/* Identity literal keywords. */
	for ( i = 0; i < sizeof(tokens) / sizeof(*tokens); i++ ) {	
		 if (*bsz < tokens[i].len) 
			continue;
		 if (memcmp(*c, tokens[i].str, tokens[i].len) ) 
			continue;
		 *toksz = tokens[i].len;
		 return tokens[i].id;
	}

	/* Integers  */
	*toksz=0;
	if ( (*toksz < *bsz) && digit[ (int) *(*c + *toksz) ] ) {
		while ( (*toksz < *bsz) && digit[ (int) *(*c + *toksz) ] )
			(*toksz)++;
		return TOK_INT; 
	}


	return -1;

}


int
isadate(const char *s, struct emsg *emsg)
{
	void			*parser  = NULL;
	char			*buf = NULL, *p, *tokentext;
	int			token, rval;
	size_t		tokensz, bufsz;

	rval = 0;

	parser = ParseAlloc(malloc);
	if (!parser)
		errx(1, "couldn't malloc Parser");

	/* Make a copy of input string, then lower case it. */
	buf = strdup(s);
	if (buf == NULL)
		errx(1, "strdup failed");

	lc(&buf);

	bufsz = strlen(buf);
	p = buf;

	while ( (token = tok(&p, &bufsz, &tokensz)) > 0 && !emsg->s ) { 
		tokentext = strndup(p, tokensz);
		if (!tokentext)
			errx(1, "failed to strdup token");
		Parse(parser, token, tokentext, emsg);
 		bufsz -= tokensz;
		p += tokensz;
	}
	Parse(parser, 0, 0, emsg);

	if (emsg->s) {
		rval = 1;
		emsg->col = (int) (strlen(buf) - bufsz) + 1;
	}
	else if (token < 0) {
		emsg->s = strdup("invalid token");
		emsg->col = (int) (strlen(buf) - bufsz) + 1;
		rval = 1;
	}
	free(buf);
	ParseFree(parser, free);

	return rval;
}