#include "squidsystem.h"

/* need to implement in library1.cpp, not here
SquidSystem* SquidSystem::Init()
{
    SquidSystem new_system();
    return new_system;
}
*/
void mergeArr(std::shared_ptr<Node<Player, int>>  players1[], int n1, std::shared_ptr<Node<Player, int>>  players2[], int n2, std::shared_ptr<Node<Player, int>>  players_merge[]);
void updateGroupPlayers(std::shared_ptr<Node<Player, int>> players_merge[], Group* group, int n);

StatusType SquidSystem::AddGroup(int GroupID) {
    if (GroupID <= 0)
        return INVALID_INPUT;
    if (g_tree.findKey(GroupID))
        return FAILURE;
    try {
        //adds the group to the groups tree
        Group new_group(GroupID);
        std::shared_ptr<Node<Group, int>> new_group_node = std::make_shared<Node<Group, int>>(new_group, GroupID);
        g_tree.insert(new_group_node);
        return SUCCESS;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType SquidSystem::AddPlayer(int player_id, int group_id, int level) {
    //what about null ss? - in library1.cpp
    if (player_id <= 0 || group_id <= 0 || level < 0) {
        return INVALID_INPUT;
    }
    if (p_tree.findKey(player_id) != nullptr)
        return FAILURE;
    std::shared_ptr<Node<Group, int>> group_to_add_node = g_tree.findKey(group_id);
    if (group_to_add_node == nullptr)
        return FAILURE;
    try {
        LevelIdKey level_id(level, player_id);
        Group *player_group = &g_tree.findKey(group_id)->getData();
        if (group_to_add_node->getData().isPlayerInGroup(player_id, level_id))
            return FAILURE;
        Player new_player(player_id, level, group_id, player_group);
        //adding to the players tree
        std::shared_ptr<Node<Player, int>> new_player_node = std::make_shared<Node<Player, int>>(new_player, player_id);
        if (new_player_node == nullptr)
            return ALLOCATION_ERROR;
        p_tree.insert(new_player_node);

        //adding to the players tree by level
        std::shared_ptr<Node<Player, LevelIdKey>> new_player_level_id_node = std::make_shared<Node<Player, LevelIdKey>>(
                new_player, new_player.getLevelIdKey());
        if (new_player_level_id_node == nullptr)
            return ALLOCATION_ERROR;
        pl_tree.insert(new_player_level_id_node);
        //checking if highest_level
        if (level > highest_level) {
            highest_level = level;
            highest_level_p = new_player_node->getDataPtr();
        }
        //adding player to the group's trees - 2*logn
        /*
        std::shared_ptr<Node<Player, int>> new_player_node_for_group = std::make_shared<Node<Player, int>>(new_player,
                                                                                                           player_id);
        std::shared_ptr<Node<Player, LevelIdKey>> new_player_level_id_node_for_group = std::make_shared<Node<Player, LevelIdKey>>(
                new_player, new_player.getLevelIdKey());

        group_to_add_node->getData().addPlayer(new_player_node_for_group, new_player_level_id_node_for_group);
        */
        group_to_add_node->getData().addPlayer1(&new_player);
        //if the group was empty, adds it to the not empty groups tree - logn
        if (!g_ne_tree.findKey(group_id)) {
            std::shared_ptr<Node<Group, int>> existing_group_node(group_to_add_node);
            g_ne_tree.insert(existing_group_node);
        }
        return SUCCESS;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }

}

StatusType SquidSystem::RemovePlayer(int PlayerID) {
    if (PlayerID <= 0)
        return INVALID_INPUT;
    if (p_tree.findKey(PlayerID) == nullptr)
        return FAILURE;
    Player player_remove = p_tree.findKey(PlayerID)->getData();
    Group *group_p = player_remove.getGroup();
    LevelIdKey level_id(player_remove.getLevel(), PlayerID);
    group_p->removePlayer(p_tree.findKey(PlayerID), pl_tree.findKey(level_id));
    p_tree.remove(p_tree.findKey(PlayerID));
    pl_tree.remove(pl_tree.findKey(level_id));
    return SUCCESS;
}


StatusType SquidSystem::ReplaceGroup(int GroupID, int ReplacementID) {
    if (GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID)
        return INVALID_INPUT;
    if (g_tree.findKey(GroupID) == nullptr || g_tree.findKey(ReplacementID) == nullptr)
        return FAILURE;
    // logk
    Group* group_delete = &g_tree.findKey(GroupID)->getData();
    Group* new_group = &g_tree.findKey(ReplacementID)->getData();
    std::shared_ptr<Node<Player, int>> players_to_move[group_delete->getNumOfPlayers()];
    std::shared_ptr<Node<Player, int>> players_stay[new_group->getNumOfPlayers()];
    //o(n_group)
    group_delete->getPlayersTree().inorder(group_delete->getPlayersTree().getRoot(),
                                          players_to_move, 0);
    //o(n_rep)
    new_group->getPlayersTree().inorder(new_group->getPlayersTree().getRoot(),
                                       players_stay, 0);

    std::shared_ptr<Node<Player, int>> players_merge[group_delete->getNumOfPlayers() + new_group->getNumOfPlayers()];
    mergeArr(players_to_move, group_delete->getNumOfPlayers(), players_stay, new_group->getNumOfPlayers(), players_merge);

    Avltree<Player,int> players_tree;
    players_tree.makeATree(players_merge,0,new_group->getNumOfPlayers()+ group_delete->getNumOfPlayers()-1);
    new_group->setPlayersTree(players_tree);

    updateGroupPlayers(players_merge,new_group,new_group->getNumOfPlayers()+group_delete->getNumOfPlayers());
    new_group->setNumOfPlayers(group_delete->getNumOfPlayers());

    g_tree.remove(g_tree.findKey(GroupID));

    return SUCCESS;
}

void updateGroupPlayers(std::shared_ptr<Node<Player, int>> players_merge[],Group* group,int n)
{
    for(int i=0;i<n;i++)
    {
        players_merge[i]->getDataPtr()->setGroup(group);
        players_merge[i]->getDataPtr()->setGroupId(group->getGroupId());
    }
}

void mergeArr(std::shared_ptr<Node<Player, int>> players1[], int n1, std::shared_ptr<Node<Player, int>> players2[], int n2, std::shared_ptr<Node<Player, int>> players_merge[]) {
    int c1 = 0, c2 = 0;
    while (c1 != n1 && c2 != n2) {
        if (players1[c1]->getData().getId() > players2[c2]->getData().getId()) {
            players_merge[c1 + c2] = players2[c2];
            c2++;
        } else {
            players_merge[c1 + c2] = players1[c1];
            c1++;
        }
    }
    while (c1 != n1) {
        players_merge[c1 + c2] = players1[c1];
        c1++;
    }
    while (c2 != n2) {
        players_merge[c1 + c2] = players2[c2];
        c2++;
    }
    for(int i=0;i<n2+n1;i++)
    {
        players_merge[i]->removeTies();
    }
}


StatusType SquidSystem::IncreaseLevel(int PlayerID, int LevelIncrease) {
    if (PlayerID <= 0 || LevelIncrease <= 0) {
        return INVALID_INPUT;
    }
    if (p_tree.findKey(PlayerID) == nullptr)
        return FAILURE;
    //does it return the player and i can manipulate it's data?
    Player *player_to_level = p_tree.findKey(PlayerID)->getDataPtr();
    int current_level = player_to_level->getLevel();
    LevelIdKey level_id_key(current_level, PlayerID);
    player_to_level->setLevel(current_level + LevelIncrease);

    //replacing player in the level tree according to he's/she's level:
    std::shared_ptr<Node<Player, LevelIdKey>> player_node_to_reposition = pl_tree.findKey(level_id_key);
    Group *group_to_reposition = player_node_to_reposition->getDataPtr()->getGroup();
    std::shared_ptr<Node<Player, LevelIdKey>> player_node_to_reposition_in_group =
            group_to_reposition->getPlayersLevelsTree().findKey(level_id_key);
    group_to_reposition->removeFromLevelTree(player_node_to_reposition_in_group);
    pl_tree.remove(player_node_to_reposition);
    (player_node_to_reposition->getKeyPtr())->setLevel(current_level + LevelIncrease);
    player_node_to_reposition->getDataPtr()->setLevel(current_level + LevelIncrease);
    (player_node_to_reposition->getKeyPtr())->setLevel(current_level + LevelIncrease);
    (player_node_to_reposition_in_group->getKeyPtr())->setLevel(current_level + LevelIncrease);
    player_node_to_reposition_in_group->getDataPtr()->setLevel(current_level + LevelIncrease);
    group_to_reposition->addToLevelTree(player_node_to_reposition_in_group);
    pl_tree.insert(player_node_to_reposition);

    if (player_to_level->getLevel() > highest_level) {
        highest_level = player_to_level->getLevel();
        highest_level_p = player_to_level;
    }
    return SUCCESS;
}

StatusType SquidSystem::GetHighestLevel(int GroupID, int *PlayerID) {
    if (GroupID == 0 || PlayerID == nullptr)
        return INVALID_INPUT;
    if (GroupID < 0) {
        if (highest_level == -1)
            *PlayerID = -1;
        else
            *PlayerID = (highest_level_p->getId());
        return SUCCESS;
    }
    if (g_tree.findKey(GroupID) == nullptr)
        return FAILURE;
    Group *group = g_tree.findKey(GroupID)->getDataPtr();
    if (group->getHighestLevel() == -1) {
        *PlayerID = -1;
        return SUCCESS;
    }
    *PlayerID = group->getHighestLevelPlayer()->getId();
    return SUCCESS;
}

