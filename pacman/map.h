#define HERO '@'
#define GHOST 'F'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'

struct Pos {
  int x;
  int y;
};

typedef struct Pos Position;

struct GameMap {
  char** matrix;
  int lines;
  int columns;
};

typedef struct GameMap Map;

int findInMap(Map* map, Position* pos, char c);
void freeMap(Map* map);
void readMap(Map* map);
void alocateMap(Map* map);
void drawMap(Map* map);
int nextPositionIsValid(Map* map, int x, int y);
void walkInMap(Map* map, int originX, int originY, int nextX, int nextY);
void copyMap(Map* destinyMap, Map* originMap);
int canWalk(Map* map, char person, int x, int y);
int isPerson(Map* map, int x, int y, char person);
int isWall(Map* map, int x, int y);