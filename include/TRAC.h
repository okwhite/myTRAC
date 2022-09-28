#define CMD_COUNT 48

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
String *cmd = NULL;
String mnem[CMD_COUNT];		// Build-in command mnemonics
static String (*impl[CMD_COUNT])( void );	// Build-in command implementation functions

// Build-in TRAC commmands
//String _null_( void);   // 'Command' "" implementation
// Input/Output
//String _rs_( void );
//String _ps_( void );
//String _rc_( void );
// Integer Arithmetic
//String _add_( void );
//String _mul_( void );
// Services
//String _cm_( void );
// Forms
//String _ds_( void );


