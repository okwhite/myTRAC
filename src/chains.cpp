#include <cstdlib>
#include <cstring>
#include <iostream>
#include "../include/chains.h"
using namespace std;

/*! \file chains.cpp
 *  Chains implementation
*/

/************************************************************************/
//! Constructor
/*!
*/
Active::Active( void ) {
    begin = new char[CHAINMEM];
    ptr = begin + CHAINMEM;
    mLength = CHAINMEM;
    aLength = 0;
};

/************************************************************************/
//! Constructor
/*!
*/
Active::Active( const char *s ) {
    int len;

    len = strlen( s );
    begin = new char[CHAINMEM];
    if ( (s != NULL) && (len > 0) ) {
        if ( len > CHAINMEM )
            len = 0;
        ptr = begin + CHAINMEM - len;
        mLength = CHAINMEM;
        aLength = len;
        memcpy( ptr, s, len );
    } else {
        ptr = begin + CHAINMEM;
        mLength = CHAINMEM;
        aLength = 0;
    }
};

/************************************************************************/
//! Destructor
/*!
*/
Active::~Active( void ) {
    if ( begin != NULL )
        delete begin;
};

/************************************************************************/
//! Write string
/*!
*/
int Active::Write( char *s, int len ) {
    if ( len > (mLength - aLength) ) {
        len = mLength - aLength;
    }
    if ( (s != NULL) && (len > 0) ) {
        ptr -= len;
        aLength += len;
        memcpy( ptr, s, len );
        return len;
    } else {
        return 0;
    }
};

/************************************************************************/
//! Read string
/*!
*/
int Active::Read( char *&s ) {
    if ( s != NULL ) {
        s = ptr;
    }
    return aLength;
};

/************************************************************************/
//! Delete string
/*!
*/
void Active::Del( int len ) {
    if ( len > aLength )
        len = aLength;
    if ( len < 1 )
        return;
    memcpy( ptr, ptr+len, aLength);
    aLength -= len;
    return;
};

/************************************************************************/
//! Expression length
/*!
*/
int Active::ExprLength( void ) {
    char *p = ptr;
    int nest = 1;
    int len = 0;
    while ( (nest > 0) && (len < aLength) ) {
        if ( *p == ')' ) {
            if ( --nest ) { len++; p++; };
        } else {
            if ( *p == '(' ) {
                nest++; len++; p++;
            } else {
                len++; p++;
            }
        }
    };
    if ( nest == 0 )
        return (len);
    else
        return (-1);
};

/************************************************************************/
//! Print chain to console
/*!
*/
void Active::Print( void ) {
    if ( aLength > 0 ) {
        char *buff = new char[aLength+1];
        char *bp = buff;
        for ( int i = 0; i < aLength; i++ ) {
            *(bp++) = *(ptr + i);
        };
        *bp = '\0';
        cout << buff;
        delete buff;
    };
    cout << "\n";
    return;
};

/************************************************************************/
//! Get length
/*!
*/
int Active::GetLength( void ) {
    return aLength;
};

/************************************************************************/
//! Constructor
/*!
*/
Neutral::Neutral( void ) {
    begin = new char[CHAINMEM];
    ptr = begin;
    mLength = CHAINMEM;
    aLength = 0;
};

/************************************************************************/
//! Destructor
/*!
*/
Neutral::~Neutral( void ) {
    if ( begin != NULL )
        delete begin;
};

/************************************************************************/
//! Write string
/*!
*/
int Neutral::Write( char *s, int len ) {
    if ( len > (mLength - aLength) )
        len = mLength - aLength;
    if ( (s == NULL) || (len < 1) )
        return 0;
    memcpy( ptr, s, len );
    ptr += len;
    aLength += len;
    return len;
};

/************************************************************************/
//! Write character
/*!
*/
int Neutral::Write( char c ) {
    if ( mLength > aLength ) {
	*ptr = c;
        ptr++;
        aLength++;
        return 1;
    } else {
        return 0;
    }
};

/************************************************************************/
//! Get ptr
/*!
*/
char *Neutral::GetPtr( void ) {
    return ptr;
};

/************************************************************************/
//! Cut chain
/*!
*/
void Neutral::Cut( char *p ) {
    char *wp;

    ptr = p;
    for ( aLength = 0,wp = begin; wp < ptr; aLength++,wp++ );
};

/************************************************************************/
//! Print chain to console
/*!
*/
void Neutral::Print( void ) {
    if ( aLength > 0 ) {
        char *buff = new char[aLength+1];
        char *bp = buff;
        for ( int i = 0; i < aLength; i++ ) {
            if ( *(begin + i) != '\0' )
                *(bp++) = *(begin + i);
        };
        *bp = '\0';
        cout << buff;
        delete buff;
    };
    cout << "\n";
    return;
};
