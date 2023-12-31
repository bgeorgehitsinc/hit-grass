#ifndef __OCT_H__
#define __OCT_H__

#include "dataoct.h"

struct octfunc {
    int (*compare)(struct quadruple *, struct octdata *);
    struct octdata **(*divide_data)(struct octdata *);
    int (*add_data)(struct quadruple *, struct octdata *);
    int (*intersect)(double, double, double, double, double, double,
                     struct octdata *);
    int (*division_check)(struct octdata *);
    int (*get_points)(struct quadruple *, struct octdata *, double, double,
                      double, double, double, double, int);
};

struct octtree {
    struct octdata *data;
    struct octtree **leafs;
    struct octtree *parent;
    struct octfunc *functions;
    int octant;
};

struct octfunc *OT_functions_new(
    int (*compare)(struct quadruple *, struct octdata *),
    struct octdata **(*divide_data)(struct octdata *),
    int (*add_data)(struct quadruple *, struct octdata *),
    int (*intersect)(double, double, double, double, double, double,
                     struct octdata *),
    int (*division_check)(struct octdata *),
    int (*get_points)(struct quadruple *, struct octdata *, double, double,
                      double, double, double, double, int));
struct octtree *OT_tree_new(struct octdata *, struct octtree **,
                            struct octtree *, struct octfunc *, int octant);
int OT_insert_oct(struct quadruple *, struct octtree *);
int OT_region_data(struct octtree *, double, double, double, double, double,
                   double, struct quadruple *, int);

#endif
