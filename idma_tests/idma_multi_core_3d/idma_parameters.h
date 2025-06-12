typedef struct {
  unsigned int size;
  unsigned int length;
  unsigned int src_stride_2d;
  unsigned int dst_stride_2d;
  unsigned int src_stride_3d;
  unsigned int dst_stride_3d;
  unsigned int num_reps_3d;
} TransferParameters;

TransferParameters transfer_params[] = {
{107, 5, 12, 13, 7, 12, 1},
{86, 5, 7, 10, 6, 12, 4},
{95, 10, 12, 20, 15, 17, 4},
{40, 2, 4, 12, 5, 4, 3},
{105, 4, 14, 6, 13, 9, 3},
{72, 8, 11, 17, 13, 15, 2},
{54, 10, 14, 20, 13, 11, 3},
{74, 6, 15, 10, 10, 11, 1},
{114, 4, 9, 8, 12, 9, 3},
{92, 3, 13, 5, 8, 5, 1},
};

