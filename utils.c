#include <ctype.h>

#define TAM_TAB 100
#define MAX_PAR 20

enum {INT, LOG};

int desempilha(char);
void empilha(int, char);
void mostrapilha();

struct elemTabSimbolos {
    char id[100];
    int end;            //endereço (global) ou deslocamento (local)
    int tip;            // tipo
    char cat;           //categoria: "f" = Função, "p" = Parametro, ou "v" = Variavel
    char esc;           // escopo "g" = Global, "l" = Local
    int rot;            // rotulo (especifico para função)
    int npa;            // numero de parametros (para função)
    int par[MAX_PAR];   //Tipos dos parametros (para função)
} tabSimb[TAM_TAB], elemTab;

int posTab = 0; 

void maiscula (char *s) {
    for(int i = 0; s[i]; i++)
        s[i] = toupper(s[i]);
}

void imprimirParametros (int pos)
    {
      int qtd = tabSimb[pos].npa;
      for (int i = 0; i = qtd - 1; i++){
        printf("%3d -> ", tabSimb[i].tip == INT ? "INT" : "LOG"; )
      }
      printf("%3s")  
    } 

void arrumarParametros (int pos)
    {
    int qtd = pos;
    for(int i = 1; i <= TAM_TAB; i++){
        if(tabSimb[i].cat == 'f'){  
           tabSimb[i].npa = pos;
           tabSimb[i].end = ((-3) - qtd);
           qtd--;
        }
    }
    }

int buscaSimbolo(char *id)
{
    int i;
    //maiscula(id);
    for (i = posTab - 1; strcmp(tabSimb[i].id, id) && i >= 0; i--)
        ;
    if (i == -1) {
        char msg[200];
        sprintf(msg, "Identificador [%s] não encontrado!", id);
        yyerror(msg);
    }
    return i;
}
void insereSimbolo (struct elemTabSimbolos elem) {
    int i; 
    //maiscula(elem.id);
    if (posTab == TAM_TAB)
        yyerror("Tabela de Simbolos Cheia!");
    for (i = posTab - 1; strcmp(tabSimb[i].id, elem.id) && i >= 0; i--)
        ;
    if (i != -1) {
        char msg[200];
        sprintf(msg, "Identificador [%s] duplicado!", elem.id);
        yyerror(msg);
    }
    tabSimb[posTab++] = elem; 
}


// Desenvolver uma rotina para ajustar o endereço dos parametros
// na tabela de simbolos e o vetor de parametros na função
// depois que for cadastrado o ultimo parametro

// Modificar a rotina mostratabela para apresentar os outros campos
// (esc, rot, cat, ...) da tabela.

//void imprimirVetor (struct elemTabSimbolos elem)
//{
//    for(int i = 0; i < tabSimb[i].npa; i++) 
//    printf("[%d] -> [%d]")
//}

void mostraTabela () {
    puts("Tabela de Simbolos");
    puts("------------------");
    printf("\n%30s | %s | %s | %s | %s | %s | %s | %s \n", "ID", "END", "TIP", "ESC", "ROT", "CAT", "PAR", "NPAR");
    for(int i = 0; i < 100; i++) 
        printf(".");
    for(int i = 0; i < posTab; i++)
        printf("\n%30s | %3d | %s | %2c | %3d | %3c | %3d \n", tabSimb[i].id, tabSimb[i].end, tabSimb[i].tip == INT ? "INT" : "LOG", tabSimb[i].esc
        , tabSimb[i].rot, tabSimb[i].cat, tabSimb[i].npa);
    printf("\n");
}

void testaTipo(int tipo1, int tipo2, int ret){
    int t1 = desempilha('t');
    int t2 = desempilha('t');
    if(t1 != tipo1 || t2 != tipo2) yyerror("Incompatibilidade de tipo!");
    empilha(ret, 't');
}

// estrutura da pilha semantica
// usada para enderecos, variaveis, rotulos

#define TAM_PIL 100
struct {
    int valor;
    char tipo; // "r" = rotulo, "n" = nvars, "t" = tipo, "p" = posicaoTabSimb
}pilha[TAM_PIL];

int topo = -1;

void empilha (int valor, char tipo) {
    if (topo == TAM_PIL)
        yyerror("Pilha semântica cheia");
    pilha[++topo].valor = valor;
    pilha[topo].tipo = tipo;
}

int desempilha(char tipo) {
    if (topo == -1)
        yyerror("Pilha semântica vazia");
    if(pilha[topo].tipo != tipo)
        yyerror("Desimpilhamento ERRADO!");
    return pilha[topo--].valor;
}

void mostrapilha()
{
    int i = topo;
    printf("Pilha = [");
    while (i >= 0)
    {
        printf("(%d, %c)", pilha[i].valor, pilha[i].tipo);
        i--;
    }
    printf("]\n");
}

