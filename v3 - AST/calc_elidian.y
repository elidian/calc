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

    
    typedef struct variavels {
		char name[50];
        int type; // string se 0, int se 1, double se 2
        char tv[100];
        int iv;
        double rv;
		struct variavels * prox;
	} VARIAVELS;

    typedef struct varsi {
		char name[30];
        int v;
		struct varsi * prox;
	} VARSI;

    typedef struct vars {
		char name[30];
        double v;
		struct vars * prox;
	} VARS;

    typedef struct varst {
		char name[30];
		char v[100];
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
        char v[100];
    }Textoval;

    typedef struct varval { /*Estrutura de um nome de variável, nesse exemplo uma variável é um número no vetor var[26]*/
        int nodetype;
        char var[30];
    }Varval;

    typedef struct flow { /*Estrutura de um desvio (if/else/while)*/
        int nodetype;
        Ast *cond;		/*condição*/
        Ast *tl;		/*then, ou seja, verdade*/
        Ast *el;		/*else*/
    }Flow;

    typedef struct symasgn { /*Estrutura para um nó de atribuição. Para atrubuir o valor de v em s*/
        int nodetype;
        char s[30];
        Ast *v;
    }Symasgn;

    typedef struct symasgnt { /*Estrutura para um nó de atribuição. Para atrubuir o valor de v em s*/
        int nodetype;
        char s[30];
        char v[100];
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
    // função pra declarar variavel e atribuir valor texto
    Ast * newvart(int t, char s[], char v[]){
        Symasgnt *a = (Symasgnt*)malloc(sizeof(Symasgnt));
        if(!a) {
            printf("out of space");
            exit(0);
        }
        a->nodetype = 't'; /*tipo i, r ou t, conforme arquivo .l*/
        strcpy(a->s, s); /*Símbolo/variável*/
        strcpy(a->v, v); /*Valor*/
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
                        printf("Erro de var nao declarada\n");
                        v = 0.0;
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
                if( ((Flow *)a)->tl ) {
                    for(eval(((Flowfor*)((Flow *)a)->cond)->v1); 
                        eval(((Flowfor*)((Flow *)a)->cond)->v2); 
                        eval(((Flowfor*)((Flow *)a)->cond)->v3)
                        ){
                            v =  eval(((Flow *)a)->tl);
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
                    if(((Realval*)a->l)->nodetype == 'K')
                        printf ("%.2f\n", ((Realval*)a->l)->v);		/*Recupera um valor real*/
                    if(((Textoval*)a->l)->nodetype == 'm')
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
                if(!isreal(((Symasgnt *)a)->v))
                    strcpy(xt->v, ((Symasgnt *)a)->v);
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
%token ENTRADA
%token SAIDA
%token INICIO
%token FINAL
%token IF ELSE FOR WHILE
%token <texto> VAR
%token <texto> COMENTARIO
//TOKENS DE ARITMETICA
%token RAIZ COS SIN REST
//TOKENS DE LOGICA
%token MAIOR MENOR MEI MAI II DIF OR AND

//DECLARAÇÃO DE TIPO DE NÃO-TERMINAIS
%type <a> exp atrib
%type <a> logica L1 L2
%type <a> arit valor arit1 arit2 arit3 list 

//DECLARAÇÃO DE PRECEDÊNCIA
//%right MAIOR MENOR MEI MAI II DIF OR AND
%right '='
%left '+' '-'
%left '*' '/'
%right '^'
%left ')'
%right '('

%nonassoc IMUNUS VAR IFX

%start prog
%%

prog: INICIO cod FINAL {printf("\nPROGRAMA FINALIZADO\n\n");}
    ;
cod: cod exp {eval($2);}
    | 
    ;
atrib: VAR '=' logica {$$ = newasgn($1, $3);}
    | TIPO VAR '=' logica {$$ = newvar($1, $2, $4);}
    ;
exp: atrib {$$ = $1;}
    | VAR '=' TEXTO {
        Symasgnt * tv = (Symasgnt*)malloc(sizeof(Symasgnt));
        strcpy(tv->v, $3);
        $$ = newasgn($1, (Ast*)tv);
    } 
    | TIPO VAR {$$ = newvar($1, $2, NULL);}
    | TIPO VAR '=' TEXTO {$$ = newvart($1, $2, $4);}
    | VAR ENTRADA {
        Varval * var = (Varval*)malloc(sizeof(Varval));
        strcpy(var->var, $1);
        $$ = newast('c', (Ast*)var, NULL);
    }
    //| ':' arit {$$ = $2;}
    | ':' logica {$$ = $2;}
    | IF logica '{' list '}' %prec IFX {$$ = newflow('I', $2, $4, NULL);}
	| IF logica '{' list '}' ELSE '{' list '}' {$$ = newflow('I', $2, $4, $8);}
	| WHILE logica '{' list '}' {$$ = newflow('W', $2, $4, NULL);}
    | FOR atrib ':' logica ':' atrib '{' list '}' {$$ = newflowfor('F', $2, $4, $6, $8, NULL);}
    | COMENTARIO {$$ = newast('P', NULL, NULL);}
    //| SAIDA arit { $$ = newast('P', $2,NULL);}
    | SAIDA logica { $$ = newast('P', $2,NULL);}
    | SAIDA TEXTO {
        Textoval * tv = (Textoval*)malloc(sizeof(Textoval));
        tv->nodetype = 'm';
        strcpy(tv->v, $2);
        $$ = newast('P', (Ast*)tv, NULL);
    }
    ;

list: exp {$$ = $1;}
    | list exp { $$ = newast('L', $1, $2);}
    ;
arit: SIN '(' arit ')' {$$ = newast('S',$3,NULL);}
    | COS '(' arit ')' {$$ = newast('C',$3,NULL);}
    | RAIZ '(' arit ')' {$$ = newast('R',$3,NULL);}
    | '-' arit %prec IMUNUS {$$ = newast('M',$2,NULL);}
    | '|' arit '|' {$$ = newast('A',$2,NULL);}
    | arit '+' arit1 {$$ = newast('+',$1,$3);}
    | arit '-' arit1 {$$ = newast('-',$1,$3);}
    | arit1 {$$=$1;}
    ;
arit1: arit1 '*' arit2 {$$ = newast('*',$1,$3);}
    | arit1 '/' arit2 {$$ = newast('/',$1,$3);}
    | arit1 REST arit2 {$$ = newast('%',$1,$3);}
    | arit2 {$$=$1;}
    ;
arit2: arit3 '^' arit2 {$$ = newast('^',$1,$3);}
    | arit3 {$$=$1;}
    ;
arit3: //'(' arit ')' {$$ = $2;}
     valor {$$ = $1;}
    ;
valor: INTEIRO {$$ = newint($1);}    // codigo 'k'
    | REAL {$$ = newreal($1);}      // codigo 'K'
    //| TEXTO {$$ = newtexto($1);}    // codigo 'm'
    | VAR {$$ = newValorVal($1);}   // codigo 'N'
    ;
logica: L1 MAIOR L2 {$$ = newcmp(1,$1,$3);}
    | L1 MENOR L2 {$$ = newcmp(2,$1,$3);}
    | L1 DIF L2 {$$ = newcmp(3,$1,$3);}
    | L1 II L2 {$$ = newcmp(4,$1,$3);}
    | L1 MAI L2 {$$ = newcmp(5,$1,$3);}
    | L1 MEI L2 {$$ = newcmp(6,$1,$3);}
    | L1 OR L2 {$$ = newcmp(7,$1,$3);}
    | L1 AND L2 {$$ = newcmp(8,$1,$3);}
    | L1 {$$ = $1;}
    ;
L1: L2 {$$=$1;}
    ;
L2:  '(' logica ')' {$$ = $2;}
    | arit {$$=$1;}
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
