#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG 0
#define N_GAS 2

enum gas_type {
    gas_O,
    gas_H
};

struct cell {
    /* a count of the number of each
     * gas in this cell
     */
    unsigned int gas_counts[N_GAS];
};

void init( struct cell *cells, unsigned int xd, unsigned int yd, unsigned int zd ){
    unsigned int x=0,
        y=0,
        z=0;

    unsigned int quan = 0;
    unsigned int gas = 0;

    struct cell *c = 0;
    unsigned int i = 0;

    unsigned int xm = xd / 2,
        ym = yd / 2,
        zm = zd / 2;

    unsigned long int quan_tot = 0;

    unsigned int bounds = xd * yd * zd;

    /* initial volume */

    /* iterate through each pair of cells and swap */
    for( x=0 ; x < xd ; ++ x ){
        for( y=0 ; y < yd ; ++ y ){
            for( z=0 ; z < zd ; ++ z ){

                i = x + (y*xd) + (z*xd*yd);
                assert( i < bounds );

                c = &(cells[i]);
                assert(c);

                for( gas=0; gas < N_GAS; ++gas ){
                    /* initial quantity is based on proximity to center of room
                     * currently no scaling
                     */
                    quan = abs( xm - x) + abs( ym - y ) + abs( zm - z );
                    quan_tot += quan;
                    c->gas_counts[gas] = quan;
                }

            }
        }
    }
    printf("total quantity of particles: %d\n", quan_tot);
}

void tick( struct cell *cells, unsigned int xd, unsigned int yd, unsigned int zd ){
    unsigned int x=0,
        y=0,
        z=0;

    unsigned int nx=0,
        ny=0,
        nz=0;

    struct cell *c_a = 0;
    struct cell *c_b = 0;

    unsigned int i = 0;
    unsigned int ni = 0;

    unsigned int ra = 0;
    unsigned int rb = 0;

    unsigned int bounds = xd * yd * zd;

#if DEBUG
    puts("tick start");
#endif

    /* iterate through each pair of cells and swap */
    for( z=0 ; z < zd ; ++ z ){
        for( y=0 ; y < yd ; ++ y ){
            for( x=0 ; x < xd ; ++ x ){

                i = x + (y*xd) + (z*xd*yd);
                assert( i < (xd * yd * zd) );

                c_a = &(cells[i]);
                assert(c_a);


                /* swap with positive x neighbour */
                nx = x + 1;
                ni = nx + (ny*xd) + (nz*xd*yd);
                if( nx < xd && ni < bounds ){
                    ni = nx + (ny*xd) + (nz*xd*yd);
                    assert( ni < (xd * yd * zd) );

                    c_b = &(cells[ni]);
                    assert(c_b);

                    /* pick random gases */
                    /* cell from a to b */
                    ra = random() % N_GAS;
                    /* cell from b to a */
                    rb = random() % N_GAS;

                    /* handle swap */
                    /* only swap if we have something to give */
                    if( c_a->gas_counts[ra] ){
                        c_a->gas_counts[ra] --;
                        c_b->gas_counts[ra] ++;
                    }

                    if( c_b->gas_counts[ra] ){
                        c_a->gas_counts[ra] ++;
                        c_b->gas_counts[ra] --;
                    }
                }

                /* swap with positive y neighbour */
                ny = y + 1;
                ni = nx + (ny*xd) + (nz*xd*yd);
                if( ny < yd && ni < bounds ){

                    c_b = &(cells[ni]);
                    assert(c_b);

                    /* pick random gases */
                    /* cell from a to b */
                    ra = random() % N_GAS;
                    /* cell from b to a */
                    rb = random() % N_GAS;

                    /* handle swap */
                    /* only swap if we have something to give */
                    if( c_a->gas_counts[ra] ){
                        c_a->gas_counts[ra] --;
                        c_b->gas_counts[ra] ++;
                    }

                    if( c_b->gas_counts[ra] ){
                        c_a->gas_counts[ra] ++;
                        c_b->gas_counts[ra] --;
                    }
                }

                /* swap with positive z neighbour */
                nz = z + 1;
                ni = nx + (ny*xd) + (nz*xd*yd);
                if( nz < zd && ni < bounds ){
                    ni = nx + (ny*xd) + (nz*xd*yd);
                    assert( ni < (xd * yd * zd) );

                    c_b = &(cells[ni]);
                    assert(c_b);

                    /* pick random gases */
                    /* cell from a to b */
                    ra = random() % N_GAS;
                    /* cell from b to a */
                    rb = random() % N_GAS;

                    /* handle swap */
                    /* only swap if we have something to give */
                    if( c_a->gas_counts[ra] ){
                        c_a->gas_counts[ra] --;
                        c_b->gas_counts[ra] ++;
                    }

                    if( c_b->gas_counts[ra] ){
                        c_a->gas_counts[ra] ++;
                        c_b->gas_counts[ra] --;
                    }
                }

            }
        }
    }

#if DEBUG
    puts("tick finished");
#endif
}

int main(void){
    unsigned int xd = 128;
    unsigned int yd = 128;
    unsigned int zd = 128;

    unsigned int i = 0;
    unsigned int nticks = 1000;

    struct cell *cells = 0;

    printf("\nRunning simulation with dims '%d' * '%d' * '%d' for '%d' ticks\n",
            xd, yd, zd, nticks
          );

    // making allocation dynamic to be a fairer comparison
    cells = calloc(xd * yd * zd, sizeof(struct cell));
    assert(cells);

    puts("\ninit");
    init(cells, xd, yd, zd);

    puts("\nticking");
    for( i=0; i < nticks; ++i ){
        tick(cells, xd, yd, zd);
    }

    puts("");

    free(cells);
}
