%{
#include<string.h>
#include<stdio.h>

struct ParserContext;

#include "yacc_sql.tab.h"
extern int atoi();
extern double atof();

#if YYDEBUG > 0
#define debug_printf  printf
#else
#define debug_printf(...)
#endif // YYDEBUG

#define RETURN_TOKEN(token) debug_printf("%s\n",#token);return token
%}

/* Prevent the need for linking with -lfl */
%option noyywrap
%option bison-bridge
%option reentrant

WHITE_SAPCE      [\ \t\b\f]
DIGIT            [0-9]+

ID               [A-Za-z_]+[A-Za-z0-9_]*
DOT              \.
QUOTE            [\'\"]
DELI			 [\-\\/\.]
%x STR

%%

{WHITE_SAPCE}                           // ignore whitespace
\n																						 ;

[\-]?{DIGIT}+					                   yylval->number=atoi(yytext); RETURN_TOKEN(NUMBER);
[\-]?{DIGIT}+{DOT}{DIGIT}+				       yylval->floats=(float)(atof(yytext)); RETURN_TOKEN(FLOAT);

";"                 	 				           RETURN_TOKEN(SEMICOLON);
{DOT}                 					         RETURN_TOKEN(DOT);
"*"                   					         RETURN_TOKEN(STAR);
(?i:is) 														 RETURN_TOKEN(IS);
(?i:not)        								     RETURN_TOKEN(NOT);
(?i:null)        								     RETURN_TOKEN(NULL_T);
(?i:nullable) 									 RETURN_TOKEN(NULLABLE);
[Ee][Xx][Ii][Tt]						             RETURN_TOKEN(EXIT);
[Hh][Ee][Ll][Pp]                    	   RETURN_TOKEN(HELP);
[Dd][Ee][Ss][Cc]                         RETURN_TOKEN(DESC);
(?i:max)										 RETURN_TOKEN(MAX_F);
(?i:min)										 RETURN_TOKEN(MIN_F);
(?i:count)										 RETURN_TOKEN(COUNT_F);
(?i:avg)										 RETURN_TOKEN(AVG_F);
(?i:join)										 RETURN_TOKEN(JOIN);
(?i:inner)										 RETURN_TOKEN(INNER);
[Cc][Rr][Ee][Aa][Tt][Ee]                 RETURN_TOKEN(CREATE);
[Dd][Rr][Oo][Pp]                    	   RETURN_TOKEN(DROP);
[Tt][Aa][Bb][Ll][Ee]					           RETURN_TOKEN(TABLE);
[Tt][Aa][Bb][Ll][Ee][Ss]			           RETURN_TOKEN(TABLES);
[Ii][Nn][Dd][Ee][Xx]                  	 RETURN_TOKEN(INDEX);
[Oo][Nn]								                 RETURN_TOKEN(ON);
[Ss][Hh][Oo][Ww]                         RETURN_TOKEN(SHOW);
[Ss][Yy][Nn][Cc]                         RETURN_TOKEN(SYNC);
[Ss][Ee][Ll][Ee][Cc][Tt]                 RETURN_TOKEN(SELECT);
[Ff][Rr][Oo][Mm]                      	 RETURN_TOKEN(FROM);
[Ww][Hh][Ee][Rr][Ee]                  	 RETURN_TOKEN(WHERE);
[Aa][Nn][Dd]                             RETURN_TOKEN(AND);
[Ii][Nn][Ss][Ee][rR][tT]                 RETURN_TOKEN(INSERT);
[Ii][Nn][Tt][Oo]					 	             RETURN_TOKEN(INTO);
[Vv][Aa][Ll][Uu][Ee][Ss]                 RETURN_TOKEN(VALUES);
[Dd][Ee][Ll][Ee][Tt][Ee]                 RETURN_TOKEN(DELETE);
[Uu][Pp][Dd][Aa][Tt][Ee]                 RETURN_TOKEN(UPDATE);
[Ss][Ee][Tt]							               RETURN_TOKEN(SET);
[Bb][Ee][Gg][Ii][Nn]                     RETURN_TOKEN(TRX_BEGIN);
[Cc][Oo][Mm][Mm][Ii][Tt]                 RETURN_TOKEN(TRX_COMMIT);
[Rr][Oo][Ll][Ll][Bb][Aa][Cc][Kk]         RETURN_TOKEN(TRX_ROLLBACK);
[Ii][Nn][Tt]					                   RETURN_TOKEN(INT_T);
[Cc][Hh][Aa][Rr]				                 RETURN_TOKEN(STRING_T);
(?i:date)										 RETURN_TOKEN(DATE_T);
[Ff][Ll][Oo][Aa][Tt]			               RETURN_TOKEN(FLOAT_T);
[Ll][Oo][Aa][Dd]			                   RETURN_TOKEN(LOAD);
[Dd][Aa][Tt][Aa]	                       RETURN_TOKEN(DATA);
[Ii][Nn][Ff][Ii][Ll][Ee]                 RETURN_TOKEN(INFILE);
{ID}							                       yylval->string=strdup(yytext); RETURN_TOKEN(ID);
"("								                       RETURN_TOKEN(LBRACE);
")"								                       RETURN_TOKEN(RBRACE);

","                                      RETURN_TOKEN(COMMA);
"="                                      RETURN_TOKEN(EQ);
"<="                                     RETURN_TOKEN(LE);
"<>"                                     RETURN_TOKEN(NE);
"<"                                      RETURN_TOKEN(LT);
">="                                     RETURN_TOKEN(GE);
">"                                      RETURN_TOKEN(GT);
{QUOTE}([0-9]{4}){DELI}(0?[1-9]|1[0-2]){DELI}(0?[1-9]|[12][0-9]|3[0-1]){QUOTE}	{
	/* parse date */;
	int i = 1, j = 0;
	int date[3];	// date[0]:year, date[1]:month, date[2]:day
	memset(date, 0, sizeof date);
	while (j < 3 && i < yyleng) {
		while (i < yyleng && (yytext[i] <= '9' && yytext[i] >= '0')) {
			date[j] = date[j] * 10 + (yytext[i] - '0');
			i++;
		}
		if (i < yyleng) {
			yytext[i] = '-';
		}
		i++, j++;
	}

	/* format date: YYYY-MM-DD */	
	char tmp[20];
	memset(tmp, 0, sizeof tmp);
	sprintf(tmp, "%04d-%02d-%02d", date[0], date[1], date[2]);
	yylval->string = strdup(tmp);

	/* WARNNING: date string may be invalid */
	RETURN_TOKEN(DATE);
}
{QUOTE}[\40\42\47A-Za-z0-9_/\.\-]*{QUOTE}	     yylval->string=strdup(yytext); RETURN_TOKEN(SSS);

.						                             printf("Unknown character [%c]\n",yytext[0]); return yytext[0];
%%

void scan_string(const char *str, yyscan_t scanner) {
	yy_switch_to_buffer(yy_scan_string(str, scanner), scanner);
}
