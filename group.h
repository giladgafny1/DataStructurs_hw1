//
// Created by Gilad on 22/11/2021.
//

#ifndef DATASTRUCTURS_HW1_GROUP_H
#define DATASTRUCTURS_HW1_GROUP_H
#include "avl.h"

class Player;
class LevelIdKey;

class Group {
private:
    int id_group;
    int num_of_players;
    //G removed the pointers from these (they caused bad creation of the tree (the root wasn't null))
    Avltree<Player,LevelIdKey> players_tree_levels;
    Avltree<Player,int> players_tree_id;
    int highest_level;
    //added a pointer to higest level player cause should be O(1)
    Player* highest_level_p;

public:
    Group(int id_group): id_group(id_group), highest_level(-1){
        num_of_players=0;
        highest_level_p = nullptr;
    };
  //  Group& operator=(Group& group)=default;
    ~Group()= default;
    Player* getHighestLevelPlayer();
    int getHighestLevel();
    int getGroupId();
    Avltree<Player, LevelIdKey> getPlayersLevelsTree();
    Avltree<Player, int> getPlayersTree();
    bool isPlayerInGroup(int player_id, LevelIdKey level_id);
    void addPlayer(std::shared_ptr<Node<Player, int>> player_by_id, std::shared_ptr<Node<Player, LevelIdKey>> player_by_level);
    void removePlayer(std::shared_ptr<Node<Player, int>> player_by_id, std::shared_ptr<Node<Player, LevelIdKey>> player_by_level);
    void removeFromLevelTree(std::shared_ptr<Node<Player, LevelIdKey>> player_by_level);
    void addToLevelTree(std::shared_ptr<Node<Player, LevelIdKey>> player_by_level);
    int getNumOfPlayers();
    void setPlayersTree(Avltree<Player,int> players_tree_id1);


};



#endif //DATASTRUCTURS_HW1_GROUP_H
