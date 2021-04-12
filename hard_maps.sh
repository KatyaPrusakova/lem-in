#!/bin/bash

test_dir="script_maps"
output="$test_dir/output.txt"
mkdir -p $test_dir

touch $output


function generate () {
	for i in {1..10}
	do
		echo run
		./generator --flow-$1 > $2
		./lem-in < $2 > $output
		index="0"
		while IFS= read -r line
		do
			if [[ "$line" == *"#Here is the number of"* ]]
			then
				lines_required=$(echo $line | tr -dc '0-9')
			fi
			if [[ $line == "" ]]
			then
				index=$(($index+1))
			fi
			if [[ $index -gt "0" ]]
			then
				index=$(($index+1))
			fi
		done < $output
		index=$(($index-2))
	done
}

generate "one" "map_f1"




