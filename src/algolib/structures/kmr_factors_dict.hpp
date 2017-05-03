// SŁOWNIK PODSŁÓW BAZOWYCH Z ALGORYTMEM KARPA-MILLERA-ROSENBERGA
#ifndef KMR_FACTORS_DICT_HPP
#define KMR_FACTORS_DICT_HPP

#include <cstdlib>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <algorithm>

namespace algolib
{
    namespace structures
    {
        class kmr_factors_dict
        {
        private:
            /** Słowo. */
            std::string text;

            /** Słownik podsłów bazowych. */
            std::map<std::string, int> factors;

        public:
            explicit kmr_factors_dict(std::string s);

            ~kmr_factors_dict() = default;
            kmr_factors_dict(const kmr_factors_dict & kmrfd) = default;
            kmr_factors_dict(kmr_factors_dict && kmrfd) = default;
            kmr_factors_dict& operator=(const kmr_factors_dict & kmrfd) = default;
            kmr_factors_dict& operator=(kmr_factors_dict && kmrfd) = default;

            std::string get_text() const
            {
                return text;
            }

            std::map<std::string, int> get_factors()
            {
                return factors;
            }

            /** Budowa słownika podsłów bazowych. */
            void kmr();

        private:
            /** Budowa podsłów złożonych z pojedynczych znaków. */
            void sign_letters();

            /**
             * Budowa nowych podsłów o podwojonej długości.
             * @param new_length nowa długość podsłów
             */
            void double_length(int new_length);
        };
    }
}

#endif

