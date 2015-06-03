/*
 * gdtout.h --
 *
 * Definitions of generating gdt file for a given tile plane.
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
 
#ifndef _GDTOUT_H
#define _GDTOUT_H

#include "../tiles/tile.h"

/*
 * --------------------------------------------------------------------
 *
 * Given a tile plane, this function will produce a gdt file with the 
 * name specified by filename. Solid tile and space tile are placed in
 * layer 1 and layer 2 respectively.
 * Once target_tile is specified (not NULL), it will be placed in
 * layer 3. 
 *
 * Results:
 *	None
 *
 * Side effects:
 *	None
 *
 * Note:
 *  You can find the description and conversion tool which will 
 *  transform a gdt format to a gds format from the following link.
 *  http://sourceforge.net/projects/gds2/
 *  A gds file can be opened through KLayout or LayoutEditor.
 *
 * --------------------------------------------------------------------
 */
void GenerateGDT(Plane *plane, const char* filename, const Tile *target_tile);


#endif
