#include "Event.h"
#include "Workday.h"
#include "Priority_Event.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdexcept>
#include <iomanip>

using namespace std;

//Sets the name value to name and the pay value to pay then calls the Event constructor
Workday::Workday(const string &name, const string &date, double pay) : Event(date) {
    pay_ = pay;
    name_ = name;
}
//Calls the first constructor but with defualt values for date and pay
Workday::Workday(const string &name) : Workday(name, "today", 15.00) {}
//Calls the first constructor but with defualt value for date
Workday::Workday(const string &name, double pay) : Workday(name, "today", pay) {}
//Calls the first constructor but with defualt value for pay
Workday::Workday(const string &name, const string &date) : Workday(name, date, 15.00) {}
//Calls the first constructor but with defualt values for pay and date then calls the event method set to set the date
Workday::Workday(const string &name, int y, int m, int d) : Workday(name, "today", 15.00) {set(y,m,d);}
//Returns name
string Workday::GetName() const {return name_;}
//Returns pay
double Workday::GetPay() const {return pay_;}
//This operator checks for chronological order by comparing year, month, and day
bool Workday::operator<(const Event &rhs) const {
    if (rhs.year() > year()) return true;
    else if (rhs.year() == year() && rhs.month() > month()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() > day()) return true;
    else return false;
}
//Makes the string rhs into a event then calls the Workday < Event operator 
bool Workday::operator<(const string &rhs) const {
    Event temp(rhs);
    return *this < temp;
}
//This operator checks for chronological order by comparing year, month, and day 
//Then if same day checks if the Priority_Event has a Priority > 10
bool Workday::operator<(const Priority_Event &rhs) const {
    if (rhs.year() > year()) return true;
    else if (rhs.year() == year() && rhs.month() > month()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() > day()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() == day() && rhs.GetPriority() < 10) return true;
    else return false;
}
//This operator checks for chronological order by comparing year, month, and day 
//Then if same day check the pay
bool Workday::operator<(const Workday &rhs) const {
    if (rhs.year() > year()) return true;
    else if (rhs.year() == year() && rhs.month() > month()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() > day()) return true;
    else if (rhs.year() == year() && rhs.month() == month() && rhs.day() == day() && rhs.GetPay() > pay_) return true;
    else return false;
}
//Outputs Name then pay then date
ostream& operator<<(ostream &out, const Workday &rhs) {
    const auto save_fill = out.fill('0');
	return out << rhs.GetName() << ", Pay: $" << rhs.GetPay() << ", Date: "
			   << std::setw(4) << rhs.year() << '-'
			   << std::setw(2) << rhs.month() << '-'
			   << std::setw(2) << rhs.day() << std::setfill(save_fill);
}