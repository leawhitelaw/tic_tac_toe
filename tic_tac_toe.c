#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 9

/*****define struct for recording each move*****/
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

/*****functions for game*****/
char matrix[3][3];
int player;
void init_matrix();
void get_player_move(int player, struct move *);
void check_play(struct stack *, struct stack *);
void display_move(struct move *);
void display_board();
void undo();
void redo();
void replay();
void instructions();
char check_win();
char check_draw();
//void get_comp_move();

/*****functions for stacks*****/
void init_stack(struct stack *);
void push(struct stack *, struct move *);
struct move *pop(struct stack *);

/*****functions for queue*****/
void enqueue(struct move *, struct move *, int *, int *);
struct move *dequeue(struct move *, int *, int *);

int main()
{
	//init structs
	struct stack s1;
	struct stack s2;
	struct move move_arr;
	//init queues
	struct move arr[MAX];
  int front = -1, rear = -1;

	init_stack(&s1);
	init_stack(&s2);
	player=1;
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
		check_play(&s1, &s2);
		move_arr = s1.array[s1.top];
		enqueue(arr, &move_arr, &front, &rear);
		display_move(&move_arr);
		printf("\n\nPlayer %d enter X,Y co-ords for your move: ", player);
		get_player_move(player, &move_arr);
		display_move(&move_arr);
		push(&s1, &move_arr);
		done = check_win();
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

/*****Initialise the board*****/
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

/*****display each move*****/
void display_move(struct move *move_arr)
{
	if(move_arr->player == 1){
		matrix[move_arr->x][move_arr->y] = 'X';
	}
	else if(move_arr->player == 2){
		matrix[move_arr->x][move_arr->y] = 'O';
	}
}

/*****get move from each player*****/
void get_player_move(int player, struct move *move_arr)
{
	int x, y;

	int check = scanf("%d%*c%d",&x, &y);
	printf("check is %d:", check);
	/*if(check!= 2 || !(isdigit(x)) || !(isdigit(y))){
		printf("Please enter integer X and Y co-ordinates in the format \"X,Y\"'.\n");
		get_player_move(player, move_arr);
	}*/

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

/*****check for undo, redo, play or replay*****/
void check_play(struct stack *s1, struct stack *s2)
{
	struct move move;
	printf("\n\nEnter 'u' to undo, 'r' to redo or any character to continue play: \n");
	char choice;
	int check = scanf(" %c", &choice);
	printf("check is %d:", check);
	if(check != 1 || !(isalpha(choice))){
		printf("Please enter 1 alphabetical character only.\n");
		check_play(s1,s2);
	}
	if(choice == 'u'){
		move = *pop(s1);
		matrix[move.x][move.y]=' ';
		player = move.player;
		push(s2, &move);
		display_board();
		check_play(s1,s2);
	}
	if(choice == 'r'){
		move = *pop(s2);
		if(move.player==1){
			player =2;
			matrix[move.x][move.y]='X';
		}
		else if(move.player==2){
			player =1;
			matrix[move.x][move.y]='O';
		}
		display_board();
		check_play(s1,s2);
	}
	return;
}

/*****check if players have drawn*****/
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


/*****display game board*****/
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

/*****check if player has won*****/
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

/*****initialise stack*****/
void init_stack(struct stack *s)
{
  s->top = -1;
}

/*****push(add) to stack*****/
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

/*****pop(remove) from stack*****/
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

/*****enqueue(add) to queue*****/
void enqueue(struct move *arr, struct move *item, int *pfront, int *prear)
{
  if(*prear == MAX-1)
  {
    printf("Queue is full\n");
    return;
  }
  else
  {
    (*prear)++;
    arr[*prear] = *item;

    if(*pfront == -1)
    {
      *pfront =0;
    }
  }
}

/*****dequeue(remove) from queue*****/
struct move *dequeue(struct move *arr, int *pfront, int *prear)
{
  struct move *data = &arr[*pfront];

//  arr[*pfront] = 0;
  if(*pfront == *prear)
    *pfront = *prear = -1;
  else
    (*pfront)++;
  return data;
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
