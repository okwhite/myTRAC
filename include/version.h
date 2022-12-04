#include <iostream>
using namespace std;

#define VERSION "0.1.1-alpha"

void StartMsg()
{
    cout << "myTRAC system  (" << VERSION << ") started." << endl;
}

void StopMsg()
{
    cout << "\n\nmyTRAC system stopped.\n\n";
}
