
#include "group.h"
#include "player.h"

int Group::getGroupId() {
    return this->id_group;
}

int Group::getHighLevelPlayer() {
    return this->highest_level_player;
}

Avltree<Player, LevelIdKey>* Group::getPlayersLevelsTree(){
    return this->players_tree_levels;
}
Avltree<Player, int>* Group::getPlayersTree(){
    return this->players_tree_id;
}
bool Group::isPlayerInGroup(int player_id, LevelIdKey level_id){
    if (players_tree_id->findKey(player_id)!= nullptr && players_tree_levels->findKey(level_id)!= nullptr)
        return true;
    return false;
}
void Group::addPlayer(std::shared_ptr<Node<Player, int>> player_by_id, std::shared_ptr<Node<Player, LevelIdKey>> player_by_level)
{
    players_tree_id->insert(player_by_id);
    players_tree_levels->insert(player_by_level);

}
