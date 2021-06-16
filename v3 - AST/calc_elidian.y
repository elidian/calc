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

    #define name_size 30
    #define string_size 1000
    #define PI 3.14159265

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

    Ast * newTamVal(char s[]) { /*Função que recupera o nome/referência de uma variável, neste caso o número*/    
        Varval *a = (Varval*) malloc(sizeof(Varval));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 'h';
        strcpy(a->var, s);
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
    double vfinal = 0;
    bool testfunc = false;
    int typefunc = 0;

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
            case 'S': v = sin(eval(a->l)*PI/180); break;				/*Operações SIN*/
            case 'C': v = cos(eval(a->l)*PI/180); break;				/*Operações COS*/
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
            case 'L': 
                if(a->l && !testfunc){
                    v = eval(a->l);
                    if(a->r && !testfunc){ 
                        v = eval(a->r); /*Lista de operções em um bloco IF/ELSE/WHILE. Assim o analisador não se perde entre os blocos*/
                        if(a->r->nodetype=='j' && !testfunc && typefunc!='v'){
                            //vfinal = v;
                            testfunc = true;
                        }
                    }
                }
                break;
            case 'l': if(a->l) v = eval(a->l); if(a->r) eval(a->r); break;
            case 'j': 
                if(typefunc!='v'){ 
                    v = eval(a->l);
                    vfinal = v;
                }
                break;
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
                    printf("%f", v);
                }
                    //printf("P5\n");
                    if(!a->r)
                        printf("\n");
                    else{
                        eval(a->r);
                    }
                    //printf("P7\n");
                    break;  /*Função que imprime um valor*/
            
            case 'h':;
                //printf("case h\n");
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
                    //int p = eval(((Varval*)a)->pos);
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
                                            v = auxvt->tam;
                                            break;
                                        }
                                    } else {
                                        v = auxvi->tam;
                                        break;
                                    }
                                } else {
                                    v = auxvr->tam;
                                    break;
                                }
                            } else {
                                v = 1;
                                break;
                            }
                        } else {
                            v = 1;
                            break;
                        }
                    }
                    else{
                        v = 1;
                        break;
                    }
                    auxl = auxl->prox;
                }
                break;

            case 'V':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(lista, ((Symasgn *)a)->s)){
                    Ast *auxv = ((Symasgn *)a)->v;
                    int posv = 0;
                    int y = eval(((Symasgn *)a)->tam);
                    //printf("type: %c\n", ((Symasgn *)a)->type);
                    //printf("node: %c\n", auxv->nodetype);
                    if(auxv){
                        if(auxv->nodetype=='N'){
                            int tam = eval(newTamVal(((Varval*)auxv)->var));
                            switch(((Symasgn *)a)->type){
                                case 'r':;
                                    lista->rvec = insvecr(lista->rvec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                    if (auxv){
                                        for(posv = 0; posv < lista->rvec->tam && auxv!=NULL; posv++){
                                            if (posv < tam)
                                                lista->rvec->v[posv] = eval(newValorVal(((Varval*)auxv)->var, newint(posv))); /*Atribui à variável*/
                                            else lista->rvec->v[posv] = 0;
                                        }
                                    } else 
                                        for(posv = 0; posv < lista->rvec->tam && auxv!=NULL; posv++){
                                            lista->rvec->v[posv] = 0;
                                        }
                                    break;
                                case 'i':;
                                    lista->ivec = insveci(lista->ivec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                    if (auxv){
                                        for(posv = 0; posv < lista->ivec->tam ; posv++){
                                            if (posv < tam)
                                                lista->ivec->v[posv] = eval(newValorVal(((Varval*)auxv)->var, newint(posv))); /*Atribui à variável*/
                                            else lista->ivec->v[posv] = 0;
                                        }
                                    } else 
                                        for(posv = 0; posv < lista->ivec->tam ; posv++){
                                            lista->ivec->v[posv] = 0;
                                        }
                                    break;
                                case 't':;
                                    lista->tvec = insvect(lista->tvec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                    if (auxv){
                                        for(posv = 0; posv < lista->tvec->tam ; posv++){
                                            if (posv < tam)
                                                lista->tvec->v[posv] = evalt(newValorVal(((Varval*)auxv)->var, newint(posv))); /*Atribui à variável*/
                                            else
                                                lista->tvec->v[posv] = evalt(newtexto(""));
                                        }
                                    } else 
                                        for(posv = 0; posv < lista->tvec->tam ; posv++)
                                            lista->tvec->v[posv] = evalt(newtexto(""));
                                    break;
                                default:;
                                    printf("\nErro (case 'V'): sem case\n");
                                    break;
                            }
                        }
                        else {
                            switch(((Symasgn *)a)->type){
                                case 'r':;
                                    lista->rvec = insvecr(lista->rvec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                    if (auxv){
                                        for(posv = 0; posv < lista->rvec->tam && auxv!=NULL; posv++, auxv = auxv->r){
                                            lista->rvec->v[posv] = eval(auxv->l); /*Atribui à variável*/
                                        }
                                    } else
                                        for(posv = 0; posv < lista->rvec->tam; posv++){
                                            lista->rvec->v[posv] = 0; /*Atribui à variável*/
                                        }
                                    break;
                                case 'i':;
                                    lista->ivec = insveci(lista->ivec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                    if (auxv){
                                        for(posv = 0; posv < lista->ivec->tam && auxv!=NULL; posv++, auxv = auxv->r){
                                            lista->ivec->v[posv] = eval(auxv->l); /*Atribui à variável*/
                                        }
                                    } else
                                        for(posv = 0; posv < lista->ivec->tam; posv++){
                                            lista->ivec->v[posv] = 0; /*Atribui à variável*/
                                        }
                                    break;
                                case 't':;
                                    lista->tvec = insvect(lista->tvec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                    if (auxv){
                                        for(posv = 0; posv < lista->tvec->tam ; posv++){
                                            if(auxv){
                                                lista->tvec->v[posv] = evalt(auxv->l); /*Atribui à variável*/
                                                auxv = auxv->r;
                                            }else{
                                                lista->tvec->v[posv] = evalt(newtexto(""));
                                            }
                                        }
                                    } else 
                                        for(posv = 0; posv < lista->tvec->tam ; posv++)
                                            lista->tvec->v[posv] = evalt(newtexto(""));
                                    break;
                                default:;
                                    printf("\nErro (case 'V'): sem case\n");
                                    break;
                            }
                        }
                    } else {
                        switch(((Symasgn *)a)->type){
                            case 'r':;
                                lista->rvec = insvecr(lista->rvec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                break;
                            case 'i':;
                                lista->ivec = insveci(lista->ivec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                break;
                            case 't':;
                                lista->tvec = insvect(lista->tvec, ((Symasgn *)a)->type, ((Symasgn *)a)->s, y);
                                for(posv = 0; posv < lista->tvec->tam ; posv++)
                                    lista->tvec->v[posv] = evalt(newtexto(""));
                                break;
                            default:;
                                printf("\nErro (case 'V'): sem case\n");
                                break;
                        }
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
                        
                        vfinal = 0;
                        testfunc = false;
                        typefunc = auxf->nodetype;
                        if(auxf->v)
                            v = eval(auxf->v);
                        
                        if(vfinal !=0)
                            if(auxf->nodetype=='i')
                                v = (int) vfinal;
                            else v = vfinal;
                        else v = 0;

                        testfunc = false;
                        typefunc = 0;
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

%}

%union{
    char texto[50];
    char stexto[1000];
    int inteiro;
    double real;
    Ast *a;
}

//DECLARAÇÃO DE TOKENS
%token <inteiro> TIPO TIPO_TEXTO
%token <inteiro> INTEIRO
%token <real> REAL
%token <stexto> TEXTO
%token <texto> TYPE RETURN
%token <texto> ENTRADA
%token <texto> SAIDA
%token <texto> INICIO
%token <texto> FINAL
%token <texto> NEWLINHA
%token <texto> IF ELSE FOR WHILE
%token <texto> VAR PASS
//TOKENS DE ARITMETICA
%token <texto> RAIZ COS SIN
//TOKENS DE LOGICA
//%token MAIOR MENOR MEI MAI II DIF OR AND
%token <texto> PLUS LESS

//DECLARAÇÃO DE TIPO DE NÃO-TERMINAIS
%type <a> declvartexto
%type <a> exp declvar atrib list saida incdec args arg //valorvec declvecmult
%type <a> logica
%type <a> arit
%type <a> valor decl declfunction outfunc
%type <a> operadorternario inicio varvar varfun
%type <a> nl else valorvec valorvectexto

//DECLARAÇÃO DE PRECEDÊNCIA
%right '='
%left OR AND
%left MAIOR MENOR MEI MAI II DIF
%left '+' '-'
%left '*' '/' '%'
%right '^'
%right PLUS2 LESS2
%left ')'
%right '('

%nonassoc FUN POT NEG
%nonassoc VARP
%start prog
%%

prog: inicio nl cod nl FINAL {eval(newast('z', NULL, NULL));}
    | inicio nl FINAL {eval(newast('z', NULL, NULL));}
    ;
inicio: INICIO {eval(newast('y', NULL, NULL));}
    ;
cod: cod NEWLINHA nl exp {eval($4);}
    | exp {eval($1);}
    ;
nl: {$$ = NULL;}
    | NEWLINHA nl {$$ = NULL;}
    ;
exp: decl {$$ = $1;}
    | VAR '=' logica %prec VARP {$$ = newasgn($1, newint(0), $3);}
    | VAR '[' arit ']' '=' logica %prec VARP {$$ = newasgn($1, $3, $6);}
    | VAR '=' TEXTO {$$ = newasgn($1, newint(0), newtexto($3));} 
    | VAR '[' arit ']' '=' TEXTO {$$ = newasgn($1, $3, newtexto($6));} 
    | VAR ENTRADA {$$ = newast('c', newValorVal($1, newint(0)), NULL);}
    | VAR '[' arit ']' ENTRADA {$$ = newast('c', newValorVal($1, $3), NULL);}
    | IF logica nl '{' nl list nl '}' else {$$ = newflow('I', $2, $6, $9);}
	| WHILE logica nl '{' nl list nl '}' {$$ = newflow('W', $2, $6, NULL);}
    | FOR atrib ';' logica ';' arit '{' nl list nl '}' {$$ = newflowfor('F', $2, $4, $6, $9, NULL);}
    | operadorternario {$$ = $1;}
    | SAIDA saida %prec FUN {$$ = $2;}
    | SAIDA ';' {$$ = newast('P', NULL, NULL);} 
    | TYPE '(' VAR ')' {$$ = newast('T', newtexto($3), NULL);}
    | incdec {$$ = $1;}
    | outfunc {$$ = $1;}
    | RETURN logica {$$ = newast('j', $2, NULL);}
    | PASS {$$ = newast('l', NULL, NULL);}
    ;
else: {$$ = NULL;}
    | ELSE nl '{' nl list nl '}' {$$ = $5;}
    ;
atrib: VAR '=' logica {$$ = newasgn($1, newint(0), $3);}
    | TIPO VAR '=' logica {$$ = newvar($1, $2, $4, NULL);}
    ;
decl: declvar {$$ = $1;}
    | declvartexto {$$ = $1;}
    //| declvectexto {$$ = $1;}
    | declfunction {$$ = $1;}
    //| declvecmult {$$ = $1;}
    ;
declfunction: 
    TIPO VAR '(' ')' nl '{' nl list nl '}' %prec FUN {$$ = newfunction($1, $2, NULL, $8);}
    | TIPO VAR '(' args ')' nl '{' nl list nl '}' {$$ = newfunction($1, $2, $4, $9);}
    ;
declvar: TIPO VAR '=' logica {$$ = newvar($1, $2, $4, NULL);}
    | TIPO VAR {$$ = newvar($1, $2, NULL, NULL);}
    | TIPO VAR '[' arit ']' '=' '{' valorvec '}' {$$ = newvec($1, $2, $4, $8, NULL);}
    | TIPO VAR '[' arit ']' '=' VAR {$$ = newvec($1, $2, $4, newValorVal($7, 0), NULL);}
    | TIPO VAR '[' arit ']' {$$ = newvec($1, $2, $4, NULL, NULL);}
    | declvar ',' VAR {
        if ($1->nodetype=='V') $$ = newvar(((Symasgn*)$1)->type, $3, NULL, $1);
        else $$ = newvar($1->nodetype, $3, NULL, $1);
    }
    | declvar ',' VAR '=' logica {
        if ($1->nodetype=='V') $$ = newvar(((Symasgn*)$1)->type, $3, $5, $1);
        else $$ = newvar($1->nodetype, $3, $5, $1);
    }
    | declvar ',' VAR '[' arit ']' {
        if ($1->nodetype=='V') $$ = newvec(((Symasgn*)$1)->type, $3, $5, NULL, $1);
        else $$ = newvec($1->nodetype, $3, $5, NULL, $1);
    }
    | declvar ',' VAR '[' arit ']' '=' '{' valorvec '}' {
        if ($1->nodetype=='V') $$ = newvec(((Symasgn*)$1)->type, $3, $5, $9, $1);
        else $$ = newvec($1->nodetype, $3, $5, $9, $1);
    }
    | declvar ',' VAR '[' arit ']' '=' VAR {
        if ($1->nodetype=='V') $$ = newvec(((Symasgn*)$1)->type, $3, $5, newValorVal($8, 0), $1);
        else $$ = newvec($1->nodetype, $3, $5, newValorVal($8, 0), $1);
    }
    ;
declvartexto: declvartexto ',' VAR {
        if ($1->nodetype=='V') $$ = newvar(((Symasgn*)$1)->type, $3, NULL, $1);
        else $$ = newvar($1->nodetype, $3, NULL, $1);
    }
    | declvartexto ',' VAR '=' TEXTO {
        if ($1->nodetype=='V') $$ = newvar(((Symasgn*)$1)->type, $3, newtexto($5), $1);
        else $$ = newvar($1->nodetype, $3, newtexto($5), $1);
    }
    | declvartexto ',' VAR '=' VAR {
        if ($1->nodetype=='V') $$ = newvar(((Symasgn*)$1)->type, $3, newValorVal($5, newint(0)), $1);
        else $$ = newvar($1->nodetype, $3, newValorVal($5, newint(0)), $1);
    }
    | TIPO_TEXTO VAR '=' TEXTO {$$ = newvar($1, $2, newtexto($4), NULL);}
    | TIPO_TEXTO VAR '=' VAR {$$ = newvar($1, $2, newValorVal($4, newint(0)), NULL);}
    | TIPO_TEXTO VAR {$$ = newvar($1, $2, NULL, NULL);}
    | TIPO_TEXTO VAR '[' arit ']' '=' '{' valorvectexto '}' {$$ = newvec($1, $2, $4, $8, NULL);}
    | TIPO_TEXTO VAR '[' arit ']' '=' VAR {$$ = newvec($1, $2, $4, newValorVal($7, newint(0)), NULL);}
    | TIPO_TEXTO VAR '[' arit ']' {$$ = newvec($1, $2, $4, NULL, NULL);}
    | declvartexto ',' VAR '[' arit ']' {
        if ($1->nodetype=='V') $$ = newvec(((Symasgn*)$1)->type, $3, $5, NULL, $1);
        else $$ = newvec($1->nodetype, $3, $5, NULL, $1);
    }
    | declvartexto ',' VAR '[' arit ']' '=' '{' valorvectexto '}' {
        if ($1->nodetype=='V') $$ = newvec(((Symasgn*)$1)->type, $3, $5, $9, $1);
        else $$ = newvec($1->nodetype, $3, $5, $9, $1);
    }
    | declvartexto ',' VAR '[' arit ']' '=' VAR {
        if ($1->nodetype=='V') $$ = newvec(((Symasgn*)$1)->type, $3, $5, newValorVal($8, newint(0)), $1);
        else $$ = newvec($1->nodetype, $3, $5, newValorVal($8, newint(0)), $1);
    }
    ;
/*
declvectexto: declvectexto ',' VAR '[' arit ']' {$$ = newvec(((Symasgn*)$1)->type, $3, $5, NULL, $1);}
    | declvectexto ',' VAR '[' arit ']' '=' '{' valorvectexto '}' {$$ = newvec(((Symasgn*)$1)->type, $3, $5, $9, $1);}
    | TIPO_TEXTO VAR '[' arit ']' '=' '{' valorvectexto '}' {$$ = newvec($1, $2, $4, $8, NULL);}
    | TIPO_TEXTO VAR '[' arit ']' {$$ = newvec($1, $2, $4, NULL, NULL);}
    ;
//*/
valorvectexto: TEXTO ',' valorvectexto {$$ = newast('l', newtexto($1), $3);}
    | TEXTO {$$ = newast('l', newtexto($1), NULL);}
    | logica ',' valorvectexto {$$ = newast('l', $1, $3);}
    | logica {$$ = newast('l', $1, NULL);}
    ;
valorvec: logica ',' valorvec {$$ = newast('l', $1, $3);}
    | logica {$$ = newast('l', $1, NULL);}
    ;
/*
declvecmult: TIPO VAR '[' arit ']' '=' '{' valorvec '}' {$$ = newvec($1, $2, $4, $8, NULL);}
    | TIPO VAR '[' arit ']' {$$ = newvec($1, $2, $4, NULL, NULL);}
    | declvecmult ',' VAR '[' arit ']' {$$ = newvec(((Symasgn*)$1)->type, $3, $5, NULL, $1);}
    | declvecmult ',' VAR '[' arit ']' '=' '{' valorvec '}' {$$ = newvec(((Symasgn*)$1)->type, $3, $5, $9, $1);}
    ;
//*/
outfunc: VAR '(' arg ')' {$$ = newast('a', newtexto($1), $3);}
    | VAR '(' ')' {$$ = newast('a', newtexto($1), NULL);}
    ; 
operadorternario: '(' logica ')' '?' exp ':' exp %prec POT {$$ = newflow('?', $2, $5, $7);}
    ;
args: TIPO VAR {$$ = newast('l', newvar($1, $2, NULL, NULL), NULL);}
    | TIPO VAR ',' args {$$ = newast('l', newvar($1, $2, NULL, NULL), $4);}
    ;
arg: logica {$$ = newast('l', $1, NULL);}
    | logica ',' arg {$$ = newast('l', $1, $3);}
    ;
saida: logica {$$ = newast('P', $1, NULL);}
    | logica ',' saida { $$ = newast('P', $1, $3);}
    | TEXTO {$$ = newast('P', newtexto($1), NULL);}
    | TEXTO ',' saida {$$ = newast('P', newtexto($1), $3);}
    | incdec {$$ = newast('P', $1, NULL);}
    | incdec ',' saida { $$ = newast('P', $1, $3);}
    ;
incdec: VAR PLUS %prec PLUS2 {$$ = newasgn($1, newint(0), newast('+', newValorVal($1, newint(0)), newint(1)));}
    | VAR LESS %prec LESS2 {$$ = newasgn($1, newint(0), newast('-', newValorVal($1, newint(0)), newint(1)));}
    //| PLUS VAR %prec PLUS1 {$$ = newast('l', newValorVal($2), newasgn($2, 0, newast('+', newValorVal($2), newint(1))));}
    //| LESS VAR %prec LESS1 {$$ = newast('l', newValorVal($2), newasgn($2, 0, newast('-', newValorVal($2), newint(1))));}
    ;
list: exp {$$ = $1;}
    | list NEWLINHA nl exp { $$ = newast('L', $1, $4);}
    ;
logica: logica OR logica {$$ = newcmp(7,$1,$3);}
    | logica AND logica {$$ = newcmp(8,$1,$3);}
    | logica MAIOR logica {$$ = newcmp(1,$1,$3);}
    | logica MENOR logica {$$ = newcmp(2,$1,$3);}
    | logica DIF logica {$$ = newcmp(3,$1,$3);}
    | logica II logica {$$ = newcmp(4,$1,$3);}
    | logica MAI logica {$$ = newcmp(5,$1,$3);}
    | logica MEI logica {$$ = newcmp(6,$1,$3);}
    | arit {$$ = $1;}
    ;
arit: SIN '(' arit ')' {$$ = newast('S',$3,NULL);}
    | COS '(' arit ')' {$$ = newast('C',$3,NULL);}
    | RAIZ '(' arit ')' {$$ = newast('R',$3,NULL);}
    | '-' arit %prec NEG {$$ = newast('M', $2, NULL);}
    | '|' arit '|' {$$ = newast('A',$2,NULL);}
    | arit '+' arit {$$ = newast('+',$1,$3);}
    | arit '-' arit {$$ = newast('-',$1,$3);}
    | arit '*' arit {$$ = newast('*',$1,$3);}
    | arit '/' arit {$$ = newast('/',$1,$3);}
    | arit '%' arit {$$ = newast('%',$1,$3);}
    | arit '^' arit {$$ = newast('^',$1,$3);}
    | '(' logica ')' {$$ = $2;}
    | valor {$$ = $1;}
    ;

valor: INTEIRO {$$ = newint($1);}    // codigo 'k'
    | REAL {$$ = newreal($1);}      // codigo 'K'
    | VAR varvar {
        if($2==NULL) $$ = newValorVal($1, newint(0));
        else $$ = newast('a', newtexto($1), $2->r);
    }
    | VAR '[' arit ']' {$$ = newValorVal($1, $3);}
    ;
varvar: {$$ = NULL;}
    | '(' varfun ')' {
        if ($2!=NULL) $$ = newast('j', NULL, $2->r);
        else $$ = newast('j', NULL, NULL);
    }
    ;
varfun: {$$ = NULL;}
    | arg {$$ = newast('j', NULL, $1);}
    ;
%%

#include "lex.yy.c"

int main(){
    yyin=fopen("exemplo.txt", "r");
    yyparse();    
    fclose(yyin);

    return 0;
}

int yywrap(){
    return 0;
}