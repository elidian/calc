%option yylineno
%{
    //codigo em C
%}

/* TIPOS DE CARACTERES BÁSICOS */
NUMERO [0-9]
LETRA [a-zA-Z]

/* TIPOS PRIMITIVOS */
REAL {NUMERO}+|{NUMERO}*"."{NUMERO}+
TEXTO \".*\"

/* TIPOS DE VARIAVEIS */
TIPO_REAL "real"
TIPO_TEXTO "texto"

/* TOKENS DE ENTRADA E SAIDA DE INFORMAÇÕES */
ENTRADA "<<"
SAIDA ">>"

/* OPÇÃO CARACTERISTICA PARA VARIAVEL TIPO TEXTO */
OPV "&"

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

{TIPO_REAL} {
    return TIPO_REAL;
}
{TIPO_TEXTO} {
    return TIPO_TEXTO;
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
{OPV} {
    return OPV;
}
{INICIO} {
    return INICIO;
}
{FINAL} {
    return FINAL;
}
{REAL} {
    yylval.real = atof(yytext);
    return REAL;
}
{TEXTO} {
    strcpy(yylval.texto, yytext);
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
