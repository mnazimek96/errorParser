import getpass
import os
import shutil
import zlib
from datetime import datetime

import pandas as pd  # need to be installed in project directory

error = 0
logfile = 0
count = 0
checksum = 0xFFFFFFFF
input_file = "gf_errors(30_10_2020).csv"


def parsefile():
    global logfile, count, input_file, error
    try:
        file = pd.read_csv(input_file, sep=';')
    except FileNotFoundError:
        writeLog("Input file " + '\"' + input_file + '\"' + " not found! Should be placed in ../errorParser/")
        error += 1
    try:
        reg_name = file["REG_NAME"]
        bitfield = file["bitfield"]
        name = file["NAME"]
        error_code = file["ERROR_CODE"]
        type = file["TYPE"]
        seriousness = file["SERIOUSNESS"]
        sw_name = file["SW_NAME"]
        not_functional = file["NOT_FUNCTIONAL"]
        safe_state = file["SAFE_STATE"]
        need_lck_out = file["NEED_LCK_OUT"]
    except:
        writeLog("Bad input file format. File must have columns: ['REG_NAME', 'bitfield', 'NAME', 'ERROR_CODE', 'TYPE', 'SERIOUSNESS', 'SW_NAME']")
        error += 1
    if count == 1 and error == 0:
        writeLog(f'\nProcessed {reg_name.size} lines\n'
                f'Column names are: {file.columns.tolist()}\n'
                f'CSV file checksum is {hex(checksum_calc(input_file))}\n'
                "\ndefaultParser.py: Execution finished without errors.")
    else:
        count += 1
        pass

    return reg_name, bitfield, name, error_code, type, seriousness, sw_name, not_functional, safe_state, need_lck_out



def mkdir():
    if not os.path.exists("output"):
        os.makedirs("output")
    if not os.path.exists("backup"):
        os.makedirs("backup")


def checksum_calc(fileName):
    global checksum
    for row in fileName:
        for ro in row:
            checksum = zlib.crc32(bytes(ro, "ascii"), checksum)
    return(checksum)


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
    global input_file
    reg_name, bitfield, name, error_code, type, seriousness, sw_name, not_functional, safe_state, need_lck_out = parsefile()
    for i in range(reg_name.size):
        line = "{:<40}{:>5}".format(sw_name[i], i)
        file.write("\n#define " + line)
    file.write("\n")
    for j in range(reg_name.size):
        if reg_name[i] == "INFORMATIONS_0":
            attribute = "infos0"
        else:
            attribute = reg_name[i].lower().replace("_", "")
        line_cgf = "{:<9}{:<49}{:<5}{:<5}{:<5}{:<5}{:<20}{:<30}{:<4}{:<4}{:<4}".format("#define",
                                                                                       "ERROR_CFG_"+sw_name[j],
                                                                                       "{"+str(bitfield[j]) + ", ",
                                                                                        str(type[j]) + ", ",
                                                                                        str(seriousness[j]) + ", ",
                                                                                        str(error_code[j]) + ", ",
                                                                                        "&error_regs." + attribute + ", ",
                                                                                        "&error_eeprom_regs." + attribute + ", ",
                                                                                        str(not_functional[j]) + ", ",
                                                                                        str(safe_state[j]) + ", ",
                                                                                        str(need_lck_out[j]) + ", }")
        file.write("\n" + line_cgf)
    return i


def definitionWriteTail(file, nr_line):
    global input_file

    test = checksum_calc(input_file)
    file.write("\n\n#define ERROR_NO " + f'{nr_line + 1}')
    file.write("\n#define ERRORS_CHECKSUM " + f'{str(hex(test))}')
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
               "\tuint8_t bitfield:4;          /* bitfield in 16-bit register */\n"
               "\tuint8_t seriousness:2;\n"
               "\tuint16_t code:12;            /* range up to 4095 */\n"
               "\tvolatile uint16_t * reg;     /* reg to store error (if active or not) */\n"
               "\tvolatile uint16_t * mem_reg; /* reg to indicate if error has already been put into memory */\n"
               "\tuint8_t not_functional:1;    /* result: gf not functional */\n"
               "\tuint8_t safe_state:1;        /* result: SAFE STATE */\n"
               "\tuint8_t need_lck_out:1;      /* result: Gap Filler need to be switched to lock-out urgently */\n"
               "} error_t;\n")
    pass


def listWriteBody(file):
    global input_file
    reg_name, bitfield, name, error_code, type, seriousness, sw_name, not_functional, safe_state, need_lck_out = parsefile()
    file.write("\nstatic const error_t errors[ERROR_NO] = {\n")
    for i in range(reg_name.size):
        line = "{:<52}{:>2}".format("ERROR_CFG_"+sw_name[i], ",")
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

