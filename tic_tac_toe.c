#include <stdio.h>
#include <stdlib.h>
#define MAX 9

struct move{
	char x;
	char y;
	int player;
};

struct stack
{
  struct move array[MAX];
  int top;
};

// functions for tic-tac-toe
char matrix[3][3];
void init_matrix();
void get_player_move(int player, struct move *);
struct move check_play(struct stack *);
void display_move(struct move *);
//void get_comp_move();
void display_board();
void undo();
void redo();
void replay();
//void instructions();
char check_win();
char check_draw();

//functions for stacks
void init_stack(struct stack *);
void push(struct stack *, struct move *);
struct move *pop(struct stack *);

int main()
{
	struct stack s1;
	struct stack s2;
	struct move move_arr;
	init_stack(&s1);
	int player=1;
	char done;
	char play;
	printf("\n\n          WELCOME TO ");
	printf("\n _________   ________   ________ ");
	printf("\n|___   ___| |___  ___| |___  ___| ");
	printf("\n   |  |        |  |       |  | ");
	printf("\n   |  |        |  |       |  | ");
	printf("\n   |__|IC      |__|AC     |__|OE");
	printf("\n\nYou are playing in two-player mode.\n\n");

	done=' ';
	init_matrix();

	do{
		display_board();
		printf("\n\nEnter 'u' to undo or 'p' to continue play: ");
		check_play(&s1);
		display_move(&move_arr);
		printf("\n\nPlayer %d enter X,Y co-ords for your move: ", player);
		get_player_move(player, &move_arr);
		display_move(&move_arr);
		push(&s1, &move_arr);
		done = check_win(); //see if anyone has won
		done = check_draw();
		if(done!=' ') break;
		if(player==1){
			player=2;
		}
		else{
			player=1;
		}
	}while(done==' ');

	if(done=='X') printf("CONGRATULATIONS Player 1: You have WON!\n");
	else if(done=='O') printf("CONGRATULATIONS Player 2: You have  WON!\n");
	else if(done=='D') printf("Unfortunately we have come to a draw! To play again type 'Y', otherwise press enter to quit.\n");
	scanf("%c", &play);
	if(play == 'Y'){
		done = ' ';
	}
	else{
		return 0;
	}
	//printf("HA! I have beaten you!\n");
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
void display_move(struct move *move_arr)
{
	if(move_arr->player == 1){
		matrix[move_arr->x][move_arr->y] = 'X';
	}
	else if(move_arr->player == 2){
		matrix[move_arr->x][move_arr->y] = 'O';
	}
}
//get move from player 1
void get_player_move(int player, struct move *move_arr)
{
	int x, y;

	scanf("%d%*c%d",&x, &y);

	x--; y--;

	if(matrix[x][y]!=' '){
		printf("Invalid move, choose and empty space.\n");
		get_player_move(player, move_arr);
	}
	else
	{
		move_arr->x = x;
		move_arr->y = y;
		move_arr->player = player;
	}
}
struct move check_play(struct stack *s1)
{
	char play;
	scanf("%c", &play);
	if(play == 'p'){
		return s1->array[s1->top];
	}
	else if(play == 'u'){
		pop(s1);
		return s1->array[s1->top];
	}
	return s1->array[s1->top];
}
char check_draw()
{
	int i, j;
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			if(matrix[i][j]==' ') return ' ';
		}
		if(matrix[i][j]==' ') return ' ';
	}
	return 'D';
}
/*void get_comp_move()
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
}*/
// Display board on screen
void display_board()
{
	int i;
	int x = 1;

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

void init_stack(struct stack *s)
{
  s->top = -1;
}
void push(struct stack *s, struct move *item)
{
  if(s->top == MAX -1)
  {
    printf("Stack is full. Couldn't push move onto stack\n");
    return;
  }
  s->top++;
  s->array[s->top] = *item;
}
struct move *pop(struct stack *s)
{
  struct move *data;
  if(s->top == -1)
  {
    printf("Stack is empty\n");
    return NULL;
  }
  data = &s->array[s->top];
  s->top--;
  return data;
}
