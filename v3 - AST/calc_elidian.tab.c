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
		char name[name_size];
        int *v;
        //struct veci * in;
		struct veci * prox;
	} Veci;
    // estrutura de vetor real
    typedef struct vecr {
		char name[name_size];
        double *v;
        //struct veci * in;
		struct vecr * prox;
	} Vecr;
    // estrutura de vetor caractere
    typedef struct vect {
		char name[name_size];
        char *v;
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
        int tam;
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
        int pos;
    }Varval;

    typedef struct listavar {
        char name[name_size];
        VARSI *ivar;
        VARS *rvar;
        VARST *tvar;
        Vec * vecg;
        Veci * ivec;
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
        int i = 1;
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
	Vec * insvec(Vec *l, int t, char n[], int tam){
		Vec *aux =(Vec*)malloc(sizeof(Vec));
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
	Vec *srchvec(Vec *l, char n[]){
		Vec *aux = l;
		while(aux != NULL){
			if(strcmp(n, aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
	}
    //add novo vetor na lista de vetores
	Veci * insveci(Veci *l, char n[], int tam){
		Veci *aux =(Veci*)malloc(sizeof(Veci));
		if(!aux) {
            printf("out of space");
            exit(0);
        }
        strcpy(aux->name, n);
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
    Ast * newvec(int t, char s[], int tam, Ast *v, Ast *n){
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

    Ast * newasgn(char s[], int pos, Ast *v) { /*Função para um nó de atribuição*/
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

    Ast * newValorVal(char s[], int pos) { /*Função que recupera o nome/referência de uma variável, neste caso o número*/    
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

    bool varexiste(Listavar * l, char v[]) {
        //printf("varexiste begin\n");
        VARS* xr = (VARS*)malloc(sizeof(VARS));
        VARSI* xi = (VARSI*)malloc(sizeof(VARSI));
        VARST* xt = (VARST*)malloc(sizeof(VARST));
        Vec*vg = (Vec*)malloc(sizeof(Vec));
        Veci*vi = (Veci*)malloc(sizeof(Veci));
        while(l!=NULL){
            xr = srch(l->rvar, v);
            xi = srchi(l->ivar, v);
            xt = srcht(l->tvar, v);
            Vec* vg = srchvec(lista->vecg, v);
            Veci* vi = srchveci(lista->ivec, v);

            if (xr) {
                //printf("varexiste end 1\n");
                return true; // se tudo NULL, var nao existe
            }
            if (xi) {
                //printf("varexiste end 2\n");
                return true; // se tudo NULL, var nao existe
            }
            if (xt) {
                //printf("varexiste end 3\n");
                return true; // se tudo NULL, var nao existe
            }
            if(vg) return true;
            if(vi) return true;
            break;
        }
        //printf("varexiste end 4\n");
        return false; // se tudo NULL, var nao existe
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
        Vec *auxg;
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
                        auxg = srchvec(auxl->vecg, var);
                        if (auxg){
                            if(pos<auxg->tam){
                            printf("%.2f", auxg->v[pos]);
                            } else {
                                printf("\nErro (printValorVar()) - posicao fora do tamanho do vetor.\n", var);
                            }
                            break;
                        }
                        else{
                            if(auxl->prox==NULL)
                                printf ("\nErro (printValorVar()) - Variavel '%s' nao foi declarada.\n", var);
                        }
                    }
                }
            }
            auxl = auxl->prox;
        }
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
        Vec * auxg = (Vec*)malloc(sizeof(Vec));
        if(!auxg) {
            printf("out of space (eval 'auxg')");
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
                    auxr = srch(auxl->rvar, ((Varval*)a)->var);
                    //if(auxr)
                        //printf("var okay\n");
                    if (auxr==NULL){
                        auxi = srchi(auxl->ivar, ((Varval*)a)->var);
                        if (!auxi){
                            auxt = srcht(auxl->tvar, ((Varval*)a)->var);
                            if (!auxt){
                                auxg = srchvec(auxl->vecg, ((Varval*)a)->var);
                                if(!auxg){
                                    if(auxl->prox==NULL){
                                        printf ("Erro (case 'N') - Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                                        v = 0.0;
                                        break;
                                    }
                                } else {
                                    if (((Varval*)a)->pos<auxg->tam)
                                        v = auxg->v[((Varval*)a)->pos];
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

            case '+': v = eval(a->l) + eval(a->r); break;	/*Operações "árv esq   +   árv dir"*/
            case '-': v = eval(a->l) - eval(a->r); break;	/*Operações*/
            case '*': v = eval(a->l) * eval(a->r); break;	/*Operações*/
            case '/': v = eval(a->l) / eval(a->r); break; /*Operações*/
            case '%':; 
                double v1 = eval(a->l);
                double v2 = eval(a->r);
                v = v1/v2;
                int aa = (int)v;
                v = (v - aa)*v2;
                break; /*Operações*/
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
                    auxr = srch(auxl->rvar, ((Symasgn *)a)->s);
                    if(!auxr){
                        auxi = srchi(auxl->ivar, ((Symasgn *)a)->s);
                        if(!auxi){
                            auxt = srcht(auxl->tvar, ((Symasgn *)a)->s);
                            if(!auxt){
                                auxg = srchvec(auxl->vecg, ((Symasgn *)a)->s);
                                if(!auxg){
                                    if(auxl->prox == NULL){
                                        printf("\nErro de var nao declarada\n");
                                        v = 0.0;
                                        break;
                                    }
                                } else {
                                    auxg->v[((Symasgn *)a)->tam] = v;
                                }
                            } else{
                                strcpy(auxt->v, ((Textoval*)((Symasgn *)a)->v)->v); /*Atribui à variável*/
                                break;
                            }
                        } else{
                            auxi->v = (int)v; /*Atribui à variável*/
                            break;
                        }
                    } else{
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
            case 'l': v = eval(a->l); eval(a->r); break;
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
                    printValorVar(lista, ((Varval*)a->l)->var, ((Varval*)a->l)->pos);
                    //printf("nodetype 'NN'\n");
                }
                else if(((Intval*)a->l)->nodetype == 'k')
                    printf ("%d", ((Intval*)a->l)->v);		/*Recupera um valor inteiro*/
                else if(((Realval*)a->l)->nodetype == 'K')
                    printf ("%.2f", ((Realval*)a->l)->v);		/*Recupera um valor real*/
                else if(((Textoval*)a->l)->nodetype == 'm') {
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
                    lista->vecg = insvec(lista->vecg, ((Symasgn *)a)->nodetype, ((Symasgn *)a)->s, ((Symasgn *)a)->tam);
                    //printf("vec name %s\n", vecg->name);
                    Ast *auxz = ((Symasgn *)a)->v;
                    //int posz = 0;
                    for(int posz = 0; posz<lista->vecg->tam && auxz!=NULL; posz++, auxz = auxz->r){
                        lista->vecg->v[posz] = eval(auxz->l); /*Atribui à variável*/
                        //auxz = auxz->prox;
                        //posz++;
                    }
                    //printf("vec name %.2f\n", vecg->v[3]);
                }else
                    printf("\nErro (case 'i'): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);                
                break;

            // declarar variavel inteiro
            case 'i':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(lista, ((Symasgn *)a)->s)){
                    VARSI *ivar = insi(lista->ivar, ((Symasgn *)a)->s);
                    if(((Symasgn *)a)->v)
                        ivar->v = (int)eval(((Symasgn *)a)->v); /*Atribui à variável*/
                }else
                    printf("\nErro (case 'i'): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
                break;
            // declarar variavel real
            case 'r':;
                //printf("real begin\n");
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                //printf("real 2: %d\n", varexiste(lista, ((Symasgn *)a)->s));
                if(!varexiste(lista, ((Symasgn *)a)->s)){
                    //printf("real 3\n");
                    
                    //printf("real 4 \n");
                    //printf("real 4.5 rvar->name = %s\n", rvar->name);
                    if(((Symasgn *)a)->v)
                        v = eval(((Symasgn *)a)->v);
                    
                    lista->rvar = ins(lista->rvar, ((Symasgn *)a)->s);
                    //printf("real 5\n");
                    lista->rvar->v = v;
                    //printf("real 6\n");
                }else
                    printf("\nErro (case 'r'): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
                //srch(lista->rvar, ((Symasgn *)a)->s)
                //printf("R real %s = %f\n", lista->rvar->name, lista->rvar->v);
                //printf("real end\n");
                break;
            // declarar variavel texto
            case 't':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(lista, ((Symasgn *)a)->s)){
                    VARST *tvar = inst(lista->tvar, ((Symasgn *)a)->s);
                    if((((Symasgn *)a)->v))
                        strcpy(tvar->v, ((Textoval*)((Symasgn*)a)->v)->v);
                }else
                    printf("\nErro (case 't'): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
                break;
            
            // leitura das variaveis: int, real e texto
            case 'c':; 
                //v = eval(((Symasgn *)a)->v); /*Recupera o valor*/
                auxl = lista;
                while(auxl != NULL){
                    auxr = srch(auxl->rvar, ((Varval *)a->l)->var);
                    if(auxr){
                        scanf("%f", &auxr->v);
                    } else {
                        auxi = srchi(auxl->ivar, ((Varval *)a->l)->var);
                        if(auxi){
                            scanf("%d", &auxi->v);
                        } else {
                            auxt = srcht(auxl->tvar, ((Varval *)a->l)->var);
                            if(auxt){
                                scanf("%s", &auxt->v);
                            } else {
                                if(auxl->prox == NULL)
                                    printf("\nErro(<<): Variavel invalida!\n");
                                else
                                    auxl = auxl->prox;
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
            
            case 'B':;
                //printf("func %s\n", ((Func*)a)->name);
                
                if(srchfunction(lista->function, ((Func*)a)->name)==NULL){
                    lista->function = insfunction(lista->function, ((Func*)a));
                } else
                    printf("\nErro (case 'B'): reescrita de funcao nao permitida\n");
                //printf("tion %s\n", ((Func*)a)->name);
                break;
            
            case 'a':;
                auxl = lista;
                while(auxl != NULL){
                    auxf = srchfunctionall(auxl, ((Textoval*)a->l)->v);
                    //printf("auxf->name = %s\n", auxf->name);
                    if(auxf==NULL){
                        if(auxl->prox == NULL)
                            printf("\nErro (case 'a'): funcao nao declarada\n");
                        auxl = auxl->prox;
                        //printf("case 'a'\n");
                    } else {
                        //printf("function yes\n");
                        
                        Listavar * auxz = (Listavar*)malloc(sizeof(Listavar));
                        strcpy(auxz->name, auxf->name);
                        auxz->ivar = NULL;
                        auxz->rvar = NULL;
                        auxz->tvar = NULL;
                        auxz->ivec = NULL;
                        auxz->function = NULL;
                        auxz->prox = lista;
                        lista = auxz;
                        //printf("hum 22\n");
                        //strcpy(lista->name, auxf->name);
                        
                        //VARSI * i1 = ivar;
                        //VARS *r1 = rvar;
                        //VARST *t1 = tvar;

                        // verifica e executa as declarações e atribuições de ARGUMENTOS da função
                        if(auxf->args!=NULL && a->r!=NULL) {
                            Ast *b = auxf->args;
                            Ast *c = a->r;
                            while(c){
                                //printf("begin c\n");
                                eval(newvar(b->l->nodetype, ((Symasgn*)b->l)->s, c->l, NULL));
                                //eval(newast('P', newValorVal(((Symasgn*)b->l)->s), NULL));
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
                g->vecg = NULL;
                g->ivec = NULL;
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


#line 1287 "calc_elidian.tab.c"

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
    COMENTARIO = 275,              /* COMENTARIO  */
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
    FUN2 = 292,                    /* FUN2  */
    ITERATOR = 293,                /* ITERATOR  */
    NEG = 294,                     /* NEG  */
    VARP = 295                     /* VARP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 1217 "calc_elidian.y"

    char texto[50];
    int inteiro;
    double real;
    Ast *a;

#line 1381 "calc_elidian.tab.c"

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
  YYSYMBOL_COMENTARIO = 20,                /* COMENTARIO  */
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
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_FUN = 44,                       /* FUN  */
  YYSYMBOL_FUN2 = 45,                      /* FUN2  */
  YYSYMBOL_ITERATOR = 46,                  /* ITERATOR  */
  YYSYMBOL_NEG = 47,                       /* NEG  */
  YYSYMBOL_VARP = 48,                      /* VARP  */
  YYSYMBOL_49_ = 49,                       /* '['  */
  YYSYMBOL_50_ = 50,                       /* ']'  */
  YYSYMBOL_51_ = 51,                       /* '{'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_53_ = 53,                       /* ';'  */
  YYSYMBOL_54_ = 54,                       /* ')'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* '?'  */
  YYSYMBOL_57_ = 57,                       /* ':'  */
  YYSYMBOL_58_ = 58,                       /* '|'  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_prog = 60,                      /* prog  */
  YYSYMBOL_inicio = 61,                    /* inicio  */
  YYSYMBOL_cod = 62,                       /* cod  */
  YYSYMBOL_nl = 63,                        /* nl  */
  YYSYMBOL_exp = 64,                       /* exp  */
  YYSYMBOL_else = 65,                      /* else  */
  YYSYMBOL_atrib = 66,                     /* atrib  */
  YYSYMBOL_decl = 67,                      /* decl  */
  YYSYMBOL_declfunction = 68,              /* declfunction  */
  YYSYMBOL_declvar = 69,                   /* declvar  */
  YYSYMBOL_declvartexto = 70,              /* declvartexto  */
  YYSYMBOL_valorvec = 71,                  /* valorvec  */
  YYSYMBOL_declvecmult = 72,               /* declvecmult  */
  YYSYMBOL_outfunc = 73,                   /* outfunc  */
  YYSYMBOL_iterator = 74,                  /* iterator  */
  YYSYMBOL_args = 75,                      /* args  */
  YYSYMBOL_arg = 76,                       /* arg  */
  YYSYMBOL_saida = 77,                     /* saida  */
  YYSYMBOL_incdec = 78,                    /* incdec  */
  YYSYMBOL_list = 79,                      /* list  */
  YYSYMBOL_logica = 80,                    /* logica  */
  YYSYMBOL_arit = 81,                      /* arit  */
  YYSYMBOL_valor = 82,                     /* valor  */
  YYSYMBOL_varvar = 83,                    /* varvar  */
  YYSYMBOL_varfun = 84                     /* varfun  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   379

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  227

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
      43,    54,    37,    35,    55,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,    53,
       2,    26,     2,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,    58,    52,     2,     2,     2,     2,
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
      42,    44,    45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,  1271,  1271,  1272,  1274,  1276,  1277,  1279,  1280,  1282,
    1283,  1287,  1288,  1289,  1291,  1292,  1294,  1295,  1296,  1298,
    1299,  1301,  1302,  1303,  1304,  1305,  1308,  1309,  1314,  1315,
    1317,  1318,  1319,  1322,  1323,  1325,  1326,  1327,  1328,  1330,
    1331,  1332,  1333,  1340,  1341,  1343,  1344,  1345,  1346,  1352,
    1353,  1355,  1358,  1359,  1361,  1362,  1367,  1368,  1369,  1370,
    1371,  1372,  1375,  1376,  1380,  1381,  1383,  1384,  1385,  1386,
    1387,  1388,  1389,  1390,  1391,  1393,  1394,  1395,  1396,  1397,
    1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,  1408,  1409,
    1417,  1421,  1423,  1424,  1430,  1431
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
  "COMENTARIO", "RAIZ", "COS", "SIN", "PLUS", "LESS", "'='", "OR", "AND",
  "MAIOR", "MENOR", "MEI", "MAI", "II", "DIF", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'^'", "PLUS2", "LESS2", "'('", "FUN", "FUN2", "ITERATOR", "NEG",
  "VARP", "'['", "']'", "'{'", "'}'", "';'", "')'", "','", "'?'", "':'",
  "'|'", "$accept", "prog", "inicio", "cod", "nl", "exp", "else", "atrib",
  "decl", "declfunction", "declvar", "declvartexto", "valorvec",
  "declvecmult", "outfunc", "iterator", "args", "arg", "saida", "incdec",
  "list", "logica", "arit", "valor", "varvar", "varfun", YY_NULLPTR
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
      94,   289,   290,    40,   291,   292,   293,   294,   295,    91,
      93,   123,   125,    59,    41,    44,    63,    58,   124
};
#endif

#define YYPACT_NINF (-192)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,  -192,    18,    10,  -192,    10,   204,  -192,     1,    25,
      38,    24,    64,  -192,    24,     6,    24,    99,  -192,    24,
      34,  -192,  -192,  -192,    -6,    13,    36,  -192,  -192,  -192,
      90,    75,    84,  -192,  -192,   -27,    61,    62,    63,    24,
      24,    24,   342,   242,  -192,    53,    72,  -192,  -192,    65,
     221,   275,   100,    92,    74,   300,  -192,  -192,  -192,   107,
       7,   126,   239,    10,   119,   115,   122,   128,    24,     8,
     146,   145,   101,    22,   148,  -192,    24,    24,    24,  -192,
     258,   278,    24,    24,    24,    24,    24,    24,    24,    24,
      24,    24,    24,    24,    24,    24,   139,   139,   139,    10,
     133,    24,    24,    10,  -192,   342,  -192,   109,   113,   104,
     108,   222,  -192,   144,   147,   123,   342,   152,   125,   120,
     127,  -192,  -192,  -192,   129,   131,    -3,   302,   308,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,    26,
      26,   149,   149,   149,   149,  -192,  -192,  -192,   222,    24,
     342,   267,   222,  -192,    22,   153,   222,  -192,    24,   177,
     180,   132,    10,   140,   166,  -192,  -192,  -192,  -192,  -192,
    -192,   181,   342,    24,   181,  -192,    24,   137,   342,  -192,
     150,   196,   222,    10,   151,    10,   154,   328,   157,   342,
     222,   178,  -192,   181,   222,    24,   222,   187,    10,  -192,
    -192,   163,   164,   181,   168,   229,  -192,   176,  -192,   222,
      24,  -192,   182,  -192,    24,    10,   181,   183,  -192,  -192,
     222,   184,  -192,   181,  -192,   186,  -192
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     7,     1,     7,     0,     8,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,    18,     0,
       7,     6,     9,    31,    30,    10,    32,    24,    19,    23,
      38,    42,     0,    88,    89,    92,     0,     0,     0,     0,
       0,     0,    25,    74,    87,    58,    92,    21,    20,    60,
      56,     0,     0,     0,     0,     0,    14,    62,    63,     0,
       0,     0,     0,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,    90,     0,     0,     0,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       0,     0,     0,     7,    13,    11,    50,     0,    54,     0,
       0,     8,     2,    35,    39,     0,    37,     0,     0,     0,
       0,    41,    22,    95,     0,     0,     0,     0,     0,    86,
      79,    66,    67,    68,    69,    73,    72,    71,    70,    80,
      81,    82,    83,    84,    85,    59,    61,    57,     0,     0,
      28,     0,     0,    49,     0,     0,     0,     5,     0,     0,
       0,    52,     7,     0,    46,    93,    91,    77,    76,    75,
      64,     7,    29,     0,     7,    55,     0,     0,    36,    40,
       0,     0,     0,     7,     0,     7,     0,     0,     0,    12,
       0,    47,    53,     7,     0,     0,     8,    26,     7,    16,
      51,     0,     0,     7,     0,    44,    65,     0,    15,     0,
       0,    33,     0,    45,     0,     7,     7,     0,    34,    43,
       0,     0,    48,     7,    17,     0,    27
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,  -192,    -5,     0,  -192,  -192,  -192,  -192,
    -192,  -192,  -191,  -192,  -192,  -192,    47,   -59,    40,    -8,
    -110,    -9,   -38,   -52,  -192,  -192
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    20,     6,   170,   208,    54,    22,    23,
      24,    25,   204,    26,    27,    28,   119,   107,    48,    29,
     171,    50,    43,    44,    75,   124
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       7,    79,    42,    81,    49,    51,    21,    55,   108,    52,
      62,   117,    33,    34,   123,    64,    73,     1,     4,   217,
      30,   108,    74,   219,     5,    53,    35,    33,    34,    33,
      34,    80,    90,    91,    92,    93,    94,    95,   126,   127,
     128,    35,   174,    35,    31,    36,    37,    38,    63,    65,
     105,   167,   139,   140,   141,   142,   143,   144,   111,   116,
      39,   106,   118,    92,    93,    94,    95,    40,    66,    33,
      34,    45,   193,   131,   132,   133,   134,   135,   136,   137,
     138,    32,    41,    46,   203,    36,    37,    38,    49,    49,
      49,    67,   150,   151,   148,   175,    57,    58,   152,   216,
      39,    71,   108,    72,    76,    77,    78,    40,    96,    56,
     223,   157,    33,    34,   104,    73,    68,    47,   101,   100,
      97,    74,    41,    57,    58,    59,    35,   102,    36,    37,
      38,   109,   112,    69,   113,   187,   145,   146,   147,    70,
     172,   114,    60,    39,    33,    34,    45,   115,    61,   178,
      40,   120,   121,   125,   155,   122,   177,   182,    46,   149,
      36,    37,    38,   153,   156,    41,   186,   189,   154,   188,
     158,   161,   160,   159,   163,    39,   162,   164,   194,   176,
     196,   166,    40,   165,   179,   180,   205,   181,   202,    95,
     200,   183,   184,   209,   190,   185,   206,    41,   212,   117,
     191,   205,   195,   207,   201,   205,   197,     8,     9,   199,
     220,   221,    10,    11,   210,    12,   211,    13,   225,    14,
     213,    15,    16,    17,    18,     8,     9,   215,   192,     0,
      10,    11,     0,    12,   218,   222,   224,    14,   226,    15,
      16,    17,    18,     0,     0,     0,     0,    19,    82,    83,
      84,    85,    86,    87,    88,    89,    82,    83,    84,    85,
      86,    87,    88,    89,     0,    19,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,    98,    90,    91,    92,
      93,    94,    95,     0,   214,    82,    83,    84,    85,    86,
      87,    88,    89,   110,    82,    83,    84,    85,    86,    87,
      88,    89,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,   129,    90,    91,    92,    93,    94,    95,     0,
     173,     0,     0,     0,     0,     0,    99,    82,    83,    84,
      85,    86,    87,    88,    89,     0,   130,    90,    91,    92,
      93,    94,    95,    90,    91,    92,    93,    94,    95,     0,
       0,   103,     0,     0,     0,     0,   168,     0,     0,     0,
       0,     0,   169,    90,    91,    92,    93,    94,    95,    82,
      83,    84,    85,    86,    87,    88,    89,     0,     0,   198
};

static const yytype_int16 yycheck[] =
{
       5,    39,    11,    41,    12,    14,     6,    16,    60,     3,
      19,     3,     5,     6,    73,    20,    43,    12,     0,   210,
      19,    73,    49,   214,    14,    19,    19,     5,     6,     5,
       6,    40,    35,    36,    37,    38,    39,    40,    76,    77,
      78,    19,   152,    19,    19,    21,    22,    23,    14,    55,
      59,    54,    90,    91,    92,    93,    94,    95,    63,    68,
      36,    54,    54,    37,    38,    39,    40,    43,    55,     5,
       6,     7,   182,    82,    83,    84,    85,    86,    87,    88,
      89,    43,    58,    19,   194,    21,    22,    23,    96,    97,
      98,    55,   101,   102,    99,   154,    24,    25,   103,   209,
      36,    26,   154,    19,    43,    43,    43,    43,    55,    10,
     220,   111,     5,     6,     7,    43,    26,    53,    26,    19,
      55,    49,    58,    24,    25,    26,    19,    53,    21,    22,
      23,     5,    13,    43,    19,   173,    96,    97,    98,    49,
     149,    19,    43,    36,     5,     6,     7,    19,    49,   158,
      43,     5,     7,     5,    50,    54,   156,   162,    19,    26,
      21,    22,    23,    54,    56,    58,   171,   176,    55,   174,
      26,    19,    49,    26,    54,    36,    51,    50,   183,    26,
     185,    50,    43,    54,     7,     5,   195,    55,   193,    40,
     190,    51,    26,   198,    57,    14,   196,    58,   203,     3,
      50,   210,    51,    16,    26,   214,    52,     3,     4,    52,
     215,   216,     8,     9,    51,    11,    52,    13,   223,    15,
      52,    17,    18,    19,    20,     3,     4,    51,   181,    -1,
       8,     9,    -1,    11,    52,    52,    52,    15,    52,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    43,    27,    28,
      29,    30,    31,    32,    33,    34,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    43,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    55,    35,    36,    37,
      38,    39,    40,    -1,    55,    27,    28,    29,    30,    31,
      32,    33,    34,    54,    27,    28,    29,    30,    31,    32,
      33,    34,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    54,    35,    36,    37,    38,    39,    40,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    51,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    58,    35,    36,    37,
      38,    39,    40,    35,    36,    37,    38,    39,    40,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    54,    35,    36,    37,    38,    39,    40,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    51
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    60,    61,     0,    14,    63,    63,     3,     4,
       8,     9,    11,    13,    15,    17,    18,    19,    20,    43,
      62,    64,    67,    68,    69,    70,    72,    73,    74,    78,
      19,    19,    43,     5,     6,    19,    21,    22,    23,    36,
      43,    58,    80,    81,    82,     7,    19,    53,    77,    78,
      80,    80,     3,    19,    66,    80,    10,    24,    25,    26,
      43,    49,    80,    14,    63,    55,    55,    55,    26,    43,
      49,    26,    19,    43,    49,    83,    43,    43,    43,    81,
      80,    81,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    55,    55,    55,    51,
      19,    26,    53,    51,     7,    80,    54,    76,    82,     5,
      54,    63,    13,    19,    19,    19,    80,     3,    54,    75,
       5,     7,    54,    76,    84,     5,    81,    81,    81,    54,
      58,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    81,    81,    81,    81,    77,    77,    77,    63,    26,
      80,    80,    63,    54,    55,    50,    56,    64,    26,    26,
      49,    19,    51,    54,    50,    54,    50,    54,    54,    54,
      64,    79,    80,    53,    79,    76,    26,    64,    80,     7,
       5,    55,    63,    51,    26,    14,    63,    81,    63,    80,
      57,    50,    75,    79,    63,    51,    63,    52,    51,    52,
      64,    26,    63,    79,    71,    80,    64,    16,    65,    63,
      51,    52,    63,    52,    55,    51,    79,    71,    52,    71,
      63,    63,    52,    79,    52,    63,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    60,    61,    62,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    65,    65,    66,    66,
      67,    67,    67,    68,    68,    69,    69,    69,    69,    70,
      70,    70,    70,    71,    71,    72,    72,    72,    72,    73,
      73,    74,    75,    75,    76,    76,    77,    77,    77,    77,
      77,    77,    78,    78,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    82,    82,
      82,    82,    83,    83,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     3,     1,     4,     1,     0,     2,     1,
       1,     3,     6,     3,     2,     8,     7,    11,     1,     1,
       2,     2,     4,     1,     1,     2,     0,     6,     3,     4,
       1,     1,     1,     9,    10,     3,     5,     4,     2,     3,
       5,     4,     2,     3,     1,     9,     5,     6,    10,     4,
       3,     7,     2,     4,     1,     3,     1,     3,     1,     3,
       1,     3,     2,     2,     1,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     4,     4,     4,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       2,     4,     0,     3,     0,     1
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
#line 1271 "calc_elidian.y"
                             {eval(newast('z', NULL, NULL));}
#line 2612 "calc_elidian.tab.c"
    break;

  case 3: /* prog: inicio nl FINAL  */
#line 1272 "calc_elidian.y"
                      {eval(newast('z', NULL, NULL));}
#line 2618 "calc_elidian.tab.c"
    break;

  case 4: /* inicio: INICIO  */
#line 1274 "calc_elidian.y"
               {eval(newast('y', NULL, NULL));}
#line 2624 "calc_elidian.tab.c"
    break;

  case 5: /* cod: cod NEWLINHA nl exp  */
#line 1276 "calc_elidian.y"
                         {eval((yyvsp[0].a));}
#line 2630 "calc_elidian.tab.c"
    break;

  case 6: /* cod: exp  */
#line 1277 "calc_elidian.y"
          {eval((yyvsp[0].a));}
#line 2636 "calc_elidian.tab.c"
    break;

  case 7: /* nl: %empty  */
#line 1279 "calc_elidian.y"
    {(yyval.a) = NULL;}
#line 2642 "calc_elidian.tab.c"
    break;

  case 8: /* nl: NEWLINHA nl  */
#line 1280 "calc_elidian.y"
                  {(yyval.a) = NULL;}
#line 2648 "calc_elidian.tab.c"
    break;

  case 9: /* exp: decl  */
#line 1282 "calc_elidian.y"
          {(yyval.a) = (yyvsp[0].a);}
#line 2654 "calc_elidian.tab.c"
    break;

  case 10: /* exp: declvartexto  */
#line 1283 "calc_elidian.y"
                   {(yyval.a) = (yyvsp[0].a);}
#line 2660 "calc_elidian.tab.c"
    break;

  case 11: /* exp: VAR '=' logica  */
#line 1287 "calc_elidian.y"
                                {(yyval.a) = newasgn((yyvsp[-2].texto), 0, (yyvsp[0].a));}
#line 2666 "calc_elidian.tab.c"
    break;

  case 12: /* exp: VAR '[' INTEIRO ']' '=' logica  */
#line 1288 "calc_elidian.y"
                                                {(yyval.a) = newasgn((yyvsp[-5].texto), (yyvsp[-3].inteiro), (yyvsp[0].a));}
#line 2672 "calc_elidian.tab.c"
    break;

  case 13: /* exp: VAR '=' TEXTO  */
#line 1289 "calc_elidian.y"
                    {(yyval.a) = newasgn((yyvsp[-2].texto), 0, newtexto((yyvsp[0].texto)));}
#line 2678 "calc_elidian.tab.c"
    break;

  case 14: /* exp: VAR ENTRADA  */
#line 1291 "calc_elidian.y"
                  {(yyval.a) = newast('c', newValorVal((yyvsp[-1].texto), 0), NULL);}
#line 2684 "calc_elidian.tab.c"
    break;

  case 15: /* exp: IF logica '{' nl list nl '}' else  */
#line 1292 "calc_elidian.y"
                                        {(yyval.a) = newflow('I', (yyvsp[-6].a), (yyvsp[-3].a), (yyvsp[0].a));}
#line 2690 "calc_elidian.tab.c"
    break;

  case 16: /* exp: WHILE logica '{' nl list nl '}'  */
#line 1294 "calc_elidian.y"
                                          {(yyval.a) = newflow('W', (yyvsp[-5].a), (yyvsp[-3].a), NULL);}
#line 2696 "calc_elidian.tab.c"
    break;

  case 17: /* exp: FOR atrib ';' logica ';' arit '{' nl list nl '}'  */
#line 1295 "calc_elidian.y"
                                                       {(yyval.a) = newflowfor('F', (yyvsp[-9].a), (yyvsp[-7].a), (yyvsp[-5].a), (yyvsp[-2].a), NULL);}
#line 2702 "calc_elidian.tab.c"
    break;

  case 18: /* exp: COMENTARIO  */
#line 1296 "calc_elidian.y"
                 {(yyval.a) = newast('P', NULL, newtexto((yyvsp[0].texto)));}
#line 2708 "calc_elidian.tab.c"
    break;

  case 19: /* exp: iterator  */
#line 1298 "calc_elidian.y"
               {(yyval.a) = (yyvsp[0].a);}
#line 2714 "calc_elidian.tab.c"
    break;

  case 20: /* exp: SAIDA saida  */
#line 1299 "calc_elidian.y"
                            {(yyval.a) = (yyvsp[0].a);}
#line 2720 "calc_elidian.tab.c"
    break;

  case 21: /* exp: SAIDA ';'  */
#line 1301 "calc_elidian.y"
                {(yyval.a) = newast('P', NULL, NULL);}
#line 2726 "calc_elidian.tab.c"
    break;

  case 22: /* exp: TYPE '(' VAR ')'  */
#line 1302 "calc_elidian.y"
                       {(yyval.a) = newast('T', newtexto((yyvsp[-1].texto)), NULL);}
#line 2732 "calc_elidian.tab.c"
    break;

  case 23: /* exp: incdec  */
#line 1303 "calc_elidian.y"
             {(yyval.a) = (yyvsp[0].a);}
#line 2738 "calc_elidian.tab.c"
    break;

  case 24: /* exp: outfunc  */
#line 1304 "calc_elidian.y"
              {(yyval.a) = (yyvsp[0].a);}
#line 2744 "calc_elidian.tab.c"
    break;

  case 25: /* exp: RETURN logica  */
#line 1305 "calc_elidian.y"
                    {(yyval.a) = newast('j', (yyvsp[0].a), NULL);}
#line 2750 "calc_elidian.tab.c"
    break;

  case 26: /* else: %empty  */
#line 1308 "calc_elidian.y"
      {(yyval.a) = NULL;}
#line 2756 "calc_elidian.tab.c"
    break;

  case 27: /* else: ELSE '{' nl list nl '}'  */
#line 1309 "calc_elidian.y"
                              {(yyval.a) = (yyvsp[-2].a);}
#line 2762 "calc_elidian.tab.c"
    break;

  case 28: /* atrib: VAR '=' logica  */
#line 1314 "calc_elidian.y"
                      {(yyval.a) = newasgn((yyvsp[-2].texto), 0, (yyvsp[0].a));}
#line 2768 "calc_elidian.tab.c"
    break;

  case 29: /* atrib: TIPO VAR '=' logica  */
#line 1315 "calc_elidian.y"
                          {(yyval.a) = newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), (yyvsp[0].a), NULL);}
#line 2774 "calc_elidian.tab.c"
    break;

  case 30: /* decl: declvar  */
#line 1317 "calc_elidian.y"
              {(yyval.a) = (yyvsp[0].a);}
#line 2780 "calc_elidian.tab.c"
    break;

  case 31: /* decl: declfunction  */
#line 1318 "calc_elidian.y"
                   {(yyval.a) = (yyvsp[0].a);}
#line 2786 "calc_elidian.tab.c"
    break;

  case 32: /* decl: declvecmult  */
#line 1319 "calc_elidian.y"
                  {(yyval.a) = (yyvsp[0].a);}
#line 2792 "calc_elidian.tab.c"
    break;

  case 33: /* declfunction: TIPO VAR '(' ')' '{' nl list nl '}'  */
#line 1322 "calc_elidian.y"
                                                  {(yyval.a) = newfunction((yyvsp[-8].inteiro), (yyvsp[-7].texto), NULL, (yyvsp[-2].a));}
#line 2798 "calc_elidian.tab.c"
    break;

  case 34: /* declfunction: TIPO VAR '(' args ')' '{' nl list nl '}'  */
#line 1323 "calc_elidian.y"
                                               {(yyval.a) = newfunction((yyvsp[-9].inteiro), (yyvsp[-8].texto), (yyvsp[-6].a), (yyvsp[-2].a));}
#line 2804 "calc_elidian.tab.c"
    break;

  case 35: /* declvar: declvar ',' VAR  */
#line 1325 "calc_elidian.y"
                         {(yyval.a) = newvar((yyvsp[-2].a)->nodetype, (yyvsp[0].texto), NULL, (yyvsp[-2].a));}
#line 2810 "calc_elidian.tab.c"
    break;

  case 36: /* declvar: declvar ',' VAR '=' logica  */
#line 1326 "calc_elidian.y"
                                 {(yyval.a) = newvar((yyvsp[-4].a)->nodetype, (yyvsp[-2].texto), (yyvsp[0].a), (yyvsp[-4].a));}
#line 2816 "calc_elidian.tab.c"
    break;

  case 37: /* declvar: TIPO VAR '=' logica  */
#line 1327 "calc_elidian.y"
                                      {(yyval.a) = newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), (yyvsp[0].a), NULL);}
#line 2822 "calc_elidian.tab.c"
    break;

  case 38: /* declvar: TIPO VAR  */
#line 1328 "calc_elidian.y"
                           {(yyval.a) = newvar((yyvsp[-1].inteiro), (yyvsp[0].texto), NULL, NULL);}
#line 2828 "calc_elidian.tab.c"
    break;

  case 39: /* declvartexto: declvartexto ',' VAR  */
#line 1330 "calc_elidian.y"
                                   {(yyval.a) = newvar((yyvsp[-2].a)->nodetype, (yyvsp[0].texto), NULL, (yyvsp[-2].a));}
#line 2834 "calc_elidian.tab.c"
    break;

  case 40: /* declvartexto: declvartexto ',' VAR '=' TEXTO  */
#line 1331 "calc_elidian.y"
                                     {(yyval.a) = newvar((yyvsp[-4].a)->nodetype, (yyvsp[-2].texto), newtexto((yyvsp[0].texto)), (yyvsp[-4].a));}
#line 2840 "calc_elidian.tab.c"
    break;

  case 41: /* declvartexto: TIPO_TEXTO VAR '=' TEXTO  */
#line 1332 "calc_elidian.y"
                               {(yyval.a) = newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), newtexto((yyvsp[0].texto)), NULL);}
#line 2846 "calc_elidian.tab.c"
    break;

  case 42: /* declvartexto: TIPO_TEXTO VAR  */
#line 1333 "calc_elidian.y"
                     {(yyval.a) = newvar((yyvsp[-1].inteiro), (yyvsp[0].texto), NULL, NULL);}
#line 2852 "calc_elidian.tab.c"
    break;

  case 43: /* valorvec: logica ',' valorvec  */
#line 1340 "calc_elidian.y"
                              {(yyval.a) = newast('l', (yyvsp[-2].a), (yyvsp[0].a));}
#line 2858 "calc_elidian.tab.c"
    break;

  case 44: /* valorvec: logica  */
#line 1341 "calc_elidian.y"
             {(yyval.a) = newast('l', (yyvsp[0].a), NULL);}
#line 2864 "calc_elidian.tab.c"
    break;

  case 45: /* declvecmult: TIPO VAR '[' INTEIRO ']' '=' '{' valorvec '}'  */
#line 1343 "calc_elidian.y"
                                                           {(yyval.a) = newvec((yyvsp[-8].inteiro), (yyvsp[-7].texto), (yyvsp[-5].inteiro), (yyvsp[-1].a), NULL);}
#line 2870 "calc_elidian.tab.c"
    break;

  case 46: /* declvecmult: TIPO VAR '[' INTEIRO ']'  */
#line 1344 "calc_elidian.y"
                               {(yyval.a) = newvec((yyvsp[-4].inteiro), (yyvsp[-3].texto), (yyvsp[-1].inteiro), NULL, NULL);}
#line 2876 "calc_elidian.tab.c"
    break;

  case 47: /* declvecmult: declvecmult ',' VAR '[' INTEIRO ']'  */
#line 1345 "calc_elidian.y"
                                          {(yyval.a) = newvec((yyvsp[-5].a)->nodetype, (yyvsp[-3].texto), (yyvsp[-1].inteiro), NULL, (yyvsp[-5].a));}
#line 2882 "calc_elidian.tab.c"
    break;

  case 48: /* declvecmult: declvecmult ',' VAR '[' INTEIRO ']' '=' '{' valorvec '}'  */
#line 1346 "calc_elidian.y"
                                                               {(yyval.a) = newvec((yyvsp[-9].a)->nodetype, (yyvsp[-7].texto), (yyvsp[-5].inteiro), (yyvsp[-1].a), (yyvsp[-9].a));}
#line 2888 "calc_elidian.tab.c"
    break;

  case 49: /* outfunc: VAR '(' arg ')'  */
#line 1352 "calc_elidian.y"
                                   {(yyval.a) = newast('a', newtexto((yyvsp[-3].texto)), (yyvsp[-1].a));}
#line 2894 "calc_elidian.tab.c"
    break;

  case 50: /* outfunc: VAR '(' ')'  */
#line 1353 "calc_elidian.y"
                             {(yyval.a) = newast('a', newtexto((yyvsp[-2].texto)), NULL);}
#line 2900 "calc_elidian.tab.c"
    break;

  case 51: /* iterator: '(' logica ')' '?' exp ':' exp  */
#line 1355 "calc_elidian.y"
                                                        {(yyval.a) = newflow('?', (yyvsp[-5].a), (yyvsp[-2].a), (yyvsp[0].a));}
#line 2906 "calc_elidian.tab.c"
    break;

  case 52: /* args: TIPO VAR  */
#line 1358 "calc_elidian.y"
               {(yyval.a) = newast('l', newvar((yyvsp[-1].inteiro), (yyvsp[0].texto), NULL, NULL), NULL);}
#line 2912 "calc_elidian.tab.c"
    break;

  case 53: /* args: TIPO VAR ',' args  */
#line 1359 "calc_elidian.y"
                        {(yyval.a) = newast('l', newvar((yyvsp[-3].inteiro), (yyvsp[-2].texto), NULL, NULL), (yyvsp[0].a));}
#line 2918 "calc_elidian.tab.c"
    break;

  case 54: /* arg: valor  */
#line 1361 "calc_elidian.y"
           {(yyval.a) = newast('l', (yyvsp[0].a), NULL);}
#line 2924 "calc_elidian.tab.c"
    break;

  case 55: /* arg: valor ',' arg  */
#line 1362 "calc_elidian.y"
                    {(yyval.a) = newast('l', (yyvsp[-2].a), (yyvsp[0].a));}
#line 2930 "calc_elidian.tab.c"
    break;

  case 56: /* saida: logica  */
#line 1367 "calc_elidian.y"
              {(yyval.a) = newast('P', (yyvsp[0].a), NULL);}
#line 2936 "calc_elidian.tab.c"
    break;

  case 57: /* saida: logica ',' saida  */
#line 1368 "calc_elidian.y"
                       { (yyval.a) = newast('P', (yyvsp[-2].a), (yyvsp[0].a));}
#line 2942 "calc_elidian.tab.c"
    break;

  case 58: /* saida: TEXTO  */
#line 1369 "calc_elidian.y"
            {(yyval.a) = newast('P', newtexto((yyvsp[0].texto)), NULL);}
#line 2948 "calc_elidian.tab.c"
    break;

  case 59: /* saida: TEXTO ',' saida  */
#line 1370 "calc_elidian.y"
                      {(yyval.a) = newast('P', newtexto((yyvsp[-2].texto)), (yyvsp[0].a));}
#line 2954 "calc_elidian.tab.c"
    break;

  case 60: /* saida: incdec  */
#line 1371 "calc_elidian.y"
             {(yyval.a) = newast('P', (yyvsp[0].a), NULL);}
#line 2960 "calc_elidian.tab.c"
    break;

  case 61: /* saida: incdec ',' saida  */
#line 1372 "calc_elidian.y"
                       { (yyval.a) = newast('P', (yyvsp[-2].a), (yyvsp[0].a));}
#line 2966 "calc_elidian.tab.c"
    break;

  case 62: /* incdec: VAR PLUS  */
#line 1375 "calc_elidian.y"
                             {(yyval.a) = newasgn((yyvsp[-1].texto), 0, newast('+',newValorVal((yyvsp[-1].texto), 0),newint(1)));}
#line 2972 "calc_elidian.tab.c"
    break;

  case 63: /* incdec: VAR LESS  */
#line 1376 "calc_elidian.y"
                           {(yyval.a) = newasgn((yyvsp[-1].texto), 0, newast('-',newValorVal((yyvsp[-1].texto), 0),newint(1)));}
#line 2978 "calc_elidian.tab.c"
    break;

  case 64: /* list: exp  */
#line 1380 "calc_elidian.y"
          {(yyval.a) = (yyvsp[0].a);}
#line 2984 "calc_elidian.tab.c"
    break;

  case 65: /* list: list NEWLINHA nl exp  */
#line 1381 "calc_elidian.y"
                           { (yyval.a) = newast('L', (yyvsp[-3].a), (yyvsp[0].a));}
#line 2990 "calc_elidian.tab.c"
    break;

  case 66: /* logica: logica OR logica  */
#line 1383 "calc_elidian.y"
                         {(yyval.a) = newcmp(7,(yyvsp[-2].a),(yyvsp[0].a));}
#line 2996 "calc_elidian.tab.c"
    break;

  case 67: /* logica: logica AND logica  */
#line 1384 "calc_elidian.y"
                        {(yyval.a) = newcmp(8,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3002 "calc_elidian.tab.c"
    break;

  case 68: /* logica: logica MAIOR logica  */
#line 1385 "calc_elidian.y"
                          {(yyval.a) = newcmp(1,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3008 "calc_elidian.tab.c"
    break;

  case 69: /* logica: logica MENOR logica  */
#line 1386 "calc_elidian.y"
                          {(yyval.a) = newcmp(2,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3014 "calc_elidian.tab.c"
    break;

  case 70: /* logica: logica DIF logica  */
#line 1387 "calc_elidian.y"
                        {(yyval.a) = newcmp(3,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3020 "calc_elidian.tab.c"
    break;

  case 71: /* logica: logica II logica  */
#line 1388 "calc_elidian.y"
                       {(yyval.a) = newcmp(4,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3026 "calc_elidian.tab.c"
    break;

  case 72: /* logica: logica MAI logica  */
#line 1389 "calc_elidian.y"
                        {(yyval.a) = newcmp(5,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3032 "calc_elidian.tab.c"
    break;

  case 73: /* logica: logica MEI logica  */
#line 1390 "calc_elidian.y"
                        {(yyval.a) = newcmp(6,(yyvsp[-2].a),(yyvsp[0].a));}
#line 3038 "calc_elidian.tab.c"
    break;

  case 74: /* logica: arit  */
#line 1391 "calc_elidian.y"
           {(yyval.a) = (yyvsp[0].a);}
#line 3044 "calc_elidian.tab.c"
    break;

  case 75: /* arit: SIN '(' arit ')'  */
#line 1393 "calc_elidian.y"
                       {(yyval.a) = newast('S',(yyvsp[-1].a),NULL);}
#line 3050 "calc_elidian.tab.c"
    break;

  case 76: /* arit: COS '(' arit ')'  */
#line 1394 "calc_elidian.y"
                       {(yyval.a) = newast('C',(yyvsp[-1].a),NULL);}
#line 3056 "calc_elidian.tab.c"
    break;

  case 77: /* arit: RAIZ '(' arit ')'  */
#line 1395 "calc_elidian.y"
                        {(yyval.a) = newast('R',(yyvsp[-1].a),NULL);}
#line 3062 "calc_elidian.tab.c"
    break;

  case 78: /* arit: '-' arit  */
#line 1396 "calc_elidian.y"
                         {(yyval.a) = newast('M', (yyvsp[0].a), NULL);}
#line 3068 "calc_elidian.tab.c"
    break;

  case 79: /* arit: '|' arit '|'  */
#line 1397 "calc_elidian.y"
                   {(yyval.a) = newast('A',(yyvsp[-1].a),NULL);}
#line 3074 "calc_elidian.tab.c"
    break;

  case 80: /* arit: arit '+' arit  */
#line 1398 "calc_elidian.y"
                    {(yyval.a) = newast('+',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3080 "calc_elidian.tab.c"
    break;

  case 81: /* arit: arit '-' arit  */
#line 1399 "calc_elidian.y"
                    {(yyval.a) = newast('-',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3086 "calc_elidian.tab.c"
    break;

  case 82: /* arit: arit '*' arit  */
#line 1400 "calc_elidian.y"
                    {(yyval.a) = newast('*',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3092 "calc_elidian.tab.c"
    break;

  case 83: /* arit: arit '/' arit  */
#line 1401 "calc_elidian.y"
                    {(yyval.a) = newast('/',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3098 "calc_elidian.tab.c"
    break;

  case 84: /* arit: arit '%' arit  */
#line 1402 "calc_elidian.y"
                    {(yyval.a) = newast('%',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3104 "calc_elidian.tab.c"
    break;

  case 85: /* arit: arit '^' arit  */
#line 1403 "calc_elidian.y"
                    {(yyval.a) = newast('^',(yyvsp[-2].a),(yyvsp[0].a));}
#line 3110 "calc_elidian.tab.c"
    break;

  case 86: /* arit: '(' logica ')'  */
#line 1404 "calc_elidian.y"
                     {(yyval.a) = (yyvsp[-1].a);}
#line 3116 "calc_elidian.tab.c"
    break;

  case 87: /* arit: valor  */
#line 1405 "calc_elidian.y"
            {(yyval.a) = (yyvsp[0].a);}
#line 3122 "calc_elidian.tab.c"
    break;

  case 88: /* valor: INTEIRO  */
#line 1408 "calc_elidian.y"
               {(yyval.a) = newint((yyvsp[0].inteiro));}
#line 3128 "calc_elidian.tab.c"
    break;

  case 89: /* valor: REAL  */
#line 1409 "calc_elidian.y"
           {(yyval.a) = newreal((yyvsp[0].real));}
#line 3134 "calc_elidian.tab.c"
    break;

  case 90: /* valor: VAR varvar  */
#line 1417 "calc_elidian.y"
                 {
        if((yyvsp[0].a)==NULL) (yyval.a) = newValorVal((yyvsp[-1].texto), 0);
        else (yyval.a) = newast('a', newtexto((yyvsp[-1].texto)), (yyvsp[0].a)->r);
    }
#line 3143 "calc_elidian.tab.c"
    break;

  case 91: /* valor: VAR '[' INTEIRO ']'  */
#line 1421 "calc_elidian.y"
                          {(yyval.a) = newValorVal((yyvsp[-3].texto), (yyvsp[-1].inteiro));}
#line 3149 "calc_elidian.tab.c"
    break;

  case 92: /* varvar: %empty  */
#line 1423 "calc_elidian.y"
        {(yyval.a) = NULL;}
#line 3155 "calc_elidian.tab.c"
    break;

  case 93: /* varvar: '(' varfun ')'  */
#line 1424 "calc_elidian.y"
                     {
        if ((yyvsp[-1].a)!=NULL) (yyval.a) = newast('j', NULL, (yyvsp[-1].a)->r);
        else (yyval.a) = newast('j', NULL, NULL);
    }
#line 3164 "calc_elidian.tab.c"
    break;

  case 94: /* varfun: %empty  */
#line 1430 "calc_elidian.y"
        {(yyval.a) = NULL;}
#line 3170 "calc_elidian.tab.c"
    break;

  case 95: /* varfun: arg  */
#line 1431 "calc_elidian.y"
          {(yyval.a) = newast('j', NULL, (yyvsp[0].a));}
#line 3176 "calc_elidian.tab.c"
    break;


#line 3180 "calc_elidian.tab.c"

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

#line 1433 "calc_elidian.y"


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
