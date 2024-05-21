#ifndef HOLIDAY_H_INCLUDED
#define HOLIDAY_H_INCLUDED

#include <iostream>
#include <string>
#include "Priority_Event.h"
class Holiday : public Priority_Event {
  public:
    Holiday() = delete;

    //Input: A string for name
    //Output: None
    Holiday(const std::string &name);

    //Input: A string for name and a bool for if the holiday is a government one
    //Output: None
    Holiday(const std::string &name, bool is_gov);

    //Input: A string for name and a string that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow
    //Output: None
    Holiday(const std::string &name, const std::string &date);

    //Input: A string for name and a string that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow and a bool for if the holiday is a government one
    //Output: None
    Holiday(const std::string &name, const std::string &date, bool is_gov);

    //Input: A string for name and 3 ints where y is the year, m is the month, and d is for day
    //Output: None
    Holiday(const std::string &name, int y, int m, int d);

    //Input: A string for name and 3 ints where y is the year, m is the month, and d is for day and a bool for if the holiday is a government one
    //Output: None
    Holiday(const std::string &name, int y, int m, int d, bool is_gov);

    Holiday(const Holiday &rhs) = default;
    Holiday &operator=(const Holiday &rhs) = default;
    Holiday &operator=(Holiday &&rhs) = default;
    Holiday(Holiday &&rhs) = default;
    virtual ~Holiday() = default;

    //Input: A Event Object
    //Output: a bool that represents wether or not the first object is smaller than the Event object
    bool operator<(const Event &rhs) const;

    //Input: A string for date that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow 
    //Output: a bool that represents wether or not the first object is smaller than the date string
    bool operator<(const std::string &rhs) const;

    //Input: A Priority_Event object
    //Output: a bool that represents wether or not the first object is smaller than the priority_event
    bool operator<(const Priority_Event &rhs) const;

    //Input: A Holiday object
    //Output: a bool that represents wether or not the first object is smaller than the Holiday object
    bool operator<(const Holiday &rhs) const;
};

std::ostream& operator<<(std::ostream &out, const Holiday &rhs);

#endif /* WORKDAY_H_INCLUDED */