
# line 2 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"

/*-----------------INCLUDE-----------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*------------------- DEFINE------------------*/
#define ESTADOFINAL 17
#define MAXLEN 30
#define CANT_ESTADOS 17
#define CANT_TERMINALES 26

/* TERMINALES */
#define T_letra_may 0
#define T_letra_min 1
#define T_digito 2
#define T_comilla 3
#define T_dospuntos 4
#define T_puntoycoma 5
#define T_mas 6
#define T_menos 7
#define T_asterisco 8
#define T_barra 9
#define T_p_abre 10
#define T_p_cierra 11
#define T_c_abre 12
#define T_c_cierra 13
#define T_igual 14
#define T_menor 15
#define T_mayor 16
#define T_n 17
#define T_y 18
#define T_o 19
#define T_punto 20
#define T_numeral 21
#define T_espacio 22
#define T_tab 23
#define T_salto 24
#define T_ilegal 25

#define ERROR -1

/*------------------DECLARACIONES-----------------*/

// VARIABLES GLOBALES
int estado;
int longitud;
int token;
char caracter = ' ';
int columna;
char palabra[MAXLEN];
FILE* codigoFuente;
FILE* strerr;
void (*proceso[CANT_ESTADOS][CANT_TERMINALES])();
int i, j, ok;
int banderaDesleer; //indica si es necesario o no leer de nuevo

char tablaDeSimbolos[100][MAXLEN];
int cantidadDeItem = 0;

// MATRIZ DE ESTADOS
int matriz_estados[CANT_ESTADOS][CANT_TERMINALES] = {

		{      2,      5,      15,       1,       6,       17,      7,       17,      17,       8,      17,      17,      17,      17,      11,      12,      13,     17,      17,      17,      14,      -1,      0,      0,      0,     -1      },
		{      1,      1,        1,      17,      1,        1,       1,        1,        1,        1,       1,        1,        1,        1,        1,        1,        1,       1,         1,       1,         1,       1,      1,      1,      -1,     1     },
		{      2,     17,       2,      17,     17,      17,     17,      17,      17,      17,     17,      17,      17,      17,      17,      17,      17,     17,       17,     17,        4,      17,    17,    17,    17,    17     },
		{      4,     -1,      -1,      -1,      -1,       -1,      -1,      -1,       -1,      -1,       -1,      -1,       -1,      -1,       -1,      -1,       -1,      -1,       -1,      -1,       -1,      -1,     -1,     -1,     -1,     -1    },
		{      4,     17,      4,       17,     17,      17,     17,      17,      17,     17,       17,     17,      17,      17,      17,      17,      17,     17,       17,     17,      17,     17,     17,     17,    17,   17    },
		{     17,     5,      17,      17,     17,      17,     17,      17,     17,      17,       17,     17,      17,      17,      17,      17,      17,     17,       17,     17,      17,     17,     17,     17,    17,    17   },
		{     -1,     -1,      -1,      -1,      -1,       -1,     -1,       -1,     -1,       -1,       -1,      -1,      -1,       -1,       17,      -1,       -1,      -1,       -1,      -1,       -1,     -1,      -1,     -1,     -1,     -1,   },
		{     17,    17,     17,     17,      17,      17,     17,      17,     17,      17,      17,      17,      17,      17,     17,       17,      17,     17,      17,     17,      17,     17,      17,     17,    17,   17    },
		{     17,    17,     17,     17,      17,      17,     17,      17,     17,      17,      17,      17,      17,      17,     17,       17,      17,     17,      17,     17,      17,       9,      17,     17,    17,   17    },
		{      9,      9,       9,       9,        9,        9,        9,       9,       9,        9,        9,        9,         9,       9,        9,        9,        9,       9,        9,       9,        9,      10,       9,        9,     9,     9    },
		{      9,      9,       9,       9,        9,        9,        9,       9,       9,        0,        9,        9,         9,       9,        9,        9,        9,       9,        9,       9,        9,      10,       9,        9,     9,     9    },
		{     -1,     -1,      -1,      -1,      -1,       -1,     -1,       -1,     -1,       -1,       -1,      -1,      -1,       -1,       17,      -1,       -1,      -1,       -1,      -1,       -1,     -1,      -1,     -1,     -1,     -1,  },
		{     17,    17,     17,     17,      17,      17,     17,      17,     17,      17,      17,      17,      17,      17,     17,       17,      17,     17,      17,     17,      17,     17,      17,     17,    17,   17    },
		{     17,    17,     17,     17,      17,      17,     17,      17,     17,      17,      17,      17,      17,      17,     17,       17,      17,     17,      17,     17,      17,     17,      17,     17,    17,   17    },
		{     17,    17,     14,     17,      17,      17,     17,      17,     17,      17,      17,      17,      17,      17,     17,       17,      17,     17,      17,     17,      17,     17,      17,     17,    17,   17    },
		{     17,    17,     15,     17,      17,      17,     17,      17,     17,      17,      17,      17,      17,      17,     17,       17,      17,     17,      17,     17,      16,     17,      17,     17,    17,   17    },
		{     17,    17,     16,     17,      17,      17,     17,      17,     17,      17,      17,      17,      17,      17,     17,       17,      17,     17,      17,     17,      17,     17,      17,     17,    17,   17    }

};

// FUNCIONES DE LA MATRIZ
void iniciarId();
void iniciarPalabraReservada();
void iniciarNumero();
void iniciarCadena();
void iniciarAsignacion();
void puntoycoma();
void iniciarConcatenador();
void resta();
void multiplicacion();
void posibleComentario();
void abrirParentesis();
void cerrarParentesis();
void abrirCorchetes();
void cerrarCorchetes();
void iniciarIgual();
void posibleDistinto();
void posibleMayor();
void negacion();
void conjuncion();
void disyuncion();
void iniciarReal();
void error();
void nada();
void continuarCadena();
void finalizarCadena();
void continuarId();
void finalizarId();
void iniciarCampo();
void continuarCampo();
void finalizarCampo();
void finalizarPalabraReservada();
void continuarPalabraReservada();
void asignacion();
void suma();
void concatenacion();
void division();
void comentario();
void iniciarComentario();
void igual();
void menor();
void menorIgual();
void distinto();
void mayor();
void mayorIgual();
void finalizarReal();
void continuarReal();
void finalizarEntero();
void continuarNumero();

// OTRAS FUNCIONES
char* aNombreDeToken(int numeroDeToken);
void desleer();
void escribir();
int estaEnTablaDeSimbolos();
int get_evento(char c);
void leer();
void mostrarTablaDeSimbolos();
void validarPalabraReservada();
int yylex();
int yyerror(char * s);
int yyparse();

#define ID 257
#define CAMPO 258
#define CTE_ENT 259
#define CTE_REAL 260
#define CTE_CAD 261
#define COMENZAR 262
#define FINAL 263
#define DECLARAR 264
#define FINDECLARAR 265
#define SI 266
#define HACER 267
#define FINSI 268
#define SINO 269
#define MIENTRAS 270
#define ESTRU 271
#define PONER 272
#define TOMAR 273
#define FINMIENTRAS 274
#define ENTERO 275
#define REAL 276
#define CADENA 277
#define BOOLEANO 278
#define CONST 279
#define FALSO 280
#define VERDADERO 281
#define TRUNCAR 282
#define REDONDEAR 283
#define PUNTOYCOMA 284
#define ASIG 285
#define SUM 286
#define RES 287
#define MUL 288
#define DIV 289
#define CONC 290
#define OP_Y 291
#define OP_O 292
#define OP_N 293
#define IGUAL 294
#define DISTINTO 295
#define MENOR 296
#define MENORIGUAL 297
#define MAYOR 298
#define MAYORIGUAL 299
#define P_ABRE 300
#define P_CIERRA 301
#define C_ABRE 302
#define C_CIERRA 303
#ifndef YYSTYPE
#define YYSTYPE int
#endif
YYSTYPE yylval, yyval;
#define YYERRCODE 256

# line 346 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"




/*---------------------FUNCION MAIN----------------------*/

int main(int argc, char *argv[]){
	
	if(argv[1] == NULL) {
		printf("%s", "FALTA ESPECIFICAR CODIGO FUENTE\n");
		return 0;
	}
	
	banderaDesleer = 0;
	yyval = 0;
	
	for(i = 0; i < cantidadDeItem; i++)
		for(j = 0; j < MAXLEN; j++)
			tablaDeSimbolos[i][j] = ' ';
	
// MATRIZ DE PUNTEROS A FUNCION
	
	for(i=0; i < CANT_ESTADOS; i++)
		for(j=0; j < CANT_TERMINALES; j++)
			proceso[i][j]=nada;

	/*ESTADO 0*/
	proceso[0][T_letra_may]=iniciarId;
	proceso[0][T_letra_min]=iniciarPalabraReservada;
	proceso[0][T_digito]=iniciarNumero;
	proceso[0][T_comilla]=iniciarCadena;
	proceso[0][T_dospuntos]=iniciarAsignacion;
	proceso[0][T_puntoycoma]=puntoycoma;
	proceso[0][T_mas]=iniciarConcatenador;
	proceso[0][T_menos]=resta;
	proceso[0][T_asterisco]=multiplicacion;
	proceso[0][T_barra]=posibleComentario;
	proceso[0][T_p_abre]=abrirParentesis;
	proceso[0][T_p_cierra]=cerrarParentesis;
	proceso[0][T_c_abre]=abrirCorchetes;
	proceso[0][T_c_cierra]=cerrarCorchetes;
	proceso[0][T_igual]=iniciarIgual;
	proceso[0][T_menor]=posibleDistinto;
	proceso[0][T_mayor]=posibleMayor;
	proceso[0][T_n]=negacion;
	proceso[0][T_y]=conjuncion;
	proceso[0][T_o]=disyuncion;
	proceso[0][T_punto]=iniciarReal;
	proceso[0][T_numeral]=error;
	proceso[0][T_ilegal]=error;

	/*ESTADO 1*/
	for(i=0;i < CANT_TERMINALES;i++)
		proceso[1][i]=continuarCadena;
	proceso[1][T_comilla]=finalizarCadena;
	proceso[1][T_salto]=error;

	/*ESTADO 2*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[2][i]=finalizarId;
	proceso[2][T_letra_may]=continuarId;
	proceso[2][T_digito]=continuarId;
	proceso[2][T_punto]=iniciarCampo;

	/*ESTADO 3*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[3][i]=error;
	proceso[3][T_letra_may]=iniciarCampo;

	/*ESTADO 4*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[4][i]=finalizarCampo;
	proceso[4][T_letra_may]=continuarCampo;
	proceso[4][T_digito]=continuarCampo;

	/*ESTADO 5*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[5][i]=finalizarPalabraReservada;
	proceso[5][T_letra_min]=continuarPalabraReservada;

	/*ESTADO 6*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[6][i]=error;
	proceso[6][T_igual]=asignacion;

	/*ESTADO 7*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[7][i]=suma;
	proceso[7][T_mas]=concatenacion;

	/*ESTADO 8*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[8][i]=division;
	proceso[8][T_numeral]=iniciarComentario;

	/*ESTADO 9*/

	/*ESTADO 10*/

	/*ESTADO 11*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[11][i]=error;
	proceso[11][T_igual]=igual;

	/*ESTADO 12*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[12][i]=menor;
	proceso[12][T_igual]=menorIgual;
	proceso[12][T_mayor]=distinto;

	/*ESTADO 13*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[13][i]=mayor;
	proceso[13][T_igual]=mayorIgual;

	/*ESTADO 14*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[14][i]=finalizarReal;
	proceso[14][T_digito]=continuarReal;

	/*ESTADO 15*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[15][i]=finalizarEntero;
	proceso[15][T_digito]=continuarNumero;
	proceso[15][T_punto]=continuarReal;

	/*ESTADO 16*/
	for(i=0;i<CANT_TERMINALES;i++)
		proceso[16][i]=finalizarReal;
	proceso[16][T_digito]=continuarReal;
	
	codigoFuente = fopen(argv[1], "r");
	strerr = fopen("error.txt","a");
	
	printf("\nARCHIVO ANALIZADO: %s\n", argv[1]);
	printf("\nTOKENS RECONOCIDOS\n");
	printf("------------------\n");
	while (feof(codigoFuente)== 0) {
		yyparse();
	}
	fclose(codigoFuente);	
	mostrarTablaDeSimbolos();
	return 0;
}

int yyerror(char * s) {
	fprintf(stderr, "%s\n", s);
}


/*-------------------FUNCIONES AUXILIARES-------------------*/

void desleer(){
	banderaDesleer = 1;
}

void escribir(){
	strcpy(tablaDeSimbolos[cantidadDeItem], palabra);
	cantidadDeItem++;
}

int estaEnTablaDeSimbolos(){
	for(i = 0; i < cantidadDeItem; i++){
		ok = 1;
		for(j = 0; j < longitud; j++)
			if(tablaDeSimbolos[i][j]!=palabra[j]) ok = 0;
		if(ok) {
			yyval = i;
			return 1;}
	}
	return 0; 
}

int get_evento(char c) {
	if(c>='A'&& c<='Z') return T_letra_may;
	if(c>='a'&& c<='z') return T_letra_min;
	if(c>='0' && c<='9') return T_digito;
	switch(c) {
		case '\'': return T_comilla;
		case ':': return T_dospuntos;
		case ';': return T_puntoycoma;
		case '+': return T_mas;
		case '-': return T_menos;
		case '*': return T_asterisco;
		case '/': return T_barra;
		case '(': return T_p_abre;
		case ')': return T_p_cierra;
		case '[': return T_c_abre;
		case ']': return T_c_cierra;
		case '=': return T_igual;
		case '<': return T_menor;
		case '>': return T_mayor;
		case '!': return T_n;
		case '&': return T_y;
		case '|': return T_o;
		case '.': return T_punto;
		case '#': return T_numeral;
		case ' ': return T_espacio;
		case '\t': return T_tab;
		case '\n': return T_salto;
		default: return T_ilegal;
	}
}

void leer(){
	if(banderaDesleer == 0)
		caracter = getc(codigoFuente);
	else banderaDesleer = 0;
}

void mostrarTablaDeSimbolos(){
	printf("\nTABLA DE SIMBOLOS (%i)\n", cantidadDeItem);
	printf("-----------------\n");
	for(i=0;i<cantidadDeItem;i++){
		for(j=0;j<MAXLEN;j++)
			printf("%c", tablaDeSimbolos[i][j]);
	printf("\n");
	}
}

void validarPalabraReservada(){
	if(strcmp(palabra, "comenzar                      ")==0) token=COMENZAR;
	if(strcmp(palabra, "final                         ")==0) token=FINAL;
	if(strcmp(palabra, "declarar                      ")==0) token=DECLARAR;
	if(strcmp(palabra, "findeclarar                   ")==0) token=FINDECLARAR;
	if(strcmp(palabra, "si                            ")==0) token=SI;
	if(strcmp(palabra, "hacer                         ")==0) token=HACER;
	if(strcmp(palabra, "finsi                         ")==0) token=FINSI;
	if(strcmp(palabra, "sino                          ")==0) token=SINO;
	if(strcmp(palabra, "mientras                      ")==0) token=MIENTRAS;
	if(strcmp(palabra, "estru                         ")==0) token=ESTRU;
	if(strcmp(palabra, "poner                         ")==0) token=PONER;
	if(strcmp(palabra, "tomar                         ")==0) token=TOMAR;
	if(strcmp(palabra, "finmientras                   ")==0) token=FINMIENTRAS;
	if(strcmp(palabra, "entero                        ")==0) token=ENTERO;
	if(strcmp(palabra, "real                          ")==0) token=REAL;
	if(strcmp(palabra, "cadena                        ")==0) token=CADENA;
	if(strcmp(palabra, "booleano                      ")==0) token=BOOLEANO;
	if(strcmp(palabra, "const                         ")==0) token=CONST;
	if(strcmp(palabra, "falso                         ")==0) token=FALSO;
	if(strcmp(palabra, "verdadero                     ")==0) token=VERDADERO;
	if(strcmp(palabra, "truncar                       ")==0) token=TRUNCAR;
	if(strcmp(palabra, "redondear                     ")==0) token=REDONDEAR;
}

/*-----------------FUNCION YYLEX-------------------*/

int yylex(void){
	/*INICIALIZO TODAS LAS VARIABLES GLOBALES*/
	estado = 0;
	longitud = 0;
	token = -1;
	for(i = 0; i < MAXLEN; i++)
		palabra[i] = ' ';
	while(estado != ESTADOFINAL){
		columna = get_evento(caracter);
		(*proceso[estado][columna])();
		estado = matriz_estados[estado][columna];
		leer();
	}
	return token;
}

/*----------------------------FUNCIONES DE LA MATRIZ------------------------------*/

void iniciarId(){
	palabra[0] = caracter;
	longitud = 1;
}

void iniciarPalabraReservada(){
	palabra[0] = caracter;
	longitud = 1;
}

void iniciarNumero(){
	palabra[0] = caracter;
	longitud = longitud + 1;
}

void iniciarCadena(){
	palabra[0] = '_';
	longitud = 1;
}

void iniciarAsignacion(){
}

void puntoycoma(){
	token = PUNTOYCOMA;
}

void iniciarConcatenador(){
}

void resta(){
	token = RES;
}

void multiplicacion(){
	token = MUL;
}

void posibleComentario(){
}

void abrirParentesis(){
	token = P_ABRE;
}

void cerrarParentesis(){
	token = P_CIERRA;
}

void abrirCorchetes(){
	token = C_ABRE;
}

void cerrarCorchetes(){
	token = C_CIERRA;
}

void iniciarIgual(){
}

void posibleDistinto(){
}

void posibleMayor(){
}

void negacion(){
	token = OP_N;
}

void conjuncion(){
	token = OP_Y;
}

void disyuncion(){
	token = OP_O;
}

void iniciarReal(){
	palabra[0] = caracter;
	longitud = 1;
}

void error(){
	token = ERROR;
}

void nada(){
	banderaDesleer = 0;
}

void continuarCadena(){
	if(longitud >= MAXLEN){
		estado = ESTADOFINAL;
		token = ERROR;
	}
	else{
		palabra[longitud] = caracter;
		longitud = longitud + 1;
	}
}

void finalizarCadena(){
	escribir();
	token = CTE_CAD;
}

void continuarId(){
	if(longitud >= 10){
		estado = ESTADOFINAL;
		token = ERROR;
	}
	else{
		palabra[longitud] = caracter;
		longitud = longitud + 1;
	}
}

void finalizarId(){
	if(!estaEnTablaDeSimbolos()) escribir();
	desleer();
	token = ID;
}

void iniciarCampo(){
	palabra[longitud] = caracter;
	longitud = longitud + 1;
}

void continuarCampo(){
	if(longitud >= 20){
		estado = ESTADOFINAL;
		token = ERROR;
	}
	else{
		palabra[longitud] = caracter;
		longitud = longitud + 1;
	}
}

void finalizarCampo(){
	if(!estaEnTablaDeSimbolos()) escribir();
	desleer();
	token = CAMPO;
}

void finalizarPalabraReservada(){
	validarPalabraReservada();
	desleer();
}

void continuarPalabraReservada(){
	if(longitud >= 11){
		estado = ESTADOFINAL;
		token = ERROR;
	}
	else{
		palabra[longitud] = caracter;
		longitud = longitud + 1;
	}
}

void asignacion(){
	token = ASIG;
}

void suma(){
	token = SUM;
	desleer();
}

void concatenacion(){
	token = CONC;
}

void division(){
	token = DIV;
	desleer();
}

void iniciarComentario(){
}

void igual(){
	token = IGUAL;
}

void menor(){
	token = MENOR;
	desleer();
}

void menorIgual(){
	token = MENORIGUAL;
}

void distinto(){
	token = DISTINTO;
}

void mayor(){
	token = MAYOR;
	desleer();
}

void mayorIgual(){
	token = MAYORIGUAL;
}

void finalizarReal(){
	escribir();
	desleer();
	token = CTE_REAL;
}

void continuarReal(){
	if(longitud >= 10){
		estado = ESTADOFINAL;
		token = ERROR;
	}
	else{
		palabra[longitud] = caracter;
		longitud = longitud + 1;
	}
}

void finalizarEntero(){
	escribir();
	desleer();
	token = CTE_ENT;
}

void continuarNumero(){
	if(longitud >= 10){
		estado = ESTADOFINAL;
		token = ERROR;
	}
	else{
		palabra[longitud] = caracter;
		longitud = longitud + 1;
	}		
}
FILE *yytfilep;
char *yytfilen;
int yytflag = 0;
int svdprd[2];
char svdnams[2][2];

int yyexca[] = {
  -1, 1,
  0, -1,
  -2, 0,
  0,
};

#define YYNPROD 64
#define YYLAST 267

int yyact[] = {
      47,      48,      44,      45,      46,      24,      25,      26,
      27,      47,      48,      44,      45,      46,      73,      74,
      75,      76,      77,      78,     110,      88,     112,      41,
      42,      73,      74,      75,      76,      77,      78,     116,
      84,      85,      83,      80,      68,      70,      71,      72,
      37,      86,      87,      43,      84,      85,      82,      99,
      35,     119,      61,      34,      43,      33,      13,      15,
      32,      31,       4,      71,      72,      71,      72,      16,
     101,      13,      15,      17,     118,      18,      19,     109,
      62,      81,      16,      60,      14,     108,      17,      22,
      18,      19,      13,      15,       4,      36,       5,      14,
      29,      55,      56,      16,      13,      15,     114,      17,
      64,      18,      19,      63,      65,      16,      21,     113,
      14,      17,      57,      18,      19,       7,      23,      59,
      28,       8,      14,      12,      24,      25,      26,      27,
      28,      30,      11,      58,      24,      25,      26,      27,
      24,      25,      26,      27,      50,      54,      51,      52,
      53,      69,      66,      10,       9,       2,      20,      79,
       8,       6,       3,      39,       2,       1,       0,       0,
       0,       0,       0,      38,      49,       0,      40,       0,
       0,      21,       0,       0,       0,       0,       0,       0,
      89,      43,       0,       0,       0,       0,       0,       0,
       0,      17,       0,      68,      90,     102,     104,       0,
       0,       0,       0,       0,      66,      63,     100,       0,
     115,     115,      67,      22,      67,       0,       0,      85,
      80,      64,      67,       0,      30,       0,       0,       0,
     117,       0,     108,       0,     114,       0,      30,       0,
       0,       0,     111,      91,      92,       7,       0,       0,
       0,      30,      73,      67,       0,       0,       0,       0,
      93,      94,      95,      96,      97,      98,       0,      72,
      39,       0,       0,     103,     103,     105,     106,     107,
       0,       0,       0,       0,      74,      75,      76,      77,
      78,      84,       0,       0,       0,       0,      86,       0,
      87,      88,      40,
};

int yypact[] = {
    -178,   -1000,   -1000,    -204,    -165,    -151,   -1000,    -175,
   -1000,    -227,    -228,    -231,    -233,    -237,    -172,    -245,
    -257,    -257,    -125,    -168,    -159,   -1000,    -182,    -234,
   -1000,   -1000,   -1000,   -1000,    -185,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,    -257,    -249,    -257,    -230,   -1000,
    -280,   -1000,   -1000,    -257,   -1000,   -1000,   -1000,   -1000,
   -1000,    -232,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,    -211,   -1000,   -1000,    -268,    -242,
    -247,   -1000,    -253,    -269,    -257,    -242,    -165,    -257,
    -257,    -248,    -248,    -248,    -248,    -248,    -248,    -254,
    -165,   -1000,   -1000,    -195,    -248,    -248,    -248,    -248,
    -248,    -242,    -192,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,    -203,    -283,    -247,   -1000,
    -247,   -1000,   -1000,   -1000,    -165,   -1000,    -278,    -165,
    -147,    -270,   -1000,    -190,   -1000,   -1000,    -235,   -1000,
};

int yypgo[] = {
       0,     149,     141,     146,     109,     142,     113,     102,
     140,     139,     122,     115,      79,     111,     110,      99,
     138,     103,      96,     100,     147,      94,     158,
};

int yyr1[] = {
       0,       1,       1,       2,       3,       4,       4,       5,
       5,       6,       6,       6,       6,       7,       7,       8,
       8,       8,       9,       9,      10,      11,      11,      11,
      11,      11,      11,      11,      12,      12,      12,      12,
      13,      13,      14,      15,      15,      15,      15,      15,
      16,      16,      16,      17,      17,      18,      18,      18,
      19,      20,      20,      20,      20,      20,      20,      20,
      20,      21,      22,      22,      22,      22,      22,      22,
};

int yyr2[] = {
       2,       1,       2,       3,       3,       1,       2,       1,
       2,       2,       2,       2,       2,       3,       2,       3,
       4,       3,       4,       6,       5,       2,       2,       2,
       2,       2,       2,       2,       1,       1,       1,       1,
       1,       2,       8,       1,       3,       3,       1,       1,
       1,       3,       3,       1,       2,       1,       3,       3,
       3,       3,       3,       3,       3,       3,       3,       1,
       1,       3,       3,       1,       1,       1,       1,       1,
};

int yychk[] = {
   -1000,      -1,      -2,      -3,     262,     264,      -2,      -4,
      -6,      -8,      -9,     -10,     -11,     257,     279,     258,
     266,     270,     272,     273,      -5,      -7,     -12,     -14,
     275,     276,     277,     278,     271,     263,      -6,     284,
     284,     284,     284,     285,     257,     285,     -16,     -20,
     -22,     280,     281,     300,     259,     260,     261,     257,
     258,     -16,     257,     259,     260,     261,     258,     257,
     258,     265,      -7,     -13,     257,     284,     257,     -15,
     -18,     -19,     -16,     -22,     285,     -15,     267,     291,
     292,     294,     295,     296,     297,     298,     299,     -15,
     267,     284,     257,     302,     286,     287,     288,     289,
     290,     -15,      -4,     -20,     -20,     -22,     -22,     -22,
     -22,     -22,     -22,     301,      -4,     259,     -18,     -22,
     -18,     -22,     -22,     -22,     269,     274,     303,      -4,
     300,     -17,     -21,     -12,     301,     -21,     258,     284,
};

int yydef[] = {
       0,      -2,       1,       0,       0,       0,       2,       0,
       5,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       7,       0,       0,
      28,      29,      30,      31,       0,       3,       6,       9,
      10,      11,      12,       0,       0,       0,       0,      40,
       0,      55,      56,       0,      59,      60,      61,      62,
      63,       0,      21,      22,      23,      24,      25,      26,
      27,       4,       8,       0,      32,      14,       0,      15,
      35,      38,      39,      45,       0,      17,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,      13,      33,       0,       0,       0,       0,       0,
       0,      16,      18,      41,      42,      49,      50,      51,
      52,      53,      54,      58,       0,       0,      36,      45,
      37,      46,      47,      48,       0,      20,       0,      19,
       0,       0,      43,       0,      34,      44,       0,      57,
};

int *yyxi;


/*****************************************************************/
/* PCYACC LALR parser driver routine -- a table driven procedure */
/* for recognizing sentences of a language defined by the        */
/* grammar that PCYACC analyzes. An LALR parsing table is then   */
/* constructed for the grammar and the skeletal parser uses the  */
/* table when performing syntactical analysis on input source    */
/* programs. The actions associated with grammar rules are       */
/* inserted into a switch statement for execution.               */
/*****************************************************************/


#ifndef YYMAXDEPTH
#define YYMAXDEPTH 200
#endif
#ifndef YYREDMAX
#define YYREDMAX 1000
#endif
#define PCYYFLAG -1000
#define WAS0ERR 0
#define WAS1ERR 1
#define WAS2ERR 2
#define WAS3ERR 3
#define yyclearin pcyytoken = -1
#define yyerrok   pcyyerrfl = 0
YYSTYPE yyv[YYMAXDEPTH];     /* value stack */
int pcyyerrct = 0;           /* error count */
int pcyyerrfl = 0;           /* error flag */
int redseq[YYREDMAX];
int redcnt = 0;
int pcyytoken = -1;          /* input token */


yyparse()
{
  int statestack[YYMAXDEPTH]; /* state stack */
  int      j, m;              /* working index */
  YYSTYPE *yypvt;
  int      tmpstate, tmptoken, *yyps, n;
  YYSTYPE *yypv;


  tmpstate = 0;
  pcyytoken = -1;
#ifdef YYDEBUG
  tmptoken = -1;
#endif
  pcyyerrct = 0;
  pcyyerrfl = 0;
  yyps = &statestack[-1];
  yypv = &yyv[-1];


  enstack:    /* push stack */
#ifdef YYDEBUG
    printf("at state %d, next token %d\n", tmpstate, tmptoken);
#endif
    if (++yyps - &statestack[YYMAXDEPTH] > 0) {
      yyerror("pcyacc internal stack overflow");
      return(1);
    }
    *yyps = tmpstate;
    ++yypv;
    *yypv = yyval;


  newstate:
    n = yypact[tmpstate];
    if (n <= PCYYFLAG) goto defaultact; /*  a simple state */


    if (pcyytoken < 0) if ((pcyytoken=yylex()) < 0) pcyytoken = 0;
    if ((n += pcyytoken) < 0 || n >= YYLAST) goto defaultact;


    if (yychk[n=yyact[n]] == pcyytoken) { /* a shift */
#ifdef YYDEBUG
      tmptoken  = pcyytoken;
#endif
      pcyytoken = -1;
      yyval = yylval;
      tmpstate = n;
      if (pcyyerrfl > 0) --pcyyerrfl;
      goto enstack;
    }


  defaultact:


    if ((n=yydef[tmpstate]) == -2) {
      if (pcyytoken < 0) if ((pcyytoken=yylex())<0) pcyytoken = 0;
      for (yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=tmpstate); yyxi += 2);
      while (*(yyxi+=2) >= 0) if (*yyxi == pcyytoken) break;
      if ((n=yyxi[1]) < 0) { /* an accept action */
        if (yytflag) {
          int ti; int tj;
          yytfilep = fopen(yytfilen, "w");
          if (yytfilep == NULL) {
            fprintf(stderr, "Can't open t file: %s\n", yytfilen);
            return(0);          }
          for (ti=redcnt-1; ti>=0; ti--) {
            tj = svdprd[redseq[ti]];
            while (strcmp(svdnams[tj], "$EOP"))
              fprintf(yytfilep, "%s ", svdnams[tj++]);
            fprintf(yytfilep, "\n");
          }
          fclose(yytfilep);
        }
        return (0);
      }
    }


    if (n == 0) {        /* error situation */
      switch (pcyyerrfl) {
        case WAS0ERR:          /* an error just occurred */
          yyerror("syntax error");
          yyerrlab:
            ++pcyyerrct;
        case WAS1ERR:
        case WAS2ERR:           /* try again */
          pcyyerrfl = 3;
	   /* find a state for a legal shift action */
          while (yyps >= statestack) {
	     n = yypact[*yyps] + YYERRCODE;
	     if (n >= 0 && n < YYLAST && yychk[yyact[n]] == YYERRCODE) {
	       tmpstate = yyact[n];  /* simulate a shift of "error" */
	       goto enstack;
            }
	     n = yypact[*yyps];


	     /* the current yyps has no shift on "error", pop stack */
#ifdef YYDEBUG
            printf("error: pop state %d, recover state %d\n", *yyps, yyps[-1]);
#endif
	     --yyps;
	     --yypv;
	   }


	   yyabort:
            if (yytflag) {
              int ti; int tj;
              yytfilep = fopen(yytfilen, "w");
              if (yytfilep == NULL) {
                fprintf(stderr, "Can't open t file: %s\n", yytfilen);
                return(1);              }
              for (ti=1; ti<redcnt; ti++) {
                tj = svdprd[redseq[ti]];
                while (strcmp(svdnams[tj], "$EOP"))
                  fprintf(yytfilep, "%s ", svdnams[tj++]);
                fprintf(yytfilep, "\n");
              }
              fclose(yytfilep);
            }
	     return(1);


	 case WAS3ERR:  /* clobber input char */
#ifdef YYDEBUG
          printf("error: discard token %d\n", pcyytoken);
#endif
          if (pcyytoken == 0) goto yyabort; /* quit */
	   pcyytoken = -1;
	   goto newstate;      } /* switch */
    } /* if */


    /* reduction, given a production n */
#ifdef YYDEBUG
    printf("reduce with rule %d\n", n);
#endif
    if (yytflag && redcnt<YYREDMAX) redseq[redcnt++] = n;
    yyps -= yyr2[n];
    yypvt = yypv;
    yypv -= yyr2[n];
    yyval = yypv[1];
    m = n;
    /* find next state from goto table */
    n = yyr1[n];
    j = yypgo[n] + *yyps + 1;
    if (j>=YYLAST || yychk[ tmpstate = yyact[j] ] != -n) tmpstate = yyact[yypgo[n]];
    switch (m) { /* actions associated with grammar rules */
      
      case 1:
# line 218 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 1\n"); //generarAssembler();} break;
      case 2:
# line 219 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 2\n"); //generarAssembler();} break;
      case 3:
# line 223 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 3\n");} break;
      case 4:
# line 227 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 4\n");} break;
      case 5:
# line 231 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 5\n");} break;
      case 6:
# line 232 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 6\n");} break;
      case 7:
# line 236 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 7\n");} break;
      case 8:
# line 237 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 8\n");} break;
      case 9:
# line 241 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 9\n");} break;
      case 10:
# line 242 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 10\n");} break;
      case 11:
# line 243 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 11\n");} break;
      case 12:
# line 244 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 12\n");} break;
      case 13:
# line 248 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 13\n");} break;
      case 14:
# line 249 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 14\n");} break;
      case 15:
# line 253 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 15\n");} break;
      case 16:
# line 254 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 16\n");} break;
      case 17:
# line 255 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 17\n");} break;
      case 18:
# line 259 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 18\n");} break;
      case 19:
# line 260 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 19\n");} break;
      case 20:
# line 264 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 20\n");} break;
      case 21:
# line 268 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 21\n");} break;
      case 22:
# line 269 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 22\n");} break;
      case 23:
# line 270 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 23\n");} break;
      case 24:
# line 271 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 24\n");} break;
      case 25:
# line 272 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 25\n");} break;
      case 26:
# line 273 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 26\n");} break;
      case 27:
# line 274 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 27\n");} break;
      case 28:
# line 278 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 28\n");} break;
      case 29:
# line 279 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 29\n");} break;
      case 30:
# line 280 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 30\n");} break;
      case 31:
# line 281 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 31\n");} break;
      case 32:
# line 285 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 32\n");} break;
      case 33:
# line 286 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 33\n");} break;
      case 34:
# line 290 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 34\n");} break;
      case 35:
# line 294 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 35\n");} break;
      case 36:
# line 295 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 36\n"); // escribirEnPolaca("+")} break;
      case 37:
# line 296 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 37\n");} break;
      case 38:
# line 297 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 38\n");} break;
      case 39:
# line 298 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 39\n");} break;
      case 40:
# line 302 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 40\n");} break;
      case 41:
# line 303 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 41\n");} break;
      case 42:
# line 304 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 42\n");} break;
      case 43:
# line 308 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 43\n");} break;
      case 44:
# line 309 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 44\n");} break;
      case 45:
# line 313 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 45\n");} break;
      case 46:
# line 314 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 46\n");} break;
      case 47:
# line 315 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 47\n");} break;
      case 48:
# line 319 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 48\n");} break;
      case 49:
# line 323 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 49\n");} break;
      case 50:
# line 324 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 50\n");} break;
      case 51:
# line 325 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 51\n");} break;
      case 52:
# line 326 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 52\n");} break;
      case 53:
# line 327 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 53\n");} break;
      case 54:
# line 328 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 54\n");} break;
      case 55:
# line 329 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 55\n");} break;
      case 56:
# line 330 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 56\n");} break;
      case 57:
# line 334 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 57\n");} break;
      case 58:
# line 338 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 58\n");} break;
      case 59:
# line 339 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 59\n");} break;
      case 60:
# line 340 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 60\n");} break;
      case 61:
# line 341 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 61\n");} break;
      case 62:
# line 342 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 62\n");} break;
      case 63:
# line 343 "D:\UNO\12\DESARR~1\GRUPO03\SINTAC~1\FEF.Y"
      {printf("REGLA 63\n");} break;    }
    goto enstack;
}
