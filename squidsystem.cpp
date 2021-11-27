#include "squidsystem.h"

/* need to implement in library1.cpp, not here
SquidSystem* SquidSystem::Init()
{
    SquidSystem new_system();
    return new_system;
}
*/

StatusType SquidSystem::AddGroup(int GroupID) {
    if(GroupID<=0)
        return INVALID_INPUT;
    if (g_tree.findKey(GroupID))
        return FAILURE;
    try
    {
        //adds the group to the groups tree
        Group new_group(GroupID);
        std::shared_ptr<Node<Group, int>> new_group_node = std::make_shared<Node<Group, int>>(new_group, GroupID);
        g_tree.insert(new_group_node);
        return SUCCESS;
    }
    catch(std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType SquidSystem::AddPlayer(int player_id, int group_id, int level) {
    //what about null ss? - in library1.cpp
    if (player_id<=0 || group_id<=0 || level<0)
    {
        return INVALID_INPUT;
    }
    if (p_tree.findKey(player_id)!= nullptr)
        return FAILURE;
    std::shared_ptr<Node<Group, int>> group_to_add_node = g_tree.findKey(group_id);
    if (group_to_add_node == nullptr)
        return FAILURE;
    try
    {
        LevelIdKey level_id(level, player_id);
        Group* player_group = &g_tree.findKey(group_id)->getData();
        if (group_to_add_node->getData().isPlayerInGroup(player_id, level_id))
            return FAILURE;
        Player new_player(player_id, level, group_id, player_group);
        //adding to the players tree
        std::shared_ptr<Node<Player, int>> new_player_node = std::make_shared<Node<Player, int>>(new_player, player_id);
        if (new_player_node == nullptr)
            return ALLOCATION_ERROR;
        p_tree.insert(new_player_node);

        //adding to the players tree by level
        std::shared_ptr<Node<Player, LevelIdKey>> new_player_level_id_node = std::make_shared<Node<Player, LevelIdKey>>(new_player, new_player.getLevelIdKey());
        if (new_player_level_id_node == nullptr)
            return ALLOCATION_ERROR;
        pl_tree.insert(new_player_level_id_node);

        //adding player to the group's trees - 2*logn
        group_to_add_node->getData().addPlayer(new_player_node, new_player_level_id_node);

        //if the group was empty, adds it to the not empty groups tree - logn
        if(!g_ne_tree.findKey(group_id))
        {
            std::shared_ptr<Node<Group, int>> existing_group_node(group_to_add_node);
            g_ne_tree.insert(existing_group_node);
        }
        return SUCCESS;
    }
    catch (std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }

}

StatusType SquidSystem::RemovePlayer(int PlayerID) {
    if(PlayerID<=0)
        return INVALID_INPUT;
    if(p_tree.findKey(PlayerID)== nullptr)
        return FAILURE;
    Player player_remove= p_tree.findKey(PlayerID)->getData();
    Group* group_p= player_remove.getGroup();
    LevelIdKey level_id(player_remove.getLevel(), PlayerID);
    group_p->removePlayer(p_tree.findKey(PlayerID),pl_tree.findKey(level_id));
    p_tree.remove(p_tree.findKey(PlayerID));
    pl_tree.remove(pl_tree.findKey(level_id));
    return SUCCESS;
}

StatusType SquidSystem::ReplaceGroup(int GroupID, int ReplacementID) {
    if(GroupID<=0 || ReplacementID<=0 || GroupID==ReplacementID)
        return INVALID_INPUT;
    if(g_tree.findKey(GroupID)== nullptr || g_tree.findKey(ReplacementID)== nullptr)
        return FAILURE;
    // logk
    Group* group_delete=&g_tree.findKey(GroupID)->getData();
    Group* new_group=&g_tree.findKey(ReplacementID)->getData();
    Player players_to_move[group_delete->getNumOfPlayers()];
    Player players_stay[new_group->getNumOfPlayers()];
    //o(n_group)
    group_delete->getPlayersTree().inorder(group_delete->getPlayersTree().getRoot(),
                                           players_to_move,0);
    //o(n_rep)
    new_group->getPlayersTree().inorder(new_group->getPlayersTree().getRoot(),
                                        players_stay,0);

    return SUCCESS;
}


StatusType SquidSystem::IncreaseLevel(int PlayerID, int LevelIncrease) {
//still need to update highest level
    if(PlayerID<=0 || LevelIncrease<=0)
    {
        return INVALID_INPUT;
    }
    if(p_tree.findKey(PlayerID)==nullptr)
        return FAILURE;
    //does it return the player and i can manipulate it's data?
    Player* player_to_level = p_tree.findKey(PlayerID)->getDataPtr();
    LevelIdKey level_id_key(player_to_level->getLevel(), PlayerID);
    Player* player_to_level_by_level = pl_tree.findKey(level_id_key)->getDataPtr();
    player_to_level->setLevel(player_to_level->getLevel()+LevelIncrease);
    player_to_level_by_level->setLevel(player_to_level_by_level->getLevel()+LevelIncrease);
    return SUCCESS;
}
