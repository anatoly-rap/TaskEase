#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>
#include <vector>
#include <iosfwd>
#include<algorithm>
#include "Event.h"

class Schedule {
public:
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
// Output operator for Schedule
std::ostream& operator<<(std::ostream& os, const Schedule& schedule);

#endif
