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

    typedef struct varsi {
		char name[name_size];
        int v;
		struct varsi * prox;
	} VARSI;

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

    typedef struct varst {
		char name[name_size];
		char v[string_size];
		struct varst * prox;
	} VARST;

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
    // estrutura de vetor
    typedef struct veci {
		char name[name_size];
        int v;
        struct veci * in;
		struct veci * prox;
	} Veci;

    //add novo vetor na lista de vetores
	Veci * insveci(Veci *l, char n[]){
		Veci *aux =(Veci*)malloc(sizeof(Veci));
		if(!aux) {
            printf("out of space");
            exit(0);
        }
        strcpy(aux->name, n);
        aux->in = (Veci*)NULL;
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

    //busca uma variável na lista de vetores
	Veci *srchvecip(Veci *l, int n){
		Veci *aux = l;
		for(int x = 0; x < n; x++){
			aux = aux->in;
            if (!aux)
                return aux;
		}
		return aux;
	}

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
		while(aux != NULL){
			if(strcmp(n,aux->name)==0){
				return aux;
			}
			aux = aux->prox;
		}
		return aux;
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

    typedef struct symasgn { /*Estrutura para um nó de atribuição. Para atrubuir o valor de v em s*/
        int nodetype;
        char s[name_size];
        Ast *v;
        Ast *n;
    }Symasgn;

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
    Ast * newvec(int t, char s[], Ast *v, Ast *n){
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

    typedef struct flow { /*Estrutura de um desvio (if/else/while)*/
        int nodetype;
        Ast *cond;		/*condição*/
        Ast *tl;		/*then, ou seja, verdade*/
        Ast *el;		/*else*/
    }Flow;

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

    typedef struct intval { /*Estrutura de um número*/
        int nodetype;
        int v;
    }Intval;
    
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

    typedef struct realval { /*Estrutura de um número*/
        int nodetype;
        double v;
    }Realval;

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

    typedef struct textoval { /*Estrutura de um número*/
        int nodetype;
        char v[string_size];
    }Textoval;

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

    typedef struct varval { /*Estrutura de um nome de variável, nesse exemplo uma variável é um número no vetor var[26]*/
        int nodetype;
        char var[name_size];
    }Varval;

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

    VARSI *ivar = NULL;
	VARS *rvar = NULL;
    VARST *tvar = NULL;
    Veci * ivec = NULL;
    Function *function = NULL;

    bool varexiste(char v[]) {
        VARS* xr = srch(rvar, v);
        VARSI* xi = srchi(ivar, v);
        VARST* xt = srcht(tvar, v);
        //Veci* vi = srchveci(ivec, v);

        if(!xr && !xi && !xt) 
            return false; // se tudo NULL, var nao existe
        else
            return true; // se algum TRUE, var já existe
    }

    void printvec(Veci *a){
        int i = 0;
        while(a){
            printf("%s[%d] = %d\n", a->name, i, a->v);
            i++;
            a = a->in;
        }
    }
    void printvecp(Veci *a, int x){
        printf("1 printvecp\n");
        int i = 0;
        char name[name_size];
        strcpy(name, a->name);
        printf("2 printvecp\n");
        bool teste = true;
        while(teste){
            printf("4 printvecp\n");
            if(a->in)
                a = a->in;
            else {
                printf("5 printvecp\n");
                teste = false;
            }
        }
        printf("3 printvecp\n");
        if(teste)
            printf("%s[%d] = %d\n", name, i, a->v);
        else
            printf("Erro (printvecp()): posicao fora do vetor\n");
    }

    void * printValorVar(char *var){
        //printf("VAR %s\n", var);
        VARS * auxr = srch(rvar, var);
        if (auxr){
            printf("%f", auxr->v);
        } else {
            VARSI * auxi = srchi(ivar, var);
            if (auxi){
                printf("%d", auxi->v);
            } else {
                VARST * auxt = srcht(tvar, var);
                if (auxt){
                    printf("%s", auxt->v);
                }
                else{
                    printf ("Erro (printValorVar()) - Variavel '%s' nao foi declarada.\n", var);
                }
            }
        }
    }

    double eval(Ast *a) { /*Função que executa operações a partir de um nó*/
        double v;
        if(!a) {
            printf("internal error, null eval\n");
            return 0.0;
        }
        //printf("\na->type: %c\n", a->nodetype);
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
                            printf ("439 - Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                            v = 0.0;
                        } else {
                            v = atof(auxt->v);
                        }
                    } else {
                        v = (double)aux2->v;
                    }
                }
                else{
                    v = aux->v;
                }
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
            case 'l': v = eval(a->l); eval(a->r); break;
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
                    printValorVar(((Varval*)a->l)->var);
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
            
            // declarar variavel inteiro
            case 'i':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(((Symasgn *)a)->s)){
                    ivar = insi(ivar, ((Symasgn *)a)->s);
                    if(((Symasgn *)a)->v)
                        ivar->v = (int)eval(((Symasgn *)a)->v); /*Atribui à variável*/
                }else
                    printf("Erro(declaracao): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
                break;
            // declarar variavel real
            case 'r':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(((Symasgn *)a)->s)){
                    rvar = ins(rvar, ((Symasgn *)a)->s);
                    VARS * xr = (VARS*)malloc(sizeof(VARS));
                    if(!xr) {
                        printf("out of space");
                        exit(0);
                    }
                    xr = srch(rvar, ((Symasgn *)a)->s);
                    if(((Symasgn *)a)->v)
                        xr->v = eval(((Symasgn *)a)->v);
                }else
                    printf("Erro(declaracao): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
                break;
            // declarar variavel texto
            case 't':;
                if(((Symasgn *)a)->n)
                    eval(((Symasgn *)a)->n);
                if(!varexiste(((Symasgn *)a)->s)){
                    tvar = inst(tvar, ((Symasgn *)a)->s);
                    VARST * xt = (VARST*)malloc(sizeof(VARST));
                    if(!xt) {
                        printf("out of space");
                        exit(0);
                    }
                    xt = srcht(tvar, ((Symasgn *)a)->s);
                    if((((Symasgn *)a)->v))
                        strcpy(xt->v, ((Textoval*)((Symasgn*)a)->v)->v);
                }else
                    printf("Erro(declaracao): variavel '%s' ja existe.\n", ((Symasgn *)a)->s);
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
                            printf("Erro(<<): Variavel invalida!\n");
                        }
                    }
                }
                break;
            case 'T':;
                // função TYPE(var)
                VARS * xcrt = srch(rvar, ((Textoval *)a->l)->v);
                if(xcrt){
                    printf("Type(%s): real\n", ((Textoval *)a->l)->v);
                } else {
                    VARSI * xcit = srchi(ivar, ((Textoval *)a->l)->v);
                    if(xcit){
                        printf("Type(%s): inteiro\n", ((Textoval *)a->l)->v);
                    } else {
                        VARST * xctt = srcht(tvar, ((Textoval *)a->l)->v);
                        if(xctt){
                            printf("Type(%s): texto\n", ((Textoval *)a->l)->v);
                        } else {
                            printf("Erro(type): Variavel invalida!\n");
                        }
                    }
                }
                break;
            
            case 'V':;
                
                break;

            case 'B':;
                if(srchfunction(function, ((Func*)a)->name)==NULL)
                    function = insfunction(function, ((Func*)a));
                else
                    printf("Erro (case 'B'): reescrita de funcao nao permitida\n");
                
                break;
            
            case 'a':;
                Function *auxa = srchfunction(function, ((Textoval*)a->l)->v);
                if(auxa==NULL)
                    printf("Erro (case 'a'): funcao nao declarada\n");
                else {
                    //*
                    // salva a lista de variaveis antes de iniciar a função
                    VARSI * i1 = ivar;
                    VARS *r1 = rvar;
                    VARST *t1 = tvar;

                    // verifica e executa as declarações e atribuições de ARGUMENTOS da função
                    if(auxa->args!=NULL && a->r!=NULL) {
                        Ast *b = auxa->args;
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
                                printf("Erro (case 'a'): arg insuficientes\n");
                            }
                        }
                    } else {
                        printf("Erro (case 'a'): chamada de funcao errada\n");
                        break;
                    }
                    // fim do bloco de ARGUMENTOS da função
                    //*/
                    
                    // chama bloco de codigos dentro da função
                    if(auxa->v)
                        eval(auxa->v);
                    // fim do bloco de codigos dentro da função

                    // excluindo as variaveis apos o final da função
                    VARSI * i2 = ivar;
                    VARS *r2 = rvar;
                    VARST *t2 = tvar;
                    VARSI * i3 = NULL;
                    VARS *r3 = NULL;
                    VARST *t3 = NULL;
                    if(i1!=NULL){
                        while(strcmp(i2->name, i1->name)!=0){
                            if(strcmp(i2->name, i1->name)==0){
                                ivar = i2;
                            } else {
                                i3 = i2;
                                i2 = i2->prox;
                                free(i3);
                                i3 = NULL;
                            }
                        }
                    } else {
                        while(i2!=NULL){
                            i3 = i2;
                            i2 = i2->prox;
                            free(i3);
                            i3 = NULL;
                        }
                    }
                    if(i1!=NULL){
                        while(strcmp(i2->name, i1->name)!=0){
                            if(r1!=NULL){
                                if(strcmp(r2->name, r1->name)==0){
                                    rvar = r2;
                                } else {
                                    r3 = r2;
                                    r2 = r2->prox;
                                    free(r3);
                                    r3 = NULL;
                                }
                            }
                        }
                    } else {
                        while(r2!=NULL){
                            r3 = r2;
                            r2 = r2->prox;
                            free(r3);
                            r3 = NULL;
                        }
                    }
                    if(i1!=NULL){
                        while(strcmp(i2->name, i1->name)!=0){
                            if(t1!=NULL){
                                if(strcmp(t2->name, t1->name)==0){
                                    tvar = t2;
                                } else {
                                    t3 = t2;
                                    t2 = t2->prox;
                                    free(t3);
                                    t3 = NULL;
                                }
                            }
                        }
                    } else {
                        while(t2!=NULL){
                            t3 = t2;
                            t2 = t2->prox;
                            free(t3);
                            t3 = NULL;
                        }
                    }
                    // FIM da exclusão da variaveis internas da função
                }
                break;

            case 'z':;
                printf("\n-> Fim do programa! <-\n\n");
                free(ivar);
                ivar = NULL;
                free(rvar);
                rvar = NULL;
                free(tvar);
                tvar = NULL;
                exit(0);
                break;

            default: printf("internal error: bad node %c\n", a->nodetype);
        }
        return v;
    }

%}

%union{
    char texto[50];
    int inteiro;
    double real;
    Ast *a;
}

//DECLARAÇÃO DE TOKENS
%token <inteiro> TIPO TIPO_TEXTO
%token <inteiro> INTEIRO
%token <real> REAL
%token <texto> TEXTO
%token <texto> TYPE
%token ENTRADA
%token SAIDA
%token INICIO
%token FINAL
%token IF ELSE FOR WHILE
%token <texto> VAR
%token <texto> COMENTARIO
//TOKENS DE ARITMETICA
%token RAIZ COS SIN
//TOKENS DE LOGICA
//%token MAIOR MENOR MEI MAI II DIF OR AND
%token <texto> PLUS LESS

//DECLARAÇÃO DE TIPO DE NÃO-TERMINAIS
%type <a> declvartexto
%type <a> exp declvar atrib list saida incdec args arg //valorvec declvecmult
%type <a> logica
%type <a> arit
%type <a> valor decl declfunction
%type <a> iterator

//DECLARAÇÃO DE PRECEDÊNCIA
//%precedence ITERATOR
%left OR AND
%left MAIOR MENOR MEI MAI II DIF
%right '='
%nonassoc NEG
%left '+' '-' MINUS
%left '*' '/' '%'
%right '^'
//%precedence NEG
//%left PLUS1 LESS1
%right PLUS2 LESS2
%left ')'
%right '('

%nonassoc VAR IFX FUN FUN2 ITERATOR

%start prog
%%

prog: INICIO cod FINAL {eval(newast('z', NULL, NULL));}
    ;
cod: cod exp {eval($2);}
    | exp {eval($1);}
    ;
atrib: VAR '=' logica {$$ = newasgn($1, $3);}
    | TIPO VAR '=' logica {$$ = newvar($1, $2, $4, NULL);}
    ;
decl: declvar {$$ = $1;}
    | declfunction {$$ = $1;}
    ;
declfunction: TIPO VAR '(' args ')' '{' list '}' %prec FUN {$$ = newfunction($1, $2, $4, $7);}
    | TIPO VAR '(' ')' '{' list '}' %prec FUN {$$ = newfunction($1, $2, NULL, $6);}
    ;
declvar: declvar ',' VAR {$$ = newvar($1->nodetype, $3, NULL, $1);}
    | declvar ',' VAR '=' logica {$$ = newvar($1->nodetype, $3, $5, $1);}
    | TIPO VAR '=' logica %prec LESS2 {$$ = newvar($1, $2, $4, NULL);}
    | TIPO VAR %prec LESS2 {$$ = newvar($1, $2, NULL, NULL);}
    ;
declvartexto: declvartexto ',' VAR {$$ = newvar($1->nodetype, $3, NULL, $1);}
    | declvartexto ',' VAR '=' TEXTO {$$ = newvar($1->nodetype, $3, newtexto($5), $1);}
    | TIPO_TEXTO VAR '=' TEXTO {$$ = newvar($1, $2, newtexto($4), NULL);}
    | TIPO_TEXTO VAR {$$ = newvar($1, $2, NULL, NULL);}
    ;

    // [1, 2, 3]
    // n1(v, 1, (2, 3) )
    // n2(v, 2, 3)
/*
valorvec: logica ',' valorvec {$$ = newast('l', $1, $3);}
    | logica {$$ = newast('l', $1, NULL);}
    ;
declvecmult: TIPO VAR '['']' '=' '[' valorvec ']' {$$ = newvec('V', $2, $7, NULL);}
    | TIPO VAR '['']' {$$ = newvec('V', $2, NULL, NULL);}
    | declvecmult ',' VAR '['']' {$$ = newvec($1->nodetype, $3, NULL, $1);}
    | declvecmult ',' VAR '['']' '=' '[' logica ']' {$$ = newvec($1->nodetype, $3, $8, $1);}
    ;
//*/
exp: decl {$$ = $1;}
    | declvartexto {$$ = $1;}
    //| declvecmult {$$ = $1;}
    //| SAIDA VAR '[' logica ']' {$$ = newast('v', newtexto($2), $4);}
    | VAR '=' logica {$$ = newasgn($1, $3);}
    | VAR '=' TEXTO {$$ = newasgn($1, newtexto($3));} 
    //| TIPO VAR '=' TEXTO {$$ = newvar($1, $2, newtexto($4), NULL);}
    | VAR ENTRADA {$$ = newast('c', newValorVal($1), NULL);}
    | IF logica '{' list '}' %prec IFX {$$ = newflow('I', $2, $4, NULL);}
	| IF logica '{' list '}' ELSE '{' list '}' {$$ = newflow('I', $2, $4, $8);}
	| WHILE logica '{' list '}' {$$ = newflow('W', $2, $4, NULL);}
    | FOR atrib ';' logica ';' arit '{' list '}' {$$ = newflowfor('F', $2, $4, $6, $8, NULL);}
    | COMENTARIO {$$ = newast('P', NULL, newtexto($1));}
    //| logica {$$ = newast('P', $1, NULL);}
    | iterator {$$ = $1;}
    | SAIDA saida {$$ = $2;}
    | SAIDA ';' { $$ = newast('P', NULL, NULL);} 
    | TYPE '(' VAR ')' {$$ = newast('T', newtexto($3), NULL);}
    | incdec {$$ = $1;}
    | VAR '(' arg ')' %prec FUN {$$ = newast('a', newtexto($1), $3);}
    | VAR '(' ')' %prec FUN2 {$$ = newast('a', newtexto($1), NULL);}
    ; 
iterator: logica '?' exp ':' exp %prec ITERATOR {$$ = newflow('?', $1, $3, $5);}
    ;
//*
args: TIPO VAR {$$ = newast('l', newvar($1, $2, NULL, NULL), NULL);}
    | TIPO VAR ',' args {$$ = newast('l', newvar($1, $2, NULL, NULL), $4);}
    //| %empty {$$ = NULL;}
    ;
arg: valor {$$ = newast('l', $1, NULL);}
    | valor ',' arg {$$ = newast('l', $1, $3);}
    //| %empty {$$ = NULL;}
    ;
//*/
    // >> 'autor: ', nome , 'valor: ' , x
    // SAIDA saida( texto , saida( logica, saida( texto, saida( logica, NULL ) ) ) )
saida: logica { $$ = newast('P', $1, NULL);}
    | logica ',' saida { $$ = newast('P', $1, $3);}
    | TEXTO {$$ = newast('P', newtexto($1), NULL);}
    | TEXTO ',' saida {$$ = newast('P', newtexto($1), $3);}
    | incdec { $$ = newast('P', $1, NULL);}
    | incdec ',' saida { $$ = newast('P', $1, $3);}
    ;
incdec: VAR PLUS %prec PLUS2 {$$ = newasgn($1, newast('+',newValorVal($1),newint(1)));}
    | VAR LESS %prec LESS2 {$$ = newasgn($1, newast('-',newValorVal($1),newint(1)));}
    //| PLUS VAR %prec PLUS1 {$$ = newast('l', newValorVal($2), newasgn($2, newast('+', newValorVal($2), newint(1))));}
    //| LESS VAR %prec LESS1 {$$ = newast('l', newValorVal($2), newasgn($2, newast('-', newValorVal($2), newint(1))));}
    ;
list: exp {$$ = $1;}
    | list exp { $$ = newast('L', $1, $2);}
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
    | arit '-' arit %prec MINUS {$$ = newast('-',$1,$3);}
    | arit '*' arit {$$ = newast('*',$1,$3);}
    | arit '/' arit {$$ = newast('/',$1,$3);}
    | arit '%' arit {$$ = newast('%',$1,$3);}
    | arit '^' arit {$$ = newast('^',$1,$3);}
    | '(' logica ')' {$$ = $2;}
    | valor {$$ = $1;}
    ;
valor: INTEIRO {$$ = newint($1);}    // codigo 'k'
    | REAL {$$ = newreal($1);}      // codigo 'K'
    //| '-' REAL {$$ = newast('M', newreal($2), NULL);}      // codigo 'K'
    //| TEXTO {$$ = newtexto($1);}    // codigo 'm'
    | VAR {$$ = newValorVal($1);}   // codigo 'N'
    //| incdec {$$ = $1;}
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
