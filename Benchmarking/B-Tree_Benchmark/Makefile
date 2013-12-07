all: testT bTreeSSDT bTreeIntercept

b-treeT: b-tree.h b-tree.cpp
	g++ -o btree b-tree.cpp

testT: b-tree.h b-tree.cpp test.cpp 
	g++ -o test test.cpp b-tree.cpp 	

bTreeSSDT: b-tree.h test.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp 
	g++ -g -std=c++0x -o btreeSSD test.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp

bTreeIntercept: b-tree.h b-tree_intercept.cpp test.cpp memory_monitor.h memory_monitor2.cpp
	g++ -g -std=c++0x -o testIntercept test.cpp b-tree_intercept.cpp memory_monitor2.cpp