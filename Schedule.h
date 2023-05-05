#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>
#include <vector>
#include <iosfwd>
#include<algorithm>
#include<iterator>
#include "Event.h"

class Schedule {
public:
    class iterator;
    class const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    Schedule();
    explicit Schedule(const std::string& filename);
    explicit Schedule(std::istream& is);
    Schedule(const Schedule& other);
    Schedule& operator=(const Schedule& other);
    ~Schedule();
    void read(std::istream& is);
    void clear();
    std::size_t size() const;
    bool empty() const;
    const Event& operator[](std::size_t index) const;
    void sort();
    friend std::ostream& operator<<(std::ostream& os, const Schedule& schedule);

private:
    std::vector<Event> events_;
};
class Schedule::iterator {
public:
    iterator();
    iterator(const iterator& other);
    iterator(Schedule* schedule, std::size_t index);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    const Event& operator*() const;
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

private:
    Schedule* schedule_;
    std::size_t index_;
};
class Schedule::const_iterator {
public:
    const_iterator();
    const_iterator(const const_iterator& other);
    const_iterator(const Schedule* schedule, std::size_t index);
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
    const Event& operator*() const;
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    operator iterator() const;

private:
    const Schedule* schedule_;
    std::size_t index_;
};
// Output operator for Schedule
std::ostream& operator<<(std::ostream& os, const Schedule& schedule);

#endif
