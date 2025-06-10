typedef struct {
  unsigned int size;
  unsigned int length;
  unsigned int src_stride;
  unsigned int dst_stride;
} TransferParameters;

TransferParameters transfer_params[] = {
{34, 1, 3, 9},
{26, 4, 6, 5},
{87, 8, 18, 9},
{115, 9, 18, 11},
{316, 4, 11, 6},
{93, 10, 15, 18},
{358, 4, 6, 11},
};

