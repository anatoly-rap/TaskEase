#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "Schedule.h"
using namespace std;

Schedule::Schedule() {}
Schedule::Schedule(const string& filename){
    ifstream file(filename);
  if(file.is_open()){
    read(file);
  }
}
Schedule::Schedule(istream& is) {
  read(is);
}
Schedule::Schedule(const Schedule& other) : events_(other.events_) {}

Schedule& Schedule::operator=(const Schedule& other){
  events_ = other.events_;
  return *this;
}
Schedule::~Schedule() {}

void Schedule::read(istream& is){
  string line;
  while (getline(is, line)) {
    istringstream iss(line);
    vector<string> words;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(words));
    for (const auto& word : words) {
      events_.emplace_back(word.c_str());
      sort();
    }
  }
}
void Schedule::clear(){
  events_.clear();
}
size_t Schedule::size() const {
  return events_.size();
}
bool Schedule::empty() const {
  return events_.empty();
}
void Schedule::sort(){
  std::sort(events_.begin(), events_.end(), [](const Event& e1, const Event& e2){
    if(e1.year() < e2.year()){
        return true;
    }else if(e1.year() > e2.year()){
        return false;
    }else if(e1.month() < e2.month()){
        return true;
    }else if(e1.month() > e2.month()){
        return false;
      }else{
        return e1.day() < e2.day();
        }
    });
}
const Event& Schedule::operator[](size_t index) const {
  return events_.at(index);
}
ostream& operator<<(ostream& os, const Schedule& schedule) {
    for (const auto& event : schedule.events_) {
        os << event << '\n';
    }
    return os;
}
