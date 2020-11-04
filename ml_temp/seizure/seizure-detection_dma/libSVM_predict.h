#ifndef _SVM_PREDICT_H
#define _SVM_PREDICT_H

#ifdef __cplusplus
extern "C" {
#endif

;

//extern int libsvm_version;

typedef struct svm_node
{
	int index;
	float value;
} svm_node;

//typedef struct svm_problem
//{
//	int l;
//	double *y;
//	struct svm_node **x;
//} svm_problem;

enum { C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR };	/* svm_type */
enum { LINEAR, POLY, RBF, SIGMOID, PRECOMPUTED }; /* kernel_type */

typedef struct svm_parameter
{
	int svm_type;
	int kernel_type;
	int degree;	/* for poly */
	float gamma;	/* for poly/rbf/sigmoid */
	double coef0;	/* for poly/sigmoid */

	/* these are for training only */
//	double cache_size; /* in MB */
//	double eps;	/* stopping criteria */
//	double C;	/* for C_SVC, EPSILON_SVR and NU_SVR */
//	int nr_weight;		/* for C_SVC */
//	int *weight_label;	/* for C_SVC */
//	double* weight;		/* for C_SVC */
//	double nu;	/* for NU_SVC, ONE_CLASS, and NU_SVR */
//	double p;	/* for EPSILON_SVR */
//	int shrinking;	/* use the shrinking heuristics */
//	int probability; /* do probability estimates */
} svm_parameter;

//
// svm_model
// 
typedef struct svm_model
{
	struct svm_parameter param;	/* parameter */
	int nr_class;		/* number of classes, = 2 in regression/one class svm */
	int l;			/* total #SV */
	struct svm_node **SV;		/* SVs (SV[l]) */
	float **sv_coef;	/* coefficients for SVs in decision functions (sv_coef[k-1][l]) */
	float *rho;		/* constants in decision functions (rho[k*(k-1)/2]) */
	float *probA;		/* pariwise probability information */
	float *probB;
	int *sv_indices;        /* sv_indices[0,...,nSV-1] are values in [1,...,num_traning_data] to indicate SVs in the training set */

	/* for classification only */

	int *label;		/* label of each class (label[k]) */
	int *nSV;		/* number of SVs for each class (nSV[k]) */
				/* nSV[0] + nSV[1] + ... + nSV[k-1] = l */
	/* XXX */
	int free_sv;		/* 1 if svm_model is created by svm_load_model*/
				/* 0 if svm_model is created by svm_train */
} svm_model;

/* functions */
//static char* readline(FILE *input);
void exit_input_error(int line_num);
void exit_with_help();

//void predict(FILE *input, FILE *output);
float kernel_function(const svm_node *x, const svm_node *y, const svm_parameter param);
//double kernel_function(svm_node *x, svm_node *y, svm_parameter& param);

//float svm_predict_values(const svm_model *model, const svm_node *x, float* dec_values);
float svm_predict_values( const svm_node *x, float* dec_values);
//struct svm_model *svm_load_model(const char *model_file_name);
//struct svm_model *svm_load_model();


void svm_free_model_content(struct svm_model *model_ptr);
void svm_free_and_destroy_model(struct svm_model **model_ptr_ptr);
void svm_destroy_param(struct svm_parameter *param);

//const char *svm_check_parameter(const struct svm_problem *prob, const struct svm_parameter *param);
//int svm_check_probability_model(const struct svm_model *model);

//void svm_set_print_string_function(void (*print_func)(const char *));

//#ifdef __cplusplus
//}
//#endif

#endif /* _LIBSVM_H */
