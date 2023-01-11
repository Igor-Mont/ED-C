#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "map.h"

Map map;
Position hero;

int endGame() {
  Position pos;
  int isAlive = findInMap(&map, &pos, HERO);
  return !isAlive;
}

int whereDoesGhostGo(int currentX, int currentY, int* destinyX, int* destinyY) {
  int options[4][2] = {
    { currentX, currentY+1 },
    { currentX+1, currentY },
    { currentX, currentY-1 },
    { currentX-1, currentY+1 },
  };

  srand(time(0));
  for(int i = 0; i < 10; i++) {
    int pos = rand() % 4;
    if(canWalk(&map, GHOST, options[pos][0], options[pos][1])) {
      *destinyX = options[pos][0];
      *destinyY = options[pos][1];

      return 1;
    }
  }

  return 0;
}

void ghosts() {
  Map copy;

  copyMap(&copy, &map);

  for(int i = 0; i < map.lines; i++) {
      for(int j = 0; j < map.columns; j++) {
        if(copy.matrix[i][j] == GHOST) {
          int destinyX;
          int destinyY;

          int ghostCanWalk = whereDoesGhostGo(i, j, &destinyX, &destinyY); 
          
          if(ghostCanWalk) {
            walkInMap(&map, i, j, destinyX, destinyY);
          }
        }
    }
  }

  freeMap(&copy);
}

int isInvalidDirection(char direction) {
  return direction != UP && direction != LEFT && direction != DOWN && direction != RIGHT;
}

void move(char direction) {
  if(isInvalidDirection(direction)) return;

  int nextX = hero.x;
  int nextY = hero.y;

  switch (direction) {
    case LEFT:
      nextY--;
      break;
    case UP:
      nextX--;
      break;
    case DOWN:
      nextX++;
      break;
    case RIGHT:
      nextY++;
      break;
  }

  if(!canWalk(&map, HERO, nextX, nextY)) return;

  walkInMap(&map, hero.x, hero.y, nextX, nextY);

  hero.x = nextX;
  hero.y = nextY;

}

int main() {
  readMap(&map);
  findInMap(&map, &hero, HERO);

  do {
    drawMap(&map);

    char command;
    scanf(" %c", &command);
    move(command);
    ghosts();

  } while(!endGame());

  freeMap(&map);

}