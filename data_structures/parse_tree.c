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
  node->is_terminal = true;
  node->t = 0;
  return node;
}

parse_tree_node *copy_node(parse_tree_node *node)
{
  parse_tree_node *copy = init_pt_node();
  copy->num_children = node->children;
  for (int i = 0; i < node->num_children; i++)
  {
    (copy->children)[i] = (node->children)[i];
  }
  copy->is_terminal = node->is_terminal;
  copy->g_rule_idx = node->g_rule_idx;
  copy->nt = node->nt;
  copy->t = node->t;

  return copy;
}

void *add_child(parse_tree_node *node, parse_tree_node *child)
{
  assert(node->num_children < MAX_RULE_LEN, "no space to add child!");

  int idx = node->num_children;
  (node->children)[idx] = copy_node(child);
  node->num_children += 1;
}

void *remove_last_child(parse_tree_node *node)
{
  if (node->num_children <= 0)
    return;

  int idx = node->num_children - 1;
  free((node->children)[idx]);
  node->num_children -= 1;
}