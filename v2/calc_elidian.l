%option yylineno
%{
    //codigo em C
%}

/* TIPOS DE CARACTERES BÁSICOS */
NUMERO [0-9]
LETRA [a-zA-Z]

/* TIPOS PRIMITIVOS */
INTEIRO {NUMERO}+
REAL {NUMERO}*"."{NUMERO}+
TEXTO \".*\"

/* TIPOS DE VARIAVEIS */
TIPO "inteiro"|"real"|"texto"

/* TOKENS DE ENTRADA E SAIDA DE INFORMAÇÕES */
ENTRADA "<<"
SAIDA ">>"

/* TOKENS DE INICIO E FIM DE PROGRAMA */
INICIO "in"
FINAL "ni"

/* CONDICIONAL E REPETIÇÃO */
IF "inif"
ELSE "infi"
FOR "infor"

/* ARITMETICA "+"|"-"|"/"|"*"|"^" */
REST "%"
SIN "sin"
COS "cos"
RAIZ "raiz"

/* LOGICA {MENOR}|{MAIOR}|{MEI}|{MAI}|{II}|{DIF} */
MAIOR ">"
MENOR "<"
IGUAL "="
MAI {MAIOR}{IGUAL}
MEI {MENOR}{IGUAL}
II {IGUAL}{IGUAL}
DIF "!"{IGUAL}

/* PADRÃO PARA NOME DE VARIAVEIS */
VAR {LETRA}({LETRA}|{NUMERO}|"-"|"_")*

/* TOKEN PARA COMENTÁRIO */
COMENTARIO "#".*

/* IGNORAR ESPAÇO, TAB */
IGNORAR [\ \t\s]

/* NÃO ACEITAR QUALQUER VALOR DIFERENTE DO QUE ESTIVER ACIMA NESTE CODIGO */
INVALIDO .
%%
{TIPO} {
    strcpy(yylval.texto, yytext);
    return TIPO;
}
"+"|"-"|"/"|"*"|"^" {
  return *yytext;
}
{RAIZ} {
    return RAIZ;
}
{COS} {
    return COS;
}
{SIN} {
    return SIN;
}
{REST} {
    return REST;
}
{MENOR} {
    return MENOR;
}
{MAIOR} {
    return MAIOR;
}
{MEI} {
    return MEI;
}
{MAI} {
    return MAI;
}
{II} {
    return II;
}
{DIF} {
    return DIF;
}
{ENTRADA} {
    return ENTRADA;
}
{SAIDA} {
    return SAIDA;
}
{INICIO} {
    return INICIO;
}
{FINAL} {
    return FINAL;
}
{INTEIRO} {
    yylval.inteiro = atoi(yytext);
    return INTEIRO;
}
{REAL} {
    yylval.real = atof(yytext);
    return REAL;
}
{TEXTO} {
    strncpy(yylval.texto, &yytext[1], strlen(yytext)-2);
    yylval.texto[strlen(yytext)-2] = '\0';
    return TEXTO;
}
{IF} {
    return IF;
}
{ELSE} {
    return ELSE;
}
{FOR} {
    return FOR;
}
{VAR} {
    strcpy(yylval.texto, yytext);
    return VAR;
}
{COMENTARIO} {
    strcpy(yylval.texto, yytext);
    return COMENTARIO;
}
[=:;,()] {
    return yytext[0];
}
[\n] {
    /* CONTADOR PARA SALTO DE LINHAS */
    yylineno++;
}
{IGNORAR} {
  /* ignore */
}
{INVALIDO} {
  /* ignore */
}

%%
