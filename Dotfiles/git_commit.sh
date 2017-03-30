#!/bin/bash

function print_help() {
    echo "Usage:
    ./git_commit.sh directory(optional) commit_message 

Example:
    ./git_commit.sh Fix bugs to README.md
   "
} 

if ! [ -x "$(command -v git)" ]; then 
    echo "You should install git first before you can commit your project"
    exit 1
fi

if [ "$#" -ne 1 ] && [ "$#" -ne 2 ]; then
    print_help 
    exit 1
fi

add_res=$(git add -A)
if [ "$?" -ne 0 ]; then
    echo "May be your commit directory is not git directory"
    exit 1
fi 

dir=$1
msg=$2

if [ -z "$msg" ];  then 
    msg=$1
    dir=${PWD}

fi

if [ -z "$msg" ]; then 
    print_help 
    exit 1
fi

commit_res=$(git commit -m "$msg")

if ! [ "$?" -ne 0 ]; then
    echo "Successfully commit "
else
    echo "Something error"
fi
    


