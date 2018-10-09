#regress.sh
#!/bin/bash

#supress pushd and popd output
pushd () {
    command pushd "$@" > /dev/null
}

popd () {
    command popd "$@" > /dev/null
}

let d_ex=0 

#check for correct arguments
if [ $# -lt 2 ] ; then
    echo "usage: regress.sh <dirname> <testfilename>"
    exit(EXIT_FAILURE);
fi


if [ -d ~/*/"$1" ] ; then
    DIRNAME=$(date +"%Y%m%d.%H%M%S")
    dirname=$1
    let d_ex=1
elif [ ! -d ~/*/"$1" ] ; then 
    DIRNAME=$1
else
    exit(EXIT_FAILURE);
fi


pushd .

mkdir ${DIRNAME}

while [ $# -gt 1 ] ; do
    shift

    if [ ! -e $1 ] ; then
				echo "usage: regress.sh <dirname> <testfilename>"
				exit(EXIT_FAILURE);
    else
				X=$1
    fi

		${X} </dev/null 1> ${DIRNAME}/${X}.stdout 2> ${DIRNAME}/${X}.stderr
		echo $? > ${DIRNAME}/${X}.status
		
		cp ${X} ${DIRNAME}/${X}.test

done

if [ $d_ex == 1 ] ; then
    if [ "$(diff -rq ~/*/${dirname} ${DIRNAME})" ] ; then
				diff -rq ~/*/"$dirname" "$DIRNAME"
				exit(exit_FAILURE);
    else
				echo "no differences"
				exit(EXIT_SUCCESS);
    fi
fi

popd
