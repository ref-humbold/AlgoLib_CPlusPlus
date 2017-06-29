CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra
GTEST = -lgtest -lgtest_main -lpthread

CMPL = $(CXX) $(CXXFLAGS)

OBJ = obj
TEST = tests
ALGOLIB = algolib
GRAPHS = $(ALGOLIB)/graphs
MATHS = $(ALGOLIB)/maths
STRUCTURES = $(ALGOLIB)/structures
OBJALGOLIB = $(OBJ)/$(ALGOLIB)
OBJTEST = $(OBJ)/$(TEST)

all: algolibDir graphsDir mathsDir structuresDir

clean :
	rm -f $(OBJALGOLIB)/*.o
	rm -f $(OBJTEST)/*.o

refresh : clean all

test : testDir testBin

testall : all test

algolibDir : closest_points.o convex_hull.o kmp.o kmr.o lis.o maximum_subarray.o sorting.o two_sat.o

graphsDir : cutting.o directed_graph.o graph.o mst.o paths.o searching.o topological_sorting.o undirected_graph.o

mathsDir : maths.o prime_tests.o sieve.o

structuresDir : avl_tree.o disjoint_sets.o equation_system.o

testDir : test_kmp.o

testBin : test_kmp

closest_points.o : $(ALGOLIB)/closest_points.cpp
	$(CMPL) -c $(ALGOLIB)/closest_points.cpp -o $(OBJALGOLIB)/closest_points.o

convex_hull.o : $(ALGOLIB)/convex_hull.cpp
	$(CMPL) -c $(ALGOLIB)/convex_hull.cpp -o $(OBJALGOLIB)/convex_hull.o

kmp.o : $(ALGOLIB)/kmp.cpp
	$(CMPL) -c $(ALGOLIB)/kmp.cpp -o $(OBJALGOLIB)/kmp.o

test_kmp.o : $(TEST)/test_kmp.cpp
	$(CMPL) -c $(TEST)/test_kmp.cpp -o $(OBJTEST)/test_kmp.o

test_kmp : $(OBJALGOLIB)/kmp.o $(OBJTEST)/test_kmp.o
	$(CMPL) $(OBJALGOLIB)/kmp.o $(OBJTEST)/test_kmp.o -o $(TEST)/test_kmp $(GTEST)

kmr.o : $(ALGOLIB)/kmr.cpp
	$(CMPL) -c $(ALGOLIB)/kmr.cpp -o $(OBJALGOLIB)/kmr.o

lis.o : $(ALGOLIB)/lis.cpp
	$(CMPL) -c $(ALGOLIB)/lis.cpp -o $(OBJALGOLIB)/lis.o

maximum_subarray.o : $(ALGOLIB)/maximum_subarray.cpp
	$(CMPL) -c $(ALGOLIB)/maximum_subarray.cpp -o $(OBJALGOLIB)/maximum_subarray.o

sorting.o : $(ALGOLIB)/sorting.cpp
	$(CMPL) -c $(ALGOLIB)/sorting.cpp -o $(OBJALGOLIB)/sorting.o

two_sat.o : $(ALGOLIB)/two_sat.cpp
	$(CMPL) -c $(ALGOLIB)/two_sat.cpp -o $(OBJALGOLIB)/two_sat.o

cutting.o : $(GRAPHS)/cutting.cpp
	$(CMPL) -c $(GRAPHS)/cutting.cpp -o $(OBJALGOLIB)/cutting.o

directed_graph.o : $(GRAPHS)/directed_graph.cpp
	$(CMPL) -c $(GRAPHS)/directed_graph.cpp -o $(OBJALGOLIB)/directed_graph.o

graph.o : $(GRAPHS)/graph.cpp
	$(CMPL) -c $(GRAPHS)/graph.cpp -o $(OBJALGOLIB)/graph.o

mst.o : $(GRAPHS)/mst.cpp
	$(CMPL) -c $(GRAPHS)/mst.cpp -o $(OBJALGOLIB)/mst.o

paths.o : $(GRAPHS)/paths.cpp
	$(CMPL) -c $(GRAPHS)/paths.cpp -o $(OBJALGOLIB)/paths.o

searching.o : $(GRAPHS)/searching.cpp
	$(CMPL) -c $(GRAPHS)/searching.cpp -o $(OBJALGOLIB)/searching.o

topological_sorting.o : $(GRAPHS)/topological_sorting.cpp
	$(CMPL) -c $(GRAPHS)/topological_sorting.cpp -o $(OBJALGOLIB)/topological_sorting.o

undirected_graph.o : $(GRAPHS)/undirected_graph.cpp
	$(CMPL) -c $(GRAPHS)/undirected_graph.cpp -o $(OBJALGOLIB)/undirected_graph.o

maths.o : $(MATHS)/maths.cpp
	$(CMPL) -c $(MATHS)/maths.cpp -o $(OBJALGOLIB)/maths.o

prime_tests.o : $(MATHS)/prime_tests.cpp
	$(CMPL) -c $(MATHS)/prime_tests.cpp -o $(OBJALGOLIB)/prime_tests.o

sieve.o : $(MATHS)/sieve.cpp
	$(CMPL) -c $(MATHS)/sieve.cpp -o $(OBJALGOLIB)/sieve.o

avl_tree.o : $(STRUCTURES)/avl_tree.cpp
	$(CMPL) -c $(STRUCTURES)/avl_tree.cpp -o $(OBJALGOLIB)/avl_tree.o

disjoint_sets.o : $(STRUCTURES)/disjoint_sets.cpp
	$(CMPL) -c $(STRUCTURES)/disjoint_sets.cpp -o $(OBJALGOLIB)/disjoint_sets.o

equation_system.o : $(STRUCTURES)/equation_system.cpp
	$(CMPL) -c $(STRUCTURES)/equation_system.cpp -o $(OBJALGOLIB)/equation_system.o
