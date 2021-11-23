//
// Created by Gilad on 22/11/2021.
//

#ifndef DATASTRUCTURS_HW1_GROUP_H
#define DATASTRUCTURS_HW1_GROUP_H
#include "avl.h"
#include "player.h"

class group {
private:
    int id_group;
    Avltree<Player,LevelIdKey> players_tree_levels;
    Avltree<Player,int> players_tree_id;
    int highest_level_player=-1;

public:
    group(int id_group): id_group(id_group);
    ~group()= default;
    int getHighLevelPlayer();
    int getGroupId();



};


#endif //DATASTRUCTURS_HW1_GROUP_H
