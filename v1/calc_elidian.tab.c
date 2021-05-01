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

    typedef struct variavels {
		char name[50];
        int type; // string se 0, int se 1, double se 2
        char tvalue[100];
        int ivalue;
        double rvalue;
		struct variavels * prox;
	} VARIAVELS;

    typedef struct vars {
		char name[50];
        double value;
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

#line 169 "calc_elidian.tab.c"

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
    TIPO_REAL = 259,               /* TIPO_REAL  */
    TIPO_TEXTO = 260,              /* TIPO_TEXTO  */
    INTEIRO = 261,                 /* INTEIRO  */
    REAL = 262,                    /* REAL  */
    TEXTO = 263,                   /* TEXTO  */
    ENTRADA = 264,                 /* ENTRADA  */
    SAIDA = 265,                   /* SAIDA  */
    INICIO = 266,                  /* INICIO  */
    FINAL = 267,                   /* FINAL  */
    IF = 268,                      /* IF  */
    ELSE = 269,                    /* ELSE  */
    FOR = 270,                     /* FOR  */
    VAR = 271,                     /* VAR  */
    OPV = 272,                     /* OPV  */
    COMENTARIO = 273,              /* COMENTARIO  */
    RAIZ = 274,                    /* RAIZ  */
    COS = 275,                     /* COS  */
    SIN = 276,                     /* SIN  */
    REST = 277,                    /* REST  */
    MAIOR = 278,                   /* MAIOR  */
    MENOR = 279,                   /* MENOR  */
    MEI = 280,                     /* MEI  */
    MAI = 281,                     /* MAI  */
    II = 282,                      /* II  */
    DIF = 283,                     /* DIF  */
    IMUNUS = 284                   /* IMUNUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 99 "calc_elidian.y"

    char texto[50];
    int inteiro;
    double real;

#line 251 "calc_elidian.tab.c"

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
  YYSYMBOL_TIPO_REAL = 4,                  /* TIPO_REAL  */
  YYSYMBOL_TIPO_TEXTO = 5,                 /* TIPO_TEXTO  */
  YYSYMBOL_INTEIRO = 6,                    /* INTEIRO  */
  YYSYMBOL_REAL = 7,                       /* REAL  */
  YYSYMBOL_TEXTO = 8,                      /* TEXTO  */
  YYSYMBOL_ENTRADA = 9,                    /* ENTRADA  */
  YYSYMBOL_SAIDA = 10,                     /* SAIDA  */
  YYSYMBOL_INICIO = 11,                    /* INICIO  */
  YYSYMBOL_FINAL = 12,                     /* FINAL  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_VAR = 16,                       /* VAR  */
  YYSYMBOL_OPV = 17,                       /* OPV  */
  YYSYMBOL_COMENTARIO = 18,                /* COMENTARIO  */
  YYSYMBOL_RAIZ = 19,                      /* RAIZ  */
  YYSYMBOL_COS = 20,                       /* COS  */
  YYSYMBOL_SIN = 21,                       /* SIN  */
  YYSYMBOL_REST = 22,                      /* REST  */
  YYSYMBOL_MAIOR = 23,                     /* MAIOR  */
  YYSYMBOL_MENOR = 24,                     /* MENOR  */
  YYSYMBOL_MEI = 25,                       /* MEI  */
  YYSYMBOL_MAI = 26,                       /* MAI  */
  YYSYMBOL_II = 27,                        /* II  */
  YYSYMBOL_DIF = 28,                       /* DIF  */
  YYSYMBOL_29_ = 29,                       /* '+'  */
  YYSYMBOL_30_ = 30,                       /* '-'  */
  YYSYMBOL_31_ = 31,                       /* '*'  */
  YYSYMBOL_32_ = 32,                       /* '/'  */
  YYSYMBOL_33_ = 33,                       /* '^'  */
  YYSYMBOL_34_ = 34,                       /* ')'  */
  YYSYMBOL_35_ = 35,                       /* '('  */
  YYSYMBOL_36_ = 36,                       /* '|'  */
  YYSYMBOL_IMUNUS = 37,                    /* IMUNUS  */
  YYSYMBOL_38_ = 38,                       /* '='  */
  YYSYMBOL_39_ = 39,                       /* ':'  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_prog = 43,                      /* prog  */
  YYSYMBOL_cod = 44,                       /* cod  */
  YYSYMBOL_exp = 45,                       /* exp  */
  YYSYMBOL_vart = 46,                      /* vart  */
  YYSYMBOL_vart1 = 47,                     /* vart1  */
  YYSYMBOL_var = 48,                       /* var  */
  YYSYMBOL_var1 = 49,                      /* var1  */
  YYSYMBOL_arit = 50,                      /* arit  */
  YYSYMBOL_arit1 = 51,                     /* arit1  */
  YYSYMBOL_arit2 = 52,                     /* arit2  */
  YYSYMBOL_arit3 = 53,                     /* arit3  */
  YYSYMBOL_valor = 54,                     /* valor  */
  YYSYMBOL_logica = 55,                    /* logica  */
  YYSYMBOL_L1 = 56,                        /* L1  */
  YYSYMBOL_L2 = 57,                        /* L2  */
  YYSYMBOL_saida = 58,                     /* saida  */
  YYSYMBOL_if = 59,                        /* if  */
  YYSYMBOL_for = 60                        /* for  */
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
#define YYLAST   199

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  123

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


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
      35,    34,    31,    29,    40,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    41,
       2,    38,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    36,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   143,   143,   145,   146,   148,   157,   166,   186,   187,
     188,   189,   223,   224,   225,   226,   227,   230,   232,   233,
     235,   244,   260,   287,   288,   290,   299,   316,   320,   324,
     328,   332,   336,   340,   344,   346,   350,   354,   358,   360,
     364,   366,   367,   369,   370,   371,   390,   391,   392,   393,
     394,   395,   397,   399,   400,   403,   409,   410,   411,   412,
     427,   429,   430,   432
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
  "\"end of file\"", "error", "\"invalid token\"", "TIPO", "TIPO_REAL",
  "TIPO_TEXTO", "INTEIRO", "REAL", "TEXTO", "ENTRADA", "SAIDA", "INICIO",
  "FINAL", "IF", "ELSE", "FOR", "VAR", "OPV", "COMENTARIO", "RAIZ", "COS",
  "SIN", "REST", "MAIOR", "MENOR", "MEI", "MAI", "II", "DIF", "'+'", "'-'",
  "'*'", "'/'", "'^'", "')'", "'('", "'|'", "IMUNUS", "'='", "':'", "','",
  "';'", "$accept", "prog", "cod", "exp", "vart", "vart1", "var", "var1",
  "arit", "arit1", "arit2", "arit3", "valor", "logica", "L1", "L2",
  "saida", "if", "for", YY_NULLPTR
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
     275,   276,   277,   278,   279,   280,   281,   282,   283,    43,
      45,    42,    47,    94,    41,    40,   124,   284,    61,    58,
      44,    59
};
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-55)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,   -73,    15,    84,   -73,    27,    27,    31,    97,   -73,
     136,   143,     7,   -73,   136,   -73,    11,    13,   -73,    13,
      19,    20,   -73,   -73,   -73,    22,   -73,    43,    33,    39,
      42,   143,   143,   143,   -19,    48,   -73,    58,   -73,   -73,
     136,   -12,    54,   165,   -73,   -73,    46,   -73,   -73,   118,
     157,   -73,   143,    27,     5,    31,    97,    55,   143,   143,
     143,   -73,    81,   -10,    -2,    -2,    97,    -2,    -2,    -2,
      -2,    81,    64,   -73,   136,   136,   136,   136,   136,   136,
     -73,   -73,    85,   -12,   -12,   -73,   -73,    90,   -73,   -73,
      97,   111,   117,   131,   -73,   -73,    48,    48,   -73,   -73,
     -73,   -73,   -73,   -73,    24,   -73,   -73,   -73,   -73,   -73,
     -73,    51,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,    68,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     1,     0,     0,     0,     0,     2,
       0,     0,     0,    16,     0,     3,    25,     8,    24,     9,
      20,    10,    19,    43,    44,    55,    45,     0,     0,     0,
       0,     0,     0,     0,    57,    34,    38,    40,    42,    17,
       0,    54,     0,     0,    52,    14,     0,    15,    11,     0,
      12,    13,     0,     0,     0,     0,     0,    59,     0,     0,
       0,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,     0,     4,     0,     0,     0,     0,     0,     0,
       4,     6,     0,     5,    26,    23,    21,     0,    18,    56,
       0,     0,     0,     0,    41,    31,    32,    33,    58,    37,
      35,    36,    39,    53,     0,    46,    47,    49,    48,    50,
      51,     0,     7,    22,    60,    29,    28,    27,     4,    62,
      63,     0,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,   -73,   -72,   -73,   -73,    53,   106,    75,    -8,   -34,
      52,   -73,   -73,    -5,   -73,   120,   -54,   -73,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    15,    21,    22,    17,    18,    41,    35,
      36,    37,    38,    42,    43,    44,    39,    45,    47
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      34,   104,    89,    46,    23,    24,    50,     1,   111,    51,
      64,    65,    98,    86,    26,     4,    48,    64,    65,    64,
      65,    66,    87,    61,    62,    63,    95,     5,     6,     7,
      96,    97,    71,    32,     8,    72,   114,    10,   118,    11,
      12,    83,    13,    16,    84,    49,   121,    20,    34,    52,
      91,    92,    93,    53,     5,     6,     7,    54,    34,    57,
      55,     8,    56,    14,    10,   119,    11,    12,    58,    13,
      67,     5,     6,     7,    59,    64,    65,    60,     8,    68,
      69,    10,    34,    11,    12,    80,    13,     5,     6,     7,
      14,    70,   120,    73,     8,    90,     9,    10,   103,    11,
      12,   112,    13,    23,    24,    25,   113,    14,    88,   122,
      64,    65,    19,    26,    27,    94,    28,    29,    30,    99,
     100,   101,   102,    14,    23,    24,    81,    31,    85,     0,
       0,     0,    32,    33,    26,    82,     0,    28,    29,    30,
      64,    65,    23,    24,     0,   115,    64,    65,    31,    23,
      24,   116,    26,    32,    33,    28,    29,    30,     0,    26,
      64,    65,    28,    29,    30,   117,    31,     0,     0,     0,
       0,    40,    33,    31,     0,     0,     0,     0,    32,    33,
     -54,   -54,   -54,   -54,   -54,   -54,    64,    65,    74,    75,
      76,    77,    78,    79,   105,   106,   107,   108,   109,   110
};

static const yytype_int8 yycheck[] =
{
       8,    73,    56,    11,     6,     7,    14,    11,    80,    14,
      29,    30,    66,     8,    16,     0,     9,    29,    30,    29,
      30,    40,    17,    31,    32,    33,    36,     3,     4,     5,
      64,    65,    40,    35,    10,    40,    90,    13,    14,    15,
      16,    49,    18,    16,    52,    38,   118,    16,    56,    38,
      58,    59,    60,    40,     3,     4,     5,    38,    66,    16,
      40,    10,    40,    39,    13,    41,    15,    16,    35,    18,
      22,     3,     4,     5,    35,    29,    30,    35,    10,    31,
      32,    13,    90,    15,    16,    39,    18,     3,     4,     5,
      39,    33,    41,    39,    10,    40,    12,    13,    34,    15,
      16,    16,    18,     6,     7,     8,    16,    39,    55,    41,
      29,    30,     6,    16,    17,    34,    19,    20,    21,    67,
      68,    69,    70,    39,     6,     7,     8,    30,    53,    -1,
      -1,    -1,    35,    36,    16,    17,    -1,    19,    20,    21,
      29,    30,     6,     7,    -1,    34,    29,    30,    30,     6,
       7,    34,    16,    35,    36,    19,    20,    21,    -1,    16,
      29,    30,    19,    20,    21,    34,    30,    -1,    -1,    -1,
      -1,    35,    36,    30,    -1,    -1,    -1,    -1,    35,    36,
      23,    24,    25,    26,    27,    28,    29,    30,    23,    24,
      25,    26,    27,    28,    74,    75,    76,    77,    78,    79
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    43,    44,     0,     3,     4,     5,    10,    12,
      13,    15,    16,    18,    39,    45,    16,    48,    49,    48,
      16,    46,    47,     6,     7,     8,    16,    17,    19,    20,
      21,    30,    35,    36,    50,    51,    52,    53,    54,    58,
      35,    50,    55,    56,    57,    59,    50,    60,     9,    38,
      50,    55,    38,    40,    38,    40,    40,    16,    35,    35,
      35,    50,    50,    50,    29,    30,    40,    22,    31,    32,
      33,    50,    55,    39,    23,    24,    25,    26,    27,    28,
      39,     8,    17,    50,    50,    49,     8,    17,    47,    58,
      40,    50,    50,    50,    34,    36,    51,    51,    58,    52,
      52,    52,    52,    34,    44,    57,    57,    57,    57,    57,
      57,    44,    16,    16,    58,    34,    34,    34,    14,    41,
      41,    44,    41
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    46,    46,
      47,    47,    47,    48,    48,    49,    49,    50,    50,    50,
      50,    50,    50,    50,    50,    51,    51,    51,    51,    52,
      52,    53,    53,    54,    54,    54,    55,    55,    55,    55,
      55,    55,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    59,    59,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     3,     3,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     1,
       1,     3,     4,     3,     1,     1,     3,     4,     4,     4,
       2,     3,     3,     3,     1,     3,     3,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     1,     1,     3,     1,     3,     2,
       4,     6,     4,     4
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
#line 143 "calc_elidian.y"
                       {;printf("PROGRAMA FINALIZADO\n");}
#line 1376 "calc_elidian.tab.c"
    break;

  case 5: /* exp: VAR '=' arit  */
#line 148 "calc_elidian.y"
                  {
        //atribuição de variavel REAL
        VARS * aux = srch(rvar, (yyvsp[-2].texto));
        if (aux == NULL)
            printf ("Variável '%s' não foi declarada\n", (yyvsp[-2].texto));
        else {
            aux->value = (yyvsp[0].real);
        }
    }
#line 1390 "calc_elidian.tab.c"
    break;

  case 6: /* exp: VAR '=' TEXTO  */
#line 157 "calc_elidian.y"
                    {
        //atribuição de variavel TEXTO
        VARTS * aux = srcht(tvar, (yyvsp[-2].texto));
        if (aux == NULL)
            printf ("Variável '%s' não foi declarada\n", (yyvsp[-2].texto));
        else {
            gets(aux->value);
        }
    }
#line 1404 "calc_elidian.tab.c"
    break;

  case 7: /* exp: VAR '=' OPV VAR  */
#line 166 "calc_elidian.y"
                      {
        //atribuição de variavel TEXTO
        VARTS * aux = srcht(tvar, (yyvsp[-3].texto));
        if (aux == NULL)
            printf ("Variável '%s' não foi declarada.\n", (yyvsp[-3].texto));
        else {
            VARTS * aux2 = srcht(tvar, (yyvsp[0].texto));
            if (aux2 == NULL){
                VARS * aux3 = srch(rvar, (yyvsp[0].texto));
                if(aux3 == NULL)
                    printf ("Variavel '%s' nao foi declarada\n", (yyvsp[0].texto));
                else
                    sprintf(aux->value, "%f", aux3->value);
            }
            else {
                //se for variavel texto
                strcpy(aux->value, aux2->value);
            }
        }
    }
#line 1429 "calc_elidian.tab.c"
    break;

  case 8: /* exp: TIPO var  */
#line 186 "calc_elidian.y"
               {printf("tipo: %s %s\n", (yyvsp[-1].texto), (yyvsp[0].texto)); }
#line 1435 "calc_elidian.tab.c"
    break;

  case 9: /* exp: TIPO_REAL var  */
#line 187 "calc_elidian.y"
                    {printf("tipo real: %s %s\n", (yyvsp[-1].texto), (yyvsp[0].texto)); }
#line 1441 "calc_elidian.tab.c"
    break;

  case 10: /* exp: TIPO_TEXTO vart  */
#line 188 "calc_elidian.y"
                      {printf("tipo texto: %s %s\n", (yyvsp[-1].texto), (yyvsp[0].texto)); }
#line 1447 "calc_elidian.tab.c"
    break;

  case 11: /* exp: VAR ENTRADA  */
#line 189 "calc_elidian.y"
                  {
        VARS * aux = srch(rvar, (yyvsp[-1].texto));
        if (aux == NULL){
            //se nao existe variavel declarada real
            VARTS * aux2 = srcht(tvar, (yyvsp[-1].texto));
            if (aux2 == NULL){
                //se tbm nao existe variavel declarada texto
                printf ("Variavel '%s' nao foi declarada\n", (yyvsp[-1].texto));
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
                    printf ("Valor '%s' deve ser real\n", (yyvsp[-1].texto));
                
            }while( is_real(test)==false );
            
            aux->value = atof(test);
        }
    }
#line 1486 "calc_elidian.tab.c"
    break;

  case 12: /* exp: ':' arit  */
#line 223 "calc_elidian.y"
               {printf("RESULTADO ARITMETICO: %f\n", (yyvsp[0].real)); }
#line 1492 "calc_elidian.tab.c"
    break;

  case 13: /* exp: ':' logica  */
#line 224 "calc_elidian.y"
                 { if ((yyvsp[0].real) != 0) printf("RESULTADO LOGICA: TRUE\n"); else printf("RESULTADO LOGICA: FALSE\n"); }
#line 1498 "calc_elidian.tab.c"
    break;

  case 14: /* exp: IF if  */
#line 225 "calc_elidian.y"
            {}
#line 1504 "calc_elidian.tab.c"
    break;

  case 15: /* exp: FOR for  */
#line 226 "calc_elidian.y"
              {}
#line 1510 "calc_elidian.tab.c"
    break;

  case 16: /* exp: COMENTARIO  */
#line 227 "calc_elidian.y"
                 {
        printf("COMENTARIO: %s\n", (yyvsp[0].texto));
    }
#line 1518 "calc_elidian.tab.c"
    break;

  case 17: /* exp: SAIDA saida  */
#line 230 "calc_elidian.y"
                  {printf("%s\n", (yyvsp[0].texto)); }
#line 1524 "calc_elidian.tab.c"
    break;

  case 18: /* vart: vart ',' vart1  */
#line 232 "calc_elidian.y"
                     {sprintf((yyval.texto), "%s, %s", (yyvsp[-2].texto), (yyvsp[0].texto)); }
#line 1530 "calc_elidian.tab.c"
    break;

  case 19: /* vart: vart1  */
#line 233 "calc_elidian.y"
            {sprintf((yyval.texto), "%s", (yyvsp[0].texto)); }
#line 1536 "calc_elidian.tab.c"
    break;

  case 20: /* vart1: VAR  */
#line 235 "calc_elidian.y"
           {
        VARTS * aux = srcht(tvar, (yyvsp[0].texto));
        if (aux == NULL){
            tvar = inst(tvar, (yyvsp[0].texto));
            sprintf((yyval.texto), "%s", (yyvsp[0].texto));
        }
        else
            printf ("A variável '%s' já existe.\n", (yyvsp[0].texto));
    }
#line 1550 "calc_elidian.tab.c"
    break;

  case 21: /* vart1: VAR '=' TEXTO  */
#line 244 "calc_elidian.y"
                    {
        VARTS * aux = srcht(tvar, (yyvsp[-2].texto));
        if (aux == NULL){
            tvar = inst(tvar, (yyvsp[-2].texto));
            
            VARTS * aux2 = srcht(tvar, (yyvsp[-2].texto));
            if (aux2 == NULL)
                printf ("Variavel '%s' nao foi declarada corretamente.\n", (yyvsp[-2].texto));
            else {
                strcpy(aux2->value, (yyvsp[0].texto));
                sprintf((yyval.texto), "%s = %s", (yyvsp[-2].texto), (yyvsp[0].texto));
            }
        }
        else
            printf ("A variavel '%s' ja existe.\n", (yyvsp[-2].texto));
    }
#line 1571 "calc_elidian.tab.c"
    break;

  case 22: /* vart1: VAR '=' OPV VAR  */
#line 260 "calc_elidian.y"
                      {
        VARTS * aux = srcht(tvar, (yyvsp[-3].texto));
        if (aux == NULL){
            tvar = inst(tvar, (yyvsp[-3].texto));
            
            VARTS * aux2 = srcht(tvar, (yyvsp[-3].texto)); //nova variavel a ser atribuida valor
            if (aux2 == NULL)
                printf ("Variavel '%s' nao foi declarada\n", (yyvsp[-3].texto));
            else {
                VARTS * aux3 = srcht(tvar, (yyvsp[0].texto));
                if (aux3 == NULL){
                    VARS * aux4 = srch(rvar, (yyvsp[0].texto));
                    if(aux4 == NULL)
                        printf ("Variavel '%s' nao foi declarada\n", (yyvsp[0].texto));
                    else
                        sprintf(aux2->value, "%f", aux4->value);
                }
                else {
                    strcpy(aux2->value, aux3->value);
                    sprintf((yyval.texto), "%s = %s = %s", (yyvsp[-3].texto), (yyvsp[0].texto), aux2->value);
                }
            }
        }
        else
            printf ("A variavel '%s' ja existe.\n", (yyvsp[-3].texto));
    }
#line 1602 "calc_elidian.tab.c"
    break;

  case 23: /* var: var ',' var1  */
#line 287 "calc_elidian.y"
                  {sprintf((yyval.texto), "%s, %s", (yyvsp[-2].texto), (yyvsp[0].texto)); }
#line 1608 "calc_elidian.tab.c"
    break;

  case 24: /* var: var1  */
#line 288 "calc_elidian.y"
           {sprintf((yyval.texto), "%s", (yyvsp[0].texto)); }
#line 1614 "calc_elidian.tab.c"
    break;

  case 25: /* var1: VAR  */
#line 290 "calc_elidian.y"
          {
        VARS * aux = srch(rvar, (yyvsp[0].texto));
        if (aux == NULL){
            rvar = ins(rvar, (yyvsp[0].texto));
            //sprintf($$, "%s", $1);
        }
        else
            printf ("A variável '%s' já existe.\n", (yyvsp[0].texto));
    }
#line 1628 "calc_elidian.tab.c"
    break;

  case 26: /* var1: VAR '=' arit  */
#line 299 "calc_elidian.y"
                   {
        VARS * aux = srch(rvar, (yyvsp[-2].texto));
        if (aux == NULL){
            rvar = ins(rvar, (yyvsp[-2].texto));
            
            VARS * aux2 = srch(rvar, (yyvsp[-2].texto));
            if (aux2 == NULL)
                printf ("Variavel '%s' nao foi declarada ou nao eh tipo real.\n", (yyvsp[-2].texto));
            else {
                aux2->value = (yyvsp[0].real);
                //sprintf($$, "%s = %f", $1, $3);
            }
        }
        else
            printf ("A variavel '%s' ja existe.\n", (yyvsp[-2].texto));
    }
#line 1649 "calc_elidian.tab.c"
    break;

  case 27: /* arit: SIN '(' arit ')'  */
#line 316 "calc_elidian.y"
                       {
                (yyval.real) = sin((yyvsp[-1].real));
                printf("SIN: %f = %f\n", (yyvsp[-1].real), (yyval.real));
    }
#line 1658 "calc_elidian.tab.c"
    break;

  case 28: /* arit: COS '(' arit ')'  */
#line 320 "calc_elidian.y"
                       {
                (yyval.real) = cos((yyvsp[-1].real));
                printf("COS: %f = %f\n", (yyvsp[-1].real), (yyval.real));
    }
#line 1667 "calc_elidian.tab.c"
    break;

  case 29: /* arit: RAIZ '(' arit ')'  */
#line 324 "calc_elidian.y"
                        {
                (yyval.real) = sqrt((yyvsp[-1].real));
                printf("RAIZ: %f = %f\n", (yyvsp[-1].real), (yyval.real));
    }
#line 1676 "calc_elidian.tab.c"
    break;

  case 30: /* arit: '-' arit  */
#line 328 "calc_elidian.y"
                            {
                (yyval.real) = -(yyvsp[0].real);
                printf("NEG: -%f = -%f\n", (yyvsp[0].real), (yyval.real));
    }
#line 1685 "calc_elidian.tab.c"
    break;

  case 31: /* arit: '|' arit '|'  */
#line 332 "calc_elidian.y"
                   {
                (yyval.real) = fabs((yyvsp[-1].real));
                printf("MODULO: |%f| = %f\n", (yyvsp[-1].real), (yyval.real));
    }
#line 1694 "calc_elidian.tab.c"
    break;

  case 32: /* arit: arit '+' arit1  */
#line 336 "calc_elidian.y"
                     {
                (yyval.real) = (yyvsp[-2].real) + (yyvsp[0].real);
                printf("SOMA: %f + %f = %f\n", (yyvsp[-2].real), (yyvsp[0].real), (yyval.real));
    }
#line 1703 "calc_elidian.tab.c"
    break;

  case 33: /* arit: arit '-' arit1  */
#line 340 "calc_elidian.y"
                     {
                (yyval.real) = (yyvsp[-2].real) - (yyvsp[0].real);
                printf("SUB: %f - %f = %f\n", (yyvsp[-2].real), (yyvsp[0].real), (yyval.real));
    }
#line 1712 "calc_elidian.tab.c"
    break;

  case 35: /* arit1: arit1 '*' arit2  */
#line 346 "calc_elidian.y"
                       {
                (yyval.real) = (yyvsp[-2].real) * (yyvsp[0].real);
                printf("PROD: %f * %f = %f\n", (yyvsp[-2].real), (yyvsp[0].real), (yyval.real));
    }
#line 1721 "calc_elidian.tab.c"
    break;

  case 36: /* arit1: arit1 '/' arit2  */
#line 350 "calc_elidian.y"
                      {
                (yyval.real) = (yyvsp[-2].real) / (yyvsp[0].real);
                printf("DIV: %f / %f = %f\n", (yyvsp[-2].real), (yyvsp[0].real), (yyval.real));
    }
#line 1730 "calc_elidian.tab.c"
    break;

  case 37: /* arit1: arit1 REST arit2  */
#line 354 "calc_elidian.y"
                       {
                (yyval.real) = remainder((yyvsp[-2].real), (yyvsp[0].real));
                printf("RESTO: %f / %f resto %f\n", (yyvsp[-2].real), (yyvsp[0].real), (yyval.real));
    }
#line 1739 "calc_elidian.tab.c"
    break;

  case 39: /* arit2: arit3 '^' arit2  */
#line 360 "calc_elidian.y"
                       {
                (yyval.real) = pow((yyvsp[-2].real), (yyvsp[0].real));
                printf("EXPO: %f ^ %f = %f\n", (yyvsp[-2].real), (yyvsp[0].real), (yyval.real));
    }
#line 1748 "calc_elidian.tab.c"
    break;

  case 41: /* arit3: '(' arit ')'  */
#line 366 "calc_elidian.y"
                    {}
#line 1754 "calc_elidian.tab.c"
    break;

  case 42: /* arit3: valor  */
#line 367 "calc_elidian.y"
            {(yyval.real) = (yyvsp[0].real); }
#line 1760 "calc_elidian.tab.c"
    break;

  case 43: /* valor: INTEIRO  */
#line 369 "calc_elidian.y"
               { (yyval.real) = (yyvsp[0].inteiro);}
#line 1766 "calc_elidian.tab.c"
    break;

  case 44: /* valor: REAL  */
#line 370 "calc_elidian.y"
           { (yyval.real) = (yyvsp[0].real);}
#line 1772 "calc_elidian.tab.c"
    break;

  case 45: /* valor: VAR  */
#line 371 "calc_elidian.y"
          {
        VARS * aux = srch(rvar, (yyvsp[0].texto));
        if (aux == NULL){
            VARTS * aux2 = srcht(tvar, (yyvsp[0].texto));
            if (aux2 == NULL){
                printf ("Variavel '%s' nao foi declarada.\n",(yyvsp[0].texto));
                (yyval.real) = 0;
            }
            else{
                printf ("Variavel '%s' eh tipo texto.\nUtilize o modificador '&' antes das variaveis tipo texto",(yyvsp[0].texto));
                (yyval.real) = 0;
            }
        }
        else{
            (yyval.real) = aux->value;
            //printf("VAR->value = %f\n", $$);
        }
    }
#line 1795 "calc_elidian.tab.c"
    break;

  case 46: /* logica: L1 MAIOR L2  */
#line 390 "calc_elidian.y"
                    {if ((yyvsp[-2].real) > (yyvsp[0].real)) (yyval.real)=1; else (yyval.real)=0; }
#line 1801 "calc_elidian.tab.c"
    break;

  case 47: /* logica: L1 MENOR L2  */
#line 391 "calc_elidian.y"
                  {if ((yyvsp[-2].real) < (yyvsp[0].real)) (yyval.real)=1; else (yyval.real)=0; }
#line 1807 "calc_elidian.tab.c"
    break;

  case 48: /* logica: L1 MAI L2  */
#line 392 "calc_elidian.y"
                {if ((yyvsp[-2].real) >= (yyvsp[0].real)) (yyval.real)=1; else (yyval.real)=0; }
#line 1813 "calc_elidian.tab.c"
    break;

  case 49: /* logica: L1 MEI L2  */
#line 393 "calc_elidian.y"
                {if ((yyvsp[-2].real) <= (yyvsp[0].real)) (yyval.real)=1; else (yyval.real)=0; }
#line 1819 "calc_elidian.tab.c"
    break;

  case 50: /* logica: L1 II L2  */
#line 394 "calc_elidian.y"
               {if ((yyvsp[-2].real) == (yyvsp[0].real)) (yyval.real)=1; else (yyval.real)=0; }
#line 1825 "calc_elidian.tab.c"
    break;

  case 51: /* logica: L1 DIF L2  */
#line 395 "calc_elidian.y"
                {if ((yyvsp[-2].real) != (yyvsp[0].real)) (yyval.real)=1; else (yyval.real)=0; }
#line 1831 "calc_elidian.tab.c"
    break;

  case 52: /* L1: L2  */
#line 397 "calc_elidian.y"
       {(yyval.real)=(yyvsp[0].real); }
#line 1837 "calc_elidian.tab.c"
    break;

  case 53: /* L2: '(' logica ')'  */
#line 399 "calc_elidian.y"
                   {(yyval.real)=(yyvsp[-1].real); }
#line 1843 "calc_elidian.tab.c"
    break;

  case 54: /* L2: arit  */
#line 400 "calc_elidian.y"
           {(yyval.real)=(yyvsp[0].real); }
#line 1849 "calc_elidian.tab.c"
    break;

  case 55: /* saida: TEXTO  */
#line 403 "calc_elidian.y"
             {
        if(strcmp((yyvsp[0].texto), "")==0)
            sprintf((yyval.texto), "");
        else
            sprintf((yyval.texto), "%s", (yyvsp[0].texto));
    }
#line 1860 "calc_elidian.tab.c"
    break;

  case 56: /* saida: TEXTO ',' saida  */
#line 409 "calc_elidian.y"
                      {sprintf((yyval.texto), "%s %s", (yyvsp[-2].texto), (yyvsp[0].texto)); }
#line 1866 "calc_elidian.tab.c"
    break;

  case 57: /* saida: arit  */
#line 410 "calc_elidian.y"
           {sprintf((yyval.texto), "%f", (yyvsp[0].real)); }
#line 1872 "calc_elidian.tab.c"
    break;

  case 58: /* saida: arit ',' saida  */
#line 411 "calc_elidian.y"
                     {sprintf((yyval.texto), "%f %s", (yyvsp[-2].real), (yyvsp[0].texto)); }
#line 1878 "calc_elidian.tab.c"
    break;

  case 59: /* saida: OPV VAR  */
#line 412 "calc_elidian.y"
              {
        VARTS * aux = srcht(tvar, (yyvsp[0].texto));
        if (aux == NULL){
            VARS * aux2 = srch(rvar, (yyvsp[0].texto));
            if (aux2 == NULL)
                printf ("Variavel '%s' nao foi declarada.\n", (yyvsp[0].texto));
            else{
                sprintf((yyval.texto), "%f", aux->value);
            }
        }
        else{
            strcpy((yyval.texto), aux->value);
            //printf("VAR->value = %f\n", $$);
        }
    }
#line 1898 "calc_elidian.tab.c"
    break;

  case 60: /* saida: OPV VAR ',' saida  */
#line 427 "calc_elidian.y"
                        {sprintf((yyval.texto), "%s, %s", (yyvsp[-2].texto), (yyvsp[0].texto)); }
#line 1904 "calc_elidian.tab.c"
    break;

  case 61: /* if: logica ':' cod ELSE cod ';'  */
#line 429 "calc_elidian.y"
                                {printf("IF ELSE CLOSE\n"); }
#line 1910 "calc_elidian.tab.c"
    break;

  case 62: /* if: logica ':' cod ';'  */
#line 430 "calc_elidian.y"
                         {printf("IF CLOSE\n"); }
#line 1916 "calc_elidian.tab.c"
    break;

  case 63: /* for: arit ':' cod ';'  */
#line 432 "calc_elidian.y"
                      {printf("FOR CLOSE\n"); }
#line 1922 "calc_elidian.tab.c"
    break;


#line 1926 "calc_elidian.tab.c"

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

#line 434 "calc_elidian.y"


#include "lex.yy.c"

int main(){

    rvar = NULL;
    tvar = NULL;
    
    yyin=fopen("calc_exemplo.txt", "r");
    yyparse();
    
    fclose(yyin);

    return 0;
}
int yywrap(){
    return 0;
}
