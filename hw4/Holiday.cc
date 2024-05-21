#include "Priority_Event.h"
#include "Holiday.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdexcept>
#include <iomanip>

using namespace std;

//Calls priority event with name, date, the checks is_gov if true priority is 0 else 15
Holiday::Holiday(const string &name, const string &date, bool is_gov) : Priority_Event(name, date, (is_gov ? 0 : 15)) {}
//Calls the first constructor but with a default value for date then calls the event method set to set the date
Holiday::Holiday(const string &name, int y, int m, int d, bool is_gov) : Holiday(name, "today", is_gov) {set(y,m,d);}
//Calls the first constructor but with defualt value for date and is_gov
Holiday::Holiday(const string &name) : Holiday(name, "today", false) {}
//Calls the first constructor but with defualt value for date
Holiday::Holiday(const string &name, bool is_gov) : Holiday(name, "today", is_gov) {}
//Calls the first constructor but with defualt value for is_gov
Holiday::Holiday(const string &name, const string &date) : Holiday(name, date, false) {}
//Calls the name, y, m, d, is_gov constructor but with a defualt value for is_gov
Holiday::Holiday(const string &name, int y, int m, int d) : Holiday(name, y, m, d, false) {}
//This operator checks for chronological order by comparing year, month, and day. 
//Then if same day checks if the Holiday has a Priority > 10
bool Holiday::operator<(const Event &rhs) const {
    if (rhs.year() > year()) return true;
    else if (rhs.year() == year() && rhs.month() > month()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() > day()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() == day() && 10 < GetPriority()) return true;
    else return false;
}
//Makes the string rhs into a event then calls the Holiday < Event operator 
bool Holiday::operator<(const string &rhs) const {
    Event temp(rhs);
    return *this < temp;
}
//This operator checks for chronological order by comparing year, month, and day 
//Then if same day checks if the the priority is higher
bool Holiday::operator<(const Priority_Event &rhs) const {
    if (rhs.year() > year()) return true;
    else if (rhs.year() == year() && rhs.month() > month()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() > day()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() == day() && rhs.GetPriority() < GetPriority()) return true;
    else return false;
}
//This operator checks for chronological order by comparing year, month, and day 
//Then if same day checks if the the priority is higher
bool Holiday::operator<(const Holiday &rhs) const {
    if (rhs.year() > year()) return true;
    else if (rhs.year() == year() && rhs.month() > month()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() > day()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() == day() && rhs.GetPriority() < GetPriority()) return true;
    else return false;
}
//Outputs name then wether or not it is a government holiday then date
ostream& operator<<(ostream &out, const Holiday &rhs) {
    const auto save_fill = out.fill('0');
    string is_gov = " Not ";
    if (rhs.GetPriority() == 0) {is_gov = " ";}
	return out << rhs.GetName() << ", Is" << is_gov << "a Government Holiday" << ", Date: "
			   << std::setw(4) << rhs.year() << '-'
			   << std::setw(2) << rhs.month() << '-'
			   << std::setw(2) << rhs.day() << std::setfill(save_fill);
}