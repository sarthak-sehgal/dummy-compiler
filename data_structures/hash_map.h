/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>
#include <string.h>
#include "../utils/general.h"

#ifndef HASH_MAP_H
#define HASH_MAP_H

typedef struct __HASH_MAP_NODE__ map_node;

struct __HASH_MAP_NODE__
{
  char *string;
  void *data;
  map_node *next;
};

struct __HASH_MAP_BUCKET__
{
  map_node *head;
  int capacity;
};

typedef struct __HASH_MAP_BUCKET__ map_bucket;

struct __HASH_MAP__
{
  map_bucket **buckets;
  int map_size;
};

typedef struct __HASH_MAP__ hash_map;

hash_map *init_map(int map_size);

void insert_into_map(hash_map *map, char *string, void *data);

void *find_in_map(hash_map *map, char *string);

void *delete_from_map(hash_map *map, char *string);

void delete_map(hash_map *map);

map_node *get_all_map_nodes(hash_map *map);

#endif