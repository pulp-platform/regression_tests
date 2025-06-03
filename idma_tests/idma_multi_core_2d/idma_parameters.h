typedef struct {
  unsigned int size;
  unsigned int length;
  unsigned int src_stride;
  unsigned int dst_stride;
} TransferParameters;

TransferParameters transfer_params[] = {
  {4, 1, 10, 22},
  {80, 8, 9, 9},
{21, 11, 1, 19},
{40, 11, 17, 16},
{68, 7, 19, 20},
{42, 3, 5, 22},
};

