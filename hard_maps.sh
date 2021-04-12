#!/bin/bash

test_dir="script_maps"
output="$test_dir/output.txt"
mkdir -p $test_dir

touch $output
index="0"


function generate () {
	for i in {1..10}
	do
		echo run
		./generator --flow-$1 > $2
		./lem-in < $2 > $output
		while IFS= read -r line
		do
			echo "read"
			if [[ "$line" == *"#Here is the number of"* ]]
			then
				lines_required=$(echo $line | tr -dc '0-9')
				echo "lines REQUIRED : $lines_required"
			fi
		done < $output
			index=$(($index+1))
	done
}

generate "one" "map_f1"




