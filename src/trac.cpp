#include <cstdlib>
#include <cstring>
#include <iostream>
#include "../include/mytypes.h"
#include "../include/chains.h"
#include "../include/stack.h"
#include "../include/forms.h"
#include "../include/TRAC.h"
#include "../include/flib.h"
#include "../include/macro.h"
using namespace std;

/*! \file trac.cpp
 *  TRAC engine algorithm
*/

/***************************************************************************/
//!
/*!  ClearProcessor
*/
void ClearProcessor( void ) {
    if ( aChain != NULL)
        delete aChain;
    if ( nChain != NULL)
        delete nChain;
    if ( args != NULL)
        delete args;
    if ( args1 != NULL)
        delete args1;
    aChain = new Active( "#(ps,(CR-LF))#(ps,#(rs))" );
    nChain = new Neutral();
    args = new Stack();
    args1 = new Stack();
};

/***************************************************************************/
//!
/*!  InitTRAC
*/
void InitTRAC( void ) {
    ClearProcessor();
    if ( forms != NULL)
        delete forms;
    forms = new Forms();
    for ( int i = 0; i < MACRO_COUNT; i++) {
        mnem[i] = (String)"";
        impl[i] = _null_;
    }
    int k = 0;
    mnem[k] = (String)"rs";
    impl[k] = _rs_;
    k++;
    mnem[k] = (String)"ps";
    impl[k] = _ps_;
    k++;
    mnem[k] = (String)"pf";
    impl[k] = _pf_;
    k++;
    mnem[k] = (String)"rc";
    impl[k] = _rc_;
    k++;
    mnem[k] = (String)"cm";
    impl[k] = _cm_;
    k++;
    mnem[k] = (String)"meta";
    impl[k] = _meta_;
    k++;
    mnem[k] = (String)"ds";
    impl[k] = _ds_;
    k++;
    mnem[k] = (String)"ss";
    impl[k] = _ss_;
    k++;
    mnem[k] = (String)"dd";
    impl[k] = _dd_;
    k++;
    mnem[k] = (String)"da";
    impl[k] = _da_;
    k++;
    mnem[k] = (String)"ln";
    impl[k] = _ln_;
    k++;
    mnem[k] = (String)"add";
    impl[k] = _add_;
    k++;
    mnem[k] = (String)"+";
    impl[k] = _add_;
    k++;
    mnem[k] = (String)"mul";
    impl[k] = _mul_;
    k++;
    mnem[k] = (String)"*";
    impl[k] = _mul_;
};

/***************************************************************************/
//!
/*!  KillTRAC
*/
void KillTRAC( void ) {
    if ( aChain != NULL)
        delete aChain;
    if ( nChain != NULL)
        delete nChain;
    if ( forms != NULL)
        delete forms;
    if ( list_of_forms != NULL)	// defined in macro.h
        delete list_of_forms;
    if ( args != NULL)
        delete args;
    if ( args1 != NULL)
        delete args1;
};

/***************************************************************************/
//!
/*!  GetMacroImpl
*/
int GetMacroImpl( String mn ) {
    int retVal = -1;
    int r;

    for ( int i = 0; i < MACRO_COUNT; i++) {
        if ( (r = strcmp( mn, mnem[ i ])) == 0 ) {
            retVal = i;
            break;
        }
    }

    return retVal;
};

/***************************************************************************/
//!
/*!  Eval
*/
int Eval( char *&val ) {
    String macroMnem;
    int valLength, r;
    int macroImpl;

    val = (char *)"";
    valLength = 0;

    // TODO: FORMs processing

    // a built-in macro executing
    if ( (macroMnem = args1->Pop()) != NULL ) {
        if ( (macroImpl = GetMacroImpl( macroMnem ) ) != (-1) ) {
            val = (impl[ macroImpl ])();
            valLength = (val != NULL) ? strlen( val ) : 0;
        } else if ( (r = strcmp( macroMnem, "bye")) == 0 ) {
            valLength = -1;
        }
    }
    delete args1;
    args1 = new Stack();
    return valLength;
}

/***************************************************************************/
//!
/*!  RunTRAC
*/
void RunTRAC( void ) {
    char *ch = (char *)"";  // current position in Active chain
    char *buff = (char *)"";
    char *ptr1, *ptr2;
    char *value;
    int vlen, el;

    step1:
//cout << "step1:\n";
    ClearProcessor();
    step2:
//aChain->Print();
//nChain->Print();
    if ( aChain->Read( ch ) == 0 )
        goto step1;	// Active chain is empty
//    step3:
    if ( (*ch == '\t') || (*ch == '\n') || (*ch == '\r') ) {
        aChain->Del( 1 );
	goto step2;
    };
//    step4:
    if ( *ch == '(' ) {
        aChain->Del( 1 );
        if ( (el = aChain->ExprLength()) > -1 ) {
            aChain->Read( buff );
            if ( strncmp(buff, CRLF, el) == 0 )
                nChain->Write( '\n' );
            else
                nChain->Write( buff, el );
            aChain->Del( el + 1 );
            goto step2;
        }
        else
            goto step1;
    };
//    step5:
    if ( *ch == ',' ) {	// Next argument
        aChain->Del( 1 );
        // each argument in neutral chain ends by '\0'
        nChain->Write( '\0' );
        if ( args->Push( nChain->GetPtr() ) == -1 ) {
            cout << "Stack 'args' overflow.\n";
            nChain->Print();
            goto step1;
        }
        if ( args->Push( argument ) == -1 ) {
            cout << "Stack 'args' overflow.\n";
            nChain->Print();
            goto step1;
        }
        else
            goto step2;
    };
//    step6:
    // Active function
    if ( (*ch == '#') && (*(ch + 1) == '(') ) {
        aChain->Del( 2 );
        // each argument in neutral chain ends by '\0'
//        nChain->Write( '\0' );
        if ( args->Push( nChain->GetPtr() ) == -1 ) {
            cout << "Stack 'args' overflow.\n";
            nChain->Print();
            goto step1;
        }
        if ( args->Push( activeFn ) == -1 ) {
            cout << "Stack 'args' overflow.\n";
            nChain->Print();
            goto step1;
        }
        else
            goto step2;
    };
//    step7:
    // Neutral function
    if ( (*ch == '#') && (*(ch + 1) == '#') && (*(ch + 2) == '(') ) {
        aChain->Del( 3 );
        // each argument in neutral chain ends by \0
//        nChain->Write( '\0' );
        if ( args->Push( nChain->GetPtr() ) == -1 ) {
            cout << "Stack 'args' overflow.\n";
            nChain->Print();
            goto step1;
        }
        if ( args->Push( neutralFn ) == -1 ) {
            cout << "Stack 'args' overflow.\n";
            nChain->Print();
            goto step1;
        }
        else
            goto step2;
    };
//    step8:
    if ( *ch == '#' ) {
        nChain->Write( *ch );
        aChain->Del( 1 );
        goto step2;
    };
//    step9:
    if ( *ch == ')' ) {	// The end of function. Evaluate it, please.
//    cout << "step9:\n";
        aChain->Del( 1 );
        // each argument in neutral chain ends by '\0'
        nChain->Write( '\0' );
        ptr1 = ptr2 = NULL;
        while ( (ptr1 != activeFn) && (ptr1 != neutralFn) ) {
            // get argument type
            if ( (ptr1 = args->Pop()) == NULL ) {
                cout << "Stack 'args' is empty\n";
                nChain->Print();
                goto step1;
            }
            // get argument
            if ( (ptr2 = args->Pop()) == NULL ) {
                cout << "Stack 'args' is empty\n";
                nChain->Print();
                goto step1;
            }
            // put argument onto function parameter stack
            if ( args1->Push( ptr2 ) == -1 ) {
                cout << "Stack 'args1' overflow.\n";
                nChain->Print();
                goto step1;
            }
        }

        value = NULL;
        if ( *ptr1 == aFn ) {
            vlen = Eval( value );
            if (vlen < 0)
                return;
            aChain->Write( value, vlen );
            if ( !value )
                free( (void *)value );
            nChain->Cut( ptr2 );
            goto step2;
        }
        if ( *ptr1 == nFn ) {
	        vlen = Eval( value );
            if (vlen < 0)
                return;
            nChain->Cut( ptr2 );
            nChain->Write( value, vlen );
            if ( !value )
                free( (void *)value );
            goto step2;
        } else {
	        goto step1;
        }
    };
//    step10:
//    cout << "step10:\n";
    nChain->Write( *ch );
    aChain->Del( 1 );
    goto step2;
};
