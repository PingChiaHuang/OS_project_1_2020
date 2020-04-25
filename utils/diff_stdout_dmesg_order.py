import argparse
import os

if __name__ == '__main__':
	
	parser = argparse.ArgumentParser()
	parser.add_argument('input_path')
	parser.add_argument('output_path')
	args = parser.parse_args()
	
	dir_list = os.listdir(args.input_path)
	dir_list.sort()
	
	for filename in dir_list:

		prefix = filename.split('.')[0]
		stdout_path = os.path.join(args.output_path, prefix + '_stdout.txt')
		dmesg_path = os.path.join(args.output_path, prefix + '_dmesg.txt')
		
		with open(stdout_path, 'r') as std:
	
			with open(dmesg_path, 'r') as dme:
				
				same = True
				std_lines = std.readlines()
				dme_lines = dme.readlines()
				
				for i in range(len(std_lines)):
					
					std_pid = std_lines[i].strip().split(' ')[1]		
					dme_pid = dme_lines[i].strip().split(' ')[1]

					if std_pid != dme_pid:

						same = False

				if len(std_lines) != len(dme_lines):
					
					same = False

		print(prefix + ' is same: ' + str(same))		
