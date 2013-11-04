all: sample interceptor

sample: sample.c
	gcc -o sample sample.c

interceptor: interceptor.cpp
	g++ -o interceptor interceptor.cpp

clean: 
	rm sample

run:
	./interceptor sample1.c sample_out.cpp 0