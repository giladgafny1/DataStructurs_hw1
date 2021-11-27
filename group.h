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
    int highest_level_player=-1;

public:
    Group(int id_group): id_group(id_group){
        num_of_players=0;
    };
  //  Group& operator=(Group& group)=default;
    ~Group()= default;
    int getHighLevelPlayer();
    int getGroupId();
    Avltree<Player, LevelIdKey> getPlayersLevelsTree();
    Avltree<Player, int> getPlayersTree();
    bool isPlayerInGroup(int player_id, LevelIdKey level_id);
    void addPlayer(std::shared_ptr<Node<Player, int>> player_by_id, std::shared_ptr<Node<Player, LevelIdKey>> player_by_level);
    void removePlayer(std::shared_ptr<Node<Player, int>> player_by_id, std::shared_ptr<Node<Player, LevelIdKey>> player_by_level);
    int getNumOfPlayers();


};



#endif //DATASTRUCTURS_HW1_GROUP_H
