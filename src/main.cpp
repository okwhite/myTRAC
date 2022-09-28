#include "../include/version.h"

/*! \file main.cpp
*/

extern void InitTRAC(void);
extern void RunTRAC(void);
extern void KillTRAC(void);

int main()
{
    StartMsg();
    InitTRAC();
    RunTRAC();
    KillTRAC();
    StopMsg();
}
