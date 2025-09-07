#ifndef GAMEDEF_H
#define GAMEDEF_H

#include <iostream>
#include <fstream>
#include <windows.h>
//назвать кодовую базу swallow
#include "map_and_keys.h"
#include "WPOINT.h"
#define MAK map_and_keys
using namespace std;

//#define GDEF_MORE_DIRECTIONS
#define DEBUGMODE
//#define GDEF_DIRECTION_MAX 3

typedef unsigned short int int_s;

typedef struct {
    char* gameName;
    char* company;
    std::string dir;
    int argc;
    char ** argv;
} gamedef_t;

class Transform {
public:
    int x,y = 0;

    Transform* operator+=(int i){
        this-> x += i;
        this-> y += i;
        return this;
    }

    Transform* operator=(int i){
        this-> x = i;
        this-> y = i;
        return this;
    }

    Transform() = default;
    Transform(int x,int y) { this->x = x; this->y =y; }

    void Addactive(int x, int y) {this->x+=x;this->y+=y;}
};

struct WH {
    int_s width;
    int_s height;
};

struct Sprite {
    WH original_sizes;
    double sizeModifi = 1.f;
    std::string path="";
};

struct Resists {
    int_s magic;
    int_s punches;
};

class Attributes {
public:
    int_s strong = 1;
    int_s intilligense = 1;
    int_s agility = 1;

    const bool operator==(Attributes at){
        return (strong==at.strong)&&(intilligense==at.intilligense)&&(agility==at.agility);
    }

    Attributes() = default;
    Attributes(int_s s, int_s i, int_s a) { this->strong=s; this->agility=a; this->intilligense=i; };
};

enum RACES             { HUMAN = 0, ELF = 1, ORC = 2, DARKELF = 3, KAJIT = 4, VAMPIRE = 5 };
#define GDEF_FAIL_ATTRIBUTE Attributes(-1,-1,-1)
struct RaceAttributs {  // 18
    const static inline vector<Attributes> human =      {Attributes(10,10,10), Attributes(6,6,6)};
    const static inline vector<Attributes> elf =        {Attributes(5,12,15), Attributes(3,8,7)};
    const static inline vector<Attributes> orc =        {Attributes(15,5,9), Attributes(8,1,9)};
    const static inline vector<Attributes> darkelf =    {Attributes(5,12,15), Attributes(3,6,9)};
    const static inline vector<Attributes> kajit =      {Attributes(5,12,15), Attributes(3,8,7)};
    const static inline vector<Attributes> vampire =    {Attributes(20,15,20), Attributes(8,8,8)};
};

static int GetRaceOnName(string r) {
    if (r=="human") {
        return RACES::HUMAN;
    } else if(r=="elf") {
        return RACES::ELF;
    } else if(r=="orc") {
        return RACES::ORC;
    } else if(r=="darkelf") {
        return RACES::DARKELF;
    } else if(r=="kajit") {
        return RACES::KAJIT;
    }
    return -1;
}
#define GDEF_FAIL_RACE "null"
static string GetRaceNameOnInt(int r) {
    switch(r) {
        case RACES::HUMAN: return "human";
        case RACES::ELF: return "elf";
        case RACES::ORC: return "orc";
        case RACES::DARKELF: return "darkelf";
        case RACES::KAJIT: return "kajit";
    }
    return GDEF_FAIL_RACE;
}

/// o - first - original, 1 - second - addactive
static Attributes GetAttributesOnRace(int race,int choice=0) {
    switch(race) {
        case RACES::HUMAN :
            return RaceAttributs::human[choice];
        case RACES::ELF:
            return RaceAttributs::elf[choice];
    }
    return GDEF_FAIL_ATTRIBUTE;
}

struct Fraction {
    string name;
    int_s globalRep;
    int_s favoriteRace;
};

class Reputation {
protected:
    vector<Fraction> *list;
    //MAK<string, int> fractions;
public:
    bool AddFraction(string,int);
    int GetRep(string);
    bool Remove(string);
};

class Levle {
protected:
    int max;
    int_s levle;
    int_s currentPoints;
    int_s needPoints;
public:
    /// true if levle is up
    bool AddPoints(int add) {

        return false;
    }
    bool Up(){
        if (levle+1 <= max || max == -1) {levle+=1;}
        else {return false;}
        currentPoints=0;
        needPoints = ((levle * 18) ) / ((levle+1)/1.2f);needPoints+=sqrt(needPoints)+levle/2+1;
        return true;
    };
    int_s GetCPoints() {return currentPoints;}
    int_s GetNPoints() {return needPoints;}
    int_s GetLevle(){return levle;};
    /// MAX = -1 -> infinite levle up
    Levle(int max=-1, int lvl=1){this->max=max;this->levle=lvl-1;Up();}
};

static string GetRandomName() {
    ofstream file;file.open("names.txt");
    if (!file.is_open()) {return "";}
    //auto d = file.getline();
    file.close();
    return "";
}

//================================================================================

/// ___________
/// | lf f rf |
/// | l     r |
/// | lb b rb |
/// |_________|
#ifndef GDEF_MORE_DIRECTIONS
#define GDEF_DIRECTION_MAX 3
enum PERSON_DIRECTIONS  { FRONT = 0, RIGHT = 1, BACKWARD = 2, LEFT = 3 };
#endif
#ifdef GDEF_MORE_DIRECTIONS
#define GDEF_DIRECTION_MAX 7
enum PERSON_DIRECTIONS  { FRONT = 0, RIGHT_FRONT = 1, RIGHT = 2, RIGHT_BACKWARD = 3, BACKWARD = 4, LEFT_BACKWARD = 5, LEFT = 6, LEFT_FRONT = 7 };
#endif
#include "entity_person.h"
#define GDEF_MAP_PLAYER 'P'
#define GDEF_MAP_WALL '#'
#define GDEF_MAP_EMPTY '-'
#define GDEF_MAP_EMPTY_EYE '*'
class MAP_POINT {
public:
    char _char;
    POINT coord;
    entity_person* entity;
    bool lock() {return entity;}
    bool operator==(char l) {
        return this->_char==l;
    }
    char operator=(char l) {
        this->_char = l;return _char;
    }
};
template <int_s x, int_s y>
struct MAP {
public:
    WPOINT GetCoofs() {
        WPOINT coof(0,0);
        switch(*plDirection) {
            case PERSON_DIRECTIONS::FRONT : {
                coof.x = -1;
                coof.y = 0 ;
                break;
            }
            case PERSON_DIRECTIONS::BACKWARD : {
                coof.x = 1;
                coof.y = 0;
                break;
            }
            case PERSON_DIRECTIONS::LEFT : {
                coof.x = 0;
                coof.y = -1;
                break;
            }
            case PERSON_DIRECTIONS::RIGHT : {
                coof.x = 0;
                coof.y = 1;
                break;
            }
#ifdef GDEF_MORE_DIRECTIONS
            case PERSON_DIRECTIONS::LEFT_FRONT : {
                coof.x = -1;
                coof.y = -1;
                break;
            }
            case PERSON_DIRECTIONS::LEFT_BACKWARD : {
                coof.x = 1;
                coof.y = -1;
                break;
            }
            case PERSON_DIRECTIONS::RIGHT_FRONT : {
                coof.x = -1;
                coof.y = 1;
                break;
            }
            case PERSON_DIRECTIONS::RIGHT_BACKWARD : {
                coof.x = 1;
                coof.y = 1;
                break;
            }
#endif
        }
        return coof;
    }

public:
    MAP_POINT* map[x][y] = new MAP_POINT[x][y]();
    POINT GetPlayerPos(){
        POINT pl; pl.x=-1;pl.y=-1;
        for (int i =0; i<x;i++) {
            for (int j =0;j<y;j++) {
                if (map[i][j]._char == GDEF_MAP_PLAYER) {pl.x=i;pl.y=j;return pl;}
            }
        }
        cout<<"[MAP GetPlayerPos] ERR? player not found."<<endl;
        return pl;
    }
    void print() {
        for (int i =0; i<x;i++) {
            for (int j =0;j<y;j++) {
                cout<<map[i][j]._char;
            }
            cout<<endl;
        }
    }
    int *plDirection;
    void Fill(char letter) {
        for (int i =0;i<x;i++) {
            for (int j = 0; j< y;j++) {
                map[i][j]._char=letter;
            }
        }
    }
    bool Move(bool forward=true) {
        WPOINT coof = GetCoofs();
        coof *= !forward ? -1 : 1;
        POINT pl = GetPlayerPos();
        if ( pl.x+coof.x >= x || pl.x+coof.x < 0 || pl.y+coof.y >= y || pl.y+coof.y < 0 || map[pl.x + coof.x][pl.y + coof.y]._char == GDEF_MAP_WALL ) { cout<<"q"<<endl;return false; }
        map[pl.x][pl.y]._char = map[pl.x + coof.x][pl.y + coof.y]._char;
        map[pl.x + coof.x][pl.y + coof.y]._char = GDEF_MAP_PLAYER;
        print();
        return true;
    }
    char GetCharOnMap(int x, int y) {
        return map[x][y]._char;
    }

    template <int distance>
    vector<char[3]> GetNextChar() {
        vector<char[3]> matrix = vector<char[3]>(distance);
        WPOINT pl = GetPlayerPos();
        POINT delta = GetCoofs();
        //cout<<endl;cout<<endl;
        for (int j = 0; j <distance; j++) {
            for (int i = 0; i < 3; i++) {
                int xn,yn;
                if (*plDirection==PERSON_DIRECTIONS::LEFT || *plDirection==PERSON_DIRECTIONS::RIGHT)
                {
                    xn = pl.x + delta.x -(1*delta.y)+i*delta.y;
                    yn = pl.y + delta.y + ( ((distance-1)-j) *(delta.y));
                }
                else if (*plDirection==PERSON_DIRECTIONS::BACKWARD || *plDirection==PERSON_DIRECTIONS::FRONT)
                {
                    xn = pl.x + delta.x - (((distance-1)-j)*(-1*delta.x));
                    yn = pl.y + delta.y-1+i;
                }

                matrix[j][i] = map[xn][yn]._char;
                if (xn < 0 || yn < 0 || xn >= x || yn >= y) {
                    matrix[j][i] = ' ';
                }
                //cout<< matrix[j][i];
            }
            //cout<<endl;
        }
        return matrix;
    }

public:
    MAP<x,y>(int* playerDirection) {
        this->plDirection=playerDirection;
    }
};
#include <random>
static random_device rd;
static mt19937 eng(rd());
static  uniform_int_distribution<int> r(0, 10);
template<int mn, int mx>
static float random() { return r(eng); }
template <int x, int y>
static void GenerateMap(MAP_POINT** map) {
    bool pl=false;
    for (int i = 0; i<x;i++) {
        for (int j =0;j<y;j++) {
            map[x][y]._char = (random<1,10>()<4?GDEF_MAP_WALL:GDEF_MAP_EMPTY);
            map[x][y]._char =(j==0 ? GDEF_MAP_WALL: j==y-1? GDEF_MAP_WALL : x==0? GDEF_MAP_WALL: i==0?GDEF_MAP_WALL:i==x-1?GDEF_MAP_WALL:map[x][y]._char);
            if (map[x][y]._char == GDEF_MAP_EMPTY && !pl) {
                map[x][y]._char = GDEF_MAP_PLAYER;
                pl=true;
            }
        }
    }
}
//=============================================================================================

#define GDEF_GDEFPOINT_STATE_TOP 't'
#define GDEF_GDEFPOINT_STATE_BOTTOM 'b'
#define GDEF_GDEFPOINT_STATE_NONE 'n'
class GDEFPOINT {
public:
    float x,y;
    /// t - top, b - bottom, n - nahui
    char state;
    GDEFPOINT()=default;
    GDEFPOINT(float x,float y, char state=GDEF_GDEFPOINT_STATE_NONE){this->x=x;this->y=y;this->state=state;}
};

class GDEFCOLOR {
private:
    float*color;
public:
    GDEFCOLOR(float r,float g,float b) { this->color = new float[3]{r,g,b};}
    GDEFCOLOR(float*c) { this->color = c;}
    float* GetPColor(){ return color; };
    float r() {return color[0];}
    float g() {return color[1];}
    float b() {return color[2];}
    void CopyTo(float* c) {c[0]=color[0];c[1]=color[1];c[2]=color[2];}
    void CopyIn(float* c) {color[0]=c[0];color[1]=c[1];color[2]=c[2];}
    float*operator+=(float d){ for (auto i = 0; i < 3;i++) {color[i] += d;};return color; }
};

#define GDEF_VK_W 0x57
#define GDEF_VK_A 0x41
#define GDEF_VK_D 0x44
#define GDEF_VK_S 0x53
#define GDEF_VK_J 0x4A
#define GDEF_VK_K 0x4B
static bool GetKeyActive(int virtualKey) {
    static bool press=false;static int time;
    if (!press) {time++;}
    if (time%30==0) {
        press = true;
    }
    if (press && GetKeyState(virtualKey)&0x8000) {
        press=false;
        return true;
    }
    return false;
}

enum PERSON_STATES      { DEAD = 0, STABLE = 1, STUNNED = 2, BLIND = 3, CUTSCENE = 4 };
enum DAMAGE_TYPES       { CLEAN = 0, FIRE = 1, BLUEFOXFIRE = 2, NECROS = 3, COLD = 4, BLOOD = 5  };
enum OBJ_TYPES          { KEY = 0 };
enum CATEGORY_TYPES     { WARRIOR = 0 };
enum EQUIPMENT_TYPES    { FLAT = 0, ARMORE_SLOT_HEAD = 1, ARMORE_SLOT_BODY = 2, ARMORE_SLOT_ARMS = 3, ARMORE_SLOT_LEGS = 4, WEAPON_LEFT = 5, WEAPON_RIGHT = 6 };
enum OBJ_RARITY_TYPES   { COMMON = 0, UNCOMMON = 1,RARITY = 2, LEGEND=3, MYTHIC=4};

#endif