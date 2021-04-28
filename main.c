#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 20
bool flag = false;
int jogadas = 0;
int NumBombs;

void preenche_matriz(char M[][N], int n);
void sorteia_bombas(char M[][N], int n);
void imprime_mat(char M[][N], int n);
void checa_jogada(char M[][N], int n);
void checa_numero(char M[][N], int n, int x, int y);
//int n_bombas(int i, int c, char M[][N], int n);

int main(void) {
  int n;
  char M[N][N];
  printf("Defina o tamanho da matriz: ");
  scanf("%d", &n);
  preenche_matriz(M, n);
  sorteia_bombas(M, n);
  imprime_mat(M, n);
  do{
    //printf("Jogadas: %d\n", jogadas);
    jogadas++;
    checa_jogada(M, n);
    imprime_mat(M, n);
  }while(!flag);
}



int percorre_matriz(char M[][N], int n, int op, int oq, int ip, int iq, int fp, int fq){
  int a = 0;
  for(int i = ip; i < fp; i++){
    for(int j = iq; j < fq; j++){
      if(M[i][j] == '*') a++;
    }  
  }
  return a;
}

int n_bombas(int i, int c, char M[][N], int n){
  int num;
    if(i == 0 && c == 0) num = percorre_matriz(M, n, i, c, i, c, 2, 2);  
    if(i == n - 1 && c == 0) num = percorre_matriz(M, n, i, c, i - 1, c, n, 2);
    if(i == 0 && c == n - 1) num = percorre_matriz(M, n, i, c, i, c - 1, n - 1, n);
    if(i == n - 1 && c == n - 1) num = percorre_matriz(M, n, i, c, i - 1, c - 1, n, n);
  
    //quadrado externo 2x3 ou 3x2
    if(i == 0 && (c > 0 && c < n - 1)) num = percorre_matriz(M, n, i, c, i, c - 1, i + 2, c + 2); //superior
    if(i == n - 1 && (c > 0 && c < n - 1)) num = percorre_matriz(M, n, i, c, i - 1, c - 1, i + 2, c + 2);  //inferior
    if(c == 0 && (i > 0 && i < n - 1)) num = percorre_matriz(M, n, i, c, i - 1, c, i + 2, c + 2); //lateral esquerda ta bugando aqui
    if(c == n - 1 && (i > 0 && i < n - 1)) num = percorre_matriz(M, n, i, c, i - 1, c - 1, i + 2, c + 1); //lateral direita

    //quadrado interno 3x3
    if((i > 0 && i < n - 1) && (c > 0 && c < n -1))num = percorre_matriz(M, n, i, c, i - 1, c - 1, i + 2, c + 2);
    return num;
}

void checa_numero(char M[][N], int n, int x, int y){
  int r;
  r = n_bombas(x, y, M, n);
  M[x][y] = r + '0';
  /*
    if(x == 0 && y == 0) percorre_matriz(M, n, x, y, x, y, 2, 2);  
    if(x == n - 1 && y == 0) percorre_matriz(M, n, x, y, x - 1, y, n, 2);
    if(x == 0 && y == n - 1) percorre_matriz(M, n, x, y, x, y - 1, n - 1, n);
    if(x == n - 1 && y == n - 1) percorre_matriz(M, n, x, y, x - 1, y - 1, n, n);
  
    //quadrado externo 2x3 ou 3x2
    if(x == 0 && (y > 0 && y < n - 1))percorre_matriz(M, n, x, y, x, y - 1, x + 2, y + 2); //superior
    if(x == n - 1 && (y > 0 && y < n - 1))percorre_matriz(M, n, x, y, x - 1, y - 1, x + 2, y + 2);  //inferior
    //if(y == 0 && (x > 0 && x < n - 1))percorre_matriz(M, n, x, y, x - 1, y, x + 2, y + 2); //lateral esquerda
    if(y == n - 1 && (x > 0 && x < n - 1))percorre_matriz(M, n, x, y, x - 1, y - 1, x + 2, y + 1); //lateral direita

    //quadrado interno 3x3
    if((x > 0 && x < n - 1) && (y > 0 && y < n -1))percorre_matriz(M, n, x, y, x - 1, y - 1, x + 2, y + 2);*/
}

void checa_jogada(char M[][N], int n){
  int x, y;
  printf("\nDigite a linha e coluna desejada: ");
  scanf("%d %d", &x, &y);
  if((x < 1 || x > n) || (y < 1 || y > n)){
    printf("Entrada invalida\n");
    jogadas--;
  }else{
    x--;
    y--;
    if(M[x][y] == '*') {
      flag = true;
      printf("\nVOCE PERDEU! FIM DE JOGO.\n\n");
    }else{
      //printf("total de jogadas %d\n", ((n*n) - NumBombs));
      if(M[x][y] != '?') {
      jogadas--;
    }else{

      if(jogadas == ((n*n) - NumBombs)){
        flag = true;
        printf("PARABENS! VOCE VENCEU!\n\n");
        checa_numero(M, n, x, y);
      }else{
        checa_numero(M, n, x, y);
      }
    }
    }
  }
}

void imprime_mat(char M[][N], int n){
   for(int i = 0; i < n; i++){
    printf("%d |", i + 1);
    for(int j = 0; j < n; j++){
      //if(M[i][j] == '*' && !flag) printf(" ? ");
      //else 
      printf(" %c ", M[i][j]); 
    }
    printf("\n");
  }
  for(int i = 0; i < 2; i++){
    printf("   ");
    for(int j = 0; j < n; j++){
      if(i == 0) printf("---");
      else printf(" %d ", j + 1);
    }
    printf("\n");
  }
}

void sorteia_bombas(char M[][N], int n){
  srand(time(NULL));
  int x, y;
  NumBombs = 0.2 * (n * n);
  for(int i = 0; i < NumBombs; i++){
    x = rand() % n;
    y = rand() % n;
    printf("%d %d\n", x + 1, y + 1);
    if(M[x][y] == '*'){
      do{
        x = rand() % n;
        y = rand() % n;
        printf("do-while: %d %d\n", x + 1, y + 1);
        //bug: ta sorteando novamento mesmo com o local n preenchido com *
      }while(M[x][y] == '*');
      M[x][y] = '*';
    }else M[x][y] = '*';
  }
}

void preenche_matriz(char M[][N], int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      M[i][j] = '?';
    }
  }
}