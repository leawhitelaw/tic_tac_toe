#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
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
void instructions();
char check_win();
char check_draw();
void clear();

/*****functions for stacks*****/
void init_stack(struct stack *);
void push(struct stack *, struct move *);
struct move *pop(struct stack *, struct stack *, struct stack*);

/*****functions for queue*****/
void enqueue(struct move *, struct move *, int *, int *);
struct move *dequeue(struct move *, int *, int *);

void delay(int);

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
	char done, draw, play, commit;
	printf("\n\n          WELCOME TO ");
	printf("\n _________   ________   ________ ");
	printf("\n|___   ___| |___  ___| |___  ___| ");
	printf("\n   |  |        |  |       |  | ");
	printf("\n   |  |        |  |       |  | ");
	printf("\n   |__|IC      |__|AC     |__|OE");
	printf("\n\nYou are playing in two-player mode.\n\n");

	draw=' ';
	done=' ';
	init_matrix();

	do{
		display_board();
		check_play(&s1, &s2);
		move_arr = s1.array[s1.top];
		display_move(&move_arr);
		printf("\n\nPlayer %d enter X,Y co-ords for your move: ", player);
		get_player_move(player, &move_arr);
		display_move(&move_arr);
		push(&s1, &move_arr);
		enqueue(arr, &move_arr, &front, &rear);
		done = check_win();
		draw = check_draw();
		if(done!=' ' || draw !=' ') break;
		if(player==1){
			player=2;
		}
		else{
			player=1;
		}
	}while(done==' ' && draw==' ');

	display_board(); //show final positions
	if(done=='X') printf("CONGRATULATIONS Player 1: You have WON! To play again type 'y', to watch a replay enter 'p', otherwise enter 'q' to quit.\n");
	else if(done=='O') printf("CONGRATULATIONS Player 2: You have  WON! To play again type 'y', to watch a replay enter 'p', otherwise enter 'q' to quit.\n");
	else if(draw=='D') printf("Unfortunately we have come to a draw! To play again type 'y', to watch a replay enter 'p', otherwise enter 'q' to quit.\n");
	clear();
	scanf(" %c", &play);

	if(play == 'Y' || play == 'y'){
		done = ' ';
		draw = ' ';
		init_matrix();
		main();
	}
	else if(play == 'p'){
		struct move *mv;
		init_matrix();
		int i;
		for(i=0; i<10; i++){
			mv = dequeue(arr, &front, &rear);
			display_board();
			display_move(mv);
			delay(1500);
		}
	}else{
		return 0;
	}
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
	clear();
	int x, y;

	int check = scanf("\n%d%*c%d",&x, &y);
	if(check== 2){
		x--; y--;

		if(matrix[x][y]!=' '){
			printf("Invalid move, choose an empty space.\n");
			get_player_move(player, move_arr);
		}
		else
		{
			move_arr->x = x;
			move_arr->y = y;
			move_arr->player = player;
		}
	}
	else{
		printf("Please enter integer X and Y co-ordinates in the format \"X,Y\"'.\n");
		get_player_move(player, move_arr);
	}
}

/*****check for undo, redo, play or replay*****/
void check_play(struct stack *s1, struct stack *s2)
{
	struct move move;
	printf("\n\nEnter 'u' to undo, 'r' to redo, 'i' for instructions OR any other character to continue play: \n");
	char choice;
	int check = scanf(" %c", &choice);
	if(check != 1){
		printf("Please enter 1 alphabetical character only.\n");
		check_play(s1,s2);
	}
	if(choice == 'u' || choice == 'U'){
		move = *pop(s1, s1, s2);
		matrix[move.x][move.y]=' ';
		player = move.player;
		push(s2, &move);
		display_board();
		check_play(s1,s2);
	}
	if(choice == 'r' || choice == 'R'){
		move = *pop(s2, s1, s2);
		push(s1, &move);
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
	if(choice == 'i' || choice == 'I'){
		instructions();
	}
	return;
}

/*****display game board*****/
void display_board()
{
	int i;
	int x = 1;
	printf("      Y   Y   Y\n");
	printf("\n      1   2   3  \n");
	for(i=0; i<3; i++)
	{
		printf("X  %d  %c | %c | %c ", i+1, matrix[i][0], matrix[i][1], matrix[i][2]);
		if(i!=2) printf("\n     ---|---|---\n");
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
		if(matrix[i][0]== matrix[i][1] && matrix[i][0]==matrix[i][2])
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
/*****check for draw*****/
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
struct move *pop(struct stack *s, struct stack *s1, struct stack *s2)
{
  struct move *data;
  if(s->top == -1)
  {
    printf("Cannot repeat this action any futher.\n");
    if(s1->top == -1){
			data = &s2->array[s2->top];
			return data;
		}else{
			data = &s1->array[s1->top];
			return data;
		}
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
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}
void clear()
{
	while(getchar()!='\n');
}
void instructions()
{
	printf("\n\n          WELCOME TO TIC TAC TOE ");
	printf("\n\n You are playing in two player mode. ");
	printf("\n Each player is automatically assigned an 'X' or an 'O'.");
	printf("\n To make a move, type in the x, y co-ordinates of the square which you wish to place your mark.");
	printf("\n After a move has been made, you can enter 'u' to undo a move and 'r' to redo it.");
	printf("\n Once a new move has been made, old moves cannot be redone.");
	printf("\n To win the game, you must get a combination of 3 of you character in a row (including diagonals).");
	printf("\n To exit the game, press Ctrl + c.");
}
