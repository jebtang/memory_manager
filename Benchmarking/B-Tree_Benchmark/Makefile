all: testT_create bTreeSSDT_create testIntercept_create testT_read bTreeSSDT_read testIntercept_read testT_update bTreeSSDT_update testIntercept_update testT_traversal bTreeSSDT_traversal testIntercept_traversal
TARGET = testT_create bTreeSSDT_create testIntercept_create testT_read bTreeSSDT_read testIntercept_read testT_update bTreeSSDT_update testIntercept_update testT_traversal bTreeSSDT_traversal testIntercept_traversal

DEP = b-tree_intercept.c
CC = gcc
CFLAGS = -g
LDFLAGS = -nostdlib -nostartfiles -static
GLIBCDIR = /home/ravi/Desktop/project/newglibc/lib
STARTFILES = $(GLIBCDIR)/crt1.o $(GLIBCDIR)/crti.o `gcc --print-file-name=crtbegin.o`
ENDFILES = `gcc --print-file-name=crtend.o` $(GLIBCDIR)/crtn.o
LIBGROUP = -Wl,--start-group $(GLIBCDIR)/libc.a -lgcc -lgcc_eh -Wl,--end-group

testIntercept_create: test_create.o
	$(CC) $(LDFLAGS) -o $@ $(DEP) $(STARTFILES) $^ $(LIBGROUP) $(ENDFILES) 

testIntercept_read: test_read.o
	$(CC) $(LDFLAGS) -o $@ $(DEP) $(STARTFILES) $^ $(LIBGROUP) $(ENDFILES) 

testIntercept_update: test_update.o
	$(CC) $(LDFLAGS) -o $@ $(DEP) $(STARTFILES) $^ $(LIBGROUP) $(ENDFILES) 

testIntercept_traversal: test_traversal.o
	$(CC) $(LDFLAGS) -o $@ $(DEP) $(STARTFILES) $^ $(LIBGROUP) $(ENDFILES) 

test_create.o: test_create.c
	$(CC) $(CFLAGS) -c $^

test_read.o: test_read.c
	$(CC) $(CFLAGS) -c $^

test_update.o: test_update.c
	$(CC) $(CFLAGS) -c $^

test_traversal.o: test_traversal.c
	$(CC) $(CFLAGS) -c $^

testT_create: b-tree.h b-tree.cpp test_create.c
	g++ -g -o test_create test_create.c b-tree.cpp         

bTreeSSDT_create: b-tree.h test_create.c b-tree_ssd.cpp ../../ssd_alloc.cpp
	g++ -g -std=c++0x -o btreeSSD_create test_create.c b-tree_ssd.cpp ../../ssd_alloc.cpp

testT_traversal: b-tree.h b-tree.cpp test_traversal.c
	g++ -g -o test_traversal test_traversal.c b-tree.cpp

bTreeSSDT_traversal: b-tree.h test_traversal.c b-tree_ssd.cpp ../../ssd_alloc.cpp
	g++ -g -std=c++0x -o btreeSSD_traversal test_traversal.c b-tree_ssd.cpp ../../ssd_alloc.cpp

testT_read: b-tree.h b-tree.cpp test_read.c
	g++ -g -std=c++0x -o test_read test_read.c b-tree.cpp

bTreeSSDT_read: b-tree.h test_read.c b-tree_ssd.cpp ../../ssd_alloc.cpp
	g++ -g -std=c++0x -o btreeSSD_read test_read.c b-tree_ssd.cpp ../../ssd_alloc.cpp

testT_update: b-tree.h b-tree.cpp test_update.cpp
	g++ -g -std=c++0x -o test_update test_update.cpp b-tree.cpp

bTreeSSDT_update: b-tree.h test_update.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp
	g++ -g -std=c++0x -o btreeSSD_update test_update.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp

clean:
	rm -f *.o *.~ $(TARGET) *~ 