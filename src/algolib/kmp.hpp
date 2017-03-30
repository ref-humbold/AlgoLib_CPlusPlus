// ALGORYTM KNUTHA-MORRISA-PRATTA WYSZUKIWANIA WZORCA W TEKŚCIE
#ifndef KMP_HPP
#define KMP_HPP

#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

namespace detail
{
    /**
    Funkcja prefiksowa pi Knutha.
    @param pattern wzorzec
    @return wartości funkcji prefiksowej
    */
    std::vector<int> prefixes(const std::string & pattern);
}

namespace algolib
{
    /**
    Algorytm Knutha-Morrisa-Pratta.
    @param text słowo
    @param pattern wzorzec
    @return lista pozycji wystąpień wzorca w słowie
    */
    std::vector<int> kmp(const std::string & text, const std::string & pattern);
}

#endif
