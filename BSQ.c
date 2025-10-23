#include <stdio.h>
#include <stdlib.h>

int len (char *str) {
    int count = 0;
    while (str && str[count]) count++;
    return (count);
}

int minTrio(int a, int b, int c) {
    int ab_min = a < b ? a : b;
    return (ab_min < c ? ab_min : c);
}

int mapMax(int **bsqDP, int w, int h) {
    int max = 0;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (bsqDP[y][x] > max) max = bsqDP[y][x];
    return (max);
}

int isValid(char **map, int h, char e, char o) {
    int mapLen = !map ? 0 : len(map[0]);
    for (int y = 0; y < h; y++) {
        if (len(map[y]) != mapLen) return (0);
        for (int x = 0; x < mapLen; x++)
            if (map[y][x] != e && map[y][x] != o) return (0);
    }
    return (1);
}

int **bsqMakeDP(char **map, int w, int h, char o) {
    int **out = malloc(sizeof(int *) * h);
    for (int i = 0 ; i < h ; i++) out[i] = malloc(sizeof(int) * w);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (map[y][x] == o) out[y][x] = 0;
            else if (y == 0 || x == 0) out[y][x] = 1;
            else out[y][x] = 1 + minTrio(out[y-1][x], out[y][x-1], out[y-1][x-1]);
        }
    }
    return (out);
}

char    **parser(char *filename,int *w, int *h, char *e, char *o, char *f) {
    FILE *file = !filename ? stdin : fopen(filename, "r");
    size_t len = 0, dataCount;
    ssize_t readbites;
    char *line = NULL;
    if ((dataCount = fscanf(file, "%d %c %c %c\n", h, e, o, f)) != 4) return (NULL);
    char **map = malloc(sizeof(char *) * (*h));
    for (int y = 0; (readbites = getline(&line, &len, file)) != -1; y++) {
        if (line[readbites - 1] == '\n')
            line[--readbites] = '\0';
        map[y] = malloc(readbites + 1);
        *w = y == 0 ? readbites : *w;
        if (*w != readbites) return (NULL);
        for (int x = 0; x < readbites; x++) map[y][x] = line[x];
        map[y][*w] = '\0'; 
    }
    fclose(file);
    return (map);
}

int    printBSQ(char *fileName) {
    int h,w;
    char e,o,f;
    char **map = parser(fileName, &w, &h, &e,&o,&f);
    if (!map) {
        fprintf(stderr, "map error !\n");
        return (1);
    }
    int **dp = bsqMakeDP(map, w, h, o);
    int maxP = mapMax(dp, w, h), maxY, maxX;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (dp[y][x] == maxP) {
                maxX = x, maxY = y, y = -1;
                break;
            }
        }
        if (y == -1) break;
    }
    for (int y = maxY; y > maxY - maxP; y--)
        for (int x = maxX; x > maxX - maxP; x--) map[y][x] = f;
    for (int i = 0; i < h; i++) fprintf(stdout ,"%s\n",map[i]);
    fprintf(stdout, "\n");
    return (0);
}

int main(int argc, char *argv[]) {
    int ret = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++)
           ret = printBSQ(argv[i]);
        if (ret)
            return (ret);
    }  else return (printBSQ(NULL));
}