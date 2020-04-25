import argparse
import os
import numpy as np

if __name__ == '__main__':
	
	parser = argparse.ArgumentParser()
	parser.add_argument('input_path')
	parser.add_argument('output_path')
	parser.add_argument('--print_input', '-pi', action = 'store_true')
	parser.add_argument('--print_theoretical', '-pt', action = 'store_true')
	parser.add_argument('--diff', '-d', action = 'store_false')
	args = parser.parse_args()
	
	with open(os.path.join(args.output_path, 'TIME_MEASUREMENT_dmesg.txt'), 'r') as f:

		exec_times = [float(line.strip().split(' ')[4]) - float(line.strip().split(' ')[3]) for line in f]
		unit_time = sum(exec_times) / len(exec_times) / 500

	print('unit time = %f' % unit_time)

	dir_list = os.listdir(args.input_path)
	dir_list.sort()
	
	for filename in dir_list:
		
		print(filename)
		print()
		
		if args.print_input == True:

			with open(os.path.join(args.input_path, filename), 'r') as f:

				for line in f:

					print(line.strip())
			print()
		
		theoretical = {}
		if os.path.isdir('theoretical'):

			with open(os.path.join('theoretical', filename), 'r') as f:

				for line in f:
					
					if args.print_theoretical == True:
						print(line.strip())
					theoretical[line.strip().split(' ')[0]] = int(line.strip().split(' ')[1])
		
		if args.print_theoretical == True:
			print()
		
		prefix = filename.split('.')[0]
		stdout_path = os.path.join(args.output_path, prefix + '_stdout.txt')
		dmesg_path = os.path.join(args.output_path, prefix + '_dmesg.txt')
		
		with open(stdout_path, 'r') as f:
		
			pid_to_name = {line.strip().split(' ')[1]: line.strip().split(' ')[0] for line in f}

		with open(dmesg_path, 'r') as f:
		
			for line in f:
				
				line_list = line.strip().split(' ')
				name = pid_to_name[line_list[2]]
				exec_time = float(line_list[4]) - float(line_list[3])
				
				if args.diff:
				
					if np.abs(theoretical[name] - round(exec_time / unit_time, 3)) / theoretical[name] > 0.1:
						print('%s theoretical time = %d exec time = %f' % (name, theoretical[name], round(exec_time / unit_time, 3)))
				
				else:
						print('%s theoretical time = %d exec time = %f' % (name, theoretical[name], round(exec_time / unit_time, 3)))
		
		print()
