#!/bin/sh
# Format coding style
# Depends on astyle binary

PATH_TO_SCRIPT=$(dirname $(readlink -f $0))
TOOLS_PATH=$(dirname $PATH_TO_SCRIPT)
ROOT_PATH=$(dirname $TOOLS_PATH)

for f in src tools
do
	cd $ROOT_PATH/$f
	for ex in cpp h
	do
		astyle -s4 -bNwpdZQ -r *.$ex
	done
done
 
