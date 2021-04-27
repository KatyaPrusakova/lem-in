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
	for i in {1..30}
	do
		./generator --$1 > $2
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
		lines=$(($index-$lines_required))
		if [ $index -gt $(($lines_required)) ]
		then
<<<<<<< HEAD
			cp $2 "$more/$2$(($index-$lines_required))"
=======
			echo "Difference greater than 3"
			cp $2 "$more/$2$maps_saved+$(($index-$lines_required))"
>>>>>>> fbae7e95230000d03fa383dcb79ccec5bef1cc06
			maps_saved=$(($maps_saved+1))
		fi
		if [ $index -lt $lines_required ]
		then
			cp $2 "$less/$2$(($index-$lines_required))"
			maps_saved=$(($maps_saved+1))
		fi
		printf "lines :"
		printf "%4d" $lines
		echo
	done
}

echo "Generate flow-one maps..."
generate "flow-one" "map_f1"
echo "Generate flow-ten maps..."
generate "flow-ten" "map_ften"
echo "Generate flow-thousand maps..."
generate "flow-thousand" "map_fthousand"
echo "Generate big maps..."
generate "big" "map_big"
echo "Generate big superposition maps..."
generate "big-superposition" "map_big_superpos"
echo "Done!"




