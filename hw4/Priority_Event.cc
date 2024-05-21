#include "Event.h"
#include "Priority_Event.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdexcept>
#include <iomanip>

using namespace std;

//Sets the name value to name and checks if priority is less than 0 then sets the priority value to priortiy 
//Then calls the Event constructor
Priority_Event::Priority_Event(const string &name, const string &date, short priority) : Event(date) {
    name_ = name;
    if (priority < 0)
        throw runtime_error("Priority_Event - Error cannot set a priority less than 0. Given Priority: " + to_string(priority) + "\n");
    priority_ = priority;
}
//Calls the first constuctor but with a defualt value for date the calls the set method of event
Priority_Event::Priority_Event(const string &name, int y, int m, int d, short priority) : Priority_Event(name, "today", priority) {set(y,m,d);}
//Calls the first constuctor but with a defualt value for name, date, and priority
Priority_Event::Priority_Event() : Priority_Event("New Event", "today", 10) {}
//Calls the first constuctor but with a defualt value for date, and priority
Priority_Event::Priority_Event(const string &name) : Priority_Event(name, "today", 10) {}
//Calls the first constuctor but with a defualt value for date
Priority_Event::Priority_Event(const string &name, short priority) : Priority_Event(name, "today", priority) {}
//Calls the first constuctor but with a defualt value for priority
Priority_Event::Priority_Event(const string &name, const string &date) : Priority_Event(name, date, 10) {}
//Calls the name, y, m, d, priority constructor but with a defualt value for priority
Priority_Event::Priority_Event(const string &name, int y, int m, int d) : Priority_Event(name, y, m, d, 10) {}
//Returns name
string Priority_Event::GetName() const {return name_;}
//Returns priority
short Priority_Event::GetPriority() const {return priority_;}
//This operator checks for chronological order by comparing year, month, and day 
//Then if same day checks if the Priority_Event has a Priority > 10
bool Priority_Event::operator<(const Event &rhs) const {
    if (rhs.year() > year()) return true;
    else if (rhs.year() == year() && rhs.month() > month()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() > day()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() == day() && 10 < priority_) return true;
    else return false;
}
//Makes the string rhs into a event then calls the Priority_Event < Event operator 
bool Priority_Event::operator<(const string &rhs) const {
    Event temp(rhs);
    return *this < temp;
}
//This operator checks for chronological order by comparing year, month, and day 
//Then if same day checks if the the priority is higher
bool Priority_Event::operator<(const Priority_Event &rhs) const {
    if (rhs.year() > year()) return true;
    else if (rhs.year() == year() && rhs.month() > month()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() > day()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() == day() && rhs.GetPriority() < priority_) return true;
    else return false;
}
//Outputs Name then priority then date
ostream& operator<<(ostream &out, const Priority_Event &rhs) {
    const auto save_fill = out.fill('0');
	return out << rhs.GetName() << ", Priority: " << rhs.GetPriority() << ", Date: "
			   << std::setw(4) << rhs.year() << '-'
			   << std::setw(2) << rhs.month() << '-'
			   << std::setw(2) << rhs.day() << std::setfill(save_fill);
}