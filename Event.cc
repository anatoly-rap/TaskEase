#include "Event.h"
#include "translate.h"
#include <ctime>
#include<iostream>
#include<iomanip>
using namespace std;

Event::Event(const char* date){

std::string str_date = std::string(date);
    str_date = trim(str_date);
    if (str_date.empty()) {
        throw runtime_error("./HW5: Empty date string");
    }
    if(isYearDayFormat(str_date)){
        string delimiter = ".";
        string year = removeZeros(str_date.substr(0,str_date.find(delimiter)));
        string days = removeZeros(str_date.substr(str_date.find(delimiter) + 1, str_date.back()));
        if(!calRange(year)){
            throw runtime_error(string("./HW5: Invalid Year - Out of Range: ") + str_date);
        }else if(checkDate(year) && checkDate(days)){
            int Intyear, Intday;
            Intyear = stoi(year);
            Intday = stoi(days);
            vector<int> tokens = getDate(Intyear,Intday);
            if(isValidDay(tokens)){
                set(tokens[3],tokens[1], tokens[2]);
            }else{
                throw runtime_error(string("./HW5: Invalid Day Range: ") + str_date);
            }
        }else{
            throw runtime_error(string("./HW5: Invalid year.day Format: ") + str_date);
        }
    }else if(isRelativeDate(str_date)){
        vector<int> dat  = toDayParser(str_date);
        set(dat[0], dat[1], dat[2]);
    }else if(isIso8601(str_date)){

        vector<int> datesVector = parse_date(str_date);
        string Year_str = to_string(datesVector[3]);
        if(!calRange(Year_str)){
            //if not in 0 <= year <= 9999
            throw runtime_error(string("./HW5: Invalid Year - Out of Range: ") + Year_str);
        }else{
                if(isValidDate(datesVector[3], datesVector[1], datesVector[2])){
                    set(datesVector[3],datesVector[1],datesVector[2]);
                }else{
                    throw runtime_error(string("./HW5: Invalid Date Range- Leap Year values used for non-Leap year: ") + str_date);
                }
            }
    }else{
        throw runtime_error(string("./HW5: Invalid data format: ") + str_date);
    }
}
Event::Event(const string& date):Event(date.c_str()){
    if(isYearDayFormat(date)){
        string delimiter = ".";
        string year = removeZeros(date.substr(0,date.find(delimiter)));
        string days = removeZeros(date.substr(date.find(delimiter) + 1, date.back()));
        if(!calRange(year)){
            throw runtime_error(string("HW5: Invalid date format: ") + date);
        }else if(checkDate(year) && checkDate(days)){
            int Intyear, Intday;
            Intyear = stoi(year);
            Intday = stoi(days);
            vector<int> tokens = getDate(Intyear,Intday);
            if(isValidDay(tokens)){
                set(tokens[3],tokens[1], tokens[2]);
            }else{
                throw runtime_error(string("HW5: Invalid date format: ") + date);
            }
        }else{
            throw runtime_error(string("HW5: Invalid date format: ") + date);
        }
    }else if(isRelativeDate(date)){
        vector<int> dat  = toDayParser(date);
        set(dat[0], dat[1], dat[2]);
    }else if(isIso8601(date)){
        vector<int> datesVector = parse_date(date);
        string Year_str = to_string(datesVector[3]);
        if(!calRange(Year_str)){
            //if not in 0 <= year <= 9999
            throw runtime_error(string("./HW5: Invalid Year - Out of Range: ") + Year_str);
        }else{
                if(isValidDate(datesVector[3], datesVector[1], datesVector[2])){
                    set(datesVector[3],datesVector[1],datesVector[2]);
                }else{
                    throw runtime_error(string("./HW5: Invalid Date Range- Leap Year values used for non-Leap year: ") + date);
                }
            }
    }else{
        throw runtime_error(string("./HW5: Invalid date format: ") + date);
    }
}

Event::Event(const Event& other){
    set(other.year(), other.month(), other.day());
}

Event& Event::operator=(const Event& other){
    set(other.year(), other.month(), other.day());
    return *this;
}

Event::~Event() {}

void Event::set(int year, int month, int day) {
    if (!isValidDate(year, month, day)) {
        throw runtime_error(string("HW5: Invalid date: ") + to_string(year) + "-" + to_string(month) + "-" + to_string(day));
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
