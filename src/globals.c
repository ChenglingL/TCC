#include "globals.h"
#include <stddef.h>
int box_type = 0;
int frames_to_analyse = 0;
int num_cluster_types = 0;



char *fXmolName = NULL, *fBoxSizeName = NULL;
long box_offsets[1000] = {0};
double *x = NULL, *y = NULL, *z = NULL;
int *particle_type = NULL;

double rcutAA = 0, rcutAA2 = 0, rcutAB = 0, rcutAB2 = 0, rcutBB = 0, rcutBB2 = 0;
double min_cutAA = 0, min_cutAA2 = 0;
double fc = 0;
int use_voronoi_bonds = 0;
int PBCs = 0;
int max_num_bonds = 0;
int use_cell_list = 0;
int analyse_all_clusters = 0;

int doWriteBonds = 0;
int doWriteClus = 0;
int doWriteRaw = 0;
int do11AcenXyz = 0;
int do13AcenXyz = 0;
int eleven_A_number = 0;
int thirteen_A_number = 0;
int doWritePopPerFrame = 0;
int doWriteXYZ = 0;

int incrStatic = 0;

double **pop_per_frame = NULL;
double *mean_pop_per_frame = NULL;
int *num_gross_particles = NULL;
int *total_clusters = NULL;

double sidex = 0, sidey = 0, sidez = 0, half_sidex = 0, half_sidey = 0, half_sidez = 0;
double tiltxy = 0, tiltxz = 0, tiltyz = 0;
long particles_in_current_frame = 0;

int *num_bonds = NULL;
int **bond_list = NULL;
double **squared_bondlengths = NULL;
int maxnb = 0;
int correctedBonds = 0;

int num_sort_columns = 0;

int n_cells_x = 0, n_cells_y = 0, n_cells_z = 0, n_cells_total = 0;
int *head = NULL;
int *linked_list = NULL;
double cell_len_x = 0, cell_len_y = 0, cell_len_z = 0;

// Cluster switches
int dosp3 = 0, dosp3a = 0, dosp3b = 0, dosp3c = 0;
int dosp4 = 0, dosp4a = 0, dosp4b = 0, dosp4c = 0;
int dosp5 = 0, dosp5a = 0, dosp5b = 0, dosp5c = 0;
int do6A = 0, do6Z = 0, do7K = 0, do7T_a = 0, do7T_s = 0;
int do8A = 0, do8B = 0, do8K = 0;
int do9A = 0, do9B = 0, do9K = 0;
int do10A = 0, do10B = 0, do10K = 0, do10W = 0;
int do11A = 0, do11B = 0, do11C = 0, do11E = 0, do11F = 0, do11W = 0;
int do12A = 0, do12B = 0, do12D = 0, do12E = 0, do12K = 0;
int do13A = 0, do13B = 0, do13K = 0;
int doFCC = 0, doHCP = 0, doBCC9 = 0;

// Cluster counters (n...)
int nsp3a = 0, nsp3b = 0, nsp3c = 0;
int nsp4a = 0, nsp4b = 0, nsp4c = 0;
int nsp5a = 0, nsp5b = 0, nsp5c = 0;
int n6A = 0, n6Z = 0, n7K = 0, n7T_a = 0, n7T_s = 0;
int n8A = 0, n8B = 0, n8K = 0;
int n9A = 0, n9B = 0, n9K = 0;
int n10A = 0, n10B = 0, n10K = 0, n10W = 0;
int n11A = 0, n11B = 0, n11C = 0, n11E = 0, n11F = 0, n11W = 0;
int n12A = 0, n12B = 0, n12D = 0, n12E = 0, n12K = 0;
int n13A = 0, n13B = 0, n13K = 0;
int nFCC = 0, nHCP = 0, nBCC_9 = 0;

// Cluster storage widths (m...)
int msp3a = 0, msp3b = 0, msp3c = 0;
int msp4a = 0, msp4b = 0, msp4c = 0;
int msp5a = 0, msp5b = 0, msp5c = 0;
int m6A = 0, m6Z = 0, m7K = 0, m7T_a = 0, m7T_s = 0;
int m8A = 0, m8B = 0, m8K = 0;
int m9A = 0, m9B = 0, m9K = 0;
int m10A = 0, m10B = 0, m10K = 0, m10W = 0;
int m11A = 0, m11B = 0, m11C = 0, m11E = 0, m11F = 0, m11W = 0;
int m12A = 0, m12B = 0, m12D = 0, m12E = 0, m12K = 0;
int m13A = 0, m13B = 0, m13K = 0;
int mFCC = 0, mHCP = 0, mBCC_9 = 0;

// Cluster data
int **hcsp3a = NULL, **hcsp3b = NULL, **hcsp3c = NULL;
int **hcsp4a = NULL, **hcsp4b = NULL, **hcsp4c = NULL;
int **hcsp5a = NULL, **hcsp5b = NULL, **hcsp5c = NULL;
int **hc6A = NULL, **hc6Z = NULL, **hc7K = NULL, **hc7T_a = NULL, **hc7T_s = NULL;
int **hc8A = NULL, **hc8B = NULL, **hc8K = NULL;
int **hc9A = NULL, **hc9B = NULL, **hc9K = NULL;
int **hc10A = NULL, **hc10B = NULL, **hc10K = NULL, **hc10W = NULL;
int **hc11A = NULL, **hc11B = NULL, **hc11C = NULL, **hc11E = NULL, **hc11F = NULL, **hc11W = NULL;
int **hc12A = NULL, **hc12B = NULL, **hc12D = NULL, **hc12E = NULL, **hc12K = NULL;
int **hc13A = NULL, **hc13B = NULL, **hc13K = NULL;
int **hcFCC = NULL, **hcHCP = NULL, **hcBCC_9 = NULL;

char *ssp3a = NULL, *ssp3b = NULL, *ssp3c = NULL;
char *ssp4a = NULL, *ssp4b = NULL, *ssp4c = NULL;
char *ssp5a = NULL, *ssp5b = NULL, *ssp5c = NULL;
char *s6A = NULL, *s6Z = NULL, *s7K = NULL, *s7T_a = NULL, *s7T_s = NULL;
char *s8A = NULL, *s8B = NULL, *s8K = NULL;
char *s9A = NULL, *s9B = NULL, *s9K = NULL;
char *s10A = NULL, *s10B = NULL, *s10K = NULL, *s10W = NULL;
char *s11A = NULL, *s11B = NULL, *s11C = NULL, *s11E = NULL, *s11F = NULL, *s11W = NULL;
char *s12A = NULL, *s12B = NULL, *s12D = NULL, *s12E = NULL, *s12K = NULL;
char *s13A = NULL, *s13B = NULL, *s13K = NULL;
char *sFCC = NULL, *sHCP = NULL, *sBCC_9 = NULL;

int **mem_sp3b = NULL, *nmem_sp3b = NULL, mmem_sp3b = 0;
int **mem_sp3c = NULL, *nmem_sp3c = NULL, mmem_sp3c = 0;
int **mem_sp4b = NULL, *nmem_sp4b = NULL, mmem_sp4b = 0;
int **mem_sp4c = NULL, *nmem_sp4c = NULL, mmem_sp4c = 0;
int **mem_sp5b = NULL, *nmem_sp5b = NULL, mmem_sp5b = 0;
int **mem_sp5c = NULL, *nmem_sp5c = NULL, mmem_sp5c = 0;
