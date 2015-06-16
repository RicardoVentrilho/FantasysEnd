#include "map.h"
#include "Character/Player/player.h"
//Adicionar os metodos addObject e removeObject

const int Map::min_chest = 5;
const int Map::max_chest = 8;
const int Map::min_stone = 7;
const int Map::max_stone = 10;

Map::Map(string new_arch_map, string new_img_way)
{
    can_go = new bool[4];

    ifstream arch_map;

    img_way = new_img_way;

    int i, j;
    char buffercleaner;

    arch_map.open(new_arch_map.c_str());
    arch_map >> size_i >> size_j;

    arch_map >> buffercleaner;
    m_col = new int*[size_i];
    for (i = 0; i < size_i; i++){
        m_col[i] = new int[size_j];
        for (j = 0; j < size_j; j++) {
            arch_map >> m_col[i][j];
        }
    }
    arch_map >> buffercleaner;
    m_base = new int*[size_i];
    for (i = 0; i < size_i; i++){
        m_base[i] = new int[size_j];
        for (j = 0; j < size_j; j++) {
            arch_map >> m_base[i][j];
        }
    }
    arch_map >> buffercleaner;
    m_s_base = new int*[size_i];
    for (i = 0; i < size_i; i++){
        m_s_base[i] = new int[size_j];
        for (j = 0; j < size_j; j++) {
            arch_map >> m_s_base[i][j];
        }
    }
    arch_map >> buffercleaner;
    m_obj = new int*[size_i];
    for (i = 0; i < size_i; i++){
        m_obj[i] = new int[size_j];
        for (j = 0; j < size_j; j++) {
            arch_map >> m_obj[i][j];
        }
    }
    arch_map >> buffercleaner;
    m_iso = new int*[size_i];
    for (i = 0; i < size_i; i++){
        m_iso[i] = new int[size_j];
        for (j = 0; j < size_j; j++) {
            arch_map >> m_iso[i][j];
        }
    }
    arch_map >> buffercleaner;
    m_s_iso = new int*[size_i];
    for (i = 0; i < size_i; i++){
        m_s_iso[i] = new int[size_j];
        for (j = 0; j < size_j; j++) {
            arch_map >> m_s_iso[i][j];
        }
    }
    arch_map >> buffercleaner;
    arch_map.close();
     randMapInteration();

//    for (i = 0; i < size_i; i++){
//        for (j = 0; j < size_j; j++) {
//            cerr << m_col[i][j] << " ";
//        }
//        cerr << endl;
//    }

}

Map::~Map()
{

}

int **Map::getColision()
{
    return m_col;
}

int **Map::getBase()
{
    return m_base;
}

int **Map::getSuperBase()
{
    return m_s_base;
}

int **Map::getObjects()
{
    return m_obj;
}

int **Map::getIsometric()
{
    return m_iso;
}

int **Map::getSuperIsometric()
{
    return m_s_iso;
}

Object ***Map::getMatIteration()
{
    return m_interation;
}

string Map::getImgWay()
{
    return img_way;
}

Cordenates Map::getCordenates()
{
    return Cordenates(size_i, size_j);
}

bool Map::hasColision(Cordenates cord)
{
    return bool(m_col[cord.i][cord.j]);
}

bool *Map::getCanGo(Cordenates cord)
{
    can_go[UP] = can_go[DOWN] = can_go[RIGHT] = can_go[LEFT] = true;
    if (m_col[(cord + UP).i][(cord + UP).j]) can_go[UP] = false;
    if (m_col[(cord + DOWN).i][(cord + DOWN).j]) can_go[DOWN] = false;
    if (m_col[(cord + RIGHT).i][(cord + RIGHT).j]) can_go[RIGHT] = false;
    if (m_col[(cord + LEFT).i][(cord + LEFT).j]) can_go[LEFT] = false;
    return can_go;
}

void Map::updateColision(Character *update_character)
{
    Cordenates temp_cord = update_character->getCordenates();
    Direction temp_dir = update_character->getDirection();
    m_col[(temp_cord - temp_dir).i][(temp_cord - temp_dir).j] = 0;
    m_col[temp_cord.i][temp_cord.j] = 2;
}

void Map::setAColision(Cordenates new_col)
{
    m_col[new_col.i][new_col.j] = 2;
}
void Map::removeAColision(Cordenates remove_col)
{
    m_col[remove_col.i][remove_col.j] = 0;
}

void Map::randMapInteration()
{
    int qtd_chest, qtd_stone;
    int obj_pos_i, obj_pos_j, k;
    qtd_chest = (random((max_chest + 1) - min_chest) + min_chest);
    chest_list = new Chest*[qtd_chest];
    qtd_stone = (random((max_stone + 1) - min_chest) + min_stone);
    stone_list = new Stone*[qtd_stone];

    m_interation = new Object**[size_i];
    for (int i = 0; i < size_i; i++){
        m_interation[i] = new Object *[size_j];
    }
    //zerando matriz Interation
    for (int i = 0; i < size_i; i++){
        for (int j = 0; j < size_j; j++) {
            m_interation[i][j] = NULL;
        }
    }
    // Random Cordenates Chest
    k = 0;
    while ( k < qtd_chest ) {
        obj_pos_i = random(size_i);
        obj_pos_j = random(size_j);
        if(!m_col[obj_pos_i][obj_pos_j]) {
            setAColision(Cordenates(obj_pos_i,obj_pos_j));
            chest_list[k] = new Chest(obj_pos_i,obj_pos_j);
            m_interation[obj_pos_i][obj_pos_j] = chest_list[k];
            k++;
        }
    }

    //random Cordenates Stone
    k = 0;
    while ( k < qtd_stone ) {
        obj_pos_i = random(size_i);
        obj_pos_j = random(size_j);
        if(!m_col[obj_pos_i][obj_pos_j]) {
            setAColision(Cordenates(obj_pos_i,obj_pos_j));
            stone_list[k] = new Stone(obj_pos_i,obj_pos_j);
            m_interation[obj_pos_i][obj_pos_j] = stone_list[k];
            k++;
        }
    }

//    for (int i = 0; i < size_i; i++){
//        for (int j = 0; j < size_j; j++) {
//            cerr << m_col[i][j] << " ";
//        }
//        cerr << endl;
//    }

}

void Map::addObjects(Object * new_object, Cordenates cord_object)
{
    m_interation[cord_object.i][cord_object.j] = new_object;
}

void Map::removeObjects(Cordenates cord_remove)
{
    m_interation[cord_remove.i][cord_remove.j] = NULL;
}

Object *Map::getObjectMap(Cordenates cord)
{
    return m_interation[cord.i][cord.j];
}
