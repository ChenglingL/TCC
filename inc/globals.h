#ifndef GLOBALS_H
#define GLOBALS_H

extern int box_type;
extern int frames_to_analyse;
extern int num_cluster_types;


extern char* cluster_names[];         // instead of char**
extern int cluster_size[];             // instead of int*
extern int* do_cluster_list[];        // instead of int**
extern int* num_cluster_list[];       // instead of int**
extern char** raw_list[];             // instead of char***
extern int*** cluster_list[];         // instead of int***
extern int* cluster_list_width[];     // instead of int**


extern char *fXmolName, *fBoxSizeName;
extern long box_offsets[1000];
extern double *x, *y, *z;
extern int *particle_type;

extern double rcutAA, rcutAA2, rcutAB, rcutAB2, rcutBB, rcutBB2;
extern double min_cutAA, min_cutAA2;
extern double fc;
extern int use_voronoi_bonds;
extern int PBCs;
extern int max_num_bonds;
extern int use_cell_list;
extern int analyse_all_clusters;

extern int doWriteBonds;
extern int doWriteClus;
extern int doWriteRaw;
extern int do11AcenXyz;
extern int do13AcenXyz;
extern int eleven_A_number;
extern int thirteen_A_number;
extern int doWritePopPerFrame;
extern int doWriteXYZ;

extern int incrStatic;

extern double **pop_per_frame;
extern double *mean_pop_per_frame;
extern int *num_gross_particles;
extern int *total_clusters;

extern double sidex, sidey, sidez, half_sidex, half_sidey, half_sidez;
extern double tiltxy, tiltxz, tiltyz;
extern long particles_in_current_frame;

extern int *num_bonds;
extern int **bond_list;
extern double **squared_bondlengths;
extern int maxnb;
extern int correctedBonds;

extern int num_sort_columns;

extern int n_cells_x, n_cells_y, n_cells_z, n_cells_total;
extern int *head;
extern int *linked_list;
extern double cell_len_x, cell_len_y, cell_len_z;

// Cluster switches
extern int dosp3, dosp3a, dosp3b, dosp3c;
extern int dosp4, dosp4a, dosp4b, dosp4c;
extern int dosp5, dosp5a, dosp5b, dosp5c;
extern int do6A, do6Z, do7K, do7T_a, do7T_s;
extern int do8A, do8B, do8K;
extern int do9A, do9B, do9K;
extern int do10A, do10B, do10K, do10W;
extern int do11A, do11B, do11C, do11E, do11F, do11W;
extern int do12A, do12B, do12D, do12E, do12K;
extern int do13A, do13B, do13K;
extern int doFCC, doHCP, doBCC9;

// Cluster counters (n...)
extern int nsp3a, nsp3b, nsp3c;
extern int nsp4a, nsp4b, nsp4c;
extern int nsp5a, nsp5b, nsp5c;
extern int n6A, n6Z, n7K, n7T_a, n7T_s;
extern int n8A, n8B, n8K;
extern int n9A, n9B, n9K;
extern int n10A, n10B, n10K, n10W;
extern int n11A, n11B, n11C, n11E, n11F, n11W;
extern int n12A, n12B, n12D, n12E, n12K;
extern int n13A, n13B, n13K;
extern int nFCC, nHCP, nBCC_9;

// Cluster storage widths (m...)
extern int msp3a, msp3b, msp3c;
extern int msp4a, msp4b, msp4c;
extern int msp5a, msp5b, msp5c;
extern int m6A, m6Z, m7K, m7T_a, m7T_s;
extern int m8A, m8B, m8K;
extern int m9A, m9B, m9K;
extern int m10A, m10B, m10K, m10W;
extern int m11A, m11B, m11C, m11E, m11F, m11W;
extern int m12A, m12B, m12D, m12E, m12K;
extern int m13A, m13B, m13K;
extern int mFCC, mHCP, mBCC_9;

// Cluster data
extern int **hcsp3a, **hcsp3b, **hcsp3c;
extern int **hcsp4a, **hcsp4b, **hcsp4c;
extern int **hcsp5a, **hcsp5b, **hcsp5c;
extern int **hc6A, **hc6Z, **hc7K, **hc7T_a, **hc7T_s;
extern int **hc8A, **hc8B, **hc8K;
extern int **hc9A, **hc9B, **hc9K;
extern int **hc10A, **hc10B, **hc10K, **hc10W;
extern int **hc11A, **hc11B, **hc11C, **hc11E, **hc11F, **hc11W;
extern int **hc12A, **hc12B, **hc12D, **hc12E, **hc12K;
extern int **hc13A, **hc13B, **hc13K;
extern int **hcFCC, **hcHCP, **hcBCC_9;

extern char *ssp3a, *ssp3b, *ssp3c;
extern char *ssp4a, *ssp4b, *ssp4c;
extern char *ssp5a, *ssp5b, *ssp5c;
extern char *s6A, *s6Z, *s7K, *s7T_a, *s7T_s;
extern char *s8A, *s8B, *s8K;
extern char *s9A, *s9B, *s9K;
extern char *s10A, *s10B, *s10K, *s10W;
extern char *s11A, *s11B, *s11C, *s11E, *s11F, *s11W;
extern char *s12A, *s12B, *s12D, *s12E, *s12K;
extern char *s13A, *s13B, *s13K;
extern char *sFCC, *sHCP, *sBCC_9;

extern int **mem_sp3b, *nmem_sp3b, mmem_sp3b;
extern int **mem_sp3c, *nmem_sp3c, mmem_sp3c;
extern int **mem_sp4b, *nmem_sp4b, mmem_sp4b;
extern int **mem_sp4c, *nmem_sp4c, mmem_sp4c;
extern int **mem_sp5b, *nmem_sp5b, mmem_sp5b;
extern int **mem_sp5c, *nmem_sp5c, mmem_sp5c;

#endif // GLOBALS_H
