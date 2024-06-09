#ifndef STL_H
#define STL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <numeric>


// use inline to avoid multiple definition linking errors

inline void initial_vector_with_3_mutiplies(std::vector<int>& v, size_t size) {
    v.resize(size);

    int multiple {0};

    std::generate(v.begin(), v.end(), [&multiple]() {
        multiple += 3;
        return multiple;
    });
}

inline int count_unique_above(std::vector<int> v, int n) {
    
    std::set<int> unique_elements(v.begin(), v.end());

    int count = std::count_if(unique_elements.begin(), unique_elements.end(), [n](int x) {
        return x > n;
    });

    return count;
}


inline std::string vector_to_string(std::vector<int> v, char separator) {
    std::reverse(v.begin(), v.end());

    std::string result = std::accumulate(v.begin(), v.end(), std::string(),
        [separator](const std::string& a, int b) {
            return a.empty() ? std::to_string(b) : a + separator + std::to_string(b);
        });

    return result;
}

inline void square_elements(std::vector<int>& v) {
    std::transform(v.begin(), v.end(), v.begin(), [](int x) {
        return x * x;
    });
}

inline void copy_if_even(const std::vector<int>& source, std::vector<int>& destination) {
    destination.clear();
    
    std::copy_if(source.begin(), source.end(), std::back_inserter(destination), 
                 [](int num) { return num % 2 == 0; });
}




#endif //STL_H