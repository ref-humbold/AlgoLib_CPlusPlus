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

graphsDir : graph.o searching.o

mathsDir : maths.o prime_tests.o sieve.o

structuresDir : avl_tree.o disjoint_sets.o equation_system.o kmr_factors_dict.o

bfs_table.o : $(ALGOLIBSRC)/bfs_table.cpp $(ALGOLIBSRC)/bfs_table.hpp
	$(CMPL) -c $(ALGOLIBSRC)/bfs_table.cpp -o $(OBJDIR)/bfs_table.o

binary_search.o : $(ALGOLIBSRC)/binary_search.cpp $(ALGOLIBSRC)/binary_search.hpp
	$(CMPL) -c $(ALGOLIBSRC)/binary_search.cpp -o $(OBJDIR)/binary_search.o

kmp.o : $(ALGOLIBSRC)/kmp.cpp $(ALGOLIBSRC)/kmp.hpp
	$(CMPL) -c $(ALGOLIBSRC)/kmp.cpp -o $(OBJDIR)/kmp.o

lis.o : $(ALGOLIBSRC)/lis.cpp $(ALGOLIBSRC)/lis.hpp
	$(CMPL) -c $(ALGOLIBSRC)/lis.cpp -o $(OBJDIR)/lis.o

najblizsze_punkty.o : $(ALGOLIBSRC)/najblizsze_punkty.cpp $(ALGOLIBSRC)/najblizsze_punkty.hpp
	$(CMPL) -c $(ALGOLIBSRC)/najblizsze_punkty.cpp -o $(OBJDIR)/najblizsze_punkty.o

otoczka_wypukla.o : $(ALGOLIBSRC)/otoczka_wypukla.cpp $(ALGOLIBSRC)/otoczka_wypukla.hpp
	$(CMPL) -c $(ALGOLIBSRC)/otoczka_wypukla.cpp -o $(OBJDIR)/otoczka_wypukla.o

psoms.o : $(ALGOLIBSRC)/psoms.cpp $(ALGOLIBSRC)/psoms.hpp
	$(CMPL) -c $(ALGOLIBSRC)/psoms.cpp -o $(OBJDIR)/psoms.o

sorting.o : $(ALGOLIBSRC)/sorting.cpp $(ALGOLIBSRC)/sorting.hpp
	$(CMPL) -c $(ALGOLIBSRC)/sorting.cpp -o $(OBJDIR)/sorting.o

graph.o : $(GRAPHSSRC)/graph.cpp $(GRAPHSSRC)/graph.hpp
	$(CMPL) -c $(GRAPHSSRC)/graph.cpp -o $(OBJDIR)/graph.o

searching.o : $(GRAPHSSRC)/searching.cpp $(GRAPHSSRC)/searching.hpp $(GRAPHSSRC)/graph.hpp
	$(CMPL) -c $(GRAPHSSRC)/searching.cpp -o $(OBJDIR)/searching.o

maths.o : $(MATHSSRC)/maths.cpp $(MATHSSRC)/maths.hpp
	$(CMPL) -c $(MATHSSRC)/maths.cpp -o $(OBJDIR)/maths.o

prime_tests.o : $(MATHSSRC)/prime_tests.cpp $(MATHSSRC)/prime_tests.hpp $(MATHSSRC)/maths.hpp
	$(CMPL) -c $(MATHSSRC)/prime_tests.cpp -o $(OBJDIR)/prime_tests.o

sieve.o : $(MATHSSRC)/sieve.cpp $(MATHSSRC)/sieve.hpp
	$(CMPL) -c $(MATHSSRC)/sieve.cpp -o $(OBJDIR)/sieve.o

avl_tree.o : $(STRUCTURESSRC)/avl_tree.cpp $(STRUCTURESSRC)/avl_tree.hpp
	$(CMPL) -c $(STRUCTURESSRC)/avl_tree.cpp -o $(OBJDIR)/avl_tree.o

disjoint_sets.o : $(STRUCTURESSRC)/disjoint_sets.cpp $(STRUCTURESSRC)/disjoint_sets.hpp
	$(CMPL) -c $(STRUCTURESSRC)/disjoint_sets.cpp -o $(OBJDIR)/disjoint_sets.o

equation_system.o : $(STRUCTURESSRC)/equation_system.cpp $(STRUCTURESSRC)/equation_system.hpp
	$(CMPL) -c $(STRUCTURESSRC)/equation_system.cpp -o $(OBJDIR)/equation_system.o

kmr_factors_dict.o : $(STRUCTURESSRC)/kmr_factors_dict.cpp $(STRUCTURESSRC)/kmr_factors_dict.hpp
	$(CMPL) -c $(STRUCTURESSRC)/kmr_factors_dict.cpp -o $(OBJDIR)/kmr_factors_dict.o
