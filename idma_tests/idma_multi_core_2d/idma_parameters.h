typedef struct {
  unsigned int size;
  unsigned int length;
  unsigned int src_stride;
  unsigned int dst_stride;
} TransferParameters;

TransferParameters transfer_params[] = {
{5, 1, 10, 8},
{64, 6, 12, 8},
{46, 5, 11, 7},
{66, 3, 5, 9},
{54, 7, 13, 10},
{84, 8, 18, 15},
{106, 2, 12, 11},
{65, 9, 12, 12},
};

