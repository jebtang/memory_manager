all: sample interceptor

sample: sample.c
	gcc -o sample sample.c

interceptor: interceptor.cpp
	g++ -o interceptor interceptor.cpp

clean: 
	rm sample

run:
	./interceptor sample.c sample_out.c