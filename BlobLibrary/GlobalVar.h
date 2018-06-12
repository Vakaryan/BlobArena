#pragma once
//Global variables for the game
//Could be used by ImGui



static float COEFF_DEF = 0.5; //multiplicative coefficient in case of defending 
static float COEFF_MAG = 0.5; //multiplicative magic coefficient when using skill : dmg_made = dmg_skill *  coef_mag / defending : def = dmg_made * (1 +- coef_mag)
static float COEFF_LVLUP = 1; //additive coefficient when levelling up::l
static int RED = 0;
static int GREEN = 1;
static int BLUE = 2;
static int PHYS = 3;
static int ARMOR = 0;
static int WEAPON = 1;
static int ACCESSORY = 2;
//basic values for lvl1 blob (may change when balancing)
static int BASE_ATK = 4;
static int BASE_DEF = 2;
static int BASE_HP = 7;
static int BASE_EP = 7;
static int BASE_MAG = 2;
static float BASE_SIZE = 100;


static int B_HP = 0;
static int B_MAXHP = 1;
static int B_EP = 2;
static int B_MAXEP = 3;
static int B_ATK = 4;
static int B_DEF = 5;
static int B_LVL = 6;

static int TIER3_CORPSE = 200;
static int TIER2_CORPSE = 550;
static int TIER1_CORPSE = 850;