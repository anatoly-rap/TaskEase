#include<vector>
#include<string>
#include<iterator>
#include<iostream>
#include<istream>
#include<getopt.h>
#include <bitset>
#include<limits>
#include <unistd.h>
#include<map>
#include <regex>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string> 
#include <cctype>
#include<cstring>
#define NUL '\0'
using namespace std;

bool calRange(string year){
  int integerYear = stoi(year);
  if(1 <= integerYear && integerYear<= 9999){
    return true;
  }else{
    return false;
  };
}
bool tfleap(int year){
    if (year % 400 == 0) {
        return true;
    }else if (year % 100 == 0) {
        return false;
    }else if (year % 4 == 0) {
        return true;
    }else {
        return false;
    }
}
bool isYearDayFormat(const string& input) {
    istringstream ss(input);
    int year, day;
    char delimiter;
    if(ss >> year >> delimiter && delimiter == '.' && ss >> day) {
        return true;
    }else{
        return false;
    }
}
void beautifyDates(vector<int> datesInfo, string format){
    char* ccx = new char[format.length() + 1];
    copy(format.begin(), format.end(), ccx);
    struct tm tm = {};
    int year = datesInfo[3];
    tm.tm_isdst = -1;
    tm.tm_year = year - 1900;
    tm.tm_mday = datesInfo[0];
    tm.tm_mon = 0;
    mktime(&tm);
    char buffer[80];
    strftime(buffer, sizeof(buffer),ccx, &tm);
    cout << buffer << '\n';
}
bool isRelativeDate(string input){
    transform(input.begin(), input.end(), input.begin(), ptr_fun <int, int> (tolower));
    map<string, bool> relativeDates = {{"today", true},{"yesterday", true},{"tomorrow", true}};
    if(relativeDates.find(input) != relativeDates.end()) {
        return true;
    }else{
        return false;
    }
}
void getfformat(string day, string fflagFormat) {
    char* ccx = new char[fflagFormat.length() + 1];
    copy(fflagFormat.begin(), fflagFormat.end(), ccx);
     time_t now = time(nullptr);
    tm* current_time = localtime(&now);
    if(day == "yesterday"){
        current_time->tm_mday--;
    }else if(day == "today"){
    }else if(day == "tomorrow"){
        current_time->tm_mday++;
    }else{
        cout << "Invalid input!" << endl;
    }
    time_t time = mktime(current_time);
    char date_str[50];
    strftime(date_str, 50, ccx, localtime(&time));
    cout << date_str << '\n';

}
void TodDay(string day){
    time_t now = time(nullptr);
    tm* current_time = localtime(&now);
    if(day == "yesterday"){
        current_time->tm_mday--;
    }else if(day == "today"){
    }else if(day == "tomorrow"){
        current_time->tm_mday++;
    }else{
        cout << "Invalid input!" << endl;
    }
    time_t time = mktime(current_time);
    char date_str[20];
    strftime(date_str, 20, "%a %d %b %Y", localtime(&time));
    cout << date_str << '\n';
}
vector<int> toDayParser(string day){
    time_t now = time(nullptr);
    tm* current_time = localtime(&now);

    if(day == "yesterday") {
        current_time->tm_mday--;
    } else if(day == "tomorrow") {
        current_time->tm_mday++;
    }

    time_t time = mktime(current_time);
    tm* date_time = localtime(&time);
    std::vector<int> date;
    date.push_back(date_time->tm_year + 1900); // tm_year is years since 1900
    date.push_back(date_time->tm_mon + 1); // tm_mon is 0-based
    date.push_back(date_time->tm_mday);
    return date;
}

string removeZeros(string str){
int i = 0;
   while(str[i]=='0' && str.size() > 1){
       i++;
   }
   str.erase(0,i);
   return str;
}
bool checkDate(string line) {
    std::istringstream iss (line);
    float fl;
    iss >> noskipws >> fl;
   return iss.eof() && !iss.fail();
   }
bool isValidDay(vector<int> elems){
    int day = elems[0];
    bool leap = tfleap(elems[3]);
    if(!leap && day == 366){
        return false;
    }else{
    return true;
    }
}
vector<int> getDate(int year, int days){
    vector<int> elements;
    elements.push_back(days);
    int month = 0;
    while(days > 0){
        int dayinMonths = 0;
switch(month){
    case 2:
        if((year % 4 == 0 && year % 100 !=0) || year % 400 == 0){
        dayinMonths = 29;
        }else{
        dayinMonths = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
    dayinMonths = 30;
    break;
    default:
    dayinMonths = 31;
    break;
    }if( days > dayinMonths){
        days -= dayinMonths;
        ++month;
    }else{
    break;
    }
}
    elements.push_back(month);
    elements.push_back(days);
    elements.push_back(year);
    return elements;
}
map<string, bool> find_year_types(const string& input) {
    map<string, bool> year_types;
    year_types["Week-based"] = false;
    year_types["Conventional"] = false;
    size_t week_based_pos = input.find("Week-based");
    if (week_based_pos != string::npos) {
        year_types["Week-based"] = true;
    }
    size_t conventional_pos = input.find("Conventional");
    if (conventional_pos != std::string::npos) {
        year_types["Conventional"] = true;
    }
    return year_types;
}
int days_since_start_of_year(int year, int month, int day) {
  int total_days = 0;
  int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  bool is_leap_year = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
  if (is_leap_year) {
    days_in_month[1] = 29;
  }
  for (int i = 0; i < month - 1; i++) {
    total_days += days_in_month[i];
  }
  total_days += day;
  return total_days;
}

void VecBeutifyDates(vector<int> datesar){
    char format[] = "%a %d %b %04Y";
    struct tm tm = {};
    int year = datesar[3];
    tm.tm_isdst = -1;
    tm.tm_year = year - 1900;
    tm.tm_mday = datesar[0];
    tm.tm_mon = 0;
    mktime(&tm);
    char buffer[50];
    strftime(buffer, sizeof(buffer), format, &tm);
    cout << buffer << '\n';
}
void ISO8601(vector<int> daysInfo){
    struct tm timeinfo = {};
    timeinfo.tm_year = daysInfo[3] - 1900;
    timeinfo.tm_mon = 0;
    timeinfo.tm_mday = daysInfo[0];
    mktime(&timeinfo);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &timeinfo);
    cout << buf << '\n';
}
bool isIso8601(const std::string& str) {
    if (str.length() != 10) {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (str[i] != '-') {
                return false;
            }
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
vector<int> parse_date(string line){
    vector<int> result;
    regex pattern("\\b(\\d{4})-(\\d{2})-(\\d{2})\\b");
            smatch match;
            if(regex_search(line, match, pattern)) {
                int year = stoi(match[1]);
                int month = stoi(match[2]);
                int day = stoi(match[3]);
                result.push_back(1);
                result.push_back(month);
                result.push_back(day);
                result.push_back(year);
            }
    return result;
}
bool isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}
bool isValidDate(int year, int month, int day) {
    int daysInMonth;
    switch (month) {
        case 2:
            daysInMonth = isLeapYear(year) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
            break;
    }
    if (day < 1 || day > daysInMonth) {
        return false;
    }
    return true;
}
string trim(const string& str) {
    // Find the position of the first non-whitespace character
    size_t start = str.find_first_not_of(" \t\n\r\f\v");

    // If the string is all whitespace, return an empty string
    if (start == string::npos) {
        return "";
    }

    // Find the position of the last non-whitespace character
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    // Return the substring between the first and last non-whitespace characters
    return str.substr(start, end - start + 1);
}