/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "FiM_Cfg_PbCfg.h"
#include "FiM_Priv_Data.h"

#define FIM_START_SEC_ROM_CONST
#include "FiM_MemMap.h"

/*
 ***************************************************************************************************
 * inhibit offset data structure
 ***************************************************************************************************
 */
const FiM_NumOffsetEventType FiM_Cfg_NumOffsetEvent_auo[FIM_CFG_NUMBEROFDEMEVENTIDS
		+ 2] = { 0, /* Element 0 denotes the invalid event Id */
0, /* Start Index of Event Id 1 (DemConf_DemEventParameter_DemEventParameter_Can_Network_1_BusOff) */
0, /* Start Index of Event Id 2 (DemConf_DemEventParameter_DemEventParameter_Can_Network_2_BusOff) */
0, /* Start Index of Event Id 3 (DemConf_DemEventParameter_DemEventParameter_Can_Network_3_BusOff) */
0, /* Start Index of Event Id 4 (DemConf_DemEventParameter_DemEventParameter_Can_Network_4_BusOff) */
0, /* Start Index of Event Id 5 (DemConf_DemEventParameter_DemEventParameter_Can_Network_5_BusOff) */
0, /* Start Index of Event Id 6 (DemConf_DemEventParameter_DemEventParameter_Can_Network_6_BusOff) */
0, /* Start Index of Event Id 7 (DemConf_DemEventParameter_DemEventParameter_P0101F0) */
1, /* Start Index of Event Id 8 (DemConf_DemEventParameter_DemEventParameter_P0101F1) */
1, /* Start Index of Event Id 9 (DemConf_DemEventParameter_DemEventParameter_P0102F0) */
1, /* Start Index of Event Id 10 (DemConf_DemEventParameter_DemEventParameter_P0102F1) */
1, /* Start Index of Event Id 11 (DemConf_DemEventParameter_DemEventParameter_P010300) */
1, /* Start Index of Event Id 12 (DemConf_DemEventParameter_DemEventParameter_P010400) */
1, /* Start Index of Event Id 13 (DemConf_DemEventParameter_DemEventParameter_P010500) */
1, /* Start Index of Event Id 14 (DemConf_DemEventParameter_DemEventParameter_P010600) */
1, /* Start Index of Event Id 15 (DemConf_DemEventParameter_DemEventParameter_P010700) */
1, /* Start Index of Event Id 16 (DemConf_DemEventParameter_DemEventParameter_P010800) */
1, /* Start Index of Event Id 17 (DemConf_DemEventParameter_DemEventParameter_P010900) */
1, /* Start Index of Event Id 18 (DemConf_DemEventParameter_DemEventParameter_P011000) */
1, /* Start Index of Event Id 19 (DemConf_DemEventParameter_DemEventParameter_P011100) */
1, /* Start Index of Event Id 20 (DemConf_DemEventParameter_DemEventParameter_P011200) */
1, /* Start Index of Event Id 21 (DemConf_DemEventParameter_DemEventParameter_P011300) */
1, /* Start Index of Event Id 22 (DemConf_DemEventParameter_DemEventParameter_P011400) */
1, /* Start Index of Event Id 23 (DemConf_DemEventParameter_DemEventParameter_P011500) */
1, /* Start Index of Event Id 24 (DemConf_DemEventParameter_DemEventParameter_P011600) */
1, /* Start Index of Event Id 25 (DemConf_DemEventParameter_DemEventParameter_P0117F0) */
1, /* Start Index of Event Id 26 (DemConf_DemEventParameter_DemEventParameter_P0117F1) */
1, /* Start Index of Event Id 27 (DemConf_DemEventParameter_DemEventParameter_P0117F2) */
1, /* Start Index of Event Id 28 (DemConf_DemEventParameter_DemEventParameter_P0118F0) */
1, /* Start Index of Event Id 29 (DemConf_DemEventParameter_DemEventParameter_P0118F1) */
1, /* Start Index of Event Id 30 (DemConf_DemEventParameter_DemEventParameter_P0118F2) */
1, /* Start Index of Event Id 31 (DemConf_DemEventParameter_DemEventParameter_P0119F0) */
1, /* Start Index of Event Id 32 (DemConf_DemEventParameter_DemEventParameter_P0119F1) */
1, /* Start Index of Event Id 33 (DemConf_DemEventParameter_DemEventParameter_P0119F2) */
1, /* Start Index of Event Id 34 (DemConf_DemEventParameter_DemEventParameter_P0120F0) */
1, /* Start Index of Event Id 35 (DemConf_DemEventParameter_DemEventParameter_P0120F1) */
1, /* Start Index of Event Id 36 (DemConf_DemEventParameter_DemEventParameter_P0120F2) */
1, /* Start Index of Event Id 37 (DemConf_DemEventParameter_DemEventParameter_P0121F0) */
1, /* Start Index of Event Id 38 (DemConf_DemEventParameter_DemEventParameter_P0121F1) */
1, /* Start Index of Event Id 39 (DemConf_DemEventParameter_DemEventParameter_P0121F2) */
1, /* Start Index of Event Id 40 (DemConf_DemEventParameter_DemEventParameter_P0122F0) */
1, /* Start Index of Event Id 41 (DemConf_DemEventParameter_DemEventParameter_P0122F1) */
1, /* Start Index of Event Id 42 (DemConf_DemEventParameter_DemEventParameter_P0122F2) */
1, /* Start Index of Event Id 43 (DemConf_DemEventParameter_DemEventParameter_P0123F0) */
1, /* Start Index of Event Id 44 (DemConf_DemEventParameter_DemEventParameter_P0123F1) */
1, /* Start Index of Event Id 45 (DemConf_DemEventParameter_DemEventParameter_P0123F2) */
1, /* Start Index of Event Id 46 (DemConf_DemEventParameter_DemEventParameter_P012400) */
1, /* Start Index of Event Id 47 (DemConf_DemEventParameter_DemEventParameter_P012500) */
1, /* Start Index of Event Id 48 (DemConf_DemEventParameter_DemEventParameter_P012600) */
1, /* Start Index of Event Id 49 (DemConf_DemEventParameter_DemEventParameter_P012700) */
1, /* Start Index of Event Id 50 (DemConf_DemEventParameter_DemEventParameter_P012800) */
1, /* Start Index of Event Id 51 (DemConf_DemEventParameter_DemEventParameter_P012801) */
1, /* Start Index of Event Id 52 (DemConf_DemEventParameter_DemEventParameter_P012900) */
1, /* Start Index of Event Id 53 (DemConf_DemEventParameter_DemEventParameter_P013000) */
1, /* Start Index of Event Id 54 (DemConf_DemEventParameter_DemEventParameter_P013100) */
1, /* Start Index of Event Id 55 (DemConf_DemEventParameter_DemEventParameter_P013200) */
1, /* Start Index of Event Id 56 (DemConf_DemEventParameter_DemEventParameter_P013300) */
1, /* Start Index of Event Id 57 (DemConf_DemEventParameter_DemEventParameter_P013400) */
1, /* Start Index of Event Id 58 (DemConf_DemEventParameter_DemEventParameter_P0135F0) */
1, /* Start Index of Event Id 59 (DemConf_DemEventParameter_DemEventParameter_P0135F1) */
1, /* Start Index of Event Id 60 (DemConf_DemEventParameter_DemEventParameter_P0135F2) */
1, /* Start Index of Event Id 61 (DemConf_DemEventParameter_DemEventParameter_P0136F0) */
1, /* Start Index of Event Id 62 (DemConf_DemEventParameter_DemEventParameter_P0136F1) */
1, /* Start Index of Event Id 63 (DemConf_DemEventParameter_DemEventParameter_P0136F2) */
1, /* Start Index of Event Id 64 (DemConf_DemEventParameter_DemEventParameter_P0137F0) */
1, /* Start Index of Event Id 65 (DemConf_DemEventParameter_DemEventParameter_P0137F1) */
1, /* Start Index of Event Id 66 (DemConf_DemEventParameter_DemEventParameter_P0137F2) */
1, /* Start Index of Event Id 67 (DemConf_DemEventParameter_DemEventParameter_P013800) */
1, /* Start Index of Event Id 68 (DemConf_DemEventParameter_DemEventParameter_P013900) */
1, /* Start Index of Event Id 69 (DemConf_DemEventParameter_DemEventParameter_P014000) */
1, /* Start Index of Event Id 70 (DemConf_DemEventParameter_DemEventParameter_P014100) */
1, /* Start Index of Event Id 71 (DemConf_DemEventParameter_DemEventParameter_P014200) */
1, /* Start Index of Event Id 72 (DemConf_DemEventParameter_DemEventParameter_P014300) */
1, /* Start Index of Event Id 73 (DemConf_DemEventParameter_DemEventParameter_P014400) */
1, /* Start Index of Event Id 74 (DemConf_DemEventParameter_DemEventParameter_P014500) */
1, /* Start Index of Event Id 75 (DemConf_DemEventParameter_DemEventParameter_P014600) */
1, /* Start Index of Event Id 76 (DemConf_DemEventParameter_DemEventParameter_P014700) */
1, /* Start Index of Event Id 77 (DemConf_DemEventParameter_DemEventParameter_P014800) */
1, /* Start Index of Event Id 78 (DemConf_DemEventParameter_DemEventParameter_P014900) */
1, /* Start Index of Event Id 79 (DemConf_DemEventParameter_DemEventParameter_P015000) */
1, /* Start Index of Event Id 80 (DemConf_DemEventParameter_DemEventParameter_P015100) */
1, /* Start Index of Event Id 81 (DemConf_DemEventParameter_DemEventParameter_P015200) */
1, /* Start Index of Event Id 82 (DemConf_DemEventParameter_DemEventParameter_P015300) */
1, /* Start Index of Event Id 83 (DemConf_DemEventParameter_DemEventParameter_P015400) */
1, /* Start Index of Event Id 84 (DemConf_DemEventParameter_DemEventParameter_P015500) */
1, /* Start Index of Event Id 85 (DemConf_DemEventParameter_DemEventParameter_P015600) */
1, /* Start Index of Event Id 86 (DemConf_DemEventParameter_DemEventParameter_P015700) */
1, /* Start Index of Event Id 87 (DemConf_DemEventParameter_DemEventParameter_P015800) */
1, /* Start Index of Event Id 88 (DemConf_DemEventParameter_DemEventParameter_P015900) */
1, /* Start Index of Event Id 89 (DemConf_DemEventParameter_DemEventParameter_P016000) */
1, /* Start Index of Event Id 90 (DemConf_DemEventParameter_DemEventParameter_P016100) */
1, /* Start Index of Event Id 91 (DemConf_DemEventParameter_DemEventParameter_P016200) */
1, /* Start Index of Event Id 92 (DemConf_DemEventParameter_DemEventParameter_P016300) */
1, /* Start Index of Event Id 93 (DemConf_DemEventParameter_DemEventParameter_P016400) */
1, /* Start Index of Event Id 94 (DemConf_DemEventParameter_DemEventParameter_P016500) */
1, /* Start Index of Event Id 95 (DemConf_DemEventParameter_DemEventParameter_P016600) */
1, /* Start Index of Event Id 96 (DemConf_DemEventParameter_DemEventParameter_P016700) */
1, /* Start Index of Event Id 97 (DemConf_DemEventParameter_DemEventParameter_P016800) */
1, /* Start Index of Event Id 98 (DemConf_DemEventParameter_DemEventParameter_P016900) */
1, /* Start Index of Event Id 99 (DemConf_DemEventParameter_DemEventParameter_P017000) */
1, /* Start Index of Event Id 100 (DemConf_DemEventParameter_DemEventParameter_P017100) */
1, /* Start Index of Event Id 101 (DemConf_DemEventParameter_DemEventParameter_P017200) */
1, /* Start Index of Event Id 102 (DemConf_DemEventParameter_DemEventParameter_P017300) */
1, /* Start Index of Event Id 103 (DemConf_DemEventParameter_DemEventParameter_P017400) */
1, /* Start Index of Event Id 104 (DemConf_DemEventParameter_DemEventParameter_P017500) */
1, /* Start Index of Event Id 105 (DemConf_DemEventParameter_DemEventParameter_P017600) */
1, /* Start Index of Event Id 106 (DemConf_DemEventParameter_DemEventParameter_P017700) */
1, /* Start Index of Event Id 107 (DemConf_DemEventParameter_DemEventParameter_P017800) */
1, /* Start Index of Event Id 108 (DemConf_DemEventParameter_DemEventParameter_P017900) */
1, /* Start Index of Event Id 109 (DemConf_DemEventParameter_DemEventParameter_P018000) */
1, /* Start Index of Event Id 110 (DemConf_DemEventParameter_DemEventParameter_P018100) */
1, /* Start Index of Event Id 111 (DemConf_DemEventParameter_DemEventParameter_P018200) */
1, /* Start Index of Event Id 112 (DemConf_DemEventParameter_DemEventParameter_P018300) */
1, /* Start Index of Event Id 113 (DemConf_DemEventParameter_DemEventParameter_P018400) */
1, /* Start Index of Event Id 114 (DemConf_DemEventParameter_DemEventParameter_P018500) */
1, /* Start Index of Event Id 115 (DemConf_DemEventParameter_DemEventParameter_P018600) */
1, /* Start Index of Event Id 116 (DemConf_DemEventParameter_DemEventParameter_P018700) */
1, /* Start Index of Event Id 117 (DemConf_DemEventParameter_DemEventParameter_P018800) */
1, /* Start Index of Event Id 118 (DemConf_DemEventParameter_DemEventParameter_P018900) */
1, /* Start Index of Event Id 119 (DemConf_DemEventParameter_DemEventParameter_P019000) */
1, /* Start Index of Event Id 120 (DemConf_DemEventParameter_DemEventParameter_P019100) */
1, /* Start Index of Event Id 121 (DemConf_DemEventParameter_DemEventParameter_P019200) */
1, /* Start Index of Event Id 122 (DemConf_DemEventParameter_DemEventParameter_P019300) */
1, /* Start Index of Event Id 123 (DemConf_DemEventParameter_DemEventParameter_P019400) */
1, /* Start Index of Event Id 124 (DemConf_DemEventParameter_DemEventParameter_P019500) */
1, /* Start Index of Event Id 125 (DemConf_DemEventParameter_DemEventParameter_P019600) */
1, /* Start Index of Event Id 126 (DemConf_DemEventParameter_DemEventParameter_P019700) */
1, /* Start Index of Event Id 127 (DemConf_DemEventParameter_DemEventParameter_P019800) */
1, /* Start Index of Event Id 128 (DemConf_DemEventParameter_DemEventParameter_P019900) */
1, /* Start Index of Event Id 129 (DemConf_DemEventParameter_DemEventParameter_P020000) */
1, /* Start Index of Event Id 130 (DemConf_DemEventParameter_DemEventParameter_P020100) */
1, /* Start Index of Event Id 131 (DemConf_DemEventParameter_DemEventParameter_P020200) */
1, /* Start Index of Event Id 132 (DemConf_DemEventParameter_DemEventParameter_P020300) */
1, /* Start Index of Event Id 133 (DemConf_DemEventParameter_DemEventParameter_P020400) */
1, /* Start Index of Event Id 134 (DemConf_DemEventParameter_DemEventParameter_P020500) */
1, /* Start Index of Event Id 135 (DemConf_DemEventParameter_DemEventParameter_P020600) */
1, /* Start Index of Event Id 136 (DemConf_DemEventParameter_DemEventParameter_P020700) */
1, /* Start Index of Event Id 137 (DemConf_DemEventParameter_DemEventParameter_P020800) */
1, /* Start Index of Event Id 138 (DemConf_DemEventParameter_DemEventParameter_P020900) */
1, /* Start Index of Event Id 139 (DemConf_DemEventParameter_DemEventParameter_P021000) */
1, /* Start Index of Event Id 140 (DemConf_DemEventParameter_DemEventParameter_P021100) */
1, /* Start Index of Event Id 141 (DemConf_DemEventParameter_DemEventParameter_P021200) */
1, /* Start Index of Event Id 142 (DemConf_DemEventParameter_DemEventParameter_P021300) */
1, /* Start Index of Event Id 143 (DemConf_DemEventParameter_DemEventParameter_P021400) */
1, /* Start Index of Event Id 144 (DemConf_DemEventParameter_DemEventParameter_P021500) */
1, /* Start Index of Event Id 145 (DemConf_DemEventParameter_DemEventParameter_P021600) */
1, /* Start Index of Event Id 146 (DemConf_DemEventParameter_DemEventParameter_P021700) */
1, /* Start Index of Event Id 147 (DemConf_DemEventParameter_DemEventParameter_P021800) */
1, /* Start Index of Event Id 148 (DemConf_DemEventParameter_DemEventParameter_P021900) */
1, /* Start Index of Event Id 149 (DemConf_DemEventParameter_DemEventParameter_P022000) */
1, /* Start Index of Event Id 150 (DemConf_DemEventParameter_DemEventParameter_P022100) */
1, /* Start Index of Event Id 151 (DemConf_DemEventParameter_DemEventParameter_P022200) */
1, /* Start Index of Event Id 152 (DemConf_DemEventParameter_DemEventParameter_P022300) */
1, /* Start Index of Event Id 153 (DemConf_DemEventParameter_DemEventParameter_P022400) */
1, /* Start Index of Event Id 154 (DemConf_DemEventParameter_DemEventParameter_P022500) */
1, /* Start Index of Event Id 155 (DemConf_DemEventParameter_DemEventParameter_P022600) */
1, /* Start Index of Event Id 156 (DemConf_DemEventParameter_DemEventParameter_P022700) */
1, /* Start Index of Event Id 157 (DemConf_DemEventParameter_DemEventParameter_P022800) */
1, /* Start Index of Event Id 158 (DemConf_DemEventParameter_DemEventParameter_P022900) */
1, /* Start Index of Event Id 159 (DemConf_DemEventParameter_DemEventParameter_P023000) */
1, /* Start Index of Event Id 160 (DemConf_DemEventParameter_DemEventParameter_P023100) */
1, /* Start Index of Event Id 161 (DemConf_DemEventParameter_DemEventParameter_P023200) */
1, /* Start Index of Event Id 162 (DemConf_DemEventParameter_DemEventParameter_P023300) */
1, /* Start Index of Event Id 163 (DemConf_DemEventParameter_DemEventParameter_P023400) */
1, /* Start Index of Event Id 164 (DemConf_DemEventParameter_DemEventParameter_P023500) */
1, /* Start Index of Event Id 165 (DemConf_DemEventParameter_DemEventParameter_P023600) */
1, /* Start Index of Event Id 166 (DemConf_DemEventParameter_DemEventParameter_P023700) */
1, /* Start Index of Event Id 167 (DemConf_DemEventParameter_DemEventParameter_P023800) */
1, /* Start Index of Event Id 168 (DemConf_DemEventParameter_DemEventParameter_P023900) */
1, /* Start Index of Event Id 169 (DemConf_DemEventParameter_DemEventParameter_P024000) */
1, /* Start Index of Event Id 170 (DemConf_DemEventParameter_DemEventParameter_P0241F0) */
1, /* Start Index of Event Id 171 (DemConf_DemEventParameter_DemEventParameter_P0242F1) */
1, /* Start Index of Event Id 172 (DemConf_DemEventParameter_DemEventParameter_P0243F0) */
1, /* Start Index of Event Id 173 (DemConf_DemEventParameter_DemEventParameter_P024400) */
1, /* Start Index of Event Id 174 (DemConf_DemEventParameter_DemEventParameter_P024500) */
1, /* Start Index of Event Id 175 (DemConf_DemEventParameter_DemEventParameter_P024600) */
1, /* Start Index of Event Id 176 (DemConf_DemEventParameter_DemEventParameter_P024700) */
1, /* Start Index of Event Id 177 (DemConf_DemEventParameter_DemEventParameter_P024800) */
1, /* Start Index of Event Id 178 (DemConf_DemEventParameter_DemEventParameter_P024900) */
1, /* Start Index of Event Id 179 (DemConf_DemEventParameter_DemEventParameter_P025000) */
1, /* Start Index of Event Id 180 (DemConf_DemEventParameter_DemEventParameter_P025100) */
1, /* Start Index of Event Id 181 (DemConf_DemEventParameter_DemEventParameter_P025200) */
1, /* Start Index of Event Id 182 (DemConf_DemEventParameter_DemEventParameter_P025300) */
1, /* Start Index of Event Id 183 (DemConf_DemEventParameter_DemEventParameter_P025400) */
1, /* Start Index of Event Id 184 (DemConf_DemEventParameter_DemEventParameter_P025500) */
1, /* Start Index of Event Id 185 (DemConf_DemEventParameter_DemEventParameter_P025600) */
1, /* Start Index of Event Id 186 (DemConf_DemEventParameter_DemEventParameter_U010100) */
1, /* Start Index of Event Id 187 (DemConf_DemEventParameter_DemEventParameter_U010200) */
1, /* Start Index of Event Id 188 (DemConf_DemEventParameter_DemEventParameter_U010300) */
1, /* Start Index of Event Id 189 (DemConf_DemEventParameter_DemEventParameter_U010400) */
1, /* Start Index of Event Id 190 (DemConf_DemEventParameter_DemEventParameter_U010500) */
1, /* Start Index of Event Id 191 (DemConf_DemEventParameter_DemEventParameter_U010600) */
1, /* Start Index of Event Id 192 (DemConf_DemEventParameter_DemEventParameter_U010700) */
1, /* Start Index of Event Id 193 (DemConf_DemEventParameter_DemEventParameter_U010800) */
1, /* Start Index of Event Id 194 (DemConf_DemEventParameter_DemEventParameter_U010900) */
1, /* Start Index of Event Id 195 (DemConf_DemEventParameter_DemEventParameter_U011000) */
1, /* Start Index of Event Id 196 (DemConf_DemEventParameter_DemEventParameter_U011100) */
1, /* Start Index of Event Id 197 (DemConf_DemEventParameter_DemEventParameter_U011200) */
1, /* Start Index of Event Id 198 (DemConf_DemEventParameter_DemEventParameter_U011300) */
1, /* Start Index of Event Id 199 (DemConf_DemEventParameter_DemEventParameter_U011400) */
1, /* Start Index of Event Id 200 (DemConf_DemEventParameter_DemEventParameter_U011500) */
1, /* Start Index of Event Id 201 (DemConf_DemEventParameter_DemEventParameter_U011600) */
1, /* Start Index of Event Id 202 (DemConf_DemEventParameter_DemEventParameter_U011700) */
1, /* Start Index of Event Id 203 (DemConf_DemEventParameter_DemEventParameter_U011800) */
1, /* Start Index of Event Id 204 (DemConf_DemEventParameter_DemEventParameter_U011900) */
1, /* Start Index of Event Id 205 (DemConf_DemEventParameter_DemEventParameter_U012000) */
1, /* Start Index of Event Id 206 (DemConf_DemEventParameter_DemEventParameter_U012100) */
1, /* Start Index of Event Id 207 (DemConf_DemEventParameter_DemEventParameter_U012288) */
1 /* Last Element denotes the invalid event Id */
};

const FiM_NumOffsetComponentType FiM_Cfg_NumOffsetComponent_auo[FIM_CFG_NUMBEROFDEMCOMPONENTIDS
		+ 2] = { 0, /* Element 0 denotes the invalid component Id */
0, /* Start Index of Component Id 1 (DemConf_DemComponent_DemComponent_P0101F0) */
1, /* Start Index of Component Id 2 (DemConf_DemComponent_DemComponent_P0101F1) */
1, /* Start Index of Component Id 3 (DemConf_DemComponent_DemComponent_P0102F0) */
1, /* Start Index of Component Id 4 (DemConf_DemComponent_DemComponent_P0102F1) */
1, /* Start Index of Component Id 5 (DemConf_DemComponent_DemComponent_P010300) */
1, /* Start Index of Component Id 6 (DemConf_DemComponent_DemComponent_P010400) */
1, /* Start Index of Component Id 7 (DemConf_DemComponent_DemComponent_P010500) */
1, /* Start Index of Component Id 8 (DemConf_DemComponent_DemComponent_P010600) */
1, /* Start Index of Component Id 9 (DemConf_DemComponent_DemComponent_P010700) */
1, /* Start Index of Component Id 10 (DemConf_DemComponent_DemComponent_P010800) */
1, /* Start Index of Component Id 11 (DemConf_DemComponent_DemComponent_P010900) */
1, /* Start Index of Component Id 12 (DemConf_DemComponent_DemComponent_P011000) */
1, /* Start Index of Component Id 13 (DemConf_DemComponent_DemComponent_P011100) */
1, /* Start Index of Component Id 14 (DemConf_DemComponent_DemComponent_P011200) */
1, /* Start Index of Component Id 15 (DemConf_DemComponent_DemComponent_P011300) */
1, /* Start Index of Component Id 16 (DemConf_DemComponent_DemComponent_P011400) */
1, /* Start Index of Component Id 17 (DemConf_DemComponent_DemComponent_P011500) */
1, /* Start Index of Component Id 18 (DemConf_DemComponent_DemComponent_P011600) */
1, /* Start Index of Component Id 19 (DemConf_DemComponent_DemComponent_P0117F0) */
1, /* Start Index of Component Id 20 (DemConf_DemComponent_DemComponent_P0117F1) */
1, /* Start Index of Component Id 21 (DemConf_DemComponent_DemComponent_P0117F2) */
1, /* Start Index of Component Id 22 (DemConf_DemComponent_DemComponent_P0118F0) */
1, /* Start Index of Component Id 23 (DemConf_DemComponent_DemComponent_P0118F1) */
1, /* Start Index of Component Id 24 (DemConf_DemComponent_DemComponent_P0118F2) */
1, /* Start Index of Component Id 25 (DemConf_DemComponent_DemComponent_P0119F0) */
1, /* Start Index of Component Id 26 (DemConf_DemComponent_DemComponent_P0119F1) */
1, /* Start Index of Component Id 27 (DemConf_DemComponent_DemComponent_P0119F2) */
1, /* Start Index of Component Id 28 (DemConf_DemComponent_DemComponent_P0120F0) */
1, /* Start Index of Component Id 29 (DemConf_DemComponent_DemComponent_P0120F1) */
1, /* Start Index of Component Id 30 (DemConf_DemComponent_DemComponent_P0120F2) */
1, /* Start Index of Component Id 31 (DemConf_DemComponent_DemComponent_P0121F0) */
1, /* Start Index of Component Id 32 (DemConf_DemComponent_DemComponent_P0121F1) */
1, /* Start Index of Component Id 33 (DemConf_DemComponent_DemComponent_P0121F2) */
1, /* Start Index of Component Id 34 (DemConf_DemComponent_DemComponent_P0122F0) */
1, /* Start Index of Component Id 35 (DemConf_DemComponent_DemComponent_P0122F1) */
1, /* Start Index of Component Id 36 (DemConf_DemComponent_DemComponent_P0122F2) */
1, /* Start Index of Component Id 37 (DemConf_DemComponent_DemComponent_P0123F0) */
1, /* Start Index of Component Id 38 (DemConf_DemComponent_DemComponent_P0123F1) */
1, /* Start Index of Component Id 39 (DemConf_DemComponent_DemComponent_P0123F2) */
1, /* Start Index of Component Id 40 (DemConf_DemComponent_DemComponent_P012400) */
1, /* Start Index of Component Id 41 (DemConf_DemComponent_DemComponent_P012500) */
1, /* Start Index of Component Id 42 (DemConf_DemComponent_DemComponent_P012600) */
1, /* Start Index of Component Id 43 (DemConf_DemComponent_DemComponent_P012700) */
1, /* Start Index of Component Id 44 (DemConf_DemComponent_DemComponent_P012800) */
1, /* Start Index of Component Id 45 (DemConf_DemComponent_DemComponent_P012801) */
1, /* Start Index of Component Id 46 (DemConf_DemComponent_DemComponent_P012900) */
1, /* Start Index of Component Id 47 (DemConf_DemComponent_DemComponent_P013000) */
1, /* Start Index of Component Id 48 (DemConf_DemComponent_DemComponent_P013100) */
1, /* Start Index of Component Id 49 (DemConf_DemComponent_DemComponent_P013200) */
1, /* Start Index of Component Id 50 (DemConf_DemComponent_DemComponent_P013300) */
1, /* Start Index of Component Id 51 (DemConf_DemComponent_DemComponent_P013400) */
1, /* Start Index of Component Id 52 (DemConf_DemComponent_DemComponent_P0135F0) */
1, /* Start Index of Component Id 53 (DemConf_DemComponent_DemComponent_P0135F1) */
1, /* Start Index of Component Id 54 (DemConf_DemComponent_DemComponent_P0135F2) */
1, /* Start Index of Component Id 55 (DemConf_DemComponent_DemComponent_P0136F0) */
1, /* Start Index of Component Id 56 (DemConf_DemComponent_DemComponent_P0136F1) */
1, /* Start Index of Component Id 57 (DemConf_DemComponent_DemComponent_P0136F2) */
1, /* Start Index of Component Id 58 (DemConf_DemComponent_DemComponent_P0137F0) */
1, /* Start Index of Component Id 59 (DemConf_DemComponent_DemComponent_P0137F1) */
1, /* Start Index of Component Id 60 (DemConf_DemComponent_DemComponent_P0137F2) */
1, /* Start Index of Component Id 61 (DemConf_DemComponent_DemComponent_P013800) */
1, /* Start Index of Component Id 62 (DemConf_DemComponent_DemComponent_P013900) */
1, /* Start Index of Component Id 63 (DemConf_DemComponent_DemComponent_P014000) */
1, /* Start Index of Component Id 64 (DemConf_DemComponent_DemComponent_P014100) */
1, /* Start Index of Component Id 65 (DemConf_DemComponent_DemComponent_P014200) */
1, /* Start Index of Component Id 66 (DemConf_DemComponent_DemComponent_P014300) */
1, /* Start Index of Component Id 67 (DemConf_DemComponent_DemComponent_P014400) */
1, /* Start Index of Component Id 68 (DemConf_DemComponent_DemComponent_P014500) */
1, /* Start Index of Component Id 69 (DemConf_DemComponent_DemComponent_P014600) */
1, /* Start Index of Component Id 70 (DemConf_DemComponent_DemComponent_P014700) */
1, /* Start Index of Component Id 71 (DemConf_DemComponent_DemComponent_P014800) */
1, /* Start Index of Component Id 72 (DemConf_DemComponent_DemComponent_P014900) */
1, /* Start Index of Component Id 73 (DemConf_DemComponent_DemComponent_P015000) */
1, /* Start Index of Component Id 74 (DemConf_DemComponent_DemComponent_P015100) */
1, /* Start Index of Component Id 75 (DemConf_DemComponent_DemComponent_P015200) */
1, /* Start Index of Component Id 76 (DemConf_DemComponent_DemComponent_P015300) */
1, /* Start Index of Component Id 77 (DemConf_DemComponent_DemComponent_P015400) */
1, /* Start Index of Component Id 78 (DemConf_DemComponent_DemComponent_P015500) */
1, /* Start Index of Component Id 79 (DemConf_DemComponent_DemComponent_P015600) */
1, /* Start Index of Component Id 80 (DemConf_DemComponent_DemComponent_P015700) */
1, /* Start Index of Component Id 81 (DemConf_DemComponent_DemComponent_P015800) */
1, /* Start Index of Component Id 82 (DemConf_DemComponent_DemComponent_P015900) */
1, /* Start Index of Component Id 83 (DemConf_DemComponent_DemComponent_P016000) */
1, /* Start Index of Component Id 84 (DemConf_DemComponent_DemComponent_P016100) */
1, /* Start Index of Component Id 85 (DemConf_DemComponent_DemComponent_P016200) */
1, /* Start Index of Component Id 86 (DemConf_DemComponent_DemComponent_P016300) */
1, /* Start Index of Component Id 87 (DemConf_DemComponent_DemComponent_P016400) */
1, /* Start Index of Component Id 88 (DemConf_DemComponent_DemComponent_P016500) */
1, /* Start Index of Component Id 89 (DemConf_DemComponent_DemComponent_P016600) */
1, /* Start Index of Component Id 90 (DemConf_DemComponent_DemComponent_P016700) */
1, /* Start Index of Component Id 91 (DemConf_DemComponent_DemComponent_P016800) */
1, /* Start Index of Component Id 92 (DemConf_DemComponent_DemComponent_P016900) */
1, /* Start Index of Component Id 93 (DemConf_DemComponent_DemComponent_P017000) */
1, /* Start Index of Component Id 94 (DemConf_DemComponent_DemComponent_P017100) */
1, /* Start Index of Component Id 95 (DemConf_DemComponent_DemComponent_P017200) */
1, /* Start Index of Component Id 96 (DemConf_DemComponent_DemComponent_P017300) */
1, /* Start Index of Component Id 97 (DemConf_DemComponent_DemComponent_P017400) */
1, /* Start Index of Component Id 98 (DemConf_DemComponent_DemComponent_P017500) */
1, /* Start Index of Component Id 99 (DemConf_DemComponent_DemComponent_P017600) */
1, /* Start Index of Component Id 100 (DemConf_DemComponent_DemComponent_P017700) */
1, /* Start Index of Component Id 101 (DemConf_DemComponent_DemComponent_P017800) */
1, /* Start Index of Component Id 102 (DemConf_DemComponent_DemComponent_P017900) */
1, /* Start Index of Component Id 103 (DemConf_DemComponent_DemComponent_P018000) */
1, /* Start Index of Component Id 104 (DemConf_DemComponent_DemComponent_P018100) */
1, /* Start Index of Component Id 105 (DemConf_DemComponent_DemComponent_P018200) */
1, /* Start Index of Component Id 106 (DemConf_DemComponent_DemComponent_P018300) */
1, /* Start Index of Component Id 107 (DemConf_DemComponent_DemComponent_P018400) */
1, /* Start Index of Component Id 108 (DemConf_DemComponent_DemComponent_P018500) */
1, /* Start Index of Component Id 109 (DemConf_DemComponent_DemComponent_P018600) */
1, /* Start Index of Component Id 110 (DemConf_DemComponent_DemComponent_P018700) */
1, /* Start Index of Component Id 111 (DemConf_DemComponent_DemComponent_P018800) */
1, /* Start Index of Component Id 112 (DemConf_DemComponent_DemComponent_P018900) */
1, /* Start Index of Component Id 113 (DemConf_DemComponent_DemComponent_P019000) */
1, /* Start Index of Component Id 114 (DemConf_DemComponent_DemComponent_P019100) */
1, /* Start Index of Component Id 115 (DemConf_DemComponent_DemComponent_P019200) */
1, /* Start Index of Component Id 116 (DemConf_DemComponent_DemComponent_P019300) */
1, /* Start Index of Component Id 117 (DemConf_DemComponent_DemComponent_P019400) */
1, /* Start Index of Component Id 118 (DemConf_DemComponent_DemComponent_P019500) */
1, /* Start Index of Component Id 119 (DemConf_DemComponent_DemComponent_P019600) */
1, /* Start Index of Component Id 120 (DemConf_DemComponent_DemComponent_P019700) */
1, /* Start Index of Component Id 121 (DemConf_DemComponent_DemComponent_P019800) */
1, /* Start Index of Component Id 122 (DemConf_DemComponent_DemComponent_P019900) */
1, /* Start Index of Component Id 123 (DemConf_DemComponent_DemComponent_P020000) */
1, /* Start Index of Component Id 124 (DemConf_DemComponent_DemComponent_P020100) */
1, /* Start Index of Component Id 125 (DemConf_DemComponent_DemComponent_P020200) */
1, /* Start Index of Component Id 126 (DemConf_DemComponent_DemComponent_P020300) */
1, /* Start Index of Component Id 127 (DemConf_DemComponent_DemComponent_P020400) */
1, /* Start Index of Component Id 128 (DemConf_DemComponent_DemComponent_P020500) */
1, /* Start Index of Component Id 129 (DemConf_DemComponent_DemComponent_P020600) */
1, /* Start Index of Component Id 130 (DemConf_DemComponent_DemComponent_P020700) */
1, /* Start Index of Component Id 131 (DemConf_DemComponent_DemComponent_P020800) */
1, /* Start Index of Component Id 132 (DemConf_DemComponent_DemComponent_P020900) */
1, /* Start Index of Component Id 133 (DemConf_DemComponent_DemComponent_P021000) */
1, /* Start Index of Component Id 134 (DemConf_DemComponent_DemComponent_P021100) */
1, /* Start Index of Component Id 135 (DemConf_DemComponent_DemComponent_P021200) */
1, /* Start Index of Component Id 136 (DemConf_DemComponent_DemComponent_P021300) */
1, /* Start Index of Component Id 137 (DemConf_DemComponent_DemComponent_P021400) */
1, /* Start Index of Component Id 138 (DemConf_DemComponent_DemComponent_P021500) */
1, /* Start Index of Component Id 139 (DemConf_DemComponent_DemComponent_P021600) */
1, /* Start Index of Component Id 140 (DemConf_DemComponent_DemComponent_P021700) */
1, /* Start Index of Component Id 141 (DemConf_DemComponent_DemComponent_P021800) */
1, /* Start Index of Component Id 142 (DemConf_DemComponent_DemComponent_P021900) */
1, /* Start Index of Component Id 143 (DemConf_DemComponent_DemComponent_P022000) */
1, /* Start Index of Component Id 144 (DemConf_DemComponent_DemComponent_P022100) */
1, /* Start Index of Component Id 145 (DemConf_DemComponent_DemComponent_P022200) */
1, /* Start Index of Component Id 146 (DemConf_DemComponent_DemComponent_P022300) */
1, /* Start Index of Component Id 147 (DemConf_DemComponent_DemComponent_P022400) */
1, /* Start Index of Component Id 148 (DemConf_DemComponent_DemComponent_P022500) */
1, /* Start Index of Component Id 149 (DemConf_DemComponent_DemComponent_P022600) */
1, /* Start Index of Component Id 150 (DemConf_DemComponent_DemComponent_P022700) */
1, /* Start Index of Component Id 151 (DemConf_DemComponent_DemComponent_P022800) */
1, /* Start Index of Component Id 152 (DemConf_DemComponent_DemComponent_P022900) */
1, /* Start Index of Component Id 153 (DemConf_DemComponent_DemComponent_P023000) */
1, /* Start Index of Component Id 154 (DemConf_DemComponent_DemComponent_P023100) */
1, /* Start Index of Component Id 155 (DemConf_DemComponent_DemComponent_P023200) */
1, /* Start Index of Component Id 156 (DemConf_DemComponent_DemComponent_P023300) */
1, /* Start Index of Component Id 157 (DemConf_DemComponent_DemComponent_P023400) */
1, /* Start Index of Component Id 158 (DemConf_DemComponent_DemComponent_P023500) */
1, /* Start Index of Component Id 159 (DemConf_DemComponent_DemComponent_P023600) */
1, /* Start Index of Component Id 160 (DemConf_DemComponent_DemComponent_P023700) */
1, /* Start Index of Component Id 161 (DemConf_DemComponent_DemComponent_P023800) */
1, /* Start Index of Component Id 162 (DemConf_DemComponent_DemComponent_P023900) */
1, /* Start Index of Component Id 163 (DemConf_DemComponent_DemComponent_P024000) */
1, /* Start Index of Component Id 164 (DemConf_DemComponent_DemComponent_P0241F0) */
1, /* Start Index of Component Id 165 (DemConf_DemComponent_DemComponent_P0242F1) */
1, /* Start Index of Component Id 166 (DemConf_DemComponent_DemComponent_P0243F0) */
1, /* Start Index of Component Id 167 (DemConf_DemComponent_DemComponent_P024400) */
1, /* Start Index of Component Id 168 (DemConf_DemComponent_DemComponent_P024500) */
1, /* Start Index of Component Id 169 (DemConf_DemComponent_DemComponent_P024600) */
1, /* Start Index of Component Id 170 (DemConf_DemComponent_DemComponent_P024700) */
1, /* Start Index of Component Id 171 (DemConf_DemComponent_DemComponent_P024800) */
1, /* Start Index of Component Id 172 (DemConf_DemComponent_DemComponent_P024900) */
1, /* Start Index of Component Id 173 (DemConf_DemComponent_DemComponent_P025000) */
1, /* Start Index of Component Id 174 (DemConf_DemComponent_DemComponent_P025100) */
1, /* Start Index of Component Id 175 (DemConf_DemComponent_DemComponent_P025200) */
1, /* Start Index of Component Id 176 (DemConf_DemComponent_DemComponent_P025300) */
1, /* Start Index of Component Id 177 (DemConf_DemComponent_DemComponent_P025400) */
1, /* Start Index of Component Id 178 (DemConf_DemComponent_DemComponent_P025500) */
1, /* Start Index of Component Id 179 (DemConf_DemComponent_DemComponent_P025600) */
1, /* Start Index of Component Id 180 (DemConf_DemComponent_DemComponent_U010100) */
1, /* Start Index of Component Id 181 (DemConf_DemComponent_DemComponent_U010200) */
1, /* Start Index of Component Id 182 (DemConf_DemComponent_DemComponent_U010300) */
1, /* Start Index of Component Id 183 (DemConf_DemComponent_DemComponent_U010400) */
1, /* Start Index of Component Id 184 (DemConf_DemComponent_DemComponent_U010500) */
1, /* Start Index of Component Id 185 (DemConf_DemComponent_DemComponent_U010600) */
1, /* Start Index of Component Id 186 (DemConf_DemComponent_DemComponent_U010700) */
1, /* Start Index of Component Id 187 (DemConf_DemComponent_DemComponent_U010800) */
1, /* Start Index of Component Id 188 (DemConf_DemComponent_DemComponent_U010900) */
1, /* Start Index of Component Id 189 (DemConf_DemComponent_DemComponent_U011000) */
1, /* Start Index of Component Id 190 (DemConf_DemComponent_DemComponent_U011100) */
1, /* Start Index of Component Id 191 (DemConf_DemComponent_DemComponent_U011200) */
1, /* Start Index of Component Id 192 (DemConf_DemComponent_DemComponent_U011300) */
1, /* Start Index of Component Id 193 (DemConf_DemComponent_DemComponent_U011400) */
1, /* Start Index of Component Id 194 (DemConf_DemComponent_DemComponent_U011500) */
1, /* Start Index of Component Id 195 (DemConf_DemComponent_DemComponent_U011600) */
1, /* Start Index of Component Id 196 (DemConf_DemComponent_DemComponent_U011700) */
1, /* Start Index of Component Id 197 (DemConf_DemComponent_DemComponent_U011800) */
1, /* Start Index of Component Id 198 (DemConf_DemComponent_DemComponent_U011900) */
1, /* Start Index of Component Id 199 (DemConf_DemComponent_DemComponent_U012000) */
1, /* Start Index of Component Id 200 (DemConf_DemComponent_DemComponent_U012100) */
1, /* Start Index of Component Id 201 (DemConf_DemComponent_DemComponent_U012288) */
1 /* Last Element denotes the invalid component Id */
};

/*
 ***************************************************************************************************
 * inhibit matrix - FID for events
 ***************************************************************************************************
 */
#define FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC    (1)
const FiM_FunctionIdType FiM_CfgInhibitSourceMatrix_au16[FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC] =
		{
		/* <----- Fim_FIds -----> */

		/* DemEvent 0: no FIds available */

		/* DemEvent 0: no FIds available */

		/* DemEvent 0: no FIds available */

		/* DemEvent 0: no FIds available */

		/* DemEvent 0: no FIds available */

		/* DemEvent 0: no FIds available */

		// DemConf_DemEventParameter_DemEventParameter_P0101F0 0 - 0 
				FiMConf_FiMFID_FiMFID_0

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */

		/* DemEvent 1: no FIds available */
		};

/*
 ***************************************************************************************************
 * inhibit matrix - mask for events
 ***************************************************************************************************
 */
const FiM_InhibitionMaskType FiM_CfgInhibitMaskMatrix_au16[FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC] =
		{
		/* <----- Fid->DemEvent Inhibit mask -----> */

		/* DemEvent 0: no inhibition mask available */

		/* DemEvent 0: no inhibition mask available */

		/* DemEvent 0: no inhibition mask available */

		/* DemEvent 0: no inhibition mask available */

		/* DemEvent 0: no inhibition mask available */

		/* DemEvent 0: no inhibition mask available */

		// DemEventParameter_P0101F0 0 - 0 
				FIM_CFG_LAST_FAILED

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */

		/* DemEvent 1: no inhibition mask available */
		};

/*
 ***************************************************************************************************
 * inhibit matrix - FID for components
 ***************************************************************************************************
 */
const FiM_FunctionIdType FiM_CfgInhibitSourceMatrixComponent_au16[FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC] =
		{
		/* <----- Fim_FIds -----> */

		// DemConf_DemComponent_DemComponent_P0101F0 0 - 0 
				FiMConf_FiMFID_FiMFID_0

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */

		/* DemComponent 1: no FIds available */
		};

const FiM_ConfigType FiMConfigSet =
		{ FiM_Cfg_NumOffsetEvent_auo, FiM_CfgInhibitSourceMatrix_au16,
				FiM_CfgInhibitMaskMatrix_au16, FiM_Cfg_NumOffsetComponent_auo,
				FiM_CfgInhibitSourceMatrixComponent_au16 };

#define FIM_STOP_SEC_ROM_CONST
#include "FiM_MemMap.h"

