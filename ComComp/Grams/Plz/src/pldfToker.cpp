/* Elimination des commentaires. */

#if !defined(USE_YACC)

#ifndef EOF_CHAR
#define EOF_CHAR	-1
#endif

/********************************************************
* Fonction: PasseCommentaire1.
* Desc: Prend une suite de commentaire (commencee par '/''*')
*       et ignore tout ce qui suit, jusqu'a '*''/'.
* Args: Aucun.
* Renvoie: Rien.
********************************************************/

void PasseCommentaire1(void)
{
    char lastChar, c;

    while (1) {
	while ((c = input()) != '/') lastChar= c;
	if (lastChar == '*') {
	    return;
	 }
        else if (c == EOF_CHAR) {
//	    sprintf(ErrorMsgBuffer, "While in comment: unexpected EOF.\n");
//	    AddWarning(NULL, ErrorMsgBuffer);
	    return;
	 }
	else lastChar= c;
    }
}


/********************************************************
* Fonction: PasseComentaire2.
* Desc: Prend une suite de commentaire (commencee par '/''/')
*       et ignore tout ce qui suit, jusqu'a la fin de la ligne.
* Args: Aucun.
* Renvoie: Rien.
********************************************************/

void PasseCommentaire2(void)
{
    char c;

    while ((c = input()) != '\n') {
	if (c == EOF_CHAR) {
	    break;
	 }
     }

    if (c == '\n') unput(c);

    return;
}

#endif		/* ! USE_YACC */


/********************************************************
* Fonction: PreCompDirective.
* Desc: Traite une directive de compilation.
* Args: Aucun.
* Renvoie: Rien.
********************************************************/

void PreCompDirective(void)
{
    int resultat;
    unsigned int i, offset, nbrDirectives= 8;	/* nbrDirectives = nbr de directives - 1. */
    static char *nomDirective[9]= { "define", "else", "elif", "endif", "if", "ifdef", "ifndef", "include", "undef" };
    static unsigned int directives[10]= { MKW_DEFINE, MKW_ELSE, MKW_ELIF, MKW_ENDIF,
    		MKW_IF, MKW_IFDEF, MKW_IFNDEF, MKW_INCLUDE, MKW_UNDEF, 0 };
    char c, *directiveName;
    bool encore, trouve;

    trouve= FALSE;
    encore= TRUE;
    i= 0;
    offset= 0;
    directiveName= nomDirective[0];
    c= input();
    do {
	if (c != *directiveName++) {
	    if (i++ == nbrDirectives) encore= FALSE;
	    else directiveName=  nomDirective[i] + offset;
	    if (offset > 0) {
		if (nomDirective[i-1][offset-1] != *(directiveName-1)) {
		    encore= FALSE;
		 }
	     }
	 }
	else if (*directiveName == '\0') {
	    c= input();
	    if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r')) {
		trouve= TRUE;
		encore= FALSE;
		unput(c);
	     }
	    else offset++;
	 }
	else {
	    c= input();
	    offset++;
	 }
     } while (encore);
    if (trouve) {

#ifdef A_FAIRE
	switch (directives[i]) {
	    case MKW_INCLUDE:    /* include "filename" .*/
		resultat= IncludeDirective();
		break;
	    case MKW_DEFINE:    /* define <nom> <valeur>. */
		resultat= DefineDirective();
		break;
	    case MKW_IFDEF:    /* ifdef <nom>. */
		resultat= IfdefDirective();
		break;
	    case MKW_IFNDEF:    /* ifndef <nom>. */
		resultat= IfNdefDirective();
		break;
	    case MKW_ELSE:    /* else. */
		resultat= elseDirective();
		break;
	    case MKW_ENDIF:    /* endif. */
		resultat= EndifDirective();
		break;
	    case MKW_IF:    /* if <expression_precom>. */
		resultat= IfDirective();
		break;
	    case MKW_ELIF:    /* elif <expression_precomp>. */
		resultat= ElifDirective();
		break;
	    case MKW_UNDEF:    /* undef <nom>. */
		resultat= UndefDirective();
		break;
	    default: /* Erreur interne. */
		break;
	 }
#endif

     }
    else {
	yyerror("syntax error: invalid compiler directive");
     }
}


wchar *wstrdup(char *nText)
{
    wchar *tmpPtr;

    tmpPtr= (wchar *)malloc((strlen(nText)+2) * sizeof(wchar));
    narrowToWide(tmpPtr, nText);
    return tmpPtr;
}


void narrowToWide(wchar *wString, char *nString)
{
    while (*nString != '\0') {
	*wString++= (wchar)(0x0000 + *(unsigned char *)nString++);
     }
    *wString= 0;
}


unsigned int wstrlen(wchar *wString)
{
    unsigned int total= 0;

    while (*wString) { total++; wString++; }

}

