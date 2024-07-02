#include <math.h>
#include "pulp.h"
//#include "mchan_tests.h"

#define VERBOSE

#define MAX_BUFFER_SIZE 0x2200

//static unsigned char *ext;
//static unsigned char *loc;

//#define EXT_DATA_ADDR  ((unsigned int)ext)
//#define TCDM_DATA_ADDR ((unsigned int)loc)

L2_DATA static unsigned char ext[MAX_BUFFER_SIZE];
L1_DATA static unsigned char loc[MAX_BUFFER_SIZE];
L1_DATA static int error_count = 0;
#define EXT_DATA_ADDR  ((unsigned int) ext)
#define TCDM_DATA_ADDR ((unsigned int) loc)
typedef enum {RX, TX, TCDM} test_type_t;

int test_idma_1d(unsigned int len, test_type_t type, unsigned int ext_addr, unsigned int tcdm_addr);
int main()
{

  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  int n_bytes [] = {5, 19, 400};

  for (int core=0; core<ARCHI_CLUSTER_NB_PE; core++) {
  if (get_core_id() == core){
    printf("Testing iDMA with cluster core %d\n", core);
    for (int i = 0; i<3; i++) {
      error_count += test_idma_1d(n_bytes[i], TX, loc, ext);
    }
    for (int i = 0; i<3; i++) {
      error_count += test_idma_1d(n_bytes[i], RX, ext, loc);
    }
    for (int i = 0; i<3; i++) {
      error_count += test_idma_1d(n_bytes[i], TCDM, loc, loc+MAX_BUFFER_SIZE/2);
    }

  }
  synch_barrier();
  }
  return error_count;
}

int test_idma_1d(unsigned int len, test_type_t type, unsigned int src, unsigned int dst){

  volatile unsigned int i,j,id;
  volatile unsigned int test,read,error=0;

  for (i=0; i<len; i++){
    *(unsigned char*)(src + i) = i & 0xFF;
  }

  for (i=0; i<len+16; i++){
    *(unsigned char*)(dst + i) = 0;
  }
  if (type == RX){

#ifdef VERBOSE
    printf ("STARTING TEST FOR RX %d OPERATION: \n", len);
#endif

    id = pulp_cl_idma_memcpy(src, dst, len, IDMA_PROT_AXI, IDMA_PROT_OBI);
  } else if (type == TX) {

#ifdef VERBOSE
    printf ("STARTING TEST FOR TX %d OPERATION: \n", len);
#endif
    id = pulp_cl_idma_memcpy(src, dst, len, IDMA_PROT_OBI, IDMA_PROT_AXI);
  } else {
#ifdef VERBOSE
    printf ("STARTING TEST FOR TCDM %d OPERATION: \n", len);
#endif
    id = pulp_cl_idma_memcpy(src, dst, len, IDMA_PROT_OBI, IDMA_PROT_OBI);
  }

  plp_dma_barrier();

    for (i=0; i<len; i++){

      test = i & 0xFF;
      read = *(unsigned char*)(dst + i);

      if ( test != read ){
  printf("Error!!! Read: %x, Test:%x, Index: %d \n ",read,test,i);
  error++;
      }
    }
      for (i=len; i<len+16; i++){

        test = 0;
        read = *(unsigned char*)(dst + i);

        if ( test != read ){
          printf("Error!!! Read: %x, Test:%x, Index: %d \n ",read,test,i);
          error++;
        }
    }


  if (error == 0)
    printf("OOOOOOK!!!!!!\n");
  else
    printf("NOT OK!!!!!\n");

  return error;
}
