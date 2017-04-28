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
	rm -rf $(OBJDIR)

algolibDir : bfs_table.o binary_search.o kmp.o lis.o najblizsze_punkty.o otoczka_wypukla.o psoms.o sorting.o

graphsDir : graph.o mst.o paths.o searching.o topological_sorting.o

mathsDir : maths.o prime_tests.o sieve.o

structuresDir : avl_tree.o disjoint_sets.o equation_system.o kmr_factors_dict.o

bfs_table.o : $(ALGOLIBSRC)/bfs_table.cpp
	$(CMPL) -c $(ALGOLIBSRC)/bfs_table.cpp -o $(OBJDIR)/bfs_table.o

binary_search.o : $(ALGOLIBSRC)/binary_search.cpp
	$(CMPL) -c $(ALGOLIBSRC)/binary_search.cpp -o $(OBJDIR)/binary_search.o

kmp.o : $(ALGOLIBSRC)/kmp.cpp
	$(CMPL) -c $(ALGOLIBSRC)/kmp.cpp -o $(OBJDIR)/kmp.o

lis.o : $(ALGOLIBSRC)/lis.cpp
	$(CMPL) -c $(ALGOLIBSRC)/lis.cpp -o $(OBJDIR)/lis.o

najblizsze_punkty.o : $(ALGOLIBSRC)/najblizsze_punkty.cpp
	$(CMPL) -c $(ALGOLIBSRC)/najblizsze_punkty.cpp -o $(OBJDIR)/najblizsze_punkty.o

otoczka_wypukla.o : $(ALGOLIBSRC)/otoczka_wypukla.cpp
	$(CMPL) -c $(ALGOLIBSRC)/otoczka_wypukla.cpp -o $(OBJDIR)/otoczka_wypukla.o

psoms.o : $(ALGOLIBSRC)/psoms.cpp
	$(CMPL) -c $(ALGOLIBSRC)/psoms.cpp -o $(OBJDIR)/psoms.o

sorting.o : $(ALGOLIBSRC)/sorting.cpp
	$(CMPL) -c $(ALGOLIBSRC)/sorting.cpp -o $(OBJDIR)/sorting.o

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

kmr_factors_dict.o : $(STRUCTURESSRC)/kmr_factors_dict.cpp
	$(CMPL) -c $(STRUCTURESSRC)/kmr_factors_dict.cpp -o $(OBJDIR)/kmr_factors_dict.o
