#include "Schedule.h"
#include "Event.h"
#include "Schedule.h"       // I meant to do that.
#include "Event.h"
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

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

    stringstream iss("   tomoRRow  ");
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


    
    Event event1("1972.100");
    cout << "Year-Day format event: " << event1 << '\n';

    // testing ISO format
    Event event2("1998-02-23");
    cout << "ISO format event: " << event2 << '\n';
    return 0;
}