%{
    //codigo C
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include <ctype.h>
    #include<stdbool.h>

    extern int yylineno;
    int yylex();
    void yyerror(char *s){ printf("\nERROR (%s) na linha %d\n", s, yylineno); }

    typedef struct vars {
		char name[50];
		float value;
		struct vars * prox;
	} VARS;

    typedef struct varts {
		char name[50];
		char value[100];
		struct varts * prox;
	} VARTS;

    //add nova variável na lista
	VARS * ins(VARS *l, char n[]){
		VARS *new =(VARS*)malloc(sizeof(VARS));
		strcpy(new->name, n);
		new->prox = l;
		return new;
	}

    //add nova variável na lista
    VARTS * inst(VARTS *l, char n[]){
		VARTS *new =(VARTS*)malloc(sizeof(VARTS));
		strcpy(new->name, n);
        strcpy(new->value, "");
		new->prox = l;
		return new;
	}

    //busca uma variável na lista de variáveis
	VARS *srch(VARS *l, char n[]){
		VARS *aux = l;
		while(aux != NULL){
			if(strcmp(n, aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
	}
	
    //busca uma variável na lista de variáveis
    VARTS *srcht(VARTS *l, char n[]){
		VARTS *aux = l;
		while(aux != NULL){
			if(strcmp(n,aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
	}

    // VERIFICAR SE DADO VALOR É REAL
    bool is_real(char test[]){
        int i = 0;
        int ponto = 0;
        do{
            if(isdigit(test[i])!=0 || test[i] == '.'){
                if(test[i]=='.')
                    ponto = ponto + 1;
                if(ponto>1)
                    return false;
                i=i+1;
            }
            else
                return false;
        }while(test[i]!='\0');
        
        return true;
    }

	VARS *rvar;
    VARTS *tvar;
%}

%union{
    char texto[50];
    int inteiro;
    double real;
}

//DECLARAÇÃO DE TOKENS
%token <texto> TIPO_REAL
%token <texto> TIPO_TEXTO
%token <real> REAL
%token <texto> TEXTO
%token ENTRADA
%token SAIDA
%token INICIO
%token FINAL
%token IF
%token ELSE
%token FOR
%token <texto> VAR
%token OPV
%token <texto> COMENTARIO
//TOKENS DE ARITMETICA
%token RAIZ COS SIN REST
//TOKENS DE LOGICA
%token MAIOR MENOR MEI MAI II DIF

//DECLARAÇÃO DE TIPO DE NÃO-TERMINAIS
%type <texto> saida var var1 vart vart1
%type <real> exp arit valor logica if arit1 arit2 arit3 L1 L2

//DECLARAÇÃO DE PRECEDÊNCIA
%left '+' '-'
%left '*' '/'
%right '^'
%left ')'
%right '('

%nonassoc '|' IMUNUS VAR

%start prog
%%

prog: INICIO cod FINAL {;printf("PROGRAMA FINALIZADO\n");}
    ;
cod: cod exp 
    |
    ;
exp: VAR '=' arit {
        //atribuição de variavel REAL
        VARS * aux = srch(rvar, $1);
        if (aux == NULL)
            printf ("Variável '%s' não foi declarada\n", $1);
        else {
            aux->value = $3;
        }
    }
    | VAR '=' TEXTO {
        //atribuição de variavel TEXTO
        VARTS * aux = srcht(tvar, $1);
        if (aux == NULL)
            printf ("Variável '%s' não foi declarada\n", $1);
        else {
            gets(aux->value);
        }
    }
    | VAR '=' OPV VAR {
        //atribuição de variavel TEXTO
        VARTS * aux = srcht(tvar, $1);
        if (aux == NULL)
            printf ("Variável '%s' não foi declarada.\n", $1);
        else {
            VARTS * aux2 = srcht(tvar, $4);
            if (aux2 == NULL){
                VARS * aux3 = srch(rvar, $4);
                if(aux3 == NULL)
                    printf ("Variavel '%s' nao foi declarada\n", $4);
                else
                    sprintf(aux->value, "%f", aux3->value);
            }
            else {
                //se for variavel texto
                strcpy(aux->value, aux2->value);
            }
        }
    }
    | TIPO_REAL var {printf("tipo real: %s %s\n", $1, $2); }
    | TIPO_TEXTO vart {printf("tipo texto: %s %s\n", $1, $2); }
    | VAR ENTRADA {
        VARS * aux = srch(rvar, $1);
        if (aux == NULL){
            //se nao existe variavel declarada real
            VARTS * aux2 = srcht(tvar, $1);
            if (aux2 == NULL){
                //se tbm nao existe variavel declarada texto
                printf ("Variavel '%s' nao foi declarada\n", $1);
            }
            else {
                //se for variavel texto
                scanf("%s", &aux2->value);
            }
        }
        else {
            //se for variavel real
            //verificar se o valor corresponde ao tipo real
            char test[100];
            do{
                int i = 0;
                do{
                    test[i] = '\0';
                    i++;
                }while(test[i]!='\0');

                scanf("%s", &test);
                if( is_real(test)==false )
                    printf ("Valor '%s' deve ser real\n", $1);
                
            }while( is_real(test)==false );
            
            aux->value = atof(test);
        }
    }
    | ':' arit {printf("RESULTADO ARITMETICO: %f\n", $2); }
    | ':' logica { if ($2 != 0) printf("RESULTADO LOGICA: TRUE\n"); else printf("RESULTADO LOGICA: FALSE\n"); }
    | IF if {}
    | FOR for {}
    | COMENTARIO {
        printf("COMENTARIO: %s\n", $1);
    }
    | SAIDA saida {printf("SAIDA: %s\n", $2); }
    ;
vart: vart ',' vart1 {sprintf($$, "%s, %s", $1, $3); }
    | vart1 {sprintf($$, "%s", $1); }
    ;
vart1: VAR {
        VARTS * aux = srcht(tvar, $1);
        if (aux == NULL){
            tvar = inst(tvar, $1);
            sprintf($$, "%s", $1);
        }
        else
            printf ("A variável '%s' já existe.\n", $1);
    }
    | VAR '=' TEXTO {
        VARTS * aux = srcht(tvar, $1);
        if (aux == NULL){
            tvar = inst(tvar, $1);
            
            VARTS * aux2 = srcht(tvar, $1);
            if (aux2 == NULL)
                printf ("Variavel '%s' nao foi declarada corretamente.\n", $1);
            else {
                strcpy(aux2->value, $3);
                sprintf($$, "%s = %s", $1, $3);
            }
        }
        else
            printf ("A variavel '%s' ja existe.\n", $1);
    }
    | VAR '=' OPV VAR {
        VARTS * aux = srcht(tvar, $1);
        if (aux == NULL){
            tvar = inst(tvar, $1);
            
            VARTS * aux2 = srcht(tvar, $1); //nova variavel a ser atribuida valor
            if (aux2 == NULL)
                printf ("Variavel '%s' nao foi declarada\n", $1);
            else {
                VARTS * aux3 = srcht(tvar, $4);
                if (aux3 == NULL){
                    VARS * aux4 = srch(rvar, $4);
                    if(aux4 == NULL)
                        printf ("Variavel '%s' nao foi declarada\n", $4);
                    else
                        sprintf(aux2->value, "%f", aux4->value);
                }
                else {
                    strcpy(aux2->value, aux3->value);
                    sprintf($$, "%s = %s = %s", $1, $4, aux2->value);
                }
            }
        }
        else
            printf ("A variavel '%s' ja existe.\n", $1);
    }
    ;
var: var ',' var1 {sprintf($$, "%s, %s", $1, $3); }
    | var1 {sprintf($$, "%s", $1); }
    ;
var1: VAR {
        VARS * aux = srch(rvar, $1);
        if (aux == NULL){
            rvar = ins(rvar, $1);
            //sprintf($$, "%s", $1);
        }
        else
            printf ("A variável '%s' já existe.\n", $1);
    }
    | VAR '=' arit {
        VARS * aux = srch(rvar, $1);
        if (aux == NULL){
            rvar = ins(rvar, $1);
            
            VARS * aux2 = srch(rvar, $1);
            if (aux2 == NULL)
                printf ("Variavel '%s' nao foi declarada ou nao eh tipo real.\n", $1);
            else {
                aux2->value = $3;
                //sprintf($$, "%s = %f", $1, $3);
            }
        }
        else
            printf ("A variavel '%s' ja existe.\n", $1);
    }
    ;
arit: SIN '(' arit ')' {
                $$ = sin($3);
                printf("SIN: %f = %f\n", $3, $$);
    }
    | COS '(' arit ')' {
                $$ = cos($3);
                printf("COS: %f = %f\n", $3, $$);
    }
    | RAIZ '(' arit ')' {
                $$ = sqrt($3);
                printf("RAIZ: %f = %f\n", $3, $$);
    }
    | '-' arit %prec IMUNUS {
                $$ = -$2;
                printf("NEG: -%f = -%f\n", $2, $$);
    }
    | '|' arit '|' {
                $$ = fabs($2);
                printf("MODULO: |%f| = %f\n", $2, $$);
    }
    | arit '+' arit1 {
                $$ = $1 + $3;
                printf("SOMA: %f + %f = %f\n", $1, $3, $$);
    }
    | arit '-' arit1 {
                $$ = $1 - $3;
                printf("SUB: %f - %f = %f\n", $1, $3, $$);
    }
    | arit1
    ;
arit1: arit1 '*' arit2 {
                $$ = $1 * $3;
                printf("PROD: %f * %f = %f\n", $1, $3, $$);
    }
    | arit1 '/' arit2 {
                $$ = $1 / $3;
                printf("DIV: %f / %f = %f\n", $1, $3, $$);
    }
    | arit1 REST arit2 {
                $$ = remainder($1, $3);
                printf("RESTO: %f / %f resto %f\n", $1, $3, $$);
    }
    | arit2
    ;
arit2: arit3 '^' arit2 {
                $$ = pow($1, $3);
                printf("EXPO: %f ^ %f = %f\n", $1, $3, $$);
    }
    | arit3
    ;
arit3: '(' arit ')' {}
    | valor {$$ = $1; }
    ;
valor: REAL { $$ = $1; /*printf("%f ", $$);*/}
    | VAR {
        VARS * aux = srch(rvar, $1);
        if (aux == NULL){
            VARTS * aux2 = srcht(tvar, $1);
            if (aux2 == NULL){
                printf ("Variavel '%s' nao foi declarada.\n",$1);
                $$ = 0;
            }
            else{
                printf ("Variavel '%s' eh tipo texto.\nUtilize o modificador '&' antes das variaveis tipo texto",$1);
                $$ = 0;
            }
        }
        else{
            $$ = aux->value;
            //printf("VAR->value = %f\n", $$);
        }
    }
    ;
logica: L1 MAIOR L2 {if ($1 > $3) $$=1; else $$=0; }
    | L1 MENOR L2 {if ($1 < $3) $$=1; else $$=0; }
    | L1 MAI L2 {if ($1 >= $3) $$=1; else $$=0; }
    | L1 MEI L2 {if ($1 <= $3) $$=1; else $$=0; }
    | L1 II L2 {if ($1 == $3) $$=1; else $$=0; }
    | L1 DIF L2 {if ($1 != $3) $$=1; else $$=0; }
    ;
L1: L2 {$$=$1; }
    ;
L2: '(' logica ')' {$$=$2; }
    | arit {$$=$1; }
    ;

saida: TEXTO {sprintf($$, "%s", $1); } 
    | TEXTO ',' saida {sprintf($$, "%s, %s", $1, $3); }
    | arit {sprintf($$, "%f", $1); } 
    | arit ',' saida {sprintf($$, "%f, %s", $1, $3); }
    | OPV VAR {
        VARTS * aux = srcht(tvar, $2);
        if (aux == NULL){
            VARS * aux2 = srch(rvar, $2);
            if (aux2 == NULL)
                printf ("Variavel '%s' nao foi declarada.\n", $2);
            else{
                sprintf($$, "%f", aux->value);
            }
        }
        else{
            strcpy($$, aux->value);
            //printf("VAR->value = %f\n", $$);
        }
    }
    | OPV VAR ',' saida {sprintf($$, "%s, %s", $2, $4); }
    ;
if: logica ':' cod ELSE cod ';' {printf("IF ELSE CLOSE\n"); }
    | logica ':' cod ';' {printf("IF CLOSE\n"); };
    ;
for: arit ':' cod ';' {printf("FOR CLOSE\n"); };
    ;
%%

#include "lex.yy.c"

int main(){

    rvar = NULL;
    tvar = NULL;
    
    yyin=fopen("calc_exemplo.txt", "r");

    do {yyparse();}
    while (!feof(yyin));
    
    fclose(yyin);

    return 0;
}
int yywrap(){
    return 0;
}