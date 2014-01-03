all: test_create test_read
OBJ = $(TARGET).o
SRC = $(TARGET).c
DEP = b-tree_intercept.c memory_monitor.c
CC = gcc
CFLAGS = -g
LDFLAGS = -nostdlib -nostartfiles -static
GLIBCDIR = /home/ravi/Desktop/project/newglibc/lib
STARTFILES = $(GLIBCDIR)/crt1.o $(GLIBCDIR)/crti.o `gcc --print-file-name=crtbegin.o`
ENDFILES = `gcc --print-file-name=crtend.o` $(GLIBCDIR)/crtn.o
LIBGROUP = -Wl,--start-group $(GLIBCDIR)/libc.a -lgcc -lgcc_eh -Wl,--end-group

test_create: test_create.o
	$(CC) $(LDFLAGS) -o $@ $(DEP) $(STARTFILES) $^ $(LIBGROUP) $(ENDFILES) 

test_read: test_read.o
	$(CC) $(LDFLAGS) -o $@ $(DEP) $(STARTFILES) $^ $(LIBGROUP) $(ENDFILES) 

test_create.o: test_create.c
	$(CC) $(CFLAGS) -c $^

test_read.o: test_read.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o *.~ $(TARGET) *~