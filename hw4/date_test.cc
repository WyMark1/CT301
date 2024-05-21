#include "Event.h"
#include "Priority_Event.h"
#include "Workday.h"
#include "Holiday.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    try{
        Event e1("yesterday");
        Event e2("1920-02-23");
        Workday w1("CS320", "today", 100.00);
        Workday w2("CT_301");
        Workday w3("CS_214", 1990, 11, 25);
        Priority_Event p1("Work","tomorrow", 5);
        Priority_Event p2("School","tomorrow", 1);
        Priority_Event p3;
        Priority_Event p4("Swim", 1930, 05, 10, 8);
        Holiday h1("Christmas");
        Holiday h2("Halloween", "2023-10-31", true);
        Holiday h3("Summer", 2020, 03, 22, false);
        Holiday h4("Winter", "2023-10-31"s);
        string tom = "tomorrow"; 
        cout << e1 << " e1\n";
        cout << e2 << " e2\n";
        cout << w1 << " w1\n";
        cout << w2 << " w2\n";
        cout << w3 << " w3\n";
        cout << p1 << " p1\n";
        cout << p2 << " p2\n";
        cout << p3 << " p3\n";
        cout << p4 << " p4\n";
        cout << h1 << " h1\n";
        cout << h2 << " h2\n";
        cout << h3 << " h3\n";
        cout << h4 << " h4\n";
        cout << (w1 < w2) << " 0\n";
        cout << (w3 < w1) << " 1\n";
        cout << (w3 < e1) << " 1\n";
        cout << (p1 < p2) << " 1\n";
        cout << (p4 < e1) << " 1\n";
        cout << (p3 < tom) << " 1\n";
        cout << (h1 < h2) << " 1\n";
        cout << (h1 < h3) << " 0\n";
        cout << (h2 < p2) << " 0\n";
        return 0;
    }
    catch(const runtime_error& e){
        cerr << "Runtime Error: " << e.what();
        return 0;
    }
}