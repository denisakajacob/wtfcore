/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "icecrown_citadel.h"

#define MAX_ENCOUNTER      12

const Position SpawnLoc[]=
{
    {4571.521f, 2481.815f, 343.365f, 3.166f} //spawn pos
};
static const DoorData doorData[] =
{
    {GO_LORD_MARROWGAR_S_ENTRANCE,           DATA_MARROWGAR_EVENT,             DOOR_TYPE_ROOM,    BOUNDARY_N   },
    {GO_ICEWALL,                             DATA_MARROWGAR_EVENT,             DOOR_TYPE_PASSAGE, BOUNDARY_NONE},
    {GO_DOODAD_ICECROWN_ICEWALL02,           DATA_MARROWGAR_EVENT,             DOOR_TYPE_PASSAGE, BOUNDARY_NONE},
    {GO_ORATORY_OF_THE_DAMNED_ENTRANCE,      DATA_DEATHWHISPER_EVENT,          DOOR_TYPE_ROOM,    BOUNDARY_N   },
    {GO_ORANGE_PLAGUE_MONSTER_ENTRANCE,      DATA_FESTERGUT_EVENT,             DOOR_TYPE_ROOM,    BOUNDARY_E   },
    {GO_GREEN_PLAGUE_MONSTER_ENTRANCE,       DATA_ROTFACE_EVENT,               DOOR_TYPE_ROOM,    BOUNDARY_E   },
    {GO_SCIENTIST_ENTRANCE,                  DATA_PROFESSOR_PUTRICIDE_EVENT,   DOOR_TYPE_ROOM,    BOUNDARY_E   },
    {GO_CRIMSON_HALL_DOOR,                   DATA_BLOOD_PRINCE_COUNCIL_EVENT,  DOOR_TYPE_ROOM,    BOUNDARY_S   },
    {GO_BLOOD_ELF_COUNCIL_DOOR,              DATA_BLOOD_PRINCE_COUNCIL_EVENT,  DOOR_TYPE_PASSAGE, BOUNDARY_W   },
    {GO_BLOOD_ELF_COUNCIL_DOOR_RIGHT,        DATA_BLOOD_PRINCE_COUNCIL_EVENT,  DOOR_TYPE_PASSAGE, BOUNDARY_E   },
    {GO_DOODAD_ICECROWN_BLOODPRINCE_DOOR_01, DATA_BLOOD_QUEEN_LANA_THEL_EVENT, DOOR_TYPE_ROOM,    BOUNDARY_S   },
    {GO_DOODAD_ICECROWN_GRATE_01,            DATA_BLOOD_QUEEN_LANA_THEL_EVENT, DOOR_TYPE_PASSAGE, BOUNDARY_NONE},
    {GO_GREEN_DRAGON_BOSS_ENTRANCE,          DATA_VALITHRIA_DREAMWALKER_EVENT, DOOR_TYPE_ROOM,    BOUNDARY_N   },
    {GO_GREEN_DRAGON_BOSS_EXIT,              DATA_VALITHRIA_DREAMWALKER_EVENT, DOOR_TYPE_PASSAGE, BOUNDARY_S   },
    {GO_SINDRAGOSA_ENTRANCE_DOOR,            DATA_SINDRAGOSA_EVENT,            DOOR_TYPE_ROOM,    BOUNDARY_S   },
    {GO_SINDRAGOSA_SHORTCUT_ENTRANCE_DOOR,   DATA_SINDRAGOSA_EVENT,            DOOR_TYPE_PASSAGE, BOUNDARY_E   },
    {GO_SINDRAGOSA_SHORTCUT_EXIT_DOOR,       DATA_SINDRAGOSA_EVENT,            DOOR_TYPE_PASSAGE, BOUNDARY_NONE},
    {GO_ICE_WALL,                            DATA_SINDRAGOSA,                  DOOR_TYPE_ROOM,    BOUNDARY_SE  }, 
    {GO_ICE_WALL,                            DATA_SINDRAGOSA,                  DOOR_TYPE_ROOM,    BOUNDARY_SW  }, 
    {0,                                      0,                                DOOR_TYPE_ROOM,    BOUNDARY_NONE} // END
};
class instance_icecrown_citadel : public InstanceMapScript
{
    public:
        instance_icecrown_citadel() : InstanceMapScript("instance_icecrown_citadel", 631) { }

        struct instance_icecrown_citadel_InstanceMapScript : public InstanceScript
        {
            instance_icecrown_citadel_InstanceMapScript(InstanceMap* pMap) : InstanceScript(pMap)
            {
                LoadDoorData(doorData);
                uiDifficulty = pMap->GetDifficulty();

                uiLordMarrowgar         = 0;
                uiGunship               = 0;
                uiDeathbringerSaurfang  = 0;
                uiFestergut             = 0;
                uiRotface               = 0;
                uiProfessorPutricide    = 0;
                uiPrinceValanar         = 0;
                uiPrinceKeleseth        = 0;
                uiPrinceTaldaram        = 0;
                uiBloodQueenLanathel    = 0;
                uiValithriaDreamwalker  = 0;
                uiValithriaAlternative  = 0;
                uiValithriaCombatTrigger= 0;
                uiLichKing              = 0;
                uiTirion                = 0;
                uiSaurfangCache         = 0;

                uiAngle                 = 0;
                uiSpawn                 = 0;
                uiAllYouCanEat          = 0;
                uiNecroticStack         = 0;
                uiBloodCouncilController = 0;
                uiBeenWaiting           = 0;
                uiNeckDeep              = 0;
                uiIceWall1              = 0;
                uiIceWall2              = 0;
                uiMarrowgarEntrance     = 0;
                uiLadyDeathwisperTransporter = 0;
                uiOratoryDoor           = 0;
                uiSaurfangDoor          = 0;
                uiOrangeMonsterDoor     = 0;
                uiGreenMonsterDoor      = 0;
                uiProfCollisionDoor     = 0;
                uiPutricideTable        = 0;
                uiOrangePipe            = 0;
                uiGreenPipe             = 0;
                uiOozeValve             = 0;
                uiGasValve              = 0;
                uiProfDoorOrange        = 0;
                uiProfDoorGreen         = 0;
                uiRotfaceEntrance       = 0;
                uiFestergurtEntrance    = 0;
                uiProffesorDoor         = 0;
                uiBloodwingDoor         = 0;
                uiCrimsonHallDoor1      = 0;
                uiCrimsonHallDoor2      = 0;
                uiCrimsonHallDoor3      = 0;
                uiBloodQueenTransporter = 0;
                uiFrostwingDoor         = 0;
                uiDragonDoor1           = 0;
                uiDragonDoor2           = 0;
                uiDragonDoor3           = 0;
                uiRoostDoor1            = 0;
                uiRoostDoor2            = 0;
                uiRoostDoor3            = 0;
                uiRoostDoor4            = 0;
                uiValithriaTransporter  = 0;
                uiSindragosaTransporter= 0;
                uiSindragosaDoor1       = 0;
                uiSindragosaDoor2       = 0;
                uiSindragosaIceWall     = 0;
                uiFirstTp               = 0;
                uiMarrowgarTp           = 0;
                uiFlightWarTp           = 0;
                uiSaurfangTp            = 0;
                uiCitadelTp             = 0;
                uiSindragosaTp         = 0;
                uiLichTp                = 0;

                uiSpiritAlarm1          = 0;
                uiSpiritAlarm2          = 0;
                uiSpiritAlarm3          = 0;
                uiSpiritAlarm4          = 0;

                uiDeathboundWard1       = 0;
                uiDeathboundWard2       = 0;
                uiDeathboundWard3       = 0;
                uiDeathboundWard4       = 0;

                sindragosa              = 0; 
                spinestalker            = 0; 
                rimefang                = 0; 
                frostwyrms              = 0; 
                spinestalkerTrash       = 0; 
                rimefangTrash           = 0; 

                isBonedEligible         = true;
                isOozeDanceEligible     = true;
                isNauseaEligible        = 0;
                isOrbWhispererEligible  = 0;
                isPortalJockeyEligible  = 0;

                memset(&uiEncounter, 0, sizeof(uiEncounter));
                //While Gunship Battle is not implemented
                uiEncounter[DATA_GUNSHIP_BATTLE_EVENT] = DONE;
            };

            bool IsEncounterInProgress() const
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    if (uiEncounter[i] == IN_PROGRESS)
                        return true;
                }

                return false;
            }

            void OnCreatureCreate(Creature* creature)
            {
                Map::PlayerList const &players = instance->GetPlayers();
                uint32 TeamInInstance = 0;


                if (!players.isEmpty())
                {
                    if (Player* pPlayer = players.begin()->getSource())
                        TeamInInstance = pPlayer->GetTeam();
                }
                switch(creature->GetEntry())
                {
                    case CREATURE_OOZE_COVERED_TENTACLE_STALKER:
                    case CREATURE_SLIMY_TENTACLE_STALKER:
                    case CREATURE_ORANGE_GAS_STALKER:
                    case CREATURE_TEAR_GAS_STALKER:
                        creature->SetReactState(REACT_PASSIVE);
                        break;
                    case CREATURE_KOR_KRON_GENERAL:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_ALLIANCE_COMMANDER, ALLIANCE);
                        break;
                    case CREATURE_TORTUNOK:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_ALANA_MOONSTRIKE, ALLIANCE);
                        break;
                    case CREATURE_GERARDO_THE_SUAVE:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_TALAN_MOONSTRIKE, ALLIANCE);
                        break;
                    case CREATURE_UVLUS_BANEFIRE:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_MALFUS_GRIMFROST, ALLIANCE);
                        break;
                    case CREATURE_IKFIRUS_THE_VILE:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_YILI, ALLIANCE);
                        break;
                    case CREATURE_VOL_GUK:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_JEDEBIA, ALLIANCE);
                        break;
                    case CREATURE_HARAGG_THE_UNSEEN:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_NIBY_THE_ALMIGHTY, ALLIANCE);
                        break;
                    case CREATURE_GARROSH_HELLSCREAM:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_KING_VARIAN_WRYNN, ALLIANCE);
                        break;
                    case CREATURE_SE_HIGH_OVERLORD_SAURFANG:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_SE_MURADIN_BRONZEBEARD, ALLIANCE);
                         break;
                    case CREATURE_SE_KOR_KRON_REAVER:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(CREATURE_SE_SKYBREAKER_MARINE, ALLIANCE);
                        break;
                    case NPC_LORD_MARROWGAR:
                        uiLordMarrowgar = creature->GetGUID();
                        //Lord Marrowgar has lard hitbox
                        creature->SetFloatValue(UNIT_FIELD_COMBATREACH, 10.0f);
                        break;
                    case CREATURE_GUNSHIP:
                        uiGunship = creature->GetGUID();
                        break;
                    case CREATURE_SAURFANG:
                        uiDeathbringerSaurfang = creature->GetGUID();
                        break;
                    case CREATURE_FESTERGUT:
                        uiFestergut = creature->GetGUID();
                        break;
                    case CREATURE_ROTFACE:
                        uiRotface = creature->GetGUID();
                        break;
                    case CREATURE_PROFESSOR_PUTRICIDE:
                        uiProfessorPutricide = creature->GetGUID();
                        break;
                    case CREATURE_PRINCE_VALANAR_ICC:
                        uiPrinceValanar = creature->GetGUID();
                        creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                        break;
                    case CREATURE_PRINCE_KELESETH_ICC:
                        uiPrinceKeleseth = creature->GetGUID();
                        creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                        break;
                    case CREATURE_PRINCE_TALDARAM_ICC:
                        uiPrinceTaldaram = creature->GetGUID();
                        creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                        break;
                    case CREATURE_BLOOD_ORB_CONTROLLER:
                        uiBloodCouncilController = creature->GetGUID();
                        break;
                    case CREATURE_BLOOD_QUEEN_LANA_THEL:
                        uiBloodQueenLanathel = creature->GetGUID();
                        creature->SetReactState(REACT_DEFENSIVE);
                        break;
                    case CREATURE_VALITHRIA_DREAMWALKER:
                        uiValithriaDreamwalker = creature->GetGUID();
                        break;
                    case CREATURE_VALITHRIA_ALTERNATIVE:
                        uiValithriaAlternative = creature->GetGUID();
                        break;
                    case CREATURE_COMBAT_TRIGGER:
                    {
                        uiValithriaCombatTrigger = creature->GetGUID();
                        creature->SetReactState(REACT_AGGRESSIVE);
                        creature->SetSpeed(MOVE_RUN, 0.0f, true);
                        creature->SetSpeed(MOVE_WALK, 0.0f, true);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
                        creature->SetVisible(false);
                        break;
                    }
                    case NPC_SINDRAGOSA: 
                        sindragosa = creature->GetGUID(); 
                        break; 
                    case NPC_SPINESTALKER: 
                        spinestalker = creature->GetGUID(); 
                        if (!creature->isDead()) 
                            ++frostwyrms; 
                        break; 
                    case NPC_RIMEFANG: 
                        rimefang = creature->GetGUID(); 
                        if (!creature->isDead()) 
                            ++frostwyrms; 
                        break;
                    case NPC_DEATHBOUND_WARD:
                    {
                        float x, y;
                        creature->GetPosition(x, y);
                        if      (fabs(x - (-193.786f)) < 10.0f && fabs(y - 2290.22f) < 10.0f)
                            uiDeathboundWard1 = creature->GetGUID();
                        else if (fabs(x - (-194.007f)) < 10.0f && fabs(y - 2137.95f) < 10.0f)
                            uiDeathboundWard2 = creature->GetGUID();
                        else if (fabs(x - (-300.354f)) < 10.0f && fabs(y - 2242.18f) < 10.0f)
                            uiDeathboundWard3 = creature->GetGUID();
                        else if (fabs(x - (-300.566f)) < 10.0f && fabs(y - 2182.60f) < 10.0f)
                            uiDeathboundWard4 = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        break;
                    }
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                if (go)
                {
                    Position pos;
                    go->GetPosition(&pos);
                    gameObjectPositions[go->GetGUID()] = pos;
                }
                switch (go->GetEntry())
                {
                    case LORD_ICE_WALL_1:
                        uiIceWall1 = go->GetGUID();
                        HandleGameObject(NULL, uiEncounter[DATA_MARROWGAR_EVENT] == DONE, go);
                        break;
                    case LORD_ICE_WALL_2:
                        uiIceWall2 = go->GetGUID();
                        HandleGameObject(NULL, uiEncounter[DATA_MARROWGAR_EVENT] == DONE, go);
                        break;
                    case LORD_ENTRANCE:
                        uiMarrowgarEntrance = go->GetGUID();
                        break;
                    case ORATORY_ENTRANCE:
                        uiOratoryDoor = go->GetGUID();
                        break;
                    case SAURFANG_DOOR:
                        uiSaurfangDoor = go->GetGUID();
                        HandleGameObject(NULL, uiEncounter[DATA_SAURFANG_EVENT] == DONE, go);
                        break;
                    case BLOODWING_DOOR:
                        uiBloodwingDoor = go->GetGUID();
                        break;
                    case FROSTWING_DOOR:
                        uiFrostwingDoor = go->GetGUID();
                        break;
                    case CRIMSONHALL_DOOR:
                        uiCrimsonHallDoor1 = go->GetGUID();
                        HandleGameObject(uiCrimsonHallDoor1, uiEncounter[DATA_BLOOD_PRINCE_COUNCIL_EVENT] != IN_PROGRESS);
                        break;
                    case CRIMSONHALL_DOOR_1:
                        uiCrimsonHallDoor2 = go->GetGUID();
                        HandleGameObject(uiCrimsonHallDoor2, uiEncounter[DATA_BLOOD_PRINCE_COUNCIL_EVENT] == DONE);
                        break;
                    case CRIMSONHALL_DOOR_2:
                        uiCrimsonHallDoor3 = go->GetGUID();
                        HandleGameObject(uiCrimsonHallDoor3, uiEncounter[DATA_BLOOD_PRINCE_COUNCIL_EVENT] == DONE);
                        break;
                    case DRAGON_DOOR_1:
                        uiDragonDoor1 = go->GetGUID();
                        break;
                    case DRAGON_DOOR_2:
                        uiDragonDoor2 = go->GetGUID();
                        break;
                    case DRAGON_DOOR_3:
                        uiDragonDoor3 = go->GetGUID();
                        break;
                    case DREAMWALKER_DOOR_1:
                        uiRoostDoor1 = go->GetGUID();
                        break;
                    case DREAMWALKER_DOOR_2:
                        uiRoostDoor2 = go->GetGUID();
                        break;
                    case DREAMWALKER_DOOR_3:
                        uiRoostDoor3 = go->GetGUID();
                        break;
                    case DREAMWALKER_DOOR_4:
                        uiRoostDoor4 = go->GetGUID();
                        break;
                    case SINDRAGOSA_DOOR_1:
                        uiSindragosaDoor1 = go->GetGUID();
                        break;
                    case SINDRAGOSA_DOOR_2:
                        uiSindragosaDoor2 = go->GetGUID();
                        break;
                    case GO_SINDRAGOSA_ICE_WALL:
                    case GO_ICE_WALL:
                        uiSindragosaIceWall = go->GetGUID();
                        break;
                    case PROF_COLLISION_DOOR:
                        uiProfCollisionDoor = go->GetGUID();
                        if (uiEncounter[DATA_FESTERGUT_EVENT] == DONE && uiEncounter[DATA_ROTFACE_EVENT] == DONE)
                            HandleGameObject(uiProfCollisionDoor, true, go);
                        break;
                    case PROF_DOOR_ORANGE:
                        uiProfDoorOrange = go->GetGUID();
                        if (uiEncounter[DATA_FESTERGUT_EVENT] == DONE && uiEncounter[DATA_ROTFACE_EVENT] == DONE)
                            go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                        else if (uiEncounter[DATA_FESTERGUT_EVENT] == DONE)
                            HandleGameObject(uiProfDoorOrange, false, go);
                        else
                            HandleGameObject(uiProfDoorOrange, true, go);
                        break;
                    case PROF_DOOR_GREEN:
                        uiProfDoorGreen = go->GetGUID();
                        if (uiEncounter[DATA_FESTERGUT_EVENT] == DONE && uiEncounter[DATA_ROTFACE_EVENT] == DONE)
                            go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                        else if (uiEncounter[DATA_ROTFACE_EVENT] == DONE)
                            HandleGameObject(uiProfDoorGreen, true, go);
                        else
                            HandleGameObject(uiProfDoorGreen, false, go);
                        break;
                    case ORANGE_PIPE:
                        uiOrangePipe = go->GetGUID();
                        if (uiEncounter[DATA_FESTERGUT_EVENT] == DONE)
                            HandleGameObject(uiOrangePipe, true, go);
                        break;
                    case GREEN_PIPE:
                        uiGreenPipe = go->GetGUID();
                        if (uiEncounter[DATA_ROTFACE_EVENT] == DONE)
                            HandleGameObject(uiGreenPipe, true, go);
                        break;
                    case OOZE_VALVE:
                        uiOozeValve = go->GetGUID();
                        if (uiEncounter[DATA_ROTFACE_EVENT] == DONE)
                            HandleGameObject(NULL, true, go);
                        break;
                    case GAS_VALVE:
                        uiGasValve = go->GetGUID();
                        if (uiEncounter[DATA_FESTERGUT_EVENT] == DONE)
                            HandleGameObject(NULL, true, go);
                        break;
                    case ROTFACE_DOOR:
                        uiGreenMonsterDoor = go->GetGUID();
                        if (uiEncounter[DATA_ROTFACE_EVENT] == DONE)
                            HandleGameObject(NULL, true, go);
                        break;
                    case FESTERGUT_DOOR:
                        uiOrangeMonsterDoor = go->GetGUID();
                        if (uiEncounter[DATA_FESTERGUT_EVENT] == DONE)
                            HandleGameObject(NULL, true, go);
                        break;
                    case PROFESSOR_DOOR:
                        uiProffesorDoor = go->GetGUID();
                        if (uiEncounter[DATA_PROFESSOR_PUTRICIDE_EVENT] == DONE)
                            HandleGameObject(NULL, true, go);
                        break;
                    case DRINK_ME:
                        uiPutricideTable = go->GetGUID();
                        break;
                    case SAURFANG_CACHE_10_N:
                    case SAURFANG_CACHE_25_N:
                    case SAURFANG_CACHE_10_H:
                    case SAURFANG_CACHE_25_H:
                        uiSaurfangCache = go->GetGUID();
                        break;
                    case DREAMWALKER_CACHE_10_N:
                    case DREAMWALKER_CACHE_25_N:
                    case DREAMWALKER_CACHE_10_H:
                    case DREAMWALKER_CACHE_25_H:
                        uiDreamwalkerCache = go->GetGUID();
                        break;
                    case LADY_ELEVATOR:
                        uiLadyDeathwisperTransporter = go->GetGUID();
                        break;
                    case BLOODQUEEN_ELEVATOR:
                        uiBloodQueenTransporter = go->GetGUID();
                        break;
                    case VALITHRIA_ELEVATOR:
                        uiValithriaTransporter = go->GetGUID();
                        break;
                    case SINDRAGOSA_ELEVATOR:
                        uiSindragosaTransporter = go->GetGUID();
                        break;
                    case FIRST_TELEPORT:
                        uiFirstTp = go->GetGUID();
                        MakeObjectClickable(go, uiEncounter[DATA_MARROWGAR_EVENT] == DONE);
                        go->SetGoState(uiEncounter[DATA_MARROWGAR_EVENT] == DONE ? GO_STATE_ACTIVE : GO_STATE_READY);
                        break;
                    case LORD_TELEPORT:
                        uiMarrowgarTp = go->GetGUID();
                        MakeObjectClickable(go, uiEncounter[DATA_MARROWGAR_EVENT] == DONE);
                        go->SetGoState(uiEncounter[DATA_MARROWGAR_EVENT] == DONE ? GO_STATE_ACTIVE : GO_STATE_READY);
                        break;
                    case GUNSHIP_TELEPORT:
                        uiFlightWarTp = go->GetGUID();
                        MakeObjectClickable(go, uiEncounter[DATA_DEATHWHISPER_EVENT] == DONE);
                        go->SetGoState(uiEncounter[DATA_DEATHWHISPER_EVENT] == DONE ? GO_STATE_ACTIVE : GO_STATE_READY);
                        break;
                    case SAURFANG_TELEPORT:
                        uiSaurfangTp = go->GetGUID();
                        MakeObjectClickable(go, uiEncounter[DATA_DEATHWHISPER_EVENT] == DONE);
                        go->SetGoState(uiEncounter[DATA_DEATHWHISPER_EVENT] == DONE ? GO_STATE_ACTIVE : GO_STATE_READY);
                        break;
                    case CITADEL_TELEPORT:
                        uiCitadelTp = go->GetGUID();
                        MakeObjectClickable(go, uiEncounter[DATA_SAURFANG_EVENT] == DONE);
                        HandleGameObject(NULL, false, go);
                        break;
                    case SINDRAGOSA_TELEPORT:
                        uiSindragosaTp = go->GetGUID();
                        MakeObjectClickable(go, uiEncounter[DATA_VALITHRIA_DREAMWALKER_EVENT] == DONE);
                        HandleGameObject(NULL, false, go);
                        break;
                    case LICH_TELEPORT:
                    {
                        uiLichTp = go->GetGUID();
                        bool bAllOthersAreDone = true;
                        for (uint8 i = 0; i <= 10 && bAllOthersAreDone; ++i)
                            bAllOthersAreDone &= (uiEncounter[i] == DONE);
                        MakeObjectClickable(go, bAllOthersAreDone);
                        go->SetGoState(bAllOthersAreDone ? GO_STATE_ACTIVE : GO_STATE_READY);
                        break;
                    }
                    case GO_DOODAD_ICECROWN_BLOODPRINCE_DOOR_01:
                    {
                        uiBloodPrinceDoor01 = go->GetGUID();
                        break;
                    }
                    case PLAGUE_SIGIL:
                    {
                        uiPlagueSigil = go->GetGUID();
                        if (uiEncounter[DATA_PROFESSOR_PUTRICIDE_EVENT] == DONE)
                            HandleGameObject(NULL, true, go);
                        break;
                    }
                    case BLOODWING_SIGIL:
                    {
                        uiBloodwingSigil = go->GetGUID();
                        if (uiEncounter[DATA_BLOOD_QUEEN_LANA_THEL_EVENT] == DONE)
                            HandleGameObject(NULL, true, go);
                        break;
                    }
                    case FROSTWING_SIGIL:
                    {
                        uiFrostwingSigil = go->GetGUID();
                        if (uiEncounter[DATA_SINDRAGOSA_EVENT] == DONE)
                            HandleGameObject(NULL, true, go);
                    }
                    case GO_SPIRIT_ALARM1:
                    {
                        uiSpiritAlarm1 = go->GetGUID();
                        break;
                    }
                    case GO_SPIRIT_ALARM2:
                    {
                        uiSpiritAlarm2 = go->GetGUID();
                        break;
                    }
                    case GO_SPIRIT_ALARM3:
                    {
                        uiSpiritAlarm3 = go->GetGUID();
                        go->SetPhaseMask(2, true);
                        break;
                    }
                    case GO_SPIRIT_ALARM4:
                    {
                        uiSpiritAlarm4 = go->GetGUID();
                        go->SetPhaseMask(2, true);
                        break;
                    }
                }
            }

            uint64 GetData64(uint32 identifier)
            {
                switch(identifier)
                {
                    case DATA_LORD_MARROWGAR:                   return uiLordMarrowgar;
                    case DATA_GUNSHIP_BATTLE:                   return uiGunship;
                    case DATA_SAURFANG:                         return uiDeathbringerSaurfang;
                    case DATA_FESTERGUT:                        return uiFestergut;
                    case DATA_ROTFACE:                          return uiRotface;
                    case DATA_PROFESSOR_PUTRICIDE:              return uiProfessorPutricide;
                    case DATA_PRINCE_VALANAR_ICC:               return uiPrinceValanar;
                    case DATA_PRINCE_KELESETH_ICC:              return uiPrinceKeleseth;
                    case DATA_PRINCE_TALDARAM_ICC:              return uiPrinceTaldaram;
                    case DATA_BLOOD_QUEEN_LANA_THEL:            return uiBloodQueenLanathel;
                    case DATA_VALITHRIA_DREAMWALKER:            return uiValithriaDreamwalker;
                    case DATA_VALITHRIA_ALTERNATIVE:            return uiValithriaAlternative;
                    case DATA_VALITHRIA_COMBAT_TRIGGER:         return uiValithriaCombatTrigger;
                    case DATA_SINDRAGOSA: 
                                                                return sindragosa; 
                    case DATA_SPINESTALKER: 
                                                                return spinestalker; 
                    case DATA_RIMEFANG: 
                                                                return rimefang; 
                    case DATA_LICH_KING:                        return uiLichKing;
                    case DATA_TIRION:                           return uiTirion;
                    case DATA_ANGLE:                            return uiAngle;
                    case DATA_ALL_YOU_CAN_EAT:                  return uiAllYouCanEat;
                    case DATA_BEEN_WAITING:                     return uiBeenWaiting;
                    case DATA_NECK_DEEP:                        return uiNeckDeep;
                    case DATA_BLOOD_PRINCES_CONTROL:            return uiBloodCouncilController;
                    case DATA_NECROTIC_STACK:                   return uiNecroticStack;
                    case DATA_PUTRICIDE_TABLE:                  return uiPutricideTable;
                    case DATA_SINDRAGOSA_ENTRANCE_DOOR:         return uiSindragosaDoor1;

                    case DATA_TELEPORT_LIGHTS_HAMMER:           return uiFirstTp;
                    case DATA_TELEPORT_ORATORY_OF_THE_DAMNED:   return uiMarrowgarTp;
                    case DATA_TELEPORT_RAMPART_OF_SKULLS:       return uiFlightWarTp;
                    case DATA_TELEPORT_DEATHBRINGERS_RISE:      return uiSaurfangTp;
                    case DATA_TELEPORT_UPPER_SPIRE:             return uiCitadelTp;
                    case DATA_TELEPORT_SINDRAGOSAS_LAIR:        return uiSindragosaTp;
                    case DATA_TELEPORT_FROZEN_THRONE:           return uiLichTp;

                    case DATA_PROF_COLLISION_DOOR:              return uiProfCollisionDoor;
                    case DATA_PROF_ORANGE_DOOR:                 return uiOrangeMonsterDoor;
                    case DATA_PROF_GREEN_DOOR:                  return uiGreenMonsterDoor;

                    case DATA_SPIRIT_ALARM1:                    return uiSpiritAlarm1;
                    case DATA_SPIRIT_ALARM2:                    return uiSpiritAlarm2;
                    case DATA_SPIRIT_ALARM3:                    return uiSpiritAlarm3;
                    case DATA_SPIRIT_ALARM4:                    return uiSpiritAlarm4;

                    case DATA_DEATHBOUND_WARD1:                 return uiDeathboundWard1;
                    case DATA_DEATHBOUND_WARD2:                 return uiDeathboundWard2;
                    case DATA_DEATHBOUND_WARD3:                 return uiDeathboundWard3;
                    case DATA_DEATHBOUND_WARD4:                 return uiDeathboundWard4;
                }
                return 0;
            }

            uint32 GetCompletedEncounterMask() const
            {
                uint32 mask = 0;
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (GetBossState(i) == DONE)
                        mask |= 1 << i;

                return mask;
            }

            void MakeObjectClickable(GameObject *obj, bool clickable = true)
            {
                if (clickable)
                    obj->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                else
                    obj->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
            }

            void MakeObjectClickable(const uint32 objectDataId, bool clickable = true)
            {
                uint64 objGUID = GetData64(objectDataId);
                GameObject *obj = instance->GetGameObject(objGUID);
                if (!obj)
                {
                    instance->LoadGrid(gameObjectPositions[objGUID].GetPositionX(), gameObjectPositions[objGUID].GetPositionY());
                    obj = instance->GetGameObject(objGUID);
                }
                if (!obj)
                    return;
                MakeObjectClickable(obj, clickable);
            }


            void EnableObject(const uint32 teleportId, GOState state)
            {
                if (GameObject *teleport = instance->GetGameObject(GetData64(teleportId)))
                    teleport->SetGoState(state);
            }

            void SetData(uint32 type, uint32 data)
            {
                switch(type)
                {
                    case DATA_MARROWGAR_EVENT:
                    {
                        if (data == FAIL)
                            HandleGameObject(uiMarrowgarEntrance, true);
                        if(data == DONE)
                        {
                            MakeObjectClickable(DATA_TELEPORT_LIGHTS_HAMMER);
                            EnableObject(DATA_TELEPORT_LIGHTS_HAMMER, data == DONE ? GO_STATE_ACTIVE : GO_STATE_READY);
                            MakeObjectClickable(DATA_TELEPORT_ORATORY_OF_THE_DAMNED);
                            HandleGameObject(uiIceWall1, true);
                            HandleGameObject(uiIceWall2, true);
                            HandleGameObject(uiMarrowgarEntrance, true);
                        }
                        if(data == IN_PROGRESS)
                            HandleGameObject(uiMarrowgarEntrance, false);
                        uiEncounter[DATA_MARROWGAR_EVENT] = data;
                        break;
                    }
                    case DATA_DEATHWHISPER_EVENT:
                    {
                        if (data == FAIL)
                            HandleGameObject(uiOratoryDoor, true);
                        if(data == DONE)
                        {
                            MakeObjectClickable(DATA_TELEPORT_RAMPART_OF_SKULLS);
                            EnableObject(DATA_TELEPORT_RAMPART_OF_SKULLS, data == DONE ? GO_STATE_ACTIVE : GO_STATE_READY);
                            MakeObjectClickable(DATA_TELEPORT_DEATHBRINGERS_RISE);
                            EnableObject(DATA_TELEPORT_DEATHBRINGERS_RISE, data == DONE ? GO_STATE_ACTIVE : GO_STATE_READY);
                            HandleGameObject(uiOratoryDoor, true);
                            if (GameObject* go = instance->GetGameObject(uiLadyDeathwisperTransporter))
                            {
                                go->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                                go->SetGoState(GO_STATE_READY);
                            }
                        }
                        if(data == IN_PROGRESS)
                            HandleGameObject(uiOratoryDoor, false);
                        uiEncounter[DATA_DEATHWHISPER_EVENT] = data;
                        break;
                    }
                    /*case DATA_GUNSHIP_BATTLE_EVENT:
                        switch(data)
                        {
                            case DONE:
                                break;
                            case NOT_STARTED:
                                break;
                        }
                        uiEncounter[DATA_GUNSHIP_BATTLE_EVENT] = data;
                        break;*/
                    case DATA_SAURFANG_EVENT:
                    {
                        //Preload the area around the Upper Spire�� teleport
                        instance->LoadGrid(4199.35f, 2769.42f);
                        MakeObjectClickable(DATA_TELEPORT_DEATHBRINGERS_RISE, data != IN_PROGRESS);
                        EnableObject(DATA_TELEPORT_DEATHBRINGERS_RISE, data == IN_PROGRESS ? GO_STATE_READY : GO_STATE_ACTIVE);
                        if (data == DONE)
                        {
                            MakeObjectClickable(DATA_TELEPORT_UPPER_SPIRE);
                            if (GameObject* pChest = instance->GetGameObject(uiSaurfangCache))
                                pChest->SetRespawnTime(pChest->GetRespawnDelay());
                            HandleGameObject(uiSaurfangDoor, true);
                            HandleGameObject(uiBloodwingDoor, true);
                            HandleGameObject(uiFrostwingDoor, true);
                        }
                        uiEncounter[DATA_SAURFANG_EVENT] = data;
                        break;
                    }
                    case DATA_FESTERGUT_EVENT:
                    {
                        if(data == DONE)
                        {
                            if (uiEncounter[DATA_ROTFACE_EVENT] == DONE)
                            {
                                //MakeObjectClickable(DATA_PROF_COLLISION_DOOR);
                                HandleGameObject(uiProfCollisionDoor, true);
                                if (GameObject* go = instance->GetGameObject(uiProfDoorOrange))
                                    go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                                if (GameObject* go = instance->GetGameObject(uiProfDoorGreen))
                                    go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                            }
                            else
                            {
                                if (GameObject* go = instance->GetGameObject(uiProfDoorOrange))
                                    HandleGameObject(uiProfDoorOrange, true, go);
                            }
                            HandleGameObject(uiOrangePipe, true);
                            HandleGameObject(uiGasValve, true);
                            HandleGameObject(uiOrangeMonsterDoor, true);
                        }
                        if(data == NOT_STARTED)
                        {
                            HandleGameObject(uiOrangeMonsterDoor, true);
                            HandleGameObject(uiOrangePipe, false);
                            HandleGameObject(uiGasValve, false);
                            HandleGameObject(uiProfDoorOrange, false);
                        }
                        if(data == IN_PROGRESS)
                        {
                            HandleGameObject(uiOrangeMonsterDoor, false);
                            HandleGameObject(uiOrangePipe, false);
                            HandleGameObject(uiGasValve, false);
                            HandleGameObject(uiProfDoorOrange, false);
                        }
                        uiEncounter[DATA_FESTERGUT_EVENT] = data;
                        break;
                    }
                    case DATA_ROTFACE_EVENT:
                    {
                        if(data == DONE)
                        {
                            if (uiEncounter[DATA_FESTERGUT_EVENT] == DONE)
                            {
                                //MakeObjectClickable(DATA_PROF_COLLISION_DOOR);
                                HandleGameObject(uiProfCollisionDoor, true);
                                if (GameObject* go = instance->GetGameObject(uiProfDoorOrange))
                                    go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                                if (GameObject* go = instance->GetGameObject(uiProfDoorGreen))
                                    go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                            }
                            else
                            {
                                if (GameObject* go = instance->GetGameObject(uiProfDoorGreen))
                                    HandleGameObject(uiProfDoorGreen, false, go);
                            }
                            HandleGameObject(uiGreenPipe, true);
                            HandleGameObject(uiOozeValve, true);
                            HandleGameObject(uiGreenMonsterDoor, true);
                        }
                        if(data == NOT_STARTED)
                        {
                            HandleGameObject(uiGreenMonsterDoor, true);
                            HandleGameObject(uiGreenPipe, false);
                            HandleGameObject(uiOozeValve, false);
                            HandleGameObject(uiProfDoorGreen, false);
                        }
                        if(data == IN_PROGRESS)
                        {
                            HandleGameObject(uiGreenMonsterDoor, false);
                            HandleGameObject(uiGreenPipe, false);
                            HandleGameObject(uiOozeValve, false);
                            HandleGameObject(uiProfDoorGreen, false);
                        }
                        uiEncounter[DATA_ROTFACE_EVENT] = data;
                        break;
                    }
                    case DATA_PROFESSOR_PUTRICIDE_EVENT:
                    {
                        if(data == DONE)
                        {
                            HandleGameObject(uiProffesorDoor, true);
                            HandleGameObject(uiPlagueSigil, true);
                            if (uiEncounter[DATA_BLOOD_QUEEN_LANA_THEL_EVENT] == DONE && uiEncounter[DATA_SINDRAGOSA_EVENT] == DONE)
                                MakeObjectClickable(DATA_TELEPORT_FROZEN_THRONE);
                        }
                        if(data == NOT_STARTED)
                            HandleGameObject(uiProffesorDoor, true);
                        if(data == IN_PROGRESS)
                            HandleGameObject(uiProffesorDoor, false);
                        uiEncounter[DATA_PROFESSOR_PUTRICIDE_EVENT] = data;
                        break;
                    }
                    case DATA_BLOOD_PRINCE_COUNCIL_EVENT:
                    {
                        if(data == DONE)
                        {
                            HandleGameObject(uiCrimsonHallDoor1, true);
                            HandleGameObject(uiCrimsonHallDoor2, true);
                            HandleGameObject(uiCrimsonHallDoor3, true);
                        }
                        if(data == NOT_STARTED || data == FAIL)
                            HandleGameObject(uiCrimsonHallDoor1, true);

                        if(data == IN_PROGRESS)
                            HandleGameObject(uiCrimsonHallDoor1, false);
                        uiEncounter[DATA_BLOOD_PRINCE_COUNCIL_EVENT] = data;
                        break;
                    }
                    case DATA_BLOOD_QUEEN_LANA_THEL_EVENT:
                    {
                        if(data == DONE)
                        {
                            if (GameObject* go = instance->GetGameObject(uiBloodQueenTransporter))
                            {
                                go->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                                go->SetGoState(GO_STATE_READY);
                            }
                            HandleGameObject(uiBloodwingSigil, true);
                            if (uiEncounter[DATA_PROFESSOR_PUTRICIDE_EVENT] == DONE && uiEncounter[DATA_SINDRAGOSA_EVENT] == DONE)
                                MakeObjectClickable(DATA_TELEPORT_FROZEN_THRONE);
                        }
                        if (data == FAIL || data == DONE)
                            HandleGameObject(uiBloodPrinceDoor01, true);
                        if (data == IN_PROGRESS)
                            HandleGameObject(uiBloodPrinceDoor01, false);
                        uiEncounter[DATA_BLOOD_QUEEN_LANA_THEL_EVENT] = data;
                        break;
                    }
                    case DATA_VALITHRIA_DREAMWALKER_EVENT:
                    {
                        if(data == DONE)
                        {
                            MakeObjectClickable(DATA_TELEPORT_SINDRAGOSAS_LAIR);
                            if (GameObject* pChest = instance->GetGameObject(uiDreamwalkerCache))
                                pChest->SetRespawnTime(pChest->GetRespawnDelay());
                            if (GameObject* go = instance->GetGameObject(uiValithriaTransporter))
                            {
                                go->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                                go->SetGoState(GO_STATE_READY);
                            }
                            if (GameObject* go = instance->GetGameObject(uiSindragosaTransporter))
                            {
                                go->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                                go->SetGoState(GO_STATE_READY);
                            }
                            HandleGameObject(uiDragonDoor1, true);
                            HandleGameObject(uiDragonDoor2, true);
                            HandleGameObject(uiDragonDoor3, true);
                        }
                        if(data == NOT_STARTED || data == FAIL)
                        {
                            HandleGameObject(uiDragonDoor1, true);
                            HandleGameObject(uiRoostDoor3, false);
                            HandleGameObject(uiRoostDoor2, false);         
                            HandleGameObject(uiRoostDoor1, false);
                            HandleGameObject(uiRoostDoor4, false);
                        }
                        if(data == IN_PROGRESS)
                        {
                            HandleGameObject(uiDragonDoor1, false);
                            HandleGameObject(uiRoostDoor3, true);
                            HandleGameObject(uiRoostDoor2, true);
                            if (uiDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || uiDifficulty == RAID_DIFFICULTY_25MAN_HEROIC)
                            {
                                HandleGameObject(uiRoostDoor1, true);
                                HandleGameObject(uiRoostDoor4, true);
                            }
                        }
                        uiEncounter[DATA_VALITHRIA_DREAMWALKER_EVENT] = data;
                        break;
                    }
                    case DATA_SINDRAGOSA_EVENT:
                    {
                        if (data == IN_PROGRESS)
                            HandleGameObject(uiSindragosaIceWall, false);
                        else
                            HandleGameObject(uiSindragosaIceWall, true);
                        if (data == DONE)
                        {
                            HandleGameObject(uiSindragosaDoor1, true);
                            HandleGameObject(uiSindragosaDoor2, true);
                            HandleGameObject(uiFrostwingSigil, true);
                        }
                        if (uiEncounter[DATA_PROFESSOR_PUTRICIDE_EVENT] == DONE && uiEncounter[DATA_BLOOD_QUEEN_LANA_THEL_EVENT] == DONE)
                            MakeObjectClickable(DATA_TELEPORT_FROZEN_THRONE);
                        uiEncounter[DATA_SINDRAGOSA_EVENT] = data;
                        break;
                    }
                    case DATA_LICH_KING_EVENT:
                        uiEncounter[DATA_LICH_KING_EVENT] = data;
                        break;
                    case DATA_BONED_ACHIEVEMENT:
                        isBonedEligible = data ? true : false;
                        break;
                    case DATA_OOZE_DANCE_ACHIEVEMENT:
                        isOozeDanceEligible = data ? true : false;
                        break;
                    case DATA_NAUSEA_ACHIEVEMENT:
                        isNauseaEligible = data ? true : false;
                        break;
                    case DATA_ORB_WHISPERER_ACHIEVEMENT:
                        isOrbWhispererEligible = data ? true : false;
                        break;
                    case DATA_PORTAL_JOCKEY_ACHIEVEMENT:
                        isPortalJockeyEligible = data ? true : false;
                        break;
                    case DATA_SINDRAGOSA_FROSTWYRMS:
                    {
                        if (data > 1) 
                            frostwyrms = data; 
                        else if (data == 1) 
                            ++frostwyrms; 
                        else if (!data && !--frostwyrms && GetBossState(DATA_SINDRAGOSA) != DONE) 
                        { 
                            instance->LoadGrid(SindragosaSpawnPos.GetPositionX(), SindragosaSpawnPos.GetPositionY()); 
                            if (Creature* boss = instance->SummonCreature(NPC_SINDRAGOSA, SindragosaSpawnPos)) 
                            { 
                                boss->setActive(true); 
                                boss->AI()->DoAction(ACTION_START_FROSTWYRM); 
                            } 
                        } 
                        break; 
                    }
                    case DATA_SPINESTALKER:
                    {
                        if (data > 1) 
                            spinestalkerTrash = data; 
                        else if (data == 1) 
                            ++spinestalkerTrash; 
                        else if (!data && !--spinestalkerTrash) 
                            if (Creature* spinestalk = instance->GetCreature(spinestalker)) 
                                spinestalk->AI()->DoAction(ACTION_START_FROSTWYRM); 
                        break;
                    }
                    case DATA_RIMEFANG:
                    {
                        if (data > 1) 
                            rimefangTrash = data; 
                        else if (data == 1) 
                            ++rimefangTrash; 
                        else if (!data && !--rimefangTrash) 
                            if (Creature* rime = instance->GetCreature(rimefang)) 
                                rime->AI()->DoAction(ACTION_START_FROSTWYRM);
                    }
                }

                if (data == DONE)
                    SaveToDB();
            }

            uint32 GetData(uint32 type)
            {
                switch(type)
                {
                case DATA_MARROWGAR_EVENT:
                    return uiEncounter[DATA_MARROWGAR_EVENT];
                case DATA_DEATHWHISPER_EVENT:
                    return uiEncounter[DATA_DEATHWHISPER_EVENT];
                case DATA_GUNSHIP_BATTLE_EVENT:
                    return uiEncounter[DATA_GUNSHIP_BATTLE_EVENT];
                case DATA_SAURFANG_EVENT:
                    return uiEncounter[DATA_SAURFANG_EVENT];
                case DATA_FESTERGUT_EVENT:
                    return uiEncounter[DATA_FESTERGUT_EVENT];
                case DATA_ROTFACE_EVENT:
                    return uiEncounter[DATA_ROTFACE_EVENT];
                case DATA_PROFESSOR_PUTRICIDE_EVENT:
                    return uiEncounter[DATA_PROFESSOR_PUTRICIDE_EVENT];
                case DATA_BLOOD_PRINCE_COUNCIL_EVENT:
                    return uiEncounter[DATA_BLOOD_PRINCE_COUNCIL_EVENT];
                case DATA_BLOOD_QUEEN_LANA_THEL_EVENT:
                    return uiEncounter[DATA_BLOOD_QUEEN_LANA_THEL_EVENT];
                case DATA_VALITHRIA_DREAMWALKER_EVENT:
                    return uiEncounter[DATA_VALITHRIA_DREAMWALKER_EVENT];
                case DATA_SINDRAGOSA_EVENT:
                    return uiEncounter[DATA_SINDRAGOSA_EVENT];
                case DATA_LICH_KING_EVENT:
                    return uiEncounter[DATA_LICH_KING_EVENT];

                case DATA_SINDRAGOSA_FROSTWYRMS: 
                    return frostwyrms; 
                case DATA_SPINESTALKER: 
                    return spinestalkerTrash; 
                case DATA_RIMEFANG: 
                    return rimefangTrash; 
                default: 
                    break; 
                } 


                return 0;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;
                //While Gunship Battle isn't implemented
                uiEncounter[DATA_GUNSHIP_BATTLE_EVENT] = DONE;
                std::ostringstream saveStream;
                saveStream << "I C" << uiEncounter[DATA_MARROWGAR_EVENT] << " " << uiEncounter[DATA_DEATHWHISPER_EVENT] << " " << uiEncounter[DATA_GUNSHIP_BATTLE_EVENT] << " " << uiEncounter[DATA_SAURFANG_EVENT]
                << " " << uiEncounter[DATA_FESTERGUT_EVENT] << " " << uiEncounter[DATA_ROTFACE_EVENT] << " " << uiEncounter[DATA_PROFESSOR_PUTRICIDE_EVENT] << " " << uiEncounter[DATA_BLOOD_PRINCE_COUNCIL_EVENT] << " " << uiEncounter[DATA_BLOOD_QUEEN_LANA_THEL_EVENT]
                << " " << uiEncounter[DATA_VALITHRIA_DREAMWALKER_EVENT] << " " << uiEncounter[DATA_SINDRAGOSA_EVENT] << " " << uiEncounter[DATA_LICH_KING_EVENT];

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            bool CheckAchievementCriteriaMeet(uint32 criteria_id, Player const* /*source*/, Unit const* /*target*/, uint32 /*miscvalue1*/)
            {
                switch (criteria_id)
                {
                    case CRITERIA_BONED_10N:
                    case CRITERIA_BONED_25N:
                    case CRITERIA_BONED_10H:
                    case CRITERIA_BONED_25H:
                        return isBonedEligible;
                    case CRITERIA_DANCES_WITH_OOZES_10N:
                    case CRITERIA_DANCES_WITH_OOZES_25N:
                    case CRITERIA_DANCES_WITH_OOZES_10H:
                    case CRITERIA_DANCES_WITH_OOZES_25H:
                        return isOozeDanceEligible;
                    case CRITERIA_NAUSEA_10N:
                    case CRITERIA_NAUSEA_25N:
                    case CRITERIA_NAUSEA_10H:
                    case CRITERIA_NAUSEA_25H:
                        return isNauseaEligible;
                    case CRITERIA_ORB_WHISPERER_10N:
                    case CRITERIA_ORB_WHISPERER_25N:
                    case CRITERIA_ORB_WHISPERER_10H:
                    case CRITERIA_ORB_WHISPERER_25H:
                        return isOrbWhispererEligible;
                    // Only one criteria for both modes, need to do it like this
                    case CRITERIA_KILL_LANA_THEL_10M:
                    case CRITERIA_ONCE_BITTEN_TWICE_SHY_10N:
                    case CRITERIA_ONCE_BITTEN_TWICE_SHY_10V:
                        return CAST_INST(InstanceMap, instance)->GetMaxPlayers() == 10;
                    case CRITERIA_KILL_LANA_THEL_25M:
                    case CRITERIA_ONCE_BITTEN_TWICE_SHY_25N:
                    case CRITERIA_ONCE_BITTEN_TWICE_SHY_25V:
                        return CAST_INST(InstanceMap, instance)->GetMaxPlayers() == 25;
                    //case CRITERIA_PORTAL_JOCKEY_10N:
                    //case CRITERIA_PORTAL_JOCKEY_10H:
                    //case CRITERIA_PORTAL_JOCKEY_25N:
                    //case CRITERIA_PORTAL_JOCKEY_25H:
                    //    return isPortalJockeyEligible;
                    default:
                        break;
                }

                return false;
            }

            void Load(const char* in)
            {
                if (!in)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(in);

                char dataHead1, dataHead2;
                uint32 data0,data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11;

                std::istringstream loadStream(in);
                loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3 >> data4 >> data5 >> data6 >> data7 >> data8 >> data9 >> data10 >> data11;

                if (dataHead1 == 'I' && dataHead2 == 'C')
                {
                    uiEncounter[DATA_MARROWGAR_EVENT] = data0;
                    uiEncounter[DATA_DEATHWHISPER_EVENT] = data1;
                    //While not implemented
                    uiEncounter[DATA_GUNSHIP_BATTLE_EVENT] = DONE;
                    //uiEncounter[DATA_GUNSHIP_BATTLE_EVENT] = data2;
                    uiEncounter[DATA_SAURFANG_EVENT] = data3;
                    uiEncounter[DATA_FESTERGUT_EVENT] = data4;
                    uiEncounter[DATA_ROTFACE_EVENT] = data5;
                    uiEncounter[DATA_PROFESSOR_PUTRICIDE_EVENT] = data6;
                    uiEncounter[DATA_BLOOD_PRINCE_COUNCIL_EVENT] = data7;
                    uiEncounter[DATA_BLOOD_QUEEN_LANA_THEL_EVENT] = data8;
                    uiEncounter[DATA_VALITHRIA_DREAMWALKER_EVENT] = data9;
                    uiEncounter[DATA_SINDRAGOSA_EVENT] = data10;
                    uiEncounter[DATA_LICH_KING_EVENT] = data11;
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        loadStream >> uiEncounter[i];

                        if (uiEncounter[i] == IN_PROGRESS)
                            uiEncounter[i] = NOT_STARTED;
                    }

                } else OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

        private:
            uint64 uiLordMarrowgar;
            uint64 uiGunship;
            uint64 uiDeathbringerSaurfang;
            uint64 uiFestergut;
            uint64 uiRotface;
            uint64 uiProfessorPutricide;
            uint64 uiPrinceValanar;
            uint64 uiPrinceKeleseth;
            uint64 uiPrinceTaldaram;
            uint64 uiBloodQueenLanathel;
            uint64 uiValithriaDreamwalker;
            uint64 uiValithriaAlternative;
            uint64 uiValithriaCombatTrigger;
            uint64 uiLichKing;
            uint64 uiTirion;
            uint64 uiIceWall1;
            uint64 uiIceWall2;
            uint64 uiMarrowgarEntrance;
            uint64 uiFrozenThrone;
            uint64 uiSaurfangCache;
            uint64 uiLadyDeathwisperTransporter;
            uint64 uiOratoryDoor;
            uint64 uiSaurfangDoor;
            uint64 uiOrangeMonsterDoor;
            uint64 uiGreenMonsterDoor;
            uint64 uiProfCollisionDoor;
            uint64 uiPutricideTable;
            uint64 uiOrangePipe;
            uint64 uiGreenPipe;
            uint64 uiOozeValve;
            uint64 uiGasValve;
            uint64 uiProfDoorOrange;
            uint64 uiProfDoorGreen;
            uint64 uiRotfaceEntrance;
            uint64 uiFestergurtEntrance;
            uint64 uiProffesorDoor;
            uint64 uiBloodwingDoor;
            uint64 uiCrimsonHallDoor1;
            uint64 uiCrimsonHallDoor2;
            uint64 uiCrimsonHallDoor3;
            uint64 uiBloodQueenTransporter;
            uint64 uiBloodPrinceDoor01;
            uint64 uiFrostwingDoor;
            uint64 uiDragonDoor1;
            uint64 uiDragonDoor2;
            uint64 uiDragonDoor3;
            uint64 uiRoostDoor1;
            uint64 uiRoostDoor2;
            uint64 uiRoostDoor3;
            uint64 uiRoostDoor4;
            uint64 uiValithriaTransporter;
            uint64 uiSindragosaTransporter;
            uint64 uiDreamwalkerCache;
            uint64 uiSindragosaDoor1;
            uint64 uiSindragosaDoor2;
            uint64 uiSindragosaIceWall;
            uint64 uiFirstTp;
            uint64 uiMarrowgarTp;
            uint64 uiFlightWarTp;
            uint64 uiSaurfangTp;
            uint64 uiCitadelTp;
            uint64 uiSindragosaTp;
            uint64 uiLichTp;
            uint64 uiBloodCouncilController;
            uint64 uiPlagueSigil;
            uint64 uiBloodwingSigil;
            uint64 uiFrostwingSigil;
            uint64 uiSpiritAlarm1;
            uint64 uiSpiritAlarm2;
            uint64 uiSpiritAlarm3;
            uint64 uiSpiritAlarm4;
            uint64 uiDeathboundWard1;
            uint64 uiDeathboundWard2;
            uint64 uiDeathboundWard3;
            uint64 uiDeathboundWard4;

            uint8 uiDifficulty;
            uint8 uiSpawn;
            uint8 uiAllYouCanEat;
            uint8 uiBeenWaiting;
            uint8 uiNeckDeep;
            uint8 uiNecroticStack;
            uint8 uiAngle;
            uint64 sindragosa; 
            uint64 spinestalker; 
            uint64 rimefang; 
            uint8 frostwyrms; 
            uint8 spinestalkerTrash; 
            uint8 rimefangTrash; 

            uint8 isBonedEligible;
            uint8 isOozeDanceEligible;
            uint8 isNauseaEligible;
            uint8 isOrbWhispererEligible;
            uint8 isPortalJockeyEligible;
            uint32 uiEncounter[MAX_ENCOUNTER];
            std::map<uint64, Position> gameObjectPositions;
        };

        InstanceScript* GetInstanceScript(InstanceMap* pMap) const
        {
            return new instance_icecrown_citadel_InstanceMapScript(pMap);
        }
};
void DespawnAllCreaturesAround(Creature *ref, uint32 entry)
{
    while (Unit *unit = ref->FindNearestCreature(entry, 80.0f, true))
        if (Creature *creature = unit->ToCreature())
            creature->DespawnOrUnsummon();
}
void UnsummonSpecificCreaturesNearby(Creature *ref, uint32 entry, float radius)
{
    std::list<Creature*> allCreaturesWithEntry;
    GetCreatureListWithEntryInGrid(allCreaturesWithEntry, ref, entry, radius);
    for(std::list<Creature*>::iterator itr = allCreaturesWithEntry.begin(); itr != allCreaturesWithEntry.end(); ++itr)
    {
        Creature *candidate = *itr;

        if (!candidate)
            continue;
        if (TempSummon* summon = candidate->ToTempSummon())
            summon->DespawnOrUnsummon();
    }
}
uint32 GetPhase(const EventMap &em)
{
    switch (em.GetPhaseMask())
    {
        case 0x01: return 0;
        case 0x02: return 1;
        case 0x04: return 2;
        case 0x08: return 3;
        case 0x10: return 4;
        case 0x20: return 5;
        case 0x40: return 6;
        case 0x80: return 7;
        default:
            return 0;
    }
}

void AddSC_instance_icecrown_citadel()
{
    new instance_icecrown_citadel();
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    