/*
 * Copyright (C) 2023-2024 ETH Zurich and University of Bologna
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

/* 
 * Author: Francesco Conti f.conti@unibo.it
 */

#include <stdint.h>

__attribute__((aligned(16))) uint32_t h_stim[] = {
  0xffff0000,
  0xfffdfffd,
  0x00130003,
  0x00200023,
  0xffabfff6,
  0xff74ff69,
  0x00f20000,
  0x01c201c7,
  0xfdd5005d,
  0xfaeafb64,
  0x0529fe0a,
  0x18340edb,
  0x1df11df1,
  0x0edb1834,
  0xfe0a0529,
  0xfb64faea,
  0x005dfdd5,
  0x01c701c2,
  0x000000f2,
  0xff69ff74,
  0xfff6ffab,
  0x00230020,
  0x00030013,
  0xfffdfffd,
  0x0000ffff,
  0x0, 0x0, 0x0, 0x0 // padding
};

