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
typedef enum {L1_TEST, L2_TEST} test_type_t;

int zeromem_test(unsigned int len, test_type_t type, unsigned int buf);
int main()
{

  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);


  int error_count_l2 = 0;
  int error_count_l1 = 0;



  if (get_core_id() == 0){


    for ( int i = 5; i < 8045; i=4*i) {
      error_count_l1 += zeromem_test(i, L1_TEST, loc);
    }

    if (error_count_l1)
      printf("OOPS -- got %d errors in L1 zeromem tests!\n", error_count_l1);
    else
      printf("L1 zeromem tests passed!\n");
    for ( int i = 5; i < 8045; i=4*i ) {
      error_count_l2 += zeromem_test(i, L2_TEST, ext);
    }
    if (error_count_l2)
      printf("OOPS -- got %d errors in L2 zeromem tests!\n", error_count_l2);
    else
      printf("L2 zeromem tests passed!\n");

  }

  return error_count_l1 + error_count_l2;
}


int zeromem_test(unsigned int len, test_type_t type, unsigned int buf) {
  unsigned int tx_id;
  int error_cnt = 0;
  uint8_t * buf_ptr = (uint8_t *) buf;
  // fill the buffer with data to make sure it gets erased
  for (int i=0; i<len; i++)
    buf_ptr[i] = i & 0xFF;

  if (type == L1_TEST) {
    tx_id = pulp_idma_zeromem(buf, len, IDMA_PROT_OBI);
  } else {
    tx_id = pulp_idma_zeromem(buf, len, IDMA_PROT_AXI);
  }
  plp_dma_barrier();
  for (int i=0; i<len; i++) {
    if (buf_ptr[i] != 0) {
      error_cnt++;
      printf("Error in %s test at element %d: expected 0, got 0x%x\n", type==L1_TEST ? "L1" : "L2", i, buf_ptr[i]);
    }
  }
  return error_cnt;
}
