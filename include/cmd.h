#include <stdio.h>
#include "flib.h"
#include <iostream>
#define CMD_BUF 2048

/*! \file cmd.h
 *  TRAC's built-in commands implementation
*/

/* AUXILIARY FUNCTIONS */
/***************************************************************************/
//!
/*!  get_arg  - "get next argument of TRAC's function"
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
    char *val, *ptr;
    int c;

    ptr = val = new char[CMD_BUF];
    while ( ((c = getchar()) != EOF) && (c != PRG_END) )
    {
        *ptr = c;
        ++ptr;
    }
    *ptr = '\0';
    // To ignore characters after PRG_END in input buffer
//    while ((c = getchar()) != '\n' && c != EOF);

//    std::cout << "The program ended\n";

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
    std::cout << arg;

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
//std::cout << "_pf_(): " << "formname=" << formname << "\n";

    if (formname != NULL) {
	form = forms->GetForm(formname);
//std::cout << "_pf_(): " << form << "=GetForm(" << formname << ")\n";
	if (form != (Form *)NULL) {
//		std::cout << form << "->ptr=" << form->ptr << "\n";
//		std::cout << "&" << form << "->body=" << &form->body << "\n";
		std::cout << form->gBody();
//		std::cout << "_pf_(): " << form << "->name=" << form->gName() << "\n";
	}
    }
 
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
    res = std::stoi(arg1)+std::stoi(arg2);
    
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
    res = std::stoi(arg1)*std::stoi(arg2);
    
    itoa(res, arg1, 10);
    return arg1;
}

/* SERVICES */
/***************************************************************************/
//!
/*!  _cm_ - "change the meta-symbol (the end-of-string symbol)"
*/
String _cm_( void )
{
    String arg;

    arg = get_arg();
    if ( *arg != '\0')
        PRG_END = *arg;

    return (String)"";
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
//std::cout << "_ds_(): " << "form=" << form << "\n";
//std::cout << "_ds_(): " << "form->name=" << form->gName() << "\n";
//std::cout << "_ds_(): " << "&form->body=" << &form->body << "\n";
//std::cout << "_ds_(): " << "form->body=" << form->gBody() << "\n";
 
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

/* 'COMMAND' "" */
/***************************************************************************/
//!
/*!  _null_  - ""
*/
String _null_( void )
{
    return (String)"";
}
