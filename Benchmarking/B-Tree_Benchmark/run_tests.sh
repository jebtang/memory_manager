#!/bin/bash
echo "running tests"
Object_Sizes=(2500 5000 7500 10000 12500 15000 17500 20000 22500 25000)
Object_Sizes_Read=(10 15 20 25 30 35 200000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000 11000000)
num_iter=10
iter=1
while [ $iter -le $num_iter ]
do
object_size=2500
increment=2500
c=1
while [ $c -le 10 ]
do
#    echo ${Object_Sizes[c]}$','$(./test_create ${Object_Sizes[c]})$','$(./testIntercept_create ${Object_Sizes[c]})$','$(./btreeSSD_create ${Object_Sizes[c]}) | tee -a ./results/createFile$iter.txt 
# echo ${object_size}$','$(./test_read ${object_size})$','$(./testIntercept_read ${object_size})$','$(./btreeSSD_read ${object_size}) | tee -a ./results/readFile$iter.txt
#    echo ${object_size}$','$(./test_update ${object_size})$','$(./testIntercept_update ${object_size})$','$(./btreeSSD_update ${object_size}) | tee -a ./results/updateFile$iter.txt 
 echo ${object_size}$','$(./test_traversal ${object_sizes})$','$(./testIntercept_traversal ${object_size})$','$(./btreeSSD_traversal ${object_size}) | tee -a ./results/traversalFile$iter.txt  
# echo ${object_size}$','$(./test_traversal ${object_sizes})$','$(./testIntercept_traversal ${object_size}) | tee -a ./results/traversalFile$iter.txt 
object_size=$(($object_size+$increment)) 
    (( c++ ))
done
    (( iter++ ))
done

