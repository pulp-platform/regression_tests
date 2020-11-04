#include <stdio.h>

/*
   -----------------------------------------------------------------------
   Copyright (c) 2001 Dr Brian Gladman <brg@gladman.uk.net>, Worcester, UK

   TERMS

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   This software is provided 'as is' with no guarantees of correctness or
   fitness for purpose.
   -----------------------------------------------------------------------
   */

/* Example of the use of the AES (Rijndael) algorithm for file  */
/* encryption.  Note that this is an example application, it is */
/* not intended for real operational use.  The Command line is: */
/*                                                              */
/* aesxam input_file_name output_file_name [D|E] hexadecimalkey */
/*                                                              */
/* where E gives encryption and D decryption of the input file  */
/* into the output file using the given hexadecimal key string  */
/* The later is a hexadecimal sequence of 32, 48 or 64 digits   */
/* Examples to encrypt or decrypt aes.c into aes.enc are:       */
/*                                                              */
/* aesxam file.c file.enc E 0123456789abcdeffedcba9876543210    */
/*                                                              */
/* aesxam file.enc file2.c D 0123456789abcdeffedcba9876543210   */
/*                                                              */
/* which should return a file 'file2.c' identical to 'file.c'   */

#include <stddef.h>

#include "pulp.h"
#include "aes.h"
#include "./jrand.c"

#ifndef fpos_t
   #define fpos_t size_t
#endif

#define FLEN flen

#define RAND(a,b) (((a = 36969 * (a & 65535) + (a >> 16)) << 16) + (b = 18000 * (b & 65535) + (b >> 16))  )


RT_LOCAL_DATA byte inbuf[16];
RT_LOCAL_DATA byte inbuf1[16];
RT_LOCAL_DATA byte inbuf2[16];
RT_LOCAL_DATA byte encoutbuf[16];
RT_LOCAL_DATA byte decoutbuf[16];
RT_LOCAL_DATA byte key[32];
RT_LOCAL_DATA aes *ctx;
RT_LOCAL_DATA byte *bp1;
RT_LOCAL_DATA byte *bp2;
RT_LOCAL_DATA byte *tp;

RT_LOCAL_DATA unsigned long a[2];
RT_LOCAL_DATA byte r[4];


void fillrand(byte *buf, int len)
{
   static unsigned long mt = 1, count = 4;
   int                  i;

   if(mt) {
      mt = 0;
      /*cycles(a);*/
      a[0]=0xeaf3;
      a[1]=0x35fe;
   }

   for(i = 0; i < len; ++i)
   {
      if(count == 4)
      {
         *(unsigned long*)r = RAND(a[0], a[1]);
         count = 0;
      }

      buf[i] = r[count++];
   }
}

int encfile(aes *ctx, byte *encoutbuf)
{
   fpos_t          flen;
   unsigned long   i=0, l=0, j, k;

   fillrand(encoutbuf, 16);           /* set an IV for CBC mode           */
   FLEN = 4096;
   fillrand(inbuf, 1);             /* make top 4 bits of a byte random */
   l = 15;                         /* and store the length of the last */
   /* block in the lower 4 bits        */
   inbuf[0] = ((char)FLEN & 15) | (inbuf[0] & ~15);

   for(j = 0; j <256; j++)
   {                               /* input 1st 16 bytes to buf[1..16] */
      for(k = 0; k < 16; ++k)
         inbuf[k] = jrand();

      for(i = 0; i < 16; ++i)         /* xor in previous cipher text  */
         inbuf[i] ^= encoutbuf[i];

      encrypt(inbuf, encoutbuf, ctx);    /* and do the encryption        */
      /* in all but first round read 16   */
      l = 16;                     /* bytes into the buffer            */
   }

   return 0;
}

int decfile(aes *ctx, byte *decoutbuf)
{
   int     i,j, l, flen, k;

   fillrand(inbuf1, 16);           /* set an IV for CBC mode           */

   for(k = 0; k < 16; ++k)
      inbuf2[k] = jrand();

   decrypt(inbuf2, decoutbuf, ctx);   /* decrypt it                       */

   for(i = 0; i < 16; ++i)         /* xor with previous input          */
      decoutbuf[i] ^= inbuf1[i];

   flen = 0;  /* recover length of the last block and set */
   l = 15;                 /* the count of valid bytes in block to 15  */
   bp1 = inbuf1;           /* set up pointers to two input buffers     */
   bp2 = inbuf2;

   for(j = 0; j < 256; ++j)
   {
      for(k = 0; k < 16; ++k)
         bp1[k] = jrand();

      decrypt(bp1, decoutbuf, ctx);  /* decrypt the new input block and  */

      for(i = 0; i < 16; ++i)     /* xor it with previous input block */
         decoutbuf[i] ^= bp2[i];

      /* set byte count to 16 and swap buffer pointers                */

      l = i; tp = bp1, bp1 = bp2, bp2 = tp;
   }

   return 0;
}

char *presetkey="ABCDEF1234567890ABCDEF1234567890";

#ifdef __LP64__
      byte check_encoutbuf[16] = {46, 100, 102, -108, 50, -49, 41, -104,
                                  36, 73, 123, -53, 14, -8, -40, 120};
      byte check_decoutbuf[16] = {-43, -117, -3, -13, 67, -93, -59, -124,
                                  16, 104, -57, 80, 12, 43, 84, 26};
#else
      /* Assume 32 bits */
#if (REPEAT_FACTOR == 8)
      byte check_encoutbuf[16] = {41, -73, 107, -88, 50, -49, 41, -104,
                                  36, 73, 123, -53, 14, -8, -40, 120};
      byte check_decoutbuf[16] = {82, -39, -70, -17, -64, -115, -124, 94,
                                  -19, 41, -115, 12, 11, 26, 113, 23};
#elif (REPEAT_FACTOR == 2)
      byte check_encoutbuf[16] = {132, 239, 82, 209, 237, 7, 193, 250, 123, 31, 223, 44, 41, 244, 39, 158, };
      byte check_decoutbuf[16] = {24, 98, 186, 131, 169, 240, 160, 138, 162, 201, 177, 246, 122, 37, 56, 93, };
#elif (REPEAT_FACTOR == 1)
      byte check_encoutbuf[16] = {100, 215, 244, 35, 56, 217, 114, 234, 0, 131, 205, 202, 173, 88, 207, 185, };
      byte check_decoutbuf[16] = {131, 215, 237, 130, 180, 147, 146, 219, 41, 130, 107, 12, 2, 203, 224, 182, };
#endif

#endif


void compute_aes();

int main()
{

  int coreid, i, error = 0;
  coreid = get_core_id();

  // set start value of jrand function
  next = 1;

  if (coreid == 0)
    {
      int f=0;
      initialize_aes();

      // 1 iterations of enc+dec
      for (f=0;f<1;f++){

	printf("Start Rijndael encryption/decryption\n\n",0,0,0,0);

#ifdef PROFILE
	reset_timer();
	start_timer();
#ifdef PIN_CAM_I2S_SDI1
	set_gpio_pin_value(PIN_CAM_I2S_SDI1+1, 1);
#endif
	perf_start();
#endif
        
        compute_aes();

#ifdef PROFILE
        perf_stop();
#ifdef PIN_CAM_I2S_SDI1
	set_gpio_pin_value(PIN_CAM_I2S_SDI1+1, 0);
#endif
	stop_timer();
#endif
        
        //check output
        for (i = 0; i < 16; i++){
          if (encoutbuf[i] != check_encoutbuf[i]) {
            error+=1;
#ifdef DEBUG_OUTPUT
	    printf("Error occured in encryption\n",0,0,0,0);
            printf("encrypted: %d, expected: %d\n",encoutbuf[i],check_encoutbuf[i],0,0);
#endif
          }
          if (decoutbuf[i] != check_decoutbuf[i]) {
            error+=1;
#ifdef DEBUG_OUTPUT
	    printf("Error occured in decryption\n",0,0,0,0);
            printf("decrypted: %d, expected: %d\n",decoutbuf[i],check_decoutbuf[i],0,0);
#endif
          }
        }
	
      }
      
      if (error == 0)
	printf("== test: %s -> success, nr. of errors: %d, execution time: %d\n", "rijndael", 0, get_time());
      else
	printf("== test: %s -> fail, nr. of errors: %d, execution time: %d\n", "rijndael", 1, get_time());
      
      perf_print_all();
    }

  return error;
}


void compute_aes(){
      char    *cp, ch;
      int     i=0, by=0, key_len=0, err = 0, n;

      for(n = 0; n < REPEAT_FACTOR; n++)
        {
          aes     ctx[1];
          by=0; key_len=0; err = 0;
          cp = presetkey;   /* this is a pointer to the hexadecimal key digits  */
          i = 0;          /* this is a count for the input digits processed   */

          while(i < 64 && *cp)    /* the maximum key length is 32 bytes and   */
            {                       /* hence at most 64 hexadecimal digits      */
              ch = *cp++;            /* process a hexadecimal digit  */
              if(ch >= '0' && ch <= '9')
                by = (by << 4) + ch - '0';
              else if(ch >= 'A' && ch <= 'F')
                by = (by << 4) + ch - 'A' + 10;
              else                            /* error if not hexadecimal     */
                {
                  err = -2; goto exit;
                }

              /* store a key byte for each pair of hexadecimal digits         */
              if(i++ & 1)
                key[i / 2 - 1] = by & 0xff;
            }

          if(*cp)
            {
              err = -3; goto exit;
            }
          else if(i < 32 || (i & 15))
            {
              err = -4; goto exit;
            }

          key_len = i / 2;

          // ENCRYPTION
#ifdef DEBUG_OUTPUT
	  printf("Set encryption key\n",0,0,0,0);
#endif
          set_key(key, key_len, enc, ctx);
#ifdef DEBUG_OUTPUT
	  printf("Key: %d\n\n",key,0,0,0);
          printf("Start encryption\n\n",0,0,0,0);
#endif
          err = encfile(ctx, encoutbuf);

          // DECRYPTION
#ifdef DEBUG_OUTPUT          
	  printf("Set decryption key\n",0,0,0,0);
#endif
          set_key(key, key_len, dec, ctx);
#ifdef DEBUG_OUTPUT
          printf("Key: %d\n\n",key,0,0,0);
          printf("Start decryption\n",0,0,0,0);
#endif
	  err = decfile(ctx, decoutbuf);

        }

    exit:
      i=0;
}
