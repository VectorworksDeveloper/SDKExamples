#!/usr/bin/env python

###############################################################################
#
# Using a pickled file, will load and save file modification times in order to
# compare them and notify clients whether the file modification time has 
# changed. 
#
# @author Lyndsey Ferguson
# @date created 07/13/2006
###############################################################################

import os, sys
import pickle

if sys.platform == 'darwin':
	from stat import *

def get_key_from_path(path):
	if sys.platform == 'win32':
		return path
	else:
		return os.stat(path)[ST_INO]

class Monitor:
	"""This class loads, compares, updates and saves file modification times so that our
	   file processing functions are not run needlessly."""
	#--------------------------------------------------------------------------

	def __init__(self, intermediate_files_dir):
		"""Initializes the data base file path as well as loading the file/mod-time dictionary if the data base exists."""
		
		self.db_file_path	= os.path.join(intermediate_files_dir, 'ModTimeDatabase.txt')
		self.db = {}
		
		# check to see if the database file exists.
		db_Exists = os.path.exists(self.db_file_path)
		
		# if the database file does exist, we read the file and remove it so that
		# when we update it, we are updating, rather than appending more data.
		#
		if (db_Exists):
			db_file = open(self.db_file_path, 'rb')
			self.db = pickle.load(db_file)
			db_file.close()
			self.reset()

	#--------------------------------------------------------------------------

	def reset(self):
		if os.path.exists(self.db_file_path):
			os.remove(self.db_file_path)
			
	#--------------------------------------------------------------------------
	
	def takedown(self):
		"""Save the file modification time dictionary to the database file."""
		
		
		parentdir = os.path.split(self.db_file_path)[0]
		if not os.path.exists(parentdir):
			try:
				os.makedirs(parentdir)
			except OSError:
				pass
		
		db_file = open(self.db_file_path, 'wb')
		pickle.dump(self.db, db_file)
		db_file.close()
		
	#--------------------------------------------------------------------------

	def file_is_current(self, file_path):
		"""Determine if the given file's modification time matches the last recorded time for the file."""
		
		current_result = False
		
		current_mod_time = os.path.getmtime(file_path);
		key = get_key_from_path(file_path)
		
		recorded_mod_time = 0;
		
		if (self.db.has_key(key)):
			recorded_mod_time = self.db[key]
		else:
			pass
		
		if (recorded_mod_time >= current_mod_time):
			current_result = True
		else:
			pass
		
		return current_result
		
	#--------------------------------------------------------------------------

	def remove_entry(self, file_path):
		"""Remove the file's entry in the database. Most likely the file is about to be removed."""
		
		key = get_key_from_path(file_path)
		
		if (self.db.has_key(key)):
			del self.db[key]
		else:
			pass
		
	#--------------------------------------------------------------------------

	def record_mod_time(self, file_path):
		"""Record the current modification time for the given file in our database."""
		
		key = get_key_from_path(file_path)
		current_mod_time = os.path.getmtime(file_path);
		
		self.db[key] = current_mod_time
		
		
	
	
