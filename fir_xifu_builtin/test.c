/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>

int main()
{

  unsigned int x = 0x01020304;
  unsigned int y = 0x01010101;
  unsigned int z = 0;
  register int *px = (int *) &x;
  register int *py = (int *) &y;
  register int *pz = (int *) &z;

  px = __builtin_xfir_lw(0, px, 0);
  py = __builtin_xfir_lw(1, py, 0);
  __builtin_xfir_dotp(2, 1, 0);
  pz = __builtin_xfir_sw(pz, 2, 0, 0);

  if(z == 0x40a06) {
    printf("Hello %08x!\n", z);
    return 0;
  }
  else {
    printf("No bueno %08x!\n", z);
    return 1;
  }

}
