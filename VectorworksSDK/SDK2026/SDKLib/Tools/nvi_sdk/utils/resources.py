#!/usr/bin/env python

import os
import sys
import zipfile
from optparse import OptionParser

def get_output_filepath(output_dir, resource_name):
	return os.path.join(output_dir, resource_name) + ".vwr"
# -----------------------------------------------------------------------------

def compress(resource_dir, output_dir, resource_name):
	output_file = get_output_filepath(output_dir, resource_name)

	output_filedir = os.path.split(output_file)[0]
	if not os.path.exists(output_filedir):
		try:
			# make sure the directory already exists; ignore any errors if it already exists.
			os.makedirs(output_filedir)
		except OSError:
			pass

	resourcesZipFile = zipfile.ZipFile(output_file, "w", compression=zipfile.ZIP_DEFLATED)

	for rootPath, directoryNames, fileNames in os.walk(resource_dir):
		for fileName in fileNames:
			filePath = os.path.join(rootPath, fileName)
			archiveName = filePath.replace(resource_dir, resource_name)
			resourcesZipFile.write(filePath, archiveName)

# -----------------------------------------------------------------------------

def build_option_parser():
	usage = "usage: %prog [options] arg1 arg2 arg3"
	parser = OptionParser(usage)
	
	parser.add_option("-i", "--input_dir_path", dest="resource_dir_src", help="the file path to the \"Resource\" directory to be compressed into a resource zip file.")
	parser.add_option("-o", "--output_dir_path", dest="resource_dir_dst", help="the file path to the directory where the resource zip file will be created.")
	parser.add_option("-n", "--product_name", dest="product_name", help="the name that will be used as the first component of the resource specifier. For example, for Vectorworks, the product name is \"Vectorworks\".")

	return parser

# -----------------------------------------------------------------------------

def main():
	parser = build_option_parser()
	
	(options, args) = parser.parse_args()

	
	if not options.resource_dir_src or not options.resource_dir_dst or not options.product_name:
		print 'options.resource_dir_src:', options.resource_dir_src
		print 'options.resource_dir_dst:', options.resource_dir_dst
		print 'options.product_name:', options.product_name
		parser.print_help()
		parser.error("incorrect number of arguments")
		
	input_dir = options.resource_dir_src.strip('"')
	if not os.path.exists(input_dir):
		sys.exit('input directory, "%s", doesn\'t exist.' % input_dir)

	output_dir = options.resource_dir_dst.strip('"')
	product_name = options.product_name.strip('"')
	
	
	compress(input_dir, output_dir, product_name)

# -----------------------------------------------------------------------------
	
if __name__ == "__main__":
	try:
		main()
	except Exception, e:
		print e
		sys.exit(-1)
