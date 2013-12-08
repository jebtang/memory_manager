#!/bin/bash
echo "running cache tests:"
Object_Sizes_Array=(1000)
#5000 7500 10000 12500 15000 17500 20000 22500 25000)

Test_Name_Array=("testIntercept_create" "testIntercept_read" "testIntercept_traversal" "btreeSSD_create" "btreeSSD_read" "btreeSSD_traversal")

output_file_name=finalout.txt
temp_valgrind_file_name=valgrind_output.temp

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
	grep -e 'D\s*refs' -e 'D1\s*misses:' -e 'LLd misses' -e 'D1\s*miss rate:' -e 'LLd miss rate' < $temp_valgrind_file_name >> $output_file_name

	echo "" >> $output_file_name
	rm $temp_valgrind_file_name
	done
done

#print the final output
cat $output_file_name
