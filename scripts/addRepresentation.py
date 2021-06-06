#!/usr/bin/env python3

import argparse
import os
from shutil import copyfile
import re

# regular expressions for patterns
typesRE = re.compile('enum representation_name {.*')
otherRep = re.compile('\s*using (?P<repName>\S*)\s*=.*')
conversionRE = re.compile('\s*/\* BEGIN Conversion.*')
typedefsRE = re.compile('\s*/\* BEGIN typedefs.*')

parser = argparse.ArgumentParser(
    description='Add a new state set representation to HyPro.')
parser.add_argument('-name', '-n', metavar='<name>',
                    required=True, help='the name of the new representation.')
parser.add_argument('-short', '-s', metavar='<short>', required=True,
                    help='the shortname which will be used internally.')
args = parser.parse_args()


def fillTemplate(template, output):
    with open(template, 'r') as f:
        with open(output, 'w') as g:
            for line in f:
                g.write(line.replace("REPRESENTATION_SHORT", str(
                    args.short)).replace("REPRESENTATION", str(args.name)))
    print("wrote " + output)


hyproPath = os.path.dirname(os.getcwd()+'/src/hypro/')
p = os.path.dirname(os.getcwd()+'/src/hypro/representations/')
print("Create directory " + p + '/' + str(args.name))
otherRepresentations = []


def matchConversionFkt(line, otherRepresentations):
    for i in range(len(otherRepresentations)):
        if re.match('\s*static '+str(otherRepresentations[i])+'.*', line):
            return otherRepresentations[i]
    return None


if not os.path.exists(p + '/' + str(args.name)):
    # set up folder and create basic mock class
    os.mkdir(p + '/' + str(args.name))
    fillTemplate(os.getcwd()+'/scripts/templates/RepresentationTemplate.h',
                 p + '/' + str(args.name) + '/' + str(args.name) + ".h")
    fillTemplate(os.getcwd()+'/scripts/templates/RepresentationTemplateTpp.tpp',
                 p + '/' + str(args.name) + '/' + str(args.name) + ".tpp")
    fillTemplate(os.getcwd()+'/scripts/templates/SettingTemplate.h',
                 p + '/' + str(args.name) + '/' + str(args.name) + "Setting.h")

    # add entries in types.h
    if str(args.name) not in open(p+'/types.h').read():
        with open(p+'/types.h', 'r') as types:
            with open('tmp', 'w') as tmp:
                for line in types:
                    if typesRE.match(line) and str(args.short) not in line:
                        tmp.write(line.replace(
                            '}', ', ' + str(args.short) + "}"))
                    else:
                        tmp.write(line)
        os.replace('tmp', p+'/types.h')

    # add entries in Converter.h
    if str(args.name) not in open(p+'/conversion/Converter.h').read():
        # otherRepresentations = []
        with open(p+'/conversion/Converter.h') as converter:
            for line in converter:
                reMatch = otherRep.match(line)
                if reMatch:
                    otherRepresentations.append(reMatch.group('repName'))

        addedConversion = []
        with open(p+'/conversion/Converter.h', 'r') as converter:
            with open('tmp', 'w') as tmp:
                conversionFound = False
                typedefFound = False
                includeFound = False
                implFound = False
                lastRep = None
                currentLine = 0

                for line in converter:
                    currentLine = currentLine + 1
                    otherRepConversion = matchConversionFkt(
                        line, otherRepresentations)
                    if otherRepConversion not in addedConversion and otherRepConversion != None:
                        # Case: A representation name is in the current line, just write it down again, but keep that representation in mind as lastRep
                        addedConversion.append(otherRepConversion)
                        lastRep = otherRepConversion
                        tmp.write(line)
                    elif otherRepConversion == None and lastRep in addedConversion:
                        # Case: The current line is a template definition line, so now insert the representation that we saved from before
                        tmp.write('\t\ttemplate<typename ' + lastRep + 'Setting = typename ' +
                                  lastRep + '::Settings, typename inSetting>\n')
                        if lastRep != 'OrthogonalPolyhedron':
                            if lastRep == 'ConstraintSet':
                                tmp.write('\t\tstatic ' + lastRep + 'T<Number,' + lastRep + 'Setting> to' + lastRep + '(const ' + str(
                                    args.name) + 'T<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
                            else:
                                tmp.write('\t\tstatic ' + lastRep + 'T<Number,Converter<Number>,' + lastRep + 'Setting> to' + lastRep + '(const ' + str(
                                    args.name) + 'T<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
                        tmp.write(line)
                        lastRep = None
                    elif not includeFound and re.match('#include.*', line):
                        includeFound = True
                        tmp.write(line)
                        tmp.write('#include "../'+str(args.name) +
                                  '/'+str(args.name)+'.h"\n')
                    elif not implFound and re.match('#include \"typedefs.h\"', line):
                        implFound = True
                        tmp.write(line)
                        tmp.write('#include "converterTo' +
                                  str(args.name)+'.tpp"\n')
                    elif typedefsRE.match(line):
                        tmp.write(line)
                        tmp.write('\n')
                        tmp.write('\t\tusing ' + str(args.name) + ' = ' + str(args.name) +
                                  'T<Number,Converter,' + str(args.name)+'Default>;')
                    elif conversionRE.match(line):
                        tmp.write(line)
                        tmp.write("\n")
                        tmp.write('\t\ttemplate<typename ' + str(args.name) + 'Setting = typename ' + str(
                            args.name) + '::Settings, typename inSetting>\n')
                        tmp.write('\t\tstatic ' + str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> to' + str(
                            args.name) + '(const ' + str(args.name) + 'T<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
                        for i in range(len(otherRepresentations)):
                            if otherRepresentations[i] == 'OrthogonalPolyhedron':
                                continue
                            elif otherRepresentations[i] == 'Ellipsoid':
                                tmp.write('\t\ttemplate<typename ' + str(args.name) +
                                          'Setting = typename ' + str(args.name) + '::Settings>\n')
                                tmp.write('\t\tstatic ' + str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> to' + str(
                                    args.name) + '(const ' + str(otherRepresentations[i]) + '& source, const CONV_MODE = CONV_MODE::EXACT);\n')
                            elif otherRepresentations[i] == 'ConstraintSet':
                                tmp.write('\t\ttemplate<typename ' + str(args.name) + 'Setting = typename ' + str(
                                    args.name) + '::Settings, typename inSetting>\n')
                                tmp.write('\t\tstatic ' + str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> to' + str(
                                    args.name) + '(const ' + str(otherRepresentations[i]) + 'T<Number,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
                            elif otherRepresentations[i] == 'Polytope':
                                tmp.write('\t\t#ifdef HYPRO_USE_PPL\n')
                                tmp.write('\t\ttemplate<typename ' + str(args.name) + 'Setting = typename ' + str(
                                    args.name) + '::Settings, typename inSetting>\n')
                                tmp.write('\t\tstatic ' + str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> to' + str(args.name) + '(const ' + str(
                                    otherRepresentations[i]) + 'T<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
                                tmp.write('\t\t#endif\n')
                            else:
                                tmp.write('\t\ttemplate<typename ' + str(args.name) + 'Setting = typename ' + str(
                                    args.name) + '::Settings, typename inSetting>\n')
                                tmp.write('\t\tstatic ' + str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> to' + str(args.name) + '(const ' + str(
                                    otherRepresentations[i]) + 'T<Number,Converter<Number>,inSetting>& source, const CONV_MODE = CONV_MODE::EXACT);\n')
                    else:
                        tmp.write(line)

        os.replace('tmp', p+'/conversion/Converter.h')

        # write/extend typedefs
        with open(p+'/conversion/typedefs.h', 'r') as tdefs:
            with open('tmp', 'w') as tmp:
                for line in tdefs:
                    if not re.match('} // namespace hypro', line):
                        tmp.write(line)
                    else:
                        tmp.write('\n/**\n * Typedef for ' +
                                  str(args.name) + 'T\n */\n')
                        tmp.write('template<typename Number>\nusing '+str(args.name) +
                                  ' = typename Converter<Number>::'+str(args.name)+';\n\n')
                        tmp.write(line)
        os.replace('tmp', p+'/conversion/typedefs.h')

        # create conversion implementation tpp-file
        with open(p+'/conversion/converterTo'+str(args.name)+'.tpp', 'w') as impl:
            impl.write(
                '#ifndef INCL_FROM_CONVERTERHEADER\nstatic_assert(false, "This file may only be included indirectly by Converter.h");\n#endif\n\n')
            impl.write('namespace hypro { \n\n')
            impl.write('template<typename Number>\n')
            impl.write('template<typename ' + str(args.name) +
                       'Setting, typename inSetting>\n')
            impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(
                args.name)+'( const '+str(args.name)+'T<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {\n')
            impl.write('\treturn _source;\n')
            impl.write('}\n\n')

            for i in range(len(otherRepresentations)):
                if otherRepresentations[i] == 'Ellipsoid':
                    # Ellipsoids have no Settings
                    impl.write('template<typename Number>\n')
                    impl.write('template<typename ' +
                               str(args.name) + 'Setting>\n')
                    impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(
                        args.name)+'( const '+otherRepresentations[i]+'& _source, const CONV_MODE  ) {\n')
                elif otherRepresentations[i] == 'OrthogonalPolyhedron':
                    pass
                elif otherRepresentations[i] == 'ConstraintSet':
                    impl.write('template<typename Number>\n')
                    impl.write('template<typename ' + str(args.name) +
                               'Setting, typename inSetting>\n')
                    impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(
                        args.name)+'( const '+otherRepresentations[i]+'T<Number,inSetting>& _source, const CONV_MODE  ) {\n')
                elif otherRepresentations[i] == 'Polytope':
                    impl.write('#ifdef HYPRO_USE_PPL\n')
                    impl.write('template<typename Number>\n')
                    impl.write('template<typename ' + str(args.name) +
                               'Setting, typename inSetting>\n')
                    impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(
                        args.name)+'( const '+otherRepresentations[i]+'T<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {\n')
                else:
                    impl.write('template<typename Number>\n')
                    impl.write('template<typename ' + str(args.name) +
                               'Setting, typename inSetting>\n')
                    impl.write(str(args.name) + 'T<Number,Converter<Number>,' + str(args.name) + 'Setting> Converter<Number>::to'+str(
                        args.name)+'( const '+otherRepresentations[i]+'T<Number,Converter<Number>,inSetting>& _source, const CONV_MODE  ) {\n')
                if otherRepresentations[i] != 'OrthogonalPolyhedron':
                    impl.write('\treturn '+str(args.name) +
                               'T<Number,Converter<Number>,'+str(args.name)+'Setting>();\n')
                    impl.write('}\n')
                if otherRepresentations[i] == 'Polytope':
                    impl.write('#endif\n')
                impl.write('\n')
            impl.write('} //namespace hypro\n')

    # extend converterTo<SomeType>.tpp with new functions
    convertToFiles = os.listdir(p + '/conversion')
    for file in convertToFiles:
        for i in range(len(otherRepresentations)):
            if re.search(str(otherRepresentations[i]), str(file)) != None:
                with open(p + '/conversion/' + file, 'a') as openedFile:
                    openedFile.write('\ntemplate<typename Number>\n')
                    openedFile.write(
                        'template<typename ' + str(otherRepresentations[i]) + 'Setting, typename inSetting>\n')
                    if otherRepresentations[i] == 'ConstraintSet':
                        openedFile.write(str(otherRepresentations[i]) + 'T<Number,' + str(otherRepresentations[i]) + 'Setting> Converter<Number>::to'+str(
                            otherRepresentations[i])+'( const '+str(args.name)+'T<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {\n')
                        openedFile.write('\treturn ' + str(otherRepresentations[i]) + 'T<Number,' + str(
                            otherRepresentations[i]) + 'Setting>();\n')
                    else:
                        openedFile.write(str(otherRepresentations[i]) + 'T<Number,Converter<Number>,' + str(otherRepresentations[i]) + 'Setting> Converter<Number>::to'+str(
                            otherRepresentations[i])+'( const '+str(args.name)+'T<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {\n')
                        openedFile.write('\treturn ' + str(otherRepresentations[i]) + 'T<Number,Converter<Number>,' + str(
                            otherRepresentations[i]) + 'Setting>();\n')
                    openedFile.write('}\n\n')
                break

    # extend the conversion helper
    with open(p+'/conversion/conversionHelper.h', 'r') as cnvHelper:
        with open('tmp', 'w') as tmp:
            for line in cnvHelper:
                if not re.match('} // hypro', line):
                    tmp.write(line)
            tmp.write(
                'template<typename Number, typename OutSettings, typename In>\n')
            tmp.write('void convert(const In& in, ' + str(args.name) +
                      'T<Number,Converter<Number>,OutSettings>& out) {\n')
            tmp.write('\tout = Converter<Number>::template to' +
                      str(args.name) + '<OutSettings>(in); \n}\n')
            tmp.write('\n} // hypro')
    os.replace('tmp', p+'/conversion/conversionHelper.h')

    # update representation enums
    with open(hyproPath + '/util/type_handling/representation_enums.h', 'r') as repEnumHelper:
        with open('tmp', 'w') as tmp:
            for line in repEnumHelper:
                if not re.match('.* \)', line):
                    tmp.write(line)
                else:
                    tmp.write("\t\t\t " + str(args.short) + ",\n")
                    tmp.write(line)
    os.replace('tmp', hyproPath + '/util/type_handling/representation_enums.h')

else:
    print("Representation already exists, exiting.")
    exit(0)
