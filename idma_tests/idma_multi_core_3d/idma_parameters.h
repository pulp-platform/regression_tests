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
  {17, 10, 9, 16, 3, 14, 1},
{47, 1, 6, 8, 9, 10, 5},
{21, 4, 8, 6, 6, 8, 2},
{52, 7, 7, 10, 7, 11, 4},
{47, 7, 10, 14, 2, 13, 1},
{37, 8, 9, 16, 8, 11, 1},
{31, 7, 6, 12, 5, 8, 4},
{41, 9, 7, 14, 5, 17, 2},
};

