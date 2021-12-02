#include "library1.h"
#include "squidsystem.h"

void* Init() {
    SquidSystem *DS = new SquidSystem();
    return (void*)DS;
}

StatusType AddGroup(void *DS, int GroupID){
    if (DS == nullptr)
        return INVALID_INPUT;
    return ((SquidSystem*)DS)-> AddGroup (GroupID);
}

StatusType  AddPlayer(void *DS, int PlayerID, int GroupID, int level)
{
    if (DS == nullptr)
        return INVALID_INPUT;
    return((SquidSystem*)DS)-> AddPlayer(PlayerID, GroupID, level);
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if (DS == nullptr)
        return INVALID_INPUT;
    return((SquidSystem*)DS)-> RemovePlayer(PlayerID);
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID)
{
    if (DS == nullptr)
        return INVALID_INPUT;
    return((SquidSystem*)DS)-> ReplaceGroup(GroupID, ReplacementID);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease)
{
    {
        if (DS == nullptr)
            return INVALID_INPUT;
        return((SquidSystem*)DS)-> IncreaseLevel(PlayerID, LevelIncrease);
    }
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID)
{
    {
        if (DS == nullptr)
            return INVALID_INPUT;
        return((SquidSystem*)DS)-> GetHighestLevel(GroupID, PlayerID);
    }
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers)
{
    {
        if (DS == nullptr)
            return INVALID_INPUT;
        return((SquidSystem*)DS)-> GetAllPlayersByLevel(GroupID, Players, numOfPlayers);
    }
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players)
{
    {
        if (DS == nullptr)
            return INVALID_INPUT;
        return((SquidSystem*)DS)-> GetGroupsHighestLevel(numOfGroups, Players);
    }
}


void Quit(void **DS)
{
    delete DS;
    DS= nullptr;

}
