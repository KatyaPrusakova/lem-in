#!/bin/bash

test_dir="script_maps"
output="$test_dir/output.txt"
less="$test_dir/less_than"
more="$test_dir/more_than"
maps_to_generate="10"
mkdir -p $test_dir

rm -f $more/*
rm -f $less/*

touch $output
mkdir -p $more
mkdir -p $less
maps_saved="0"

function generate () {
	for i in {1..10}
	do
		echo .
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
		if [ $index -gt $(($lines_required+3)) ]
		then
			echo "Difference greater than 3"
			cp $2 $more/$2$maps_saved
			maps_saved=$(($maps_saved+1))
		fi
		if [ $index -lt $lines_required ]
		then
			echo "Number of lines is less than required"
			cp $2 $less/$2$maps_saved
			maps_saved=$(($maps_saved+1))
		fi
	done
}

echo "Generate flow-one maps..."
generate "one" "map_f1"
echo "Generate flow-ten maps..."
generate "ten" "map_ften"
echo "Generate flow-thousand maps..."
generate "thousand" "map_fthousand"
echo "Done!"




