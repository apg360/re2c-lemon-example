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

	result=$(printf "%s" "$1" | ./test_isadate)
	if [ "$result" == "$2" ] ; then
		echo " OK";
	else
		echo " FAIL"; 
		echo "	got	|${result}|"
		echo "	exp	|${2}|"
		FAILED=`expr $FAILED + 1`
	fi
}

t 	'12/25/2014'					'0: col=0 msg=(null)'
t	'Bill Russell'					'1: col=1 msg=Invalid syntax'
t	'12/25zzzabc'					'1: col=6 msg=Invalid syntax'


t 	'Jan 30 @ 10am and 3:15p'		'0: col=0 msg=(null)'
t 	'Jan 30 @ 10am, noon and 4pm'		'0: col=0 msg=(null)'
t	'Jan 30 through Feb 15 at 8pm'		'0: col=0 msg=(null)'


t	'Jan'							'1: col=4 msg=Invalid syntax'
t	'Jan 5'						'0: col=0 msg=(null)'

t	'Jan 54'						'1: col=7 msg=invalid day'

t	'Jan 5, 1804'					'1: col=12 msg=invalid year'

t	'9999/5/42'					'1: col=10 msg=invalid month'
t	'12/0/2030'					'1: col=10 msg=invalid day'
t	'12/10/99999999999999999999999999999999'	'1: col=39 msg=invalid year'

t	'Jan 1 @ 25pm'					'1: col=13 msg=invalid hour'
t	'Jan 1 @ 0am'					'0: col=0 msg=(null)'
t	'Jan 1 @ 10:15am'				'0: col=0 msg=(null)'
t	'Jan 1 @ 10:61am'				'1: col=16 msg=invalid minute'


echo ""
echo "Failed: $FAILED"
[ $FAILED -gt 0 ] && exit 1
exit 0