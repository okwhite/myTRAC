#ifndef TRAC
#define TRAC

#define MACRO_COUNT 50

const char *CRLF = "CR-LF";	// CRLF in TRAC syntax
char PRG_END = '\x27';		// TRAC program end character "'"
char TERMINATOR = '\x1B';	// TRAC algorithm termination character ESC
char arg = 'p';		// Argument qualifier
char aFn = 'a';		// Active function qualifier
char nFn = 'n';		// Neutral function qualifier
char *argument = &arg;
char *activeFn = &aFn;
char *neutralFn = &nFn;

Active *aChain = NULL;
Neutral *nChain = NULL;
Forms *forms = NULL;	// Current form library
Stack *args = NULL;	// Argument stack with qualifiers
Stack *args1 = NULL;	// Argument stack without qualifiers (for Eval())
//String *cmd = NULL;
String mnem[MACRO_COUNT];		// Build-in command mnemonics
static String (*impl[MACRO_COUNT])( void );	// Build-in command implementation functions

// Build-in TRAC macros
//String _null_( void);   // 'Macro' "" implementation
// Input/Output
//String _rs_( void );
//String _ps_( void );
//String _rc_( void );
// Integer Arithmetic
//String _add_( void );
//String _mul_( void );
// Services
//String _cm_( void );
//String _meta_( void );
// Forms
//String _ds_( void );
//String _ss_( void );
//String _dd_( void );
//String _pf_( void );
//String _da_( void );
//String _ln_( void );
// Other
//String _null_( void );

#endif


