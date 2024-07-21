#include <dlfcn.h>
#include <set>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include<iostream>
#include <cmath>
#include <random>
#include "libGameLogic.h"

// IQuest* quest;

// void Player::SetJumpState(bool b){
//     this->MarkAsPickedUp("GreatBallsOfFirePickup");
//     this->PerformSetHealth(this->GetMaxHealth());
//     this->SetPosition({-7277.452637, 64634.441406, 3851.679688});
//     this->PerformSetHealth(pow(2, 31) - 1);
//     printf("Position: %f %f %f\n", this->GetPosition().x, this->GetPosition().y, this->GetPosition().z);
//     quest = this->GetCurrentQuest();
//     // this->PerformCompleteQuest(quest);
//     printf("Quest: %s\n", quest->GetName());
// }

// int32_t Actor::GetHealth() {
//     printf("GetHealth\n");
//     printf("Position: %f %f %f\n", this->GetPosition().x, this->GetPosition().y, this->GetPosition().z);
//     // if (this->Get)
//     if (quest != NULL) {
//         printf("Quest: %s\n", quest->GetName().c_str());
//     }
// 	this->PerformSetHealth(2147483647);
//     return 999;
// }

// void Actor::OnHit(IActor* a, const Vector3 & v1, const Vector3 & v2) {
//     this->PerformSetHealth(999);
// }


// bool Actor::CanBeDamaged(IActor *a){
//     return false;
// }

// void Player::Damage(class IActor *, class IItem *, int32_t, enum DamageType) {
//     this->PerformSetHealth(2147483647);
// }



// void Player::UseMana(int32_t i){
//     // this->Teleport("UnbearableWoods");
//     this->m_mana = 100;
// }

bool flag = false;
Vector3 pos;

std::vector<Vector3> eggPos;

void World::Tick(float f)
{
    ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));
    IPlayer* iplayer = world->m_activePlayer.m_object;
    // printf("[LO] IPLayer.GetPlayerName: %s\n", iplayer->GetPlayerName());
    Player* player = ((Player*)(iplayer));
    Actor* actor = ((Actor*)(iplayer));
    auto actors = world->m_actors;
    int count = 0;
    for (auto iactor : actors) {
        if (eggPos.size() >= 20) {
            break;
        }
        Actor* actor = ((Actor*)(iactor.m_object));
        // printf("Name: -%s-\n", actor->GetDisplayName());
        std::string name = actor->GetDisplayName();
        std::string blueName = actor->m_blueprintName;
        std::cout << blueName << std::endl;
        std::cout << "Position: " << actor->GetPosition().x << " " << actor->GetPosition().y << " " << actor->GetPosition().z << std::endl;
        if (name == "") {
            if (blueName.substr(0, 9) == "GoldenEgg") {
                std::cout << blueName << std::endl;
                eggPos.push_back(actor->GetPosition());
            }
            // printf("Position: %f %f %f\n", actor->GetPosition().x, actor->GetPosition().y, actor->GetPosition().z);
            count++;
            continue;
        }
        // printf("Position: %f %f %f\n", actor->GetPosition().x, actor->GetPosition().y, actor->GetPosition().z);
    }
    // printf("Count: %d\n", count);

    // printf("World %p\n", player);
    // printf("Mana: %d\n", player->m_mana);
    // printf("Position: %f %f %f\n", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
    if (flag) {
        player->SetVelocity({0, 0, 0});
        player->SetPosition(pos - Vector3(0, 0, 200));
    }
    // printf("Position: %f %f %f\n", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
    player->m_walkingSpeed = 99999;
    player->m_jumpHoldTime = 99999;
    player->m_jumpSpeed = 999;
    player->m_healthRegenTimer = 0;
    player->m_health = 999999;
}

bool Player::CanJump(){
    return true;
}

void Player::Chat(const char* msg){
    printf("Chat: %s\n", msg);
    std::string s = msg;
    if (s[0] == 't' && s[1] == 'p'){
        std::string loc = s.substr(2);
        std::vector<float> pos;
        while (loc[0] == ' ') {
            std::string num = "";
            int index = 1;
            while(loc[index] != ' ') {
                num += loc[index];
                index++;
                if (index >= loc.size()) {
                    break;
                }
            }
            pos.push_back(std::stof(num));
            loc = loc.substr(index);
            if (loc.size() == 0) {
                break;
            }
        }
        if (pos.size() == 3) {
            this->SetPosition({pos[0], pos[1], pos[2]});
        }
    }
    if (s.substr(0, 5) == "under") {
        flag = true;
        pos = this->GetPosition();
    }
    if (s.substr(0, 5) == "above") {
        flag = false;
        this->SetPosition(pos + Vector3(0, 0, 200));
    }

    if (s.substr(0, 3) == "egg") {
        if (s == "egg 10") {
            this->SetPosition(eggPos[9]);
        } else {
            int index = stoi(s.substr(4, 1));
            this->SetPosition(eggPos[index-1]);
        }
    }
}

// void World::Tick(float f) {
//     void* world = (dlsym(RTLD_NEXT, "GameWorld"));
//     printf("World %p\n",world);
// }