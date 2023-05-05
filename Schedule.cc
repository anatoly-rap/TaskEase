#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "Schedule.h"
using namespace std;

//Schedule implementation

Schedule::Schedule() {}

Schedule::Schedule(const string& filename){
    ifstream file(filename);
  if(file.is_open()){
    read(file);
  }
}

Schedule::Schedule(istream& is){
  read(is);
}

Schedule::Schedule(const Schedule& other):events_(other.events_) {}

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

//Schedule iterator implementation

Schedule::iterator::iterator():schedule_(nullptr), index_(0) {}

Schedule::iterator::iterator(const iterator& other):
    schedule_(other.schedule_), index_(other.index_) {}

Schedule::iterator::iterator(Schedule* schedule, std::size_t index) :
    schedule_(schedule), index_(index) {}

// Increment operators
Schedule::iterator& Schedule::iterator::operator++() {
    index_++;
    return *this;
}

Schedule::iterator Schedule::iterator::operator++(int) {
    iterator tmp(*this);
    operator++();
    return tmp;
}

// Decrement operators
Schedule::iterator& Schedule::iterator::operator--() {
    index_--;
    return *this;
}

Schedule::iterator Schedule::iterator::operator--(int) {
    iterator tmp(*this);
    operator--();
    return tmp;
}

// Dereference operator
const Event& Schedule::iterator::operator*() const {
    return schedule_->events_[index_];
}

// Comparison operators
bool Schedule::iterator::operator==(const iterator& other) const {
    return schedule_ == other.schedule_ && index_ == other.index_;
}

bool Schedule::iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

Schedule::iterator Schedule::begin() {
    return Schedule::iterator(this, 0);
}

Schedule::iterator Schedule::end() {
    return Schedule::iterator(this, events_.size());
}

//const iterator implementation

Schedule::const_iterator::const_iterator()
    : schedule_(nullptr), index_(0) {}

Schedule::const_iterator::const_iterator(const const_iterator& other)
    : schedule_(other.schedule_), index_(other.index_) {}

Schedule::const_iterator::const_iterator(const Schedule* schedule, std::size_t index)
    : schedule_(schedule), index_(index) {}

Schedule::const_iterator& Schedule::const_iterator::operator++() {
    ++index_;
    return *this;
}

Schedule::const_iterator Schedule::const_iterator::operator++(int) {
    const_iterator result(*this);
    ++(*this);
    return result;
}

Schedule::const_iterator& Schedule::const_iterator::operator--() {
    --index_;
    return *this;
}

Schedule::const_iterator Schedule::const_iterator::operator--(int) {
    const_iterator result(*this);
    --(*this);
    return result;
}

const Event& Schedule::const_iterator::operator*() const {
    return schedule_->events_[index_];
}

bool Schedule::const_iterator::operator==(const const_iterator& other) const {
    return schedule_ == other.schedule_ && index_ == other.index_;
}

bool Schedule::const_iterator::operator!=(const const_iterator& other) const {
    return !(*this == other);
}

Schedule::const_iterator Schedule::begin() const {
    return Schedule::const_iterator(this, 0);
}

Schedule::const_iterator Schedule::end() const {
    return Schedule::const_iterator(this, events_.size());
}

Schedule::const_iterator::operator iterator() const {
    return Schedule::iterator(const_cast<Schedule*>(schedule_), index_);
}
