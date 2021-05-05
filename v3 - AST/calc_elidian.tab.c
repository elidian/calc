/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "calc_elidian.y"

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

    #define name_size 50
    #define string_size 1000
    
    typedef struct variavels {
		char name[name_size];
        int type; // string se 0, int se 1, double se 2
        char tv[string_size];
        int iv;
        double rv;
		struct variavels * prox;
	} VARIAVELS;

    typedef struct varsi {
		char name[name_size];
        int v;
		struct varsi * prox;
	} VARSI;

    typedef struct vars {
		char name[name_size];
        double v;
		struct vars * prox;
	} VARS;

    typedef struct varst {
		char name[name_size];
		char v[string_size];
		struct varst * prox;
	} VARST;

    //add nova variável na lista
	VARS * ins(VARS *l, char n[]){
		VARS *aux =(VARS*)malloc(sizeof(VARS));
		if(!aux) {
            printf("out of space");
            exit(0);
        }
        strcpy(aux->name, n);
		aux->prox = l;
		return aux;
	}

    VARSI * insi(VARSI *l, char n[]){
		VARSI *aux =(VARSI*)malloc(sizeof(VARSI));
		if(!aux) {
            printf("out of space");
            exit(0);
        }
        strcpy(aux->name, n);
		aux->prox = l;
		return aux;
	}

    //add nova variável na lista
    VARST * inst(VARST *l, char n[]){
		VARST *aux =(VARST*)malloc(sizeof(VARST));
		if(!aux) {
            printf("out of space");
            exit(0);
        }
        strcpy(aux->name, n);
        strcpy(aux->v, "");
		aux->prox = l;
		return aux;
	}

    //busca uma variável na lista de variáveis
	VARSI *srchi(VARSI *l, char n[]){
		VARSI *aux = l;
		while(aux != NULL){
			if(strcmp(n, aux->name)==0) 
                break;
			else
                aux = aux->prox;
		}
		return aux;
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
    VARST *srcht(VARST *l, char n[]){
		VARST *aux = l;
		while(aux != NULL){
			if(strcmp(n,aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
	}

    // VERIFICAR SE DADO VALOR É REAL
    bool isreal(char test[]){
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

    VARSI *ivar = NULL;
	VARS *rvar = NULL;
    VARST *tvar = NULL;

    /*O nodetype serve para indicar o tipo de nó que está na árvore. Isso serve para a função eval() entender o que realizar naquele nó*/

    typedef struct ast { /*Estrutura de um nó*/
        int nodetype;
        struct ast *l; /*Esquerda*/
        struct ast *r; /*Direita*/
    }Ast; 

    typedef struct intval { /*Estrutura de um número*/
        int nodetype;
        int v;
    }Intval;

    typedef struct realval { /*Estrutura de um número*/
        int nodetype;
        double v;
    }Realval;

    typedef struct textoval { /*Estrutura de um número*/
        int nodetype;
        char v[string_size];
    }Textoval;

    typedef struct varval { /*Estrutura de um nome de variável, nesse exemplo uma variável é um número no vetor var[26]*/
        int nodetype;
        char var[name_size];
    }Varval;

    typedef struct flow { /*Estrutura de um desvio (if/else/while)*/
        int nodetype;
        Ast *cond;		/*condição*/
        Ast *tl;		/*then, ou seja, verdade*/
        Ast *el;		/*else*/
    }Flow;

    typedef struct symasgn { /*Estrutura para um nó de atribuição. Para atrubuir o valor de v em s*/
        int nodetype;
        char s[name_size];
        Ast *v;
    }Symasgn;

    typedef struct symasgnt { /*Estrutura para um nó de atribuição. Para atrubuir o valor de v em s*/
        int nodetype;
        char s[name_size];
        char v[string_size];
    }Symasgnt;

    //double var[26]; /*Variáveis*/
    //int aux;

    Ast * newast(int nodetype, Ast *l, Ast *r){ /*Função para criar um nó*/

        Ast *a = (Ast*) malloc(sizeof(Ast));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = nodetype;
        a->l = l;
        a->r = r;
        return a;
    }
    
    Ast * newint(int d) {			/*Função de que cria um número (folha)*/
        Intval *a = (Intval*) malloc(sizeof(Intval));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 'k';
        a->v = d;
        return (Ast*)a;
    }

    Ast * newreal(double d) {			/*Função de que cria um número (folha)*/
        Realval *a = (Realval*) malloc(sizeof(Realval));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 'K';
        a->v = d;
        return (Ast*)a;
    }

    Ast * newtexto(char d[]) {			/*Função de que cria um número (folha)*/
        Textoval *a = (Textoval*) malloc(sizeof(Textoval));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 'm';
        strcpy(a->v, d);
        return (Ast*)a;
    }

    Ast * newflow(int nodetype, Ast *cond, Ast *tl, Ast *el){ /*Função que cria um nó de if/else/while*/
        Flow *a = (Flow*)malloc(sizeof(Flow));
        if(!a) {
            printf("out of space");
        exit(0);
        }
        a->nodetype = nodetype;
        a->cond = cond;
        a->tl = tl;
        a->el = el;
        return (Ast *)a;
    }

    typedef struct flowfor{
        int nodetype;
        Ast* v1;
        Ast* v2;
        Ast* v3;
    }Flowfor;

    Ast * newflowfor(int nodetype, Ast *b1, Ast *b2, Ast *b3, Ast *tl, Ast *el){ /*Função que cria um nó de FOR*/
        Flow *a = (Flow*)malloc(sizeof(Flow));
        if(!a) {
            printf("out of space");
        exit(0);
        }
        Flowfor *b = (Flowfor*)malloc(sizeof(Flowfor));
        if(!b) {
            printf("out of space");
        exit(0);
        }
        b->nodetype = 'F';
        b->v1 = b1;
        b->v2 = b2;
        b->v3 = b3;
        a->nodetype = nodetype;
        a->cond = (Ast*)b;
        a->tl = tl;
        a->el = el;
        return (Ast *)a;
    }

    Ast * newcmp(int cmptype, Ast *l, Ast *r){ /*Função que cria um nó para testes lógicos*/
        Ast *a = (Ast*)malloc(sizeof(Ast));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = '0' + cmptype; /*Para pegar o tipe de teste, definido no arquivo.l e utilizar na função eval()*/
        a->l = l;
        a->r = r;
        return a;
    }
    // função pra declarar variavel e atribuir
    Ast * newvar(int t, char s[], Ast *v){
        Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = t; /*tipo i, r ou t, conforme arquivo .l*/
        strcpy(a->s, s); /*Símbolo/variável*/
        a->v = v; /*Valor*/
        return (Ast *)a;
    }

    Ast * newasgn(char s[], Ast *v) { /*Função para um nó de atribuição*/
        Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = '=';
        strcpy(a->s, s); /*Símbolo/variável*/
        a->v = v; /*Valor*/
        return (Ast *)a;
    }

    Ast * newasgnt(char s[], char v[]) { /*Função para um nó de atribuição*/
        Symasgnt *a = (Symasgnt*)malloc(sizeof(Symasgnt));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 'n';
        strcpy(a->s, s); /*Símbolo/variável*/
        strcpy(a->v, v); /*Valor*/
        return (Ast *)a;
    }

    Ast * newValorVal(char s[]) { /*Função que recupera o nome/referência de uma variável, neste caso o número*/    
        Varval *a = (Varval*) malloc(sizeof(Varval));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 'N';
        strcpy(a->var, s);
        return (Ast*)a;
    }

    double eval(Ast *a) { /*Função que executa operações a partir de um nó*/
        double v;
        if(!a) {
            printf("internal error, null eval\n");
            return 0.0;
        }
        switch(a->nodetype) {
            case 'k': v = ((Intval *)a)->v; break; 	/*Recupera um número inteiro*/
            case 'K': v = ((Realval *)a)->v; break; 	/*Recupera um número real*/
            case 'm': v = atof(((Textoval *)a)->v); break; 	/*Recupera um número real dentro de string*/
            case 'N':;
                VARS * aux = (VARS*)malloc(sizeof(VARS));
                aux = srch(rvar, ((Varval*)a)->var);
                if (!aux){
                    VARSI * aux2 = srchi(ivar, ((Varval*)a)->var);
                    if (!aux2){
                        VARST * auxt = srcht(tvar, ((Varval*)a)->var);
                        if (!auxt){
                            printf ("337 - Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                            v = 0.0;
                        }
                        else{
                            v = atof(auxt->v);
                        }
                    }
                    else{
                        v = (double)aux2->v;
                    }
                }
                else{
                    v = aux->v;
                }
                break;
            case 'n':;
                VARS * auxn = (VARS*)malloc(sizeof(VARS));
                auxn = srch(rvar, ((Varval*)a)->var);
                if (!auxn){
                    VARSI * auxn2 = srchi(ivar, ((Varval*)a)->var);
                    if (!auxn2){
                        VARST * auxn3 = srcht(tvar, ((Varval*)a)->var);
                        if (!auxn3){
                            printf ("359 - Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                            v = 0.0;
                        }
                        else{
                            Ast * auxnt = (Ast*)malloc(sizeof(Ast));
                            if(!auxnt){
                                printf("out of space");
                                exit(0);
                            }
                            auxnt->nodetype = 'P';
                            auxnt->l = newtexto(auxn3->v);
                            eval(auxnt);
                            v = atof(auxn3->v);
                        }
                    }
                    else{
                        Ast * auxni = (Ast*)malloc(sizeof(Ast));
                        if(!auxni){
                            printf("out of space");
                            exit(0);
                        }
                        auxni->nodetype = 'P';
                        auxni->l = newint(auxn2->v);
                        eval(auxni);
                        v = (double)auxn2->v;
                    }
                }
                else{
                    Ast * auxnr = (Ast*)malloc(sizeof(Ast));
                    if(!auxnr){
                        printf("out of space");
                        exit(0);
                    }
                    auxnr->nodetype = 'P';
                    auxnr->l = newreal(auxn->v);
                    eval(auxnr);
                    v = auxn->v;
                }
                break;
            case '+': v = eval(a->l) + eval(a->r); break;	/*Operações "árv esq   +   árv dir"*/
            case '-': v = eval(a->l) - eval(a->r); break;	/*Operações*/
            case '*': v = eval(a->l) * eval(a->r); break;	/*Operações*/
            case '/': v = eval(a->l) / eval(a->r); break; /*Operações*/
            case 'S': v = sin(eval(a->l)); break;				/*Operações SIN*/
            case 'C': v = cos(eval(a->l)); break;				/*Operações COS*/
            case 'R': v = sqrt(eval(a->l)); break;				/*Operações RAIZ*/
            case 'M': v = -eval(a->l); break;				/*Operações, número negativo*/
            case 'A': v = fabs(eval(a->l)); break;

            case '1': v = (eval(a->l) > eval(a->r))? 1 : 0; break;	/*Operações lógicas. "árv esq   >   árv dir"  Se verdade 1, falso 0*/
            case '2': v = (eval(a->l) < eval(a->r))? 1 : 0; break;
            case '3': v = (eval(a->l) != eval(a->r))? 1 : 0; break;
            case '4': v = (eval(a->l) == eval(a->r))? 1 : 0; break;
            case '5': v = (eval(a->l) >= eval(a->r))? 1 : 0; break;
            case '6': v = (eval(a->l) <= eval(a->r))? 1 : 0; break;
            case '7': v = (eval(a->l) || eval(a->r))? 1 : 0; break;
            case '8': v = (eval(a->l) && eval(a->r))? 1 : 0; break;
            
            case '=':;
                v = eval(((Symasgn *)a)->v); /*Recupera o valor*/
                
                VARS * x = (VARS*)malloc(sizeof(VARS));
                if(!x) {
                    printf("out of space");
                    exit(0);
                }
                x = srch(rvar, ((Symasgn *)a)->s);
                if(!x){
                    VARSI * xi = (VARSI*)malloc(sizeof(VARSI));
                    if(!xi) {
                        printf("out of space");
                        exit(0);
                    }
                    xi = srchi(ivar, ((Symasgn *)a)->s);
                    if(!xi){
                        VARST * xt = (VARST*)malloc(sizeof(VARST));
                        if(!xt) {
                            printf("out of space");
                            exit(0);
                        }
                        xt = srcht(tvar, ((Symasgn *)a)->s);
                        if(!xt){
                            printf("Erro de var nao declarada\n");
                            v = 0.0;
                        } else
                            strcpy(xt->v, ((Textoval*)((Symasgn *)a)->v)->v); /*Atribui à variável*/
                    } else
                        xi->v = (int)v; /*Atribui à variável*/
                } else
                    x->v = v;   /*Atribui à variável*/
                break;
            /*CASO IF*/
            case 'I': 
                if (eval(((Flow *)a)->cond) != 0) {	/*executa a condição / teste*/
                    if (((Flow *)a)->tl)		/*Se existir árvore*/
                        v = eval(((Flow *)a)->tl); /*Verdade*/
                    else
                        v = 0.0;
                } else {
                    if( ((Flow *)a)->el ) {
                        v = eval(((Flow *)a)->el); /*Falso*/
                    } else
                        v = 0.0;
                    }
                break;
            /*CASO WHILE*/
            case 'W':
                v = 0.0;
                if( ((Flow *)a)->tl ) {
                    while( eval(((Flow *)a)->cond) != 0){
                        v = eval(((Flow *)a)->tl);
                        }
                }
            break;
            /*CASO FOR*/
            case 'F':
                v = 0.0;
                /*
                if( ((Flow *)a)->tl ) {
                    for(eval(((Flowfor*)((Flow *)a)->cond)->v1); 
                        eval(((Flowfor*)((Flow *)a)->cond)->v2); 
                        eval(((Flowfor*)((Flow *)a)->cond)->v3)
                        ){
                            v =  eval(((Flow *)a)->tl);
                    }
                }//*/
                if( ((Flow *)a)->tl ){
                    char name[name_size];
                    if(((Symasgn*)((Flowfor*)((Flow *)a)->cond)->v1)->s){
                        strcpy(name, ((Symasgn*)((Flowfor*)((Flow *)a)->cond)->v1)->s);
                    }
                    if(((Flowfor*)((Flow *)a)->cond)->v1)
                        v = eval(((Flowfor*)((Flow *)a)->cond)->v1);
                    VARS* auxrf = srch(rvar, name);
                    if(auxrf){
                        for(auxrf->v; 
                            eval(((Flowfor*)((Flow *)a)->cond)->v2); 
                            auxrf->v += eval(((Flowfor*)((Flow *)a)->cond)->v3)
                            ){
                                v =  eval(((Flow *)a)->tl);
                        }
                    } else {
                        VARSI* auxif = srchi(ivar, name);
                        if(auxif){
                            for(auxif->v; 
                                eval(((Flowfor*)((Flow *)a)->cond)->v2); 
                                auxif->v += eval(((Flowfor*)((Flow *)a)->cond)->v3)
                                ){
                                    v =  eval(((Flow *)a)->tl);
                            }
                        } else {
                            printf("Erro no FOR: variavel nao numerica\n");
                        }
                    }
                }
            break;
            // multiplas linhas de códigos em IF/ELSE/WHILE/FOR
            case 'L': eval(a->l); v = eval(a->r); break; /*Lista de operções em um bloco IF/ELSE/WHILE. Assim o analisador não se perde entre os blocos*/
            // print na tela
            case 'P': 
                    if(!a->l)
                        break;
                    //printf("P - %c\n", a->l->nodetype);
                    if(a->l->nodetype == 'N'){
                        a->l->nodetype = 'n';
                        v = eval(a->l);
                    } else {
                        v = eval(a->l);
                        if(a->l->nodetype != 'n' && a->l->nodetype != 'k' && a->l->nodetype != 'K' && a->l->nodetype != 'm')
                            printf("%.2f\n", v);
                    }
                    if(((Intval*)a->l)->nodetype == 'k')
                        printf ("%d\n", ((Intval*)a->l)->v);		/*Recupera um valor inteiro*/
                    else if(((Realval*)a->l)->nodetype == 'K')
                        printf ("%.2f\n", ((Realval*)a->l)->v);		/*Recupera um valor real*/
                    else if(((Textoval*)a->l)->nodetype == 'm')
                        printf ("%s\n", ((Textoval*)a->l)->v);		/*Recupera um valor real*/
                    break;  /*Função que imprime um valor*/

            // declarar variavel inteiro
            case 'i':;
                ivar = insi(ivar, ((Symasgn *)a)->s);
                VARSI * xi = (VARSI*)malloc(sizeof(VARSI));
                if(!xi) {
                    printf("out of space");
                    exit(0);
                }
                xi = srchi(ivar, ((Symasgn *)a)->s);
                if(((Symasgn *)a)->v)
                    xi->v = (int)eval(((Symasgn *)a)->v); /*Atribui à variável*/
                break;
            // declarar variavel real
            case 'r':;
                rvar = ins(rvar, ((Symasgn *)a)->s);
                VARS * xr = (VARS*)malloc(sizeof(VARS));
                if(!xr) {
                    printf("out of space");
                    exit(0);
                }
                xr = srch(rvar, ((Symasgn *)a)->s);
                if(((Symasgn *)a)->v)
                    xr->v = eval(((Symasgn *)a)->v);
                break;
            // declarar variavel texto
            case 't':;
                tvar = inst(tvar, ((Symasgn *)a)->s);
                VARST * xt = (VARST*)malloc(sizeof(VARST));
                if(!xt) {
                    printf("out of space");
                    exit(0);
                }
                xt = srcht(tvar, ((Symasgn *)a)->s);
                if((((Symasgn *)a)->v))
                    strcpy(xt->v, ((Textoval*)((Symasgn*)a)->v)->v);
                break;

            
            // leitura das variaveis: int, real e texto
            case 'c':; 
                //v = eval(((Symasgn *)a)->v); /*Recupera o valor*/
                VARS * xcr = (VARS*)malloc(sizeof(VARS));
                if(!xcr) {
                    printf("out of space");
                    exit(0);
                }
                xcr = srch(rvar, ((Varval *)a->l)->var);
                if(xcr){
                    scanf("%f", &xcr->v);
                } else {
                    VARSI * xci = (VARSI*)malloc(sizeof(VARSI));
                    if(!xci) {
                        printf("out of space");
                        exit(0);
                    }
                    xci = srchi(ivar, ((Varval *)a->l)->var);
                    if(xci){
                        scanf("%d", &xci->v);
                    } else {
                        VARST * xct = (VARST*)malloc(sizeof(VARST));
                        if(!xct) {
                            printf("out of space");
                            exit(0);
                        }
                        xct = srcht(tvar, ((Varval *)a->l)->var);
                        if(xct){
                            scanf("%s", &xct->v);
                        } else {
                            printf("Variavel inválida!\n");
                        }
                    }
                }
                break;

            default: printf("internal error: bad node %c\n", a->nodetype);
        }
        return v;
    }


#line 707 "calc_elidian.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TIPO = 258,                    /* TIPO  */
    INTEIRO = 259,                 /* INTEIRO  */
    REAL = 260,                    /* REAL  */
    TEXTO = 261,                   /* TEXTO  */
    ENTRADA = 262,                 /* ENTRADA  */
    SAIDA = 263,                   /* SAIDA  */
    INICIO = 264,                  /* INICIO  */
    FINAL = 265,                   /* FINAL  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    FOR = 268,                     /* FOR  */
    WHILE = 269,                   /* WHILE  */
    VAR = 270,                     /* VAR  */
    COMENTARIO = 271,              /* COMENTARIO  */
    RAIZ = 272,                    /* RAIZ  */
    COS = 273,                     /* COS  */
    SIN = 274,                     /* SIN  */
    REST = 275,                    /* REST  */
    MAIOR = 276,                   /* MAIOR  */
    MENOR = 277,                   /* MENOR  */
    MEI = 278,                     /* MEI  */
    MAI = 279,                     /* MAI  */
    II = 280,                      /* II  */
    DIF = 281,                     /* DIF  */
    OR = 282,                      /* OR  */
    AND = 283,                     /* AND  */
    IMUNUS = 284,                  /* IMUNUS  */
    IFX = 285                      /* IFX  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 637 "calc_elidian.y"

    char texto[50];
    int inteiro;
    double real;
    Ast *a;

#line 791 "calc_elidian.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TIPO = 3,                       /* TIPO  */
  YYSYMBOL_INTEIRO = 4,                    /* INTEIRO  */
  YYSYMBOL_REAL = 5,                       /* REAL  */
  YYSYMBOL_TEXTO = 6,                      /* TEXTO  */
  YYSYMBOL_ENTRADA = 7,                    /* ENTRADA  */
  YYSYMBOL_SAIDA = 8,                      /* SAIDA  */
  YYSYMBOL_INICIO = 9,                     /* INICIO  */
  YYSYMBOL_FINAL = 10,                     /* FINAL  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_VAR = 15,                       /* VAR  */
  YYSYMBOL_COMENTARIO = 16,                /* COMENTARIO  */
  YYSYMBOL_RAIZ = 17,                      /* RAIZ  */
  YYSYMBOL_COS = 18,                       /* COS  */
  YYSYMBOL_SIN = 19,                       /* SIN  */
  YYSYMBOL_REST = 20,                      /* REST  */
  YYSYMBOL_MAIOR = 21,                     /* MAIOR  */
  YYSYMBOL_MENOR = 22,                     /* MENOR  */
  YYSYMBOL_MEI = 23,                       /* MEI  */
  YYSYMBOL_MAI = 24,                       /* MAI  */
  YYSYMBOL_II = 25,                        /* II  */
  YYSYMBOL_DIF = 26,                       /* DIF  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_29_ = 29,                       /* '='  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_34_ = 34,                       /* '^'  */
  YYSYMBOL_35_ = 35,                       /* ')'  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_IMUNUS = 37,                    /* IMUNUS  */
  YYSYMBOL_IFX = 38,                       /* IFX  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* ':'  */
  YYSYMBOL_42_ = 42,                       /* '|'  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_prog = 44,                      /* prog  */
  YYSYMBOL_cod = 45,                       /* cod  */
  YYSYMBOL_atrib = 46,                     /* atrib  */
  YYSYMBOL_exp = 47,                       /* exp  */
  YYSYMBOL_list = 48,                      /* list  */
  YYSYMBOL_arit = 49,                      /* arit  */
  YYSYMBOL_arit1 = 50,                     /* arit1  */
  YYSYMBOL_arit2 = 51,                     /* arit2  */
  YYSYMBOL_arit3 = 52,                     /* arit3  */
  YYSYMBOL_valor = 53,                     /* valor  */
  YYSYMBOL_logica = 54,                    /* logica  */
  YYSYMBOL_L1 = 55,                        /* L1  */
  YYSYMBOL_L2 = 56                         /* L2  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    35,    32,    30,     2,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,     2,
       2,    29,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    34,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,    42,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   680,   680,   682,   683,   685,   686,   688,   689,   690,
     691,   692,   693,   694,   695,   696,   697,   698,   699,   700,
     702,   703,   705,   706,   707,   708,   709,   710,   711,   712,
     714,   715,   716,   717,   719,   720,   723,   725,   726,   728,
     730,   731,   732,   733,   734,   735,   736,   737,   738,   740,
     742,   743
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TIPO", "INTEIRO",
  "REAL", "TEXTO", "ENTRADA", "SAIDA", "INICIO", "FINAL", "IF", "ELSE",
  "FOR", "WHILE", "VAR", "COMENTARIO", "RAIZ", "COS", "SIN", "REST",
  "MAIOR", "MENOR", "MEI", "MAI", "II", "DIF", "OR", "AND", "'='", "'+'",
  "'-'", "'*'", "'/'", "'^'", "')'", "'('", "IMUNUS", "IFX", "'{'", "'}'",
  "':'", "'|'", "$accept", "prog", "cod", "atrib", "exp", "list", "arit",
  "arit1", "arit2", "arit3", "valor", "logica", "L1", "L2", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    61,
      43,    45,    42,    47,    94,    41,    40,   284,   285,   123,
     125,    58,   124
};
#endif

#define YYPACT_NINF (-63)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,   -63,    26,    63,   -63,    17,    10,   -63,   107,    32,
     107,     2,   -63,   107,   -63,   -63,    31,   -63,   -63,   -63,
     -63,    21,    25,    34,   165,   107,   165,   -20,     1,   -63,
      30,   -63,   -63,   191,   -63,    33,    60,    53,    46,    49,
     -63,    50,   -63,    79,   165,   165,   165,   -63,    56,   -12,
      35,    35,    35,    35,    35,    35,   107,   107,   107,   107,
     107,   107,   107,   107,   195,    66,   107,   107,   195,   -63,
     -63,   -63,   -63,   -18,    18,    28,   -63,   -63,     1,     1,
     -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   120,   107,    62,   137,   -63,   -63,   -63,
      95,   -63,   165,   -63,    69,    12,   195,   195,   151,   160,
     -63,   -63
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     1,     0,     0,     2,     0,     0,
       0,     0,    16,     0,     7,     3,     9,    37,    38,    18,
      39,     0,     0,     0,     0,     0,     0,    51,    29,    33,
      35,    36,    17,    48,    49,     0,     0,     0,     0,     0,
      11,     0,    19,     0,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       5,    10,     6,     0,     0,     0,    50,    26,    27,    28,
      32,    30,    31,    34,    40,    41,    45,    44,    43,    42,
      46,    47,    20,     0,     0,     0,     0,    24,    23,    22,
      12,    21,     0,    14,     0,     0,     0,     0,     0,     0,
      13,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -63,   -63,   -63,   100,    -3,   -62,   -22,   -14,    47,   -63,
     -63,    -5,   -63,   164
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    14,    92,    93,    27,    28,    29,    30,
      31,    70,    33,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      15,    32,    47,    35,    49,    39,    96,     1,    42,    40,
      50,    51,    50,    51,    17,    18,    19,    97,    50,    51,
      48,    52,    73,    74,    75,    20,     4,    21,    22,    23,
      77,    41,    16,    53,    54,    36,    78,    79,    72,    17,
      18,    24,    50,    51,   108,   109,    25,    37,    50,    51,
      20,   107,    26,    98,    17,    18,    69,    44,    50,    51,
      43,    45,    95,    99,    55,    20,     5,    21,    22,    23,
      46,     6,    64,     7,     8,    65,     9,    10,    11,    12,
     105,    24,    66,    17,    18,    71,    25,    67,    68,    72,
     101,    76,    26,   101,    20,    94,    21,    22,    23,    80,
      81,    82,    83,   102,    13,   101,   101,   104,   106,    38,
      24,    17,    18,     0,     0,    25,     0,     0,     0,     0,
       0,    26,    20,     5,    21,    22,    23,     0,     6,     0,
       0,     8,     0,     9,    10,    11,    12,     0,    24,     0,
       5,     0,     0,    25,     0,     6,     0,     0,     8,    26,
       9,    10,    11,    12,     5,     0,     0,     0,     0,     6,
     100,    13,     8,     5,     9,    10,    11,    12,     6,    17,
      18,     8,     0,     9,    10,    11,    12,   103,    13,     0,
      20,     0,    21,    22,    23,     0,     0,     0,     0,     0,
       0,   110,    13,     0,     0,     0,    24,     0,     5,     0,
     111,    13,     0,     6,     0,     0,     8,    26,     9,    10,
      11,    12,    56,    57,    58,    59,    60,    61,    62,    63,
      84,    85,    86,    87,    88,    89,    90,    91,     0,     0,
       0,     0,     0,     0,     0,     0,    13
};

static const yytype_int8 yycheck[] =
{
       3,     6,    24,     8,    26,    10,    68,     9,    13,     7,
      30,    31,    30,    31,     4,     5,     6,    35,    30,    31,
      25,    20,    44,    45,    46,    15,     0,    17,    18,    19,
      42,    29,    15,    32,    33,     3,    50,    51,    43,     4,
       5,    31,    30,    31,   106,   107,    36,    15,    30,    31,
      15,    39,    42,    35,     4,     5,     6,    36,    30,    31,
      29,    36,    67,    35,    34,    15,     3,    17,    18,    19,
      36,     8,    39,    10,    11,    15,    13,    14,    15,    16,
     102,    31,    29,     4,     5,     6,    36,    41,    39,    94,
      93,    35,    42,    96,    15,    29,    17,    18,    19,    52,
      53,    54,    55,    41,    41,   108,   109,    12,    39,     9,
      31,     4,     5,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    42,    15,     3,    17,    18,    19,    -1,     8,    -1,
      -1,    11,    -1,    13,    14,    15,    16,    -1,    31,    -1,
       3,    -1,    -1,    36,    -1,     8,    -1,    -1,    11,    42,
      13,    14,    15,    16,     3,    -1,    -1,    -1,    -1,     8,
      40,    41,    11,     3,    13,    14,    15,    16,     8,     4,
       5,    11,    -1,    13,    14,    15,    16,    40,    41,    -1,
      15,    -1,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    -1,    -1,    -1,    31,    -1,     3,    -1,
      40,    41,    -1,     8,    -1,    -1,    11,    42,    13,    14,
      15,    16,    21,    22,    23,    24,    25,    26,    27,    28,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    44,    45,     0,     3,     8,    10,    11,    13,
      14,    15,    16,    41,    46,    47,    15,     4,     5,     6,
      15,    17,    18,    19,    31,    36,    42,    49,    50,    51,
      52,    53,    54,    55,    56,    54,     3,    15,    46,    54,
       7,    29,    54,    29,    36,    36,    36,    49,    54,    49,
      30,    31,    20,    32,    33,    34,    21,    22,    23,    24,
      25,    26,    27,    28,    39,    15,    29,    41,    39,     6,
      54,     6,    54,    49,    49,    49,    35,    42,    50,    50,
      51,    51,    51,    51,    56,    56,    56,    56,    56,    56,
      56,    56,    47,    48,    29,    54,    48,    35,    35,    35,
      40,    47,    41,    40,    12,    49,    39,    39,    48,    48,
      40,    40
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      48,    48,    49,    49,    49,    49,    49,    49,    49,    49,
      50,    50,    50,    50,    51,    51,    52,    53,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      56,    56
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     3,     4,     1,     3,     2,
       4,     2,     5,     9,     5,     9,     1,     2,     2,     2,
       1,     2,     4,     4,     4,     2,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* prog: INICIO cod FINAL  */
#line 680 "calc_elidian.y"
                       {printf("\nPROGRAMA FINALIZADO\n\n");}
#line 1913 "calc_elidian.tab.c"
    break;

  case 3: /* cod: cod exp  */
#line 682 "calc_elidian.y"
             {eval((yyvsp[0].a));}
#line 1919 "calc_elidian.tab.c"
    break;

  case 5: /* atrib: VAR '=' logica  */
#line 685 "calc_elidian.y"
                      {(yyval.a) = newasgn((yyvsp[-2].texto), (yyvsp[0].a));}
#line 1925 "calc_elidian.tab.c"
    break;

  case 6: /* atrib: TIPO VAR '=' logica  */
#line 686 "calc_elidian.y"
                          {(yyval.a) = newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), (yyvsp[0].a));}
#line 1931 "calc_elidian.tab.c"
    break;

  case 7: /* exp: atrib  */
#line 688 "calc_elidian.y"
           {(yyval.a) = (yyvsp[0].a);}
#line 1937 "calc_elidian.tab.c"
    break;

  case 8: /* exp: VAR '=' TEXTO  */
#line 689 "calc_elidian.y"
                    {(yyval.a) = newasgn((yyvsp[-2].texto), newtexto((yyvsp[0].texto)));}
#line 1943 "calc_elidian.tab.c"
    break;

  case 9: /* exp: TIPO VAR  */
#line 690 "calc_elidian.y"
               {(yyval.a) = newvar((yyvsp[-1].inteiro), (yyvsp[0].texto), NULL);}
#line 1949 "calc_elidian.tab.c"
    break;

  case 10: /* exp: TIPO VAR '=' TEXTO  */
#line 691 "calc_elidian.y"
                         {(yyval.a) = newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), newtexto((yyvsp[0].texto)));}
#line 1955 "calc_elidian.tab.c"
    break;

  case 11: /* exp: VAR ENTRADA  */
#line 692 "calc_elidian.y"
                  {(yyval.a) = newast('c', newValorVal((yyvsp[-1].texto)), NULL);}
#line 1961 "calc_elidian.tab.c"
    break;

  case 12: /* exp: IF logica '{' list '}'  */
#line 693 "calc_elidian.y"
                                       {(yyval.a) = newflow('I', (yyvsp[-3].a), (yyvsp[-1].a), NULL);}
#line 1967 "calc_elidian.tab.c"
    break;

  case 13: /* exp: IF logica '{' list '}' ELSE '{' list '}'  */
#line 694 "calc_elidian.y"
                                                   {(yyval.a) = newflow('I', (yyvsp[-7].a), (yyvsp[-5].a), (yyvsp[-1].a));}
#line 1973 "calc_elidian.tab.c"
    break;

  case 14: /* exp: WHILE logica '{' list '}'  */
#line 695 "calc_elidian.y"
                                    {(yyval.a) = newflow('W', (yyvsp[-3].a), (yyvsp[-1].a), NULL);}
#line 1979 "calc_elidian.tab.c"
    break;

  case 15: /* exp: FOR atrib ':' logica ':' arit '{' list '}'  */
#line 696 "calc_elidian.y"
                                                 {(yyval.a) = newflowfor('F', (yyvsp[-7].a), (yyvsp[-5].a), (yyvsp[-3].a), (yyvsp[-1].a), NULL);}
#line 1985 "calc_elidian.tab.c"
    break;

  case 16: /* exp: COMENTARIO  */
#line 697 "calc_elidian.y"
                 {(yyval.a) = newast('P', NULL, NULL);}
#line 1991 "calc_elidian.tab.c"
    break;

  case 17: /* exp: SAIDA logica  */
#line 698 "calc_elidian.y"
                   { (yyval.a) = newast('P', (yyvsp[0].a),NULL);}
#line 1997 "calc_elidian.tab.c"
    break;

  case 18: /* exp: SAIDA TEXTO  */
#line 699 "calc_elidian.y"
                  {(yyval.a) = newast('P', newtexto((yyvsp[0].texto)), NULL);}
#line 2003 "calc_elidian.tab.c"
    break;

  case 19: /* exp: ':' logica  */
#line 700 "calc_elidian.y"
                 {(yyval.a) = (yyvsp[0].a);}
#line 2009 "calc_elidian.tab.c"
    break;

  case 20: /* list: exp  */
#line 702 "calc_elidian.y"
          {(yyval.a) = (yyvsp[0].a);}
#line 2015 "calc_elidian.tab.c"
    break;

  case 21: /* list: list exp  */
#line 703 "calc_elidian.y"
               { (yyval.a) = newast('L', (yyvsp[-1].a), (yyvsp[0].a));}
#line 2021 "calc_elidian.tab.c"
    break;

  case 22: /* arit: SIN '(' arit ')'  */
#line 705 "calc_elidian.y"
                       {(yyval.a) = newast('S',(yyvsp[-1].a),NULL);}
#line 2027 "calc_elidian.tab.c"
    break;

  case 23: /* arit: COS '(' arit ')'  */
#line 706 "calc_elidian.y"
                       {(yyval.a) = newast('C',(yyvsp[-1].a),NULL);}
#line 2033 "calc_elidian.tab.c"
    break;

  case 24: /* arit: RAIZ '(' arit ')'  */
#line 707 "calc_elidian.y"
                        {(yyval.a) = newast('R',(yyvsp[-1].a),NULL);}
#line 2039 "calc_elidian.tab.c"
    break;

  case 25: /* arit: '-' arit  */
#line 708 "calc_elidian.y"
                            {(yyval.a) = newast('M',(yyvsp[0].a),NULL);}
#line 2045 "calc_elidian.tab.c"
    break;

  case 26: /* arit: '|' arit '|'  */
#line 709 "calc_elidian.y"
                   {(yyval.a) = newast('A',(yyvsp[-1].a),NULL);}
#line 2051 "calc_elidian.tab.c"
    break;

  case 27: /* arit: arit '+' arit1  */
#line 710 "calc_elidian.y"
                     {(yyval.a) = newast('+',(yyvsp[-2].a),(yyvsp[0].a));}
#line 2057 "calc_elidian.tab.c"
    break;

  case 28: /* arit: arit '-' arit1  */
#line 711 "calc_elidian.y"
                     {(yyval.a) = newast('-',(yyvsp[-2].a),(yyvsp[0].a));}
#line 2063 "calc_elidian.tab.c"
    break;

  case 29: /* arit: arit1  */
#line 712 "calc_elidian.y"
            {(yyval.a)=(yyvsp[0].a);}
#line 2069 "calc_elidian.tab.c"
    break;

  case 30: /* arit1: arit1 '*' arit2  */
#line 714 "calc_elidian.y"
                       {(yyval.a) = newast('*',(yyvsp[-2].a),(yyvsp[0].a));}
#line 2075 "calc_elidian.tab.c"
    break;

  case 31: /* arit1: arit1 '/' arit2  */
#line 715 "calc_elidian.y"
                      {(yyval.a) = newast('/',(yyvsp[-2].a),(yyvsp[0].a));}
#line 2081 "calc_elidian.tab.c"
    break;

  case 32: /* arit1: arit1 REST arit2  */
#line 716 "calc_elidian.y"
                       {(yyval.a) = newast('%',(yyvsp[-2].a),(yyvsp[0].a));}
#line 2087 "calc_elidian.tab.c"
    break;

  case 33: /* arit1: arit2  */
#line 717 "calc_elidian.y"
            {(yyval.a)=(yyvsp[0].a);}
#line 2093 "calc_elidian.tab.c"
    break;

  case 34: /* arit2: arit3 '^' arit2  */
#line 719 "calc_elidian.y"
                       {(yyval.a) = newast('^',(yyvsp[-2].a),(yyvsp[0].a));}
#line 2099 "calc_elidian.tab.c"
    break;

  case 35: /* arit2: arit3  */
#line 720 "calc_elidian.y"
            {(yyval.a)=(yyvsp[0].a);}
#line 2105 "calc_elidian.tab.c"
    break;

  case 36: /* arit3: valor  */
#line 723 "calc_elidian.y"
           {(yyval.a) = (yyvsp[0].a);}
#line 2111 "calc_elidian.tab.c"
    break;

  case 37: /* valor: INTEIRO  */
#line 725 "calc_elidian.y"
               {(yyval.a) = newint((yyvsp[0].inteiro));}
#line 2117 "calc_elidian.tab.c"
    break;

  case 38: /* valor: REAL  */
#line 726 "calc_elidian.y"
           {(yyval.a) = newreal((yyvsp[0].real));}
#line 2123 "calc_elidian.tab.c"
    break;

  case 39: /* valor: VAR  */
#line 728 "calc_elidian.y"
          {(yyval.a) = newValorVal((yyvsp[0].texto));}
#line 2129 "calc_elidian.tab.c"
    break;

  case 40: /* logica: L1 MAIOR L2  */
#line 730 "calc_elidian.y"
                    {(yyval.a) = newcmp(1,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2135 "calc_elidian.tab.c"
    break;

  case 41: /* logica: L1 MENOR L2  */
#line 731 "calc_elidian.y"
                  {(yyval.a) = newcmp(2,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2141 "calc_elidian.tab.c"
    break;

  case 42: /* logica: L1 DIF L2  */
#line 732 "calc_elidian.y"
                {(yyval.a) = newcmp(3,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2147 "calc_elidian.tab.c"
    break;

  case 43: /* logica: L1 II L2  */
#line 733 "calc_elidian.y"
               {(yyval.a) = newcmp(4,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2153 "calc_elidian.tab.c"
    break;

  case 44: /* logica: L1 MAI L2  */
#line 734 "calc_elidian.y"
                {(yyval.a) = newcmp(5,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2159 "calc_elidian.tab.c"
    break;

  case 45: /* logica: L1 MEI L2  */
#line 735 "calc_elidian.y"
                {(yyval.a) = newcmp(6,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2165 "calc_elidian.tab.c"
    break;

  case 46: /* logica: L1 OR L2  */
#line 736 "calc_elidian.y"
               {(yyval.a) = newcmp(7,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2171 "calc_elidian.tab.c"
    break;

  case 47: /* logica: L1 AND L2  */
#line 737 "calc_elidian.y"
                {(yyval.a) = newcmp(8,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2177 "calc_elidian.tab.c"
    break;

  case 48: /* logica: L1  */
#line 738 "calc_elidian.y"
         {(yyval.a) = (yyvsp[0].a);}
#line 2183 "calc_elidian.tab.c"
    break;

  case 49: /* L1: L2  */
#line 740 "calc_elidian.y"
       {(yyval.a)=(yyvsp[0].a);}
#line 2189 "calc_elidian.tab.c"
    break;

  case 50: /* L2: '(' logica ')'  */
#line 742 "calc_elidian.y"
                    {(yyval.a) = (yyvsp[-1].a);}
#line 2195 "calc_elidian.tab.c"
    break;

  case 51: /* L2: arit  */
#line 743 "calc_elidian.y"
           {(yyval.a)=(yyvsp[0].a);}
#line 2201 "calc_elidian.tab.c"
    break;


#line 2205 "calc_elidian.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 745 "calc_elidian.y"


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
