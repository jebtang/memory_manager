all: b-treeT testT

b-treeT: b-tree.h b-tree.c
	gcc -o btree b-tree.c

testT: b-tree.h b-tree.c test.c
	gcc -o test test.c b-tree.c  	
	
	