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
{111, 2, 5, 3, 4, 5, 3},
{43, 3, 6, 5, 8, 7, 5},
{84, 1, 3, 3, 2, 3, 3},
};

