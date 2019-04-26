// ALGORYTM KNUTHA-MORRISA-PRATTA WYSZUKIWANIA WZORCA W TEKŚCIE
#ifndef KMP_HPP_
#define KMP_HPP_

#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

namespace detail
{
    /**
     * Funkcja prefiksowa pi Knutha.
     * @param pattern wzorzec
     * @return wartości funkcji prefiksowej
     */
    std::vector<size_t> prefixes(const std::string & pattern);
}

namespace algolib
{
    namespace text
    {
        /**
         * Algorytm Knutha-Morrisa-Pratta.
         * @param text słowo
         * @param pattern wzorzec
         * @return lista pozycji wystąpień wzorca w słowie
         */
        std::vector<size_t> kmp(const std::string & text, const std::string & pattern);
    }
}

#endif
