#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 20

bool Q = false;
int W = 0;
int B;

void preenche_matriz(char M[][N], int n);
void sorteia_bombas(char M[][N], int n);
void imprime_mat(char M[][N], int n);
void checa_jogada(char M[][N], int n);
void checa_numero(char M[][N], int n, int x, int y);
int n_bombas(int i, int c, char M[][N], int n);
int percorre_matriz(char M[][N], int ip, int iq, int fp, int fq);

int main(void) {
  int n;
  char M[N][N];
  printf("Defina o tamanho da matriz: ");
  scanf("%d", &n);
  preenche_matriz(M, n);
  sorteia_bombas(M, n);
  imprime_mat(M, n);
  do{
    W++;
    checa_jogada(M, n);
    imprime_mat(M, n);
  }while(!Q);
}



int percorre_matriz(char M[][N], int ip, int iq, int fp, int fq){
  int x = 0;
  for(int i = ip; i < fp; i++){
    for(int j = iq; j < fq; j++){
      if(M[i][j] == '*') x++;
    }  
  }
  return x;
}

int n_bombas(int l, int c, char M[][N], int n){
  int x;
  if(l == 0 && c == 0) x = percorre_matriz(M, l, c, 2, 2);  
  if(l == n - 1 && c == 0) x = percorre_matriz(M, l - 1, c, n, 2);
  if(l == 0 && c == n - 1) x = percorre_matriz(M, l, c - 1, 2, n);
  if(l == n - 1 && c == n - 1) x = percorre_matriz(M,  l - 1, c - 1, n, n); 
  if(l == 0 && (c > 0 && c < n - 1)) x = percorre_matriz(M, l, c - 1, l + 2, c + 2); 
  if(l == n - 1 && (c > 0 && c < n - 1)) x = percorre_matriz(M, l - 1, c - 1, l + 2, c + 2); 
  if(c == 0 && (l > 0 && l < n - 1)) x = percorre_matriz(M, l - 1, c, l + 2, c + 2); 
  if(c == n - 1 && (l > 0 && l < n - 1)) x = percorre_matriz(M, l - 1, c - 1, l + 2, c + 1); 
  if((l > 0 && l < n - 1) && (c > 0 && c < n -1)) x = percorre_matriz(M, l - 1, c - 1, l + 2, c + 2);
  return x;
}

void checa_numero(char M[][N], int n, int x, int y){
  int r;
  r = n_bombas(x, y, M, n);
  M[x][y] = r + '0';
}

void checa_jogada(char M[][N], int n){
  int x, y;
  printf("\nDigite a linha e coluna desejada: ");
  scanf("%d %d", &x, &y);
  if((x < 1 || x > n) || (y < 1 || y > n)){
    printf("Entrada invalida\n");
    W--;
  }else{
    x--;
    y--;
    if(M[x][y] == '*') {
      Q = true;
      printf("\nVOCE PERDEU! FIM DE JOGO.\n\n");
    }else{
      if(M[x][y] != '?') {
      W--;
    }else{
      if(W == ((n*n) - B)){
        Q = true;
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
    if(n > 9 && i < 9) printf(" %d |", i + 1);
    else printf("%d |", i + 1);
    for(int j = 0; j < n; j++){
      if(M[i][j] == '*' && !Q) printf(" ? ");
      else printf(" %c ", M[i][j]); 
    }
    printf("\n");
  }
  for(int i = 0; i < 2; i++){
    if(n > 9) printf("    ");
    else printf("   ");
    for(int j = 0; j < n; j++){
      if(i == 0) printf("---");
      else {
        if(n > 9 && j > 8) printf(" %d", j + 1);
        else printf(" %d ", j + 1);
        }
    }
    printf("\n");
  }
}

void sorteia_bombas(char M[][N], int n){
  srand(time(NULL));
  int x, y;
  B = 0.2 * (n * n);
  for(int i = 0; i < B; i++){
    x = rand() % n;
    y = rand() % n;
    if(M[x][y] == '*'){
      do{
        x = rand() % n;
        y = rand() % n;
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