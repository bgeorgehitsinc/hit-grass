/*
 * Name
 *  cubic_f.c -- use cubic interpolation with fallback for given row, col
 *
 * Description
 *  cubic interpolation for the given row, column indices.
 *  If the interpolated value (but not the nearest) is null,
 *  it falls back to bilinear.  If that interp value is null,
 *  it falls back to nearest neighbor.
 */

#include <grass/gis.h>
#include <grass/raster.h>
#include "r.proj.h"

void p_cubic_f(struct cache *ibuffer,   /* input buffer                  */
               void *obufptr,           /* ptr in output buffer          */
               int cell_type,           /* raster map type of obufptr    */
               double col_idx,          /* column index          */
               double row_idx,          /* row index                     */
               struct Cell_head *cellhd /* cell header of input layer    */
)
{
    /* start nearest neighbor to do some basic tests */
    int row, col; /* row/col of nearest neighbor   */
    FCELL cell;

    /* cut indices to integer */
    row = (int)floor(row_idx);
    col = (int)floor(col_idx);

    /* check for out of bounds - if out of bounds set NULL value     */
    if (row < 0 || row >= cellhd->rows || col < 0 || col >= cellhd->cols) {
        Rast_set_null_value(obufptr, 1, cell_type);
        return;
    }

    cell = CVAL(ibuffer, row, col);
    /* if nearest is null, all the other interps will be null */
    if (Rast_is_f_null_value(&cell)) {
        Rast_set_null_value(obufptr, 1, cell_type);
        return;
    }

    p_cubic(ibuffer, obufptr, cell_type, col_idx, row_idx, cellhd);
    /* fallback to bilinear if cubic is null */
    if (Rast_is_f_null_value(obufptr)) {
        p_bilinear(ibuffer, obufptr, cell_type, col_idx, row_idx, cellhd);
        /* fallback to nearest if bilinear is null */
        if (Rast_is_f_null_value(obufptr))
            Rast_set_f_value(obufptr, cell, cell_type);
    }
}
