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

int max(int **BSQmap, int height, int width) {
	int	output = 0;
	for(int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (BSQmap[i][j] > output)
				output = BSQmap[i][j];
	return (output);
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

int **findBSQ(char **map, char obstacle, char empty, int height) {
	int **output = malloc(height * sizeof(int *));
	int width = len(map[0]);

	for(int i = 0; i < height; i++) {
		output[i] = malloc(width * sizeof(int));
		int j;
		for (j = 0; j < width; j++) {
			if (map[i][j] == obstacle)
				output[i][j] = 0;
			else if (i == 0 || j == 0)
				output[i][j] = 1;
			else
				output[i][j] = 1 + minPos(output[i-1][j], output[i][j-1], output[i-1][j-1]);
		}
	}
	return (output);
}

void printBSQ(char **map, int height, int width, char obstacle, char empty, char full) {
	int **BSQmap = findBSQ(map, obstacle, empty, height);
	int	maxSqSize = max(BSQmap, height, width);
	int maxI, maxJ;

	for(int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (BSQmap[i][j] == maxSqSize) {
				maxI = i;
				maxJ = j;
				i = -1;
				break;
			}
		}
		if (i == -1) break;
	}
	for (int y = maxI; y > maxI - maxSqSize; y--)
		for (int x = maxJ; x > maxJ - maxSqSize; x--)
			map[y][x] = full;
	for (int i = 0; i < height; i++)
		printf("%s\n", map[i]);
}

int main(int argc, char *argv[]) {
	if (argc < 2)
		return (perror("map error\n"),1);
	FILE *mapFile = fopen(argv[1], "r");
	if (!mapFile)
		return (perror("map error\n"),1);
	char line[1024];
	int	 firstLine = 1;
	char obstacle;
	char empty;
	char full;
	int height;
	int isValidData = fscanf(mapFile, "%d %c %c %c", &height, &empty, &obstacle, &full);
	if (isValidData != 4 || !((empty - obstacle) * (empty - full) * (obstacle - full)))
		return (perror("map error\n"), 1);
	char **map = malloc(height * sizeof(char *));
	int i = 0;
	while (fgets(line, sizeof(line), mapFile)) {
		if (firstLine && !(firstLine = 0)) ;
		else {
			map[i] = malloc(len(line) + 1);
			int j;
			for (j = 0; line[j] != '\n' && line[j]; j++) 
				map[i][j] = line[j];
			map[i][j] = '\0';
			i++;
		}
	}
	if (!isValidMap(map, height, obstacle, empty, full))	
		return (perror("map error\n"), 1);
	printBSQ(map, height, len(map[0]), obstacle, empty, full);
	return (0);
}
