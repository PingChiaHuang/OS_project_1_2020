import argparse
import os

if __name__ == '__main__':
	
	parser = argparse.ArgumentParser()
	parser.add_argument('input_path')
	parser.add_argument('executive_file')
	args = parser.parse_args()

	os.makedirs('theoretical', exist_ok = True)
	
	dir_list = os.listdir(args.input_path)
	dir_list.sort()
	
	for filename in dir_list:

		print(filename)

		prefix = filename.split('.')[0]
		stdout_path = os.path.join('theoretical', prefix + '.txt')
		
		os.system('dmesg -c')
		os.system('./%s < %s > %s' % (args.executive_file, os.path.join(args.input_path, filename), stdout_path))
