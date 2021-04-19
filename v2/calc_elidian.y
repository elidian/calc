%{
    //codigo C
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include <ctype.h>
    #include <stdbool.h>

    extern int yylineno;
    int yylex();
    void yyerror(char *s){ printf("\nERROR (%s) na linha %d\n", s, yylineno); }
    #define MAX(a,b) (((a)>(b))?(a):(b))

    // VERIFICAR SE DADO VALOR É REAL
    bool is_real(char test[]){
        int i = 0, ponto = 0;
        do{
            if(isdigit(test[i])!=0 || test[i] == '.'){
                if(test[i]=='.')
                    ponto++;
                if(ponto>1)
                    return false;
                i++;
            } else
                return false;
        }while(test[i]!='\0');
        
        return true;
    }

    // VERIFICAR SE DADO VALOR É INTEIRO
    bool is_int(char test[]){
        int i = 0, ponto = 0;
        do{
            if(isdigit(test[i])!=0){
                i++;
            }
            else
                return false;
        }while(test[i]!='\0');
        return true;
    }

    int typeToInt(char t[]){
        if (strcmp("texto", t)==0)
                return 0;
            else if (strcmp("inteiro", t)==0)
                return 1;
                else if (strcmp("real", t)==0)
                    return 2;
    }

    char *intToType(int n){
        if (n==0)
                return "texto";
            else if (n==1)
                return "inteiro";
                else if (n==2)
                    return "real";
    }

    typedef struct ftype {
        int type; // string se 0, int se 1, double se 2
        char t[100];
        int i;
        double r;
	} FTYPE;

    typedef struct variavels {
		char name[50];
        int type; // string se 0, int se 1, double se 2
        char t[100];
        int i;
        double r;
		struct variavels * prox;
	} VARIAVELS;

    typedef struct ast {
        int type;
        struct ast *l;
        struct ast *r;
    } AST;

    typedef struct flow{
        int type;
        AST *cond; 
        AST *t1;
        AST *e2;
    } FLOW;

    //add nova variável na lista
	VARIAVELS * insVar(VARIAVELS *l, char n[], int type){
		VARIAVELS *new =(VARIAVELS*)malloc(sizeof(VARIAVELS));
		strcpy(new->name, n);
		new->prox = l;
        new->type = type;
		return new;
	}

    VARIAVELS * insVarV(VARIAVELS *l, char n[], int type, FTYPE v){
		VARIAVELS *new =(VARIAVELS*)malloc(sizeof(VARIAVELS));
		new->prox = l;
		strcpy(new->name, n);
        new->type = type;
        if (new->type == v.type){
            if (new->type == 0)
                strcpy(new->t, v.t);
            else if (new->type == 1)
                    new->i = v.i;
                else if (new->type == 2)
                    new->r = v.r;
        } else {
            if (new->type == 0){
                if (v.type == 1)
                    sprintf(new->t,"%d", v.i);
                else if (v.type == 2)
                    sprintf(new->t,"%f", v.r);
            } else {
                if (new->type == 1){
                    if (v.type == 0)
                        new->i = atoi(v.t);
                    else if (v.type == 2)
                        new->i = (int)v.r;
                } else {
                    if (new->type == 2){
                        if (v.type == 0)
                            new->r = atof(v.t);
                        else if (v.type == 1)
                            new->r = (double)v.i;
                    }
                }
            }
        }
		return new;
	}

    //add nova variável na lista
	VARIAVELS * insVarI(VARIAVELS *l, char n[], int i){
		VARIAVELS *new =(VARIAVELS*)malloc(sizeof(VARIAVELS));
		strcpy(new->name, n);
		new->prox = l;
        new->type = 0;
        new->i = i;
		return new;
	}

    //add nova variável na lista
	VARIAVELS * insVarR(VARIAVELS *l, char n[], double r){
		VARIAVELS *new =(VARIAVELS*)malloc(sizeof(VARIAVELS));
		strcpy(new->name, n);
		new->prox = l;
        new->type = 0;
        new->r = r;
		return new;
	}

    //add nova variável na lista texto
	VARIAVELS * insVarT(VARIAVELS *l, char n[], char t[]){
		VARIAVELS *new =(VARIAVELS*)malloc(sizeof(VARIAVELS));
		strcpy(new->name, n);
        new->type = 0;
        strcpy(new->t, t);
		return new;
	}

    //add nova variável na lista texto
	VARIAVELS * pushVarVal(VARIAVELS *l, char n[], FTYPE v){
        VARIAVELS *new = l;
		while(new != NULL){
            if(strcmp(n, new->name)==0){
                if (new->type == v.type){
                    if (new->type == 0)
                        strcpy(new->t, v.t);
                    else if (new->type == 1)
                        new->i = v.i;
                        else if (new->type == 2)
                            new->r = v.r;
                    return new;
                } else {
                    if (new->type == 0){
                        if (v.type == 1)
                            sprintf(new->t,"%d", v.i);
                        else if (v.type == 2)
                            sprintf(new->t,"%f", v.r);
		                return new;
                    } else {
                        if (new->type == 1){
                            if (v.type == 0){
                                if (v.t[0]=='"')
                                    strcpy(v.t, &v.t[1]) ;
                                new->i = atoi(v.t);
                            } else if (v.type == 2)
                                new->i = (int)v.r;
		                    return new;
                        } else {
                            if (new->type == 2){
                                if (v.type == 0){
                                    if (v.t[0]=='"')
                                        strcpy(v.t, &v.t[1]) ;
                                    new->r = atof(v.t);
                                } else if (v.type == 1)
                                    new->r = (double)v.i;
		                        return new;
                            }
                        }
                    }
                }
            }
			new = new->prox;
		}
		return new;
	}

    //busca uma variável na lista de variáveis
	VARIAVELS *srchVar(VARIAVELS *l, char n[]){
		VARIAVELS *aux = l;
		while(aux != NULL){
			if(strcmp(n, aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
	}

    VARIAVELS *var0 = NULL;
    
%}

%union{
    char texto[50];
    int inteiro;
    double real;
    FTYPE ftype;
    AST *a;
}

//DECLARAÇÃO DE TOKENS
%token <texto> TIPO TEXTO VAR COMENTARIO
%token <inteiro> INTEIRO
%token <real> REAL
%token ENTRADA SAIDA INICIO FINAL IF ELSE FOR
//TOKENS DE ARITMETICA
%token RAIZ COS SIN REST
//TOKENS DE LOGICA
%token MAIOR MENOR MEI MAI II DIF
//DECLARAÇÃO DE TIPO DE NÃO-TERMINAIS
%type <texto> saida
%type <real> exp L1 L2
%type <inteiro> logica
%type <ftype> ivar ivar2 val atrib arit arit1 arit2 arit3 valor
%type <a> if for
//DECLARAÇÃO DE PRECEDÊNCIA
%left '+' '-'
%left '*' '/'
%right '^'
%left ')'
%right '('

%nonassoc '|' IMUNUS

%start prog
%%

prog: INICIO cod FINAL {;printf("PROGRAMA FINALIZADO\n");}
    ;
cod: cod exp 
    |
    ;
exp: atrib {}
    | ivar {}
    | VAR ENTRADA {
        char test[100];
        int i = 0;
        do {
            test[i] = '\0';
            i++;
        } while(test[i]!='\0');
        scanf("%s", &test);
        if ( is_int(test)==true ){
            FTYPE new;
            new.type = 1;
            new.i = atoi(test);
            VARIAVELS *aux = pushVarVal(var0, $1, new);
            if (aux==NULL)
                printf("ERRO 305: Variavel %s ainda nao declarada\n", $1);
        } else {
            if (is_real(test)==true ){
                FTYPE new;
                new.type = 2;
                new.r = atof(test);
                VARIAVELS *aux = pushVarVal(var0, $1, new);
                if (aux==NULL)
                    printf("ERRO 313: Variavel %s ainda nao declarada\n", $1);
            } else {
                FTYPE new;
                new.type = 0;
                strcpy(new.t, test);
                VARIAVELS *aux = pushVarVal(var0, $1, new);
                if (aux==NULL)
                    printf("ERRO 320: Variavel %s ainda nao declarada\n", $1);
            }
        }
    }
    | ':' arit {printf("RESULTADO ARITMETICO: %f\n", $2); }
    | ':' logica { if ($2 != 0) printf("RESULTADO LOGICA: TRUE\n"); else printf("RESULTADO LOGICA: FALSE\n"); }
    | if {}
    | for {}
    | COMENTARIO { printf("COMENTARIO: %s\n", $1);}
    | SAIDA saida {printf("%s\n", $2); }
    ;
atrib: VAR '=' arit {
        //atribuição de variavel REAL
        VARIAVELS * aux = pushVarVal(var0, $1, $3);
        if (aux == NULL)
            printf ("ERRO 2: Variável '%s' não foi declarada\n", $1);
    }
    ;
ivar: ivar ',' VAR { 
        VARIAVELS * aux = srchVar(var0, $3);
        if (aux == NULL){
            var0 = insVar(var0, $3, $1.type);
        } else
            printf ("A variável '%s' já existe.\n", $3);
    }
    | ivar ',' VAR '=' val { 
        VARIAVELS * aux = srchVar(var0, $3);
        if (aux == NULL){
            var0 = insVarV(var0, $3, $1.type, $5);
        } else
            printf ("A variável '%s' já existe.\n", $3);
    }
    | ivar2 {printf("TIPO: %d\n", $1.type);}
    ;
ivar2: TIPO VAR { 
        $$.type = typeToInt($1);
        if (srchVar(var0, $2) == NULL){
            var0 = insVar(var0, $2, typeToInt($1));
            printf("TIPO VAR: %s\n", intToType(var0->type) );
        } else
            printf ("A variável '%s' já existe.\n", $2);
    }
    | TIPO VAR '=' arit { 
        $$.type = typeToInt($1);
        if (srchVar(var0, $2) == NULL){
            var0 = insVar(var0, $2, typeToInt($1));
            pushVarVal(var0, $2, $4);
            printf("TIPO VAR = val: %s %s\n", $1, $2 );
        } else
            printf ("A variável '%s' já existe.\n", $2);
    }
    ;
val: TEXTO { strcpy($$.t, $1); $$.type = 0;}
    | INTEIRO { $$.i = $1; $$.type = 1;}
    | REAL { $$.r = $1; $$.type = 2;}
    | VAR {
        VARIAVELS * aux = srchVar(var0, $1);
        if (aux == NULL){
            printf ("Variavel '%s' nao declarada",$1);    
        } else {
            $$.type = aux->type;
            if ($$.type == 0)
                    strcpy($$.t, aux->t);
                else if ($$.type == 1)
                    $$.i = aux->i;
                    else if ($$.type == 2)
                        $$.r = aux->r;
        }
    }
    ;
arit: SIN '(' arit ')' {
                $$.type = 2;
                $$.r = sin($3.r);
                printf("SIN: %f = %f\n", $3.r, $$.r);
    }
    | COS '(' arit ')' {
                $$.type = 2;
                $$.r = cos($3.r);
                printf("COS: %f = %f\n", $3.r, $$.r);
    }
    | RAIZ '(' arit ')' {
                $$.type = 2;
                $$.r = sqrt($3.r);
                printf("RAIZ: %f = %f\n", $3.r, $$.r);
    }
    | '-' arit %prec IMUNUS {
                $$.type = 2;
                $$.r = -$2.r;
                printf("NEG: -%f = -%f\n", $2.r, $$.r);
    }
    | '|' arit '|' {
        $$.type = $2.type;
        if($2.type == 1){
            $$.i = fabs($2.i);
            printf("MODULO: |%d| = %d\n", $2.i, $$.i);
        }else if($2.type == 2){
            $$.r = fabs($2.r);
            printf("MODULO: |%f| = %f\n", $2.r, $$.r);
        }
    }
    | arit '+' arit1 {
        $$.type = MAX($1.type, $3.type);
        if($$.type==1){
            $$.i = $1.i + $3.i;
            printf("SOMA 1: = %d\n", $$.i);
        } else if($$.type==2){
                if($1.type ==1 && $3.type ==2)
                    $$.r = $1.i + $3.r; 
                else if($1.type ==2 && $3.type ==1)
                        $$.r = $1.r + $3.i; 
                    else if($1.type ==2 && $3.type ==2)
                            $$.r = $1.r + $3.r; 
                        else
                            printf("Variavel tipo texto\n");
                printf("SOMA 2: = %f\n", $$.r);
        }
    }
    | arit '-' arit1 {
        $$.type = MAX($1.type, $3.type);
        if($$.type==1){
            $$.i = $1.i - $3.i;
            printf("SUB 1: = %d\n", $$.i);
        } else if($$.type==2){
                if($1.type ==1 && $3.type ==2)
                    $$.r = $1.i - $3.r; 
                else if($1.type ==2 && $3.type ==1)
                        $$.r = $1.r - $3.i; 
                    else if($1.type ==2 && $3.type ==2)
                            $$.r = $1.r - $3.r; 
                        else
                            printf("Variavel tipo texto\n");
                printf("SUB 2: = %f\n", $$.r);
        }
    }
    | arit1 {$$ = $1;}
    ;
arit1: arit1 '*' arit2 {
        $$.type = MAX($1.type, $3.type);
        if($$.type==1){
            $$.i = $1.i * $3.i;
            printf("PROD 1: = %d\n", $$.i);
        } else if($$.type==2){
                if($1.type ==1 && $3.type ==2)
                    $$.r = $1.i * $3.r; 
                else if($1.type ==2 && $3.type ==1)
                        $$.r = $1.r * $3.i; 
                    else if($1.type ==2 && $3.type ==2)
                            $$.r = $1.r * $3.r; 
                        else
                            printf("Variavel tipo texto\n");
                printf("PROD 2: = %f\n", $$.r);
        }
    }
    | arit1 '/' arit2 {
        $$.type = MAX($1.type, $3.type);
        if($$.type==1 && ($1.i % $3.i)==0){
            $$.i = $1.i / $3.i;
            printf("DIV 1: = %d\n", $$.i);
        } else if($$.type==2 || ($1.i % $3.i)!=0){
                $$.type = 2;
                if($1.type ==1 && $3.type ==2){
                    $$.r = $1.i / $3.r; 
                    printf("ops0\n");
                } else if($1.type ==2 && $3.type ==1){
                        $$.r = $1.r / $3.i; 
                            printf("ops1\n");
                    } else if($1.type ==2 && $3.type ==2){
                            $$.r = $1.r / $3.r; 
                            printf("ops2\n");
                        } else if($1.type ==1 && $3.type ==1){
                                $$.r = (double)$1.i / $3.i; 
                                printf("ops3\n");
                            } else
                                printf("Variavel tipo texto\n");
                printf("DIV 2: = %f\n", $$.r);
            }
    }
    | arit1 REST arit2 {
        $$.type = MAX($1.type, $3.type);
        if($$.type==1){
            $$.i = $1.i % $3.i;
            printf("REST 1: = %d\n", $$.i);
        } else if($$.type==2){
                if($1.type ==1 && $3.type ==2){
                    $$.r = fmod($1.i, $3.r); 
                    printf("ops0\n");
                } else if($1.type ==2 && $3.type ==1){
                        $$.r = fmod($1.r, $3.i); 
                        printf("ops1\n");
                    } else if($1.type ==2 && $3.type ==2){
                            $$.r = fmod($1.r, $3.r); 
                            printf("ops2\n");
                        } else
                                printf("Variavel tipo texto\n");
                printf("REST 2: = %f\n", $$.r);
            }
    }
    | arit2 {$$ = $1;}
    ;
arit2: arit3 '^' arit2 {
        $$.type = MAX($1.type, $3.type);
        if($$.type==1){
            $$.i = pow($1.i, $3.i);
            printf("EXPO 1: = %d\n", $$.i);
        } else if($$.type==2){
                if($1.type ==1 && $3.type ==2){
                    $$.r = pow($1.i, $3.r); 
                    printf("ops0\n");
                } else if($1.type ==2 && $3.type ==1){
                        $$.r = pow($1.r, $3.i); 
                        printf("ops1\n");
                    } else if($1.type ==2 && $3.type ==2){
                            $$.r = pow($1.r, $3.r); 
                            printf("ops2\n");
                        } else
                            printf("Variavel tipo texto\n");
                printf("REST 2: = %f\n", $$.r);
            }
    }
    | arit3 {$$ = $1;}
    ;
arit3: '(' arit ')' {$$=$2;}
    | valor {$$=$1;}
    ;
valor: INTEIRO {
        $$.type = 1;
        $$.i = $1;
    }
    | REAL {
        $$.type = 2;
        $$.r = $1;
    }
    | VAR {
        VARIAVELS * aux = srchVar(var0, $1);
        if (aux == NULL){
            printf ("ERRO: Variavel '%s' nao foi declarada.\n",$1);
            $$.r = 0;
            $$.i = 0;
            strcpy($$.t, "");
        } else{
            $$.type = aux->type;
            switch(aux->type){
                case 0: strcpy($$.t, aux->t); break;
                case 1: $$.i = aux->i; break;
                case 2: $$.r = aux->r; break;
            }
        }
    }
    | TEXTO { strcpy($$.t, $1); $$.type = 0;}
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
    | arit {
        if($1.type==0)
            $$ = atof($1.t);
        else if($1.type==1)
                $$ = (double)$1.i;
            else if($1.type==2)
                    $$ = $1.r;
    }
    ;

saida: arit {
        if($1.type==0)
            sprintf($$, "%s", $1.t);
        else if($1.type==1)
                sprintf($$, "%d", $1.i);
            else if($1.type==2)
                    sprintf($$, "%f", $1.r);
    } 
    | arit ',' saida {
        if($1.type==0)
            sprintf($$, "%s %s", $1.t, $3);
        else if($1.type==1)
                sprintf($$, "%d %s", $1.i, $3);
            else if($1.type==2)
                    sprintf($$, "%f %s", $1.r, $3);
    }
    | logica {sprintf($$, "%d", $1);} 
    | logica ',' saida {sprintf($$, "%d %s", $1, $3);}
    ;
if: IF logica ':' cod ELSE cod ';' {
       
    }
    | logica ':' cod ';' {
      
    }
    ;
for: FOR arit ':' cod ';' {printf("FOR CLOSE\n"); };
    ;

%%

#include "lex.yy.c"

int main(){
    yyin=fopen("calc_exemplo.txt", "r");
    yyparse();
    fclose(yyin);
    return 0;
}

int yywrap(){
    return 0;
}