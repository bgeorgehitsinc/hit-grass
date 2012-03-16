/*!
   \file lib/vector/Vlib/header.c

   \brief Vector library - header manipulation

   Higher level functions for reading/writing/manipulating vectors.

   (C) 2001-2010 by the GRASS Development Team

   This program is free software under the GNU General Public License
   (>=v2). Read the file COPYING that comes with GRASS for details.

   \author Original author CERL, probably Dave Gerdes or Mike Higgins.
   \author Update to GRASS 5.7 Radim Blazek and David D. Gray.
   \author Update to GRASS 7 (OGR support) by Martin Landa <landa.martin gmail.com>
 */

#include <stdlib.h>
#include <string.h>
#include <grass/vector.h>
#include <grass/glocale.h>

static int lookup(const char *file, const char *key, char *value, size_t len);

/*!
   \brief Print vector map header to stdout

   \param Map pointer to Map_info structure

   \return 0 on success
*/
int Vect_print_header(const struct Map_info *Map)
{
    fprintf(stdout, "\nSelected information from dig header\n");
    fprintf(stdout, " Organization:  %s\n", Vect_get_organization(Map));
    fprintf(stdout, " Map Name:      %s\n", Vect_get_map_name(Map));
    fprintf(stdout, " Source Date:   %s\n", Vect_get_map_date(Map));
    fprintf(stdout, " Orig. Scale:   %d\n", Vect_get_scale(Map));

    return 0;
}

/*!
   \brief Read vector map header from map head file

   \param Map pointrt to Map_info structure

   \return 0
*/
int Vect_read_header(struct Map_info *Map)
{
    Vect__read_head(Map);
    return 0;
}

/*!
   \brief Write vector map header to map head file

   \param Map pointer to Map_info structure

   \return 0
*/
int Vect_write_header(const struct Map_info *Map)
{
    /* do some sanity checking here */
    Vect__write_head(Map);
    return 0;
}

/*! 
   \brief Writes head information to text file (GV_HEAD_ELEMENT)

   \param Map pointer to Map_info structure

   \return 0 on success
   \return -1 on error
 */
int Vect__write_head(const struct Map_info *Map)
{
    char buf[GPATH_MAX];
    FILE *head_fp;

    sprintf(buf, "%s/%s", GV_DIRECTORY, Map->name);

    head_fp = G_fopen_new(buf, GV_HEAD_ELEMENT);
    if (head_fp == NULL) {
	G_warning(_("Unable to open header file of vector <%s>"),
		  Vect_get_full_name(Map));
	return -1;
    }

    fprintf(head_fp, "ORGANIZATION: %s\n", Vect_get_organization(Map));
    fprintf(head_fp, "DIGIT DATE:   %s\n", Vect_get_date(Map));
    fprintf(head_fp, "DIGIT NAME:   %s\n", Vect_get_person(Map));
    fprintf(head_fp, "MAP NAME:     %s\n", Vect_get_map_name(Map));
    fprintf(head_fp, "MAP DATE:     %s\n", Vect_get_map_date(Map));
    fprintf(head_fp, "MAP SCALE:    %d\n", Vect_get_scale(Map));
    fprintf(head_fp, "OTHER INFO:   %s\n", Vect_get_comment(Map));
    if (Vect_get_proj(Map) > 0)
	fprintf(head_fp, "PROJ:         %d\n", Vect_get_proj(Map));
    fprintf(head_fp, "ZONE:         %d\n", Vect_get_zone(Map));
    fprintf(head_fp, "MAP THRESH:   %f\n", Vect_get_thresh(Map));

    fclose(head_fp);
    return (0);
}

/*!
   \brief Reads head information from text file (GV_HEAD_ELEMENT) - for internal use only

   \param Map pointer to Map_info structure

   \return 0 on success
   \return -1 on error
 */
int Vect__read_head(struct Map_info *Map)
{
    FILE *head_fp;
    char buff[GPATH_MAX];
    char *ptr;

    /* Reset / init */
    Vect_set_organization(Map, "");
    Vect_set_date(Map, "");
    Vect_set_person(Map, "");
    Vect_set_map_name(Map, "");
    Vect_set_map_date(Map, "");
    Vect_set_scale(Map, 1);
    Vect_set_comment(Map, "");
    Vect_set_zone(Map, -1);
    Vect_set_thresh(Map, 0.);

    G_debug(1, "Vect__read_head(): vector = %s@%s", Map->name, Map->mapset);
    sprintf(buff, "%s/%s", GV_DIRECTORY, Map->name);
    head_fp = G_fopen_old(buff, GV_HEAD_ELEMENT, Map->mapset);
    if (head_fp == NULL) {
	G_warning(_("Unable to open header file of vector <%s>"),
		  Vect_get_full_name(Map));
	return -1;
    }

    while (G_getl2(buff, 2000, head_fp)) {

	if (!(ptr = strchr(buff, ':'))) {
	    G_warning(_("Corrupted row in head: %s"), buff);
	    continue;
	}

	ptr++;			/* Search for the start of text */
	while (*ptr == ' ')
	    ptr++;

	if (strncmp(buff, "ORGANIZATION:", sizeof(char) * 12) == 0)
	    Vect_set_organization(Map, ptr);
	else if (strncmp(buff, "DIGIT DATE:", sizeof(char) * 11) == 0)
	    Vect_set_date(Map, ptr);
	else if (strncmp(buff, "DIGIT NAME:", sizeof(char) * 11) == 0)
	    Vect_set_person(Map, ptr);
	else if (strncmp(buff, "MAP NAME:", sizeof(char) * 9) == 0)
	    Vect_set_map_name(Map, ptr);
	else if (strncmp(buff, "MAP DATE:", sizeof(char) * 9) == 0)
	    Vect_set_map_date(Map, ptr);
	else if (strncmp(buff, "MAP SCALE:", sizeof(char) * 10) == 0)
	    Vect_set_scale(Map, atoi(ptr));
	else if (strncmp(buff, "OTHER INFO:", sizeof(char) * 11) == 0)
	    Vect_set_comment(Map, ptr);
	else if (strncmp(buff, "PROJ:", sizeof(char) * 5) == 0)
	    Vect_set_proj(Map, atoi(ptr));
	else if (strncmp(buff, "ZONE:", sizeof(char) * 5) == 0 ||
		 strncmp(buff, "UTM ZONE:", sizeof(char) * 9) == 0)
	    Vect_set_zone(Map, atoi(ptr));
	else if (strncmp(buff, "WEST EDGE:", sizeof(char) * 10) == 0) {
	}
	else if (strncmp(buff, "EAST EDGE:", sizeof(char) * 10) == 0) {
	}
	else if (strncmp(buff, "SOUTH EDGE:", sizeof(char) * 11) == 0) {
	}
	else if (strncmp(buff, "NORTH EDGE:", sizeof(char) * 11) == 0) {
	}
	else if (strncmp(buff, "MAP THRESH:", sizeof(char) * 11) == 0)
	    Vect_set_thresh(Map, atof(ptr));
	else
	    G_warning(_("Unknown keyword '%s' in vector head"), buff);
    }

    fclose(head_fp);

    return 0;
}

/*!
   \brief Get name of vector map

   \param Map pointer to Map_info structure

   \return string containing name
*/
const char *Vect_get_name(const struct Map_info *Map)
{
    return Map->name;
}

/*!
   \brief Get name of mapset where vector map lives

   \param Map pointer to Map_info structure

   \return string containing mapset name
*/
const char *Vect_get_mapset(const struct Map_info *Map)
{
    return Map->mapset;
}

/*!
  \brief Get fully qualified name of vector map
  
  - for GV_FORMAT_NATIVE and GV_FORMAT_OGR returns "map@mapset"
  - for GV_FORMAT_OGR_DIRECT returns "layer@datasourse"

  Allocated string should be freed by G_free().
  
  \param Map pointer to Map_info structure
  
  \return allocated string "name@mapset"
 */
const char *Vect_get_full_name(const struct Map_info *Map)
{
    char *ptr;

    if (Map->format == GV_FORMAT_OGR_DIRECT &&
	Map->fInfo.ogr.dsn &&
	Map->fInfo.ogr.layer_name) {
	ptr = (char *) G_malloc(strlen(Map->fInfo.ogr.layer_name) +
				strlen(Map->fInfo.ogr.dsn) + 2);	
	sprintf(ptr, "%s@%s", Map->fInfo.ogr.layer_name,
		Map->fInfo.ogr.dsn);

	return ptr;
    }

    ptr = (char *) G_malloc(strlen(Map->name) + strlen(Map->mapset) + 2);
    if (strlen(Map->mapset) > 0) {
	sprintf(ptr, "%s@%s", Map->name, Map->mapset);
    }
    else {
	sprintf(ptr, "%s", Map->name);
    }

    return ptr;
}

/*!
   \brief Get datasource name (relevant only for non-native formats)

   Returns:
    - datasource name for OGR format (GV_FORMAT_OGR and GV_FORMAT_OGR_DIRECT)
    - database name for PostGIS format (GV_FORMAT_POSTGIS)
   
   \param Map pointer to Map_info structure

   \return string containing OGR/PostGIS datasource name
   \return NULL on error (map format is native)
 */
const char *Vect_get_finfo_dsn_name(const struct Map_info *Map)
{
    if (Map->format == GV_FORMAT_OGR ||
	Map->format == GV_FORMAT_OGR_DIRECT) {
#ifndef HAVE_OGR
	G_warning(_("GRASS is not compiled with OGR support"));
#endif
        return Map->fInfo.ogr.dsn;
    }
    else if (Map->format == GV_FORMAT_POSTGIS) {
#ifndef HAVE_POSTGRES
	G_warning(_("GRASS is not compiled with PostgreSQL support"));
#endif
        return Map->fInfo.pg.db_name;
    }
    
    G_warning(_("Native vector format detected for <%s>"),
	      Vect_get_full_name(Map));
    
    return NULL;
}

/*!
   \brief Get layer name (relevant only for non-native formats)

   Returns:
    - layer name for OGR format (GV_FORMAT_OGR and GV_FORMAT_OGR_DIRECT)
    - table name for PostGIS format (GV_FORMAT_POSTGIS)

   \param Map pointer to Map_info structure

   \return string containing layer name
   \return NULL on error (map format is native)
 */
const char *Vect_get_finfo_layer_name(const struct Map_info *Map)
{
    if (Map->format == GV_FORMAT_OGR ||
	Map->format == GV_FORMAT_OGR_DIRECT) {
#ifndef HAVE_OGR
	G_warning(_("GRASS is not compiled with OGR support"));
#endif
	return Map->fInfo.ogr.layer_name;
    }
    else if (Map->format == GV_FORMAT_POSTGIS) {
#ifndef HAVE_POSTGRES
	G_warning(_("GRASS is not compiled with PostgreSQL support"));
#endif
        return Map->fInfo.pg.table_name;
    }

    G_warning(_("Native vector format detected for <%s>"),
	      Vect_get_full_name(Map));
    
    return NULL;
}

/*!
  \brief Get format info (relevant only for non-native formats)

  Allocated space should be freed by G_free().

   Returns:
    - layer name for OGR format (GV_FORMAT_OGR and GV_FORMAT_OGR_DIRECT)
    
  \param Map pointer to Map_info structure
  
  \return string containing name of OGR format (allocated by G_store())
  \return NULL on error (or on missing OGR support)
*/
const char *Vect_get_finfo_format_info(const struct Map_info *Map)
{
    char format[GPATH_MAX];

    if (Map->format == GV_FORMAT_OGR ||
	Map->format == GV_FORMAT_OGR_DIRECT) {
#ifndef HAVE_OGR
	G_warning(_("GRASS is not compiled with OGR support"));
#else
	if (!Map->fInfo.ogr.ds)
	    return NULL;

	sprintf(format, "%s/%s", "OGR",
		OGR_Dr_GetName(OGR_DS_GetDriver(Map->fInfo.ogr.ds)));
	return G_store(format);
#endif
    }
    else if (Map->format == GV_FORMAT_POSTGIS) {
#ifndef HAVE_OGR
	G_warning(_("GRASS is not compiled with PostgreSQL support"));
#else
	return G_store("PostGIS");
#endif
    }
    
    return NULL;
}

/*!
  \brief Get geometry type (relevant only for non-native formats)

  Note: All inner spaces are removed, function returns feature type in
  lowercase.

  \param Map pointer to Map_info structure

  \return allocated string containing geometry type info
  (point, linestring, polygon, ...)
  \return NULL on error (map format is native)
*/
const char *Vect_get_finfo_geometry_type(const struct Map_info *Map)
{
    char *ftype, *ftype_tmp;
    
    ftype_tmp = ftype = NULL;
    if (Map->format == GV_FORMAT_OGR ||
	Map->format == GV_FORMAT_OGR_DIRECT) {
#ifndef HAVE_OGR
    G_warning(_("GRASS is not compiled with OGR support"));
#else
    OGRwkbGeometryType Ogr_geom_type;
    OGRFeatureDefnH    Ogr_feature_defn;
    
    if (!Map->fInfo.ogr.layer)
	return NULL;

    Ogr_feature_defn = OGR_L_GetLayerDefn(Map->fInfo.ogr.layer);
    Ogr_geom_type = wkbFlatten(OGR_FD_GetGeomType(Ogr_feature_defn));
    
    ftype_tmp = G_store(OGRGeometryTypeToName(Ogr_geom_type));
#endif
    }
    else if (Map->format == GV_FORMAT_POSTGIS) {
#ifndef HAVE_POSTGRES
	G_warning(_("GRASS is not compiled with PostgreSQL support"));
#else
	char stmt[DB_SQL_MAX];
	
	const struct Format_info_pg *pg_info;
	
	PGresult *res;
		
	pg_info = &(Map->fInfo.pg);
	sprintf(stmt, "SELECT type FROM geometry_columns "
		"WHERE f_table_name = '%s'", pg_info->table_name);
	G_debug(2, "SQL: %s", stmt);
	
	res = PQexec(pg_info->conn, stmt);
	if (!res || PQresultStatus(res) != PGRES_TUPLES_OK ||
	    PQntuples(res) != 1)
	    G_warning("%s\n%s", _("Unable to get feature type."),
		      PQresultErrorMessage(res));
	
	ftype_tmp = G_store(PQgetvalue(res, 0, 0));
	PQclear(res);
#endif
    }
    
    if (!ftype_tmp)
	return NULL;

    ftype = G_str_replace(ftype_tmp, " ", "");
    G_free(ftype_tmp);
    G_str_to_lower(ftype);

    return ftype;
}

/*!
   \brief Check if vector map is 3D

   Check vector map header.

   \param Map pointer to Map_info structure

   \return TRUE  vector map is 3D
   \return FALSE vector map is not 3D
 */
int Vect_is_3d(const struct Map_info *Map)
{
    return Map->head.with_z;
}

/*!
   \brief Set organization string in map header

   \param Map pointer to Map_info structure
   \param str organization name

   \return 0
*/
int Vect_set_organization(struct Map_info *Map, const char *str)
{
    G_free(Map->head.organization);
    Map->head.organization = G_store(str);

    return 0;
}

/*!
   \brief Get organization string from map header

   \param Map pointer to Map_info structure

   \return string containing organization name
 */
const char *Vect_get_organization(const struct Map_info *Map)
{
    return Map->head.organization;
}

/*!
   \brief Set date of digitization in map header

   \todo This should be coupled to DateTime functions to support
   time series

   \param Map pointer to Map_info structure
   \param str date given as string

   \return 0
*/
int Vect_set_date(struct Map_info *Map, const char *str)
{
    G_free(Map->head.date);
    Map->head.date = G_store(str);

    return 0;
}

/*!
   \brief Get date of digitization from map header

   \param Map pointer to Map_info structure

   \return date of digitization string
 */
const char *Vect_get_date(const struct Map_info *Map)
{
    return (Map->head.date);
}

/*!
   \brief Set name of user who digitized the map in map header

   \param Map pointer to Map_info structure
   \param str user name

   \return 0
*/
int Vect_set_person(struct Map_info *Map, const char *str)
{
    G_free(Map->head.user_name);
    Map->head.user_name = G_store(str);

    return 0;
}

/*!
   \brief Get user name string who digitized the map from map header

   \param Map pointer to Map_info structure

   \return string containing user name
 */
const char *Vect_get_person(const struct Map_info *Map)
{
    return (Map->head.user_name);
}

/*!
   \brief Set map name in map header

   \param Map pointer to Map_info structure
   \param str map name to be set

   \return 0 
 */
int Vect_set_map_name(struct Map_info *Map, const char *str)
{
    G_free(Map->head.map_name);
    Map->head.map_name = G_store(str);
    
    return 0;
}

/*!
   \brief Get map name from map header

   \param Map pointer to Map_info structure

   \return string containing map name
*/
const char *Vect_get_map_name(const struct Map_info *Map)
{
    return Map->head.map_name;
}

/*!
   \brief Set date when the source map was originally produced in map header

   \param Map pointer to Map_info structure
   \param str date given as a string

   \return 0
 */
int Vect_set_map_date(struct Map_info *Map, const char *str)
{
    G_free(Map->head.source_date);
    Map->head.source_date = G_store(str);
    
    return 0;
}

/*!
   \brief Get date when the source map was originally produced from map header

   \param Map pointer to Map_info structure

   \return string containg a date
 */
const char *Vect_get_map_date(const struct Map_info *Map)
{
    return Map->head.source_date;
}

/*!
   \brief Set map scale in map header

   \param Map pointer to Map_info structure
   \param scale map scale

   \return 0
 */
int Vect_set_scale(struct Map_info *Map, int scale)
{
    Map->head.orig_scale = scale;
    
    return 0;
}

/*!
   \brief Get map scale from map header

   \param Map pointer to Map_info structure

   \return map scale
 */
int Vect_get_scale(const struct Map_info *Map)
{
    return (int) Map->head.orig_scale;
}

/*!
   \brief Set comment or other info string in map header

   \param Map pointer to Map_info structure
   \param str comment or other info string

   \return 0
 */
int Vect_set_comment(struct Map_info *Map, const char *str)
{
    G_free(Map->head.comment);
    Map->head.comment = G_store(str);
    
    return 0;
}

/*!
   \brief Get comment or other info string from map header

   \param Map pointer to Map_info structure

   \return comment or other info string
 */
const char *Vect_get_comment(const struct Map_info *Map)
{
    return (Map->head.comment);
}

/*!
   \brief Set projection zone in map header

   \param Map pointer to Map_info structure
   \param zone projection zone

   \return 0
 */
int Vect_set_zone(struct Map_info *Map, int zone)
{
    Map->head.plani_zone = zone;
    
    return 0;
}

/*!
   \brief Get projection zone from map header

   \param Map pointer to Map_info structure

   \return projection zone
 */
int Vect_get_zone(const struct Map_info *Map)
{
    return Map->head.plani_zone;
}

/*!
   \brief Set projection in map header

   Supported projections:
    - PROJECTION_XY  0 - x,y (Raw imagery),
    - PROJECTION_UTM 1 - UTM   Universal Transverse Mercator,
    - PROJECTION_SP  2 - State Plane (in feet),
    - PROJECTION_LL  3 - Latitude-Longitude

   \param Map pointer to Map_info structure
   \param proj projection code
   
   \return 0
 */
int Vect_set_proj(struct Map_info *Map, int proj)
{
    Map->head.proj = proj;
    
    return 0;
}

/*!
   \brief Get projection from map header

   \param Map pointer to Map_info structure

   \return PROJECTION_XY  0 - x,y (Raw imagery),
   \return PROJECTION_UTM 1 - UTM   Universal Transverse Mercator,
   \return PROJECTION_SP  2 - State Plane (in feet),
   \return PROJECTION_LL  3 - Latitude-Longitude
*/
int Vect_get_proj(const struct Map_info *Map)
{
    return (Map->head.proj);
}

/*!
   \brief Query cartographic projection name of pointer to Map_info structure

   Returns a pointer to a string which is a printable name for
   projection code <em>proj</em> (as returned by Vect_get_proj()).

   \param Map pointer to Map_info structure

   \return allocated string containing projection name
   \return NULL if <em>proj</em> is not a valid projection
 */

const char *Vect_get_proj_name(const struct Map_info *Map)
{
    char name[256];
    int n;

    switch (n = Vect_get_proj(Map)) {
    case PROJECTION_XY:
    case PROJECTION_UTM:
    case PROJECTION_LL:
    case PROJECTION_SP:
	return G__projection_name(n);
    case PROJECTION_OTHER:
	/* this won't protect against differing "other" projections, so
	   better to just include P_OTHER in the above list so we return the
	   strictly more correct, but less nice, string: "Other projection" ? */
	return G_database_projection_name();
    default:
	G_debug(1, "Vect_get_proj_name(): "
		   "Vect_get_proj() returned an invalid result (%d)", n);
	break;
    }

    strcpy(name, _("Unknown projection"));
    return G_store(name);
}

/*!
   \brief Set threshold used for digitization in map header

   \param Map pointer to Map_info structure
   \param thresh threshold used for digitization

   \return 0
 */
int Vect_set_thresh(struct Map_info *Map, double thresh)
{
    G_debug(1, "Vect_set_thresh(): thresh = %f", thresh);
    Map->head.digit_thresh = thresh;
    return 0;
}

/*!
   \brief Get threshold used for digitization from map header

   \param Map pointer to Map_info structure

   \return threshold used for digitization
 */
double Vect_get_thresh(const struct Map_info *Map)
{
    G_debug(1, "Vect_get_thresh(): thresh = %f", Map->head.digit_thresh);
    return Map->head.digit_thresh;
}


/* from lib/gis/proj3.c */
static int lookup(const char *file, const char *key, char *value, size_t len)
{
    char path[GPATH_MAX];

    G_file_name(path, "", file, "PERMANENT");
    return G_lookup_key_value_from_file(path, key, value, (int) len) == 1;
}
