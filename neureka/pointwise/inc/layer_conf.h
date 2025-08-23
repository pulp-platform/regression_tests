#ifndef __LAYER_CONF_H__
#define __LAYER_CONF_H__

#define TEST_NAME "test"
#define INPUT_HEIGHT (7)
#define INPUT_WIDTH (5)
#define INPUT_CHANNEL (257)
#define INPUT_SIGNED (0)
#define INPUT_BITS (8)

#define OUTPUT_HEIGHT (7)
#define OUTPUT_WIDTH (5)
#define OUTPUT_CHANNEL (39)
#define OUTPUT_BITS (8)

#define WEIGHT_HEIGHT (1)
#define WEIGHT_WIDTH (1)
#define WEIGHT_CHANNEL_IN (257)
#define WEIGHT_CHANNEL_OUT (39)
#define WEIGHT_BITS (8)
#define WEIGHT_OFFSET (-128)

#define SCALE_BITS (8)

#define BIAS_BITS (32)

#define PADDING_TOP (0)
#define PADDING_BOTTOM (0)
#define PADDING_LEFT (0)
#define PADDING_RIGHT (0)
#define PADDING_VALUE (0)

#define STRIDE_HEIGHT (1)
#define STRIDE_WIDTH (1)

#define GROUPS (1)
#define OUTSHIFT (12)
#define HAS_NORM_QUANT (1)
#define HAS_BIAS (1)
#define HAS_RELU (1)

#endif  // __LAYER_CONF_H__
