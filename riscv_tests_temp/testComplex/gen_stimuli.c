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
#include<stdio.h>
#include<stdlib.h>

#define N 100

int main()
{

   FILE * fp = fopen ("number_of_stimuli.h","w");
   fprintf(fp, "#ifndef NUM_STIM\n#define NUM_STIM\n #define N %d\n#endif",N );
   fclose(fp);
   //generate pv_complex
   pv_complex(0,"pv_complex_stimuli.h", "PVCOMPLEX");
   //generate pv_complex div2
   pv_complex(1,"pv_complex_stimuli_div2.h", "PVCOMPLEX_DIV2");
   //generate pv_complex div4
   pv_complex(2,"pv_complex_stimuli_div4.h", "PVCOMPLEX_DIV4");
   //generate pv_complex div8
   pv_complex(3,"pv_complex_stimuli_div8.h", "PVCOMPLEX_DIV8");
   //generate cplxbitman
   cplxbitman("cplxbitman_stimuli.h", "CLPBITMAN");
   //generate pv.cplxmul.h.r
   cplxmul(15, 1, "pv_cplxmul_real_stimuli.h", "PV_CPLXMUL_REAL");
   //generate pv.cplxmul.h.r.div2
   cplxmul(16, 1, "pv_cplxmul_real_stimuli_div2.h", "PV_CPLXMUL_REAL_DIV2");
   //generate pv.cplxmul.h.r.div4
   cplxmul(17, 1, "pv_cplxmul_real_stimuli_div4.h", "PV_CPLXMUL_REAL_DIV4");
   //generate pv.cplxmul.h.r.div8
   cplxmul(18, 1, "pv_cplxmul_real_stimuli_div8.h", "PV_CPLXMUL_REAL_DIV8");
   //generate pv.cplxmul.h.i
   cplxmul(15, 0, "pv_cplxmul_img_stimuli.h", "PV_CPLXMUL_IMG");
   //generate pv.cplxmul.h.i.div2
   cplxmul(16, 0, "pv_cplxmul_img_stimuli_div2.h", "PV_CPLXMUL_IMG_DIV2");
   //generate pv.cplxmul.h.i.div4
   cplxmul(17, 0, "pv_cplxmul_img_stimuli_div4.h", "PV_CPLXMUL_IMG_DIV4");
   //generate pv.cplxmul.h.i.div8
   cplxmul(18, 0, "pv_cplxmul_img_stimuli_div8.h", "PV_CPLXMUL_IMG_DIV8");

return 0;
}

void pv_complex(int div, char* fileName, char* ifdef_tag)
{
        int i;
        short a0[N], b0[N], a1[N], b1[N];
        short r0, r1;
        int c[N];
        FILE * fp;
        char str[10], strdot[10];
        time_t t;


        /* Intializes random number generator */
        srand((unsigned) time(&t));


        fp = fopen (fileName,"w");

        fprintf(fp, "#ifndef %s\n",ifdef_tag);
        fprintf(fp, "#define %s\n",ifdef_tag);

        if(div == 0)
                str[0] = 0;
        else if (div == 1)
                strcpy(str,"div2");
        else if (div == 2)
                strcpy(str,"div4");
        else if (div == 3)
                strcpy(str,"div8");

        if(div == 0)
                str[0] = 0;
        else if (div == 1)
                strcpy(strdot,".div2");
        else if (div == 2)
                strcpy(strdot,".div4");
        else if (div == 3)
                strcpy(strdot,".div8");


        fprintf(fp, "int cplx_opA%s[] = {\n",str);
        for(i=0;i<N;i++){
            a0[i] = rand();
            a1[i] = rand();
            int a = (a1[i] << 16) | (a0[i] & 0xFFFF);
            fprintf(fp, "0x%x,\n",a);
        }
        fprintf(fp, "};\n\n");

        fprintf(fp, "int cplx_opB%s[] = {\n",str);
        for(i=0;i<N;i++){
            b0[i] = rand();
            b1[i] = rand();
            int b = (b1[i] << 16) | (b0[i] & 0xFFFF);
            fprintf(fp, "0x%x,\n",b);
        }
        fprintf(fp, "};\n\n");

        fprintf(fp, "int subrotmj_opC%s[] = {\n",str);

        for(i=0;i<N;i++)
        {
            r1    = (short)(((b0[i] - a0[i]) & 0xFFFF)) >> div;
            r0    = (short)(((a1[i] - b1[i]) & 0xFFFF)) >> div;
            c[i]  = (r1 << 16) | (r0 & 0xFFFF);
            fprintf(fp, "0x%x,\n",c[i]);
        }
        fprintf(fp, "};\n\n");

        if(div==0){
            fprintf(fp, "int cplxconj_opC%s[] = {\n",str);
            for(i=0;i<N;i++)
            {
                r0    = a0[i];
                r1    = -a1[i];
                c[i]  = (r1 << 16) | (r0 & 0xFFFF);
                fprintf(fp, "0x%x,\n",c[i]);
            }

            fprintf(fp, "};\n\n");
        }

        if(div!=0)
        {
            fprintf(fp, "int cplxadd_opC%s[] = {\n",str);
            for(i=0;i<N;i++)
            {
                r0    = (short)(((a0[i] + b0[i]) & 0xFFFF)) >> div;
                r1    = (short)(((a1[i] + b1[i]) & 0xFFFF)) >> div;
                c[i]  = (r1 << 16) | (r0 & 0xFFFF);
                fprintf(fp, "0x%x,\n", c[i]);
            }

            fprintf(fp, "};\n\n");
            //fprintf(fp, "\"pv.add.h%s \%[c], \%[a], \%[b]\"\n", str);
            fprintf(fp, "int cplxsub_opC%s[] = {\n",str);
            for(i=0;i<N;i++)
            {
                r0    = (short)(((a0[i] - b0[i]) & 0xFFFF)) >> div;
                r1    = (short)(((a1[i] - b1[i]) & 0xFFFF)) >> div;
                c[i]  = (r1 << 16) | (r0 & 0xFFFF);
                fprintf(fp, "0x%x,\n",c[i]);
            }

            fprintf(fp, "};\n\n");
            //printf("\"pv.sub.h%s \%[c], \%[a], \%[b]\"\n", str);
        }

        fprintf(fp, "#endif\n");
        fclose(fp);
        return;
}

void cplxmul(int div, int r, char* fileName, char* ifdef_tag)
{
    int i;
    short a0[N], b0[N], a1[N], b1[N];
    int   c[N],cRes[N], r0, r1;
    char str[10];
    FILE * fp;
    time_t t;


    /* Intializes random number generator */
    srand((unsigned) time(&t));

    fp = fopen (fileName,"w");
    fprintf(fp, "#ifndef %s\n",ifdef_tag);
    fprintf(fp, "#define %s\n",ifdef_tag);
    if(div == 15)
           str[0] = 0;
    else if (div == 16)
        strcpy(str,"div2");
    else if (div == 17)
        strcpy(str,"div4");
    else if (div == 18)
        strcpy(str,"div8");


    fprintf(fp,"int cplxmul_opA%s%s[] = {\n",r? "r_" : "i_", str);
    for(i=0;i<N;i++){
        a0[i] = rand();
        a1[i] = rand();
        int a = (a1[i] << 16) | (a0[i] & 0xFFFF);
        fprintf(fp,"0x%x,\n",a);
    }
    fprintf(fp,"};\n\n");

    fprintf(fp,"int cplxmul_opB%s%s[] = {\n",r? "r_" : "i_", str);
    for(i=0;i<N;i++){
        b0[i] = rand();
        b1[i] = rand();
        int b = (b1[i] << 16) | (b0[i] & 0xFFFF);
        fprintf(fp,"0x%x,\n",b);
    }
    fprintf(fp,"};\n\n");

    fprintf(fp,"int cplxmul_opC%s%s[] = {\n",r? "r_" : "i_", str);
    for(i=0;i<N;i++){
        c[i] = rand();
        fprintf(fp,"0x%x,\n",c[i]);
    }
    fprintf(fp,"};\n\n");

    fprintf(fp,"int cplxmul_opCRes%s%s[] = {\n",r? "r_" : "i_", str);

    for(i=0;i<N;i++)
    {
        if(r) {
        r0       = a0[i]*b0[i];
        r1       = a1[i]*b1[i];
        cRes[i]  = (r0 - r1) >> div;
        fprintf(fp,"0x%x,\n",(c[i] & 0XFFFF0000) | (cRes[i] & 0xFFFF));
        } else {
        r0       = a0[i]*b1[i];
        r1       = a1[i]*b0[i];
        cRes[i]  = (r0 + r1) >> div;
        fprintf(fp,"0x%x,\n",((cRes[i] & 0xFFFF) << 16) | (c[i] & 0xFFFF));
        }
     }
     fprintf(fp,"};\n\n");

    //printf("\"pv.cplxmul.h.%s%s \%[c], \%[a], \%[b]\"\n",r ? "r" : "i", str);
    fprintf(fp, "#endif\n");
    fclose(fp);

    return;
}

void cplxbitman(char* fileName, char* ifdef_tag)
{
        int i;
        short a0[N], b0[N], a1[N], b1[N];
        short r0, r1;
        int c[N];
        FILE * fp;
        time_t t;

       /* Intializes random number generator */
       srand((unsigned) time(&t));

        fp = fopen (fileName,"w");


        fprintf(fp, "#ifndef %s\n",ifdef_tag);
        fprintf(fp, "#define %s\n",ifdef_tag);

        fprintf(fp,"int cplxbitman_opA[] = {\n");

        for(i=0;i<N;i++){
            a0[i] = rand();
            a1[i] = rand();
            int a = (a1[i] << 16) | (a0[i] & 0xFFFF);
            fprintf(fp,"0x%x,\n",a);
        }
        fprintf(fp,"};\n\n");

        fprintf(fp,"int cplxbitman_opB[] = {\n");

        for(i=0;i<N;i++){
           b0[i] = rand();
           b1[i] = rand();
           int b = (b1[i] << 16) | (b0[i] & 0xFFFF);
           fprintf(fp,"0x%x,\n",b);
        }
        fprintf(fp,"};\n\n");

        fprintf(fp,"int cplxpack_opC[] = {\n");

        for(i=0;i<N;i++)
        {
                r0    = b1[i];
                r1    = a1[i];
                c[i]  = (r1 << 16) | (r0 & 0xFFFF);
                fprintf(fp,"0x%x,\n",c[i]);
         }
        fprintf(fp,"};\n\n");

        fprintf(fp, "#endif\n");
        fclose(fp);

        return;
}
