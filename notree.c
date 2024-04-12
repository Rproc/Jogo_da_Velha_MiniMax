#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio_ext.h>

#define TRUE 1;
#define FALSE 0;
int const SIZE = 3;

void CopiaGrid(int *antiga[], int *nova[]);
void iniciagrid(int *grid[SIZE]);
void printaGrid(int *grid[SIZE]);
int minimax(int *grid[SIZE], int player);
int verificaFim(int *grid[SIZE]);
void cpuJogada(int *grid[SIZE]);
char retornaCaracter(int letra);

int main( int argc, const char* argv[]){
	int **grid = (int**)malloc(SIZE * sizeof(int*));

	int player = 3, coluna, linha, playAgain = 1; 

	do{
		player = 10;
		while(player!=0 && player!=1){
			printf("\nDigite 1 para a cpu comecar ou 0 para voce comecar.\n");
			scanf(" %d",&player);
		}

		iniciagrid(grid);
		printaGrid(grid);

		if(player==0){
			printf("Digite linha e coluna separadas por espaços (0 à 2)\n");
			scanf("%d %d",&linha,&coluna);

			grid[linha][coluna] = -1; 

		}else
			cpuJogada(grid);
		

		printaGrid(grid);

		for(int i = 0; i < 8 && verificaFim(grid)==0; i++){
			printf("\n-----%d----\n", i);

			if((i+player) % 2 == 0){
		  		cpuJogada(grid);
		  		printaGrid(grid);

			}else {
				printf("Digite linha e coluna separadas por espaços (0 à 2)\n");
				scanf("%d %d",&linha,&coluna);

			    grid[linha][coluna] = -1; 
			    printaGrid(grid);
			}
		}

		puts("\n\n");

		int win = verificaFim(grid);

		if (win == 0)
			printf("\n Deu velha\n");

		else if (win == 1)
			printf("\nCpu Ganhou\n");

		else
			printf("\nVocê Ganhou???????\n");

		printaGrid(grid);

		puts("Deseja jogar novamente? 1 para sim e 0 para não");
		scanf("%d",&playAgain);

		printf("\e[H\e[2J");

		fflush(stdin);
    	__fpurge(stdin);

	}while (playAgain != 0);
}

void cpuJogada(int *grid[SIZE]){
	int linha = -1, coluna = -1;
	int score = -2;
	int i=0,j,k;
	for(int j = 0; j < SIZE; j++){
		for(int k = 0; k < SIZE; k++){
			if(grid[j][k] == 0){

				grid[j][k] = 1;
				int temp = -minimax(grid, -1);
				grid[j][k] = 0;

				if(temp>score){
					score = temp;
					linha = j;
					coluna = k;
				}
			}
		}	
	}
	grid[linha][coluna] = 1;
}

int minimax(int *grid[SIZE], int player){ 

	int fim = verificaFim(grid);
	if(fim != 0)
		return fim *player;

	int linha = -1;
	int coluna = -1;
	int score = -2;
	// int i=0,j,k;

	for(int j = 0; j < SIZE; j++){
		for(int k = 0; k < SIZE; k++){

			if(grid[j][k] == 0){
				grid[j][k] = player;
				int temp = -minimax(grid, player*-1);
				grid[j][k] = 0;

				if(temp > score){
					score = temp;
					linha = j;
					coluna = k;
				}
			}
		}			
	}

	if(linha == -1 || coluna == -1)
		return 0;

	return score;
}

int verificaFim(int *grid[SIZE]){
	// int i,j,k;
	for(int i = 0; i < SIZE; i++){
		if(grid[i][0] !=0 && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] )
			return grid[i][0];
	}

	for(int i = 0; i < SIZE; i++){
		if(grid[0][i] !=0 && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
			return grid[0][i];
	}

	if(grid[0][0] !=0 && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
		return 	grid[0][0];

	if(grid[0][2] !=0 && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
		return grid[0][2];

	return 0;
}

void CopiaGrid(int *antiga[], int *nova[]){
	// int i,j;
	for(int i = 0; i < SIZE; i++){
		nova[i] = (int*)malloc(SIZE * sizeof(int));
		for(int j = 0; j < SIZE; j++){
			nova[i][j] = antiga[i][j];
		}
	}
}

void iniciagrid(int *grid[SIZE]){
	// int i=0,j=0; 
	for(int i = 0; i < SIZE; i++){
		grid[i] = (int*)malloc(SIZE * sizeof(int));
		for(int j = 0; j < SIZE; j++){
			grid[i][j] = 0;
		}
	}
}

void printaGrid(int *grid[SIZE]){
	// int i,j;
	printf("\n");
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			printf(" %c ", retornaCaracter(grid[i][j]));

			if(j!= SIZE-1)
				printf("|");
		}

		if(i!= SIZE-1)
			printf("\n---+---+---\n");
	}
	printf("\n");
}

char retornaCaracter(int letra){

	 switch(letra) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}
