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

    #define name_size 30
    #define string_size 1000

    typedef struct variavels {
		char name[name_size];
        int type; // string se 0, int se 1, double se 2
        char tv[string_size];
        int iv;
        double rv;
		struct variavels * prox;
	} VARIAVELS;

    typedef struct ast { /*Estrutura de um nó*/
        int nodetype;
        struct ast *l; /*Esquerda*/
        struct ast *r; /*Direita*/
    }Ast; 

    typedef struct vars {
		char name[name_size];
        double v;
		struct vars * prox;
	} VARS;

    typedef struct varsi {
		char name[name_size];
        int v;
		struct varsi * prox;
	} VARSI;

    typedef struct varst {
		char name[name_size];
		char v[string_size];
		struct varst * prox;
	} VARST;
    // estrutura de vetor geral
    typedef struct vec {
		int nodetype;
        int tam;
        char name[name_size]; 
        double *v;
        //struct veci * in;
		struct vec * prox;
	} Vec;
    // estrutura de vetor inteiro
    typedef struct veci {
		int nodetype;
        int tam;
        char name[name_size];
        int *v;
        //struct veci * in;
		struct veci * prox;
	} Veci;
    // estrutura de vetor real
    typedef struct vecr {
		int nodetype;
        int tam;
		char name[name_size];
        double *v;
        //struct veci * in;
		struct vecr * prox;
	} Vecr;
    // estrutura de vetor caractere
    typedef struct vect {
		int nodetype;
        int tam;
		char name[name_size];
        char **v;
        //struct veci * in;
		struct vect * prox;
	} Vect;
    typedef struct varfunction {
        int nodetype;
		char name[name_size];
        double v;
		struct varfunction * prox;
	} Varfunction;

    // struct funtion
    typedef struct function {
        int nodetype;
		char name[name_size];
        struct varfunction *var;
        Ast *args;
        Ast *v;
		struct function * prox;
	} Function;
    
    typedef struct func {
        int nodetype;
        int type;
		char name[name_size];
        Ast *args;
        Ast *v;
	} Func;

    typedef struct symasgn { /*Estrutura para um nó de atribuição. Para atrubuir o valor de v em s*/
        int nodetype;
        int type;
        char s[name_size];
        Ast *tam;
        Ast *v;
        Ast *n;
    }Symasgn;

    typedef struct flow { /*Estrutura de um desvio (if/else/while)*/
        int nodetype;
        Ast *cond;		/*condição*/
        Ast *tl;		/*then, ou seja, verdade*/
        Ast *el;		/*else*/
    }Flow;

    typedef struct flowfor{
        int nodetype;
        Ast* v1;
        Ast* v2;
        Ast* v3;
    }Flowfor;

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
        Ast *pos;
    }Varval;

    typedef struct listavar {
        char name[name_size];
        VARSI *ivar;
        VARS *rvar;
        VARST *tvar;
        Vecr * rvec;
        Veci * ivec;
        Vect * tvec;
        Function *function;
        struct listavar * prox;
    } Listavar;

    //add nova variável na lista
	VARS * ins(VARS *l, char n[]){
		//printf("ins begin\n");
        VARS *aux =(VARS*)malloc(sizeof(VARS));
		if(!aux) {
            printf("out of space 'ins()'\n");
            exit(0);
        }
        strcpy(aux->name, n);
		aux->prox = l;
        //printf("ins end\n");
		return aux;
	}

    //busca uma variável na lista de variáveis
	VARS *srch(VARS *aux, char n[]){
		//printf("srch begin\n");
        //int i = 1;
        //printf("srch real 0: %s\n", n);
		while(aux != NULL){
            //printf("srch real %d: %s\n", i++, aux->name);
			if(strcmp(n, aux->name)==0){
                //printf("return %s\n", aux->name);
				return aux;
			}
			aux = aux->prox;
		}
        //printf("srch end\n");
		return aux;
	}
    
    VARS *srchall(Listavar *l, char n[]){
		//printf("srch begin\n");
        //int i = 1;
        //printf("srch real %d: %s\n", i++, aux->name);
		VARS * aux;
        while(l != NULL){
            aux = l->rvar;
            while(aux != NULL){
                if(strcmp(n, aux->name)==0){
                    return aux;
                }
                aux = aux->prox;
            }
            l = l->prox;
        }
        //printf("srch end\n");
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

    //busca uma variável na lista de variáveis
	VARSI *srchi(VARSI *aux, char n[]){
        //printf("srchi begin\n");
		while(aux!=NULL){
            //printf("inteiro %s\n", aux->name);
			if(strcmp(n, aux->name)==0) 
                break;
			else
                aux = aux->prox;
		}
        //printf("srchi end\n");
		return aux;
	}

    VARSI *srchiall(Listavar *l, char n[]){
        //printf("srchi begin\n");
		VARSI * aux;
        while(l!=NULL){
            aux = l->ivar;
            while(aux!=NULL){
                //printf("inteiro %s\n", aux->name);
                if(strcmp(n, aux->name)==0) 
                    break;
                else
                    aux = aux->prox;
            }
            l = l->prox;
        }
        //printf("srchi end\n");
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
    VARST *srcht(VARST *aux, char n[]){
		//printf("srcht begin\n");
		while(aux!=NULL){
			if(strcmp(n, aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
        //printf("srcht end\n");
		return aux;
	}
    //add novo vetor na lista de vetores
	Vecr * insvecr(Vecr *l, int t, char n[], int tam){
		Vecr *aux =(Vecr*)malloc(sizeof(Vecr));
		if(!aux) {
            printf("out of space");
            exit(0);
        }
        aux->nodetype = t;
        strcpy(aux->name, n);
        aux->tam = tam;
        aux->v = (double*)malloc(tam*sizeof(double));
        /*
        if(t=='k')
            aux->v = (Ast*)malloc(tam*sizeof(int));
        else if(t=='K')
            aux->v = (Ast*)malloc(tam*sizeof(double));
        else if(t=='m')
            aux->v = (Ast*)malloc(tam*sizeof(char));
        //*/
        //aux->in = (Veci*)NULL;
		aux->prox = l;
		return aux;
	}

    //busca uma variável na lista de vetores
	Vecr *srchvecr(Vecr *l, char n[]){
		Vecr *aux = l;
		while(aux != NULL){
			if(strcmp(n, aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
	}
    //add novo vetor na lista de vetores
	Veci * insveci(Veci *l, int t, char n[], int tam){
		Veci *aux =(Veci*)malloc(sizeof(Veci));
		if(!aux) {
            printf("out of space");
            exit(0);
        }
        aux->nodetype = t;
        strcpy(aux->name, n);
        aux->tam = tam;
        aux->v = (int*)malloc(tam*sizeof(int));
        //aux->in = (Veci*)NULL;
		aux->prox = l;
		return aux;
	}

    //busca uma variável na lista de vetores
	Veci *srchveci(Veci *l, char n[]){
		Veci *aux = l;
		while(aux != NULL){
			if(strcmp(n, aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
	}
    //add novo vetor na lista de vetores
	Vect * insvect(Vect *l, int t, char n[], int tam){
		Vect *aux =(Vect*)malloc(sizeof(Vect));
		if(!aux) {
            printf("out of space");
            exit(0);
        }
        aux->nodetype = t;
        strcpy(aux->name, n);
        aux->tam = tam;
        aux->v = (char**)malloc(tam*sizeof(char*));
        //aux->in = (Veci*)NULL;
		aux->prox = l;
		return aux;
	}

    //busca uma variável na lista de vetores
	Vect *srchvect(Vect *l, char n[]){
		Vect *aux = l;
		while(aux != NULL){
			if(strcmp(n, aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
	}
    /*
    //busca uma variável na lista de vetores
	Veci *srchvecip(Veci *l, int n){
		Veci *aux = l;
		for(int x = 0; x < n; x++){
			//aux = aux->in;
            if (!aux)
                return aux;
		}
		return aux;
	}
    //*/
    //add nova variável na lista
    Function * insfunction(Function *l, Func *fun){
		Function *aux =(Function*)malloc(sizeof(Function));
		if(!aux) {
            printf("out of space in insfuntion()\n");
            exit(1);
        }
        aux->nodetype = fun->type;
        strcpy(aux->name, fun->name);
        aux->var = NULL;
        aux->args = fun->args;
        aux->v = fun->v;
		aux->prox = l;
		return aux;
	}
	
    //busca uma variável na lista de variáveis
    Function *srchfunction(Function *l, char n[]){
		Function *aux = l;
        //printf("open srchfuntion\n");
		while(aux != NULL){
			if(strcmp(n,aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
        //printf("function NULL\n");
		return aux;
	}

    Function *srchfunctionall(Listavar *auxl, char n[]){
        Function *auxf;
        while(auxl != NULL){
            auxf = auxl->function;
            //printf("open srchfuntion\n");
            while(auxf != NULL){
                if(auxf->name)
                    //printf("auxf->name = %s\n", auxf->name);
                if(strcmp(n, auxf->name)==0){
                    return auxf;
                }
                auxf = auxf->prox;
            }
            auxl = auxl->prox;
        }
        //printf("function NULL\n");
		return auxf;
	}

    Ast * newfunction(int type, char n[], Ast *a, Ast *fun){
        Func *aux = (Func*)malloc(sizeof(Func));
        if(!aux){
            printf("out of space in newfuntion()");
            exit(1);
        }
        aux->nodetype = 'B';
        aux->type = type;
        strcpy(aux->name, n);
        aux->args = a;
        aux->v = fun;
        return (Ast*)aux;
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

    /*O nodetype serve para indicar o tipo de nó que está na árvore. Isso serve para a função eval() entender o que realizar naquele nó*/
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
    Ast * newvar(int t, char s[], Ast *v, Ast *n){
        Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = t; /*tipo i, r ou t, conforme arquivo .l*/
        strcpy(a->s, s); /*Símbolo/variável*/
        a->v = v; /*Valor*/
        a->n = n; /*proxima declaração*/
        return (Ast *)a;
    }

    // função pra declarar variavel e atribuir
    Ast * newvec(int t, char s[], Ast *tam, Ast *v, Ast *n){
        Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 'V'; /*tipo i, r ou t, conforme arquivo .l*/
        a->type = t;
        strcpy(a->s, s); /*Símbolo/variável*/
        a->tam = tam; /*tamanho do vetor*/
        a->v = v; /*Valor*/
        a->n = n; /*proxima declaração*/
        return (Ast *)a;
    }

    Ast * newasgn(char s[], Ast *pos, Ast *v) { /*Função para um nó de atribuição*/
        Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = '=';
        strcpy(a->s, s); /*Símbolo/variável*/
        a->tam = pos;
        a->v = v; /*Valor*/
        return (Ast *)a;
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

    Ast * newValorVal(char s[], Ast *pos) { /*Função que recupera o nome/referência de uma variável, neste caso o número*/    
        Varval *a = (Varval*) malloc(sizeof(Varval));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 'N';
        strcpy(a->var, s);
        a->pos = pos;
        return (Ast*)a;
    }

    Listavar * lista = NULL;

    /* 
        verifica se uma variavel já existe na lista de variaveis 
        @param Listavar 
        @param char* 
        @return true or false 
    */
    bool varexiste(Listavar * l, char v[]) {
        
        VARS* xr = (VARS*)malloc(sizeof(VARS));
        VARSI* xi = (VARSI*)malloc(sizeof(VARSI));
        VARST* xt = (VARST*)malloc(sizeof(VARST));
        Vecr *vr = (Vecr*)malloc(sizeof(Vecr));
        Veci *vi = (Veci*)malloc(sizeof(Veci));
        Vect *vt = (Vect*)malloc(sizeof(Vect));

        while(l!=NULL){
            xr = srch(l->rvar, v);
            xi = srchi(l->ivar, v);
            xt = srcht(l->tvar, v);
            vr = srchvecr(l->rvec, v);
            vi = srchveci(l->ivec, v);
            vt = srchvect(l->tvec, v);

            if (xr) return true; // se TRUE, var ja existe
            if (xi) return true; // se TRUE, var ja existe
            if (xt) return true; // se TRUE, var ja existe
            if (vr) return true; // se TRUE, var ja existe
            if (vi) return true; // se TRUE, var ja existe
            if (vt) return true; // se TRUE, var ja existe
            break;
        }
        
        return false; // se FALSE, var ainda nao existe
    }
/*
    void printvec(Veci *a){
        int i = 0;
        while(a){
            printf("%s[%d] = %d\n", a->name, i, a->v);
            i++;
            a = a->in;
        }
    }
    void printvecp(Veci *a, int x){
        //printf("1 printvecp\n");
        int i = 0;
        char name[name_size];
        strcpy(name, a->name);
        //printf("2 printvecp\n");
        bool teste = true;
        while(teste){
            //printf("4 printvecp\n");
            if(a->in)
                a = a->in;
            else {
                //printf("5 printvecp\n");
                teste = false;
            }
        }
        //printf("3 printvecp\n");
        if(teste)
            printf("%s[%d] = %d\n", name, i, a->v);
        else
            printf("\nErro (printvecp()): posicao fora do vetor\n");
    }
//*/
    void * printValorVar(Listavar *auxl, char var[], int pos){
        //printf("VAR %s\n", var);
        VARS * auxr;
        VARSI * auxi;
        VARST * auxt;
        Vecr * auxvr;
        Veci * auxvi;
        Vect * auxvt;
        if(auxl==NULL)
            printf ("\nErro (printValorVar()) - lista de variaveis nula. Variavel nao declarada.\n", var);
        while(auxl!=NULL){
            auxr = srch(auxl->rvar, var);
            if (auxr){
                printf("%.2f", auxr->v);
                break;
            } else {
                auxi = srchi(auxl->ivar, var);
                if (auxi){
                    printf("%d", auxi->v);
                    break;
                } else {
                    auxt = srcht(auxl->tvar, var);
                    if (auxt){
                        printf("%s", auxt->v);
                        break;
                    }
                    else{
                        auxvr = srchvecr(auxl->rvec, var);
                        if (auxvr){
                            if(pos<auxvr->tam){
                            printf("%.2f", auxvr->v[pos]);
                            } else {
                                printf("\nErro (printValorVar()) - posicao fora do tamanho do vetor.\n", var);
                            }
                            break;
                        }
                        else{
                            auxvi = srchveci(auxl->ivec, var);
                            if (auxvi){
                                if(pos<auxvi->tam){
                                printf("%d", auxvi->v[pos]);
                                } else {
                                    printf("\nErro (printValorVar()) - posicao fora do tamanho do vetor.\n", var);
                                }
                                break;
                            }
                            else{
                                auxvt = srchvect(auxl->tvec, var);
                                if (auxvt){
                                    if(pos<auxvt->tam){
                                    printf("%s", auxvt->v[pos]);
                                    } else {
                                        printf("\nErro (printValorVar()) - posicao fora do tamanho do vetor.\n", var);
                                    }
                                    break;
                                }
                                else if(auxl->prox==NULL)
                                        printf ("\nErro (printValorVar()) - Variavel '%s' nao foi declarada.\n", var);
                            }
                        }
                    }
                }
            }
            auxl = auxl->prox;
        }
    }

    double eval(Ast *a);

    char *evalt(Ast *a){
        char *t = NULL;
        if(!a) {
            printf("\ninternal error, null evalt\n");
            return NULL;
        }
        VARS * auxr = (VARS*)malloc(sizeof(VARS));
        if(!auxr) {
            printf("out of space (eval 'auxr')");
            exit(1);
        }
        VARSI * auxi = (VARSI*)malloc(sizeof(VARSI));
        if(!auxi) {
            printf("out of space (eval 'auxi')");
            exit(1);
        }
        VARST * auxt = (VARST*)malloc(sizeof(VARST));
        if(!auxt) {
            printf("out of space (eval 'auxt')");
            exit(1);
        }
        Vecr * auxvr = (Vecr*)malloc(sizeof(Vecr));
        if(!auxvr) {
            printf("out of space (eval 'auxvr')");
            exit(1);
        }
        Veci * auxvi = (Veci*)malloc(sizeof(Veci));
        if(!auxvi) {
            printf("out of space (eval 'auxvi')");
            exit(1);
        }
        Vect * auxvt = (Vect*)malloc(sizeof(Vect));
        if(!auxvt) {
            printf("out of space (eval 'auxvt')");
            exit(1);
        }
        Function * auxf = (Function*)malloc(sizeof(Function));
        if(!auxf) {
            printf("out of space (eval 'auxf')");
            exit(1);
        }
        Listavar * auxl = (Listavar*)malloc(sizeof(Listavar));
        if(!auxl) {
            printf("out of space (eval 'auxl')");
            exit(1);
        }
        //printf("case evalt() 1\n");
        switch(a->nodetype) {
            case 'k':; 
                t = (char*)malloc(sizeof(((Intval *)a)->v)*sizeof(char));
                sprintf(t, "%d", ((Intval *)a)->v); 
                break; 	
            case 'K':; 
                t = (char*)malloc(sizeof(((Realval *)a)->v)*sizeof(char));
                sprintf(t, "%f", ((Realval *)a)->v);
                break; 
            case 'm':; 
                t = (char*)malloc(sizeof(((Textoval *)a)->v)*sizeof(char));
                sprintf(t, "%s", ((Textoval *)a)->v);
                break; 
            case 'N':;
                auxl = lista;
                if(auxl==NULL){
                    printf ("\nErro (case 'N') - Lista Null. Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                    break;
                }
                while(auxl!=NULL){
                    int z = eval(((Varval*)a)->pos);
                    auxr = srch(auxl->rvar, ((Varval*)a)->var);
                    if (!auxr){
                        auxi = srchi(auxl->ivar, ((Varval*)a)->var);
                        if (!auxi){
                            auxt = srcht(auxl->tvar, ((Varval*)a)->var);
                            if (!auxt){
                                auxvr = srchvecr(auxl->rvec, ((Varval*)a)->var);
                                if(!auxvr){
                                    auxvi = srchveci(auxl->ivec, ((Varval*)a)->var);
                                    if(!auxvi){
                                        auxvt = srchvect(auxl->tvec, ((Varval*)a)->var);
                                        if(!auxvt){
                                            if(auxl->prox==NULL){
                                                printf ("Erro (case 'N') - Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                                                break;
                                            }
                                        } else {
                                            if (z<auxvt->tam){
                                                //printf("opa\n");
                                                t = auxvt->v[z];
                                            } else {
                                                printf("Erro (case 'N') - posicao fora do tamanho do vetor. Return 0.\n");
                                            }
                                            break;
                                        }
                                    } else {
                                        if (z<auxvi->tam){
                                            t = (char*)malloc(auxvi->v[z]*sizeof(char));
                                            sprintf(t, "%d", auxvi->v[z]);
                                        } else {
                                            printf("Erro (case 'N') - posicao fora do tamanho do vetor. Return 0.\n");
                                        }
                                        break;
                                    }
                                } else {
                                    if (z<auxvr->tam){
                                        t = (char*)malloc(auxvr->v[z]*sizeof(char));
                                        sprintf(t, "%f", auxvr->v[z]);
                                    } else {
                                        printf("Erro (case 'N') - posicao fora do tamanho do vetor. Return 0.\n");
                                    }
                                    break;
                                }
                            } else {
                                t = (char*)malloc(sizeof(char));
                                strcpy(t, auxt->v);
                                break;
                            }
                        } else {
                            t = (char*)malloc(auxi->v*sizeof(char));
                            sprintf(t, "%d", auxi->v);
                            break;
                        }
                    }
                    else{
                        //printf("hm\n");
                        t = (char*)malloc(auxr->v*sizeof(char));
                        sprintf(t, "%f", auxr->v);
                        break;
                    }
                    auxl = auxl->prox;
                }
                break;

            default: printf("\ninternal error: bad node %c\n in evalt\n", a->nodetype); break;
        }
            
        return t;
    }

    double eval(Ast *a) { /*Função que executa operações a partir de um nó*/
        double v = 0;
        if(!a) {
            printf("\ninternal error, null eval\n");
            return 0.0;
        }
        VARS * auxr = (VARS*)malloc(sizeof(VARS));
        if(!auxr) {
            printf("out of space (eval 'auxr')");
            exit(1);
        }
        VARSI * auxi = (VARSI*)malloc(sizeof(VARSI));
        if(!auxi) {
            printf("out of space (eval 'auxi')");
            exit(1);
        }
        VARST * auxt = (VARST*)malloc(sizeof(VARST));
        if(!auxt) {
            printf("out of space (eval 'auxt')");
            exit(1);
        }
        Vecr * auxvr = (Vecr*)malloc(sizeof(Vecr));
        if(!auxvr) {
            printf("out of space (eval 'auxvr')");
            exit(1);
        }
        Veci * auxvi = (Veci*)malloc(sizeof(Veci));
        if(!auxvi) {
            printf("out of space (eval 'auxvi')");
            exit(1);
        }
        Vect * auxvt = (Vect*)malloc(sizeof(Vect));
        if(!auxvt) {
            printf("out of space (eval 'auxvt')");
            exit(1);
        }
        Function * auxf = (Function*)malloc(sizeof(Function));
        if(!auxf) {
            printf("out of space (eval 'auxf')");
            exit(1);
        }
        Listavar * auxl = (Listavar*)malloc(sizeof(Listavar));
        if(!auxl) {
            printf("out of space (eval 'auxl')");
            exit(1);
        }

        //printf("\na->type: %c\n", a->nodetype);
        switch(a->nodetype) {
            case 'k': v = ((Intval *)a)->v; break; 	/*Recupera um número inteiro*/
            case 'K': v = ((Realval *)a)->v; break; 	/*Recupera um número real*/
            case 'm': v = atof(((Textoval *)a)->v); break; 	/*Recupera um número real dentro de string*/
            case 'N':;
                //printf("case N begin\n");
                auxl = lista;
                if(auxl==NULL){
                    printf ("\nErro (case 'N') - Lista Null. Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                    v = 0.0;
                    break;
                }
                //int i = 1;
//                printf("case N begin while\n");
                while(auxl!=NULL){
                    //printf("case 'N' %d\n", i++);
                    int p = eval(((Varval*)a)->pos);
                    auxr = srch(auxl->rvar, ((Varval*)a)->var);
                    if (!auxr){
                        auxi = srchi(auxl->ivar, ((Varval*)a)->var);
                        if (!auxi){
                            auxt = srcht(auxl->tvar, ((Varval*)a)->var);
                            if (!auxt){
                                auxvr = srchvecr(auxl->rvec, ((Varval*)a)->var);
                                if(!auxvr){
                                    auxvi = srchveci(auxl->ivec, ((Varval*)a)->var);
                                    if(!auxvi){
                                        auxvt = srchvect(auxl->tvec, ((Varval*)a)->var);
                                        if(!auxvt){
                                            if(auxl->prox==NULL){
                                                printf ("Erro (case 'N') - Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                                                v = 0.0;
                                                break;
                                            }
                                        } else {
                                            if (p<auxvt->tam)
                                                v = atof(auxvt->v[p]);
                                            else {
                                                v = 0;
                                                printf("Erro (case 'N') - posicao fora do tamanho do vetor. Return 0.\n");
                                            }
                                            break;
                                        }
                                    } else {
                                        if (p<auxvi->tam)
                                            v = auxvi->v[p];
                                        else {
                                            v = 0;
                                            printf("Erro (case 'N') - posicao fora do tamanho do vetor. Return 0.\n");
                                        }
                                        break;
                                    }
                                } else {
                                    if (p<auxvr->tam)
                                        v = auxvr->v[p];
                                    else {
                                        v = 0;
                                        printf("Erro (case 'N') - posicao fora do tamanho do vetor. Return 0.\n");
                                    }
                                    break;
                                }
                            } else {
                                v = atof(auxt->v);
                                break;
                            }
                        } else {
                            v = (double)auxi->v;
                            break;
                        }
                    }
                    else{
                        v = auxr->v;
                        break;
                    }
                    auxl = auxl->prox;
                }
                //printf("case N end\n");
                break;

            case '^': v = pow(eval(a->l), eval(a->r)); break;	/*Operações "árv esq   +   árv dir"*/
            case '+': v = eval(a->l) + eval(a->r); break;	/*Operações "árv esq   +   árv dir"*/
            case '-': v = eval(a->l) - eval(a->r); break;	/*Operações "árv esq   -   árv dir"*/
            case '*': v = eval(a->l) * eval(a->r); break;	/*Operações "árv esq   *   árv dir"*/
            case '/': v = eval(a->l) / eval(a->r); break; /*Operações "árv esq   /   árv dir"*/
            case '%':; 
                double v1 = eval(a->l);
                double v2 = eval(a->r);
                v = v1/v2;
                int aa = (int)v;
                v = (v - aa)*v2;
                break; /*Operações "árv esq   %   árv dir"*/
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
            case '?': 
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
            
            case '=':;
                //printf("case '=' begin\n");
                v = eval(((Symasgn *)a)->v); /*Recupera o valor*/
                auxl = lista;
                if(auxl == NULL){
                    printf("\nErro de var nao declarada\n");
                    v = 0.0;
                    break;
                }
                //printf("case = begin while\n");
                while(auxl!=NULL){
                    int x = eval(((Symasgn *)a)->tam);
                    auxr = srch(auxl->rvar, ((Symasgn *)a)->s);
                    if(!auxr){
                        auxi = srchi(auxl->ivar, ((Symasgn *)a)->s);
                        if(!auxi){
                            auxt = srcht(auxl->tvar, ((Symasgn *)a)->s);
                            if(!auxt){
                                auxvr = srchvecr(auxl->rvec, ((Symasgn *)a)->s);
                                if(!auxvr){
                                    auxvi = srchveci(auxl->ivec, ((Symasgn *)a)->s);
                                    if(!auxvi){
                                        auxvt = srchvect(auxl->tvec, ((Symasgn *)a)->s);
                                        if(!auxvt){
                                            if(auxl->prox == NULL){
                                                printf("\nErro de var nao declarada\n");
                                                v = 0.0;
                                                break;
                                            }
                                        } else {
                                            auxvt->v[x] = evalt(((Symasgn *)a)->v);
                                        }
                                    } else {
                                        auxvi->v[x] = v;
                                    }
                                } else {
                                    auxvr->v[x] = v;
                                }
                            } else {
                                strcpy(auxt->v, evalt(((Symasgn *)a)->v)); /*Atribui à variável*/
                                break;
                            }
                        } else {
                            auxi->v = (int)v; /*Atribui à variável*/
                            break;
                        }
                    } else {
                        auxr->v = v;   /*Atribui à variável*/
                        break;
                    }
                    auxl = auxl->prox;
                }
                //printf("case '=' end\n");
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
                    
                    auxl = lista;
                    while(auxl!=NULL){
                        auxr = srch(auxl->rvar, name);
                        if(auxr){
                            for(auxr->v; 
                                eval(((Flowfor*)((Flow *)a)->cond)->v2); 
                                auxr->v += eval(((Flowfor*)((Flow *)a)->cond)->v3)
                                ){
                                    v =  eval(((Flow *)a)->tl);
                            }
                        } else {
                            auxi = srchi(auxl->ivar, name);
                            if(auxi){
                                for(auxi->v; 
                                    eval(((Flowfor*)((Flow *)a)->cond)->v2); 
                                    auxi->v += eval(((Flowfor*)((Flow *)a)->cond)->v3)
                                    ){
                                        v =  eval(((Flow *)a)->tl);
                                }
                            } else {
                                if(auxl->prox == NULL)
                                    printf("\nErro no FOR: variavel nao numerica\n");
                                else
                                    auxl = auxl->prox;
                            }
                        }
                    }
                }
            break;
            // multiplas linhas de códigos em IF/ELSE/WHILE/FOR
            case 'L': eval(a->l); v = eval(a->r); break; /*Lista de operções em um bloco IF/ELSE/WHILE. Assim o analisador não se perde entre os blocos*/
            case 'l': if(a->l) v = eval(a->l); if(a->r) eval(a->r); break;
            case 'j': v = eval(a->l); return v; break;
            // print na tela
            case 'P':;
                //printf("P1\n");
                if(!a->l) {
                    if(!a->r)
                        printf("\n");
                    break;
                }
                //printf("P - %c\n", a->l->nodetype);
                if(a->l->nodetype == 'N') {
                    //a->l->nodetype = 'n';
                    //if(!lista)
                        //printf("lista null\n");
                    int w = eval(((Varval*)a->l)->pos);
                    printValorVar(lista, ((Varval*)a->l)->var, w);
                    //printf("nodetype 'NN'\n");
                }
                else if(((Intval*)a->l)->nodetype == 'k')
                    printf ("%d", ((Intval*)a->l)->v);		/*Recupera um valor inteiro*/
                else if(((Realval*)a->l)->nodetype == 'K')
                    printf ("%.2f", ((Realval*)a->l)->v);		/*Recupera um valor real*/
                else if(((Textoval*)a->l)->nodetype == 'm') {
                    if(strcmp(((Textoval*)a->l)->v, "\\n")==0)
                        printf("\n");
                    else
                        printf ("%s", ((Textoval*)a->l)->v);		/*Recupera um valor texto*/
                } else {
                    //printf("not 'NN'\n");
                    v = eval(a->l);
                    printf("%.2f", v);
                }
                    //printf("P5\n");
                    if(!a->r)
                        printf("\n");
                    else{
                        eval(a->r);
                    }
                    //printf("P7\n");
                    break;  /*Função que imprime um valor*/
            
            case 'V':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(lista, ((Symasgn *)a)->s)){
                    Ast *auxv = ((Symasgn *)a)->v;
                    int posv = 0;
                    int y = eval(((Symasgn *)a)->tam);
                    
                    switch(((Symasgn *)a)->type){
                        case 'r':;
                            lista->rvec = insvecr(lista->rvec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                            for(posv = 0; posv < lista->rvec->tam && auxv!=NULL; posv++, auxv = auxv->r){
                                lista->rvec->v[posv] = eval(auxv->l); /*Atribui à variável*/
                            }
                            break;
                        case 'i':;
                            lista->ivec = insveci(lista->ivec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                            for(posv = 0; posv < lista->ivec->tam && auxv!=NULL; posv++, auxv = auxv->r){
                                lista->ivec->v[posv] = eval(auxv->l); /*Atribui à variável*/
                            }
                            break;
                        case 't':;
                            lista->tvec = insvect(lista->tvec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                            
                            for(posv = 0; posv < lista->tvec->tam ; posv++){
                                if(auxv){
                                    lista->tvec->v[posv] = evalt(auxv->l); /*Atribui à variável*/
                                    auxv = auxv->r;
                                }else{
                                    lista->tvec->v[posv] = evalt(newtexto(""));
                                }
                            }
                            break;
                        default:;
                            printf("\nErro (case 'V'): sem case\n");
                            break;
                    }
                }else
                    printf("\nErro (case 'i'): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);                
                break;

            // declarar variavel inteiro
            case 'i':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(lista, ((Symasgn *)a)->s)){
                    if(((Symasgn *)a)->v)
                        v = (int)eval(((Symasgn *)a)->v); /*Atribui à variável*/
                    lista->ivar = insi(lista->ivar, ((Symasgn *)a)->s);
                    lista->ivar->v = v;
                }else
                    printf("\nErro (case 'i'): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
                break;
            // declarar variavel real
            case 'r':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(lista, ((Symasgn *)a)->s)){
                    if(((Symasgn *)a)->v)
                        v = eval(((Symasgn *)a)->v);
                    lista->rvar = ins(lista->rvar, ((Symasgn *)a)->s);
                    lista->rvar->v = v;
                }else
                    printf("\nErro 3 (case 'r'): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
                break;
            // declarar variavel texto
            case 't':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(lista, ((Symasgn *)a)->s)){
                    char auxtt[string_size];
                    if((((Symasgn *)a)->v))
                        strcpy(auxtt, evalt(((Symasgn*)a)->v));
                    lista->tvar = inst(lista->tvar, ((Symasgn *)a)->s);
                    strcpy(lista->tvar->v, auxtt);
                }else
                    printf("\nErro (case 't'): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
                break;
            
            // leitura das variaveis: int, real e texto
            case 'c':; 
                //v = eval(((Symasgn *)a)->v); /*Recupera o valor*/
                auxl = lista;
                while(auxl != NULL){
                    int r = eval(((Varval *)a->l)->pos);
                    auxr = srch(auxl->rvar, ((Varval *)a->l)->var);
                    if(auxr){
                        scanf("%Lf", &auxr->v);
                        break;
                    } else {
                        auxi = srchi(auxl->ivar, ((Varval *)a->l)->var);
                        if(auxi){
                            scanf("%d", &auxi->v);
                            break;
                        } else {
                            auxt = srcht(auxl->tvar, ((Varval *)a->l)->var);
                            if(auxt){
                                scanf("%s", &auxt->v);
                                break;
                            } else {
                                auxvr = srchvecr(auxl->rvec, ((Varval *)a->l)->var);
                                if(auxvr){
                                    scanf("%Lf", &auxvr->v[r]);
                                    break;
                                } else {
                                    auxvi = srchveci(auxl->ivec, ((Varval *)a->l)->var);
                                    if(auxvi){
                                        scanf("%d", &auxvi->v[r]);
                                        break;
                                    } else {
                                        auxvt = srchvect(auxl->tvec, ((Varval *)a->l)->var);
                                        if(auxvt){
                                            scanf("%s", &auxvt->v[r]);
                                            break;
                                        } else {
                                            if(auxl->prox == NULL)
                                                printf("\nErro(<<): Variavel invalida!\n");
                                            auxl = auxl->prox;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case 'T':;
                // função TYPE(var)
                auxl = lista;
                while(auxl != NULL){
                    auxr = srch(auxl->rvar, ((Textoval *)a->l)->v);
                    if(auxr){
                        printf("Type(%s): real\n", ((Textoval *)a->l)->v);
                        break;
                    } else {
                        auxi = srchi(auxl->ivar, ((Textoval *)a->l)->v);
                        if(auxi){
                            printf("Type(%s): inteiro\n", ((Textoval *)a->l)->v);
                            break;
                        } else {
                            auxt = srcht(auxl->tvar, ((Textoval *)a->l)->v);
                            if(auxt){
                                printf("Type(%s): texto\n", ((Textoval *)a->l)->v);
                                break;
                            } else {
                                if(auxl->prox == NULL) {
                                    printf("\nErro(type): Variavel invalida!\n");
                                    break;
                                } else
                                    auxl = auxl->prox;
                            }
                        }
                    }
                }
                break;
            
            case 'B':; /* adiciona uma nova função na lista de funções */
                //printf("func %s\n", ((Func*)a)->name);
                
                if(srchfunction(lista->function, ((Func*)a)->name)==NULL){
                    lista->function = insfunction(lista->function, ((Func*)a));
                } else
                    printf("\nErro (case 'B'): reescrita de funcao nao permitida\n");
                //printf("tion %s\n", ((Func*)a)->name);
                break;
            
            case 'a':; /* executa uma função quando for chamada */
                auxl = lista;
                while(auxl != NULL){
                    auxf = srchfunctionall(auxl, ((Textoval*)a->l)->v);
                    //printf("auxf->name = %s\n", auxf->name);
                    if(auxf==NULL){
                        if(auxl->prox == NULL)
                            printf("\nErro (case 'a'): funcao nao declarada\n");
                        else
                            auxl = auxl->prox;
                        //printf("case 'a'\n");
                    } else {
                        //printf("function yes\n");
                        Listavar * auxz = (Listavar*)malloc(sizeof(Listavar));
                        strcpy(auxz->name, auxf->name);
                        auxz->ivar = NULL;
                        auxz->rvar = NULL;
                        auxz->tvar = NULL;
                        auxz->rvec = NULL;
                        auxz->ivec = NULL;
                        auxz->tvec = NULL;
                        auxz->function = NULL;
                        auxz->prox = lista;
                        lista = auxz;
                        //printf("hum 22\n");

                        // verifica e executa as declarações e atribuições de ARGUMENTOS da função
                        if(auxf->args!=NULL && a->r!=NULL) {
                            Ast *b = auxf->args;
                            Ast *c = a->r;
                            while(c){
                                eval(newvar(b->l->nodetype, ((Symasgn*)b->l)->s, c->l, NULL));
                                if (b->r!=NULL && c->r!=NULL){
                                    b = b->r;
                                    c = c->r;
                                } else if(b->r==NULL && c->r==NULL){
                                    // fim de argumentos
                                    break;
                                } else {
                                    printf("\nErro (case 'a'): arg insuficientes ou excedente\n");
                                }
                            }
                            //printf("end c\n");
                        } else if(auxf->args==NULL && a->r==NULL) {
                            // função sem argumentos ok
                        } else {
                            printf("\nErro (case 'a'): chamada de funcao errada\n");
                            break;
                        }
                        // fim do bloco de ARGUMENTOS da função
                        //*/
                        // chama bloco de codigos dentro da função
                        //printf("hum 99\n");
                        if(auxf->v)
                            v = eval(auxf->v);
                        
                        // fim do bloco de codigos dentro da função
                        //printf("hum 7799\n");
                        auxl = lista;
                        lista = lista->prox;
                        free(auxl);
                        auxl = NULL;
                        break;
                    }
                } // end while
                break;

            case 'y':;
                lista = NULL;
                Listavar * g = (Listavar*)malloc(sizeof(Listavar));
                if(!g)
                    exit(1);
                strcpy(g->name, "main");
                g->rvar = NULL; 
                g->ivar = NULL;
                g->tvar = NULL;
                g->rvec = NULL;
                g->ivec = NULL;
                g->tvec = NULL;
                g->function = NULL;
                g->prox = NULL;
                lista = g;
                break; 

            case 'z':;
                printf("\n-> Fim do programa! <-\n\n");
                free(lista);
                lista = NULL;
                exit(0);
                break;

            case '\n':; break;

            default: printf("internal error: bad node %c\n", a->nodetype);
        }
        return v;
    }


#line 1564 "calc_elidian.tab.c"

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
    TIPO_TEXTO = 259,              /* TIPO_TEXTO  */
    INTEIRO = 260,                 /* INTEIRO  */
    REAL = 261,                    /* REAL  */
    TEXTO = 262,                   /* TEXTO  */
    TYPE = 263,                    /* TYPE  */
    RETURN = 264,                  /* RETURN  */
    ENTRADA = 265,                 /* ENTRADA  */
    SAIDA = 266,                   /* SAIDA  */
    INICIO = 267,                  /* INICIO  */
    FINAL = 268,                   /* FINAL  */
    NEWLINHA = 269,                /* NEWLINHA  */
    IF = 270,                      /* IF  */
    ELSE = 271,                    /* ELSE  */
    FOR = 272,                     /* FOR  */
    WHILE = 273,                   /* WHILE  */
    VAR = 274,                     /* VAR  */
    PASS = 275,                    /* PASS  */
    RAIZ = 276,                    /* RAIZ  */
    COS = 277,                     /* COS  */
    SIN = 278,                     /* SIN  */
    PLUS = 279,                    /* PLUS  */
    LESS = 280,                    /* LESS  */
    OR = 281,                      /* OR  */
    AND = 282,                     /* AND  */
    MAIOR = 283,                   /* MAIOR  */
    MENOR = 284,                   /* MENOR  */
    MEI = 285,                     /* MEI  */
    MAI = 286,                     /* MAI  */
    II = 287,                      /* II  */
    DIF = 288,                     /* DIF  */
    PLUS2 = 289,                   /* PLUS2  */
    LESS2 = 290,                   /* LESS2  */
    FUN = 291,                     /* FUN  */
    ITERATOR = 292,                /* ITERATOR  */
    NEG = 293,                     /* NEG  */
    VARP = 294                     /* VARP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 1494 "calc_elidian.y"

    char texto[50];
    char stexto[1000];
    int inteiro;
    double real;
    Ast *a;

#line 1658 "calc_elidian.tab.c"

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
  YYSYMBOL_TIPO_TEXTO = 4,                 /* TIPO_TEXTO  */
  YYSYMBOL_INTEIRO = 5,                    /* INTEIRO  */
  YYSYMBOL_REAL = 6,                       /* REAL  */
  YYSYMBOL_TEXTO = 7,                      /* TEXTO  */
  YYSYMBOL_TYPE = 8,                       /* TYPE  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_ENTRADA = 10,                   /* ENTRADA  */
  YYSYMBOL_SAIDA = 11,                     /* SAIDA  */
  YYSYMBOL_INICIO = 12,                    /* INICIO  */
  YYSYMBOL_FINAL = 13,                     /* FINAL  */
  YYSYMBOL_NEWLINHA = 14,                  /* NEWLINHA  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_FOR = 17,                       /* FOR  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_VAR = 19,                       /* VAR  */
  YYSYMBOL_PASS = 20,                      /* PASS  */
  YYSYMBOL_RAIZ = 21,                      /* RAIZ  */
  YYSYMBOL_COS = 22,                       /* COS  */
  YYSYMBOL_SIN = 23,                       /* SIN  */
  YYSYMBOL_PLUS = 24,                      /* PLUS  */
  YYSYMBOL_LESS = 25,                      /* LESS  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_MAIOR = 29,                     /* MAIOR  */
  YYSYMBOL_MENOR = 30,                     /* MENOR  */
  YYSYMBOL_MEI = 31,                       /* MEI  */
  YYSYMBOL_MAI = 32,                       /* MAI  */
  YYSYMBOL_II = 33,                        /* II  */
  YYSYMBOL_DIF = 34,                       /* DIF  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_40_ = 40,                       /* '^'  */
  YYSYMBOL_PLUS2 = 41,                     /* PLUS2  */
  YYSYMBOL_LESS2 = 42,                     /* LESS2  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* '('  */
  YYSYMBOL_FUN = 45,                       /* FUN  */
  YYSYMBOL_ITERATOR = 46,                  /* ITERATOR  */
  YYSYMBOL_NEG = 47,                       /* NEG  */
  YYSYMBOL_VARP = 48,                      /* VARP  */
  YYSYMBOL_49_ = 49,                       /* '['  */
  YYSYMBOL_50_ = 50,                       /* ']'  */
  YYSYMBOL_51_ = 51,                       /* '{'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_53_ = 53,                       /* ';'  */
  YYSYMBOL_54_ = 54,                       /* ','  */
  YYSYMBOL_55_ = 55,                       /* '?'  */
  YYSYMBOL_56_ = 56,                       /* ':'  */
  YYSYMBOL_57_ = 57,                       /* '|'  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_prog = 59,                      /* prog  */
  YYSYMBOL_inicio = 60,                    /* inicio  */
  YYSYMBOL_cod = 61,                       /* cod  */
  YYSYMBOL_nl = 62,                        /* nl  */
  YYSYMBOL_exp = 63,                       /* exp  */
  YYSYMBOL_else = 64,                      /* else  */
  YYSYMBOL_atrib = 65,                     /* atrib  */
  YYSYMBOL_decl = 66,                      /* decl  */
  YYSYMBOL_declfunction = 67,              /* declfunction  */
  YYSYMBOL_declvar = 68,                   /* declvar  */
  YYSYMBOL_declvartexto = 69,              /* declvartexto  */
  YYSYMBOL_declvectexto = 70,              /* declvectexto  */
  YYSYMBOL_valorvectexto = 71,             /* valorvectexto  */
  YYSYMBOL_valorvec = 72,                  /* valorvec  */
  YYSYMBOL_declvecmult = 73,               /* declvecmult  */
  YYSYMBOL_outfunc = 74,                   /* outfunc  */
  YYSYMBOL_iterator = 75,                  /* iterator  */
  YYSYMBOL_args = 76,                      /* args  */
  YYSYMBOL_arg = 77,                       /* arg  */
  YYSYMBOL_saida = 78,                     /* saida  */
  YYSYMBOL_incdec = 79,                    /* incdec  */
  YYSYMBOL_list = 80,                      /* list  */
  YYSYMBOL_logica = 81,                    /* logica  */
  YYSYMBOL_arit = 82,                      /* arit  */
  YYSYMBOL_valor = 83,                     /* valor  */
  YYSYMBOL_varvar = 84,                    /* varvar  */
  YYSYMBOL_varfun = 85                     /* varfun  */
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
typedef yytype_int16 yy_state_t;

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
#define YYLAST   494

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  257

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
       2,     2,     2,     2,     2,     2,     2,    39,     2,     2,
      44,    43,    37,    35,    54,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    53,
       2,    26,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,    57,    52,     2,     2,     2,     2,
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
      25,    27,    28,    29,    30,    31,    32,    33,    34,    41,
      42,    45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,  1546,  1546,  1547,  1549,  1551,  1552,  1554,  1555,  1557,
    1558,  1559,  1560,  1561,  1562,  1563,  1564,  1565,  1566,  1567,
    1568,  1569,  1570,  1571,  1572,  1573,  1574,  1576,  1577,  1579,
    1580,  1582,  1583,  1584,  1585,  1586,  1589,  1590,  1592,  1593,
    1594,  1595,  1597,  1598,  1599,  1600,  1602,  1603,  1604,  1605,
    1607,  1608,  1609,  1610,  1612,  1613,  1615,  1616,  1617,  1618,
    1620,  1621,  1623,  1625,  1626,  1628,  1629,  1631,  1632,  1633,
    1634,  1635,  1636,  1638,  1639,  1643,  1644,  1646,  1647,  1648,
    1649,  1650,  1651,  1652,  1653,  1654,  1656,  1657,  1658,  1659,
    1660,  1661,  1662,  1663,  1664,  1665,  1666,  1667,  1668,  1671,
    1672,  1673,  1677,  1679,  1680,  1685,  1686
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
  "\"end of file\"", "error", "\"invalid token\"", "TIPO", "TIPO_TEXTO",
  "INTEIRO", "REAL", "TEXTO", "TYPE", "RETURN", "ENTRADA", "SAIDA",
  "INICIO", "FINAL", "NEWLINHA", "IF", "ELSE", "FOR", "WHILE", "VAR",
  "PASS", "RAIZ", "COS", "SIN", "PLUS", "LESS", "'='", "OR", "AND",
  "MAIOR", "MENOR", "MEI", "MAI", "II", "DIF", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'^'", "PLUS2", "LESS2", "')'", "'('", "FUN", "ITERATOR", "NEG",
  "VARP", "'['", "']'", "'{'", "'}'", "';'", "','", "'?'", "':'", "'|'",
  "$accept", "prog", "inicio", "cod", "nl", "exp", "else", "atrib", "decl",
  "declfunction", "declvar", "declvartexto", "declvectexto",
  "valorvectexto", "valorvec", "declvecmult", "outfunc", "iterator",
  "args", "arg", "saida", "incdec", "list", "logica", "arit", "valor",
  "varvar", "varfun", YY_NULLPTR
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
     275,   276,   277,   278,   279,   280,    61,   281,   282,   283,
     284,   285,   286,   287,   288,    43,    45,    42,    47,    37,
      94,   289,   290,    41,    40,   291,   292,   293,   294,    91,
      93,   123,   125,    59,    44,    63,    58,   124
};
#endif

#define YYPACT_NINF (-211)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -8,  -211,    11,     0,  -211,     0,    22,  -211,    24,    26,
      10,   255,   101,  -211,   255,     4,   255,   149,  -211,   255,
      44,  -211,  -211,  -211,    13,    21,    28,    29,  -211,  -211,
    -211,    35,   -13,    43,  -211,  -211,    16,    32,    36,    41,
     255,   255,   255,   447,   448,  -211,    33,   -15,  -211,  -211,
      48,    99,   338,    85,    83,    65,   338,  -211,  -211,  -211,
     144,    58,   255,   346,     0,    98,   100,   102,   106,   115,
     255,     3,   255,   128,   255,    93,    86,   255,  -211,   255,
     255,   255,  -211,   363,   245,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   222,
     222,   222,    88,   114,   255,   255,    92,  -211,   447,  -211,
     104,   107,   364,   105,   300,  -211,   130,   142,   120,   121,
     447,   153,     0,   138,   372,  -211,   380,  -211,  -211,   140,
     388,   412,   421,   430,  -211,  -211,   460,   460,  -211,  -211,
    -211,  -211,  -211,  -211,   139,   139,   146,   146,   146,   146,
    -211,  -211,  -211,     0,   255,   447,   330,     0,  -211,    86,
       2,   300,  -211,   255,   175,   255,   255,   133,   143,     0,
     158,   163,  -211,  -211,  -211,  -211,  -211,   300,   447,   255,
     300,  -211,  -211,   231,   141,   447,  -211,   396,   404,   192,
       0,   148,   151,   155,  -211,   190,   303,   190,  -211,   447,
     300,   181,   182,  -211,   300,     0,   255,   250,     0,   157,
       0,   159,  -211,   161,   162,   190,   300,   164,   294,   165,
     168,   302,   300,   201,   300,  -211,   250,   255,   169,   190,
    -211,   255,   250,  -211,   250,  -211,     0,  -211,   190,   170,
     171,  -211,   173,  -211,  -211,  -211,   179,   174,  -211,  -211,
    -211,     0,  -211,   300,   190,   180,  -211
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     7,     1,     7,     0,     8,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,    26,     0,
       7,     6,     9,    34,    31,    32,    33,    35,    24,    19,
      23,    41,    45,     0,    99,   100,   103,     0,     0,     0,
       0,     0,     0,    25,    85,    98,    69,   103,    21,    20,
      71,    67,     7,     0,     0,     0,     7,    14,    73,    74,
       0,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,     0,   101,     0,
       0,     0,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,    10,    61,
       0,    65,     0,     0,     8,     2,    38,    42,     0,     0,
      40,     0,     7,     0,     0,    44,     0,    22,   106,     0,
       0,     0,     0,     0,    97,    90,    77,    78,    79,    80,
      84,    83,    82,    81,    91,    92,    93,    94,    95,    96,
      70,    72,    68,     7,     0,    29,     0,     7,    60,     0,
       0,     0,     5,     0,     0,     0,     0,    63,     0,     7,
      57,    49,   104,   102,    88,    87,    86,     0,    30,     0,
       0,    66,    15,     0,     0,    39,    43,     0,     0,     0,
       7,     0,     0,     0,    75,     7,     0,     7,    13,    11,
       0,    46,    58,    64,     0,     7,     0,     0,     7,     0,
       7,     0,    62,     0,     0,     7,     0,     0,    55,    51,
       0,    53,     8,    27,     0,    17,     0,     0,     0,     7,
      56,     0,     0,    48,     0,    76,     7,    16,     7,     0,
       0,    36,     0,    54,    50,    52,     0,     0,    47,    59,
      37,     7,    18,     0,     7,     0,    28
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,  -211,  -211,    -5,    -4,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,   -88,  -210,  -211,  -211,  -211,    59,   -73,
      15,   -11,  -172,     8,   -24,   -56,  -211,  -211
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    20,     6,   194,   237,    55,    22,    23,
      24,    25,    26,   220,   217,    27,    28,    29,   123,   110,
      49,    30,   195,    51,    44,    45,    78,   129
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    50,    21,   128,     1,   111,   121,    53,   197,    58,
      59,     4,   182,    73,     5,    65,    82,   240,    84,    43,
     111,   243,    52,    54,    56,     8,     9,    63,   183,    76,
      10,    11,   215,    12,    77,    13,    74,    14,   112,    15,
      16,    17,    18,    31,   229,    32,   122,   102,   124,    83,
     126,   106,   238,   130,    33,   131,   132,   133,    64,   114,
      76,    70,    75,    34,    35,    77,    19,    66,   108,   144,
     145,   146,   147,   148,   149,    67,    79,    36,   120,    71,
      80,   254,    68,    69,    72,    81,   181,    99,    50,    50,
      50,    34,    35,   136,   137,   138,   139,   140,   141,   142,
     143,   109,   100,   111,   103,    36,    34,    35,    46,   104,
     162,   115,   155,   156,   150,   151,   152,   168,   105,   116,
      47,   117,    37,    38,    39,   118,    85,    86,    87,    88,
      89,    90,    91,    92,   119,   125,   127,    40,   239,   153,
     154,   187,   188,   157,   244,    41,   245,   158,   177,    34,
      35,   107,   180,   101,    48,   196,   163,   184,    42,    57,
     161,   159,   178,    36,   191,    37,    38,    39,   164,   165,
     166,   185,   167,    58,    59,    60,    95,    96,    97,    98,
      40,   169,   186,   172,   192,   204,    98,   189,    41,   193,
     209,   199,   211,    61,   190,   121,   212,   200,    62,   205,
     216,    42,   206,   222,   208,   224,   207,   213,   214,   223,
     228,   225,   226,   227,   218,   221,   230,   236,   235,   232,
     233,   241,   248,   249,   242,   250,   252,    34,    35,    46,
     251,   246,   256,   247,   221,   218,    34,    35,   198,   218,
     221,    47,   221,    37,    38,    39,   253,     0,   203,   255,
      36,     0,    37,    38,    39,    34,    35,   219,    40,     0,
      34,    35,     0,     0,     0,     0,    41,    40,     0,    36,
       0,    37,    38,    39,    36,    41,    37,    38,    39,    42,
      93,    94,    95,    96,    97,    98,    40,     0,    42,     0,
       0,    40,     0,     0,    41,     0,     0,     0,     0,    41,
       0,     0,   135,     8,     9,     0,     0,    42,    10,    11,
       0,    12,    42,     0,     0,    14,     0,    15,    16,    17,
      18,    85,    86,    87,    88,    89,    90,    91,    92,    85,
      86,    87,    88,    89,    90,    91,    92,     0,    93,    94,
      95,    96,    97,    98,    19,     0,     0,     0,   231,     0,
       0,     0,     5,     0,   210,     0,   234,    85,    86,    87,
      88,    89,    90,    91,    92,    85,    86,    87,    88,    89,
      90,    91,    92,    85,    86,    87,    88,    89,    90,    91,
      92,     0,     0,   179,     0,     0,     0,     0,     0,   113,
      85,    86,    87,    88,    89,    90,    91,    92,     0,    93,
      94,    95,    96,    97,    98,     0,   134,    93,    94,    95,
      96,    97,    98,     0,   160,    93,    94,    95,    96,    97,
      98,     0,   170,    93,    94,    95,    96,    97,    98,     0,
     171,    93,    94,    95,    96,    97,    98,     0,   173,    93,
      94,    95,    96,    97,    98,     0,   201,    93,    94,    95,
      96,    97,    98,     0,   202,   174,    93,    94,    95,    96,
      97,    98,     0,     0,   175,    93,    94,    95,    96,    97,
      98,     0,     0,   176,    85,    86,    87,    88,    89,    90,
      91,    92,     0,    93,    94,    95,    96,    97,    98,    87,
      88,    89,    90,    91,    92
};

static const yytype_int16 yycheck[] =
{
       5,    12,     6,    76,    12,    61,     3,     3,   180,    24,
      25,     0,    10,    26,    14,    20,    40,   227,    42,    11,
      76,   231,    14,    19,    16,     3,     4,    19,    26,    44,
       8,     9,   204,    11,    49,    13,    49,    15,    62,    17,
      18,    19,    20,    19,   216,    19,    43,    52,    72,    41,
      74,    56,   224,    77,    44,    79,    80,    81,    14,    64,
      44,    26,    19,     5,     6,    49,    44,    54,    60,    93,
      94,    95,    96,    97,    98,    54,    44,    19,    70,    44,
      44,   253,    54,    54,    49,    44,   159,    54,    99,   100,
     101,     5,     6,    85,    86,    87,    88,    89,    90,    91,
      92,    43,    54,   159,    19,    19,     5,     6,     7,    26,
     114,    13,   104,   105,    99,   100,   101,   122,    53,    19,
      19,    19,    21,    22,    23,    19,    27,    28,    29,    30,
      31,    32,    33,    34,    19,     7,    43,    36,   226,    51,
      26,   165,   166,    51,   232,    44,   234,    43,   153,     5,
       6,     7,   157,    54,    53,   179,    26,   161,    57,    10,
      55,    54,   154,    19,   169,    21,    22,    23,    26,    49,
      49,   163,    19,    24,    25,    26,    37,    38,    39,    40,
      36,    43,     7,    43,    26,   190,    40,    54,    44,    26,
     195,   183,   197,    44,    51,     3,   200,    56,    49,    51,
     205,    57,    51,   208,    14,   210,    51,    26,    26,    52,
     215,    52,    51,    51,   206,   207,    52,    16,   222,    54,
      52,    52,    52,    52,   229,    52,    52,     5,     6,     7,
      51,   236,    52,   238,   226,   227,     5,     6,     7,   231,
     232,    19,   234,    21,    22,    23,   251,    -1,   189,   254,
      19,    -1,    21,    22,    23,     5,     6,     7,    36,    -1,
       5,     6,    -1,    -1,    -1,    -1,    44,    36,    -1,    19,
      -1,    21,    22,    23,    19,    44,    21,    22,    23,    57,
      35,    36,    37,    38,    39,    40,    36,    -1,    57,    -1,
      -1,    36,    -1,    -1,    44,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    57,     3,     4,    -1,    -1,    57,     8,     9,
      -1,    11,    57,    -1,    -1,    15,    -1,    17,    18,    19,
      20,    27,    28,    29,    30,    31,    32,    33,    34,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    35,    36,
      37,    38,    39,    40,    44,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    14,    -1,    51,    -1,    54,    27,    28,    29,
      30,    31,    32,    33,    34,    27,    28,    29,    30,    31,
      32,    33,    34,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    43,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    35,
      36,    37,    38,    39,    40,    -1,    43,    35,    36,    37,
      38,    39,    40,    -1,    50,    35,    36,    37,    38,    39,
      40,    -1,    50,    35,    36,    37,    38,    39,    40,    -1,
      50,    35,    36,    37,    38,    39,    40,    -1,    50,    35,
      36,    37,    38,    39,    40,    -1,    50,    35,    36,    37,
      38,    39,    40,    -1,    50,    43,    35,    36,    37,    38,
      39,    40,    -1,    -1,    43,    35,    36,    37,    38,    39,
      40,    -1,    -1,    43,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    35,    36,    37,    38,    39,    40,    29,
      30,    31,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    59,    60,     0,    14,    62,    62,     3,     4,
       8,     9,    11,    13,    15,    17,    18,    19,    20,    44,
      61,    63,    66,    67,    68,    69,    70,    73,    74,    75,
      79,    19,    19,    44,     5,     6,    19,    21,    22,    23,
      36,    44,    57,    81,    82,    83,     7,    19,    53,    78,
      79,    81,    81,     3,    19,    65,    81,    10,    24,    25,
      26,    44,    49,    81,    14,    62,    54,    54,    54,    54,
      26,    44,    49,    26,    49,    19,    44,    49,    84,    44,
      44,    44,    82,    81,    82,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    54,
      54,    54,    62,    19,    26,    53,    62,     7,    81,    43,
      77,    83,    82,    43,    62,    13,    19,    19,    19,    19,
      81,     3,    43,    76,    82,     7,    82,    43,    77,    85,
      82,    82,    82,    82,    43,    57,    81,    81,    81,    81,
      81,    81,    81,    81,    82,    82,    82,    82,    82,    82,
      78,    78,    78,    51,    26,    81,    81,    51,    43,    54,
      50,    55,    63,    26,    26,    49,    49,    19,    62,    43,
      50,    50,    43,    50,    43,    43,    43,    62,    81,    53,
      62,    77,    10,    26,    63,    81,     7,    82,    82,    54,
      51,    62,    26,    26,    63,    80,    82,    80,     7,    81,
      56,    50,    50,    76,    62,    51,    51,    51,    14,    62,
      51,    62,    63,    26,    26,    80,    62,    72,    81,     7,
      71,    81,    62,    52,    62,    52,    51,    51,    62,    80,
      52,    54,    54,    52,    54,    63,    16,    64,    80,    71,
      72,    52,    62,    72,    71,    71,    62,    62,    52,    52,
      52,    51,    52,    62,    80,    62,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    59,    60,    61,    61,    62,    62,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    65,
      65,    66,    66,    66,    66,    66,    67,    67,    68,    68,
      68,    68,    69,    69,    69,    69,    70,    70,    70,    70,
      71,    71,    71,    71,    72,    72,    73,    73,    73,    73,
      74,    74,    75,    76,    76,    77,    77,    78,    78,    78,
      78,    78,    78,    79,    79,    80,    80,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      83,    83,    83,    84,    84,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     3,     1,     4,     1,     0,     2,     1,
       3,     6,     3,     6,     2,     5,     9,     8,    11,     1,
       2,     2,     4,     1,     1,     2,     1,     0,     7,     3,
       4,     1,     1,     1,     1,     1,    10,    11,     3,     5,
       4,     2,     3,     5,     4,     2,     6,    10,     9,     5,
       3,     1,     3,     1,     3,     1,     9,     5,     6,    10,
       4,     3,     7,     2,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     4,     4,     4,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     2,     4,     0,     3,     0,     1
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
  case 2: /* prog: inicio nl cod nl FINAL  */
#line 1546 "calc_elidian.y"
                             {eval(newast('z', NULL, NULL));}
#line 2927 "calc_elidian.tab.c"
    break;

  case 3: /* prog: inicio nl FINAL  */
#line 1547 "calc_elidian.y"
                      {eval(newast('z', NULL, NULL));}
#line 2933 "calc_elidian.tab.c"
    break;

  case 4: /* inicio: INICIO  */
#line 1549 "calc_elidian.y"
               {eval(newast('y', NULL, NULL));}
#line 2939 "calc_elidian.tab.c"
    break;

  case 5: /* cod: cod NEWLINHA nl exp  */
#line 1551 "calc_elidian.y"
                         {eval((yyvsp[0].a));}
#line 2945 "calc_elidian.tab.c"
    break;

  case 6: /* cod: exp  */
#line 1552 "calc_elidian.y"
          {eval((yyvsp[0].a));}
#line 2951 "calc_elidian.tab.c"
    break;

  case 7: /* nl: %empty  */
#line 1554 "calc_elidian.y"
    {(yyval.a) = NULL;}
#line 2957 "calc_elidian.tab.c"
    break;

  case 8: /* nl: NEWLINHA nl  */
#line 1555 "calc_elidian.y"
                  {(yyval.a) = NULL;}
#line 2963 "calc_elidian.tab.c"
    break;

  case 9: /* exp: decl  */
#line 1557 "calc_elidian.y"
          {(yyval.a) = (yyvsp[0].a);}
#line 2969 "calc_elidian.tab.c"
    break;

  case 10: /* exp: VAR '=' logica  */
#line 1558 "calc_elidian.y"
                                {(yyval.a) = newasgn((yyvsp[-2].texto), newint(0), (yyvsp[0].a));}
#line 2975 "calc_elidian.tab.c"
    break;

  case 11: /* exp: VAR '[' arit ']' '=' logica  */
#line 1559 "calc_elidian.y"
                                             {(yyval.a) = newasgn((yyvsp[-5].texto), (yyvsp[-3].a), (yyvsp[0].a));}
#line 2981 "calc_elidian.tab.c"
    break;

  case 12: /* exp: VAR '=' TEXTO  */
#line 1560 "calc_elidian.y"
                    {(yyval.a) = newasgn((yyvsp[-2].texto), newint(0), newtexto((yyvsp[0].stexto)));}
#line 2987 "calc_elidian.tab.c"
    break;

  case 13: /* exp: VAR '[' arit ']' '=' TEXTO  */
#line 1561 "calc_elidian.y"
                                 {(yyval.a) = newasgn((yyvsp[-5].texto), (yyvsp[-3].a), newtexto((yyvsp[0].stexto)));}
#line 2993 "calc_elidian.tab.c"
    break;

  case 14: /* exp: VAR ENTRADA  */
#line 1562 "calc_elidian.y"
                  {(yyval.a) = newast('c', newValorVal((yyvsp[-1].texto), newint(0)), NULL);}
#line 2999 "calc_elidian.tab.c"
    break;

  case 15: /* exp: VAR '[' arit ']' ENTRADA  */
#line 1563 "calc_elidian.y"
                               {(yyval.a) = newast('c', newValorVal((yyvsp[-4].texto), (yyvsp[-2].a)), NULL);}
#line 3005 "calc_elidian.tab.c"
    break;

  case 16: /* exp: IF logica nl '{' nl list nl '}' else  */
#line 1564 "calc_elidian.y"
                                           {(yyval.a) = newflow('I', (yyvsp[-7].a), (yyvsp[-3].a), (yyvsp[0].a));}
#line 3011 "calc_elidian.tab.c"
    break;

  case 17: /* exp: WHILE logica nl '{' nl list nl '}'  */
#line 1565 "calc_elidian.y"
                                             {(yyval.a) = newflow('W', (yyvsp[-6].a), (yyvsp[-2].a), NULL);}
#line 3017 "calc_elidian.tab.c"
    break;

  case 18: /* exp: FOR atrib ';' logica ';' arit '{' nl list nl '}'  */
#line 1566 "calc_elidian.y"
                                                       {(yyval.a) = newflowfor('F', (yyvsp[-9].a), (yyvsp[-7].a), (yyvsp[-5].a), (yyvsp[-2].a), NULL);}
#line 3023 "calc_elidian.tab.c"
    break;

  case 19: /* exp: iterator  */
#line 1567 "calc_elidian.y"
               {(yyval.a) = (yyvsp[0].a);}
#line 3029 "calc_elidian.tab.c"
    break;

  case 20: /* exp: SAIDA saida  */
#line 1568 "calc_elidian.y"
                            {(yyval.a) = (yyvsp[0].a);}
#line 3035 "calc_elidian.tab.c"
    break;

  case 21: /* exp: SAIDA ';'  */
#line 1569 "calc_elidian.y"
                {(yyval.a) = newast('P', NULL, NULL);}
#line 3041 "calc_elidian.tab.c"
    break;

  case 22: /* exp: TYPE '(' VAR ')'  */
#line 1570 "calc_elidian.y"
                       {(yyval.a) = newast('T', newtexto((yyvsp[-1].texto)), NULL);}
#line 3047 "calc_elidian.tab.c"
    break;

  case 23: /* exp: incdec  */
#line 1571 "calc_elidian.y"
             {(yyval.a) = (yyvsp[0].a);}
#line 3053 "calc_elidian.tab.c"
    break;

  case 24: /* exp: outfunc  */
#line 1572 "calc_elidian.y"
              {(yyval.a) = (yyvsp[0].a);}
#line 3059 "calc_elidian.tab.c"
    break;

  case 25: /* exp: RETURN logica  */
#line 1573 "calc_elidian.y"
                    {(yyval.a) = newast('j', (yyvsp[0].a), NULL);}
#line 3065 "calc_elidian.tab.c"
    break;

  case 26: /* exp: PASS  */
#line 1574 "calc_elidian.y"
           {(yyval.a) = newast('l', NULL, NULL);}
#line 3071 "calc_elidian.tab.c"
    break;

  case 27: /* else: %empty  */
#line 1576 "calc_elidian.y"
      {(yyval.a) = NULL;}
#line 3077 "calc_elidian.tab.c"
    break;

  case 28: /* else: ELSE nl '{' nl list nl '}'  */
#line 1577 "calc_elidian.y"
                                 {(yyval.a) = (yyvsp[-2].a);}
#line 3083 "calc_elidian.tab.c"
    break;

  case 29: /* atrib: VAR '=' logica  */
#line 1579 "calc_elidian.y"
                      {(yyval.a) = newasgn((yyvsp[-2].texto), newint(0), (yyvsp[0].a));}
#line 3089 "calc_elidian.tab.c"
    break;

  case 30: /* atrib: TIPO VAR '=' logica  */
#line 1580 "calc_elidian.y"
                          {(yyval.a) = newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), (yyvsp[0].a), NULL);}
#line 3095 "calc_elidian.tab.c"
    break;

  case 31: /* decl: declvar  */
#line 1582 "calc_elidian.y"
              {(yyval.a) = (yyvsp[0].a);}
#line 3101 "calc_elidian.tab.c"
    break;

  case 32: /* decl: declvartexto  */
#line 1583 "calc_elidian.y"
                   {(yyval.a) = (yyvsp[0].a);}
#line 3107 "calc_elidian.tab.c"
    break;

  case 33: /* decl: declvectexto  */
#line 1584 "calc_elidian.y"
                   {(yyval.a) = (yyvsp[0].a);}
#line 3113 "calc_elidian.tab.c"
    break;

  case 34: /* decl: declfunction  */
#line 1585 "calc_elidian.y"
                   {(yyval.a) = (yyvsp[0].a);}
#line 3119 "calc_elidian.tab.c"
    break;

  case 35: /* decl: declvecmult  */
#line 1586 "calc_elidian.y"
                  {(yyval.a) = (yyvsp[0].a);}
#line 3125 "calc_elidian.tab.c"
    break;

  case 36: /* declfunction: TIPO VAR '(' ')' nl '{' nl list nl '}'  */
#line 1589 "calc_elidian.y"
                                                     {(yyval.a) = newfunction((yyvsp[-9].inteiro), (yyvsp[-8].texto), NULL, (yyvsp[-2].a));}
#line 3131 "calc_elidian.tab.c"
    break;

  case 37: /* declfunction: TIPO VAR '(' args ')' nl '{' nl list nl '}'  */
#line 1590 "calc_elidian.y"
                                                  {(yyval.a) = newfunction((yyvsp[-10].inteiro), (yyvsp[-9].texto), (yyvsp[-7].a), (yyvsp[-2].a));}
#line 3137 "calc_elidian.tab.c"
    break;

  case 38: /* declvar: declvar ',' VAR  */
#line 1592 "calc_elidian.y"
                         {(yyval.a) = newvar((yyvsp[-2].a)->nodetype, (yyvsp[0].texto), NULL, (yyvsp[-2].a));}
#line 3143 "calc_elidian.tab.c"
    break;

  case 39: /* declvar: declvar ',' VAR '=' logica  */
#line 1593 "calc_elidian.y"
                                 {(yyval.a) = newvar((yyvsp[-4].a)->nodetype, (yyvsp[-2].texto), (yyvsp[0].a), (yyvsp[-4].a));}
#line 3149 "calc_elidian.tab.c"
    break;

  case 40: /* declvar: TIPO VAR '=' logica  */
#line 1594 "calc_elidian.y"
                          {(yyval.a) = newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), (yyvsp[0].a), NULL);}
#line 3155 "calc_elidian.tab.c"
    break;

  case 41: /* declvar: TIPO VAR  */
#line 1595 "calc_elidian.y"
               {(yyval.a) = newvar((yyvsp[-1].inteiro), (yyvsp[0].texto), NULL, NULL);}
#line 3161 "calc_elidian.tab.c"
    break;

  case 42: /* declvartexto: declvartexto ',' VAR  */
#line 1597 "calc_elidian.y"
                                   {(yyval.a) = newvar((yyvsp[-2].a)->nodetype, (yyvsp[0].texto), NULL, (yyvsp[-2].a));}
#line 3167 "calc_elidian.tab.c"
    break;

  case 43: /* declvartexto: declvartexto ',' VAR '=' TEXTO  */
#line 1598 "calc_elidian.y"
                                     {(yyval.a) = newvar((yyvsp[-4].a)->nodetype, (yyvsp[-2].texto), newtexto((yyvsp[0].stexto)), (yyvsp[-4].a));}
#line 3173 "calc_elidian.tab.c"
    break;

  case 44: /* declvartexto: TIPO_TEXTO VAR '=' TEXTO  */
#line 1599 "calc_elidian.y"
                               {(yyval.a) = newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), newtexto((yyvsp[0].stexto)), NULL);}
#line 3179 "calc_elidian.tab.c"
    break;

  case 45: /* declvartexto: TIPO_TEXTO VAR  */
#line 1600 "calc_elidian.y"
                     {(yyval.a) = newvar((yyvsp[-1].inteiro), (yyvsp[0].texto), NULL, NULL);}
#line 3185 "calc_elidian.tab.c"
    break;

  case 46: /* declvectexto: declvectexto ',' VAR '[' arit ']'  */
#line 1602 "calc_elidian.y"
                                                {(yyval.a) = newvec(((Symasgn*)(yyvsp[-5].a))->type, (yyvsp[-3].texto), (yyvsp[-1].a), NULL, (yyvsp[-5].a));}
#line 3191 "calc_elidian.tab.c"
    break;

  case 47: /* declvectexto: declvectexto ',' VAR '[' arit ']' '=' '{' valorvectexto '}'  */
#line 1603 "calc_elidian.y"
                                                                  {(yyval.a) = newvec(((Symasgn*)(yyvsp[-9].a))->type, (yyvsp[-7].texto), (yyvsp[-5].a), (yyvsp[-1].a), (yyvsp[-9].a));}
#line 3197 "calc_elidian.tab.c"
    break;

  case 48: /* declvectexto: TIPO_TEXTO VAR '[' arit ']' '=' '{' valorvectexto '}'  */
#line 1604 "calc_elidian.y"
                                                            {(yyval.a) = newvec((yyvsp[-8].inteiro), (yyvsp[-7].texto), (yyvsp[-5].a), (yyvsp[-1].a), NULL);}
#line 3203 "calc_elidian.tab.c"
    break;

  case 49: /* declvectexto: TIPO_TEXTO VAR '[' arit ']'  */
#line 1605 "calc_elidian.y"
                                  {(yyval.a) = newvec((yyvsp[-4].inteiro), (yyvsp[-3].texto), (yyvsp[-1].a), NULL, NULL);}
#line 3209 "calc_elidian.tab.c"
    break;

  case 50: /* valorvectexto: TEXTO ',' valorvectexto  */
#line 1607 "calc_elidian.y"
                                       {(yyval.a) = newast('l', newtexto((yyvsp[-2].stexto)), (yyvsp[0].a));}
#line 3215 "calc_elidian.tab.c"
    break;

  case 51: /* valorvectexto: TEXTO  */
#line 1608 "calc_elidian.y"
            {(yyval.a) = newast('l', newtexto((yyvsp[0].stexto)), NULL);}
#line 3221 "calc_elidian.tab.c"
    break;

  case 52: /* valorvectexto: logica ',' valorvectexto  */
#line 1609 "calc_elidian.y"
                               {(yyval.a) = newast('l', (yyvsp[-2].a), (yyvsp[0].a));}
#line 3227 "calc_elidian.tab.c"
    break;

  case 53: /* valorvectexto: logica  */
#line 1610 "calc_elidian.y"
             {(yyval.a) = newast('l', (yyvsp[0].a), NULL);}
#line 3233 "calc_elidian.tab.c"
    break;

  case 54: /* valorvec: logica ',' valorvec  */
#line 1612 "calc_elidian.y"
                              {(yyval.a) = newast('l', (yyvsp[-2].a), (yyvsp[0].a));}
#line 3239 "calc_elidian.tab.c"
    break;

  case 55: /* valorvec: logica  */
#line 1613 "calc_elidian.y"
             {(yyval.a) = newast('l', (yyvsp[0].a), NULL);}
#line 3245 "calc_elidian.tab.c"
    break;

  case 56: /* declvecmult: TIPO VAR '[' arit ']' '=' '{' valorvec '}'  */
#line 1615 "calc_elidian.y"
                                                        {(yyval.a) = newvec((yyvsp[-8].inteiro), (yyvsp[-7].texto), (yyvsp[-5].a), (yyvsp[-1].a), NULL);}
#line 3251 "calc_elidian.tab.c"
    break;

  case 57: /* declvecmult: TIPO VAR '[' arit ']'  */
#line 1616 "calc_elidian.y"
                            {(yyval.a) = newvec((yyvsp[-4].inteiro), (yyvsp[-3].texto), (yyvsp[-1].a), NULL, NULL);}
#line 3257 "calc_elidian.tab.c"
    break;

  case 58: /* declvecmult: declvecmult ',' VAR '[' arit ']'  */
#line 1617 "calc_elidian.y"
                                       {(yyval.a) = newvec(((Symasgn*)(yyvsp[-5].a))->type, (yyvsp[-3].texto), (yyvsp[-1].a), NULL, (yyvsp[-5].a));}
#line 3263 "calc_elidian.tab.c"
    break;

  case 59: /* declvecmult: declvecmult ',' VAR '[' arit ']' '=' '{' valorvec '}'  */
#line 1618 "calc_elidian.y"
                                                            {(yyval.a) = newvec(((Symasgn*)(yyvsp[-9].a))->type, (yyvsp[-7].texto), (yyvsp[-5].a), (yyvsp[-1].a), (yyvsp[-9].a));}
#line 3269 "calc_elidian.tab.c"
    break;

  case 60: /* outfunc: VAR '(' arg ')'  */
#line 1620 "calc_elidian.y"
                         {(yyval.a) = newast('a', newtexto((yyvsp[-3].texto)), (yyvsp[-1].a));}
#line 3275 "calc_elidian.tab.c"
    break;

  case 61: /* outfunc: VAR '(' ')'  */
#line 1621 "calc_elidian.y"
                  {(yyval.a) = newast('a', newtexto((yyvsp[-2].texto)), NULL);}
#line 3281 "calc_elidian.tab.c"
    break;

  case 62: /* iterator: '(' logica ')' '?' exp ':' exp  */
#line 1623 "calc_elidian.y"
                                                        {(yyval.a) = newflow('?', (yyvsp[-5].a), (yyvsp[-2].a), (yyvsp[0].a));}
#line 3287 "calc_elidian.tab.c"
    break;

  case 63: /* args: TIPO VAR  */
#line 1625 "calc_elidian.y"
               {(yyval.a) = newast('l', newvar((yyvsp[-1].inteiro), (yyvsp[0].texto), NULL, NULL), NULL);}
#line 3293 "calc_elidian.tab.c"
    break;

  case 64: /* args: TIPO VAR ',' args  */
#line 1626 "calc_elidian.y"
                        {(yyval.a) = newast('l', newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), NULL, NULL), (yyvsp[0].a));}
#line 3299 "calc_elidian.tab.c"
    break;

  case 65: /* arg: valor  */
#line 1628 "calc_elidian.y"
           {(yyval.a) = newast('l', (yyvsp[0].a), NULL);}
#line 3305 "calc_elidian.tab.c"
    break;

  case 66: /* arg: valor ',' arg  */
#line 1629 "calc_elidian.y"
                    {(yyval.a) = newast('l', (yyvsp[-2].a), (yyvsp[0].a));}
#line 3311 "calc_elidian.tab.c"
    break;

  case 67: /* saida: logica  */
#line 1631 "calc_elidian.y"
              {(yyval.a) = newast('P', (yyvsp[0].a), NULL);}
#line 3317 "calc_elidian.tab.c"
    break;

  case 68: /* saida: logica ',' saida  */
#line 1632 "calc_elidian.y"
                       { (yyval.a) = newast('P', (yyvsp[-2].a), (yyvsp[0].a));}
#line 3323 "calc_elidian.tab.c"
    break;

  case 69: /* saida: TEXTO  */
#line 1633 "calc_elidian.y"
            {(yyval.a) = newast('P', newtexto((yyvsp[0].stexto)), NULL);}
#line 3329 "calc_elidian.tab.c"
    break;

  case 70: /* saida: TEXTO ',' saida  */
#line 1634 "calc_elidian.y"
                      {(yyval.a) = newast('P', newtexto((yyvsp[-2].stexto)), (yyvsp[0].a));}
#line 3335 "calc_elidian.tab.c"
    break;

  case 71: /* saida: incdec  */
#line 1635 "calc_elidian.y"
             {(yyval.a) = newast('P', (yyvsp[0].a), NULL);}
#line 3341 "calc_elidian.tab.c"
    break;

  case 72: /* saida: incdec ',' saida  */
#line 1636 "calc_elidian.y"
                       { (yyval.a) = newast('P', (yyvsp[-2].a), (yyvsp[0].a));}
#line 3347 "calc_elidian.tab.c"
    break;

  case 73: /* incdec: VAR PLUS  */
#line 1638 "calc_elidian.y"
                             {(yyval.a) = newasgn((yyvsp[-1].texto), newint(0), newast('+', newValorVal((yyvsp[-1].texto), newint(0)), newint(1)));}
#line 3353 "calc_elidian.tab.c"
    break;

  case 74: /* incdec: VAR LESS  */
#line 1639 "calc_elidian.y"
                           {(yyval.a) = newasgn((yyvsp[-1].texto), newint(0), newast('-', newValorVal((yyvsp[-1].texto), newint(0)), newint(1)));}
#line 3359 "calc_elidian.tab.c"
    break;

  case 75: /* list: exp  */
#line 1643 "calc_elidian.y"
          {(yyval.a) = (yyvsp[0].a);}
#line 3365 "calc_elidian.tab.c"
    break;

  case 76: /* list: list NEWLINHA nl exp  */
#line 1644 "calc_elidian.y"
                           { (yyval.a) = newast('L', (yyvsp[-3].a), (yyvsp[0].a));}
#line 3371 "calc_elidian.tab.c"
    break;

  case 77: /* logica: logica OR logica  */
#line 1646 "calc_elidian.y"
                         {(yyval.a) = newcmp(7,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3377 "calc_elidian.tab.c"
    break;

  case 78: /* logica: logica AND logica  */
#line 1647 "calc_elidian.y"
                        {(yyval.a) = newcmp(8,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3383 "calc_elidian.tab.c"
    break;

  case 79: /* logica: logica MAIOR logica  */
#line 1648 "calc_elidian.y"
                          {(yyval.a) = newcmp(1,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3389 "calc_elidian.tab.c"
    break;

  case 80: /* logica: logica MENOR logica  */
#line 1649 "calc_elidian.y"
                          {(yyval.a) = newcmp(2,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3395 "calc_elidian.tab.c"
    break;

  case 81: /* logica: logica DIF logica  */
#line 1650 "calc_elidian.y"
                        {(yyval.a) = newcmp(3,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3401 "calc_elidian.tab.c"
    break;

  case 82: /* logica: logica II logica  */
#line 1651 "calc_elidian.y"
                       {(yyval.a) = newcmp(4,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3407 "calc_elidian.tab.c"
    break;

  case 83: /* logica: logica MAI logica  */
#line 1652 "calc_elidian.y"
                        {(yyval.a) = newcmp(5,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3413 "calc_elidian.tab.c"
    break;

  case 84: /* logica: logica MEI logica  */
#line 1653 "calc_elidian.y"
                        {(yyval.a) = newcmp(6,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3419 "calc_elidian.tab.c"
    break;

  case 85: /* logica: arit  */
#line 1654 "calc_elidian.y"
           {(yyval.a) = (yyvsp[0].a);}
#line 3425 "calc_elidian.tab.c"
    break;

  case 86: /* arit: SIN '(' arit ')'  */
#line 1656 "calc_elidian.y"
                       {(yyval.a) = newast('S',(yyvsp[-1].a),NULL);}
#line 3431 "calc_elidian.tab.c"
    break;

  case 87: /* arit: COS '(' arit ')'  */
#line 1657 "calc_elidian.y"
                       {(yyval.a) = newast('C',(yyvsp[-1].a),NULL);}
#line 3437 "calc_elidian.tab.c"
    break;

  case 88: /* arit: RAIZ '(' arit ')'  */
#line 1658 "calc_elidian.y"
                        {(yyval.a) = newast('R',(yyvsp[-1].a),NULL);}
#line 3443 "calc_elidian.tab.c"
    break;

  case 89: /* arit: '-' arit  */
#line 1659 "calc_elidian.y"
                         {(yyval.a) = newast('M', (yyvsp[0].a), NULL);}
#line 3449 "calc_elidian.tab.c"
    break;

  case 90: /* arit: '|' arit '|'  */
#line 1660 "calc_elidian.y"
                   {(yyval.a) = newast('A',(yyvsp[-1].a),NULL);}
#line 3455 "calc_elidian.tab.c"
    break;

  case 91: /* arit: arit '+' arit  */
#line 1661 "calc_elidian.y"
                    {(yyval.a) = newast('+',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3461 "calc_elidian.tab.c"
    break;

  case 92: /* arit: arit '-' arit  */
#line 1662 "calc_elidian.y"
                    {(yyval.a) = newast('-',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3467 "calc_elidian.tab.c"
    break;

  case 93: /* arit: arit '*' arit  */
#line 1663 "calc_elidian.y"
                    {(yyval.a) = newast('*',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3473 "calc_elidian.tab.c"
    break;

  case 94: /* arit: arit '/' arit  */
#line 1664 "calc_elidian.y"
                    {(yyval.a) = newast('/',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3479 "calc_elidian.tab.c"
    break;

  case 95: /* arit: arit '%' arit  */
#line 1665 "calc_elidian.y"
                    {(yyval.a) = newast('%',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3485 "calc_elidian.tab.c"
    break;

  case 96: /* arit: arit '^' arit  */
#line 1666 "calc_elidian.y"
                    {(yyval.a) = newast('^',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3491 "calc_elidian.tab.c"
    break;

  case 97: /* arit: '(' logica ')'  */
#line 1667 "calc_elidian.y"
                     {(yyval.a) = (yyvsp[-1].a);}
#line 3497 "calc_elidian.tab.c"
    break;

  case 98: /* arit: valor  */
#line 1668 "calc_elidian.y"
            {(yyval.a) = (yyvsp[0].a);}
#line 3503 "calc_elidian.tab.c"
    break;

  case 99: /* valor: INTEIRO  */
#line 1671 "calc_elidian.y"
               {(yyval.a) = newint((yyvsp[0].inteiro));}
#line 3509 "calc_elidian.tab.c"
    break;

  case 100: /* valor: REAL  */
#line 1672 "calc_elidian.y"
           {(yyval.a) = newreal((yyvsp[0].real));}
#line 3515 "calc_elidian.tab.c"
    break;

  case 101: /* valor: VAR varvar  */
#line 1673 "calc_elidian.y"
                 {
        if((yyvsp[0].a)==NULL) (yyval.a) = newValorVal((yyvsp[-1].texto), newint(0));
        else (yyval.a) = newast('a', newtexto((yyvsp[-1].texto)), (yyvsp[0].a)->r);
    }
#line 3524 "calc_elidian.tab.c"
    break;

  case 102: /* valor: VAR '[' arit ']'  */
#line 1677 "calc_elidian.y"
                       {(yyval.a) = newValorVal((yyvsp[-3].texto), (yyvsp[-1].a));}
#line 3530 "calc_elidian.tab.c"
    break;

  case 103: /* varvar: %empty  */
#line 1679 "calc_elidian.y"
        {(yyval.a) = NULL;}
#line 3536 "calc_elidian.tab.c"
    break;

  case 104: /* varvar: '(' varfun ')'  */
#line 1680 "calc_elidian.y"
                     {
        if ((yyvsp[-1].a)!=NULL) (yyval.a) = newast('j', NULL, (yyvsp[-1].a)->r);
        else (yyval.a) = newast('j', NULL, NULL);
    }
#line 3545 "calc_elidian.tab.c"
    break;

  case 105: /* varfun: %empty  */
#line 1685 "calc_elidian.y"
        {(yyval.a) = NULL;}
#line 3551 "calc_elidian.tab.c"
    break;

  case 106: /* varfun: arg  */
#line 1686 "calc_elidian.y"
          {(yyval.a) = newast('j', NULL, (yyvsp[0].a));}
#line 3557 "calc_elidian.tab.c"
    break;


#line 3561 "calc_elidian.tab.c"

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

#line 1688 "calc_elidian.y"


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
