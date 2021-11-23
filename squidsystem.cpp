#include "squidsystem.h"

StatusType SquidSystem::AddPlayer(int player_id, int group_id, int level) {
    //what about null ss?
    if (player_id<=0 || group_id<=0 || level<0)
    {
        return INVALID_INPUT;
    }
    if (p_tree.findKey(player_id)!= nullptr)
        return FAILURE;
    if (g_tree.findKey(group_id) == nullptr)
        return FAILURE;
    Player new_player(player_id, level, group_id);
    if (new_player== nullptr)
        return ALLOCATION_ERROR;
    //adding to the players tree
    std::shared_ptr<Node<Player, int>> new_player_node = std::make_shared<Node<Player, int>>(new_player, player_id);
    if (new_player_node == nullptr)
        return ALLOCATION_ERROR;
    p_tree.insert(new_player_node);
    // here insert to group tree

    //adding to the players tree by level
    std::shared_ptr<Node<Player, LevelIdKey>> new_player_level_id_node = std::make_shared<Node<Player, LevelIdKey>>(new_player, new_player.getLevelIdKey());
    if (new_player_level_id_node == nullptr)
        return ALLOCATION_ERROR;
    pl_tree.insert(new_player_level_id_node)
    //here insert to group level tree
}

