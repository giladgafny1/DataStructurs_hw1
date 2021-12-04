
#include "group.h"
#include "player.h"
std::shared_ptr<Player> getNewHighestPlayer(Avltree<std::shared_ptr<Player>,LevelIdKey> players_tree);


int Group::getGroupId() {
    return this->id_group;
}

std::weak_ptr<Player> Group::getHighestLevelPlayer() {
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
        if (new_player->getId()<highest_level_p.lock()->getId())
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
    if(num_of_players==0)
    {
        highest_level=-1;
        highest_level_p.lock()= nullptr;
    }
    else
    {
        if(highest_level_p.lock()->getId()==player_by_id->getData()->getId())
        {
            highest_level_p= getNewHighestPlayer(players_tree_levels);
            highest_level=highest_level_p.lock()->getLevel();
        }
    }
}

std::shared_ptr<Player> getNewHighestPlayer(Avltree<std::shared_ptr<Player>,LevelIdKey> players_tree)
{
    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> node=players_tree.getRoot();
    while (node->getLeft()!= nullptr)
    {
        node=node->getLeft();
    }
    return node->getData();
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
        if (player_to_level->getId()<highest_level_p.lock()->getId())
        {
            highest_level = player_to_level->getLevel();
            highest_level_p = player_to_level;
        }
    }
}


void Group::resetHighPlayer() {
    highest_level_p.reset();
}


int Group::getNumOfPlayers() {
    return num_of_players;
}

void Group::setPlayersTree(Avltree<std::shared_ptr<Player> , int> players_tree_id1 ,Avltree<std::shared_ptr<Player> , LevelIdKey> players_tree_level) {
    players_tree_id=players_tree_id1;
    players_tree_levels=players_tree_level;
}

void Group::setNumOfPlayers(int num) {
    this->num_of_players+=num;
}

void Group::setHighestPlayer(std::shared_ptr<Player> player) {
    this->highest_level_p=player;
    this->highest_level=player->getLevel();
}

StatusType Group::GetAllPlayersByLevelInGroup(int **Players, int *numOfPlayers)
{
    if(num_of_players==0)
    {
        Players = nullptr;
        *numOfPlayers=0;
        return SUCCESS;
    }
    int* ret_arr;
    ret_arr = (int*)malloc(num_of_players*sizeof(int));
    if (ret_arr == nullptr)
        return ALLOCATION_ERROR;
    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> *players_arr;
    try{
        players_arr= new std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> [num_of_players];
    }
    catch (std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }
    players_tree_levels.inorder(players_tree_levels.getRoot(), players_arr, 0,num_of_players);
    for (int i=0;i<num_of_players;i++)
    {
        ret_arr[i]=(players_arr[i]->getData()->getId());
    }
    *numOfPlayers=num_of_players;
    *Players=ret_arr;
    delete [] players_arr;
    return SUCCESS;
}

void Group::resetTrees() {
    std::shared_ptr<Node<std::shared_ptr<Player>, int>> *players_arr;
    players_arr=new std::shared_ptr<Node<std::shared_ptr<Player>, int>> [num_of_players];

    std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> *players_arr_level;
    players_arr_level=new std::shared_ptr<Node<std::shared_ptr<Player>, LevelIdKey>> [num_of_players];

    players_tree_levels.preorder(players_tree_levels.getRoot(),players_arr_level,0);
    players_tree_id.preorder(players_tree_id.getRoot(),players_arr,0);
    for (int i = 0; i < num_of_players; ++i) {
        players_arr[i]->getData()->resetGroup();
        players_arr[i]->getData().reset();
        if(players_arr[i]->getParent()!= nullptr)
        {
            if(players_arr[i]->isLeft())
                players_arr[i]->getParent()->setLeft(nullptr);
            else
                players_arr[i]->getParent()->setRight(nullptr);
        }
        players_arr[i]->setParent(nullptr);
        players_arr[i]->setLeft(nullptr);
        players_arr[i]->setRight(nullptr);
        players_arr[i].reset();


        players_arr_level[i]->getData().reset();
        if(players_arr_level[i]->getParent()!= nullptr)
        {
            if(players_arr_level[i]->isLeft())
                players_arr_level[i]->getParent()->setLeft(nullptr);
            else
                players_arr_level[i]->getParent()->setRight(nullptr);
        }
        players_arr_level[i]->setParent(nullptr);
        players_arr_level[i]->setLeft(nullptr);
        players_arr_level[i]->setRight(nullptr);
        players_arr_level[i].reset();
    }
    delete [] players_arr;
    delete [] players_arr_level;
}

StatusType Group::updatePlayerToTree(std::weak_ptr<Group> group) {
    std::shared_ptr<Node<std::shared_ptr<Player> , int>>* player_id;
    try {
        player_id=new std::shared_ptr<Node<std::shared_ptr<Player> , int>>[ num_of_players];
    }
    catch (std::bad_alloc)
    {
        return ALLOCATION_ERROR;
    }
    std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>>* player_level;
    try {
        player_level=new std::shared_ptr<Node<std::shared_ptr<Player> , LevelIdKey>>[ num_of_players];
    }
    catch (std::bad_alloc)
    {
        delete []player_id;
        return ALLOCATION_ERROR;
    }
    players_tree_id.inorder(players_tree_id.getRoot(),player_id,0,num_of_players);
    players_tree_levels.inorder(players_tree_levels.getRoot(),player_level,0,num_of_players);
    for (int i = 0; i < num_of_players; ++i) {
        player_id[i]->getData()->setGroup(group);
        player_level[i]->getData()->setGroup(group);
    }
    delete []player_id;
    delete[] player_level;
    return SUCCESS;

}