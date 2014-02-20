#!/bin/sh
# Format coding style
# Depends on astyle binary

# List of options:
#	-s4	indentation = 4 spaces
#	-b	breack brackets from pre-block statement
#	-N	add extra indentation for namespaces
#	-w	indent preprosessor multiline statements
#	-p	insert space padding around operators
#	-d	insert space padding around parenthesis (outside only)
#	-Z	conserve original file's date and time modified
#	-Q	display only formatted files
#	-z2	end of line in linux style
#	-r	recursive

# Fail at first error
set -e

PATH_TO_SCRIPT=$(dirname $(readlink -f $0))
TOOLS_PATH=$(dirname $PATH_TO_SCRIPT)
ROOT_PATH=$(dirname $TOOLS_PATH)

for f in src tools
do
	for ex in cpp h
	do
		cmd="$ROOT_PATH/$f/*.$ex"
		astyle -s4 -bNwpdZQ -z2 -r "$cmd"
	done
done
 
