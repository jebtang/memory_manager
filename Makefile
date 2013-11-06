all: sample interceptor output ssd_alloc

sample: sample.c
	gcc -o sample sample.c

interceptor: interceptor.cpp
	g++ -o interceptor interceptor.cpp

clean: 
	rm sample

output: sample_out.cpp memory_monitor.cpp 
	g++ -o profile sample_out.cpp memory_monitor.cpp 

ssd_alloc: sample_ssd_alloc.cpp ssd_alloc.cpp
	g++ -o ssd_alloc sample_ssd_alloc.cpp ssd_alloc.cpp

run_out:
	./profile

run:
	./interceptor sample.c sample_out.cpp 1