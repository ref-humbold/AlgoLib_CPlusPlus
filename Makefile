CXX = g++ -std=c++11
CXXFLAGS = -Wall -Wextra
CMPL = $(CXX) $(CXXFLAGS)

SRCDIR = src
OBJDIR = obj

ALGOLIBSRC = $(SRCDIR)/algolib
GRAPHSSRC = $(SRCDIR)/algolib/graphs
MATHSSRC = $(SRCDIR)/algolib/maths
STRUCTURESSRC = $(SRCDIR)/algolib/structures

all: algolibDir graphsDir mathsDir structuresDir

clean :
	rm -f $(OBJDIR)/*.o

refresh : clean all

algolibDir : closest_points.o convex_hull.o kmp.o kmr.o lis.o maximum_subarray.o sorting.o two_sat.o

graphsDir : cutting.o directed_graph.o graph.o mst.o paths.o searching.o topological_sorting.o undirected_graph.o

mathsDir : maths.o prime_tests.o sieve.o

structuresDir : avl_tree.o disjoint_sets.o equation_system.o

closest_points.o : $(ALGOLIBSRC)/closest_points.cpp
	$(CMPL) -c $(ALGOLIBSRC)/closest_points.cpp -o $(OBJDIR)/closest_points.o

convex_hull.o : $(ALGOLIBSRC)/convex_hull.cpp
	$(CMPL) -c $(ALGOLIBSRC)/convex_hull.cpp -o $(OBJDIR)/convex_hull.o

kmp.o : $(ALGOLIBSRC)/kmp.cpp
	$(CMPL) -c $(ALGOLIBSRC)/kmp.cpp -o $(OBJDIR)/kmp.o

kmr.o : $(ALGOLIBSRC)/kmr.cpp
	$(CMPL) -c $(ALGOLIBSRC)/kmr.cpp -o $(OBJDIR)/kmr.o

lis.o : $(ALGOLIBSRC)/lis.cpp
	$(CMPL) -c $(ALGOLIBSRC)/lis.cpp -o $(OBJDIR)/lis.o

maximum_subarray.o : $(ALGOLIBSRC)/maximum_subarray.cpp
	$(CMPL) -c $(ALGOLIBSRC)/maximum_subarray.cpp -o $(OBJDIR)/maximum_subarray.o

sorting.o : $(ALGOLIBSRC)/sorting.cpp
	$(CMPL) -c $(ALGOLIBSRC)/sorting.cpp -o $(OBJDIR)/sorting.o

two_sat.o : $(ALGOLIBSRC)/two_sat.cpp
	$(CMPL) -c $(ALGOLIBSRC)/two_sat.cpp -o $(OBJDIR)/two_sat.o

cutting.o : $(GRAPHSSRC)/cutting.cpp
	$(CMPL) -c $(GRAPHSSRC)/cutting.cpp -o $(OBJDIR)/cutting.o

directed_graph.o : $(GRAPHSSRC)/directed_graph.cpp
	$(CMPL) -c $(GRAPHSSRC)/directed_graph.cpp -o $(OBJDIR)/directed_graph.o

graph.o : $(GRAPHSSRC)/graph.cpp
	$(CMPL) -c $(GRAPHSSRC)/graph.cpp -o $(OBJDIR)/graph.o

mst.o : $(GRAPHSSRC)/mst.cpp
	$(CMPL) -c $(GRAPHSSRC)/mst.cpp -o $(OBJDIR)/mst.o

paths.o : $(GRAPHSSRC)/paths.cpp
	$(CMPL) -c $(GRAPHSSRC)/paths.cpp -o $(OBJDIR)/paths.o

searching.o : $(GRAPHSSRC)/searching.cpp
	$(CMPL) -c $(GRAPHSSRC)/searching.cpp -o $(OBJDIR)/searching.o

topological_sorting.o : $(GRAPHSSRC)/topological_sorting.cpp
	$(CMPL) -c $(GRAPHSSRC)/topological_sorting.cpp -o $(OBJDIR)/topological_sorting.o

undirected_graph.o : $(GRAPHSSRC)/undirected_graph.cpp
	$(CMPL) -c $(GRAPHSSRC)/undirected_graph.cpp -o $(OBJDIR)/undirected_graph.o

maths.o : $(MATHSSRC)/maths.cpp
	$(CMPL) -c $(MATHSSRC)/maths.cpp -o $(OBJDIR)/maths.o

prime_tests.o : $(MATHSSRC)/prime_tests.cpp
	$(CMPL) -c $(MATHSSRC)/prime_tests.cpp -o $(OBJDIR)/prime_tests.o

sieve.o : $(MATHSSRC)/sieve.cpp
	$(CMPL) -c $(MATHSSRC)/sieve.cpp -o $(OBJDIR)/sieve.o

avl_tree.o : $(STRUCTURESSRC)/avl_tree.cpp
	$(CMPL) -c $(STRUCTURESSRC)/avl_tree.cpp -o $(OBJDIR)/avl_tree.o

disjoint_sets.o : $(STRUCTURESSRC)/disjoint_sets.cpp
	$(CMPL) -c $(STRUCTURESSRC)/disjoint_sets.cpp -o $(OBJDIR)/disjoint_sets.o

equation_system.o : $(STRUCTURESSRC)/equation_system.cpp
	$(CMPL) -c $(STRUCTURESSRC)/equation_system.cpp -o $(OBJDIR)/equation_system.o
