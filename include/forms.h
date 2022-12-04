#ifndef FORMS
#define FORMS

/*! \file forms.h
 *  form list declaration
*/


//! Form class (list's element)
/*!
*/
class Form {

public:
    Form();
    Form(String formname);
    Form(String formname, String formbody);
    ~Form();
    String gName(void);
    String gBody(void);
    Form *gPrev(void);
    Form *gNext(void);
    void sPrev(Form *form);
    void sNext(Form *form);
protected:
    String name;
    String body;
    char *ptr;
    Form *prev;
    Form *next;
};

//! Forms class (form list)
/*!
*/
class Forms {

public:
    Forms();
    Forms( String filename );
    ~Forms();
    void AddForm( Form * );			// add form to the list
    void KillForm( String name );		// remove a form from the list
    void KillAll();				// kill the list of forms
    Form *GetForm( String name );		// search and get the form by name
    String GetList( String delimiter );		// get the list of form names
    
protected:
    Form *firstform;
    Form *lastform;
    String frmfile;
    int LoadForms();
    int SaveForms();
};

#endif
