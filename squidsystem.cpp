#include "squidsystem.h"

/* need to implement in library1.cpp, not here
SquidSystem* SquidSystem::Init()
{
    SquidSystem new_system();
    return new_system;
}
*/
void mergeArr(std::shared_ptr<Node<std::shared_ptr<Player> , int>>  players1[], int n1, std::shared_ptr<Node<std::shared_ptr<Player> , int>>  players2[], int n2, std::shared_ptr<Node<std::shared_ptr<Player> , int>>  players_merge[]);
void updateGroupPlayers(std::shared_ptr<Node<std::shared_ptr<Player> , int>> players_merge[],std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players_merge_level [],std::shared_ptr<Group> group,int n);
std::shared_ptr<Player> updateHighestPlayer(std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player,std::shared_ptr<Player> player);
void mergeArrLevel(std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players1[], int n1, std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players2[], int n2, std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players_merge[]);

StatusType SquidSystem::AddGroup(int GroupID) {
    if (GroupID <= 0)
        return INVALID_INPUT;
    if (g_tree.findKey(GroupID))
        return FAILURE;
    try {
        //adds the group to the groups tree
        std::shared_ptr<Group> new_group = std::make_shared<Group>(GroupID);
        std::shared_ptr<Node<std::shared_ptr<Group>, int>> new_group_node = std::make_shared<Node<std::shared_ptr<Group>, int>>(new_group, GroupID);
        g_tree.insert(new_group_node);
        return SUCCESS;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType SquidSystem::AddPlayer(int player_id, int group_id, int level) {
    if (player_id <= 0 || group_id <= 0 || level < 0) {
        return INVALID_INPUT;
    }
    if (p_tree.findKey(player_id) != nullptr)
        return FAILURE;
    std::shared_ptr<Node<std::shared_ptr<Group>, int>> group_to_add_node = g_tree.findKey(group_id);
    if (group_to_add_node == nullptr)
        return FAILURE;
    try {
        LevelIdKey level_id(level, player_id);
        std::shared_ptr<Group> player_group = group_to_add_node->getData();
        //not needed
        if (player_group->isPlayerInGroup(player_id, level_id))
            return FAILURE;
        std::shared_ptr<Player> new_player = std::make_shared<Player>(player_id, level, group_id, player_group);
        //adding to the players tree
        std::shared_ptr<Node<std::shared_ptr<Player>, int>> new_player_node = std::make_shared<Node<std::shared_ptr<Player>, int>>(new_player, player_id);
        if (new_player_node == nullptr)
            return ALLOCATION_ERROR;
        p_tree.insert(new_player_node);

        //adding to the players tree by level
        std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> new_player_level_id_node = std::make_shared<Node<std::shared_ptr<Player>, LevelIdKey>>(
                new_player, level_id);
        pl_tree.insert(new_player_level_id_node);
        //checking if highest_level
        if (level > highest_level) {
            highest_level = level;
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
        //adding player to the group's trees - 2*logn

        if(player_group->getNumOfPlayers()==0)
        {
            std::shared_ptr<Node<std::shared_ptr<Player>, int>> node_to_highest_player_tree=
                    std::make_shared<Node<std::shared_ptr<Player>, int>>(new_player,group_id);
            pl_tree_by_group.insert(node_to_highest_player_tree);
            num_of_no_empty_group++;
        }
        else
        {
            std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player = pl_tree_by_group.findKey(group_id);
            if(updateHighestPlayer(high_player,new_player)!= nullptr)
                high_player->setData(updateHighestPlayer(high_player,new_player));
        }

        group_to_add_node->getData()->addPlayer(new_player);
        num_of_players_in_sys++;
        return SUCCESS;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }

}

std::shared_ptr<Player> updateHighestPlayer(std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player,std::shared_ptr<Player> player)
{
    if(high_player->getData()->getLevel()<player->getLevel())
    {
        return player;
    }
    if(high_player->getData()->getLevel()==player->getLevel())
    {
        if(player->getId()<high_player->getData()->getId())
        {
            return player;
        }
    }
    return nullptr;
}

StatusType SquidSystem::RemovePlayer(int PlayerID) {
    if (PlayerID <= 0)
        return INVALID_INPUT;
    if (p_tree.findKey(PlayerID) == nullptr)
        return FAILURE;
    std::shared_ptr<Player> player_remove = p_tree.findKey(PlayerID)->getData();
    std::shared_ptr<Group> group_p = player_remove->getGroup();
    LevelIdKey level_id(player_remove->getLevel(), PlayerID);
    bool change= false;
    if(player_remove->getId()== group_p->getHighestLevelPlayer()->getId())
        change= true;
    group_p->removePlayer(group_p->getPlayersTree().findKey(PlayerID),group_p->getPlayersLevelsTree().findKey(level_id));
    p_tree.remove(p_tree.findKey(PlayerID));
    pl_tree.remove(pl_tree.findKey(level_id));

    if(change)
    {
        std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player = pl_tree_by_group.findKey(group_p->getGroupId());
        high_player->setData(group_p->getHighestLevelPlayer());
    }

    if(group_p->getNumOfPlayers()==0)
    {
        pl_tree_by_group.remove(pl_tree_by_group.findKey(group_p->getGroupId()));
        num_of_no_empty_group--;
    }
    num_of_players_in_sys--;
    return SUCCESS;
}


StatusType SquidSystem::ReplaceGroup(int GroupID, int ReplacementID) {
    if (GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID)
        return INVALID_INPUT;
    if (g_tree.findKey(GroupID) == nullptr || g_tree.findKey(ReplacementID) == nullptr)
        return FAILURE;
    // logk
    std::shared_ptr<Group>  group_delete = g_tree.findKey(GroupID)->getData();
    std::shared_ptr<Group>  new_group = g_tree.findKey(ReplacementID)->getData();
    std::shared_ptr<Node<std::shared_ptr<Player> , int>> *players_to_move;
    try {
        players_to_move=new  std::shared_ptr<Node<std::shared_ptr<Player> , int>> [group_delete->getNumOfPlayers()];
    }
    catch (std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }

    std::shared_ptr<Node<std::shared_ptr<Player> , int>> *players_stay;
    try {
        players_stay=new  std::shared_ptr<Node<std::shared_ptr<Player> , int>> [new_group->getNumOfPlayers()];
    }
    catch(std::bad_alloc) {
        delete [] players_to_move;
        return ALLOCATION_ERROR;
    }
    std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> *players_to_move_level;
    try {
        players_to_move_level=new std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>>[group_delete->getNumOfPlayers()];
    }
    catch (std::bad_alloc)
    {
        delete [] players_to_move;
        delete [] players_stay;
        return ALLOCATION_ERROR;
    }

    std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> *players_stay_level;
    try {
        players_stay_level=new std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>>[new_group->getNumOfPlayers()];
    }
    catch (std::bad_alloc)
    {
        delete [] players_to_move;
        delete [] players_stay;
        delete [] players_to_move_level;
        return ALLOCATION_ERROR;
    }
    //o(n_group)
    group_delete->getPlayersTree().inorder(group_delete->getPlayersTree().getRoot(),
                                          players_to_move, 0);
    group_delete->getPlayersLevelsTree().inorder(group_delete->getPlayersLevelsTree().getRoot(),
                                        players_to_move_level,0);
    //o(n_rep)
    new_group->getPlayersTree().inorder(new_group->getPlayersTree().getRoot(),
                                       players_stay, 0);
    new_group->getPlayersLevelsTree().inorder(new_group->getPlayersLevelsTree().getRoot(),
                                        players_stay_level, 0);

    std::shared_ptr<Node<std::shared_ptr<Player> , int>> *players_merge;
    try {
        players_merge= new std::shared_ptr<Node<std::shared_ptr<Player> , int>> [group_delete->getNumOfPlayers() + new_group->getNumOfPlayers()];
    }
    catch (std::bad_alloc)
    {
        delete [] players_to_move;
        delete [] players_stay;
        delete [] players_to_move_level;
        delete [] players_stay_level;
        return ALLOCATION_ERROR;
    }
    mergeArr(players_to_move, group_delete->getNumOfPlayers(), players_stay, new_group->getNumOfPlayers(), players_merge);
    std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> *players_merge_level;
    try {
        players_merge_level= new std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> [group_delete->getNumOfPlayers() + new_group->getNumOfPlayers()];
    }
    catch (std::bad_alloc)
    {
        delete [] players_to_move;
        delete [] players_stay;
        delete [] players_to_move_level;
        delete [] players_stay_level;
        delete [] players_merge;
        return ALLOCATION_ERROR;
    }
    mergeArrLevel(players_to_move_level, group_delete->getNumOfPlayers(), players_stay_level, new_group->getNumOfPlayers(), players_merge_level);

    Avltree<std::shared_ptr<Player> ,int> players_tree;
    players_tree.makeATree(players_merge,0,new_group->getNumOfPlayers()+ group_delete->getNumOfPlayers()-1);


    Avltree<std::shared_ptr<Player> ,LevelIdKey> players_tree_level;
    players_tree_level.makeATree(players_merge_level,0,new_group->getNumOfPlayers()+ group_delete->getNumOfPlayers()-1);
    new_group->setPlayersTree(players_tree,players_tree_level);

    updateGroupPlayers(players_merge,players_merge_level,new_group,new_group->getNumOfPlayers()+group_delete->getNumOfPlayers());
    new_group->setNumOfPlayers(group_delete->getNumOfPlayers());

    g_tree.remove(g_tree.findKey(GroupID));
    if(group_delete->getNumOfPlayers()>0)
        num_of_no_empty_group--;
    std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player = pl_tree_by_group.findKey(ReplacementID);
    if(updateHighestPlayer(high_player,group_delete->getHighestLevelPlayer())!= nullptr){
        high_player->setData(group_delete->getHighestLevelPlayer());
        new_group->setHighestPlayer(group_delete->getHighestLevelPlayer());
    }

    pl_tree_by_group.remove(pl_tree_by_group.findKey(group_delete->getGroupId()));
    delete [] players_to_move;
    delete [] players_stay;
    delete [] players_to_move_level;
    delete [] players_stay_level;
    delete [] players_merge;
    delete [] players_merge_level;
    return SUCCESS;
}

void updateGroupPlayers(std::shared_ptr<Node<std::shared_ptr<Player> , int>> players_merge[],std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players_merge_level [],std::shared_ptr<Group> group,int n)
{
    for(int i=0;i<n;i++)
    {
        players_merge[i]->getData()->setGroup(group);
        players_merge[i]->getData()->setGroupId(group->getGroupId());
        players_merge_level[i]->getData()->setGroup(group);
        players_merge_level[i]->getData()->setGroupId(group->getGroupId());
    }
}

void mergeArr(std::shared_ptr<Node<std::shared_ptr<Player> , int>> players1[], int n1, std::shared_ptr<Node<std::shared_ptr<Player> , int>> players2[], int n2, std::shared_ptr<Node<std::shared_ptr<Player> , int>> players_merge[]) {
    int c1 = 0, c2 = 0;
    while (c1 != n1 && c2 != n2) {
        if (players1[c1]->getData()->getId() > players2[c2]->getData()->getId()) {
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

void mergeArrLevel(std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players1[], int n1, std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players2[], int n2, std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players_merge[]) {
    int c1 = 0, c2 = 0;
    while (c1 != n1 && c2 != n2) {
        if (players1[c1]->getData()->getId() > players2[c2]->getData()->getId()) {
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

    std::shared_ptr<Player> player_to_level = p_tree.findKey(PlayerID)->getData();
    int current_level = player_to_level->getLevel();
    LevelIdKey past_level_id_key(current_level, PlayerID);
    player_to_level->setLevel(current_level + LevelIncrease);

    //replacing player in the level tree according to he's/she's level:
    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> player_node_to_reposition = pl_tree.findKey(past_level_id_key);
    std::shared_ptr<Group> group_to_reposition = player_node_to_reposition->getData()->getGroup();
    std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player = pl_tree_by_group.findKey(group_to_reposition->getGroupId());
    if(updateHighestPlayer(high_player,player_to_level)!= nullptr){
       high_player->setData(player_to_level);
    }
    group_to_reposition->increasePlayerLevel(player_to_level, current_level, current_level+LevelIncrease, past_level_id_key);;
    pl_tree.remove(player_node_to_reposition);
    (player_node_to_reposition->getKeyPtr())->setLevel(current_level + LevelIncrease);
    player_node_to_reposition->getData()->setLevel(current_level + LevelIncrease);
    pl_tree.insert(player_node_to_reposition);
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
    std::shared_ptr<Group> group = g_tree.findKey(GroupID)->getData();
    if (group->getHighestLevel() == -1) {
        *PlayerID = -1;
        return SUCCESS;
    }
    *PlayerID = group->getHighestLevelPlayer()->getId();
    return SUCCESS;
}

StatusType SquidSystem::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers)
{
    if (GroupID==0 || Players==nullptr || numOfPlayers==nullptr)
        return INVALID_INPUT;
    if (GroupID<0)
    {
        if(num_of_players_in_sys==0)
        {
            Players = nullptr;
            *numOfPlayers=0;
            return SUCCESS;
        }
        int* ret_arr;
        ret_arr = (int*)malloc(num_of_players_in_sys*sizeof(int));
        if (ret_arr == nullptr)
            return ALLOCATION_ERROR;
        //helper array so can be statically allocated - try?
        std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> *players_arr;
        try {
            players_arr=new std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> [num_of_players_in_sys];
        }
        catch (std::bad_alloc)
        {
            return ALLOCATION_ERROR;
        }
        pl_tree.inorder(pl_tree.getRoot(), players_arr, 0);
        for (int i=0;i<num_of_players_in_sys;i++)
        {
            ret_arr[i]=(players_arr[i]->getData()->getId());
        }
        *numOfPlayers=num_of_players_in_sys;
        *Players=ret_arr;
        delete [] players_arr;
        return SUCCESS;
    }
    if (g_tree.findKey(GroupID) == nullptr)
        return FAILURE;
    std::shared_ptr<Group> group = g_tree.findKey(GroupID)->getData();
    return (group->GetAllPlayersByLevelInGroup(Players, numOfPlayers));
}

StatusType SquidSystem::GetGroupsHighestLevel(int numOfGroups, int **Players)
{
    if(Players== nullptr || numOfGroups<1)
        return INVALID_INPUT;
    if(numOfGroups>num_of_no_empty_group)
        return FAILURE;
    int* ret_arr;
    ret_arr = (int*)malloc(numOfGroups*sizeof(int));
    if (ret_arr == nullptr)
        return ALLOCATION_ERROR;
    std::shared_ptr<Node<std::shared_ptr<Player>, int>> *players_arr;
    try {
        players_arr=new std::shared_ptr<Node<std::shared_ptr<Player>, int>> [numOfGroups];
    }
    catch (std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }
    pl_tree_by_group.inorder(pl_tree_by_group.getRoot(), players_arr, 0);
    for (int i=0;i<numOfGroups;i++)
    {
        ret_arr[i]=(players_arr[i]->getData()->getId());
    }
    *Players=ret_arr;
    delete [] players_arr;
    return SUCCESS;
}


void SquidSystem::Quit() {

}