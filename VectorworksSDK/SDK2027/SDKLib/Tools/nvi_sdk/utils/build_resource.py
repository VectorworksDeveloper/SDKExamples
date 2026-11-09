#!/usr/bin/env python

import os, sys
from optparse import OptionParser

from file_monitor import Monitor
import resources

def get_monitor_database_dirpath(options):
	dirpath = ''
	
	if not options.intermediate_files_dir:
		dirpath = options.resource_dir_src + '.build'
		if options.verbose:
			print '\tIntermediate files directory not found, using "%s".' % dirpath
	else:
		dirpath = options.intermediate_files_dir
		if options.verbose:
			print '\tIntermediate files directory: "%s".' % dirpath
	
	return dirpath

# -----------------------------------------------------------------------------

def have_files_been_modified(options):
	watch_dir_record = get_monitor_database_dirpath(options)
	
	found_modification = False
	
	m = Monitor(watch_dir_record)
	for root_path, directory_names, file_names in os.walk(options.resource_dir_src):
		for fileName in file_names:
			if fileName != '.DS_Store':
				file_path = os.path.join(root_path, fileName)
				if not m.file_is_current(file_path):
					if options.verbose:
						print '\t%s has been modified.' % fileName
						
					found_modification = True
					m.record_mod_time(file_path)
	
	m.takedown()
	
	return found_modification

# -----------------------------------------------------------------------------

def clean(options):
	output_file = resources.get_output_filepath(options.resource_dir_dst, options.product_name)
	output_file = os.path.normpath(output_file)
	
	if options.verbose:
		print 'Removing resource file "%s".' % output_file
		
	if os.path.exists(output_file):
		os.remove(output_file)
	
	m = Monitor(get_monitor_database_dirpath(options))
	m.reset()
	
# -----------------------------------------------------------------------------

def build(options):
	output_file = resources.get_output_filepath(options.resource_dir_dst, options.product_name)
	
	does_output_file_exist = os.path.exists(output_file)
	have_resources_been_modified = have_files_been_modified(options)
	
	if options.verbose:
		existStr = 'Exists'
		if not does_output_file_exist:
			existStr = 'Does\'nt exist'
			
		print 'Checking existence of "%s". %s.' % (output_file, does_output_file_exist)

		modifiedStr = 'Yes'
		if not have_resources_been_modified:
			modifiedStr = 'No'
			
		print 'Have resources been modified? %s.' % have_resources_been_modified
		
	if not does_output_file_exist or have_resources_been_modified:
		if options.verbose:
			print 'Building resource file "%s".' % output_file
			print 'Intermediate files may be found at "%s".' % options.intermediate_files_dir
		
		resources.compress(options.resource_dir_src, options.resource_dir_dst, options.product_name)
	
# -----------------------------------------------------------------------------

def build_option_parser():
	usage = "usage: %prog [options] arg1 arg2 arg3"
	p = OptionParser(usage)
	
	p.add_option("-i", "--input_dir_path", dest="resource_dir_src", help="the file path to the \"Resource\" directory to be compressed into a resource zip file.")
	p.add_option("-o", "--output_dir_path", dest="resource_dir_dst", help="the file path to the directory where the resource zip file will be created.")
	p.add_option("-n", "--product_name", dest="product_name", help="the name that will be used as the first component of the resource specifier. For example, for Vectorworks, the product name is \"Vectorworks\".")
	p.add_option("-b", "--build", action="store_true", help="this will build the resource file", default=True)
	p.add_option("-c", "--clean", action="store_true", help="this will delete the resource file", default=False)
	p.add_option("-x", "--intermediate_files_dir", help="the directory where intermediate files will be stored", default=None)
	p.add_option("-v", "--verbose", action="store_true", help="display information on what is being processed", default=False)
	return p


# -----------------------------------------------------------------------------

def normalize_dir_path(dir_path):
	if dir_path[-1] == ' ':
		dir_path = dir_path[0:-1]
	
	return os.path.normpath(dir_path)

# -----------------------------------------------------------------------------

def main():
	p = build_option_parser()
	
	(options, args) = 	p.parse_args()
	
	if not options.resource_dir_src or not options.resource_dir_dst or not options.product_name:
		print 'options.resource_dir_src:', options.resource_dir_src
		print 'options.resource_dir_dst:', options.resource_dir_dst
		print 'options.product_name:', options.product_name
		p.print_help()
		p.error("incorrect number of arguments")
	
	if sys.platform == 'win32':
		options.resource_dir_src = normalize_dir_path(options.resource_dir_src)
		options.resource_dir_dst = normalize_dir_path(options.resource_dir_dst)
		if options.intermediate_files_dir:
			options.intermediate_files_dir = normalize_dir_path(options.intermediate_files_dir)
	
	if options.clean or (sys.platform == 'darwin' and os.environ['ACTION'] == 'clean'):
		clean(options)
		print 'Clean complete'
	
	if (not options.build) and (sys.platform == 'darwin' and os.environ['ACTION'] == ''):
		print 'os.environ[\'ACTION\']:', os.environ['ACTION']
		options.build = True
		
	if options.build:
		build(options)
		print 'Build complete'
	
if __name__ == '__main__':
	main()