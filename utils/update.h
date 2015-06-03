/*
 * update.h --
 *
 * Definitions of the update functions for a given tile and a tile plane.
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

#ifndef _UPDATE_H
#define	_UPDATE_H

#include "../tiles/tile.h"
#define SOLID_TILE 1


/*
 * --------------------------------------------------------------------
 *
 * Create a tile at specified location.
 *
 * Results:
 *	Return the created tile.
 *
 * Side effects:
 *	None
 *
 * --------------------------------------------------------------------
 */
Tile* CreateTile(int x, int y);


/*
 * --------------------------------------------------------------------
 *
 * Given a tile to be inserted and the tile plane, insert the tile 
 * into the tile plane.
 *
 * Results:
 *	Return the inserted tile.
 *  Return NULL if the insertion fail.
 *
 * Side effects:
 *	Tiles around the inserted tile are split and relinked.
 *	The hint tile pointer in the supplied plane is adjusted to 
 *  point the inserted tile.
 *
 * --------------------------------------------------------------------
 */
Tile* InsertTile(Rect *rect, Plane *plane);


/*
 * --------------------------------------------------------------------
 *
 * Given a tile to be removed and the tile plane, remove the tile 
 * from the tile plane. 
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Tiles around the removed tile are joint and relinked.
 *	The hint tile pointer in the supplied plane is adjusted to 
 *  point the nearest tile.
 *
 * --------------------------------------------------------------------
 */
void RemoveTile(Tile *tile, Plane *plane);


/*
 * --------------------------------------------------------------------
 *
 * Create a tile plane.
 *
 * Results:
 *	An allocated tile plane.
 *
 * Side effects:
 *	Allocate memory.
 *
 * --------------------------------------------------------------------
 */
Plane* CreateTilePlane();


/*
 * --------------------------------------------------------------------
 *
 * Given a tile plane, remove all the tiles in the tile plane and
 * the tile plane itself.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Free memory
 *
 * --------------------------------------------------------------------
 */
void RemoveTilePlane(Plane *plane);


#endif /* _UPDATE_H */
