
class PlDfToker : public yyFlexLexer {

/*** Variables globales proventant d'autres modules. ***/

extern int isInSubset;
extern int yychar;

/*** Variables globales definies dans ce module. ***/
static char StrBuffer[1024];

/*** Les prototypes des fonctions definies dans ce module. ***/

void PreCompDirective(void);
void narrowToWide(wchar *, char *);
wchar *wstrdup(char *);
unsigned int wstrlen(wchar *);

};

