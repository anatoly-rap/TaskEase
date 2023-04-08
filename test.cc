#include "Schedule.h"
#include "Event.h"
#include "Schedule.h"       // I meant to do that.
#include "Event.h"
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

int main() {
    cout << boolalpha;  // need this for several things
    Schedule s;
    ifstream in("data");
    try {
        s.read(in);
    }
    catch (const exception &e) {
        cout << "Caught: " << e.what() << '\n';
    }
    // That stream should now be failed, but not at eof:
    cout << "fail: " << in.fail() << " eof: " << in.eof() << '\n';

    stringstream iss("today");
    s.read(iss);
    auto e = s[0];
    cout << "Oldest: |" << e << "|"
         << " year=" << e.year() << " month=" << e.month()
         << " day=" << e.day() << '\n';
    cout << "size=" << s.size() << " empty=" << s.empty() << '\n' << s;
    s.clear();
    cout << "size=" << s.size() << " empty=" << s.empty() << '\n' << s;
    s.clear();
    cout << "size=" << s.size() << " empty=" << s.empty() << '\n' << s;

    // A poor implementation might have altered cout’s fill character:
    cout << left << setw(15) << "All done." << '\n';


    // Event objects, independent of Scheduler. 
    Event event1("1972.100");
    cout << "Year-Day format event: " << event1 << '\n';

    auto day1 = event1.day();
    cout  << "testing Event1 properties day: " <<  day1 << '\n';

    auto mont1 = event1.month();
    cout  << "testing Event1 properties month: " <<  mont1 << '\n';
    
    auto year1 = event1.year();
    cout  << "testing Event1 properties year: " <<  year1 << '\n';

    cout << "------------now testing Event copy: first copy via constructor, then by = method -------------" << '\n';

    Event eventK(event1);
    assert(event1 == eventK);
    cout << "constructor copy passed " << '\n';

    Event eventEQ = eventK;
    assert(eventEQ == eventK);

    cout<< " == passed" << '\n';

    eventEQ.set(1956,2,5);

    cout << "check new set values..." <<  '\n';

    auto yearEQ = eventEQ.year();
    auto dayEQ = eventEQ.day();
    auto monthEQ = eventEQ.month();

    cout << "new year val: " << yearEQ << '\n';
    cout << "new day val: " << dayEQ << '\n';
    cout << "new month val: " << monthEQ << '\n';


    cout << "now the program should exit due to failed assertion" << '\n';
    assert(eventEQ == eventK);



    // testing ISO format
    Event event2("1998-02-23");
    cout << "ISO format event: " << event2 << '\n';

    Event event3("1996.120");
    cout << "YEAR.DAY format event: " << event3 << '\n';

    Event event4("today");
    cout << "relative TODAY format event: " << event4 << '\n';

    Event event5("tomorrow");
    cout << "relative TOMORROW format event: " << event5 << '\n';

    Event event6("yesterday");
    cout << "relative YESTERDAY format event: " << event6 << '\n';


    //additional tests:




    return 0;
}
