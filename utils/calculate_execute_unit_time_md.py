import argparse
import os
import numpy as np

if __name__ == '__main__':
	
	parser = argparse.ArgumentParser()
	parser.add_argument('input_path')
	parser.add_argument('output_path')
	parser.add_argument('theoretical_path')
	args = parser.parse_args()
	
	with open(os.path.join(args.output_path, 'TIME_MEASUREMENT_dmesg.txt'), 'r') as f:

		exec_times = [float(line.strip().split(' ')[3]) - float(line.strip().split(' ')[2]) for line in f]
		unit_time = sum(exec_times) / len(exec_times) / 500

	print('unit time = %f' % unit_time)

	dir_list = os.listdir(args.input_path)
	dir_list.sort()
	theoretical_times = []
	error_times = []
	
	print('|file|process name|theoretical time|execution time|error|error percentage|')	
	print('|:---:|:---:|:---:|:---:|:---:|:---:|')	
	for filename in dir_list:
		
		print('|' + filename + '||||||')
		
		theoretical = {}
		if os.path.isdir(args.theoretical_path):

			with open(os.path.join(args.theoretical_path, filename), 'r') as f:

				for line in f:
					
					theoretical[line.strip().split(' ')[0]] = int(line.strip().split(' ')[1])
		
		prefix = filename.split('.')[0]
		stdout_path = os.path.join(args.output_path, prefix + '_stdout.txt')
		dmesg_path = os.path.join(args.output_path, prefix + '_dmesg.txt')
		
		with open(stdout_path, 'r') as f:
		
			pid_to_name = {line.strip().split(' ')[1]: line.strip().split(' ')[0] for line in f}

		with open(dmesg_path, 'r') as f:
		
			for line in f:
				
				line_list = line.strip().split(' ')
				name = pid_to_name[line_list[1]]
				exec_time = (float(line_list[3]) - float(line_list[2])) / unit_time
				error_time = exec_time - theoretical[name]
				theoretical_times.append(theoretical[name])
				error_times.append(error_time)
				
				print('||%s|%d|%.2f|%.2f|%.2f%%|' % (name, theoretical[name], round(exec_time, 2), round(error_time, 2), round(error_time / theoretical[name] * 100, 2)))
	
	theoretical_times = np.array(theoretical_times)
	error_times = np.array(error_times)
	average_theoretical_time = np.mean(theoretical_times)
	average_error_time = np.mean(error_times)
	average_abs_error_time = np.mean(np.abs(error_times))
	print('average theoretical times = %f' % average_theoretical_time)
	print('average error times = %f' % average_error_time)
	print('average abs error times = %f' % average_abs_error_time)
	print('average error percentange = %f' % (average_error_time / average_theoretical_time))
	print('average absolute error percentage = %f' % (average_abs_error_time / average_theoretical_time))
