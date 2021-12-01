
#include "group.h"
#include "player.h"

int Group::getGroupId() {
    return this->id_group;
}

std::shared_ptr<Player> Group::getHighestLevelPlayer() {
    return highest_level_p;
}
int Group::getHighestLevel() {
    return this->highest_level;
}

Avltree<std::shared_ptr<Player>, LevelIdKey> Group::getPlayersLevelsTree(){
    return this->players_tree_levels;
}
Avltree<std::shared_ptr<Player>, int> Group::getPlayersTree(){
    return this->players_tree_id;
}
bool Group::isPlayerInGroup(int player_id, LevelIdKey level_id){
    if (players_tree_id.findKey(player_id)!= nullptr && players_tree_levels.findKey(level_id)!= nullptr)
        return true;
    return false;
}
void Group::addPlayer(std::shared_ptr<Player> new_player)
{
    std::shared_ptr<Node<std::shared_ptr<Player>, int>> new_player_node_for_group = std::make_shared<Node<std::shared_ptr<Player>, int>>(new_player,
                                                                                                                                         new_player->getId());
    LevelIdKey level_id_key = LevelIdKey(new_player->getLevel(), new_player->getId());
    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> new_player_level_id_node_for_group = std::make_shared<Node<std::shared_ptr<Player>, LevelIdKey>>(
            new_player, level_id_key);
    players_tree_id.insert(new_player_node_for_group);
    players_tree_levels.insert(new_player_level_id_node_for_group);
    num_of_players++;
    if((new_player->getLevel())>highest_level)
    {
        highest_level = new_player->getLevel();
        highest_level_p = new_player;
    }
    if((new_player->getLevel())==highest_level)
    {
        if (new_player->getId()<highest_level_p->getId())
        {
            highest_level = new_player->getLevel();
            highest_level_p = new_player;
        }
    }
}




void Group::removePlayer(std::shared_ptr<Node<std::shared_ptr<Player> , int>> player_by_id, std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> player_by_level) {
    this->players_tree_id.remove(player_by_id);
    this->players_tree_levels.remove(player_by_level);
    num_of_players--;
}

void Group::increasePlayerLevel(std::shared_ptr<Player> player_to_level, int past_lvl, int future_lvl, LevelIdKey past_lvl_id_key)
{
    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> player_node_to_reposition_in_group =
            this->getPlayersLevelsTree().findKey(past_lvl_id_key);
    this->players_tree_levels.remove(player_node_to_reposition_in_group);
    (player_node_to_reposition_in_group->getKeyPtr())->setLevel(future_lvl);
    this->players_tree_levels.insert(player_node_to_reposition_in_group);
    if (player_to_level->getLevel() > highest_level) {
        highest_level = player_to_level->getLevel();
        highest_level_p = player_to_level;
    }
    if((player_to_level->getLevel())==highest_level)
    {
        if (player_to_level->getId()<highest_level_p->getId())
        {
            highest_level = player_to_level->getLevel();
            highest_level_p = player_to_level;
        }
    }
}

void Group::removeFromLevelTree(std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> player_by_level)
{
    int current_level = player_by_level->getData()->getLevel();
    players_tree_levels.remove(player_by_level);
}
void Group::addToLevelTree(std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> player_by_level)
{
    int current_level = player_by_level->getData()->getLevel();
    players_tree_levels.insert(player_by_level);
}

int Group::getNumOfPlayers() {
    return num_of_players;
}

void Group::setPlayersTree(Avltree<std::shared_ptr<Player> , int> players_tree_id1) {
    players_tree_id=players_tree_id1;
}

void Group::setNumOfPlayers(int num) {
    this->num_of_players+=num;
}

void Group::setHighestPlayer(std::shared_ptr<Player> player) {
    this->highest_level_p=player;
    this->highest_level=player->getLevel();
}
