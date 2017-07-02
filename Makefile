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

test : avl_tree_test directed_graph_test disjoint_sets_test kmp_test mst_test topological_sorting_test undirected_graph_test

alltest : all test

clean :
	rm -f $(OBJALGOLIB)/*.o
	rm -f $(OBJTEST)/*.o

refresh : clean all

refreshtest : clean alltest

algolibDir : closest_points.o convex_hull.o kmp.o kmr.o lis.o maximum_subarray.o sorting.o two_sat.o

graphsDir : cutting.o directed_graph.o graph.o mst.o paths.o searching.o topological_sorting.o undirected_graph.o

mathsDir : maths.o prime_tests.o sieve.o

structuresDir : avl_tree.o disjoint_sets.o equation_system.o


closest_points.o : $(ALGOLIB)/closest_points.cpp
	$(CMPL) -c $(ALGOLIB)/closest_points.cpp -o $(OBJALGOLIB)/closest_points.o


convex_hull.o : $(ALGOLIB)/convex_hull.cpp
	$(CMPL) -c $(ALGOLIB)/convex_hull.cpp -o $(OBJALGOLIB)/convex_hull.o


kmp.o : $(ALGOLIB)/kmp.cpp
	$(CMPL) -c $(ALGOLIB)/kmp.cpp -o $(OBJALGOLIB)/kmp.o

kmp_test.o : $(TEST)/kmp_test.cpp
	$(CMPL) -c $(TEST)/kmp_test.cpp -o $(OBJTEST)/kmp_test.o

kmp_test : kmp.o kmp_test.o
	$(CMPL) $(OBJALGOLIB)/kmp.o $(OBJTEST)/kmp_test.o -o $(TEST)/kmp_test $(GTEST)


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

directed_graph_test.o : $(TEST)/directed_graph_test.cpp
	$(CMPL) -c $(TEST)/directed_graph_test.cpp -o $(OBJTEST)/directed_graph_test.o

directed_graph_test : graph.o directed_graph.o directed_graph_test.o
	$(CMPL) $(OBJALGOLIB)/graph.o $(OBJALGOLIB)/directed_graph.o $(OBJTEST)/directed_graph_test.o -o $(TEST)/directed_graph_test $(GTEST)


graph.o : $(GRAPHS)/graph.cpp
	$(CMPL) -c $(GRAPHS)/graph.cpp -o $(OBJALGOLIB)/graph.o


mst.o : $(GRAPHS)/mst.cpp
	$(CMPL) -c $(GRAPHS)/mst.cpp -o $(OBJALGOLIB)/mst.o

mst_test.o : $(TEST)/mst_test.cpp
	$(CMPL) -c $(TEST)/mst_test.cpp -o $(OBJTEST)/mst_test.o

mst_test : graph.o directed_graph.o undirected_graph.o disjoint_sets.o mst.o mst_test.o
	$(CMPL) $(OBJALGOLIB)/graph.o $(OBJALGOLIB)/directed_graph.o $(OBJALGOLIB)/undirected_graph.o $(OBJALGOLIB)/disjoint_sets.o $(OBJALGOLIB)/mst.o $(OBJTEST)/mst_test.o -o $(TEST)/mst_test $(GTEST)


paths.o : $(GRAPHS)/paths.cpp
	$(CMPL) -c $(GRAPHS)/paths.cpp -o $(OBJALGOLIB)/paths.o


searching.o : $(GRAPHS)/searching.cpp
	$(CMPL) -c $(GRAPHS)/searching.cpp -o $(OBJALGOLIB)/searching.o


topological_sorting.o : $(GRAPHS)/topological_sorting.cpp
	$(CMPL) -c $(GRAPHS)/topological_sorting.cpp -o $(OBJALGOLIB)/topological_sorting.o

topological_sorting_test.o : $(TEST)/topological_sorting_test.cpp
	$(CMPL) -c $(TEST)/topological_sorting_test.cpp -o $(OBJTEST)/topological_sorting_test.o

topological_sorting_test : graph.o directed_graph.o topological_sorting.o topological_sorting_test.o
	$(CMPL) $(OBJALGOLIB)/graph.o $(OBJALGOLIB)/directed_graph.o $(OBJALGOLIB)/topological_sorting.o $(OBJTEST)/topological_sorting_test.o -o $(TEST)/topological_sorting_test $(GTEST)


undirected_graph.o : $(GRAPHS)/undirected_graph.cpp
	$(CMPL) -c $(GRAPHS)/undirected_graph.cpp -o $(OBJALGOLIB)/undirected_graph.o

undirected_graph_test.o : $(TEST)/undirected_graph_test.cpp
	$(CMPL) -c $(TEST)/undirected_graph_test.cpp -o $(OBJTEST)/undirected_graph_test.o

undirected_graph_test : graph.o directed_graph.o undirected_graph.o undirected_graph_test.o
	$(CMPL) $(OBJALGOLIB)/graph.o $(OBJALGOLIB)/directed_graph.o $(OBJALGOLIB)/undirected_graph.o $(OBJTEST)/undirected_graph_test.o -o $(TEST)/undirected_graph_test $(GTEST)


maths.o : $(MATHS)/maths.cpp
	$(CMPL) -c $(MATHS)/maths.cpp -o $(OBJALGOLIB)/maths.o


prime_tests.o : $(MATHS)/prime_tests.cpp
	$(CMPL) -c $(MATHS)/prime_tests.cpp -o $(OBJALGOLIB)/prime_tests.o


sieve.o : $(MATHS)/sieve.cpp
	$(CMPL) -c $(MATHS)/sieve.cpp -o $(OBJALGOLIB)/sieve.o


avl_tree.o : $(STRUCTURES)/avl_tree.cpp
	$(CMPL) -c $(STRUCTURES)/avl_tree.cpp -o $(OBJALGOLIB)/avl_tree.o

avl_tree_test.o : $(TEST)/avl_tree_test.cpp
	$(CMPL) -c $(TEST)/avl_tree_test.cpp -o $(OBJTEST)/avl_tree_test.o

avl_tree_test : avl_tree.o avl_tree_test.o
	$(CMPL) $(OBJALGOLIB)/avl_tree.o $(OBJTEST)/avl_tree_test.o -o $(TEST)/avl_tree_test $(GTEST)


disjoint_sets.o : $(STRUCTURES)/disjoint_sets.cpp
	$(CMPL) -c $(STRUCTURES)/disjoint_sets.cpp -o $(OBJALGOLIB)/disjoint_sets.o

disjoint_sets_test.o : $(TEST)/disjoint_sets_test.cpp
	$(CMPL) -c $(TEST)/disjoint_sets_test.cpp -o $(OBJTEST)/disjoint_sets_test.o

disjoint_sets_test : disjoint_sets.o disjoint_sets_test.o
	$(CMPL) $(OBJALGOLIB)/disjoint_sets.o $(OBJTEST)/disjoint_sets_test.o -o $(TEST)/disjoint_sets_test $(GTEST)


equation_system.o : $(STRUCTURES)/equation_system.cpp
	$(CMPL) -c $(STRUCTURES)/equation_system.cpp -o $(OBJALGOLIB)/equation_system.o
