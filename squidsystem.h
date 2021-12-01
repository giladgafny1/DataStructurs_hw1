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

typedef Avltree<std::shared_ptr<Player>, int> PlayersTree;
typedef Avltree<std::shared_ptr<Player>, LevelIdKey> PlayersTreeByLevel;
typedef Avltree<std::shared_ptr<Group>, int> GroupsTree;
typedef Avltree<std::shared_ptr<Group>, int> NotEmptyGroupsTree;

class SquidSystem {
private:
    PlayersTree p_tree;
    PlayersTreeByLevel pl_tree;
    GroupsTree g_tree;
    NotEmptyGroupsTree  g_ne_tree;
    int highest_level;
    std::shared_ptr<Player> highest_level_p;
public:
    SquidSystem(): highest_level(-1), highest_level_p(nullptr) {};
    ~SquidSystem()=default;

    SquidSystem* Init();

    StatusType AddGroup(int GroupID);

    StatusType AddPlayer(int player_id, int group_id, int level);

    StatusType RemovePlayer(int PlayerID);

    StatusType ReplaceGroup(int GroupID, int ReplacementID);

    StatusType IncreaseLevel( int PlayerID, int LevelIncrease);

    StatusType GetHighestLevel(int GroupID, int *PlayerID);

    StatusType GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);

    StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);

};

#endif //DATASTRUCTURS_HW1_SQUIDSYSTEM_H
