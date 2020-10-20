/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "parse_tree.h"

parse_tree_node *init_pt_node()
{
  parse_tree_node *node = (parse_tree_node *)calloc(1, sizeof(parse_tree_node));
  node->num_children = 0;
  node->is_terminal = false;
  node->nt = 0;
  node->line_num = 0;
  return node;
}

void add_pt_child(parse_tree_node *node, parse_tree_node *child)
{
  assert(node->num_children < MAX_RULE_LEN, "no space to add child!");

  int idx = node->num_children;
  (node->children)[idx] = child;
  node->num_children += 1;
}

void remove_node(parse_tree_node *node)
{
  if (node->num_children == 0)
  {
    free(node);
    return;
  }
  for (int i = 0; i < node->num_children; i++)
    remove_node((node->children)[i]);

  node->num_children = 0;
  free(node);
  return;
}

void remove_pt_children(parse_tree_node *node)
{
  if (node->num_children == 0)
    return;
  for (int i = 0; i < node->num_children; i++)
    remove_node((node->children)[i]);

  node->num_children = 0;
  return;
}