#!/bin/bash

test_dir="script_maps/"
flow_one=$test_dir"f1"

mkdir -p $test_dir

./generator --flow-one > $flow_one

index="0"

for i in {1..10}
do
	./lem-in < $flow_one > $test_diroutput.txt
	while IFS= read -r line
	do
		echo $index
		index = $($index+1)
	done
done




