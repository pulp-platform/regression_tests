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
{94, 5, 9, 10, 9, 8, 5},
{66, 9, 11, 14, 13, 13, 3},
{126, 3, 6, 4, 4, 4, 5},
{106, 6, 7, 7, 8, 7, 2},
{28, 7, 9, 12, 9, 12, 4},
{64, 10, 13, 15, 11, 12, 4},
};

