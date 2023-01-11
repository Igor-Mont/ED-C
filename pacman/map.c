#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

void copyMap(Map* destinyMap, Map* originMap) {
  destinyMap->lines = originMap->lines;
  destinyMap->columns = originMap->columns;
  alocateMap(destinyMap);
  for(int i = 0; i < originMap->lines; i++) {
    strcpy(destinyMap->matrix[i], originMap->matrix[i]);
  }
}

void walkInMap(Map* map, int originX, int originY, int nextX, int nextY) {
  char character = map->matrix[originX][originY];
  map->matrix[nextX][nextY] = character;
  map->matrix[originX][originY] = EMPTY;
}

int nextPositionIsValid(Map* map, int x, int y) {
  if(x >= map->lines) return 0;
  if(y >= map->columns) return 0;

  return 1;
}

int isWall(Map* map, int x, int y) {
  return map->matrix[x][y] == VERTICAL_WALL || map->matrix[x][y] == HORIZONTAL_WALL;
}

int isPerson(Map* map, int x, int y, char person) {
  return map->matrix[x][y] == person;
}

int canWalk(Map* map, char person, int x, int y) {
  return nextPositionIsValid(map, x, y) && !isWall(map, x, y) && !isPerson(map, x, y, person);
}

int findInMap(Map* map, Position* pos, char c) {
  for(int i = 0; i < map->lines; i++) {
    for(int j = 0; j < map->columns; j++) {
      if(map->matrix[i][j] == c) {
        pos->x = i;
        pos->y = j;
        return 1;
      }
    }
  }
  
  return 0;
}

void freeMap(Map* map) {
  for(int i = 0;i < map->lines; i++) {
    free(map->matrix[i]);
  }
  free(map->matrix);
}

void alocateMap(Map* map) {
  map->matrix = malloc(sizeof(char*) * map->lines);
  for (int i = 0; i < map->lines; i++) {
    map->matrix[i] = malloc(sizeof(char) * (map->columns + 1));
  }
}

void readMap(Map* map) {
  FILE* f;
  f = fopen("map.txt", "r");

  if(f == 0) {
    printf("Map reading error\n");
    exit(1);
  }

  fscanf(f, "%d %d", &map->lines, &map->columns);

  alocateMap(map);

  for(int i = 0; i < 5; i++) {
    fscanf(f, "%s", map->matrix[i]);
  }
  
  fclose(f);
}

void drawMap(Map* map) {
    for(int i = 0; i < 5; i++) {
    printf("%s\n", map->matrix[i]);
  }
}