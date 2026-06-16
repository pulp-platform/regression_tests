#define STATS 
#define STACK_SIZE 1024
#define MOUNT 1
#define UNMOUNT 0
#define CID 0
#define M_PI		3.14159265358979323846	/* pi */


inline float Sqrt(float x)
{
	float res;
	asm("fsqrt.s %0, %1"
		: "=f"(res)
		: "f"(x));
	return res;
}


#define BarrierCounter //if(pi_core_id() == 0){numBarr++;}
#define definePrefArr 							\
int cyclesArr [NUM_CORES];						\
int instrArr  [NUM_CORES];						\
int activeArr [NUM_CORES];						\
int ldEXTArr  [NUM_CORES];						\
int TCDMArr   [NUM_CORES];						\
int ldstallArr[NUM_CORES];						\
int imissArr  [NUM_CORES];						\
int ldEXTCYCArr  [NUM_CORES];					\
int stEXTCYCArr  [NUM_CORES];					\
int C11Arr    [NUM_CORES];						\
int C12Arr    [NUM_CORES];						\
int C13Arr    [NUM_CORES];						\
int C14Arr    [NUM_CORES];						\
long int AVGCycles = 0;   						\
long int AVGInstr  = 0;   						\
long int AVGActive = 0;   						\
long int AVGldEXT  = 0;   						\
long int AVGTCDM   = 0;   						\
long int AVGLdstall= 0;   						\
long int AVGImiss  = 0;   						\
long int AVGldEXTCYC  = 0;   					\
long int AVGstEXTCYC  = 0;   					\
long int AVGC11  = 0;   						\
long int AVGC12  = 0;   						\
long int AVGC13  = 0;   						\
long int AVGC14  = 0;   						\

#define printPerfCounters										\
unsigned long cycles   = pi_perf_read (PI_PERF_CYCLES);			\
unsigned long instr    = pi_perf_read (PI_PERF_INSTR);		 	\
unsigned long active   = pi_perf_read (PI_PERF_ACTIVE_CYCLES);	\
unsigned long ldext    = pi_perf_read (PI_PERF_LD_EXT);		 	\
unsigned long tcdmcont = pi_perf_read (PI_PERF_TCDM_CONT);		\
unsigned long ldstall  = pi_perf_read (PI_PERF_LD_STALL);		\
unsigned long imiss    = pi_perf_read (PI_PERF_IMISS);		 	\
unsigned long ldEXTCYC = pi_perf_read (PI_PERF_LD_EXT_CYC);   	\
unsigned long stEXTCYC = pi_perf_read (PI_PERF_ST_EXT_CYC);   	\
unsigned long C11      = pi_perf_read (0x11);		 			\
unsigned long C12      = pi_perf_read (0x12);		 			\
unsigned long C13      = pi_perf_read (0x13);		 			\
unsigned long C14      = pi_perf_read (0x14);		 			\
																\
cyclesArr [pi_core_id()] = cycles;								\
instrArr  [pi_core_id()] = instr;								\
activeArr [pi_core_id()] = active;								\
ldEXTArr  [pi_core_id()] = ldext;								\
ldEXTCYCArr[pi_core_id()] = ldEXTCYC;							\
stEXTCYCArr[pi_core_id()] = stEXTCYC;							\
TCDMArr   [pi_core_id()] = tcdmcont;							\
ldstallArr[pi_core_id()] = ldstall;								\
imissArr  [pi_core_id()] = imiss;								\
C11Arr    [pi_core_id()] = C11; 								\
C12Arr    [pi_core_id()] = C12; 								\
C13Arr    [pi_core_id()] = C13; 								\
C14Arr    [pi_core_id()] = C14; 								\
pi_cl_team_barrier();											\
if(pi_core_id() == 0){											\
	for (int i = 0; i < NUM_CORES; i++){						\
		AVGCycles  += cyclesArr [i];							\
		AVGInstr   += instrArr  [i];							\
		AVGActive  += activeArr [i];							\
		AVGldEXT   += ldEXTArr  [i];							\
		AVGTCDM    += TCDMArr   [i];							\
		AVGLdstall += ldstallArr[i];							\
		AVGImiss   += imissArr  [i];							\
		AVGldEXTCYC   += ldEXTCYCArr  [i];						\
		AVGstEXTCYC   += stEXTCYCArr  [i];						\
		AVGC11     += C11Arr  [i];  							\
		AVGC12     += C12Arr  [i];  							\
		AVGC13     += C13Arr  [i];  							\
		AVGC14     += C14Arr  [i];  							\
		printf("%d => %d\t %d\n",i,cyclesArr[i],AVGCycles);		\
	}															\
	printf("%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\
\t%lu\t%lu\t%lu\t%lu\t%lu\n",									\
	AVGCycles/NUM_CORES,AVGInstr/NUM_CORES,		 				\
	AVGActive/NUM_CORES,AVGldEXT/NUM_CORES,		 				\
	AVGTCDM/NUM_CORES,AVGLdstall/NUM_CORES,		 				\
	AVGImiss/NUM_CORES,AVGldEXTCYC/NUM_CORES,AVGstEXTCYC/NUM_CORES, \
	AVGC11/NUM_CORES,AVGC12/NUM_CORES,AVGC13/NUM_CORES,AVGC14/NUM_CORES);\
	for (int i = 0; i < NUM_CORES; i++){						\
		printf("%d\t cyclesArr = %lu\n",i,cyclesArr[i]);		\
		printf("%d\t activeArr = %lu\n",i,activeArr[i]);		\
		printf("%d\t instrArr = %lu\n",i,instrArr[i]);			\
		printf("%d\t ldEXTArr = %lu\n",i,ldEXTArr[i]);			\
		printf("%d\t TCDMArr = %lu\n",i,TCDMArr[i]);			\
		printf("%d\t ldstallArr = %lu\n",i,ldstallArr[i]);		\
		printf("%d\t imissArr = %lu\n",i,imissArr[i]);			\
		printf("%d\t ldEXTCYC = %lu\n",i,ldEXTCYCArr[i]);		\
		printf("%d\t stEXTCYC = %lu\n",i,stEXTCYCArr[i]);		\
		printf("%d\t C11Arr = %lu\n",i,C11Arr[i]);				\
		printf("%d\t C12Arr = %lu\n",i,C12Arr[i]);				\
		printf("%d\t C13Arr = %lu\n",i,C13Arr[i]);				\
		printf("%d\t C14Arr = %lu\n",i,C14Arr[i]);				\
		printf("\n");											\
	}															\
}		 										 				\

void initialMatrixMatrix(float *inp,int rowSize,int colSize,float *initMatrix){
	for (int i = 0; i < rowSize; i++){
		for (int j = 0; j < colSize; j++){
			inp[i*colSize+j] = initMatrix[i*colSize+j];
		}
	}
}

void initialMatrixMatrixPP(float **inp,int rowSize,int colSize,float **initMatrix){
	for (int i = 0; i < rowSize; i++){
		for (int j = 0; j < colSize; j++){
			inp[i][j] = initMatrix[i][j];
		}
	}
}

void initialMatrixConst (float *inp,int rowSize,int colSize,float initValue){
	for (int i = 0; i < rowSize; i++){
		for (int j = 0; j < colSize; j++){
			inp[i*colSize+j] = initValue;
		}
	}
}

void initialMatrixConstPP (float **inp,int rowSize,int colSize,float initValue, int core_id){
	#if NUM_CORES > 1
		int blockSize_COL = colSize / NUM_CORES;
		int start_COL = core_id * blockSize_COL;
		if (core_id == (NUM_CORES - 1)){
			blockSize_COL = colSize - (NUM_CORES - 1) * blockSize_COL;
		}
		int end_COL = start_COL + blockSize_COL;
		for (int i = 0; i < rowSize; i++){
			for (int j = start_COL; j < end_COL; j++){
				inp[i][j] = initValue;
			}
		}
	#else
		for (int i = 0; i < rowSize; i++){
			for (int j = 0; j < colSize; j++){
				inp[i][j] = initValue;
			}
		}
	#endif

}

void initialMatrixEYE (float *inp,int rowSize,int colSize){
	for (int i = 0; i < rowSize; i++){
		for (int j = 0; j < colSize; j++){
			if(i == j){
				inp[i*colSize+j] = 1;
			}else{
				inp[i*colSize+j] = 0;
			}
		}
	}
}

void initialMatrixEYEPP (float **inp,int rowSize,int colSize){
	for (int i = 0; i < rowSize; i++){
		for (int j = 0; j < colSize; j++){
			if(i == j){
				inp[i][j] = 1;
			}else{
				inp[i][j] = 0;
			}
		}
	}
}


void printMatrix(float *inp,int rowSize,int colSize,const char name[], int transposed){
	printf("\n\n%s = \n",name);
	for (int i = 0; i < rowSize; i++){
		for (int j = 0; j < colSize; j++){
			if(transposed){
				printf("%.20f ",inp[j*rowSize+i]);
			}else{
				printf("%.20f ",inp[i*colSize+j]);
			}
		}    
		printf("\n");
	}
}

void printMatrixPP(float **inp,int rowSize,int colSize,const char name[], int transposed){
	printf("\n\n%s = \n",name);
	for (int i = 0; i < rowSize; i++){
		for (int j = 0; j < colSize; j++){
			if(transposed){
				printf("%.20f ",inp[j][i]);
			}else{
				printf("%.20f ",inp[i][j]);
			}
		}    
		printf("\n");
	}
}
