CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra
GTEST = -lgtest -lgtest_main -lpthread
CMPL = $(CXX) $(CXXFLAGS)
SRC = src
OBJ = build
TEST = test
ALGOLIB = $(SRC)/algolib
GRAPHS = $(ALGOLIB)/graphs
MATHS = $(ALGOLIB)/maths
STRUCTURES = $(ALGOLIB)/structures
OBJSRC = $(OBJ)/$(SRC)
OBJTEST = $(OBJ)/$(TEST)

all : prepare srcDir testDir

source : prepare srcDir

tests : prepare testDir

prepare :
	mkdir -p $(OBJSRC)
	mkdir -p $(OBJTEST)

clean :
	rm -rf $(OBJ)

refresh : clean all

refreshtest : clean alltest

testDir : avl_tree_test directed_graph_test disjoint_sets_test kmp_test maths_test maximum_subarray_test mst_test sieve_test topological_sorting_test undirected_graph_test

srcDir: algolibDir graphsDir mathsDir structuresDir

algolibDir : closest_points.o convex_hull.o kmp.o kmr.o lis.o maximum_subarray.o sorting.o two_sat.o

graphsDir : cutting.o directed_graph.o graph.o mst.o paths.o searching.o topological_sorting.o undirected_graph.o

mathsDir : maths.o prime_checking.o sieve.o

structuresDir : avl_tree.o disjoint_sets.o equation_system.o


closest_points.o : $(ALGOLIB)/closest_points.cpp
	$(CMPL) -c $(ALGOLIB)/closest_points.cpp -o $(OBJSRC)/closest_points.o


convex_hull.o : $(ALGOLIB)/convex_hull.cpp
	$(CMPL) -c $(ALGOLIB)/convex_hull.cpp -o $(OBJSRC)/convex_hull.o


kmp.o : $(ALGOLIB)/kmp.cpp
	$(CMPL) -c $(ALGOLIB)/kmp.cpp -o $(OBJSRC)/kmp.o

kmp_test.o : $(TEST)/kmp_test.cpp
	$(CMPL) -c $(TEST)/kmp_test.cpp -o $(OBJTEST)/kmp_test.o

kmp_test : kmp.o kmp_test.o
	$(CMPL) $(OBJSRC)/kmp.o $(OBJTEST)/kmp_test.o -o $(TEST)/kmp_test $(GTEST)


kmr.o : $(ALGOLIB)/kmr.cpp
	$(CMPL) -c $(ALGOLIB)/kmr.cpp -o $(OBJSRC)/kmr.o


lis.o : $(ALGOLIB)/lis.cpp
	$(CMPL) -c $(ALGOLIB)/lis.cpp -o $(OBJSRC)/lis.o


maximum_subarray.o : $(ALGOLIB)/maximum_subarray.cpp
	$(CMPL) -c $(ALGOLIB)/maximum_subarray.cpp -o $(OBJSRC)/maximum_subarray.o

maximum_subarray_test.o : $(TEST)/maximum_subarray_test.cpp
	$(CMPL) -c $(TEST)/maximum_subarray_test.cpp -o $(OBJTEST)/maximum_subarray_test.o

maximum_subarray_test : maximum_subarray.o maximum_subarray_test.o
	$(CMPL) $(OBJSRC)/maximum_subarray.o $(OBJTEST)/maximum_subarray_test.o -o $(TEST)/maximum_subarray_test $(GTEST)


sorting.o : $(ALGOLIB)/sorting.cpp
	$(CMPL) -c $(ALGOLIB)/sorting.cpp -o $(OBJSRC)/sorting.o


two_sat.o : $(ALGOLIB)/two_sat.cpp
	$(CMPL) -c $(ALGOLIB)/two_sat.cpp -o $(OBJSRC)/two_sat.o


cutting.o : $(GRAPHS)/cutting.cpp
	$(CMPL) -c $(GRAPHS)/cutting.cpp -o $(OBJSRC)/cutting.o


directed_graph.o : $(GRAPHS)/directed_graph.cpp
	$(CMPL) -c $(GRAPHS)/directed_graph.cpp -o $(OBJSRC)/directed_graph.o

directed_graph_test.o : $(TEST)/directed_graph_test.cpp
	$(CMPL) -c $(TEST)/directed_graph_test.cpp -o $(OBJTEST)/directed_graph_test.o

directed_graph_test : graph.o directed_graph.o directed_graph_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJTEST)/directed_graph_test.o -o $(TEST)/directed_graph_test $(GTEST)


graph.o : $(GRAPHS)/graph.cpp
	$(CMPL) -c $(GRAPHS)/graph.cpp -o $(OBJSRC)/graph.o


mst.o : $(GRAPHS)/mst.cpp
	$(CMPL) -c $(GRAPHS)/mst.cpp -o $(OBJSRC)/mst.o

mst_test.o : $(TEST)/mst_test.cpp
	$(CMPL) -c $(TEST)/mst_test.cpp -o $(OBJTEST)/mst_test.o

mst_test : graph.o directed_graph.o undirected_graph.o disjoint_sets.o mst.o mst_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/undirected_graph.o $(OBJSRC)/disjoint_sets.o $(OBJSRC)/mst.o $(OBJTEST)/mst_test.o -o $(TEST)/mst_test $(GTEST)


paths.o : $(GRAPHS)/paths.cpp
	$(CMPL) -c $(GRAPHS)/paths.cpp -o $(OBJSRC)/paths.o


searching.o : $(GRAPHS)/searching.cpp
	$(CMPL) -c $(GRAPHS)/searching.cpp -o $(OBJSRC)/searching.o


topological_sorting.o : $(GRAPHS)/topological_sorting.cpp
	$(CMPL) -c $(GRAPHS)/topological_sorting.cpp -o $(OBJSRC)/topological_sorting.o

topological_sorting_test.o : $(TEST)/topological_sorting_test.cpp
	$(CMPL) -c $(TEST)/topological_sorting_test.cpp -o $(OBJTEST)/topological_sorting_test.o

topological_sorting_test : graph.o directed_graph.o topological_sorting.o topological_sorting_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/topological_sorting.o $(OBJTEST)/topological_sorting_test.o -o $(TEST)/topological_sorting_test $(GTEST)


undirected_graph.o : $(GRAPHS)/undirected_graph.cpp
	$(CMPL) -c $(GRAPHS)/undirected_graph.cpp -o $(OBJSRC)/undirected_graph.o

undirected_graph_test.o : $(TEST)/undirected_graph_test.cpp
	$(CMPL) -c $(TEST)/undirected_graph_test.cpp -o $(OBJTEST)/undirected_graph_test.o

undirected_graph_test : graph.o directed_graph.o undirected_graph.o undirected_graph_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/undirected_graph.o $(OBJTEST)/undirected_graph_test.o -o $(TEST)/undirected_graph_test $(GTEST)


maths.o : $(MATHS)/maths.cpp
	$(CMPL) -c $(MATHS)/maths.cpp -o $(OBJSRC)/maths.o

maths_test.o : $(TEST)/maths_test.cpp
	$(CMPL) -c $(TEST)/maths_test.cpp -o $(OBJTEST)/maths_test.o

maths_test : maths.o maths_test.o
	$(CMPL) $(OBJSRC)/maths.o $(OBJTEST)/maths_test.o -o $(TEST)/maths_test $(GTEST)


prime_checking.o : $(MATHS)/prime_checking.cpp
	$(CMPL) -c $(MATHS)/prime_checking.cpp -o $(OBJSRC)/prime_checking.o


sieve.o : $(MATHS)/sieve.cpp
	$(CMPL) -c $(MATHS)/sieve.cpp -o $(OBJSRC)/sieve.o

sieve_test.o : $(TEST)/sieve_test.cpp
	$(CMPL) -c $(TEST)/sieve_test.cpp -o $(OBJTEST)/sieve_test.o

sieve_test : sieve.o sieve_test.o
	$(CMPL) $(OBJSRC)/sieve.o $(OBJTEST)/sieve_test.o -o $(TEST)/sieve_test $(GTEST)


avl_tree.o : $(STRUCTURES)/avl_tree.cpp
	$(CMPL) -c $(STRUCTURES)/avl_tree.cpp -o $(OBJSRC)/avl_tree.o

avl_tree_test.o : $(TEST)/avl_tree_test.cpp
	$(CMPL) -c $(TEST)/avl_tree_test.cpp -o $(OBJTEST)/avl_tree_test.o

avl_tree_test : avl_tree.o avl_tree_test.o
	$(CMPL) $(OBJSRC)/avl_tree.o $(OBJTEST)/avl_tree_test.o -o $(TEST)/avl_tree_test $(GTEST)


disjoint_sets.o : $(STRUCTURES)/disjoint_sets.cpp
	$(CMPL) -c $(STRUCTURES)/disjoint_sets.cpp -o $(OBJSRC)/disjoint_sets.o

disjoint_sets_test.o : $(TEST)/disjoint_sets_test.cpp
	$(CMPL) -c $(TEST)/disjoint_sets_test.cpp -o $(OBJTEST)/disjoint_sets_test.o

disjoint_sets_test : disjoint_sets.o disjoint_sets_test.o
	$(CMPL) $(OBJSRC)/disjoint_sets.o $(OBJTEST)/disjoint_sets_test.o -o $(TEST)/disjoint_sets_test $(GTEST)


equation_system.o : $(STRUCTURES)/equation_system.cpp
	$(CMPL) -c $(STRUCTURES)/equation_system.cpp -o $(OBJSRC)/equation_system.o
