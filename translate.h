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


bool calRange(std::string year);
bool tfleap(int year);
bool isYearDayFormat(const std::string& input);
void beautifyDates(std::vector<int> datesInfo, std::string format);
bool isRelativeDate(std::string input);
void getfformat(std::string day, std::string fflagFormat);
void TodDay(std::string day);
std::vector<int> toDayParser(std::string day);
std::string removeZeros(std::string str);
bool checkDate(std::string line);
bool isValidDay(std::vector<int> elems);
std::vector<int> getDate(int year, int days);
std::map<std::string, bool> find_year_types(const std::string& input);
int days_since_start_of_year(int year, int month, int day);
void VecBeutifyDates(std::vector<int> datesar);
void ISO8601(std::vector<int> daysInfo);
bool isIso8601(const std::string& str);
std::vector<int> parse_date(std::string line);
bool isLeapYear(int year);
bool isValidDate(int year, int month, int day);
std::string trim(const std::string& str);

#endif
