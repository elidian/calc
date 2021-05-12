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

    typedef struct ast { /*Estrutura de um nó*/
        int nodetype;
        struct ast *l; /*Esquerda*/
        struct ast *r; /*Direita*/
    }Ast; 

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
            printf("Erro(vetor): posicao fora do vetor\n");
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
            case 'n':;
                VARS * auxn = (VARS*)malloc(sizeof(VARS));
                auxn = srch(rvar, ((Varval*)a)->var);
                if (!auxn){
                    VARSI * auxn2 = srchi(ivar, ((Varval*)a)->var);
                    if (!auxn2){
                        VARST * auxn3 = srcht(tvar, ((Varval*)a)->var);
                        if (!auxn3){
                            printf ("460 - Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
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
                            auxnt->r = NULL;
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
                        auxni->r = NULL;
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
                    auxnr->r = NULL;
                    eval(auxnr);
                    v = auxn->v;
                }
                break;
            case 'u':;
                VARS * auxu = (VARS*)malloc(sizeof(VARS));
                auxu = srch(rvar, ((Varval*)a)->var);
                if (!auxu){
                    VARSI * auxu2 = srchi(ivar, ((Varval*)a)->var);
                    if (!auxu2){
                        VARST * auxu3 = srcht(tvar, ((Varval*)a)->var);
                        if (!auxu3){
                            printf ("507 - Variavel '%s' nao foi declarada.\n", ((Varval*)a)->var);
                            v = 0.0;
                        }
                        else{
                            Ast * auxut = (Ast*)malloc(sizeof(Ast));
                            if(!auxut){
                                printf("out of space");
                                exit(0);
                            }
                            auxut->nodetype = 'p';
                            auxut->l = newtexto(auxu3->v);
                            auxut->r = NULL;
                            eval(auxut);
                            v = atof(auxu3->v);
                        }
                    }
                    else{
                        Ast * auxui = (Ast*)malloc(sizeof(Ast));
                        if(!auxui){
                            printf("out of space");
                            exit(0);
                        }
                        auxui->nodetype = 'p';
                        auxui->l = newint(auxu2->v);
                        auxui->r = NULL;
                        eval(auxui);
                        v = (double)auxu2->v;
                    }
                }
                else{
                    Ast * auxur = (Ast*)malloc(sizeof(Ast));
                    if(!auxur){
                        printf("out of space");
                        exit(0);
                    }
                    auxur->nodetype = 'p';
                    auxur->l = newreal(auxu->v);
                    auxur->r = NULL;
                    eval(auxur);
                    v = auxu->v;
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
            case 'P': 
                    //printf("P1\n");
                    if(!a->l)
                        break;
                    //printf("P - %c\n", a->l->nodetype);
                    if(a->l->nodetype == 'N'){
                        a->l->nodetype = 'n';
                        //printf("P2\n");
                        v = eval(a->l);
                    } else {
                        //printf("P3\n");
                        v = eval(a->l);
                        if(a->l->nodetype != 'n' && a->l->nodetype != 'k' && a->l->nodetype != 'K' && a->l->nodetype != 'm'){
                            
                            printf("%.2f\n", v);
                        }
                    }
                    //printf("P4\n");
                    if(((Intval*)a->l)->nodetype == 'k')
                        printf ("%d\n", ((Intval*)a->l)->v);		/*Recupera um valor inteiro*/
                    else if(((Realval*)a->l)->nodetype == 'K')
                        printf ("%.2f\n", ((Realval*)a->l)->v);		/*Recupera um valor real*/
                    else if(((Textoval*)a->l)->nodetype == 'm')
                        printf ("%s\n", ((Textoval*)a->l)->v);		/*Recupera um valor real*/
                    //printf("P5\n");
                    if(!a->r)
                        break;
                    else{
                        //printf("P6\n");
                        //printf("a->r->nodetype: %c\n", a->r->nodetype);
                        eval(a->r);
                    }
                    //printf("P7\n");
                    break;  /*Função que imprime um valor*/
            case 'p': 
                    //printf("pp1\n");
                    if(!a->l)
                        break;
                    //printf("P - %c\n", a->l->nodetype);
                    if(a->l->nodetype == 'N'){
                        //printf("pp2\n");
                        a->l->nodetype = 'u';
                        v = eval(a->l);
                    } else {
                        //printf("pp3\n");
                        v = eval(a->l);
                        if(a->l->nodetype != 'n' && a->l->nodetype != 'k' && a->l->nodetype != 'K' && a->l->nodetype != 'm'){    
                            printf("%.2f", v);
                        }
                    }
                    //printf("pp4\n");
                    if(((Intval*)a->l)->nodetype == 'k')
                        printf ("%d", ((Intval*)a->l)->v);		/*Recupera um valor inteiro*/
                    else if(((Realval*)a->l)->nodetype == 'K')
                        printf ("%.2f", ((Realval*)a->l)->v);		/*Recupera um valor real*/
                    else if(((Textoval*)a->l)->nodetype == 'm')
                        printf ("%s", ((Textoval*)a->l)->v);		/*Recupera um valor real*/
                    //printf("pp5\n");
                    if(!a->r)
                        break;
                    else{
                        //printf("pp6\n");
                        //printf("a->r->nodetype: %c\n", a->r->nodetype);
                        eval(a->r);
                    }
                    //printf("pp7\n");
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
%token <inteiro> TIPO
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
%type <a> exp declmult atrib list saida incdec //valorvec declvecmult
%type <a> logica
%type <a> L1
%type <a> arit
%type <a> arit0
%type <a> arit1
%type <a> arit2
%type <a> arit3
%type <a> valor



//DECLARAÇÃO DE PRECEDÊNCIA
%left OR AND
%left MAIOR MENOR MEI MAI II DIF
%right '='
%left '+' '-'
%left '*' '/' '%'
%right '^'
%left PLUS1 LESS1
%right PLUS2 LESS2
%left ')'
%right '('

%nonassoc IMUNUS VAR IFX 

%start prog
%%

prog: INICIO cod FINAL {printf("\nFIM\n\n"); return 0;}
    ;
cod: cod exp {eval($2);}
    | 
    ;
atrib: VAR '=' logica {$$ = newasgn($1, $3);}
    | TIPO VAR '=' logica {$$ = newvar($1, $2, $4, NULL);}
    ;
declmult: declmult ',' VAR {$$ = newvar($1->nodetype, $3, NULL, $1);}
    | declmult ',' VAR '=' logica {$$ = newvar($1->nodetype, $3, $5, $1);}
    | TIPO VAR '=' logica {$$ = newvar($1, $2, $4, NULL);}
    | TIPO VAR {$$ = newvar($1, $2, NULL, NULL);}
    ;
    // [1, 2, 3]
    // n1(v, 1,(2, 3) )
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
exp: declmult {$$ = $1;}
    //| declvecmult {$$ = $1;}
    //| SAIDA VAR '[' logica ']' {$$ = newast('v', newtexto($2), $4);}
    | VAR '=' logica {$$ = newasgn($1, $3);}
    | VAR '=' TEXTO {$$ = newasgn($1, newtexto($3));} 
    | TIPO VAR '=' TEXTO {$$ = newvar($1, $2, newtexto($4), NULL);}
    | VAR ENTRADA {$$ = newast('c', newValorVal($1), NULL);}
    | IF logica '{' list '}' %prec IFX {$$ = newflow('I', $2, $4, NULL);}
	| IF logica '{' list '}' ELSE '{' list '}' {$$ = newflow('I', $2, $4, $8);}
	| WHILE logica '{' list '}' {$$ = newflow('W', $2, $4, NULL);}
    | FOR atrib ':' logica ':' arit '{' list '}' {$$ = newflowfor('F', $2, $4, $6, $8, NULL);}
    | COMENTARIO {$$ = newast('P', NULL, NULL);}
    | logica {$$ = newast('P', $1, NULL);}
    | logica '?' exp ':' exp {$$ = newflow('?', $1, $3, $5);}
    | SAIDA saida {$$ = $2;}
    | TYPE '(' VAR ')' {$$ = newast('T', newtexto($3), NULL);}
    | incdec {$$ = $1;}
    ; 
    // >> 'autor: ', nome , 'valor: ' , x
    // SAIDA saida( texto , saida( logica, saida( texto, saida( logica ) ) ) )
saida: logica { $$ = newast('P', $1, NULL);}
    | logica ',' saida { $$ = newast('p', $1, $3);}
    | TEXTO {$$ = newast('P', newtexto($1), NULL);}
    | TEXTO ',' saida {$$ = newast('p', newtexto($1), $3);}
    | incdec { $$ = newast('P', $1, NULL);}
    | incdec ',' saida { $$ = newast('p', $1, $3);}
    ;
incdec: VAR PLUS %prec PLUS2 {$$ = newasgn($1, newast('+',newValorVal($1),newint(1)));}
    | VAR LESS %prec LESS2 {$$ = newasgn($1, newast('-',newValorVal($1),newint(1)));}
    | PLUS VAR %prec PLUS1 {$$ = newast('l', newValorVal($2), newasgn($2, newast('+', newValorVal($2), newint(1))));}
    | LESS VAR %prec LESS1 {$$ = newast('l', newValorVal($2), newasgn($2, newast('-', newValorVal($2), newint(1))));}
    ;
list: exp {$$ = $1;}
    | list exp { $$ = newast('L', $1, $2);}
    ;
logica: logica OR L1 {$$ = newcmp(7,$1,$3);}
    | logica AND L1 {$$ = newcmp(8,$1,$3);}
    | L1 {$$ = $1;}
    ;
L1: L1 MAIOR arit {$$ = newcmp(1,$1,$3);}
    | L1 MENOR arit {$$ = newcmp(2,$1,$3);}
    | L1 DIF arit {$$ = newcmp(3,$1,$3);}
    | L1 II arit {$$ = newcmp(4,$1,$3);}
    | L1 MAI arit {$$ = newcmp(5,$1,$3);}
    | L1 MEI arit {$$ = newcmp(6,$1,$3);}
    | arit {$$ = $1;}
    ;
arit: SIN '(' arit ')' {$$ = newast('S',$3,NULL);}
    | COS '(' arit ')' {$$ = newast('C',$3,NULL);}
    | RAIZ '(' arit ')' {$$ = newast('R',$3,NULL);}
    | '|' arit '|' {$$ = newast('A',$2,NULL);}
    | arit0 {$$=$1;}
    ;
arit0: arit0 '+' arit1 {$$ = newast('+',$1,$3);}
    | arit0 '-' arit1 {$$ = newast('-',$1,$3);}
    | arit1 {$$=$1;}
    ;
arit1: arit1 '*' arit2 {$$ = newast('*',$1,$3);}
    | arit1 '/' arit2 {$$ = newast('/',$1,$3);}
    | arit1 '%' arit2 {$$ = newast('%',$1,$3);}
    | arit2 {$$=$1;}
    ;
arit2: arit3 '^' arit2 {$$ = newast('^',$1,$3);}
    | arit3 {$$=$1;}
    ;
arit3: '(' logica ')' {$$ = $2;}
    | valor {$$ = $1;}
    | '(' '-' arit3 ')' %prec IMUNUS {$$ = newast('M',$3,NULL);}
    ;
valor: INTEIRO {$$ = newint($1);}    // codigo 'k'
    | REAL {$$ = newreal($1);}      // codigo 'K'
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
