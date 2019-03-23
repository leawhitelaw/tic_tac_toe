#include <stdio.h>
#include <stdlib.h>

char matrix[3][3]; // two dimensional array/matrix
char check();
void init_matrix();
void get_player_move(int player);
void get_comp_move();
void display_board();
void undo();
void redo();
void replay();
void instructions();
char check_win();

int main()
{
	int player=1;
	char done;
	printf("\n\nWelcome to Tic Tac Toe.\n");
	printf("\nYou are playing in two-player mode.\n\n");

	done=' ';
	init_matrix();

	do{
		display_board();
		get_player_move(player);
		done = check_win(); //see if anyone has won
		if(done!=' ') break;
		if(player==1){
			player=2;
		}
		else{
			player=1;
		}
		get_player_move(player);
		done = check_win();
	}while(done==' ');

	if(done=='X') printf("CONGRATULATIONS! You have WON!\n");
	else printf("HA! I have beaten you!\n");
	display_board(); //show final positions

	return 0;
}

//Initialise Matrix/Board
void init_matrix()
{
	int i, j;
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			matrix[i][j] = ' ';
		}
	}
}
//get move from player 1
void get_player_move(int player)
{
	int x, y;

	printf("\n\nPlayer %d enter X,Y co-ords for your move: ", player);
	scanf("%d%*c%d",&x, &y);

	x--; y--;

	if(matrix[x][y]!=' '){
		printf("Invalid move, choose and empty space.\n");
		get_player_move(player);
	}
	else
	{
		if(player == 1){
			matrix[x][y] = 'X';
		}
		else if(player == 2){
			matrix[x][y] = 'O';
		}
	}
}

void get_comp_move()
{
	int i, j;
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			if(matrix[i][j]==' ') break;
		}
		if(matrix[i][j]==' ') break;
	}

	if(i*j==9)
	{
		printf("Draw\n");
		exit(0);
	}
	else
	{
		matrix[i][j] = 'O';
	}
}
// Display board on screen
void display_board()
{
	int i;

	printf("   Y   Y   Y  \n");
	for(i=0; i<3; i++)
	{
		printf("X  %c | %c | %c ", matrix[i][0], matrix[i][1], matrix[i][2]);
		if(i!=2) printf("\n  ---|---|---\n");
	}
	printf("\n");
}
// check if someone has won
char check_win()
{
	int i;

	//check rows
	for(i=0; i<3; i++)
	{
		if(matrix[i][0]==matrix[i][1] &&
				matrix[i][0]==matrix[i][2])
				return matrix[i][0];
	}
	//check columns
	for(i=0; i<3; i++)
	{
		if(matrix[0][i]==matrix[1][i] &&
				matrix[0][i]==matrix[2][i])
				return matrix[0][i];
	}
	//check diagonals
	if(matrix[0][0]==matrix[1][1] && matrix[1][1] == matrix[2][2])
	{
		return matrix[0][0];
	}
	if(matrix[0][2]==matrix[1][1] && matrix[1][1]==matrix[2][0])
	{
		return matrix[0][2];
	}
	return ' ';
}
