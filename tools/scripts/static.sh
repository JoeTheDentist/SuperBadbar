#!/bin/sh
# Static analysis of the code.
# Should be cleqn for commit.
# Depends on cppcheck.

PATH_TO_SCRIPT=$(dirname $(readlink -f $0))
TOOLS_PATH=$(dirname $PATH_TO_SCRIPT)
ROOT_PATH=$(dirname $TOOLS_PATH)
LOG_DIR=$ROOT_PATH/log
LOG_FILE=$LOG_DIR/cppcheck_lastrun
#CHECKS="performance,portability,unusedFunction,missingInclude"
CHECKS="performance"

mkdir -p $LOG_DIR
cppcheck -v -j 5 --enable=$CHECKS -i $ROOT_PATH/src/soil $ROOT_PATH/src -I $ROOT_PATH/src > /dev/null | tee $LOG_FILE

