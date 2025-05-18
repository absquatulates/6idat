#
# Makefile
#

CCC      = g++ -pipe
CCFLAGS += -std=c++17 -pedantic -Wall -g

avl_tree-test: avl_tree-test.o
	$(CCC) $(CCFLAGS) -o avl_tree-test avl_tree-test.o

test: test.o
	$(CCC) $(CCFLAGS) -o test test.o

test2: test2.o
	$(CCC) $(CCFLAGS) -o test2 test2.o

avl_tree-test.o: avl_tree-test.cpp avl_tree.cpp
	$(CCC) $(CCFLAGS) -c avl_tree-test.cpp

test.o: test.cc avl_tree.cpp
	$(CCC) $(CCFLAGS) -c test.cc

test2.o: test2.cc avl_tree.cpp
	$(CCC) $(CCFLAGS) -c test2.cc

clean:
	@ \rm -f *.o

zap: clean
	@ \rm -rf avl_tree-test *.o *~ 
