#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <iostream>
#include <vector>

class Event {
public:
    explicit Event(const char* date);
    explicit Event(const std::string& date);
    Event(const Event& other);
    Event& operator=(const Event& other);
    ~Event();
    std::string fmt(const std::string& format = "%Y-%m-%d") const;
    Event& operator++(); 
    Event operator++(int);
    Event& operator--();
    Event operator--(int);
    bool operator==(const Event& other) const;
    bool operator!=(const Event& other) const;
    bool operator<=(const Event& other) const;
    bool operator>=(const Event& other) const;
    bool operator<(const Event& other) const;
    bool operator>(const Event& other) const;
    void set(int year, int month, int day);
    int year() const;
    int month() const;
    int day() const;
    std::string toString() const;
private:
    int m_year;
    int m_month;
    int m_day;
    void parseDate(const std::string& date);
};
std::ostream& operator<<(std::ostream& os, const Event& event);
#endif // EVENT_H
