#!/bin/sh
#
# Copyright (c) June 2014 Mark Bucciarelli <mkbucc@gmail.com>. Amherst, MA.
# All rights reserved. 
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
# testscanner.sh - check if datescanner works
#

ERROR=0 FAILED=0

t ()
{
	# $1 -> string to parse
	# $2 -> expected tokens

	printf "%s: " "$1"

	result=$(printf "%s" "$1" | ./test_tokenizer)
	if [ "$result" == "$2" ] ; then
		echo " OK";
	else
		echo " FAIL"; 
		echo "	got	|${result}|"
		echo "	exp	|${2}|"
		FAILED=`expr $FAILED + 1`
	fi
}

t 	'a.m.'					'AM'
t	'p.m.'					'PM'
t	'a'						'AM'
t	'p'						'PM'
t	'am'						'AM'
t	'pm'						'PM'

t	'Jan'			'MONTH'
t	'Feb'			'MONTH'
t	'Mar'			'MONTH'
t	'Apr'			'MONTH'
t	'May'			'MONTH'
t	'Jun'			'MONTH'
t	'Jul'			'MONTH'
t	'Aug'			'MONTH'
t	'Sep'			'MONTH'
t	'Oct'			'MONTH'
t	'Nov'			'MONTH'
t	'Dec'			'MONTH'


t 	'12/25/2014'					'INT SLASH INT SLASH INT'
t 	'Jan 30 @ 10am and 3:15p'		'MONTH INT AT INT AM AND INT COLON INT PM'
t 	'Jan 30 @ 10am, noon and 4pm'	'MONTH INT AT INT AM COMMA NOON AND INT PM'
t	'Jan 30 through Feb 15 at 8pm'		'MONTH INT TO MONTH INT AT INT PM'




echo ""
echo "Failed: $FAILED"
[ $FAILED -gt 0 ] && exit 1
exit 0