#include <clusters/simple_cluster_methods.h>
#include "globals.h"
#include "bonds.h"
#include "tools.h"
#include "11F.h"
#include "13K.h"

//!  An 11F cluster is the intersection of two 5A and two 6A clusters
/*!
*  Find 11F clusters
*  An 11F is constructed from two 5A and two 6A clusters where:
*      - Each spindle of 5Ai is bonded to a spindle of 5Aj.
*      - There is one common ring particle between the 5A clusters.
*      - There is one bonded pair of ring particle between the 5A clusters.
*      - 6A_i has a distinct spindle and a spindle which is the common ring particle of the 5As
 *     - 6A_j has a distinct spindle and a spindle which is the common ring particle of the 5As
*      - Each 6A has two bonded 5A spindles and two bonded 5A ring particles as its ring.
*
*  Cluster output: BOOOOOOBBBB
*  Storage order: 5A_common particle, 6A_uncommon_spindle x 2, 5A_spindles x 4, 5A_ring_particles x 4
*
*/
void Clusters_Get11F_13K() {
    int first_5A_ring_pointer;

    int first_5A_id, second_5A_id, second_5A_pointer;
    int *first_5A_cluster, *second_5A_cluster;
    int first_5A_ring_particle;

    int spindles_5A[4];             // The 4 spindle particles of the 2 5As
    int common_particle;            // The common ring particle of the 5As
    int bonded_5A_ring_ids[2];      // The bonded ring particles of the 5As
    int extra_6A_particles[2];      // The two particles that are not in the 5As
    int bonded_6A_id;               // The id of the first 6A cluster to pass to the 13A method

    for(first_5A_id = 0; first_5A_id < nsp3c; first_5A_id++) {
        first_5A_cluster = hcsp3c[first_5A_id];
        // loop over only the rings of the 5A clusters
        for (first_5A_ring_pointer = 0; first_5A_ring_pointer < 3; first_5A_ring_pointer++) {
            first_5A_ring_particle = first_5A_cluster[first_5A_ring_pointer];
            for (second_5A_pointer = 0; second_5A_pointer < nmem_sp3c[first_5A_ring_particle]; second_5A_pointer++) {
                second_5A_id = mem_sp3c[first_5A_ring_particle][second_5A_pointer];
                second_5A_cluster = hcsp3c[second_5A_id];
                if (second_5A_id <= first_5A_id) continue;

                // Check that the 5A spindles are bonded
                if (are_spindles_bonded(first_5A_id, second_5A_id, spindles_5A) != 1) continue;

                // There must be only 1 particle common between the two 5As
                int return_array[6];
                if (count_common_particles(first_5A_cluster, second_5A_cluster, 3, 3, return_array) != 1) continue;
                common_particle = return_array[0];

                // There must be exactly one pair of bonded ring particles between the 5As
                if (count_bonded_ring_particles_11F(common_particle, first_5A_cluster, second_5A_cluster, bonded_5A_ring_ids) != 1) continue;

                if (get_bonded_6As(common_particle, bonded_5A_ring_ids, extra_6A_particles, &bonded_6A_id, spindles_5A)) {
                    write_11F(common_particle, extra_6A_particles, first_5A_cluster, second_5A_cluster);

                    if (do13K == 1) {
                        if (Clusters_Get13K(first_5A_id, second_5A_id, bonded_6A_id)) {
                            ++n13K;
                        }
                    }
                    ++n11F;
                }
            }
        }
    }
}

int are_spindles_bonded(int first_5A_id, int second_5A_id, int *bonded_pairs) {

    int *first_5A_cluster = hcsp3c[first_5A_id];
    int *second_5A_cluster = hcsp3c[second_5A_id];

    // First check that the spindles are unique
    if (first_5A_cluster[3] == second_5A_cluster[3]) return 0;
    if (first_5A_cluster[3] == second_5A_cluster[4]) return 0;
    if (first_5A_cluster[4] == second_5A_cluster[4]) return 0;

    // Now check if both pairs of spindles are bonded
    if (Bonds_BondCheck(first_5A_cluster[3], second_5A_cluster[3]) == 1 &&
        Bonds_BondCheck(first_5A_cluster[4], second_5A_cluster[4]) == 1) {
        bonded_pairs[0] = first_5A_cluster[3];
        bonded_pairs[1] = second_5A_cluster[3];
        bonded_pairs[2] = first_5A_cluster[4];
        bonded_pairs[3] = second_5A_cluster[4];
        return 1;
    }
    else if (Bonds_BondCheck(first_5A_cluster[3], second_5A_cluster[4]) == 1 &&
               Bonds_BondCheck(first_5A_cluster[4], second_5A_cluster[3]) == 1) {
        bonded_pairs[0] = first_5A_cluster[3];
        bonded_pairs[1] = second_5A_cluster[4];
        bonded_pairs[2] = first_5A_cluster[4];
        bonded_pairs[3] = second_5A_cluster[3];
        return 1;
    }
    return 0;
}

int count_bonded_ring_particles_11F(int cp, const int *first_5A, const int *second_5A, int *bonded_particle_ids) {
    int num_bonded_pairs = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (first_5A[i] != cp && second_5A[j] != cp) {
                if (Bonds_BondCheck(first_5A[i], second_5A[j]) == 1) {
                    bonded_particle_ids[0] = first_5A[i];
                    bonded_particle_ids[1] = second_5A[j];
                    num_bonded_pairs++;
                }
            }
        }
    }
    return num_bonded_pairs;
}

int get_bonded_6As(int common_particle, int* bonded_particle_ids, int *extra_particles, int *bonded_6A_id, const int *bonded_pairs) {
    // We know that the 6As must have the common spindle as a spindle so use the mem arrays.
    int first_6A_detected = 0;
    int second_6A_detected = 0;

    for (int mem_pointer = 0; mem_pointer < nmem_sp4c[common_particle]; ++mem_pointer) {
        int potential_6A_id = mem_sp4c[common_particle][mem_pointer];
        int *potential_6A_cluster = hcsp4c[potential_6A_id];

        if (potential_6A_cluster[4] == common_particle || potential_6A_cluster[5] == common_particle) {

            if (first_6A_detected == 0) {
                int i;
                int counter;

                for (i = 0; i < 4; i++) {
                    counter =
                            potential_6A_cluster[i] == bonded_pairs[0] || potential_6A_cluster[i] == bonded_pairs[1] ||
                            potential_6A_cluster[i] == bonded_particle_ids[0] ||
                            potential_6A_cluster[i] == bonded_particle_ids[1];
                    if (counter == 0) break;
                }
                if (i == 4) {
                    if (potential_6A_cluster[4] == common_particle) {
                        extra_particles[0] = potential_6A_cluster[5];
                    } else {
                        extra_particles[0] = potential_6A_cluster[4];
                    }
                    *bonded_6A_id = potential_6A_id;
                    first_6A_detected = 1;
                }
            }
            if (second_6A_detected == 0) {
                int i;
                int counter;

                for (i = 0; i < 4; i++) {
                    counter =
                            potential_6A_cluster[i] == bonded_pairs[2] || potential_6A_cluster[i] == bonded_pairs[3] ||
                            potential_6A_cluster[i] == bonded_particle_ids[0] ||
                            potential_6A_cluster[i] == bonded_particle_ids[1];
                    if (counter == 0) break;
                }
                if (i == 4) {
                    if (potential_6A_cluster[4] == common_particle) {
                        extra_particles[1] = potential_6A_cluster[5];
                    } else {
                        extra_particles[1] = potential_6A_cluster[4];
                    }
                    second_6A_detected = 1;
                }
            }
            if (first_6A_detected == 1 && second_6A_detected == 1) {
                return 1;
            }
        }
    }
    return 0;
}


void write_11F(int common_particle, const int *extra_particles, const int *first_5A, const int *second_5A) {
    int clusSize = 11;

    if (n11F == m11F) {
        hc11F = resize_2D_int(hc11F, m11F, m11F + incrStatic, clusSize, -1);
        m11F = m11F + incrStatic;
    }

    hc11F[n11F][0] = common_particle;
    hc11F[n11F][1] = extra_particles[0];
    hc11F[n11F][2] = extra_particles[1];
    hc11F[n11F][3] = first_5A[3];
    hc11F[n11F][4] = first_5A[4];
    hc11F[n11F][5] = second_5A[3];
    hc11F[n11F][6] = second_5A[4];

    int j = 7;
    for (int i = 0; i < 3; ++i) {
        if (first_5A[i] != common_particle) {
            hc11F[n11F][j] = first_5A[i];
            j++;
        }
        if (second_5A[i] != common_particle) {
            hc11F[n11F][j] = second_5A[i];
            j++;
        }
    }

    if (s11F[hc11F[n11F][0]] == 'C') s11F[hc11F[n11F][0]] = 'B';
    for(int i = 1; i < 7; i++) {
        s11F[hc11F[n11F][i]] = 'O';
    }
    for(int i = 7; i < 11; i++) {
        if (s11F[hc11F[n11F][i]] == 'C') s11F[hc11F[n11F][i]] = 'B';
    }
}