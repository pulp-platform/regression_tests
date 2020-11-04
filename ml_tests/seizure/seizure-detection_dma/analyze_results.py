#!/usr/bin/python

import sys, os, glob
import subprocess
import shlex
import array
import numpy

##############################################
# configuration
builddirs = ["private_simple","private_iter","shared_iter","shared_iter_8t1", "shared_iter_8t1_2mac", "shared_iter_2t1", "shared", "shared_8t1", "shared_8t1_2mac", "shared_2t1"]
jdx=int(sys.argv[1])

##############################################
#create output directory
if not os.path.exists('results'):
	os.mkdir('results')

if not os.path.exists('results/'+builddirs[jdx]):
        os.mkdir('results/'+builddirs[jdx])

##############################################
# profiling list
prof_list = ["CYCLES", "INSTR", "CINSTR", "LD_STALL", "IMISS", "LD", "ST", "BRANCH", "BTAKEN", "APU_TY_CONF", "APU_CONT", "APU_DEP", "APU_WB", "TCDM"]
prof_len = len(prof_list)
func_id=['"PCA"', '"COVARIANCE"','"HOUSEHOLDER"','"ACCUMULATE"','"DIAGONALIZE"','"END PC"','"END DWT"','"END SVM"','"Kernel completed in"',]
func_name=['PCA','COV','HOU','ACC','DIA','EPC','DWT','SVM','TOT']
func_len = len(func_id)

##############################################
# clear files
result_filename = "results/"+builddirs[jdx]+"/summary_"+builddirs[jdx]+".m"
f = open(result_filename,'w')
f.close()
fsummary = open('results/'+builddirs[jdx]+'/summary_'+builddirs[jdx],'w')
f.close()

##############################################
#loop over prof_list and func_id

for ind_func in range (0, func_len):
	
	# clear tmp files
	for idx in range (0, prof_len):
		f = open('results/'+builddirs[jdx]+'/'+prof_list[idx],'w')
		f.close()

	f = open('results/'+builddirs[jdx]+'/names','w')
	f.close()
	f = open('results/'+builddirs[jdx]+'/res','w')
	f.close()
	

##############################################
#parse results and write to files
	for k in range (0, prof_len-1):
		cmd_prof = ['cat ` find '+builddirs[jdx]+'/ri5cyv2*_*cores/stdout/stdout_fake_pe0_0 ` | grep -A 21 '+func_id[ind_func]+' | grep "Perf '+prof_list[k]+':" | awk -F \' \' \'{print $3}\' >> results/'+builddirs[jdx]+'/'+prof_list[k]]
		subprocess.call(cmd_prof,shell=True)
# tcdm
	cmd_tcdm = ['cat ` find '+builddirs[jdx]+'/ri5cyv2*_*cores/stdout/stdout_fake_pe0_0 ` | grep -A 21 '+func_id[ind_func]+' | grep "Perf '+prof_list[prof_len-1]+'" | awk -F \' \' \'{print $4}\' >> results/'+builddirs[jdx]+'/'+prof_list[prof_len-1]]
	subprocess.call(cmd_tcdm,shell=True)

#names
	cmd_names  = ['find '+builddirs[jdx]+'/ri5cyv2*_*cores/*.s19 >> results/'+builddirs[jdx]+'/names']
    
	cmd_res = ['cat ` find '+builddirs[jdx]+'/ri5cyv2*_*cores/stdout/stdout_fake_pe0_0 ` | grep "RESULT"  >> results/'+builddirs[jdx]+'/res']

	subprocess.call(cmd_names,shell=True)
	subprocess.call(cmd_res,shell=True)

##############################################
# parse files and write to single file
	num_lines = sum(1 for line in open('results/'+builddirs[jdx]+'/names'))

	prof_dif = numpy.zeros((num_lines, prof_len))

	if (ind_func == 0):
		prof_abs = numpy.zeros((num_lines, prof_len))
	names = []
	res = []

	for idx in range (0, prof_len):
		k=0
		with open('results/'+builddirs[jdx]+'/'+prof_list[idx], 'r') as f:
			for line in f:
				if (ind_func == 0 or ind_func == func_len-1):
					prof_dif[k][idx] = int(line)
				else:
					prof_dif[k][idx] = int(line) - prof_abs[k][idx]
					prof_abs[k][idx] = int(line)
				k=k+1
		f.close()

	with open('results/'+builddirs[jdx]+'/names', 'r') as f:
		names = f.read().replace("main.s19","").replace(builddirs[jdx]+"/ri5cyv2-rvc_wolfe_0_gcc_bench_omp_libgomp_","").replace("/","").splitlines()
	f.close()

	with open('results/'+builddirs[jdx]+'/res', 'r') as f:
		res = f.read().replace("RESULT:0","true").replace("RESULT:1","false").splitlines()
	f.close()

##############################################
# excel output
	fsummary = open('results/'+builddirs[jdx]+'/summary_'+builddirs[jdx],'a')

	fsummary.write(func_id[ind_func]+"\n")
	fsummary.write('AppName ; Version ; ')
	for idx in range (0,prof_len):
		fsummary.write(prof_list[idx]+' ; ')
	fsummary.write(' test_result ; \n')

	for idx in range (0,num_lines):
		fsummary.write('\''+names[idx]+'\' ; \''+builddirs[jdx]+'\' ; ')
		for k in range (0, prof_len):
			fsummary.write(str(prof_dif[idx][k])+' ; ')
		fsummary.write(' '+res[idx]+' \n')
	fsummary.close()

##############################################
# matlab output
	result_filename = "results/"+builddirs[jdx]+"/summary_"+builddirs[jdx]+".m"
	f = open(result_filename,'a')

	for idx in range (0, prof_len):
		f.write(func_name[ind_func]+'_'+prof_list[idx]+' = [ ...\n')
		for k in range (0, num_lines):
			f.write(str(prof_dif[k][idx])+',...\n')
		f.write('];\n')
	f.close()

