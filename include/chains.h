#ifndef __CHAINS
#define __CHAINS

#define CHAINMEM	1024	// memory size limit for a chain (characters)


/*! \file chains.h
 *  chains's declaration
*/

//! Chain class
/*!
*/
class Chain {

public:
    Chain() {}
    ~Chain() {}

protected:
    char *begin;
    char *ptr;
    int aLength;	// actual length
    int mLength;	// max length
};


//! Active class
/*!
*/
class Active : public Chain {	// grows from right to left

public:
    Active( void );
    Active( const char * );
    ~Active( void );

    int Write( char *, int );
    int Read( char *& );
    void Del( int );
    int ExprLength( void );
    void Print( void );
    int GetLength( void );
};


//! Neutral class
/*!
*/
class Neutral : public Chain {	// grows from left to right

public:
    Neutral( void );
    ~Neutral( void );

    int Write( char *, int );
    int Write( char );
//    int Read( char *s, int len );
    char *GetPtr( void );
    void Cut( char * );
    void Print( void );
};
#endif  //__CHAINS
