#include "squidsystem.h"


void mergeArr(std::shared_ptr<Node<std::shared_ptr<Player> , int>>  players1[], int n1, std::shared_ptr<Node<std::shared_ptr<Player> , int>>  players2[], int n2, std::shared_ptr<Node<std::shared_ptr<Player> , int>>  players_merge[]);
void updateGroupPlayers(std::shared_ptr<Node<std::shared_ptr<Player> , int>> players_merge[],std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players_merge_level [],std::shared_ptr<Group> group,int n);
std::shared_ptr<Player> updateHighestPlayer(std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player,std::shared_ptr<Player> player);
void mergeArrLevel(std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players1[], int n1, std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players2[], int n2, std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> players_merge[]);
std::shared_ptr<Player> getNewHighestPlayer1(Avltree<std::shared_ptr<Player>,LevelIdKey> players_tree);

StatusType SquidSystem::AddGroup(int GroupID) {
    if (GroupID <= 0)
        return INVALID_INPUT;
    if (g_tree.findKey(GroupID))
        return FAILURE;
    try {
        std::shared_ptr<Group> new_group = std::make_shared<Group>(GroupID);
        std::shared_ptr<Node<std::shared_ptr<Group>, int>> new_group_node = std::make_shared<Node<std::shared_ptr<Group>, int>>(new_group, GroupID);
        g_tree.insert(new_group_node);
        num_of_groups++;
        return SUCCESS;
    }
    catch (std::bad_alloc&) {
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
        std::shared_ptr<Player> new_player = std::make_shared<Player>(player_id, level, group_id, player_group);
        std::shared_ptr<Node<std::shared_ptr<Player>, int>> new_player_node = std::make_shared<Node<std::shared_ptr<Player>, int>>(new_player, player_id);
        if (new_player_node == nullptr)
            return ALLOCATION_ERROR;
        p_tree.insert(new_player_node);

        std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> new_player_level_id_node = std::make_shared<Node<std::shared_ptr<Player>, LevelIdKey>>(
                new_player, level_id);
        pl_tree.insert(new_player_level_id_node);

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
    catch (std::bad_alloc&) {
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

std::shared_ptr<Player> getNewHighestPlayer1(Avltree<std::shared_ptr<Player>,LevelIdKey> players_tree)
{
    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> node=players_tree.getRoot();
    while (node->getLeft()!= nullptr)
    {
        node=node->getLeft();
    }
    return node->getData();
}

StatusType SquidSystem::RemovePlayer(int PlayerID) {
    if (PlayerID <= 0)
        return INVALID_INPUT;
    if (p_tree.findKey(PlayerID) == nullptr)
        return FAILURE;
    std::shared_ptr<Player> player_remove = p_tree.findKey(PlayerID)->getData();
    std::weak_ptr<Group> group_p = player_remove->getGroup();
    LevelIdKey level_id(player_remove->getLevel(), PlayerID);
    bool change= false;
    if(player_remove->getId()== group_p.lock()->getHighestLevelPlayer().lock()->getId())
        change= true;
    group_p.lock()->removePlayer(group_p.lock()->getPlayersTree().findKey(PlayerID),group_p.lock()->getPlayersLevelsTree().findKey(level_id));
    p_tree.remove(p_tree.findKey(PlayerID));
    pl_tree.remove(pl_tree.findKey(level_id));
    num_of_players_in_sys--;
    if(num_of_players_in_sys==0)
    {
        highest_level=-1;
        highest_level_p= nullptr;
    }
    else
    {
        if(highest_level_p->getId()==player_remove->getId())
        {
            highest_level_p= getNewHighestPlayer1(pl_tree);
            highest_level=highest_level_p->getLevel();
        }
    }


    if(change)
    {
        std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player = pl_tree_by_group.findKey(group_p.lock()->getGroupId());
        high_player->setData(group_p.lock()->getHighestLevelPlayer().lock());
    }

    if(group_p.lock()->getNumOfPlayers()==0)
    {
        pl_tree_by_group.remove(pl_tree_by_group.findKey(group_p.lock()->getGroupId()));
        num_of_no_empty_group--;
    }

    return SUCCESS;
}


StatusType SquidSystem::ReplaceGroup(int GroupID, int ReplacementID) {
    if (GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID)
        return INVALID_INPUT;
    if (g_tree.findKey(GroupID) == nullptr || g_tree.findKey(ReplacementID) == nullptr)
        return FAILURE;
    std::shared_ptr<Group>  group_delete = g_tree.findKey(GroupID)->getData();
    std::shared_ptr<Group>  new_group = g_tree.findKey(ReplacementID)->getData();
    int num_pl_delete_group=group_delete->getNumOfPlayers(), num_pl_new_group=new_group->getNumOfPlayers();
    if(num_pl_delete_group==0)
    {
        g_tree.remove(g_tree.findKey(GroupID));
        num_of_groups--;
        group_delete.reset();
        return SUCCESS;
    }

    if(num_pl_new_group==0)
    {
        new_group->setPlayersTree(group_delete->getPlayersTree(),group_delete->getPlayersLevelsTree());
        new_group->setNumOfPlayers(num_pl_delete_group);
        new_group->updatePlayerToTree(new_group);
        new_group->setHighestPlayer(group_delete->getHighestLevelPlayer().lock());
        pl_tree_by_group.remove(pl_tree_by_group.findKey(group_delete->getGroupId()));
        std::shared_ptr<Node<std::shared_ptr<Player>, int>> node_to_highest_player_tree=
                std::make_shared<Node<std::shared_ptr<Player>, int>>(group_delete->getHighestLevelPlayer().lock(),ReplacementID);
        pl_tree_by_group.insert(node_to_highest_player_tree);
        g_tree.remove(g_tree.findKey(GroupID));
        num_of_groups--;
        group_delete->resetHighPlayer();
        group_delete.reset();
        return SUCCESS;
    }

    std::shared_ptr<Node<std::shared_ptr<Player> , int>> *players_to_move;
    try {
        players_to_move=new std::shared_ptr<Node<std::shared_ptr<Player> , int>>[num_pl_delete_group];
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    std::shared_ptr<Node<std::shared_ptr<Player> , int>> *players_stay;
    try {
        players_stay=new std::shared_ptr<Node<std::shared_ptr<Player> , int>>[num_pl_new_group];
    }
    catch (std::bad_alloc&)
    {
        delete [] players_to_move;
        return ALLOCATION_ERROR;
    }
    std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> *players_to_move_level;
    try {
        players_to_move_level=new std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>>[num_pl_delete_group];
    }
    catch (std::bad_alloc&)
    {
        delete [] players_to_move;
        delete [] players_stay;
        return ALLOCATION_ERROR;
    }

    std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> *players_stay_level;
    try {
        players_stay_level=new std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>>[num_pl_new_group];
    }
    catch (std::bad_alloc&)
    {
        delete [] players_to_move;
        delete [] players_stay;
        delete [] players_to_move_level;
        return ALLOCATION_ERROR;
    }
    group_delete->getPlayersTree().inorder(group_delete->getPlayersTree().getRoot(),
                                          players_to_move, 0,num_pl_delete_group);
    group_delete->getPlayersLevelsTree().inorder(group_delete->getPlayersLevelsTree().getRoot(),
                                                 players_to_move_level,0,num_pl_delete_group);
    new_group->getPlayersTree().inorder(new_group->getPlayersTree().getRoot(),
                                        players_stay, 0,num_pl_new_group);
    new_group->getPlayersLevelsTree().inorder(new_group->getPlayersLevelsTree().getRoot(),
                                              players_stay_level, 0,num_pl_new_group);

    std::shared_ptr<Node<std::shared_ptr<Player> , int>> *players_merge;
    try {
        players_merge= new std::shared_ptr<Node<std::shared_ptr<Player> , int>> [num_pl_new_group+num_pl_delete_group];
    }
    catch (std::bad_alloc&)
    {
        delete [] players_to_move;
        delete [] players_stay;
        delete [] players_to_move_level;
        delete [] players_stay_level;
        return ALLOCATION_ERROR;
    }
    mergeArr(players_to_move, num_pl_delete_group, players_stay,num_pl_new_group, players_merge);
    std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> *players_merge_level;
    try {
        players_merge_level= new std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>> [num_pl_new_group+num_pl_delete_group];
    }
    catch (std::bad_alloc&)
    {
        delete [] players_to_move;
        delete [] players_stay;
        delete [] players_to_move_level;
        delete [] players_stay_level;
        delete [] players_merge;
        return ALLOCATION_ERROR;
    }
    mergeArrLevel(players_to_move_level, num_pl_delete_group, players_stay_level, num_pl_new_group, players_merge_level);

    Avltree<std::shared_ptr<Player> ,int> players_tree;
    players_tree.makeATree(players_merge,0,num_pl_new_group+num_pl_delete_group-1);

    Avltree<std::shared_ptr<Player> ,LevelIdKey> players_tree_level;
    players_tree_level.makeATree(players_merge_level,0,num_pl_new_group+num_pl_delete_group-1);
    new_group->setPlayersTree(players_tree,players_tree_level);

    updateGroupPlayers(players_merge,players_merge_level,new_group,num_pl_new_group+num_pl_delete_group);
    new_group->setNumOfPlayers(num_pl_delete_group);

    g_tree.remove(g_tree.findKey(GroupID));

    if(num_pl_delete_group>0)
        num_of_no_empty_group--;
    if(num_pl_new_group>0 && num_pl_delete_group>0){
        std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player = pl_tree_by_group.findKey(ReplacementID);
        if(updateHighestPlayer(high_player,group_delete->getHighestLevelPlayer().lock())!= nullptr){
            high_player->setData(group_delete->getHighestLevelPlayer().lock());
            new_group->setHighestPlayer(group_delete->getHighestLevelPlayer().lock());
        }
    }
    num_of_groups--;
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
        if (players1[c1]->getKey() > players2[c2]->getKey()) {
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

    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> player_node_to_reposition = pl_tree.findKey(past_level_id_key);
    std::weak_ptr<Group> group_to_reposition = player_node_to_reposition->getData()->getGroup();
    std::shared_ptr<Node<std::shared_ptr<Player>, int>> high_player = pl_tree_by_group.findKey(group_to_reposition.lock()->getGroupId());
    if(updateHighestPlayer(high_player,player_to_level)!= nullptr){
       high_player->setData(player_to_level);
    }
    group_to_reposition.lock()->increasePlayerLevel(player_to_level, current_level, current_level+LevelIncrease, past_level_id_key);;
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
    *PlayerID = group->getHighestLevelPlayer().lock()->getId();
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
            *Players = nullptr;
            *numOfPlayers=0;
            return SUCCESS;
        }
        int* ret_arr;
        ret_arr = (int*)malloc(num_of_players_in_sys*sizeof(int));
        if (ret_arr == nullptr)
            return ALLOCATION_ERROR;
        std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> *players_arr;
        try {
            players_arr=new std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> [num_of_players_in_sys];
        }
        catch (std::bad_alloc&)
        {
            *Players==nullptr;
            free(ret_arr);
            return ALLOCATION_ERROR;
        }
        pl_tree.inorder(pl_tree.getRoot(), players_arr, 0,num_of_players_in_sys);
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
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    pl_tree_by_group.inorder(pl_tree_by_group.getRoot(), players_arr, 0,numOfGroups);
    for (int i=0;i<numOfGroups;i++)
    {
        ret_arr[i]=(players_arr[i]->getData()->getId());
    }
    *Players=ret_arr;
    delete [] players_arr;
    return SUCCESS;
}


SquidSystem::~SquidSystem() {

    destroy();
}

StatusType SquidSystem::destroy() {
    std::shared_ptr<Node<std::shared_ptr<Player>, int>> *players_arr;
    try {
        players_arr=new std::shared_ptr<Node<std::shared_ptr<Player>, int>> [num_of_players_in_sys];
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> *players_arr_level;
    try {
        players_arr_level=new std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> [num_of_players_in_sys];
    }
    catch (std::bad_alloc&)
    {
        delete [] players_arr;
        return ALLOCATION_ERROR;
    }
    std::shared_ptr<Node<std::shared_ptr<Player>, int>> *players_arr_2;
    try {
        players_arr_2=new std::shared_ptr<Node<std::shared_ptr<Player>, int>> [num_of_no_empty_group];
    }
    catch (std::bad_alloc&)
    {
        delete [] players_arr;
        delete [] players_arr_level;
        return ALLOCATION_ERROR;
    }
    std::shared_ptr<Node<std::shared_ptr<Group>, int>> *group_arr;
    try {
        group_arr=new std::shared_ptr<Node<std::shared_ptr<Group>, int>> [num_of_groups];
    }
    catch (std::bad_alloc&)
    {
        delete [] players_arr;
        delete [] players_arr_level;
        delete [] players_arr_2;
        return ALLOCATION_ERROR;
    }

    p_tree.preorder(p_tree.getRoot(),players_arr,0);
    pl_tree.preorder(pl_tree.getRoot(),players_arr_level,0);
    pl_tree_by_group.preorder(pl_tree_by_group.getRoot(),players_arr_2,0);
    g_tree.preorder(g_tree.getRoot(),group_arr,0);

    for (int (i) = 0; (i) < num_of_players_in_sys; ++(i)) {
        players_arr[i]->getData()->resetGroup();
        players_arr[i]->getData().reset();
        players_arr_level[i]->getData().reset();
    }

    for (int i = 0; i < num_of_no_empty_group; ++i) {
        players_arr_2[i]->getData().reset();
    }
    for (int i = 0; i < num_of_groups; ++i) {
        group_arr[i]->getData()->resetHighPlayer();
        group_arr[i]->getData()->resetTrees();
    }

    pl_tree_by_group.destroy();
    p_tree.destroy();
    g_tree.destroy();
    pl_tree.destroy();
    highest_level_p.reset();

    delete [] players_arr;
    delete [] players_arr_level;
    delete [] players_arr_2;
    delete [] group_arr;

    return  SUCCESS;
}


