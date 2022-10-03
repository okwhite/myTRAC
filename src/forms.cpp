#include <cstdlib>
#include <cstring>
#include <iostream>
#include "../include/mytypes.h"
#include "../include/forms.h"
using namespace std;

/*! \file forms.cpp
 *  Form implementation
*/

/************************************************************************/
//! Constructor
/*!
*/
Form::Form( void ) {
    prev = next = (Form *)NULL;
    name = body = ptr = NULL;
};

/************************************************************************/
//! Constructor
/*!
*/
Form::Form( String formname ) {
    int slen;

    prev = next = (Form *)NULL;
    name = body = ptr = NULL;

    if (formname != NULL) {
	slen = strlen(formname);
	name = new char[slen + 1];
        memcpy( name, formname, slen );
	name[slen] = '\0';
    }
};

/************************************************************************/
//! Constructor
/*!
*/
Form::Form( String formname, String formbody) {
    int slen;

    prev = next = (Form *)NULL;
    name = body = ptr = NULL;

    if (formname != NULL) {
	slen = strlen(formname);
	name = new char[slen + 1];
        memcpy( name, formname, slen );
	name[slen] = '\0';
    }

    if (formbody != NULL) {
	slen = strlen(formbody);
	body = new char[slen + 1];
        memcpy( body, formbody, slen );
	body[slen] = '\0';
    }
};

/************************************************************************/
//! Destructor
/*!
*/
Form::~Form( void ) {
    // prev = next = (Form *)NULL;
    // ptr = NULL;
    if ( name != NULL )
	delete name;
    if ( body != NULL )
	delete body;
};

/*
 *  Form Library (list) implementation
*/

/************************************************************************/
//! Get the form's name
/*!
*/
String Form::gName( void ) {
    return name;
}

/************************************************************************/
//! Get the form's body
/*!
*/
String Form::gBody( void ) {
    return body;
}

/************************************************************************/
//! Get the prev ptr
/*!
*/
Form * Form::gPrev( void ) {
    return prev;
}

/************************************************************************/
//! Get the next ptr
/*!
*/
Form * Form::gNext( void ) {
    return next;
}

/************************************************************************/
//! Set the prev ptr
/*!
*/
void Form::sPrev( Form *f ) {
    this->prev = f;
}

/************************************************************************/
//! Set the next ptr
/*!
*/
void Form::sNext( Form *f ) {
    this->next = f;
}

/************************************************************************/
//! Constructor
/*!
*/
Forms::Forms( void ) {
    frmfile = NULL;
    firstform = lastform = (Form *)NULL;
};

/************************************************************************/
//! Constructor
/*!
*/
Forms::Forms( String filename ) {
    frmfile = filename;
    firstform = lastform = (Form *)NULL;
};

/************************************************************************/
//! Destructor
/*!
*/
Forms::~Forms( void ) {
    KillAll();
    if ( frmfile != NULL )
        delete frmfile;
};

/************************************************************************/
//! Add a form to the list 
/*!
*/
void Forms::AddForm( Form *frm ) {
//    cout << "AddForm(): AddForm(" << frm << ")\n";
//    cout << "AddForm():firstform=" << this->firstform << "\n";
//    cout << "AddForm():lastform=" << this->lastform << "\n";

    if (this->firstform == (Form *)NULL) {	// if the list is empty
	cout << "Formlist is empty\n";
	this->firstform = frm;
	this->lastform = this->firstform;
    }
    else {
	this->lastform->sNext(frm);
	frm->sPrev(this->lastform);
	this->lastform = frm;
    }
//    cout << "AddForm(): firstform=" << this->firstform << "\n";
//    cout << "AddForm(): firstform->name=" << this->firstform->gName() << "\n";
//    cout << "AddForm(): firstform->body=" << this->firstform->gBody() << "\n";
//    cout << "AddForm(): lastform=" << this->lastform << "\n";
//    cout << "AddForm(): lastform->name=" << this->lastform->gName() << "\n";
//    cout << "AddForm(): lastform->body=" << this->lastform->gBody() << "\n";
};

/************************************************************************/
//! Get the form pointer
/*!
*/
Form * Forms::GetForm( String fname ) {
    Form *f, *found;
    int r;

//cout << "GetForm(): " << "GetForm(" << fname << ")\n";
    found = (Form *)NULL;
    f = this->firstform;
    while (f != (Form *)NULL) {	// Scan the list of forms
//cout << "GetForm(): " << "f->body=" << f->gBody() << "\n";
//cout << "GetForm(): " << "f=" << f << "\n";
//cout << "GetForm(): " << "f->name=" << f->gName() << "\n";
//cout << "GetForm(): " << "fname=" << fname << "\n";
	if ((r = strncmp(f->gName(), fname, strlen(fname))) == 0) {
		found = f;
		break;
	}
	else
		f = f->gNext();
    }

    return found;
};

/************************************************************************/
//! Remove the form
/*!
*/
void Forms::KillForm( String name ) {
    Form *frm, *nextfrm, *prevfrm;
    int flag;

    flag = 0;
    frm = this->GetForm(name);
    if (frm != (Form *)NULL) {
	if (frm == this->lastform) {
		this->lastform = frm->gPrev();
		if (this->lastform != (Form *)NULL) this->lastform->sNext((Form*)NULL);
		flag = 1;
	}
	if (frm == this->firstform) {
		this->firstform = frm->gNext();
		if (this->firstform != (Form *)NULL) this->firstform->sPrev((Form*)NULL);
		flag = 1;
	}
	if (!flag) {
		nextfrm = frm->gNext();
		prevfrm = frm->gPrev();
		nextfrm->sPrev(prevfrm);
		prevfrm->sNext(nextfrm);
	}

	delete frm;
    }
};

/************************************************************************/
//! Remove all forms
/*!
*/
void Forms::KillAll( void ) {
    Form *frm, *victim;

    frm = firstform;
    while (frm != (Form *)NULL) {	// while the list is not empty
	victim = frm;
	frm = frm->gNext();
//cout << "kill victim : " << victim << "\n";
	delete victim;
//cout << "frm : " << frm << "\n";
    }
    firstform = lastform = (Form *)NULL;
};

/************************************************************************/
//! Get the list of form names
/*!
*/
String Forms::GetList( String delimiter ) {
    static int chunk = 32;	// is memory allocation portion size in bytes
    int size, dl, nl;		// dl - delimiter length, nl - name length
    Form *frm;
    String res, ptr, fname;
    String ws;

    size = chunk;
    res = new char[size]; ptr = res;
    res[0] = '\0';
    dl = strlen(delimiter);
    frm = firstform;
    while (frm != (Form *)NULL) {	// while the form list is not empty
	fname = frm->gName();
	nl = strlen(fname);
	if ((dl+nl) < (&res[size]-ptr)) {
		memcpy(ptr, delimiter, dl);
		ptr = ptr + dl;
		memcpy(ptr, fname, nl);
		ptr = ptr + nl;
		*ptr = '\0';
		frm = frm->gNext();
	}
	else {
		ws = res;
		size = size + chunk;
		res = new char[size];
		memcpy(res, ws, size-chunk);
		ptr = res + strlen(ws);
		delete ws;
	}
    }    
    return res;
}

/************************************************************************/
//! Load form list from disk cash
/*!
*/
int Forms::LoadForms( void ) {
    return 0;
};

/************************************************************************/
//! Upload form list to disk cash
/*!
*/
int Forms::SaveForms( void ) {
    return 0;
};

