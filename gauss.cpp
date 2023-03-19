#include <stdio.h>
#include <time.h>
#define MAX 380
#define fin "gauss.in"
#define fout "gauss.out"
#define EPS 0.00000001

double matrix[MAX][MAX],//the matrix
       xsol[MAX]; //the array of solutions: x1, x2, x2
int n, //rows
    m; //columns

int main(int argc, char const *argv[]) {

  clock_t start = clock();
  freopen(fin, "r", stdin);
  freopen(fout, "w", stdout);

  //read the matrix
  scanf("%d %d", &n, &m);

  for(int i = 1; i <= n; ++i) {

    for(int j = 1; j <= m+1; ++j) {

      scanf("%lf", &matrix[i][j]);
    }
  }

  int i = 1, j = 1, k;
  double aux;

  while(i <= n && j <= m) {

    //search for a line for which mat[k][j] is != 0
    for(k = i; k <= n; ++i)
        if(matrix[k][j] -EPS || matrix[k][j] > EPS)
          break;

    if(k == n + 1) {
      ++j;
      continue;
    }

    if( k != i ) {
       for(int l = 1; l <= m + 1; l++) {
         aux = matrix[i][l];
         matrix[i][l] = matrix[k][l];
         matrix[k][l] = aux;
       }
    }

    //divide first line with matrix[i][j]
    for(int l = j + 1; l <= m + 1; l++) {

        matrix[i][l] /= matrix[i][j];
    }
    matrix[i][j] = 1;

    //substruct Eq2 - Eq1
    for( int nextLine = i + 1; nextLine <= n; ++nextLine ) {

        for( int c = j + 1; c <= m + 1; ++c )

            matrix[ nextLine ][ c ] -= matrix[ nextLine ][ j ] * matrix[ i ][ c ];

        matrix[ nextLine ][ j ] = 0;
    }

    i++;
    j++;
  }

  for(int i = n; i > 0; --i)

     for(int j = 1; j <= m + 1; j++)

       if(matrix[ i ][ j ] > EPS || matrix[i][j] < -EPS) {

          if(j == m + 1) {
            printf("Imposibil\n");
            return 0;
          }

          xsol[j] = matrix[i][m+1];

          for(int k = j + 1; k <= m; ++k)
            xsol[j] -= xsol[k] * matrix[i][k];

            break;
        }

  for(int j = 1; j <= m; j++) printf("%.8lf ", xsol[j]);
  printf("\n");
  clock_t end = clock();
  double time_spent = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Running Time Spent: %lf", time_spent);
  return 0;
}
