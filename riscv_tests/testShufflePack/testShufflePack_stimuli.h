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

/* 
 * Mantainer: Luca Valente, luca.valente2@unibo.it
 */
#define NumberOfStimuli 10

unsigned int g_shuffle_h_a[] = {
0x00B08B6D,
0xDC22A073,
0x7736A3B3,
0xFD7ED483,
0xA0D2D297,
0xD98B7FF0,
0xA685AAD4,
0xF60555C5,
0x9084D723,
0xADD3600A,
};

unsigned int g_shuffle_h_b[] = {
0x15DD3767,
0x73365B62,
0xC825842B,
0x59024EB8,
0x1A4544E7,
0xB0CD735A,
0xF5021415,
0xB6B17770,
0x3B84EEF7,
0x670E803C,
};

unsigned int g_shuffle_h_exp[] = {
0x00B000B0,
0xA073A073,
0x77367736,
0xD483D483,
0xA0D2A0D2,
0xD98B7FF0,
0xAAD4A685,
0xF60555C5,
0xD7239084,
0x600A600A,
};

unsigned int g_shuffle_b_a[] = {
0xE9E92EF7,
0x1AC5F45C,
0x4D2289D6,
0x93AAED8B,
0x5FFFBC41,
0x9042F2B0,
0xF950C39F,
0xAA56328E,
0x3966994A,
0x829A9619,
};

unsigned int g_shuffle_b_b[] = {
0xE0EE24EB,
0xDD1F8476,
0x60F85096,
0x05CEFB27,
0xFFDBD786,
0xD0F6CAB6,
0xC668EDED,
0x832A7DC7,
0x8ED5F86B,
0x19BE966F,
};

unsigned int g_shuffle_b_exp[] = {
0xF7E9F7E9,
0xF41A5CC5,
0xD6D6D622,
0xEDAA9393,
0x5F5F5FFF,
0xB0424242,
0x509FC3C3,
0xAA5632AA,
0x66994A39,
0x969A9A82,
};

#define g_shuffle_sci_h_0 28

#define g_shuffle_sci_h_1 22

#define g_shuffle_sci_h_2 28

#define g_shuffle_sci_h_3 8

#define g_shuffle_sci_h_4 19

#define g_shuffle_sci_h_5 23

#define g_shuffle_sci_h_6 31

#define g_shuffle_sci_h_7 27

#define g_shuffle_sci_h_8 3

#define g_shuffle_sci_h_9 28

unsigned int g_shuffle_sci_h_a[] = {
0x98133A7A,
0x77EF8226,
0x19514BF5,
0xE0CA425D,
0x11B20DD8,
0x8B9F2683,
0x24BB8923,
0x96DC6680,
0x0545D467,
0x1CC39530,
};

unsigned int g_shuffle_sci_h_exp[] = {
0x3A7A3A7A,
0x77EF8226,
0x4BF54BF5,
0x425D425D,
0x11B211B2,
0x8B9F8B9F,
0x24BB24BB,
0x96DC96DC,
0x05450545,
0x95309530,
};

#define g_shuffle_sci_b_0 7

#define g_shuffle_sci_b_1 15

#define g_shuffle_sci_b_2 28

#define g_shuffle_sci_b_3 19

#define g_shuffle_sci_b_4 2

#define g_shuffle_sci_b_5 31

#define g_shuffle_sci_b_6 10

#define g_shuffle_sci_b_7 31

#define g_shuffle_sci_b_8 18

#define g_shuffle_sci_b_9 25

unsigned int g_shuffle_sci_b_a[] = {
0x22E8BFC0,
0x1D9B93E5,
0x755BE0C2,
0xB3BFA985,
0x2C7AA522,
0x0D765EAE,
0x0F121201,
0x0DED5EE0,
0x290F1615,
0x4C4DAE97,
};

unsigned int g_shuffle_sci_b_exp[] = {
0xC0C0BF22,
0xE5E51D1D,
0xC2E075C2,
0x85A985B3,
0x2222227A,
0xAE5E0D0D,
0x01011212,
0xE05E0D0D,
0x1516150F,
0x97AE4DAE,
};

unsigned int g_shuffle2_h_a[] = {
0xABD03F6E,
0x511B0706,
0x9D2D15F2,
0x2C48AA34,
0xADE8E999,
0x6BF30059,
0xB7FED864,
0xFDC2EA55,
0x32CBBE72,
0xCB19A2A3,
};

unsigned int g_shuffle2_h_b[] = {
0x1D4B26D0,
0xEB397322,
0x5C71278E,
0x4887D28E,
0xD26AD68F,
0xEFB6AF79,
0x5BBB1058,
0x7292CF23,
0x6DB6060F,
0x00BCDD22,
};

unsigned int g_shuffle2_h_c[] = {
0xF0C3A85B,
0x93A613C6,
0x2BCEDA18,
0x55247E80,
0x23A14961,
0x517C1495,
0x4583A035,
0x4F82A53E,
0x22C33B63,
0xFB744389,
};

unsigned int g_shuffle2_h_exp[] = {
0xABD0A85B,
0x93A60706,
0x2BCE15F2,
0x2C48AA34,
0xE999ADE8,
0x0059517C,
0xB7FEA035,
0xEA55FDC2,
0xBE7232CB,
0x4389A2A3,
};

unsigned int g_shuffle2_b_a[] = {
0x35A309D9,
0xCA850EB8,
0xE433C0A1,
0x36DE6217,
0xD8CE132C,
0x657BF4D6,
0x617EEED1,
0x43AB21CB,
0x052B5263,
0xFFABF194,
};

unsigned int g_shuffle2_b_b[] = {
0x8AE410B6,
0x256B969B,
0xC8381F65,
0xC98AEA7D,
0x67D8BF89,
0x06DB0232,
0xE4D33275,
0x4B2EC0BE,
0x85BB52D0,
0x35CBE594,
};

unsigned int g_shuffle2_b_c[] = {
0x22DA0BEC,
0xF438D1D7,
0xAC7DBC14,
0x9D6781F4,
0x166FB40D,
0x9E049D7E,
0x55264DEE,
0x7306984C,
0x35C4A31D,
0xE0A7A1D1,
};

unsigned int g_shuffle2_b_exp[] = {
0xDAD9ECA3,
0x0EF485F4,
0x1414E4C0,
0x81676762,
0xD80DD8B4,
0x7B9E0404,
0xD15526EE,
0x73AB4CAB,
0x5235C41D,
0xF1E0F194,
};

unsigned int g_pack_h_a[] = {
0xFB32EE74,
0x05D6BF1F,
0x22E44358,
0x38A2CE44,
0xF47A843C,
0xE7F3CE16,
0x92195600,
0x29F395F7,
0x358F2C23,
0xA53495F6,
};

unsigned int g_pack_h_b[] = {
0xD906FA66,
0x42642BD3,
0x1A51524C,
0xFA8B96FD,
0x918CCE8B,
0x19F20369,
0x2AA36439,
0xE0173779,
0xE79DFC1B,
0xD30EB417,
};

unsigned int g_pack_h_exp[] = {
0xEE74FA66,
0xBF1F2BD3,
0x4358524C,
0xCE4496FD,
0x843CCE8B,
0xCE160369,
0x56006439,
0x95F73779,
0x2C23FC1B,
0x95F6B417,
};

unsigned int g_pack_hi_b_a[] = {
0x6D991324,
0x0DBB3040,
0x47F314E1,
0xC223F582,
0xA14763A7,
0x2716E5B4,
0xC5BD7136,
0x0BC71F3D,
0x9174CD00,
0xBE62DEF3,
};

unsigned int g_pack_hi_b_b[] = {
0x665B1490,
0x7303E2E7,
0xC8D11590,
0x3482BE59,
0x6013071B,
0x0EE89DC7,
0xF4BD1938,
0x4FE009C2,
0x7E2E33AD,
0xE1A5A355,
};

unsigned int g_pack_hi_b_c[] = {
0x6B722D15,
0xC795F9DE,
0x9DCB4003,
0x217CAE32,
0xADC6688F,
0x88D06748,
0x954B564F,
0x93AC5A41,
0x0849E92E,
0x37236701,
};

unsigned int g_pack_hi_b_exp[] = {
0x24902D15,
0x40E7F9DE,
0xE1904003,
0x8259AE32,
0xA71B688F,
0xB4C76748,
0x3638564F,
0x3DC25A41,
0x00ADE92E,
0xF3556701,
};

unsigned int g_pack_lo_b_a[] = {
0xEB3B312F,
0x8CEF9F2B,
0x33368FE4,
0xD784C7FA,
0x425F04FA,
0x97A668A1,
0xB52EC7E4,
0x0BD38105,
0xC415BC55,
0x46AB47AF,
};

unsigned int g_pack_lo_b_b[] = {
0xD42B1DB3,
0xDF8481E1,
0x1B2DA726,
0xBD8EE373,
0xE8E0BD38,
0xF4ECF626,
0x7712263B,
0x1D948D30,
0x41E68AF7,
0xF5AC6275,
};

unsigned int g_pack_lo_b_c[] = {
0x0CDF3309,
0x09A5017A,
0x5DC8D410,
0x4C12B91A,
0x710FB226,
0xBCF6030F,
0xFDFD8C0D,
0x47A32DA2,
0xF1BCC41D,
0xF85B2AEC,
};

unsigned int g_pack_lo_b_exp[] = {
0x0CDF2FB3,
0x09A52BE1,
0x5DC8E426,
0x4C12FA73,
0x710FFA38,
0xBCF6A126,
0xFDFDE43B,
0x47A30530,
0xF1BC55F7,
0xF85BAF75,
};

