#include "Event.h"
#include "translate.h"
#include <ctime>
#include<iostream>
#include<iomanip>
using namespace std;

void Event::parseDate(const string& date){

    if(isYearDayFormat(date)){
        string year = removeZeros(date.substr(0,date.find(".")));
        string days = removeZeros(date.substr(date.find(".") + 1, date.back()));
        if(!calRange(year)){
            throw runtime_error(string("./HW7: Invalid Year - Out of Range: ") + date);
        }else if(checkDate(year) && checkDate(days)){
            int Intyear = stoi(year);
            int Intday = stoi(days);
            vector<int> tokens = getDate(Intyear,Intday);
            if(isValidDay(tokens)){
                set(tokens[3],tokens[1], tokens[2]);
            }else{
                throw runtime_error(string("./HW7: Invalid Day Range: ") + date);
            }
        }else{
            throw runtime_error(string("./HW7: Invalid year.day Format: ") + date);
        }
    }else if(isRelativeDate(date)){
        vector<int> dat  = toDayParser(date);
        set(dat[0], dat[1], dat[2]);
    }else if(isIso8601(date)){
        vector<int> datesVec = parse_date(date);
        string Year_str = to_string(datesVec[3]);
        if(!calRange(Year_str)){
            throw runtime_error(string("./HW7: Invalid Year - Out of Range: ") + Year_str);
        }else{
            if(isValidDate(datesVec[3], datesVec[1], datesVec[2])){
                set(datesVec[3],datesVec[1],datesVec[2]);
            }else{
                throw runtime_error(string("./HW7: Invalid Date Range- Leap Year values used for non-Leap year: ") + date);
                }
            }
    }else{
        throw runtime_error(string("./HW7: Invalid data format: ") + date);
    }
}

Event::Event(const char* date){

std::string str_date = std::string(date);
    str_date = trim(str_date);
    if (str_date.empty()) {
        throw runtime_error("./HW7: Empty date string");
    }
    parseDate(str_date);
}

Event::Event(const string& date):Event(date.c_str()){
    parseDate(date);
}

Event::Event(const Event& other){
    set(other.year(), other.month(), other.day());
}

Event& Event::operator=(const Event& other){
    set(other.year(), other.month(), other.day());
    return *this;
}

Event::~Event() {}

void Event::set(int year, int month, int day){
    if (!isValidDate(year, month, day)){
        throw runtime_error(string("./HW7: Invalid date: ") + to_string(year) + "-" + to_string(month) + "-" + to_string(day));
    }
    m_year = year;
    m_month = month;
    m_day = day;
}

int Event::year() const {
    return m_year;
}
int Event::month() const {
    return m_month;
}
int Event::day() const {
    return m_day;
}

string Event::toString() const {
    ostringstream ss;
    ss << setfill('0') << std::setw(4) << year() << '-'
       << setw(2) << month() << '-'
       << setw(2) << day();
    return ss.str();
}

ostream& operator<<(ostream& os, const Event& event){
    os << event.toString();
    return os;
}

bool Event::operator==(const Event& other) const {
    return (year() == other.year() && month() == other.month() && day() == other.day());
}

bool Event::operator!=(const Event& other) const {
    return !(*this == other);
}

bool Event::operator<=(const Event& other) const {
    if (m_year < other.m_year){
        return true;
    }else if(m_year == other.m_year && m_month < other.m_month){
        return true;
    }else if(m_year == other.m_year && m_month == other.m_month && m_day <= other.m_day) {
        return true;
    }else{
        return false;
    }
}

bool Event::operator>=(const Event& other) const {
    if(m_year > other.m_year){
        return true;
    }else if(m_year == other.m_year && m_month > other.m_month){
        return true;
    }else if(m_year == other.m_year && m_month == other.m_month && m_day >= other.m_day) {
        return true;
    }else{
        return false;
    }
}

bool Event::operator<(const Event& other) const {
    return !(*this >= other);
}

bool Event::operator>(const Event& other) const {
    return !(*this <= other);
}

string Event::fmt(const string& format) const {

    tm timeinfo{};
    timeinfo.tm_year = year() - 1900;
    timeinfo.tm_mon = month() - 1;
    timeinfo.tm_mday = day();
    const char* format_cstr = format.c_str();
    const int bufsize = 64;  
    char buf[bufsize];
    const size_t result = strftime(buf, bufsize, format_cstr, &timeinfo);
    if (result == 0){
        throw runtime_error("HW7: strftime failed");
    }
    return string(buf);
}

Event& Event::operator++() {
    ++m_day;
    if (!isValidDate(m_year, m_month, m_day)) {
        throw runtime_error("./HW7: Invalid date range after incrementing.");
    }
    return *this;
}

Event Event::operator++(int) {
    Event temp = *this;
    ++(*this);
    return temp;
}

Event& Event::operator--() {
    --m_day;
    if (!isValidDate(m_year, m_month, m_day)) {
        throw runtime_error("./HW7: Invalid date range after decrementing.");
    }
    return *this;
}

Event Event::operator--(int) {
    Event temp = *this;
    --(*this);
    return temp;
}
