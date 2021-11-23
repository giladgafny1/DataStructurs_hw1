//
// Created by Gilad on 22/11/2021.
//

#ifndef DATASTRUCTURS_HW1_SQUIDSYSTEM_H
#define DATASTRUCTURS_HW1_SQUIDSYSTEM_H

#include <iostream>
#include <memory>
#include "player.h"
#include "avl.h"
#include "group.h"
#include "library1.h"

typedef Avltree<Player, int> PlayersTree;
typedef Avltree<Player, LevelIdKey> PlayersTreeByLevel;
//typedef Avltree<Group, int> GroupsTree;


class SquidSystem {
private:
    PlayersTree p_tree;
    PlayersTreeByLevel pl_tree;
    //GroupsTree g_tree;
public:
    SquidSystem();
    ~SquidSystem()=default;
    SquidSystem(const SquidSystem& other);
    SquidSystem& operator=(const SquidSystem& other);

    StatusType AddPlayer(int player_id, int group_id, int level);

};

#endif //DATASTRUCTURS_HW1_SQUIDSYSTEM_H
