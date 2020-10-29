import getpass
import os
import shutil
import zlib
from datetime import datetime

import pandas as pd  # need to be installed in project directory

logfile = 0
count = 0


def parsefile(input_file):
    global logfile, count
    try:
        file = pd.read_csv(input_file, sep=';')
    except FileNotFoundError:
        writeLog("Input file " + '\"' + input_file + '\"' + " not found! Should be placed in ../errorParser/")
    try:
        reg_name = file["REG_NAME"]
        bitfield = file["bitfield"]
        name = file["NAME"]
        error_code = file["ERROR_CODE"]
        type = file["TYPE"]
        seriousness = file["SERIOUSNESS"]
        sw_name = file["SW_NAME"]
    except:
        writeLog("Bad input file format. File must have columns: ['REG_NAME', 'bitfield', 'NAME', 'ERROR_CODE', 'TYPE', 'SERIOUSNESS', 'SW_NAME']")
    if count == 1:
        writeLog(f'\nProcessed {reg_name.size} lines\n'
                f'Column names are: {file.columns.tolist()}\n')
    else:
        count += 1
        pass
    return reg_name, bitfield, name, error_code, type, seriousness, sw_name



def mkdir():
    if not os.path.exists("output"):
        os.makedirs("output")
    if not os.path.exists("backup"):
        os.makedirs("backup")


def crc(fileName):
    prev = 0
    for eachLine in open(fileName,"rb"):
        prev = zlib.crc32(eachLine, prev)
    return "%X"%(prev & 0xFFFFFFFF)


def definitionWriteHeader(file):
    username = getpass.getuser()
    now = datetime.now()
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
    file.write("/* \n"
               " * errors_definition.h\n"
               " *\n *\n"
               " * generated on: " + dt_string + "\n"
               " * Author: " + username + "\n"
               " */\n\n"
               "#ifndef ERRORS_DEFINITION_H_\n"
               "#define ERRORS_DEFINITION_H_\r\n")


def definitionWriteBody(file):
    reg_name, bitfield, name, error_code, type, seriousness, sw_name = parsefile("gf_errors.csv")
    for i in range(reg_name.size):
        line = "{:<40}{:>5}".format(sw_name[i], i)
        file.write("\n#define " + line)

    return i


def definitionWriteTail(file, nr_line):
    input_file = "gf_errors.csv"
    sum = crc(input_file)
    file.write("\n\n#define ERROR_NO " + f'{nr_line + 1}')
    file.write("\n#define ERRORS_CHECKSUM " + f'0x{sum}')
    file.write("\n\n#endif /* ERRORS_DEFINITION_H_ */")


def listWriteHead(file):
    username = getpass.getuser()
    now = datetime.now()
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
    file.write("/* \n"
               " * errors_list.h\n"
               " *\n *\n"
               " * generated on: " + dt_string + "\n"
               " * Author: " + username + "\n"
               " */\n\n"
               "#ifndef ERRORS_LIST_H_\n"
               "#define ERRORS_LIST_H_\n\n"
               "typedef struct {\n"
               "\tuint8_t id;\t/* == array index */\n"
               "\tuint8_t bitfield;\t/* range up to 15, as registers are 16 bit */\n"
               "\tuint8_t type:2;\n"
               "\tuint8_t seriousness:2;\n"
               "\tuint16_t code:12;\t/* range up to 4095 */\n"
               "\tvolatile uint16_t * reg;\t/* reg to store error (if active or not) */\n"
               "\tvolatile uint16_t * mem_reg;\t/* reg to indicate if error has already been put into memory */\n"
               "} error_t;\n")
    pass


def listWriteBody(file):
    reg_name, bitfield, name, error_code, type, seriousness, sw_name = parsefile("gf_errors.csv")
    file.write("\nstatic const error_t errors[ERROR_NO] = {\n")
    for i in range(reg_name.size):
        if reg_name[i] == "INFORMATIONS_0":
            attribute = "infos0"
        else:
            attribute = reg_name[i].lower().replace("_", "")

        line = "{:<42}{:<4}{:<4}{:<4}{:<5}{:<23}{:<30}{:>5}".format("{"+sw_name[i] + ", ",
                                                                    str(bitfield[i]) + ", ",
                                                                    str(type[i]) + ", ",
                                                                    str(seriousness[i]) + ", ",
                                                                    str(error_code[i]) + ", ",
                                                                    "&error_regs." + attribute + ", ",
                                                                    "&error_eeprom_regs." + attribute + ", ",
                                                                    "},")
        file.write("\t" + line + "\n")
    file.write("};\n\n")
    pass


def listWriteTail(file):
    file.write("#else\n"
                "#error This file must be included only once\n"
                "#endif /* ERRORS_LIST_H_ */")
    pass


def generateErrorDefinition(output_file):
    if os.path.exists("output/"+output_file):
        makeBackup(output_file)
        writeLog(f'Backup of \"{output_file}\" successfully created')
    file = open("output/"+output_file, "w+")
    definitionWriteHeader(file)
    nr_lines = definitionWriteBody(file)
    definitionWriteTail(file, nr_lines)
    file.close()
    pass


def generateErrorsList(output_file):
    if os.path.exists("output/"+output_file):
        makeBackup(output_file)
        writeLog(f'Backup of \"{output_file}\" successfully created')
    file = open("output/"+output_file, "w+")
    listWriteHead(file)
    listWriteBody(file)
    listWriteTail(file)
    file.close()
    pass


def makeBackup(file):
    shutil.copy2("output/"+file, 'backup/'+file+'.bak')


def openLog(path):
    global logfile
    logfile = open(path, "w")
    username = getpass.getuser()
    now = datetime.now()
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
    logfile.write("errorParser.py: Parser run by " + username + ". Date: " + dt_string + "\n\n")
    pass


def writeLog(info):
    global logfile
    print(info, file=logfile)
    print(info)
    pass


def closeLog():
    global logfile
    logfile.close()
    pass


if __name__ == '__main__':
    mkdir()
    openLog("errorParser.log")
    generateErrorDefinition("errors_definition.h")
    generateErrorsList("errors_list.h")
    closeLog()

