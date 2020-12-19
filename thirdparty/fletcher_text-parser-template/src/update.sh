#!/bin/sh

# This command can be run any time to ensure that all submodules are on
# the most recent commit for the configured branch, as set up
# in the `link_git_modules` script.

# Create lexer/tokenizer
re2c -i -8 lexer.re > lexer.c


# Create parser
lemon -l parser.y
