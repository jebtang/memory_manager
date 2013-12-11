all: testT_create bTreeSSDT_create bTreeIntercept_create testT_traversal bTreeSSDT_traversal bTreeIntercept_traversal testT_read bTreeSSDT_read bTreeIntercept_read testT_update bTreeSSDT_update bTreeIntercept_update

testT_create: b-tree.h b-tree.cpp test_create.cpp 
	g++ -o test_create test_create.cpp b-tree.cpp 	

bTreeSSDT_create: b-tree.h test_create.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp 
	g++ -g -std=c++0x -o btreeSSD_create test_create.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp

bTreeIntercept_create: b-tree.h b-tree_intercept.cpp test_create.cpp memory_monitor.h memory_monitor2.cpp
	g++ -g -std=c++0x -o testIntercept_create test_create.cpp b-tree_intercept.cpp memory_monitor2.cpp

testT_traversal: b-tree.h b-tree.cpp test_traversal.cpp
	g++ -o test_traversal test_traversal.cpp b-tree.cpp  

bTreeSSDT_traversal: b-tree.h test_traversal.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp
	g++ -g -std=c++0x -o btreeSSD_traversal test_traversal.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp

bTreeIntercept_traversal: b-tree.h b-tree_intercept.cpp test_traversal.cpp memory_monitor.h memory_monitor2.cpp
	g++ -g -std=c++0x -o testIntercept_traversal test_traversal.cpp b-tree_intercept.cpp memory_monitor2.cpp

testT_read: b-tree.h b-tree.cpp test_read.cpp
	g++ -g -std=c++0x -o test_read test_read.cpp b-tree.cpp  

bTreeSSDT_read: b-tree.h test_read.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp
	g++ -g -std=c++0x -o btreeSSD_read test_read.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp

bTreeIntercept_read: b-tree.h b-tree_intercept.cpp test_read.cpp memory_monitor.h memory_monitor2.cpp
	g++ -g -std=c++0x -o testIntercept_read test_read.cpp b-tree_intercept.cpp memory_monitor2.cpp

testT_update: b-tree.h b-tree.cpp test_update.cpp
	g++ -g -std=c++0x -o test_update test_update.cpp b-tree.cpp  

bTreeSSDT_update: b-tree.h test_update.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp
	g++ -g -std=c++0x -o btreeSSD_update test_update.cpp b-tree_ssd.cpp ../../ssd_alloc.cpp

bTreeIntercept_update: b-tree.h b-tree_intercept.cpp test_update.cpp memory_monitor.h memory_monitor2.cpp
	g++ -g -std=c++0x -o testIntercept_update test_update.cpp b-tree_intercept.cpp memory_monitor2.cpp