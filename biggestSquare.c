#include <stdio.h>
#include <stdlib.h>

int len(char *str) {
	int count = 0;
	while(str[count] && str[count] != '\n') count++;
	return (count);
}

int min(int a, int b) {
	return (a < b ? a : b);
}

int	minPos(int top, int left, int top_left) {
	return (min(min(top, left), top_left));
}

int isValidMap(char **map, int heigth, int obstacle, int empty, int full) {
	int mapLength = len(map[0]);
	for (int i = 0; i < heigth; i++) {
		if (len(map[i]) != mapLength)
			return (0);
		for (int j = 0; j < mapLength; j++)
			if (map[i][j] != obstacle && map[i][j] != empty && map[i][j] != full)
				return (0);
	}
	return (1);
}

char **findBSQ(char **map, char obstacle, char empty, int height) {
	char **output;

	return (output);
}

void printBSQ(char **BSQmap) {

}

int main(int argc, char *argv[]) {
	FILE *mapFile = fopen("map.bsq", "r");
	
	if (!mapFile) {
		perror("map error\n");
		return (1);
	}

	char line[1024];
	int	 firstLine = 1;
	char obstacle;
	char empty;
	char full;
	int height;
	int isValidData = fscanf(mapFile, "%d %c %c %c", &height, &empty, &obstacle, &full);
	if (isValidData != 4 || !((empty - obstacle) * (empty - full) * (obstacle - full)))
		return (perror("map error\n"), 1);
	printf("height: %d | empty: %c | obstacle: %c | full: %c\n", height, empty, obstacle, full);
	char **map = malloc(height * sizeof(char *));
	int i = 0;
	while (fgets(line, sizeof(line), mapFile)) {
		if (firstLine && !(firstLine = 0)) ;
		else {
			map[i] = malloc(len(line));
			for (int j = 0; line[j] != '\n' && line[j]; j++) 
				map[i][j] = line[j];
			i++;
		}
	}
	if (!isValidMap(map, height, obstacle, empty, full))	
		return (perror("map error\n"), 1);
	
	return (0);
}
