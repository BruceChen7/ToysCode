#!/bin/bash
function usage() {
    cat << END
    Usage: wc.sh [-sh][file][fold_name] 
            -s skip the file line count if you specified
            -h show this help message
            file_name count the specified file's line 
            fold_name count all file regular text file lines in the folders
END
    exit
}

function count_line() {
    file_name=$1
    eval cnt=`awk '$0 != "" { count = count + 1; }; END{print count}'  $file_name`
    echo $cnt
    return $cnt
}

function count_dir_file_line() {
    local fold=$1
    local skip_file=$2


    if ! [[ -d "$fold" ]] || [[ -z "$fold" ]]; then 
        return 0
    fi

    local file=`ls -l $fold | awk 'NR != 1 { print $9}'`
    # convert string to array
    local file_arr=($file)
    local line=0
    local length=${#file_arr[@]}
    
    [[ $length -eq 0 ]] && return 0
    local f=""
    for f in ${file_arr[@]}; do
        
        f=$fold"/"$f
    
        if [[ "$skip_file" = "$f" ]]; then
            continue
        fi
        # directory
       
        if [[ -d $f ]]; then 
            count_dir_file_line $f $skip_file
            num=$?
            line=$((line + $num))
            continue
        fi

       
        if [[ -r $f ]]; then
            line_num=`count_line $f`
            line=$((line + $line_num))
        fi
    done
    return $line
}

skip_file=
file=
fold_name=$PWD

while getopts s:h opt
do 
    case $opt in
    s) skip_file=$OPTARG ;;
    h|?) usage ;
    esac
done

shift $(( $OPTIND - 1 ))
if (( $# )); then
	path=$1
	shift
fi

(( $# )) && usage

[[ -d "$path" ]] && fold_name=`realpath $path`
[[ -f "$path" ]] && file_name=`realpath $path`



# count the specified file num
if [[ -n $file_name ]]; then 
    line=`count_line $file_name` 
    printf "the file %s you specifled has %d lines \n" $file_name, $line
    exit 0
fi

[[ $fold_name = $PWD ]] && cat << END
Scan current working directory to count file lines 
Because you specified directory or file is not existed
END


count_dir_file_line $fold_name  $skip_file
line=$?
printf "the directory %s you specified has %d lines\n" $fold_name, $line

