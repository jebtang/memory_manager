all: testT bTreeSSDT

b-treeT: b-tree.h b-tree.cpp
	g++ -o btree b-tree.cpp

testT: b-tree.h b-tree.cpp test.cpp 
	g++ -o test test.cpp b-tree.cpp 	

bTreeSSDT: b-tree.h test.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp 
	g++ -o btreeSSD test.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp

	
	
