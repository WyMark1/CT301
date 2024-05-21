#include <iostream>
#include "basic_vector.h"
#include <string>
#include <cstddef>

using namespace std;

int main(int argc, char const *argv[]) {
    try {
        basic_vector<double> p(5);
        for (int i = 0; i < 20; ++i) {
            p.push_back(i);
            cout <<  "Capacity: " << p.capacity() << '\n';
        }
        cout << p.max_size() << '\n';
        p.clear();
        p.push_back(100);
        p.shrink_to_fit();
        basic_vector<double> w(7);
        w.push_back(69);
        p.swap(w);
        cout << "W head " << w.front() << "\n";
        cout <<"W Size: " << w.size() << "\nW Capacity: " << w.capacity() << "\n";
        cout << "P head " << p.front() << "\n";
        cout <<"P Size: " << p.size() << "\nP Capacity: " << p.capacity() << "\n";
        p.shrink_to_fit();
        cout <<"P Size: " << p.size() << "\nP Capacity: " << p.capacity() << "\n";
        return 0;
    } catch(const exception& e){
        cerr << "Runtime Error: " << e.what();
        return 0;
    }
}