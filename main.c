#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/update.h"
#include "utils/gdtout.h"


static void readFile(Plane *plane, const char* filename);


int main(const int argc, const char* argv[])
{
	Plane *plane = CreateTilePlane();	
	readFile(plane, argv[1]);
	GenerateGDT(plane, argv[2], NULL);
	RemoveTilePlane(plane);
	
	return 0;
}


static void readFile(Plane *plane, const char* filename)
{
#define BUF_SIZE 128
	FILE *ifile = fopen(filename, "r");
	
	char buf[BUF_SIZE];
	const char* del = " \t\r\n";
	while ( fgets(buf, BUF_SIZE, ifile) != NULL ) {
		char *token = strtok(buf, del);
		// skip when this line is a comment
		if (token[0] == '#') { continue; }
		// read coordinates (clockwise order)
		int coor[8] = {0}, i = 0;
		for (i = 0; token != NULL; (token = strtok(NULL, del)), (++i)) {
			coor[i] = atoi(token);
		}

		// skip when the tile is not a rectangle
		if ( (coor[0] != coor[2]) || (coor[3] != coor[5]) || (coor[4] != coor[6]) || (coor[7] != coor[1]) ) {
			fprintf(stderr, "Skip invalid rectangle: (%d, %d) - (%d, %d) - (%d, %d) - (%d, %d)\n", coor[0], coor[1], coor[2], coor[3], coor[4], coor[5], coor[6], coor[7]);
			continue;
		}
		
		// insert tile into tile plane
		Rect rect = { {coor[0], coor[1]}, {coor[4], coor[5]} };
		if (InsertTile(&rect, plane) == NULL) {
			fprintf (stderr, "Invalid insertion due to the overlapping with existing rectangles: (%d, %d) - (%d, %d).\n", coor[0], coor[1], coor[4], coor[5]);
		}
	}
	
	fclose(ifile);
#undef BUF_SIZE
}
