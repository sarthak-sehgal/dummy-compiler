/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "./entities.h"
#include "./general.h"

#ifndef PARSE_TREE_H
#define PARSE_TREE_H

parse_tree_node *init_pt_node();

void add_pt_child(parse_tree_node *node, parse_tree_node *child);

void remove_pt_children(parse_tree_node *node);

#endif