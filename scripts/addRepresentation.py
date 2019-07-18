#!/usr/bin/env python3

import argparse
import os
from shutil import copyfile
import re

#regular expressions for patterns
typesRE = re.compile('enum representation_name {.*')
otherRep = re.compile('\s*using (?P<repName>\S*)\s*=.*')
conversionRE = re.compile('\s*/\* BEGIN Conversion.*')
typedefsRE = re.compile('\s*/\* BEGIN typedefs.*')

parser = argparse.ArgumentParser(description='Add a new state set representation to HyPro.')
parser.add_argument('-name','-n', metavar='<name>',required=True,help='the name of the new representation.')
parser.add_argument('-short','-s', metavar='<short>',required=True,help='the shortname which will be used internally.')
args = parser.parse_args()

def fillTemplate(template,output):
	with open(template,'r') as f:
		with open(output,'w') as g:
			for line in f:
				g.write(line.replace("REPRESENTATION_SHORT",str(args.short)).replace("REPRESENTATION",str(args.name)))
	print("wrote " + output)

p = os.path.dirname(os.getcwd()+'/src/hypro/representations/')
print("Create directory " + p + '/' + str(args.name))
otherRepresentations = []

def matchConversionFkt(line,otherRepresentations):
	for i in range(len(otherRepresentations)):
		#if re.match('\s*template<typename *>*static '+str(otherRepresentations[i]+'.*'), line):
		if re.match('\s*static '+str(otherRepresentations[i])+'.*',line):
			return otherRepresentations[i]
	return ''

#def matchTemplateDefinition(line):
#	if re.search('\s*template.*', line):
#		print('matchTemplateDefinition: returning true')
#		return True
#	print('matchTemplateDefinition: returning false')
#	return False

if not os.path.exists(p+ '/' + str(args.name)):
	# set up folder and create basic mock class
	os.mkdir(p+ '/' + str(args.name))
	fillTemplate(os.getcwd()+'/scripts/templates/RepresentationTemplate.h', p+ '/' + str(args.name) + '/' + str(args.name) + ".h")
	fillTemplate(os.getcwd()+'/scripts/templates/RepresentationTemplateTpp.tpp', p+ '/' + str(args.name) + '/' + str(args.name) + ".tpp")
	fillTemplate(os.getcwd()+'/scripts/templates/SettingTemplate.h', p+ '/' + str(args.name) + '/' + str(args.name) + "Setting.h")

	# add entries in types.h
	if str(args.name) not in open(p+'/types.h').read():
		with open(p+'/types.h','r') as types:
			with open('tmp','w') as tmp:
				for line in types:
					if typesRE.match(line) and str(args.short) not in line:
						tmp.write(line.replace('}', ', ' + str(args.short) + "}"))
					else:
						tmp.write(line)
		os.replace('tmp',p+'/types.h')

	# add entries in Converter.h
	if str(args.name) not in open(p+'/conversion/Converter.h').read():
		#otherRepresentations = []
		with open(p+'/conversion/Converter.h') as converter:
			for line in converter:
				reMatch = otherRep.match(line)
				if reMatch:
					otherRepresentations.append(reMatch.group('repName'))

		addedConversion = []
		with open(p+'/conversion/Converter.h','r') as converter:
			with open('tmp','w') as tmp:
				conversionFound = False
				typedefFound = False
				includeFound = False
				implFound = False
				
				for line in converter:
					otherRepConversion = matchConversionFkt(line,otherRepresentations)
					if otherRepConversion not in addedConversion:
						addedConversion.append(otherRepConversion)
						tmp.write('\t\ttemplate<typename ' + otherRepConversion + 'Setting = typename ' + otherRepConversion + '::Settings, typename inSetting>\n');
						tmp.write('\t\tstatic ' + otherRepConversion + 'T<Number,Converter<Number>,' + otherRepConversion + 'Setting> to' + otherRepConversion + '(const '+ str(args.name) + 'T<Number,Converter<Number>,InSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
						tmp.write(line)
					elif not includeFound and re.match('#include.*',line):
						includeFound = True
						tmp.write(line)
						tmp.write('#include "../'+str(args.name)+'/'+str(args.name)+'.h"\n')
					elif not implFound and re.match('#include \"typedefs.h\"',line):
						implFound = True
						tmp.write(line)
						tmp.write('#include "converterTo'+str(args.name)+'.tpp"\n')
					elif typedefsRE.match(line):
						tmp.write(line)
						tmp.write('\n')
						tmp.write('\t\tusing ' + str(args.name) + ' = '+ str(args.name) +'T<Number,Converter,'+ str(args.name)+'Default>;')
					elif conversionRE.match(line):
						tmp.write(line)
						tmp.write("\n")
						tmp.write('\t\ttemplate<typename ' + str(args.name) + 'Setting = typename ' + str(args.name) + '::Settings, typename inSetting>\n');
						tmp.write('\t\tstatic ' + str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> to' + str(args.name) + '(const '+ str(args.name) + 'T<Number,Converter<Number>,InSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
						for i in range(len(otherRepresentations)):
							tmp.write('\t\ttemplate<typename ' + str(args.name) + 'Setting = typename ' + str(args.name) + '::Settings, typename inSetting>\n');
							tmp.write('\t\tstatic ' + str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> to' + str(args.name) + '(const '+ str(otherRepresentations[i]) + 'T<Number,Converter<Number>,InSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
					else:
						tmp.write(line)

		os.replace('tmp',p+'/conversion/Converter.h')

		# write/extend typedefs
		with open(p+'/conversion/typedefs.h','r') as tdefs:
			with open('tmp','w') as tmp:
				tmp.write('template<typename Number>\nusing '+str(args.name)+' = typename Converter<Number>::'+str(args.name)+';\n\n')
				for line in tdefs:
					tmp.write(line)

		os.replace('tmp',p+'/conversion/typedefs.h')

		# create conversion implementation tpp-file
		with open(p+'/conversion/converterTo'+str(args.name)+'.tpp','w') as impl:
			impl.write('#ifndef INCL_FROM_CONVERTERHEADER\nstatic_assert(false, "This file may only be included indirectly by Converter.h");\n#endif\n\n')
			impl.write('template<typename Number>\n')
			impl.write('template<typename ' + str(args.name) + 'Setting, typename InSetting>\n')
			impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(args.name)+'( const '+str(args.name)+'T<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {\n')
			impl.write('\treturn _source;\n')
			impl.write('}\n\n')

			for i in range(len(otherRepresentations)):
				impl.write('template<typename Number>\n')
				if otherRepresentations[i] == 'Ellipsoid':
					#Ellipsoids have no Settings
					impl.write('template<typename ' + str(args.name) + 'Setting>\n')
				else:
					impl.write('template<typename ' + str(args.name) + 'Setting, typename InSetting>\n')
				if otherRepresentations[i] == 'Ellipsoid':
					#Ellipsoids have no Settings
					impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(args.name)+'( const '+otherRepresentations[i]+'& _source, const CONV_MODE  ) {\n')
				elif otherRepresentations[i] == 'ConstraintSet':
					#ConstraintSets have no Converter template
					impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(args.name)+'( const '+otherRepresentations[i]+'T<Number,InSetting>& _source, const CONV_MODE  ) {\n')	
				else:
					impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(args.name)+'( const '+otherRepresentations[i]+'T<Number,Converter<Number>,InSetting>& _source, const CONV_MODE  ) {\n')
				impl.write('\treturn '+str(args.name)+'T<Number,Converter<Number>,'+str(args.name)+'Setting>();\n')
				impl.write('}\n\n')

	# extend converterTo<SomeType>.tpp with new functions
	convertToFiles = os.listdir(p + '/conversion')
	for file in convertToFiles:
		for i in range(len(otherRepresentations)):
			if re.search(str(otherRepresentations[i]),str(file)) != None:
				#print('found ' + str(otherRepresentations[i]) + ' in ' + str(file))
				with open(p + '/conversion/' + file,'a') as openedFile:
					openedFile.write('\ntemplate<typename Number>\n')
					openedFile.write('template<typename ' + str(otherRepresentations[i]) + 'Setting, typename InSetting>\n')
					openedFile.write(str(otherRepresentations[i]) + 'T<Number,Converter<Number>,' + str(otherRepresentations[i]) + 'Setting> Converter<Number>::to'+str(otherRepresentations[i])+'( const '+str(args.name)+'T<Number,Converter<Number>,InSetting>& source, const CONV_MODE ) {\n')
					openedFile.write('\treturn ' + str(otherRepresentations[i]) + 'T<Number,Converter<Number>,' + str(otherRepresentations[i]) + 'Setting>();\n')
					openedFile.write('}\n\n')
				break
			
else:
	print("Representation already exists, exiting.")
	exit(0)
