/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_NODES_H
#define DEM_CFG_NODES_H

/* ---------------------------------------- */
/* DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE  */
/* ---------------------------------------- */
#define DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE_OFF  STD_OFF
#define DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE_ON   STD_ON
#define DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE  DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE_OFF

/* ---------------------------------------- */
/* DEM_CFG_DEPRECOVERYLIMIT                 */
/* ---------------------------------------- */
#define DEM_CFG_DEPRECOVERYLIMIT_OFF  STD_OFF
#define DEM_CFG_DEPRECOVERYLIMIT_ON   STD_ON
#define DEM_CFG_DEPRECOVERYLIMIT  DEM_CFG_DEPRECOVERYLIMIT_OFF

#define DEM_CFG_DEPENDENCY_PENDING_ON             FALSE

#define DEM_CFG_FAILUREDEPENDENCY_RECHECK_LIMIT  80u

/*                  ALLOWEDRECOVERIES             IGNORESPRIO    FAILEDCALLBACK_IDX                       */

#define DEM_CFG_NODEPARAMS \
{ \
    DEM_NODES_INIT (DEM_NODE_INFINITE_RECOVERIES, 0,             0                                       ) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0101F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0101F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0102F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0102F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0117F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0117F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0117F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0118F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0118F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0118F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0119F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0119F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0119F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0120F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0120F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0120F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0121F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0121F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0121F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0122F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0122F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0122F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0123F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0123F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0123F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012801_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0135F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0135F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0135F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0136F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0136F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0136F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0137F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0137F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0137F2_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0241F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0242F1_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0243F0_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011200_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011300_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011400_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011500_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011600_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011700_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011800_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011900_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U012000_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U012100_ComponentStatusChanged_IDX) \
   ,DEM_NODES_INIT (5,                            0,             DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U012288_ComponentStatusChanged_IDX) \
}

#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0101F0_ComponentStatusChanged_IDX    1
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0101F1_ComponentStatusChanged_IDX    2
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0102F0_ComponentStatusChanged_IDX    3
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0102F1_ComponentStatusChanged_IDX    4
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010300_ComponentStatusChanged_IDX    5
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010400_ComponentStatusChanged_IDX    6
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010500_ComponentStatusChanged_IDX    7
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010600_ComponentStatusChanged_IDX    8
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010700_ComponentStatusChanged_IDX    9
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010800_ComponentStatusChanged_IDX    10
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P010900_ComponentStatusChanged_IDX    11
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011000_ComponentStatusChanged_IDX    12
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011100_ComponentStatusChanged_IDX    13
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011200_ComponentStatusChanged_IDX    14
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011300_ComponentStatusChanged_IDX    15
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011400_ComponentStatusChanged_IDX    16
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011500_ComponentStatusChanged_IDX    17
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P011600_ComponentStatusChanged_IDX    18
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0117F0_ComponentStatusChanged_IDX    19
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0117F1_ComponentStatusChanged_IDX    20
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0117F2_ComponentStatusChanged_IDX    21
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010100_ComponentStatusChanged_IDX    22
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010200_ComponentStatusChanged_IDX    23
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010300_ComponentStatusChanged_IDX    24
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010400_ComponentStatusChanged_IDX    25
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010500_ComponentStatusChanged_IDX    26
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010600_ComponentStatusChanged_IDX    27
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010700_ComponentStatusChanged_IDX    28
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010800_ComponentStatusChanged_IDX    29
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U010900_ComponentStatusChanged_IDX    30
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011000_ComponentStatusChanged_IDX    31
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0118F0_ComponentStatusChanged_IDX    32
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0118F1_ComponentStatusChanged_IDX    33
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0118F2_ComponentStatusChanged_IDX    34
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011100_ComponentStatusChanged_IDX    35
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0119F0_ComponentStatusChanged_IDX    36
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0119F1_ComponentStatusChanged_IDX    37
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0119F2_ComponentStatusChanged_IDX    38
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011200_ComponentStatusChanged_IDX    39
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0120F0_ComponentStatusChanged_IDX    40
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0120F1_ComponentStatusChanged_IDX    41
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0120F2_ComponentStatusChanged_IDX    42
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011300_ComponentStatusChanged_IDX    43
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0121F0_ComponentStatusChanged_IDX    44
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0121F1_ComponentStatusChanged_IDX    45
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0121F2_ComponentStatusChanged_IDX    46
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011400_ComponentStatusChanged_IDX    47
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0122F0_ComponentStatusChanged_IDX    48
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0122F1_ComponentStatusChanged_IDX    49
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0122F2_ComponentStatusChanged_IDX    50
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011500_ComponentStatusChanged_IDX    51
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0123F0_ComponentStatusChanged_IDX    52
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0123F1_ComponentStatusChanged_IDX    53
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0123F2_ComponentStatusChanged_IDX    54
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011600_ComponentStatusChanged_IDX    55
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012400_ComponentStatusChanged_IDX    56
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012500_ComponentStatusChanged_IDX    57
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012600_ComponentStatusChanged_IDX    58
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012700_ComponentStatusChanged_IDX    59
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012800_ComponentStatusChanged_IDX    60
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011700_ComponentStatusChanged_IDX    61
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011800_ComponentStatusChanged_IDX    62
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U011900_ComponentStatusChanged_IDX    63
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012801_ComponentStatusChanged_IDX    64
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P012900_ComponentStatusChanged_IDX    65
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013000_ComponentStatusChanged_IDX    66
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013100_ComponentStatusChanged_IDX    67
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013200_ComponentStatusChanged_IDX    68
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013300_ComponentStatusChanged_IDX    69
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013400_ComponentStatusChanged_IDX    70
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0135F0_ComponentStatusChanged_IDX    71
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0135F1_ComponentStatusChanged_IDX    72
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0135F2_ComponentStatusChanged_IDX    73
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0136F0_ComponentStatusChanged_IDX    74
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0136F1_ComponentStatusChanged_IDX    75
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0136F2_ComponentStatusChanged_IDX    76
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0137F0_ComponentStatusChanged_IDX    77
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0137F1_ComponentStatusChanged_IDX    78
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0137F2_ComponentStatusChanged_IDX    79
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013800_ComponentStatusChanged_IDX    80
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P013900_ComponentStatusChanged_IDX    81
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014000_ComponentStatusChanged_IDX    82
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014100_ComponentStatusChanged_IDX    83
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014200_ComponentStatusChanged_IDX    84
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014300_ComponentStatusChanged_IDX    85
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014400_ComponentStatusChanged_IDX    86
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014500_ComponentStatusChanged_IDX    87
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014600_ComponentStatusChanged_IDX    88
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014700_ComponentStatusChanged_IDX    89
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014800_ComponentStatusChanged_IDX    90
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P014900_ComponentStatusChanged_IDX    91
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015000_ComponentStatusChanged_IDX    92
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015100_ComponentStatusChanged_IDX    93
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015200_ComponentStatusChanged_IDX    94
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015300_ComponentStatusChanged_IDX    95
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015400_ComponentStatusChanged_IDX    96
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015500_ComponentStatusChanged_IDX    97
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015600_ComponentStatusChanged_IDX    98
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015700_ComponentStatusChanged_IDX    99
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015800_ComponentStatusChanged_IDX    100
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P015900_ComponentStatusChanged_IDX    101
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016000_ComponentStatusChanged_IDX    102
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016100_ComponentStatusChanged_IDX    103
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016200_ComponentStatusChanged_IDX    104
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016300_ComponentStatusChanged_IDX    105
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016400_ComponentStatusChanged_IDX    106
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016500_ComponentStatusChanged_IDX    107
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016600_ComponentStatusChanged_IDX    108
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016700_ComponentStatusChanged_IDX    109
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016800_ComponentStatusChanged_IDX    110
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P016900_ComponentStatusChanged_IDX    111
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017000_ComponentStatusChanged_IDX    112
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017100_ComponentStatusChanged_IDX    113
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017200_ComponentStatusChanged_IDX    114
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017300_ComponentStatusChanged_IDX    115
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017400_ComponentStatusChanged_IDX    116
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017500_ComponentStatusChanged_IDX    117
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017600_ComponentStatusChanged_IDX    118
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017700_ComponentStatusChanged_IDX    119
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017800_ComponentStatusChanged_IDX    120
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P017900_ComponentStatusChanged_IDX    121
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018000_ComponentStatusChanged_IDX    122
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018100_ComponentStatusChanged_IDX    123
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018200_ComponentStatusChanged_IDX    124
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018300_ComponentStatusChanged_IDX    125
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018400_ComponentStatusChanged_IDX    126
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018500_ComponentStatusChanged_IDX    127
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018600_ComponentStatusChanged_IDX    128
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018700_ComponentStatusChanged_IDX    129
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018800_ComponentStatusChanged_IDX    130
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P018900_ComponentStatusChanged_IDX    131
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019000_ComponentStatusChanged_IDX    132
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019100_ComponentStatusChanged_IDX    133
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019200_ComponentStatusChanged_IDX    134
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019300_ComponentStatusChanged_IDX    135
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019400_ComponentStatusChanged_IDX    136
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019500_ComponentStatusChanged_IDX    137
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019600_ComponentStatusChanged_IDX    138
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019700_ComponentStatusChanged_IDX    139
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019800_ComponentStatusChanged_IDX    140
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P019900_ComponentStatusChanged_IDX    141
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020000_ComponentStatusChanged_IDX    142
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020100_ComponentStatusChanged_IDX    143
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020200_ComponentStatusChanged_IDX    144
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020300_ComponentStatusChanged_IDX    145
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020400_ComponentStatusChanged_IDX    146
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020500_ComponentStatusChanged_IDX    147
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020600_ComponentStatusChanged_IDX    148
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020700_ComponentStatusChanged_IDX    149
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020800_ComponentStatusChanged_IDX    150
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P020900_ComponentStatusChanged_IDX    151
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021000_ComponentStatusChanged_IDX    152
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021100_ComponentStatusChanged_IDX    153
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021200_ComponentStatusChanged_IDX    154
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021300_ComponentStatusChanged_IDX    155
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021400_ComponentStatusChanged_IDX    156
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021500_ComponentStatusChanged_IDX    157
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021600_ComponentStatusChanged_IDX    158
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021700_ComponentStatusChanged_IDX    159
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021800_ComponentStatusChanged_IDX    160
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P021900_ComponentStatusChanged_IDX    161
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022000_ComponentStatusChanged_IDX    162
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022100_ComponentStatusChanged_IDX    163
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022200_ComponentStatusChanged_IDX    164
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022300_ComponentStatusChanged_IDX    165
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022400_ComponentStatusChanged_IDX    166
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022500_ComponentStatusChanged_IDX    167
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022600_ComponentStatusChanged_IDX    168
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022700_ComponentStatusChanged_IDX    169
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022800_ComponentStatusChanged_IDX    170
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P022900_ComponentStatusChanged_IDX    171
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023000_ComponentStatusChanged_IDX    172
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023100_ComponentStatusChanged_IDX    173
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023200_ComponentStatusChanged_IDX    174
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023300_ComponentStatusChanged_IDX    175
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023400_ComponentStatusChanged_IDX    176
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023500_ComponentStatusChanged_IDX    177
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023600_ComponentStatusChanged_IDX    178
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023700_ComponentStatusChanged_IDX    179
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023800_ComponentStatusChanged_IDX    180
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P023900_ComponentStatusChanged_IDX    181
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024000_ComponentStatusChanged_IDX    182
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0241F0_ComponentStatusChanged_IDX    183
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0242F1_ComponentStatusChanged_IDX    184
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P0243F0_ComponentStatusChanged_IDX    185
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U012000_ComponentStatusChanged_IDX    186
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U012100_ComponentStatusChanged_IDX    187
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_U012288_ComponentStatusChanged_IDX    188
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024400_ComponentStatusChanged_IDX    189
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024500_ComponentStatusChanged_IDX    190
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024600_ComponentStatusChanged_IDX    191
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024700_ComponentStatusChanged_IDX    192
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024800_ComponentStatusChanged_IDX    193
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P024900_ComponentStatusChanged_IDX    194
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025000_ComponentStatusChanged_IDX    195
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025100_ComponentStatusChanged_IDX    196
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025200_ComponentStatusChanged_IDX    197
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025300_ComponentStatusChanged_IDX    198
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025400_ComponentStatusChanged_IDX    199
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025500_ComponentStatusChanged_IDX    200
#define  DEM_CFG_Rte_Call_Dem_CBStatusComp_DemComponent_P025600_ComponentStatusChanged_IDX    201

#define  DEM_CFG_NODEFAILEDCALLBACK_COUNT  201
#define  DEM_CFG_NODEFAILEDCALLBACK_ARRAYLENGTH  (DEM_CFG_NODEFAILEDCALLBACK_COUNT+1)

#define DEM_CFG_NODEFAILEDCALLBACKS \
{ \
	NULL_PTR \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0101F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0101F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0102F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0102F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P010300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P010400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P010500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P010600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P010700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P010800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P010900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P011000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P011100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P011200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P011300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P011400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P011500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P011600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0117F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0117F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0117F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U010900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0118F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0118F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0118F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0119F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0119F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0119F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0120F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0120F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0120F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0121F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0121F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0121F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0122F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0122F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0122F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0123F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0123F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0123F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P012400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P012500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P012600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P012700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P012800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U011900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P012801_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P012900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P013000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P013100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P013200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P013300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P013400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0135F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0135F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0135F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0136F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0136F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0136F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0137F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0137F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0137F2_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P013800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P013900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P014900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P015900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P016900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P017900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P018900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P019900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P020900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P021900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P022900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P023900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P024000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0241F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0242F1_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P0243F0_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U012000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U012100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_U012288_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P024400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P024500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P024600_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P024700_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P024800_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P024900_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P025000_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P025100_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P025200_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P025300_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P025400_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P025500_ComponentStatusChanged \
    ,&Rte_Call_Dem_CBStatusComp_DemComponent_P025600_ComponentStatusChanged \
}

#endif

