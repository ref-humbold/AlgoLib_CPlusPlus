CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra -iquote include
CMPL = $(CXX) $(CXXFLAGS)
GTEST = -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main -lpthread
SRC = src
OBJ = obj
TEST = test
ALGOLIB = $(SRC)/algolib
GRAPHS = $(ALGOLIB)/graphs
MATHS = $(ALGOLIB)/maths
STRUCTURES = $(ALGOLIB)/structures
OBJSRC = $(OBJ)/$(SRC)
OBJTEST = $(OBJ)/$(TEST)
TESTBIN = $(TEST)/bin

.PHONY: all prepare clean refresh test testDir srcDir algolibDir graphsDir mathsDir structuresDir

all : prepare srcDir testDir

prepare :
	mkdir -p $(OBJSRC) $(OBJTEST) $(TESTBIN)

clean :
	rm -rf $(OBJ)

refresh : clean all

test : prepare testDir
	@sh run-tests.sh

testDir : avl_tree_test directed_graph_test disjoint_sets_test fraction_test kmp_test lca_test \
maths_test maximum_subarray_test mst_test paths_test scc_test primes_test sorting_test \
topological_sorting_test undirected_graph_test

srcDir : algolibDir graphsDir mathsDir structuresDir

algolibDir : closest_points.o convex_hull.o kmp.o kmr.o lis.o maximum_subarray.o sorting.o two_sat.o

graphsDir : cutting.o directed_graph.o forest_graph.o graph.o lca.o matching.o mst.o \
multipartite_graph.o paths.o scc.o searching.o topological_sorting.o undirected_graph.o

mathsDir : fraction.o maths.o primes.o

structuresDir : avl_tree.o disjoint_sets.o equation_system.o

# algolib

closest_points.o : $(ALGOLIB)/closest_points.cpp
	$(CMPL) -c $(ALGOLIB)/closest_points.cpp -o $(OBJSRC)/closest_points.o

convex_hull.o : $(ALGOLIB)/convex_hull.cpp
	$(CMPL) -c $(ALGOLIB)/convex_hull.cpp -o $(OBJSRC)/convex_hull.o

kmp.o : $(ALGOLIB)/kmp.cpp
	$(CMPL) -c $(ALGOLIB)/kmp.cpp -o $(OBJSRC)/kmp.o

kmp_test : $(TEST)/kmp_test.cpp kmp.o
	$(CMPL) -c $(TEST)/kmp_test.cpp -o $(OBJTEST)/kmp_test.o
	$(CMPL) $(OBJSRC)/kmp.o $(OBJTEST)/kmp_test.o -o $(TESTBIN)/kmp_test $(GTEST)

kmr.o : $(ALGOLIB)/kmr.cpp
	$(CMPL) -c $(ALGOLIB)/kmr.cpp -o $(OBJSRC)/kmr.o

lis.o : $(ALGOLIB)/lis.cpp
	$(CMPL) -c $(ALGOLIB)/lis.cpp -o $(OBJSRC)/lis.o

maximum_subarray.o : $(ALGOLIB)/maximum_subarray.cpp
	$(CMPL) -c $(ALGOLIB)/maximum_subarray.cpp -o $(OBJSRC)/maximum_subarray.o

maximum_subarray_test : $(TEST)/maximum_subarray_test.cpp maximum_subarray.o
	$(CMPL) -c $(TEST)/maximum_subarray_test.cpp -o $(OBJTEST)/maximum_subarray_test.o
	$(CMPL) $(OBJSRC)/maximum_subarray.o $(OBJTEST)/maximum_subarray_test.o \
	  -o $(TESTBIN)/maximum_subarray_test $(GTEST)

sorting.o : $(ALGOLIB)/sorting.cpp
	$(CMPL) -c $(ALGOLIB)/sorting.cpp -o $(OBJSRC)/sorting.o

sorting_test : $(TEST)/sorting_test.cpp sorting.o
	$(CMPL) -c $(TEST)/sorting_test.cpp -o $(OBJTEST)/sorting_test.o
	$(CMPL) $(OBJSRC)/sorting.o $(OBJTEST)/sorting_test.o -o $(TESTBIN)/sorting_test $(GTEST)

two_sat.o : $(ALGOLIB)/two_sat.cpp
	$(CMPL) -c $(ALGOLIB)/two_sat.cpp -o $(OBJSRC)/two_sat.o

# algolib/graphs

cutting.o : $(GRAPHS)/cutting.cpp
	$(CMPL) -c $(GRAPHS)/cutting.cpp -o $(OBJSRC)/cutting.o

directed_graph.o : $(GRAPHS)/directed_graph.cpp
	$(CMPL) -c $(GRAPHS)/directed_graph.cpp -o $(OBJSRC)/directed_graph.o

directed_graph_test : $(TEST)/directed_graph_test.cpp graph.o directed_graph.o
	$(CMPL) -c $(TEST)/directed_graph_test.cpp -o $(OBJTEST)/directed_graph_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJTEST)/directed_graph_test.o \
	  -o $(TESTBIN)/directed_graph_test $(GTEST)

forest_graph.o : $(GRAPHS)/forest_graph.cpp
	$(CMPL) -c $(GRAPHS)/forest_graph.cpp -o $(OBJSRC)/forest_graph.o

graph.o : $(GRAPHS)/graph.cpp
	$(CMPL) -c $(GRAPHS)/graph.cpp -o $(OBJSRC)/graph.o

lca.o : $(GRAPHS)/lca.cpp
	$(CMPL) -c $(GRAPHS)/lca.cpp -o $(OBJSRC)/lca.o

lca_test : $(TEST)/lca_test.cpp graph.o directed_graph.o undirected_graph.o disjoint_sets.o forest_graph.o lca.o
	$(CMPL) -c $(TEST)/lca_test.cpp -o $(OBJTEST)/lca_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/undirected_graph.o \
	  $(OBJSRC)/disjoint_sets.o $(OBJSRC)/forest_graph.o $(OBJSRC)/lca.o $(OBJTEST)/lca_test.o \
	  -o $(TESTBIN)/lca_test $(GTEST)

matching.o : $(GRAPHS)/matching.cpp
	$(CMPL) -c $(GRAPHS)/matching.cpp -o $(OBJSRC)/matching.o

mst.o : $(GRAPHS)/mst.cpp
	$(CMPL) -c $(GRAPHS)/mst.cpp -o $(OBJSRC)/mst.o

mst_test : $(TEST)/mst_test.cpp graph.o directed_graph.o undirected_graph.o disjoint_sets.o mst.o
	$(CMPL) -c $(TEST)/mst_test.cpp -o $(OBJTEST)/mst_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/undirected_graph.o \
	  $(OBJSRC)/disjoint_sets.o $(OBJSRC)/mst.o $(OBJTEST)/mst_test.o -o $(TESTBIN)/mst_test \
	  $(GTEST)

multipartite_graph.o : $(GRAPHS)/multipartite_graph.cpp
	$(CMPL) -c $(GRAPHS)/multipartite_graph.cpp -o $(OBJSRC)/multipartite_graph.o

paths.o : $(GRAPHS)/paths.cpp
	$(CMPL) -c $(GRAPHS)/paths.cpp -o $(OBJSRC)/paths.o

paths_test : $(TEST)/paths_test.cpp graph.o directed_graph.o undirected_graph.o paths.o
	$(CMPL) -c $(TEST)/paths_test.cpp -o $(OBJTEST)/paths_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/undirected_graph.o \
	  $(OBJSRC)/paths.o $(OBJTEST)/paths_test.o -o $(TESTBIN)/paths_test $(GTEST)

scc.o : $(GRAPHS)/scc.cpp
	$(CMPL) -c $(GRAPHS)/scc.cpp -o $(OBJSRC)/scc.o

scc_test : $(TEST)/scc_test.cpp graph.o directed_graph.o scc.o
	$(CMPL) -c $(TEST)/scc_test.cpp -o $(OBJTEST)/scc_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/scc.o $(OBJTEST)/scc_test.o \
	  -o $(TESTBIN)/scc_test $(GTEST)

searching.o : $(GRAPHS)/searching.cpp
	$(CMPL) -c $(GRAPHS)/searching.cpp -o $(OBJSRC)/searching.o

topological_sorting.o : $(GRAPHS)/topological_sorting.cpp
	$(CMPL) -c $(GRAPHS)/topological_sorting.cpp -o $(OBJSRC)/topological_sorting.o

topological_sorting_test : $(TEST)/topological_sorting_test.cpp graph.o directed_graph.o topological_sorting.o
	$(CMPL) -c $(TEST)/topological_sorting_test.cpp -o $(OBJTEST)/topological_sorting_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/topological_sorting.o \
	  $(OBJTEST)/topological_sorting_test.o -o $(TESTBIN)/topological_sorting_test $(GTEST)

undirected_graph.o : $(GRAPHS)/undirected_graph.cpp
	$(CMPL) -c $(GRAPHS)/undirected_graph.cpp -o $(OBJSRC)/undirected_graph.o

undirected_graph_test : $(TEST)/undirected_graph_test.cpp graph.o directed_graph.o undirected_graph.o
	$(CMPL) -c $(TEST)/undirected_graph_test.cpp -o $(OBJTEST)/undirected_graph_test.o
	$(CMPL) $(OBJSRC)/graph.o $(OBJSRC)/directed_graph.o $(OBJSRC)/undirected_graph.o \
	  $(OBJTEST)/undirected_graph_test.o -o $(TESTBIN)/undirected_graph_test $(GTEST)

# algolib/maths

fraction.o : $(MATHS)/fraction.cpp
	$(CMPL) -c $(MATHS)/fraction.cpp -o $(OBJSRC)/fraction.o

fraction_test : $(TEST)/fraction_test.cpp maths.o fraction.o
	$(CMPL) -c $(TEST)/fraction_test.cpp -o $(OBJTEST)/fraction_test.o
	$(CMPL) $(OBJSRC)/maths.o $(OBJSRC)/fraction.o $(OBJTEST)/fraction_test.o \
	  -o $(TESTBIN)/fraction_test $(GTEST)


maths.o : $(MATHS)/maths.cpp
	$(CMPL) -c $(MATHS)/maths.cpp -o $(OBJSRC)/maths.o

maths_test : $(TEST)/maths_test.cpp maths.o
	$(CMPL) -c $(TEST)/maths_test.cpp -o $(OBJTEST)/maths_test.o
	$(CMPL) $(OBJSRC)/maths.o $(OBJTEST)/maths_test.o -o $(TESTBIN)/maths_test $(GTEST)

primes.o : $(MATHS)/primes.cpp
	$(CMPL) -c $(MATHS)/primes.cpp -o $(OBJSRC)/primes.o

primes_test : $(TEST)/primes_test.cpp maths.o primes.o
	$(CMPL) -c $(TEST)/primes_test.cpp -o $(OBJTEST)/primes_test.o
	$(CMPL) $(OBJSRC)/maths.o $(OBJSRC)/primes.o $(OBJTEST)/primes_test.o \
	  -o $(TESTBIN)/primes_test $(GTEST)

# algolib/structures

avl_tree.o : $(STRUCTURES)/avl_tree.cpp
	$(CMPL) -c $(STRUCTURES)/avl_tree.cpp -o $(OBJSRC)/avl_tree.o

avl_tree_test : $(TEST)/avl_tree_test.cpp avl_tree.o
	$(CMPL) -c $(TEST)/avl_tree_test.cpp -o $(OBJTEST)/avl_tree_test.o
	$(CMPL) $(OBJSRC)/avl_tree.o $(OBJTEST)/avl_tree_test.o -o $(TESTBIN)/avl_tree_test $(GTEST)

disjoint_sets.o : $(STRUCTURES)/disjoint_sets.cpp
	$(CMPL) -c $(STRUCTURES)/disjoint_sets.cpp -o $(OBJSRC)/disjoint_sets.o

disjoint_sets_test : $(TEST)/disjoint_sets_test.cpp disjoint_sets.o
	$(CMPL) -c $(TEST)/disjoint_sets_test.cpp -o $(OBJTEST)/disjoint_sets_test.o
	$(CMPL) $(OBJSRC)/disjoint_sets.o $(OBJTEST)/disjoint_sets_test.o \
	  -o $(TESTBIN)/disjoint_sets_test $(GTEST)

equation_system.o : $(STRUCTURES)/equation_system.cpp
	$(CMPL) -c $(STRUCTURES)/equation_system.cpp -o $(OBJSRC)/equation_system.o
