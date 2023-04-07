#ifndef MAIN_H
#define MAIN_H
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <map>
#include <functional>
#include <iostream>
using namespace std;

bool calRange(string year);
bool tfleap(int year);
bool isYearDayFormat(const string& input);
void beautifyDates(vector<int> datesInfo, string format);
bool isRelativeDate(string input);
void getfformat(string day, string fflagFormat);
void TodDay(string day);
vector<int> toDayParser(string day);
string removeZeros(string str);
bool checkDate(string line);
bool isValidDay(vector<int> elems);
vector<int> getDate(int year, int days);
map<string, bool> find_year_types(const string& input);
int days_since_start_of_year(int year, int month, int day);
void VecBeutifyDates(vector<int> datesar);
void ISO8601(vector<int> daysInfo);
bool isIso8601(const std::string& str);
vector<int> parse_date(string line);
bool isLeapYear(int year);
bool isValidDate(int year, int month, int day);
string trim(const string& str);



#endif
