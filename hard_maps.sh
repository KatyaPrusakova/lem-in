#!/bin/bash

test_dir="script_maps"
flow_one="$test_dir/f1"

mkdir -p $test_dir

./generator --flow-one > $flow_one

index="0"

for i in {1..10}
do
	echo run
	./lem-in < $flow_one > "$test_dir/output.txt"
	while IFS= read -r line
	do
		echo "read"
		echo $index
		index = $(($index+1))
	done
done




