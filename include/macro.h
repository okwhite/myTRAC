#ifndef __MACRO
#define __MACRO

#include <cstdio>
#include <iostream>
using namespace std;

#define CMD_BUF 2048

/*! \file macro.h
 *  TRAC's built-in macros implementation
*/

/* AUXILIARY FUNCTIONS */
/***************************************************************************/
//!
/*!  get_arg  - "get next argument of TRAC's macro"
*/
String get_arg(void)
{
    String arg;

    if ( (arg = args1->Pop()) == NULL )
    {
        arg = (String)"";
    }
    return arg;
}

/* INPUT/OUTPUT */
/***************************************************************************/
//!
/*!  _rs_  - "read string"
*/
String _rs_( void )
{
    String val;
    String ptr;
    int c;

    ptr = val = new char[CMD_BUF];
    while ( ((c = getchar()) != EOF) && (c != PRG_END) )
    {
        *ptr = c;
        ++ptr;
    }
    if( c == EOF) {
        *ptr = PRG_END;
        ++ptr;
        *ptr = '#';
        ++ptr;
        *ptr = '(';
        ++ptr;
        *ptr = 'b';
        ++ptr;
        *ptr = 'y';
        ++ptr;
        *ptr = 'e';
        ++ptr;
        *ptr = ')';
        ++ptr;
        *ptr = PRG_END;
        ++ptr;
    }
    *ptr = '\0';
    // To ignore characters after PRG_END in input buffer
//    while ((c = getchar()) != '\n' && c != EOF);

//    cout << "The program ended\n";

    return val;
}

/***************************************************************************/
//!
/*!  _rc_  - "read character"
*/
String _rc_( void )
{
    char *val;
    int c;

    val = new char[2];
    val[0] = val[1] = '\0';
    if ( (c = getchar()) != EOF)
        *val = c;

    return val;
}

/***************************************************************************/
//!
/*!  _ps_ - "print string"
*/
String _ps_( void )
{
    String arg;

    arg = get_arg();
    if(*arg != '\0')
        cout << arg;

    return (String)"";
}

/* INTEGER ARITHMETIC */
/***************************************************************************/
//!
/*!  _add_ - "add (arg1+arg2)"
*/
String _add_( void )
{
    String arg1, arg2;
    int res;
 
    arg1 = get_arg();
    arg2 = get_arg();
    res = stoi(arg1)+stoi(arg2);
    
    itoa(res, arg1, 10);
    return arg1;
}

/***************************************************************************/
//!
/*!  _mul_ - "mul (arg1*arg2)"
*/
String _mul_( void )
{
    String arg1, arg2;
    int res;
 
    arg1 = get_arg();
    arg2 = get_arg();
    res = stoi(arg1)*stoi(arg2);
    
    itoa(res, arg1, 10);
    return arg1;
}

/***************************************************************************/
//!
/*!  _sub_ - "sub (arg1-arg2)"
*/
String _sub_( void )
{
    String arg1, arg2;
    int res;
 
    arg1 = get_arg();
    arg2 = get_arg();
    res = stoi(arg1)-stoi(arg2);
    
    itoa(res, arg1, 10);
    return arg1;
}

/***************************************************************************/
//!
/*!  _div_ - "div (arg1/arg2)"
*/
String _div_( void )
{
    String arg1, arg2;
    int res;
 
    arg1 = get_arg();
    arg2 = get_arg();
    res = stoi(arg1)/stoi(arg2);
    
    itoa(res, arg1, 10);
    return arg1;
}

/* SERVICES */
/***************************************************************************/
//!
/*!  _cm_ - "change meta character (the end-of-string character)"
*/
String _cm_( void )
{
    String arg;

    arg = get_arg();
    if ( *arg != '\0')
        PRG_END = *arg;
//cout << "meta-symbol = " << PRG_END << endl;
    return (String)"";
}

/***************************************************************************/
//!
/*!  _meta_ - "return current meta character"
*/
String _meta_( void )
{
    char *meta;
    meta = new char[2];
    meta[0] = meta[1] = '\0';
    *meta = PRG_END;
//cout << "meta-symbol = " << meta << endl;
    return (String)meta;
}

/* FORMS */
/***************************************************************************/
//!
/*!  _ds_ - "define string"
*/
String _ds_( void )
{
    String formname, formbody;
    Form *form;

    formname = get_arg();
    formbody = get_arg();
    form = new Form(formname, formbody);

    // Add the new form to the list
    forms->KillForm(formname);	// Prevent form name duplication
    forms->AddForm(form);
//cout << "_ds_(): " << "form=" << form << "\n";
//cout << "_ds_(): " << "form->name=" << form->gName() << "\n";
//cout << "_ds_(): " << "&form->body=" << &form->body << "\n";
//cout << "_ds_(): " << "form->body=" << form->gBody() << "\n";
 
    return (String)"";
}

/***************************************************************************/
//!
/*!  _ss_ - "segment string"
*/
String _ss_( void )
{
    return (String)"";
}

/***************************************************************************/
//!
/*!  _dd_ - "delete definition"
*/
String _dd_( void )
{
    return (String)"";
}

/***************************************************************************/
//!
/*!  _pf_ - "print form"
*/
String _pf_( void )
{
    Form *form;
    String formname;

    formname = get_arg();
//cout << "_pf_(): " << "formname=" << formname << "\n";

    if (formname != NULL) {
	form = forms->GetForm(formname);
//cout << "_pf_(): " << form << "=GetForm(" << formname << ")\n";
	if (form != (Form *)NULL) {
//		cout << form << "->ptr=" << form->ptr << "\n";
//		cout << "&" << form << "->body=" << &form->body << "\n";
		cout << form->gBody();
//		cout << "_pf_(): " << form << "->name=" << form->gName() << "\n";
	}
    }
 
    return (String)"";
}

/***************************************************************************/
//!
/*!  _da_ - "delete all"
*/
String _da_( void )
{
    delete forms;
    return (String)"";
}

static String list_of_forms = NULL;

/***************************************************************************/
//!
/*!  _ln_ - "list names"
*/
String _ln_( void )
{
    String delimiter;

    if (list_of_forms != NULL) delete list_of_forms;

    delimiter = get_arg();
    if (*delimiter == '\0') delimiter = (String)" ";

    list_of_forms = forms->GetList(delimiter);
    return list_of_forms;
}

/* 'MACRO' "" */
/***************************************************************************/
//!
/*!  _null_  - ""
*/
String _null_( void )
{
    return (String)"";
}

#endif  //__MACRO
