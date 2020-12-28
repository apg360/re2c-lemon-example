%include {
#include <stdio.h>
#include <assert.h>

#include "dateparser.h"

	void
	logemsg(struct emsg *p, const char *msg)
	{
		// Keep the first error.
		if (p->s)
			return;
		p->s = strdup(msg);
		if (!p->s)
			errx(1, "strdup failed in dategrammar error handler");
	}
}


%token_type 		{ const char* }
%token_prefix 		TOK_
%extra_argument	{ struct emsg	*emsg}

%syntax_error		{ logemsg(emsg, "Invalid syntax"); }

main			::= date_expr.

date_expr		::= date_range AT times.
date_expr		::= date AT times.
date_expr		::= date.

date_range	::= date TO date.
date_range	::= date DASH date.

date			::= INT(A) date_sep INT(B) date_sep INT(C).	{ chkdt3(A, B, C, emsg); }
date			::= MONTH(A) INT(B) INT(C).				{ chkdt2(A, B, C, emsg); }
date			::= MONTH(A) INT(B) COMMA INT(C).		{ chkdt2(A, B, C, emsg); }
date			::= MONTH(A) INT(B).					{ chkdt1(A, B, emsg); }

date_sep		::= DASH.
date_sep		::= SLASH.

times		::= times AND time.
times		::= times COMMA time.
times		::= times COMMA AND time.
times		::= time.

time			::= INT(A) meridian (B).					{  chktm1(A, 0, B, emsg); }
time			::= INT(A) COLON INT(B) meridian(C).		{  chktm1(A, B, C, emsg); }
time			::= NOON.
time			::= MIDNIGHT.


meridian(A)	::= AM(B).								{ A = B; }
meridian(A)	::= PM(B).								{ A = B;  }


