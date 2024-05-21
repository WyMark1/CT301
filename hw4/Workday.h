#ifndef WORKDAY_H_INCLUDED
#define WORKDAY_H_INCLUDED

#include <iostream>
#include <string>
#include "Event.h"
#include "Priority_Event.h"

class Workday : public Event {
  double pay_;
  std::string name_;
  public:
    Workday() = delete;

    //Input: A string for name
    //Output: None
    Workday(const std::string &name);

    //Input: A string for name and a double for pay
    //Output: None
    Workday(const std::string &name, double pay);

    //Input: A string for name and a string that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow
    //Output: None
    Workday(const std::string &name, const std::string &date);

    //Input: A string for name and a string that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow and a double pay
    //Output: None
    Workday(const std::string &name, const std::string &date, double pay);

    //Input: A string for name and 3 ints where y is the year, m is the month, and d is for day
    //Output: None
    Workday(const std::string &name, int y, int m, int d);

    Workday(const Workday &rhs) = default;
    Workday &operator=(const Workday &rhs) = default;
    Workday &operator=(Workday &&rhs) = default;
    Workday(Workday &&rhs) = default;
    virtual ~Workday() = default;

    //Input: A event object
    //Output: a bool that represents wether or not the first object is smaller than the second object
    bool operator<(const Event &rhs) const;

    //Input: A string for date that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow 
    //Output: a bool that represents wether or not the first object is smaller than the date string
    bool operator<(const std::string &rhs) const;

    //Input: A Priority_Event object
    //Output: a bool that represents wether or not the first object is smaller than the priority_event
    bool operator<(const Priority_Event &rhs) const;

    //Input: A Workday object
    //Output: a bool that represents wether or not the first object is smaller than the workday object
    bool operator<(const Workday &rhs) const;

    //Input: None
    //Output: The a string that is the name of the object 
    std::string GetName() const;

    //Input: none
    //Output: The pay variable
    double GetPay() const;
};

std::ostream& operator<<(std::ostream &out, const Workday &rhs);


#endif /* WORKDAY_H_INCLUDED */