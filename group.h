//
// Created by Gilad on 22/11/2021.
//

#ifndef DATASTRUCTURS_HW1_GROUP_H
#define DATASTRUCTURS_HW1_GROUP_H
#include "avl.h"
#include "library1.h"

class Player;
class LevelIdKey;

class Group {
private:
    int id_group;
    int num_of_players;
    Avltree<std::shared_ptr<Player>,LevelIdKey> players_tree_levels;
    Avltree<std::shared_ptr<Player>,int> players_tree_id;
    int highest_level;
    std::weak_ptr<Player> highest_level_p;

public:
    Group(int id_group): id_group(id_group), highest_level(-1){
        num_of_players=0;
        highest_level_p.lock() = nullptr;
    };
    ~Group()= default;
    std::weak_ptr<Player> getHighestLevelPlayer();
    int getHighestLevel();
    int getGroupId();
    Avltree<std::shared_ptr<Player>, LevelIdKey> getPlayersLevelsTree();
    Avltree<std::shared_ptr<Player>, int> getPlayersTree();
    bool isPlayerInGroup(int player_id, LevelIdKey level_id);
    void addPlayer(std::shared_ptr<Player> new_player);
    void removePlayer(std::shared_ptr<Node<std::shared_ptr<Player> , int>> player_by_id, std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> player_by_level);
    void increasePlayerLevel(std::shared_ptr<Player> player_to_level, int past_lvl, int future_lvl, LevelIdKey past_lvl_id_key);
    int getNumOfPlayers();
    void setPlayersTree(Avltree<std::shared_ptr<Player> ,int> players_tree_id1 , Avltree<std::shared_ptr<Player> , LevelIdKey> players_tree_level);
    void setNumOfPlayers(int num);
    void setHighestPlayer(std::shared_ptr<Player> player);
    StatusType GetAllPlayersByLevelInGroup(int **Players, int *numOfPlayers);
    void resetHighPlayer();
    void resetTrees();
    StatusType updatePlayerToTree(std::weak_ptr<Group> group);

};



#endif //DATASTRUCTURS_HW1_GROUP_H
