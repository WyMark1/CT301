#ifndef PRIORITY_EVENT_H_INCLUDED
#define PRIORITY_EVENT_H_INCLUDED

#include <iostream>
#include <string>
#include "Event.h"

class Priority_Event : public Event {
  short priority_;
  std::string name_;
  public:
    //Input: None
    //Output: None
    Priority_Event();

    //Input: A string for name
    //Output: None
    Priority_Event(const std::string &name);

    //Input: A string for name and a short for the priority of the object
    //Output: None
    Priority_Event(const std::string &name, short priority);

    //Input: A string for name and a string that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow
    //Output: None
    Priority_Event(const std::string &name, const std::string &date);

    //Input: A string for name and a string that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow and a short for the priority of the object
    //Output: None
    Priority_Event(const std::string &name, const std::string &date, short priority);

    //Input: A string for name and 3 ints where y is the year, m is the month, and d is for day
    //Output: None
    Priority_Event(const std::string &name, int y, int m, int d);

    //Input: A string for name and 3 ints where y is the year, m is the month, and d is for day and a short for the priority of the object
    //Output: None
    Priority_Event(const std::string &name, int y, int m, int d, short priority);

    Priority_Event(const Priority_Event &rhs) = default;
    Priority_Event &operator=(const Priority_Event &rhs) = default;
    Priority_Event &operator=(Priority_Event &&rhs) = default;
    Priority_Event(Priority_Event &&rhs) = default;
    virtual ~Priority_Event() = default;

    //Input: A Event Object
    //Output: a bool that represents wether or not the first object is smaller than the Event object
    virtual bool operator<(const Event &rhs) const;

    //Input: A string for date that is formatted such as yyyy-mm-dd or yyyy-ddd or yesterday, today, tomorrow 
    //Output: a bool that represents wether or not the first object is smaller than the date string
    virtual bool operator<(const std::string &rhs) const;

    //Input: A Priority_Event object
    //Output: a bool that represents wether or not the first object is smaller than the priority_event
    virtual bool operator<(const Priority_Event &rhs) const;

    //Input: None
    //Output: The a string that is the name of the object 
    std::string GetName() const;

    //Input: None
    //Output: the priority of the object
    short GetPriority() const;
};

std::ostream& operator<<(std::ostream &out, const Priority_Event &rhs);

#endif /* PRIORITY_EVENT_H_INCLUDED */