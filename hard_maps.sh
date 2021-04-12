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
			echo $line
			if [[ "$line" == *"#Here is the number of"* ]]
			then
				echo "FOUND IN STRING"
			fi
			index=$(($index+1))
		done < $output
	done
}

generate "one" "map_f1"




