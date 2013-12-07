all: sample interceptor output output2 test

sample: sample.c
	gcc -o sample sample.c

interceptor: interceptor.cpp
	g++ -o interceptor interceptor.cpp

clean: 
	rm sample

output: sample_out.cpp memory_monitor.cpp 
	g++ -g -std=c++0x -o profile sample_out.cpp memory_monitor.cpp 

ssd_alloc: sample_ssd_alloc.cpp ssd_alloc.cpp
	g++ -o ssd_alloc sample_ssd_alloc.cpp ssd_alloc.cpp

run_out:
	./profile

test_dir_ssd_alloc =./Test/SSD_Alloc/
test: ssd_alloc.cpp $(test_dir_ssd_alloc)test_create_object.cpp
	g++ -o testobj $(test_dir_ssd_alloc)test_create_object.cpp ssd_alloc.cpp

run:
	./interceptor sample.c sample_out.cpp 1
