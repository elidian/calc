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
    

#line 301 "calc_elidian.tab.c"

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
    TEXTO = 259,                   /* TEXTO  */
    VAR = 260,                     /* VAR  */
    COMENTARIO = 261,              /* COMENTARIO  */
    INTEIRO = 262,                 /* INTEIRO  */
    REAL = 263,                    /* REAL  */
    ENTRADA = 264,                 /* ENTRADA  */
    SAIDA = 265,                   /* SAIDA  */
    INICIO = 266,                  /* INICIO  */
    FINAL = 267,                   /* FINAL  */
    IF = 268,                      /* IF  */
    ELSE = 269,                    /* ELSE  */
    FOR = 270,                     /* FOR  */
    RAIZ = 271,                    /* RAIZ  */
    COS = 272,                     /* COS  */
    SIN = 273,                     /* SIN  */
    REST = 274,                    /* REST  */
    MAIOR = 275,                   /* MAIOR  */
    MENOR = 276,                   /* MENOR  */
    MEI = 277,                     /* MEI  */
    MAI = 278,                     /* MAI  */
    II = 279,                      /* II  */
    DIF = 280,                     /* DIF  */
    IMUNUS = 281                   /* IMUNUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 231 "calc_elidian.y"

    char texto[50];
    int inteiro;
    double real;
    FTYPE ftype;
    AST *a;

#line 382 "calc_elidian.tab.c"

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
  YYSYMBOL_TEXTO = 4,                      /* TEXTO  */
  YYSYMBOL_VAR = 5,                        /* VAR  */
  YYSYMBOL_COMENTARIO = 6,                 /* COMENTARIO  */
  YYSYMBOL_INTEIRO = 7,                    /* INTEIRO  */
  YYSYMBOL_REAL = 8,                       /* REAL  */
  YYSYMBOL_ENTRADA = 9,                    /* ENTRADA  */
  YYSYMBOL_SAIDA = 10,                     /* SAIDA  */
  YYSYMBOL_INICIO = 11,                    /* INICIO  */
  YYSYMBOL_FINAL = 12,                     /* FINAL  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_RAIZ = 16,                      /* RAIZ  */
  YYSYMBOL_COS = 17,                       /* COS  */
  YYSYMBOL_SIN = 18,                       /* SIN  */
  YYSYMBOL_REST = 19,                      /* REST  */
  YYSYMBOL_MAIOR = 20,                     /* MAIOR  */
  YYSYMBOL_MENOR = 21,                     /* MENOR  */
  YYSYMBOL_MEI = 22,                       /* MEI  */
  YYSYMBOL_MAI = 23,                       /* MAI  */
  YYSYMBOL_II = 24,                        /* II  */
  YYSYMBOL_DIF = 25,                       /* DIF  */
  YYSYMBOL_26_ = 26,                       /* '+'  */
  YYSYMBOL_27_ = 27,                       /* '-'  */
  YYSYMBOL_28_ = 28,                       /* '*'  */
  YYSYMBOL_29_ = 29,                       /* '/'  */
  YYSYMBOL_30_ = 30,                       /* '^'  */
  YYSYMBOL_31_ = 31,                       /* ')'  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* '|'  */
  YYSYMBOL_IMUNUS = 34,                    /* IMUNUS  */
  YYSYMBOL_35_ = 35,                       /* ':'  */
  YYSYMBOL_36_ = 36,                       /* '='  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_prog = 40,                      /* prog  */
  YYSYMBOL_cod = 41,                       /* cod  */
  YYSYMBOL_exp = 42,                       /* exp  */
  YYSYMBOL_atrib = 43,                     /* atrib  */
  YYSYMBOL_ivar = 44,                      /* ivar  */
  YYSYMBOL_ivar2 = 45,                     /* ivar2  */
  YYSYMBOL_val = 46,                       /* val  */
  YYSYMBOL_arit = 47,                      /* arit  */
  YYSYMBOL_arit1 = 48,                     /* arit1  */
  YYSYMBOL_arit2 = 49,                     /* arit2  */
  YYSYMBOL_arit3 = 50,                     /* arit3  */
  YYSYMBOL_valor = 51,                     /* valor  */
  YYSYMBOL_logica = 52,                    /* logica  */
  YYSYMBOL_L1 = 53,                        /* L1  */
  YYSYMBOL_L2 = 54,                        /* L2  */
  YYSYMBOL_saida = 55,                     /* saida  */
  YYSYMBOL_if = 56,                        /* if  */
  YYSYMBOL_for = 57                        /* for  */
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
#define YYLAST   248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


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
      32,    31,    28,    26,    37,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    35,    38,
       2,    36,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    33,     2,     2,     2,     2,     2,
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
      25,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   266,   266,   268,   269,   271,   272,   273,   306,   307,
     308,   309,   310,   311,   313,   320,   327,   334,   336,   344,
     354,   355,   356,   357,   372,   377,   382,   387,   392,   402,
     419,   436,   438,   455,   479,   499,   501,   521,   523,   524,
     526,   530,   534,   550,   552,   553,   554,   555,   556,   557,
     559,   561,   562,   572,   580,   588,   589,   591,   594,   598
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
  "\"end of file\"", "error", "\"invalid token\"", "TIPO", "TEXTO", "VAR",
  "COMENTARIO", "INTEIRO", "REAL", "ENTRADA", "SAIDA", "INICIO", "FINAL",
  "IF", "ELSE", "FOR", "RAIZ", "COS", "SIN", "REST", "MAIOR", "MENOR",
  "MEI", "MAI", "II", "DIF", "'+'", "'-'", "'*'", "'/'", "'^'", "')'",
  "'('", "'|'", "IMUNUS", "':'", "'='", "','", "';'", "$accept", "prog",
  "cod", "exp", "atrib", "ivar", "ivar2", "val", "arit", "arit1", "arit2",
  "arit3", "valor", "logica", "L1", "L2", "saida", "if", "for", YY_NULLPTR
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
     275,   276,   277,   278,   279,   280,    43,    45,    42,    47,
      94,    41,    40,   124,   281,    58,    61,    44,    59
};
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -6,   -61,    18,   143,   -61,     6,   -61,    -8,   -61,   -61,
     -61,   197,   -61,   197,   215,   -10,    17,    34,   215,   197,
     215,   197,   -61,   -61,    10,   -61,    -1,     2,   -61,     4,
     -61,    45,   142,   -61,   -61,   -61,    33,   -61,   215,   -61,
      70,    48,   -61,    64,   215,    -3,   215,   215,   215,   -61,
      28,    -2,    30,   106,   -61,    97,    12,    12,    12,    12,
      12,    12,   -61,   197,   197,   197,   197,   197,   197,   215,
      -1,   197,   197,   -61,    28,   -61,    74,   110,   146,   -61,
     -61,   -61,    72,     2,     2,   -61,   -61,   -61,   -61,    35,
     -61,   -61,   -61,   -61,   -61,   -61,    -1,   -61,   -61,   176,
      71,   -61,   -61,   -61,   230,   -61,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,   107,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     1,     0,    43,    42,    12,    40,
      41,     0,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     5,     6,    17,    52,    31,    35,    37,
      39,     0,     0,    50,    10,    11,    18,     7,     0,    42,
      53,    55,    13,     0,     0,     0,     0,     0,     0,    27,
      52,     0,     0,     8,     9,     0,     0,     0,     0,     0,
       0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
      14,     0,     0,     4,     0,     4,     0,     0,     0,    38,
      51,    28,    15,    29,    30,    34,    32,    33,    36,     0,
      44,    45,    47,    46,    48,    49,    19,    54,    56,     0,
       0,    26,    25,    24,     0,    58,     4,    59,    20,    23,
      21,    22,    16,     0,    57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   -60,   -61,   -61,   -61,   -61,   -61,   -11,    15,
     167,   -61,   -61,    -7,   -61,   132,    11,   -61,   -61
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    22,    23,    24,    25,   112,    26,    27,
      28,    29,    30,    31,    32,    33,    42,    34,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      40,    37,    89,    45,    41,     1,    43,    49,    50,    52,
      53,    36,    51,    99,    54,   100,     6,    39,     4,     9,
      10,    58,    46,    56,    57,    56,    57,    70,    38,    80,
      59,    60,    75,    74,    61,    76,    77,    78,     5,     6,
       7,     8,     9,    10,    44,    11,   113,    55,    13,    47,
      14,    15,    16,    17,    56,    57,    56,    57,    96,    79,
      40,    40,    18,    81,    41,    41,    48,    19,    20,    69,
      21,    83,    84,   105,     5,     6,     7,     8,     9,    10,
      62,    11,    97,    98,    13,    72,    14,    15,    16,    17,
     -52,   -52,   -52,   -52,   -52,   -52,    56,    57,    18,    73,
      56,    57,    82,    19,    20,   101,    21,    71,   104,   107,
       5,     6,     7,     8,     9,    10,     0,    11,     0,     0,
      13,     0,    14,    15,    16,    17,   -52,   -52,   -52,   -52,
     -52,   -52,    56,    57,    18,     0,    56,    57,     0,    19,
      20,   102,    21,     0,     0,   114,     5,     6,     7,     8,
       9,    10,     0,    11,     0,    12,    13,     0,    14,    15,
      16,    17,    63,    64,    65,    66,    67,    68,     0,     0,
      18,     0,    56,    57,     0,    19,    20,   103,    21,     5,
       6,     7,     8,     9,    10,     0,    11,     0,     0,    13,
     106,    14,    15,    16,    17,    90,    91,    92,    93,    94,
      95,     6,    39,    18,     9,    10,     0,     0,    19,    20,
       0,    21,     0,    15,    16,    17,     0,     0,     0,     6,
      39,     0,     9,    10,    18,    85,    86,    87,    88,    19,
      20,    15,    16,    17,   108,   109,     0,   110,   111,     0,
       0,     0,    18,     0,     0,     0,     0,    44,    20
};

static const yytype_int8 yycheck[] =
{
      11,     9,    62,    14,    11,    11,    13,    18,    19,    20,
      21,     5,    19,    73,    21,    75,     4,     5,     0,     7,
       8,    19,    32,    26,    27,    26,    27,    38,    36,    31,
      28,    29,    35,    44,    30,    46,    47,    48,     3,     4,
       5,     6,     7,     8,    32,    10,   106,    37,    13,    32,
      15,    16,    17,    18,    26,    27,    26,    27,    69,    31,
      71,    72,    27,    33,    71,    72,    32,    32,    33,    36,
      35,    56,    57,    38,     3,     4,     5,     6,     7,     8,
      35,    10,    71,    72,    13,    37,    15,    16,    17,    18,
      20,    21,    22,    23,    24,    25,    26,    27,    27,    35,
      26,    27,     5,    32,    33,    31,    35,    37,    36,    38,
       3,     4,     5,     6,     7,     8,    -1,    10,    -1,    -1,
      13,    -1,    15,    16,    17,    18,    20,    21,    22,    23,
      24,    25,    26,    27,    27,    -1,    26,    27,    -1,    32,
      33,    31,    35,    -1,    -1,    38,     3,     4,     5,     6,
       7,     8,    -1,    10,    -1,    12,    13,    -1,    15,    16,
      17,    18,    20,    21,    22,    23,    24,    25,    -1,    -1,
      27,    -1,    26,    27,    -1,    32,    33,    31,    35,     3,
       4,     5,     6,     7,     8,    -1,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    63,    64,    65,    66,    67,
      68,     4,     5,    27,     7,     8,    -1,    -1,    32,    33,
      -1,    35,    -1,    16,    17,    18,    -1,    -1,    -1,     4,
       5,    -1,     7,     8,    27,    58,    59,    60,    61,    32,
      33,    16,    17,    18,     4,     5,    -1,     7,     8,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    32,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    40,    41,     0,     3,     4,     5,     6,     7,
       8,    10,    12,    13,    15,    16,    17,    18,    27,    32,
      33,    35,    42,    43,    44,    45,    47,    48,    49,    50,
      51,    52,    53,    54,    56,    57,     5,     9,    36,     5,
      47,    52,    55,    52,    32,    47,    32,    32,    32,    47,
      47,    52,    47,    47,    52,    37,    26,    27,    19,    28,
      29,    30,    35,    20,    21,    22,    23,    24,    25,    36,
      47,    37,    37,    35,    47,    35,    47,    47,    47,    31,
      31,    33,     5,    48,    48,    49,    49,    49,    49,    41,
      54,    54,    54,    54,    54,    54,    47,    55,    55,    41,
      41,    31,    31,    31,    36,    38,    14,    38,     4,     5,
       7,     8,    46,    41,    38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    43,    44,    44,    44,    45,    45,
      46,    46,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    48,    48,    48,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    52,    52,    52,    52,    52,    52,
      53,    54,    54,    55,    55,    55,    55,    56,    56,    57
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     1,     1,     2,     2,     2,
       1,     1,     1,     2,     3,     3,     5,     1,     2,     4,
       1,     1,     1,     1,     4,     4,     4,     2,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     1,     1,     3,     1,     3,     7,     4,     5
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
#line 266 "calc_elidian.y"
                       {;printf("PROGRAMA FINALIZADO\n");}
#line 1506 "calc_elidian.tab.c"
    break;

  case 5: /* exp: atrib  */
#line 271 "calc_elidian.y"
           {}
#line 1512 "calc_elidian.tab.c"
    break;

  case 6: /* exp: ivar  */
#line 272 "calc_elidian.y"
           {}
#line 1518 "calc_elidian.tab.c"
    break;

  case 7: /* exp: VAR ENTRADA  */
#line 273 "calc_elidian.y"
                  {
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
            VARIAVELS *aux = pushVarVal(var0, (yyvsp[-1].texto), new);
            if (aux==NULL)
                printf("ERRO 305: Variavel %s ainda nao declarada\n", (yyvsp[-1].texto));
        } else {
            if (is_real(test)==true ){
                FTYPE new;
                new.type = 2;
                new.r = atof(test);
                VARIAVELS *aux = pushVarVal(var0, (yyvsp[-1].texto), new);
                if (aux==NULL)
                    printf("ERRO 313: Variavel %s ainda nao declarada\n", (yyvsp[-1].texto));
            } else {
                FTYPE new;
                new.type = 0;
                strcpy(new.t, test);
                VARIAVELS *aux = pushVarVal(var0, (yyvsp[-1].texto), new);
                if (aux==NULL)
                    printf("ERRO 320: Variavel %s ainda nao declarada\n", (yyvsp[-1].texto));
            }
        }
    }
#line 1556 "calc_elidian.tab.c"
    break;

  case 8: /* exp: ':' arit  */
#line 306 "calc_elidian.y"
               {printf("RESULTADO ARITMETICO: %f\n", (yyvsp[0].ftype)); }
#line 1562 "calc_elidian.tab.c"
    break;

  case 9: /* exp: ':' logica  */
#line 307 "calc_elidian.y"
                 { if ((yyvsp[0].inteiro) != 0) printf("RESULTADO LOGICA: TRUE\n"); else printf("RESULTADO LOGICA: FALSE\n"); }
#line 1568 "calc_elidian.tab.c"
    break;

  case 10: /* exp: if  */
#line 308 "calc_elidian.y"
         {}
#line 1574 "calc_elidian.tab.c"
    break;

  case 11: /* exp: for  */
#line 309 "calc_elidian.y"
          {}
#line 1580 "calc_elidian.tab.c"
    break;

  case 12: /* exp: COMENTARIO  */
#line 310 "calc_elidian.y"
                 { printf("COMENTARIO: %s\n", (yyvsp[0].texto));}
#line 1586 "calc_elidian.tab.c"
    break;

  case 13: /* exp: SAIDA saida  */
#line 311 "calc_elidian.y"
                  {printf("%s\n", (yyvsp[0].texto)); }
#line 1592 "calc_elidian.tab.c"
    break;

  case 14: /* atrib: VAR '=' arit  */
#line 313 "calc_elidian.y"
                    {
        //atribuição de variavel REAL
        VARIAVELS * aux = pushVarVal(var0, (yyvsp[-2].texto), (yyvsp[0].ftype));
        if (aux == NULL)
            printf ("ERRO 2: Variável '%s' não foi declarada\n", (yyvsp[-2].texto));
    }
#line 1603 "calc_elidian.tab.c"
    break;

  case 15: /* ivar: ivar ',' VAR  */
#line 320 "calc_elidian.y"
                   { 
        VARIAVELS * aux = srchVar(var0, (yyvsp[0].texto));
        if (aux == NULL){
            var0 = insVar(var0, (yyvsp[0].texto), (yyvsp[-2].ftype).type);
        } else
            printf ("A variável '%s' já existe.\n", (yyvsp[0].texto));
    }
#line 1615 "calc_elidian.tab.c"
    break;

  case 16: /* ivar: ivar ',' VAR '=' val  */
#line 327 "calc_elidian.y"
                           { 
        VARIAVELS * aux = srchVar(var0, (yyvsp[-2].texto));
        if (aux == NULL){
            var0 = insVarV(var0, (yyvsp[-2].texto), (yyvsp[-4].ftype).type, (yyvsp[0].ftype));
        } else
            printf ("A variável '%s' já existe.\n", (yyvsp[-2].texto));
    }
#line 1627 "calc_elidian.tab.c"
    break;

  case 17: /* ivar: ivar2  */
#line 334 "calc_elidian.y"
            {printf("TIPO: %d\n", (yyvsp[0].ftype).type);}
#line 1633 "calc_elidian.tab.c"
    break;

  case 18: /* ivar2: TIPO VAR  */
#line 336 "calc_elidian.y"
                { 
        (yyval.ftype).type = typeToInt((yyvsp[-1].texto));
        if (srchVar(var0, (yyvsp[0].texto)) == NULL){
            var0 = insVar(var0, (yyvsp[0].texto), typeToInt((yyvsp[-1].texto)));
            printf("TIPO VAR: %s\n", intToType(var0->type) );
        } else
            printf ("A variável '%s' já existe.\n", (yyvsp[0].texto));
    }
#line 1646 "calc_elidian.tab.c"
    break;

  case 19: /* ivar2: TIPO VAR '=' arit  */
#line 344 "calc_elidian.y"
                        { 
        (yyval.ftype).type = typeToInt((yyvsp[-3].texto));
        if (srchVar(var0, (yyvsp[-2].texto)) == NULL){
            var0 = insVar(var0, (yyvsp[-2].texto), typeToInt((yyvsp[-3].texto)));
            pushVarVal(var0, (yyvsp[-2].texto), (yyvsp[0].ftype));
            printf("TIPO VAR = val: %s %s\n", (yyvsp[-3].texto), (yyvsp[-2].texto) );
        } else
            printf ("A variável '%s' já existe.\n", (yyvsp[-2].texto));
    }
#line 1660 "calc_elidian.tab.c"
    break;

  case 20: /* val: TEXTO  */
#line 354 "calc_elidian.y"
           { strcpy((yyval.ftype).t, (yyvsp[0].texto)); (yyval.ftype).type = 0;}
#line 1666 "calc_elidian.tab.c"
    break;

  case 21: /* val: INTEIRO  */
#line 355 "calc_elidian.y"
              { (yyval.ftype).i = (yyvsp[0].inteiro); (yyval.ftype).type = 1;}
#line 1672 "calc_elidian.tab.c"
    break;

  case 22: /* val: REAL  */
#line 356 "calc_elidian.y"
           { (yyval.ftype).r = (yyvsp[0].real); (yyval.ftype).type = 2;}
#line 1678 "calc_elidian.tab.c"
    break;

  case 23: /* val: VAR  */
#line 357 "calc_elidian.y"
          {
        VARIAVELS * aux = srchVar(var0, (yyvsp[0].texto));
        if (aux == NULL){
            printf ("Variavel '%s' nao declarada",(yyvsp[0].texto));    
        } else {
            (yyval.ftype).type = aux->type;
            if ((yyval.ftype).type == 0)
                    strcpy((yyval.ftype).t, aux->t);
                else if ((yyval.ftype).type == 1)
                    (yyval.ftype).i = aux->i;
                    else if ((yyval.ftype).type == 2)
                        (yyval.ftype).r = aux->r;
        }
    }
#line 1697 "calc_elidian.tab.c"
    break;

  case 24: /* arit: SIN '(' arit ')'  */
#line 372 "calc_elidian.y"
                       {
                (yyval.ftype).type = 2;
                (yyval.ftype).r = sin((yyvsp[-1].ftype).r);
                printf("SIN: %f = %f\n", (yyvsp[-1].ftype).r, (yyval.ftype).r);
    }
#line 1707 "calc_elidian.tab.c"
    break;

  case 25: /* arit: COS '(' arit ')'  */
#line 377 "calc_elidian.y"
                       {
                (yyval.ftype).type = 2;
                (yyval.ftype).r = cos((yyvsp[-1].ftype).r);
                printf("COS: %f = %f\n", (yyvsp[-1].ftype).r, (yyval.ftype).r);
    }
#line 1717 "calc_elidian.tab.c"
    break;

  case 26: /* arit: RAIZ '(' arit ')'  */
#line 382 "calc_elidian.y"
                        {
                (yyval.ftype).type = 2;
                (yyval.ftype).r = sqrt((yyvsp[-1].ftype).r);
                printf("RAIZ: %f = %f\n", (yyvsp[-1].ftype).r, (yyval.ftype).r);
    }
#line 1727 "calc_elidian.tab.c"
    break;

  case 27: /* arit: '-' arit  */
#line 387 "calc_elidian.y"
                            {
                (yyval.ftype).type = 2;
                (yyval.ftype).r = -(yyvsp[0].ftype).r;
                printf("NEG: -%f = -%f\n", (yyvsp[0].ftype).r, (yyval.ftype).r);
    }
#line 1737 "calc_elidian.tab.c"
    break;

  case 28: /* arit: '|' arit '|'  */
#line 392 "calc_elidian.y"
                   {
        (yyval.ftype).type = (yyvsp[-1].ftype).type;
        if((yyvsp[-1].ftype).type == 1){
            (yyval.ftype).i = fabs((yyvsp[-1].ftype).i);
            printf("MODULO: |%d| = %d\n", (yyvsp[-1].ftype).i, (yyval.ftype).i);
        }else if((yyvsp[-1].ftype).type == 2){
            (yyval.ftype).r = fabs((yyvsp[-1].ftype).r);
            printf("MODULO: |%f| = %f\n", (yyvsp[-1].ftype).r, (yyval.ftype).r);
        }
    }
#line 1752 "calc_elidian.tab.c"
    break;

  case 29: /* arit: arit '+' arit1  */
#line 402 "calc_elidian.y"
                     {
        (yyval.ftype).type = MAX((yyvsp[-2].ftype).type, (yyvsp[0].ftype).type);
        if((yyval.ftype).type==1){
            (yyval.ftype).i = (yyvsp[-2].ftype).i + (yyvsp[0].ftype).i;
            printf("SOMA 1: = %d\n", (yyval.ftype).i);
        } else if((yyval.ftype).type==2){
                if((yyvsp[-2].ftype).type ==1 && (yyvsp[0].ftype).type ==2)
                    (yyval.ftype).r = (yyvsp[-2].ftype).i + (yyvsp[0].ftype).r; 
                else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==1)
                        (yyval.ftype).r = (yyvsp[-2].ftype).r + (yyvsp[0].ftype).i; 
                    else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==2)
                            (yyval.ftype).r = (yyvsp[-2].ftype).r + (yyvsp[0].ftype).r; 
                        else
                            printf("Variavel tipo texto\n");
                printf("SOMA 2: = %f\n", (yyval.ftype).r);
        }
    }
#line 1774 "calc_elidian.tab.c"
    break;

  case 30: /* arit: arit '-' arit1  */
#line 419 "calc_elidian.y"
                     {
        (yyval.ftype).type = MAX((yyvsp[-2].ftype).type, (yyvsp[0].ftype).type);
        if((yyval.ftype).type==1){
            (yyval.ftype).i = (yyvsp[-2].ftype).i - (yyvsp[0].ftype).i;
            printf("SUB 1: = %d\n", (yyval.ftype).i);
        } else if((yyval.ftype).type==2){
                if((yyvsp[-2].ftype).type ==1 && (yyvsp[0].ftype).type ==2)
                    (yyval.ftype).r = (yyvsp[-2].ftype).i - (yyvsp[0].ftype).r; 
                else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==1)
                        (yyval.ftype).r = (yyvsp[-2].ftype).r - (yyvsp[0].ftype).i; 
                    else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==2)
                            (yyval.ftype).r = (yyvsp[-2].ftype).r - (yyvsp[0].ftype).r; 
                        else
                            printf("Variavel tipo texto\n");
                printf("SUB 2: = %f\n", (yyval.ftype).r);
        }
    }
#line 1796 "calc_elidian.tab.c"
    break;

  case 31: /* arit: arit1  */
#line 436 "calc_elidian.y"
            {(yyval.ftype) = (yyvsp[0].ftype);}
#line 1802 "calc_elidian.tab.c"
    break;

  case 32: /* arit1: arit1 '*' arit2  */
#line 438 "calc_elidian.y"
                       {
        (yyval.ftype).type = MAX((yyvsp[-2].ftype).type, (yyvsp[0].ftype).type);
        if((yyval.ftype).type==1){
            (yyval.ftype).i = (yyvsp[-2].ftype).i * (yyvsp[0].ftype).i;
            printf("PROD 1: = %d\n", (yyval.ftype).i);
        } else if((yyval.ftype).type==2){
                if((yyvsp[-2].ftype).type ==1 && (yyvsp[0].ftype).type ==2)
                    (yyval.ftype).r = (yyvsp[-2].ftype).i * (yyvsp[0].ftype).r; 
                else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==1)
                        (yyval.ftype).r = (yyvsp[-2].ftype).r * (yyvsp[0].ftype).i; 
                    else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==2)
                            (yyval.ftype).r = (yyvsp[-2].ftype).r * (yyvsp[0].ftype).r; 
                        else
                            printf("Variavel tipo texto\n");
                printf("PROD 2: = %f\n", (yyval.ftype).r);
        }
    }
#line 1824 "calc_elidian.tab.c"
    break;

  case 33: /* arit1: arit1 '/' arit2  */
#line 455 "calc_elidian.y"
                      {
        (yyval.ftype).type = MAX((yyvsp[-2].ftype).type, (yyvsp[0].ftype).type);
        if((yyval.ftype).type==1 && ((yyvsp[-2].ftype).i % (yyvsp[0].ftype).i)==0){
            (yyval.ftype).i = (yyvsp[-2].ftype).i / (yyvsp[0].ftype).i;
            printf("DIV 1: = %d\n", (yyval.ftype).i);
        } else if((yyval.ftype).type==2 || ((yyvsp[-2].ftype).i % (yyvsp[0].ftype).i)!=0){
                (yyval.ftype).type = 2;
                if((yyvsp[-2].ftype).type ==1 && (yyvsp[0].ftype).type ==2){
                    (yyval.ftype).r = (yyvsp[-2].ftype).i / (yyvsp[0].ftype).r; 
                    printf("ops0\n");
                } else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==1){
                        (yyval.ftype).r = (yyvsp[-2].ftype).r / (yyvsp[0].ftype).i; 
                            printf("ops1\n");
                    } else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==2){
                            (yyval.ftype).r = (yyvsp[-2].ftype).r / (yyvsp[0].ftype).r; 
                            printf("ops2\n");
                        } else if((yyvsp[-2].ftype).type ==1 && (yyvsp[0].ftype).type ==1){
                                (yyval.ftype).r = (double)(yyvsp[-2].ftype).i / (yyvsp[0].ftype).i; 
                                printf("ops3\n");
                            } else
                                printf("Variavel tipo texto\n");
                printf("DIV 2: = %f\n", (yyval.ftype).r);
            }
    }
#line 1853 "calc_elidian.tab.c"
    break;

  case 34: /* arit1: arit1 REST arit2  */
#line 479 "calc_elidian.y"
                       {
        (yyval.ftype).type = MAX((yyvsp[-2].ftype).type, (yyvsp[0].ftype).type);
        if((yyval.ftype).type==1){
            (yyval.ftype).i = (yyvsp[-2].ftype).i % (yyvsp[0].ftype).i;
            printf("REST 1: = %d\n", (yyval.ftype).i);
        } else if((yyval.ftype).type==2){
                if((yyvsp[-2].ftype).type ==1 && (yyvsp[0].ftype).type ==2){
                    (yyval.ftype).r = fmod((yyvsp[-2].ftype).i, (yyvsp[0].ftype).r); 
                    printf("ops0\n");
                } else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==1){
                        (yyval.ftype).r = fmod((yyvsp[-2].ftype).r, (yyvsp[0].ftype).i); 
                        printf("ops1\n");
                    } else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==2){
                            (yyval.ftype).r = fmod((yyvsp[-2].ftype).r, (yyvsp[0].ftype).r); 
                            printf("ops2\n");
                        } else
                                printf("Variavel tipo texto\n");
                printf("REST 2: = %f\n", (yyval.ftype).r);
            }
    }
#line 1878 "calc_elidian.tab.c"
    break;

  case 35: /* arit1: arit2  */
#line 499 "calc_elidian.y"
            {(yyval.ftype) = (yyvsp[0].ftype);}
#line 1884 "calc_elidian.tab.c"
    break;

  case 36: /* arit2: arit3 '^' arit2  */
#line 501 "calc_elidian.y"
                       {
        (yyval.ftype).type = MAX((yyvsp[-2].ftype).type, (yyvsp[0].ftype).type);
        if((yyval.ftype).type==1){
            (yyval.ftype).i = pow((yyvsp[-2].ftype).i, (yyvsp[0].ftype).i);
            printf("EXPO 1: = %d\n", (yyval.ftype).i);
        } else if((yyval.ftype).type==2){
                if((yyvsp[-2].ftype).type ==1 && (yyvsp[0].ftype).type ==2){
                    (yyval.ftype).r = pow((yyvsp[-2].ftype).i, (yyvsp[0].ftype).r); 
                    printf("ops0\n");
                } else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==1){
                        (yyval.ftype).r = pow((yyvsp[-2].ftype).r, (yyvsp[0].ftype).i); 
                        printf("ops1\n");
                    } else if((yyvsp[-2].ftype).type ==2 && (yyvsp[0].ftype).type ==2){
                            (yyval.ftype).r = pow((yyvsp[-2].ftype).r, (yyvsp[0].ftype).r); 
                            printf("ops2\n");
                        } else
                            printf("Variavel tipo texto\n");
                printf("REST 2: = %f\n", (yyval.ftype).r);
            }
    }
#line 1909 "calc_elidian.tab.c"
    break;

  case 37: /* arit2: arit3  */
#line 521 "calc_elidian.y"
            {(yyval.ftype) = (yyvsp[0].ftype);}
#line 1915 "calc_elidian.tab.c"
    break;

  case 38: /* arit3: '(' arit ')'  */
#line 523 "calc_elidian.y"
                    {(yyval.ftype)=(yyvsp[-1].ftype);}
#line 1921 "calc_elidian.tab.c"
    break;

  case 39: /* arit3: valor  */
#line 524 "calc_elidian.y"
            {(yyval.ftype)=(yyvsp[0].ftype);}
#line 1927 "calc_elidian.tab.c"
    break;

  case 40: /* valor: INTEIRO  */
#line 526 "calc_elidian.y"
               {
        (yyval.ftype).type = 1;
        (yyval.ftype).i = (yyvsp[0].inteiro);
    }
#line 1936 "calc_elidian.tab.c"
    break;

  case 41: /* valor: REAL  */
#line 530 "calc_elidian.y"
           {
        (yyval.ftype).type = 2;
        (yyval.ftype).r = (yyvsp[0].real);
    }
#line 1945 "calc_elidian.tab.c"
    break;

  case 42: /* valor: VAR  */
#line 534 "calc_elidian.y"
          {
        VARIAVELS * aux = srchVar(var0, (yyvsp[0].texto));
        if (aux == NULL){
            printf ("ERRO: Variavel '%s' nao foi declarada.\n",(yyvsp[0].texto));
            (yyval.ftype).r = 0;
            (yyval.ftype).i = 0;
            strcpy((yyval.ftype).t, "");
        } else{
            (yyval.ftype).type = aux->type;
            switch(aux->type){
                case 0: strcpy((yyval.ftype).t, aux->t); break;
                case 1: (yyval.ftype).i = aux->i; break;
                case 2: (yyval.ftype).r = aux->r; break;
            }
        }
    }
#line 1966 "calc_elidian.tab.c"
    break;

  case 43: /* valor: TEXTO  */
#line 550 "calc_elidian.y"
            { strcpy((yyval.ftype).t, (yyvsp[0].texto)); (yyval.ftype).type = 0;}
#line 1972 "calc_elidian.tab.c"
    break;

  case 44: /* logica: L1 MAIOR L2  */
#line 552 "calc_elidian.y"
                    {if ((yyvsp[-2].real) > (yyvsp[0].real)) (yyval.inteiro)=1; else (yyval.inteiro)=0; }
#line 1978 "calc_elidian.tab.c"
    break;

  case 45: /* logica: L1 MENOR L2  */
#line 553 "calc_elidian.y"
                  {if ((yyvsp[-2].real) < (yyvsp[0].real)) (yyval.inteiro)=1; else (yyval.inteiro)=0; }
#line 1984 "calc_elidian.tab.c"
    break;

  case 46: /* logica: L1 MAI L2  */
#line 554 "calc_elidian.y"
                {if ((yyvsp[-2].real) >= (yyvsp[0].real)) (yyval.inteiro)=1; else (yyval.inteiro)=0; }
#line 1990 "calc_elidian.tab.c"
    break;

  case 47: /* logica: L1 MEI L2  */
#line 555 "calc_elidian.y"
                {if ((yyvsp[-2].real) <= (yyvsp[0].real)) (yyval.inteiro)=1; else (yyval.inteiro)=0; }
#line 1996 "calc_elidian.tab.c"
    break;

  case 48: /* logica: L1 II L2  */
#line 556 "calc_elidian.y"
               {if ((yyvsp[-2].real) == (yyvsp[0].real)) (yyval.inteiro)=1; else (yyval.inteiro)=0; }
#line 2002 "calc_elidian.tab.c"
    break;

  case 49: /* logica: L1 DIF L2  */
#line 557 "calc_elidian.y"
                {if ((yyvsp[-2].real) != (yyvsp[0].real)) (yyval.inteiro)=1; else (yyval.inteiro)=0; }
#line 2008 "calc_elidian.tab.c"
    break;

  case 50: /* L1: L2  */
#line 559 "calc_elidian.y"
       {(yyval.real)=(yyvsp[0].real); }
#line 2014 "calc_elidian.tab.c"
    break;

  case 51: /* L2: '(' logica ')'  */
#line 561 "calc_elidian.y"
                   {(yyval.real)=(yyvsp[-1].inteiro); }
#line 2020 "calc_elidian.tab.c"
    break;

  case 52: /* L2: arit  */
#line 562 "calc_elidian.y"
           {
        if((yyvsp[0].ftype).type==0)
            (yyval.real) = atof((yyvsp[0].ftype).t);
        else if((yyvsp[0].ftype).type==1)
                (yyval.real) = (double)(yyvsp[0].ftype).i;
            else if((yyvsp[0].ftype).type==2)
                    (yyval.real) = (yyvsp[0].ftype).r;
    }
#line 2033 "calc_elidian.tab.c"
    break;

  case 53: /* saida: arit  */
#line 572 "calc_elidian.y"
            {
        if((yyvsp[0].ftype).type==0)
            sprintf((yyval.texto), "%s", (yyvsp[0].ftype).t);
        else if((yyvsp[0].ftype).type==1)
                sprintf((yyval.texto), "%d", (yyvsp[0].ftype).i);
            else if((yyvsp[0].ftype).type==2)
                    sprintf((yyval.texto), "%f", (yyvsp[0].ftype).r);
    }
#line 2046 "calc_elidian.tab.c"
    break;

  case 54: /* saida: arit ',' saida  */
#line 580 "calc_elidian.y"
                     {
        if((yyvsp[-2].ftype).type==0)
            sprintf((yyval.texto), "%s %s", (yyvsp[-2].ftype).t, (yyvsp[0].texto));
        else if((yyvsp[-2].ftype).type==1)
                sprintf((yyval.texto), "%d %s", (yyvsp[-2].ftype).i, (yyvsp[0].texto));
            else if((yyvsp[-2].ftype).type==2)
                    sprintf((yyval.texto), "%f %s", (yyvsp[-2].ftype).r, (yyvsp[0].texto));
    }
#line 2059 "calc_elidian.tab.c"
    break;

  case 55: /* saida: logica  */
#line 588 "calc_elidian.y"
             {sprintf((yyval.texto), "%d", (yyvsp[0].inteiro));}
#line 2065 "calc_elidian.tab.c"
    break;

  case 56: /* saida: logica ',' saida  */
#line 589 "calc_elidian.y"
                       {sprintf((yyval.texto), "%d %s", (yyvsp[-2].inteiro), (yyvsp[0].texto));}
#line 2071 "calc_elidian.tab.c"
    break;

  case 57: /* if: IF logica ':' cod ELSE cod ';'  */
#line 591 "calc_elidian.y"
                                   {
       
    }
#line 2079 "calc_elidian.tab.c"
    break;

  case 58: /* if: logica ':' cod ';'  */
#line 594 "calc_elidian.y"
                         {
      
    }
#line 2087 "calc_elidian.tab.c"
    break;

  case 59: /* for: FOR arit ':' cod ';'  */
#line 598 "calc_elidian.y"
                          {printf("FOR CLOSE\n"); }
#line 2093 "calc_elidian.tab.c"
    break;


#line 2097 "calc_elidian.tab.c"

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

#line 601 "calc_elidian.y"


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
