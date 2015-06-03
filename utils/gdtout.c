/*
 * gdtout.c --
 *
 * tile manipulation for updating tile plane structures
 *
 *     ************************************************************************ 
 *     * Copyright (C) 2015 lionking, National Chiao Tung University, Taiwan. * 
 *     * Permission to use, copy, modify, and distribute this                 * 
 *     * software and its documentation for any purpose and without           * 
 *     * fee is hereby granted, provided that the above copyright             * 
 *     * notice appear in all copies.                                         * 
 *     ************************************************************************
 *
 */

#ifndef	lint
static char rcsid[] __attribute__ ((unused)) = "$Header: /usr/cvsroot/corner_stitch/utils/gdtout.c, 2015/06/01 tim Exp $";
#endif	/* not lint */

#include <time.h>
#include <stdio.h>
#include <math.h>
#include "gdtout.h"
#include "update.h"
#define EPS 1e-1

static FILE* ofile = NULL;


static void GetTimingInfo(char *timeseq)
{
	// get current time, and output to a string
	time_t rawtime;
	struct tm * timeinfo = NULL;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	// tm_year is the years counted from 1900 A.D.
	sprintf(timeseq, "%d-%02d-%02d %02d:%02d:%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}


static int print(Tile *tile, ClientData cdata)
{
	const int SOLID_LAYER = 1;
	const int SPACE_LAYER = 2;
	const int TARGET_LAYER = 3;
	const int TEXT_LAYER = 131;
	
	int layer_no = SPACE_LAYER;
	Tile *target = (Tile*)cdata;
	if (TiGetBody(tile) == SOLID_TILE) { layer_no = SOLID_LAYER; }
	if (tile == target) { layer_no = TARGET_LAYER; }
	
	const double MINF = MINFINITY / 1000.0;
	const double INF = INFINITY / 1000.0;
	double left = LEFT(tile) / 1000.0;
	double right = RIGHT(tile) / 1000.0;
	double top = TOP(tile) / 1000.0;
	double bottom = BOTTOM(tile) / 1000.0;

	// Avoid generating a rectangle with infinity coordinate
	if ((fabs(left - MINF) < EPS) && (fabs(right - INF) < EPS)) { return 0; }
	if ((fabs(bottom - MINF) < EPS) && (fabs(top - INF) < EPS)) { return 0; }
	
	if (fabs(left - MINF) < EPS) { left = right - 0.1; }
	if (fabs(bottom - MINF) < EPS) { bottom = top - 0.1; }
	if (fabs(right - INF) < EPS) { right = left + 0.1; }
	if (fabs(top - INF) < EPS) { top = bottom + 0.1; }
	
	fprintf(ofile, "b{%d xy(%.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf)}\n", layer_no, left, bottom, right, bottom, right, top, left, top);

	// output text
	char text[128];
	sprintf(text, "(%d, %d)-(%d, %d)", LEFT(tile), BOTTOM(tile), RIGHT(tile), TOP(tile));
	fprintf(ofile, "t{%d mc m0.05 xy(%.3lf %.3lf) '%s'}\n", TEXT_LAYER, left, bottom, text);

	return 0;
}


void GenerateGDT(Plane *plane, const char* filename, const Tile *target_tile)
{
	ofile = fopen(filename, "w");
	
	// get current time, and output to a string
	char timeseq[32];
	GetTimingInfo(timeseq);
	
	// gdt header
	fputs("gds2{600\n", ofile);
	fprintf(ofile, "m=%s a=%s\n", timeseq, timeseq);
	fputs("lib 'Flat' 0.001 1e-09\n", ofile);
	
	// output layout info
	fprintf(ofile, "cell{c=%s m=%s '%s'\n", timeseq, timeseq, filename);
	
	// traverse all the tiles in the tile plane
	Rect rect = { {MINFINITY + 1, MINFINITY + 1}, {INFINITY - 1, INFINITY - 1} };
	TiSrArea(NULL, plane, &rect, print, (ClientData)target_tile);
	
	// gdt end
	fputs("}\n}\n", ofile);
}
