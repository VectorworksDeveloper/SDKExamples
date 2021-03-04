#!/usr/bin/env python

import os, sys, time, codecs

COMPANY_URL		= 'net.nemetschek'
HELP_PREFIX		= '.help.'
TYPE_DIALOG		= 'dialog'
TYPE_MENU_ITEM	= 'menuitem'
TYPE_TOOL		= 'tool'
TYPE_SPECIAL	= 'special'

# -----------------------------------------------------------------------------	

def GetType(oldType):
	if oldType == 'Menu' or oldType == 'SubMenu':
		return TYPE_MENU_ITEM
	elif oldType == 'Tool':
		return TYPE_TOOL
	elif oldType == 'Special':
		return TYPE_SPECIAL
	else:
		raise TypeError("Encountered a help entry of an unknown type: \"%s\"." % oldType)

# -----------------------------------------------------------------------------	
	
def GetNewUniqueIdentifier():	
	return COMPANY_URL + HELP_PREFIX + os.popen('uuidgen').read()[:-1]

# -----------------------------------------------------------------------------	

def RemoveInvalidCharacters(oldValue):		
	oldValue = oldValue.replace('É', '')
	oldValue = oldValue.replace('.', '')
	oldValue = oldValue.replace('*', '')
		
	return oldValue
	
	
def RemoveCategory(oldValue):
	return oldValue.split(':')[0]
	
# -----------------------------------------------------------------------------	

def GetElementName(oldNameValue, oldIdentifierValue):
	if oldNameValue == '‘|·|‘|õ{‘|t°{‘|':
		return oldIdentifierValue
	else:
		return RemoveInvalidCharacters(RemoveCategory(oldNameValue))

# -----------------------------------------------------------------------------	

def WriteElement(outputFile, elementName, elementValue, indentDepth):
	outputFile.write('\t'*indentDepth)
	outputFile.write('<%s>%s</%s>\n' % (elementName, elementValue, elementName))
	
# -----------------------------------------------------------------------------	

def WriteElementIfExists(outputFile, elementName, elementValue, indentDepth):
	if elementValue:
		WriteElement(outputFile, elementName, elementValue, indentDepth)
		
# -----------------------------------------------------------------------------	

def IsValidColumn(columnEntry):
	return RemoveInvalidCharacters(columnEntry)
	
# -----------------------------------------------------------------------------	

def IsValidElement(elementLine):
	columns = elementLine[:-1].split('\t')
	
	if not IsValidColumn(GetType(columns[0])): # The Type
		return False
	
	if not IsValidColumn(GetElementName(columns[1], columns[2])): # The Name
		return False
		
	if not IsValidColumn(columns[3]): # The product 
		return False
	
	if not IsValidColumn(columns[4]) and not IsValidColumn(columns[5]): # The help id (topic id) and url are invalid
		return False
		
	return True

# -----------------------------------------------------------------------------	

def WriteElementHead(outputFile, elementIdentifier, indentDepth):
	outputFile.write('\t'*indentDepth)
	outputFile.write('<%s>\n' % elementIdentifier)

# -----------------------------------------------------------------------------	
	
def WriteElementTail(outputFile, elementIdentifier, indentDepth):
	outputFile.write('\t'*indentDepth)
	outputFile.write('</%s>\n' % elementIdentifier)

# -----------------------------------------------------------------------------	

def GetElements(elementLine):
	columns = elementLine[:-1].split('\t')
	
	identifier = GetNewUniqueIdentifier()
	elementName = GetElementName(columns[1], columns[2])
	type = GetType(columns[0])
	product = RemoveInvalidCharacters(columns[3])
	url = RemoveInvalidCharacters(columns[5])
	helpID = RemoveInvalidCharacters(columns[4])
	
	if url:
		product = 'ThirdParty'
		
	return identifier, elementName, type, product, url, helpID
	
# -----------------------------------------------------------------------------	
		
def ConvertHelpFile(oldHelpFilePath, newHelpDirPath):
	inputFile = open(oldHelpFilePath, 'r')

	helpFileName = COMPANY_URL + '.xml'
	
	if not os.path.isdir(newHelpDirPath):
		sys.exit(newHelpDirPath + ' is not a path to a directory where the help file, ' + helpFileName + ', will be created.')
		
	newHelpFilePath = newHelpDirPath + os.sep + helpFileName
	
	if os.path.exists(newHelpFilePath):
		os.remove(newHelpFilePath)
	
	outputFile = codecs.open(newHelpFilePath, 'w', 'utf_8')
	
	outputFile.write('<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n')
	outputFile.write('<%s>\n' % COMPANY_URL)
	outputFile.write('\t<Elements>\n')
	
	identifier = ''

	for line in inputFile:
		if IsValidElement(line):
			identifier, elementName, type, product, url, helpID = GetElements(line)
			
			WriteElementHead(outputFile, identifier, 2)
			
			WriteElement(outputFile, 'Name', elementName, 3)
			WriteElement(outputFile, 'ModificationDate', str(time.time()), 3)
			WriteElement(outputFile, 'Type', type, 3)
			
			WriteElementHead(outputFile, 'Help', 3)
			WriteElementHead(outputFile, product, 4)
			
			if url:
				WriteElement(outputFile, 'URL', url, 5)
			elif helpID:
				WriteElement(outputFile, 'ID', helpID, 5)
			
			WriteElementTail(outputFile, product, 4)
			WriteElementTail(outputFile, 'Help', 3)	
			
			WriteElementTail(outputFile, identifier, 2)
	
	outputFile.write('\t</Elements>\n')
	outputFile.write('</%s>\n' % COMPANY_URL)

if __name__ == '__main__':
	if sys.platform == 'darwin': 
		oldHelpFilePath = sys.argv[1]
		newHelpDirPath = sys.argv[2]
		ConvertHelpFile(oldHelpFilePath, newHelpDirPath)
	else:
		sys.exit('This script only functions on Mac OS X because it uses the Unix command-line tool uuidgen to generate unique values for each item identifier.')
	