typedef struct {
  unsigned int size;
  unsigned int length;
  unsigned int src_stride;
  unsigned int dst_stride;
} TransferParameters;

TransferParameters transfer_params[] = {
{88, 3, 8, 11},
{85, 2, 6, 5},
{73, 1, 10, 8},
{69, 3, 4, 5},
{21, 8, 14, 14},
{27, 2, 11, 8},
{67, 7, 13, 15},
};

