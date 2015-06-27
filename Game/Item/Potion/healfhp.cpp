#include "healfhp.h"

const int HealfHP::hp_heal = 100; //Multiplicador de pontos de cura de HP (HEALTH POINTS)
std::string HealfHP::healfhp_img_way = "Inventory/Items/healhp.png";

HealfHP::HealfHP() : Potion(healfhp_img_way, "HP", 0)
{

}

HealfHP::~HealfHP()
{

}

void HealfHP::doEffect(Player &player)
{
    player.addHP(hp_heal * item_level);
}

void HealfHP::setImgWay(std::string new_img_way)
{
    healfhp_img_way = new_img_way;
}

