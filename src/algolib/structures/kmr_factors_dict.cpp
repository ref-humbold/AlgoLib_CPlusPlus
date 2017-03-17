// SŁOWNIK PODSŁÓW BAZOWYCH Z ALGORYTMEM KARPA-MILLERA-ROSENBERGA
#include "kmr_factors_dict.hpp"

algolib::kmr_factors_dict::kmr_factors_dict(std::string s) : text{s}
{
    kmr();
}

void algolib::kmr_factors_dict::kmr()
{
    sign_letters();

    for(size_t lngt = 2; lngt <= text.size(); lngt <<= 1)
        double_length(lngt);
}

void algolib::kmr_factors_dict::sign_letters()
{
    int code_value = 0;
    std::vector<std::string> letters;

    for(size_t i = 0; i < text.size(); ++i)
        letters.push_back( text.substr(i, 1) );

    std::string prev_ltr = letters[0];
    sort(letters.begin(), letters.end());
    factors.emplace(letters[0], code_value);

    for(auto ltr : letters)
        if(ltr != prev_ltr)
        {
            ++code_value;
            factors.emplace(ltr, code_value);
        }
}

void algolib::kmr_factors_dict::double_length(int new_length)
{
    int code_value = 0;
    std::vector< std::tuple<int, int, int> > codes;

    for(size_t i = 0; i <= text.size()-new_length; ++i)
    {
        std::string s1 = text.substr(i, new_length>>1);
        std::string s2 = text.substr(i+new_length/2, new_length>>1);

        codes.push_back( std::make_tuple(factors[s1], factors[s2], i) );
    }

    int prev_left, prev_right;

    sort(codes.begin(), codes.end());
    factors.emplace(text.substr(std::get<2>(codes[0]), new_length), code_value);
    std::tie(prev_left, prev_right, std::ignore) = codes[0];

    for(auto cds : codes)
        if(std::get<0>(cds) != prev_left || std::get<1>(cds) != prev_right)
        {
            ++code_value;
            factors.emplace(text.substr(std::get<2>(cds), new_length), code_value);
        }
}

