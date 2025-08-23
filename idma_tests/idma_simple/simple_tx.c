#include <math.h>
#include "pulp.h"
//#include "mchan_tests.h"

#define VERBOSE

#define MAX_BUFFER_SIZE 0x2000

//static unsigned char *ext;
//static unsigned char *loc;

//#define EXT_DATA_ADDR  ((unsigned int)ext)
//#define TCDM_DATA_ADDR ((unsigned int)loc)

L2_DATA static unsigned char ext[MAX_BUFFER_SIZE];
L1_DATA static unsigned char loc[MAX_BUFFER_SIZE];

#define EXT_DATA_ADDR  ((unsigned int) ext)
#define TCDM_DATA_ADDR ((unsigned int) loc)
typedef enum {RX, TX} test_type_t;

int testMCHAN(unsigned int len, test_type_t type, unsigned int ext_addr, unsigned int tcdm_addr);
int main()
{

  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);


  int   error_count = 0;


 /*  if (rt_core_id() == 0) */
/*   { */
/*     if ((ext = rt_alloc(RT_ALLOC_L2_CL_DATA, MAX_BUFFER_SIZE)) == 0) return -1; */
/*     if ((loc = rt_alloc(RT_ALLOC_CL_DATA, MAX_BUFFER_SIZE)) == 0) return -1; */
/*   } */

  if (get_core_id() == 0){


    for ( int i = 5; i < 8045; i=5*i) {
      error_count += testMCHAN(i, TX, ext, loc);
    }
    for ( int i = 5; i < 8045; i=5*i ) {
      error_count += testMCHAN(i, RX, ext, loc);
    }

  }

  return error_count;

}

int testMCHAN(unsigned int len, test_type_t type, unsigned int ext_addr, unsigned int tcdm_addr){

  volatile unsigned int i,j,id;
  volatile unsigned int test,read,error=0;

  if (type == RX){

#ifdef VERBOSE
    printf ("STARTING TEST FOR RX %d OPERATION: \n", len);
#endif

    for (i=0; i<len; i++){
      *(unsigned char*)(ext_addr + i) = i & 0xFF;
    }

    for (i=0; i<len+16; i++){
      *(unsigned char*)(tcdm_addr + i) = 0;
    }
    id = pulp_idma_memcpy(ext_addr, tcdm_addr, len, IDMA_PROT_AXI, IDMA_PROT_OBI);
  } else {

#ifdef VERBOSE
    printf ("STARTING TEST FOR TX %d OPERATION: \n", len);
#endif

    for (i=0; i<len; i++){
      *(unsigned char*)(tcdm_addr + i) = i & 0xFF;
    }

    for (i=0; i<len+16; i++){
      *(unsigned char*)(ext_addr+ i) = 0;
    }
    id = pulp_idma_memcpy(tcdm_addr, ext_addr, len, IDMA_PROT_OBI, IDMA_PROT_AXI);
  }

  plp_dma_barrier();


  if (type == RX){

    for (i=0; i<len; i++){

      test = i & 0xFF;
      read = *(unsigned char*)(tcdm_addr + i);

      if ( test != read ){
  printf("Error!!! Read: %x, Test:%x, Index: %d \n ",read,test,i);
  error++;
      }

    }




  }else{

    for (i=0; i<len; i++){

      test = i & 0xFF;
      read = *(unsigned char*)(ext_addr + i);

      if ( test != read ){
  printf("Error!!! Read: %x, Test:%x, Index: %d \n ",read,test,i);
  error++;
      }

    }

  }

  if (error == 0)
    printf("OOOOOOK!!!!!!\n");
  else
    printf("NOT OK!!!!!\n");

  return error;

}
