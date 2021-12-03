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
typedef Avltree<std::shared_ptr<Player>, int> HighestPlayerByGroup;
typedef Node<std::shared_ptr<Player> , int> NodePlayerId;
typedef Node<std::shared_ptr<Player> , LevelIdKey> NodePlayerLevel;

class SquidSystem {
private:
    PlayersTree p_tree;
    PlayersTreeByLevel pl_tree;
    GroupsTree g_tree;
    HighestPlayerByGroup  pl_tree_by_group;
    int highest_level;
    std::shared_ptr<Player> highest_level_p;
    int num_of_players_in_sys;
    int num_of_groups;
    int num_of_no_empty_group;
public:
    SquidSystem(): highest_level(-1), highest_level_p(nullptr), num_of_players_in_sys(0), num_of_groups(0), num_of_no_empty_group(0)
    {};
    ~SquidSystem();

    StatusType destroy();

    SquidSystem* Init();

    StatusType AddGroup(int GroupID);

    StatusType AddPlayer(int player_id, int group_id, int level);

    StatusType RemovePlayer(int PlayerID);

    StatusType ReplaceGroup(int GroupID, int ReplacementID);

    StatusType IncreaseLevel( int PlayerID, int LevelIncrease);

    StatusType GetHighestLevel(int GroupID, int *PlayerID);

    StatusType GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);

    StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);

    void Quit();

};

#endif //DATASTRUCTURS_HW1_SQUIDSYSTEM_H
