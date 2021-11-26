//
// Created by Gilad on 22/11/2021.
//

#ifndef DATASTRUCTURS_HW1_PLAYER_H
#define DATASTRUCTURS_HW1_PLAYER_H
#include "group.h"

class LevelIdKey
{
public:
    int level;
    int id;

    LevelIdKey(int level, int id): level(level), id(id){}
    LevelIdKey():level(0), id(0){}
    ~LevelIdKey()=default;
    LevelIdKey &operator=(const LevelIdKey &level_id_key) = default;

    void setLevel(int level)
    {
        this->level = level;
    }

    friend bool operator==(const LevelIdKey &key1, const LevelIdKey &key2);
    friend bool operator<(const LevelIdKey &key1, const LevelIdKey &key2);
    friend bool operator>(const LevelIdKey &key1, const LevelIdKey &key2);

};

class Player {
public:
    int id;
    int level;
    LevelIdKey level_id;
    int group_id;
    Group* group;


    Player(int id, int level, int group_i, Group* group): id(id), level(level), group_id(group_id){
        //good?
        level_id = LevelIdKey(level, id);
        this->group = group;
    }
    ~Player()=default;

    int getLevel();
    void setLevel(int new_level);
    int getId();
    LevelIdKey getLevelIdKey();
    int getGroupId();
    void setGroupId(int new_id);
    Group getGroup();
    void setGroup(Group group);


};


#endif //DATASTRUCTURS_HW1_PLAYER_H
