#!/bin/bash
echo "running cache tests:"
Object_Sizes_Array=(1000)
#5000 7500 10000 12500 15000 17500 20000 22500 25000)

Test_Name_Array=("testIntercept_create" "testIntercept_read" "testIntercept_traversal" "btreeSSD_create" "btreeSSD_read" "btreeSSD_traversal")

output_file_name=finalout.txt
temp_valgrind_file_name=valgrind_output.temp
temp_file_name=random.temp

#remove final output file if it exists
if [ -e $output_file_name ] ; then
	rm $output_file_name
fi

for test in ${Test_Name_Array[*]}
do
	for item in ${Object_Sizes_Array[*]}
	do
		valgrind --log-file=$temp_valgrind_file_name --tool=cachegrind ./$test $item

	echo 'Test Name:'$test', Object Size:'$item >> $output_file_name

	#Ignore whitespace, of which there seems to be an arbitrary amount, between the first and second word.
	((grep -e 'D\s*refs' -e 'D1\s*misses:' < $temp_valgrind_file_name) | awk '{print $4}') >> $temp_file_name

	
	line_output=""
	for i in 1 2
	do 
		read line
		line_output="$line:$line_output"
	done < $temp_file_name

	echo $line_output >> $output_file_name
	echo "" >> $output_file_name
	rm $temp_valgrind_file_name
	rm $temp_file_name
	done
done

rm cachegrind.out.*
#print the final output
cat $output_file_name
