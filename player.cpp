

#include "player.h"


bool operator==(const LevelIdKey &key1, const LevelIdKey &key2)
{
return (key1.level==key2.level && key1.id==key2.id);
}
bool operator<(const LevelIdKey &key1, const LevelIdKey &key2)
{
    if (key1.level>key2.level)
        return true;
    else
    {
        if (key1.level==key2.level)
        {
            if(key1.id<key2.id)
                return true;
        }
    }
    return false;
}
bool operator>(const LevelIdKey &key1, const LevelIdKey &key2)
{
    if (key1.level<key2.level)
        return true;
    else
    {
        if (key1.level==key2.level)
        {
            if(key1.id>key2.id)
                return true;
        }
    }
    return false;
}

int Player::getLevel(){
    return this->level;
}
void Player::setLevel(int new_level){
   this->level = new_level;
}
int Player::getId(){
    return this->id;
}
int Player::getGroupId(){
    return this->group_id;
}
void Player::setGroupId(int new_id)
{
    this->group_id = new_id;
}

std::weak_ptr<Group> Player::getGroup() {
    return this->group;
}

void Player::setGroup(std::weak_ptr<Group> group) {
    this->group=group;
}