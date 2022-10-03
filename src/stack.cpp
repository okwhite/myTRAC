#include <cstdlib>
#include "../include/stack.h"

/*! \file stack.cpp
 *  Stack implementation
*/

/***********************************************************************/
//! Constructor
/*!
*/
Stack::Stack( void ) {
    bottom = new char *[STACKSIZE];
    top = bottom;
    mDepth = STACKSIZE;
    aDepth = 0;
};

/***********************************************************************/
//! Destructor
/*!
*/
Stack::~Stack( void ) {
    delete bottom;
};

/***********************************************************************/
//! Pop
/*!
*/
char *Stack::Pop( void ) {
    if ( aDepth > 0 ) {
        top--;
        aDepth--;
        return (*top);
    } else {
        return NULL;
    }
};


/***********************************************************************/
//! Push
/*!
*/
int Stack::Push( char *s ) {
    if ( aDepth < mDepth ) {
        *top = s;
        top++;
        aDepth++;
        return 0;
    } else {
        return (-1);
    }
};

/***********************************************************************/
//! GetDepth
/*!
*/
int Stack::GetDepth( void ) {
    return aDepth;
};
