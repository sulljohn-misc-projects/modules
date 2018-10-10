#!/bin/bash
if [ $# != 1 ]; then
		echo 'usage: valgrind.sh "command arg1 ... argN"'
		exit 
fi
valgrind --leak-check=yes $1 2>&1 | grep -q "in use at exit: 0 bytes in 0 blocks"
RESVAL=$?
# decide what to print based on the result
if [ ${RESVAL} == 0 ] ; then
		echo -e "No memory leaks detected"
else
		echo -e "!!! Memory leak detected"
fi
