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

/* TOKENS */
#define PUNTOYCOMA 257
#define ASIG 258
#define SUM 259
#define RES 260
#define MUL 261
#define DIV 262
#define CONC 263
#define OP_Y 264
#define OP_O 265
#define OP_N 266
#define IGUAL 267
#define DISTINTO 268
#define MENOR 269
#define MENORIGUAL 270
#define MAYOR 271
#define MAYORIGUAL 272
#define P_ABRE 273
#define P_CIERRA 274
#define C_ABRE 275
#define C_CIERRA 276
#define ID 277
#define CAMPO 278
#define CTE_ENT 279
#define CTE_REAL 280
#define CTE_CAD 281
#define COMENZAR 282
#define FINAL 283
#define DECLARAR 284
#define FINDECLARAR 285
#define SI 286
#define HACER 287
#define FINSI 288
#define SINO 289
#define MIENTRAS 290
#define ESTRU 291
#define PONER 292
#define TOMAR 293
#define FINMIENTRAS 294
#define ENTERO 295
#define REAL 296
#define CADENA 297
#define BOOLEANO 298
#define CONST 299
#define FALSO 300
#define VERDADERO 301
#define TRUNCAR 302
#define REDONDEAR 303
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
void (*proceso[CANT_ESTADOS][CANT_TERMINALES])();
int i, j, ok;
int banderaDesleer; //indica si es necesario o no leer de nuevo
int yyval;

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

/*---------------------FUNCION MAIN----------------------*/

int main(int argc, char *argv[]){
	
	if(argv[1] == NULL) {
		printf("%s", "FALTA ESPECIFICAR CODIGO FUENTE\n");
		return 0;
	}
	
	banderaDesleer = 0;
	
	for(i = 0; i < cantidadDeItem; i++)
		for(j = 0; j < MAXLEN; j++)
			tablaDeSimbolos[i][j] = ' ';

	yyval = -1;
	
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
	printf("\nARCHIVO ANALIZADO: %s\n", argv[1]);
	printf("\nTOKENS RECONOCIDOS\n");
	printf("------------------\n");
	while(caracter != EOF){
		//fprintf(listaDeTokens, aNombreDeToken(yylex()));
		//fprintf(listaDeTokens, "\n");
		printf("%s", aNombreDeToken(yylex()));
		printf("\n");
	}
	fclose(codigoFuente);	
	mostrarTablaDeSimbolos();
	return 0;
}

/*-------------------FUNCIONES AUXILIARES-------------------*/

char* aNombreDeToken(int numeroDeToken){
	switch(numeroDeToken){
		case 257: return "puntoycoma";
		case 258: return "asignacion";
		case 259: return "suma";
		case 260: return "resta";
		case 261: return "multiplicacion";
		case 262: return "division";
		case 263: return "concatenacion";
		case 264: return "operador_y";
		case 265: return "operador_o";
		case 266: return "operador_n";
		case 267: return "igual";
		case 268: return "distinto";
		case 269: return "menor";
		case 270: return "menorigual";
		case 271: return "mayor";
		case 272: return "mayorigual";
		case 273: return "p_abre";
		case 274: return "p_cierra";
		case 275: return "c_abre";
		case 276: return "c_cierra";
		case 277: return "identificador";
		case 278: return "campo";
		case 279: return "cte_ent";
		case 280: return "cte_real";
		case 281: return "cte_cad";
		case 282: return "comenzar";
		case 283: return "final";
		case 284: return "declarar";
		case 285: return "findeclarar";
		case 286: return "si";
		case 287: return "hacer";
		case 288: return "finsi";
		case 289: return "sino";
		case 290: return "mientras";
		case 291: return "estru";
		case 292: return "poner";
		case 293: return "tomar";
		case 294: return "finmientras";
		case 295: return "entero";
		case 296: return "real";
		case 297: return "cadena";
		case 298: return "booleano";
		case 299: return "const";
		case 300: return "falso";
		case 301: return "verdadero";
		case 302: return "truncar";
		case 303: return "redondear";
		default: return "error";
	}
}

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
		finalizarId();
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
		finalizarId();
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

