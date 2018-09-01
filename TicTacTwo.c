/* Command line tictactoe or noughts & crosses, but with numbers I guess. */
#include <stdio.h>
#include <math.h>

#define ROWS 3
#define COLUMNS 3

void displayTheGrid(int grid[ROWS][COLUMNS]);
int checkIfGameEnded(int grid[ROWS][COLUMNS], int turn, int turnCounter);
int topLeftBottomRightCheck(int grid[ROWS][COLUMNS], int sumOfValues);
int topRightBottomLeftCheck(int grid[ROWS][COLUMNS], int sumOfValues);
int verticalCheck(int grid[ROWS][COLUMNS], int sumOfValues);
int horizontalCheck(int grid[ROWS][COLUMNS], int sumOfValues);

int main()
{

  /* Initialise main variables*/
  int grid[ROWS][COLUMNS];
  int x, y, getRow, getColumn;
  int gameOver = 0;
  int turn =  2;
  int turnCounter = 0;

  /* Initialise the grid */
  for(x=0;x<ROWS;x++)
		for(y=0;y<COLUMNS;y++)
			grid[x][y] = 0;

  /* Play the game */
  while(!gameOver)
  {
    /* display the grid */
    displayTheGrid(grid);

    /* update turns, check for a winner */
    turnCounter+=1;
    gameOver = checkIfGameEnded(grid, turn, turnCounter);
    if (gameOver) break; // end immediately
    turn = turn % 2 + 1; // alternate turns

    /* play current player's turn */
    printf("It is player %d's turn.\n",turn);
    while(1) {
      puts("Select a row");
      scanf("%d", &getRow);
      puts("Now select a column");
      scanf("%d",&getColumn);
      if (grid[getRow-1][getColumn-1] == 0)
      {
        grid[getRow-1][getColumn-1] = turn;
        break;
      }
      else {
        puts("Invalid space! Try again.\n");
        displayTheGrid(grid);
      }
    }
  };

  return 0;
}

int checkIfGameEnded(int grid[ROWS][COLUMNS], int turn, int turnCounter)
{
  printf("TurnCount %d\n", turnCounter);
  if (turnCounter < 6)
  {
    return 0;  // You can't win before your third move.
  }
  /* Victory conditions check */
  else if (topLeftBottomRightCheck(grid, 0) || topRightBottomLeftCheck(grid, 0) || verticalCheck(grid, 0) || horizontalCheck(grid, 0))
  {
    printf("Player %d is the winner!\n", turn);
    return 1;
  }
  /* Max turns limit */
  else if (turnCounter > 8)
  {
    puts("Stalemate!");
    return 1;
  }
  return 0;
}

void displayTheGrid(int grid[ROWS][COLUMNS])
{
  int x,y;
  for(x=0;x<ROWS;x++) {
    for(y=0;y<COLUMNS;y++)
      printf("|%d|\t",grid[x][y]);
    putchar('\n');
  }
  putchar('\n');
}

int topLeftBottomRightCheck(int grid[ROWS][COLUMNS], int sumOfValues)
{
  int x = 0;
  for (x=0;x<ROWS;x++)
  {
    if (grid[x][x] == 0)
      return 0;
    else
      sumOfValues = sumOfValues + grid[x][x];
  }
  if (sumOfValues % 3 == 0 && sumOfValues != 0)
    return 1;
  else
    return 0;
}

int topRightBottomLeftCheck(int grid[ROWS][COLUMNS], int sumOfValues)
{
  int x = 0, y = 2;
  while (x < ROWS)
  {
    if (grid[x][y] == 0)
      return 0;
    else {
      sumOfValues = sumOfValues + grid[x][y];
      x++, y--;
    }
  }
  if (sumOfValues % 3 == 0 && sumOfValues != 0)
    return 1;
  else
    return 0;
}

int verticalCheck(int grid[ROWS][COLUMNS], int sumOfValues)
{
  int x = 0,y;
  for (y=0;y<COLUMNS;y++)
  {
    x = 0;
    while (x<ROWS)
    {
      if (grid[x][y] == 0)
      {
        /* just move to next column */
        y++;
        x = 0;
        sumOfValues = 0;
      }
      else {
        sumOfValues = sumOfValues + grid[x][y];
        x++;
      }
    }
    if (sumOfValues % 3 == 0 && sumOfValues != 0)
    {
      printf("%d, X = %d, Y = %d\n", sumOfValues,x,y);
      printf("vertical\n");
      return 1;
    }
    sumOfValues = 0; // reset
  }
  return 0;
}

int horizontalCheck(int grid[ROWS][COLUMNS], int sumOfValues)
{
  int y = 0,x;
  for (x=0;x<ROWS;x++)
  {
    y = 0;
    while (y<COLUMNS)
    {
      if (grid[x][y] == 0)
      {
        /* just move to next row */
        x++;
        y = 0;
        sumOfValues = 0;
      }
      else {
        sumOfValues = sumOfValues + grid[x][y];
        y++;
        }
    }
    if (sumOfValues % 3 == 0 && sumOfValues != 0)
    {
      printf("%d, X = %d, Y = %d\n", sumOfValues,x,y);
      printf("HORIZONTAL\n");
      return 1;
    }
    sumOfValues = 0; // reset
  }
  return 0;
}
