

#ifndef DEM_DEBSHARING_H
#define DEM_DEBSHARING_H


/* FC_VariationPoint_START */

/*
 * Debouncer is restructured to simplify re-use in DGS implementation. Following constraints have to be considered.
 *
 * Reuse of debouncer files in DGS implementation:
 * Dem_Deb.c -> remove
 * Dem_Deb.h -> replace with specific implementation: reduce to #include section
 * Dem_DebArCounter.c -> copy
 * Dem_DebArCounter.h -> copy
 * Dem_DebArTime.c -> copy
 * Dem_DebArTime.h -> copy
 * Dem_DebCtrBaseClass.c -> copy
 * Dem_DebCtrBaseClass.h -> copy
 * Dem_DebBase.c -> copy
 * Dem_DebBase.h -> copy
 * Dem_DebMonInternal.h -> copy
 * Dem_DebSharing.h -> specific implementation in CDG and DGS
 *
 * Stubbing using defines:
 * - create empty define DEM_CFG_DEB_DEFINE_ALL_PARAMSETS
 * - use DEM_DEB_FORCE_CONST_CONFIG to make Dem_Cfg_DebClasses const
 * - use DEM_DEB_LOCAL_CALC_PARAMS to define parameters
 * - set #defines of double include protection to remove unwanted header content
 *
 */

/* FC_VariationPoint_END */


#define DEM_DEB_LOCAL_CALC_PARAMS


#endif

