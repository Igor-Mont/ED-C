#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

int isInvalidDirection(char direction);
int endGame();
void move(char direction);
void ghosts();
int whereDoesGhostGo(int currentX, int currentY, int* destinyX, int* destinyY);