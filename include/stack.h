#define STACKSIZE 64	// Stack depth

/*! \file stack.h
 *  stack declaration
*/


//! Stack class
/*!
*/
class Stack {

public:
    Stack();
    ~Stack();
    char *Pop();
    int Push( char *s );
    int GetDepth( void );
    
protected:
    char **top;
    char **bottom;
    int aDepth, mDepth;
};
