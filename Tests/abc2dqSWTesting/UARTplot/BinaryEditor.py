import re
import os
import sys
from shutil import copyfile
import json
import binascii
import pprint
import errno



'''
--BinEditor--
Created on 11.01

@summary: The script performs the task of writing a series of Bytes input by the user
with a .json file inside the RH850 and TDA3x in their APP, BL and Cal binary. The script sizes the input binaries 
and adds the proper padding if the size is smaller than it should. The padding bytes
are also user configured.
@organization: FICOSA ADAS
@version: 0.6.1
@author: Nicolas Murguizur - F36NMB0
@contact: ee.nmurguizur@ficosa.com
@requires: Python 2.7
@changelog:
    0.6.1   -    CRC calculation written to the address specified in the memory layout Excel, 0x7FFB0.
    0.6     -    CRC calculation aligned with HexWorkshop and lammertbies.nl. When the MCU is
                capable of obtaining the same value, the calculated value will be written in the .bin.
                Also added TDA_APP, TDA_SBL and TDA_DTP side selection and also BootloaderUpdater.
    0.5.1   -    Changed the import so it isn't necessary to install install if not needed, also the output directories
                are automatically created.
    0.5     -    Added TDA_DTP zone. Added Reserved Bytes zone (13 Bytes). Some exceptions handled properly printing the 
                error to the user for taking proper actions. Increased compatibility matrix size.
    0.4     -    Added CRC check in RH850 APP. If the "CRCcheck" field inside RH850_L_APP tag is set to "yes", the script
                will calculate the APP CRC and write the result to a predefied .bin's direction.
    0.3     -    Added support to Calibration and "Right" binaries.
'''

def main():
    
        
    success = False
    tag_names   =   ["RH850_L_BL","RH_L_BLDRU","RH850_L_APP","RH850_L_APP_NOASIL","RH850_L_Cal","RH850_R_BL","RH_R_BLDRU","RH850_R_APP","RH850_R_APP_NOASIL","RH850_R_Cal","TDA_SBL_L","TDA_SBL_R","TDA_APP_L","TDA_APP_R","TDA_CAL_L","TDA_CAL_R","TDA_DTP_L","TDA_DTP_R"]
    CRC_calculation_tags = ["RH850_L_APP", "RH850_R_APP", "RH850_L_APP_NOASIL", "RH850_R_APP_NOASIL"]
   
    print 'Welcome to BinEditor v0.6 The script performs the task of writing a series of Bytes input by the user with a .json file inside the RH850 and TDA3x binary. The script sizes the input binaries and adds the proper padding if the size is smaller than it should. The padding bytes are also user configured. Also, the CRC calculation is performed. THis task is carried on using binascii library. \n'
    inputs = input_read_json()
    
    if inputs:
        for tag in tag_names:
            if inputs[tag]["modify"].upper() == 'YES':
                print '##',tag,'##'
                success = copy_paste(inputs[tag]["pathIN"], inputs[tag]["pathOUT"], inputs[tag]["filename"])
                if success:
                    success = size_padding(inputs[tag]["pathOUT"],inputs[tag]["filename"],inputs[tag]["padding"],int(inputs[tag]["filesize"]))
                    if success:
                        success = writing(inputs[tag]["pathOUT"], inputs[tag], inputs[tag]["filename"], int(inputs[tag]["filesize"]))
                        if success:
                            print '       ',inputs[tag]["filename"], "bytes' setting Success\n"
                    if not success:
                        print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                        print "!!!!!!!!!!!!!!!!! Error: Fix the error in order to continue !!!!!!!!!!!!!!!!!!!!!!"
                        print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                        return 1
                if not success:
                        print '       ',inputs[tag]["filename"], "bytes' setting Failed\n"
            else:
                print 'Skipping',tag,'as input file "modify" field is set as "NO".\n'
            if tag in CRC_calculation_tags:
                if inputs[tag]["CRCcheck"].upper() == "YES":
                    CRCcreation(inputs[tag]["pathOUT"], inputs[tag]["filename"], inputs[tag]["filesize"], inputs[tag]["signature_length"])
            
    
def copy_paste(pathin, pathout,file_name):
    
    #Create output directories
    try:
        os.makedirs(pathout)
    except OSError as exc:  
        if exc.errno == errno.EEXIST and os.path.isdir(pathout):
            pass
        else:
            raise
    try:
        copyfile(pathin+file_name, pathout+file_name)
    except IOError:
        print '    The directories for', file_name,'might not be correct. For this file the process was skipped.\n'
        return False
    return True
    
def input_read_json():
 
    print '**Input read beginning**\n'   
    
    try:
        data = json.load(open('input.json'))
    except:
        print ".json could not be loaded. It probably doesn't have a valid structure. Validate it in a web service like https://jsonlint.com/"
        return 0
    #pp = pprint.PrettyPrinter(indent=4)
    #pp.pprint(data)
    configuration = data["CONF"]
    print 'Done.\n'
    return configuration
    
def size_padding(path, file_name,padding,file_default_size):
    
    print '    **Sizing and padding of ',file_name,' beginning**'
    
    with open(path+file_name, 'a') as fil:    #Append mode
        file_size = os.path.getsize(path+file_name)
        last_address_used = int(file_size/16)
        if int(last_address_used) < int(file_default_size/16):
            for direction in range(last_address_used, int(file_default_size/16)):
                fil.write(padding)
            print '    default size',file_default_size
            print '    Padding performed over ',file_name,' with ',padding
        elif int(last_address_used) > file_default_size/16:
            print'    Error: The binary size is too big. Maximum size = ',file_default_size,' Bytes. File size:', int(last_address_used)*16,' \n'
            return False
        else:
            print '        The binary size is correct,',file_size,',bytes so no padding was performed.\n'
            
        fil.close()
    
    return True

def writing(path, input_data, target, file_default_size):
    
    print '    **Binary writing started**'
        
    #--input data concatenation--
    byte_conc_ascii = ''
    bytesum = 0
    for byte in input_data['CompatibilityMatrix']:
        byte_conc = int('0b' + input_data['CompatibilityMatrix'][byte].replace(" ", ""), 2)
        bytesum = bytesum + byte_conc
    if bytesum == 0:
        byte_conc_ascii = '0 0 0 0 0 0 0 0'
    else:
        byte_conc_ascii = byte_conc_ascii + binascii.unhexlify('%x' % byte_conc)
    try:
        input_data['CV'] = byte_conc_ascii
        
        input_data['Conc_Data'] = (input_data['Reserved'].decode('string_escape').replace(" ","") +
                                   input_data['CV'].decode('string_escape').replace(" ","") + 
                                   input_data['HardwareVersion'].decode('string_escape').replace(" ","") + 
                                   input_data['ODXFileVersion'].decode('string_escape').replace(" ","") + 
                                   input_data['ODXFileIdentifier'].decode('string_escape').replace(" ","") + 
                                   input_data['VWCodingRepairShopCodeOrSerialNumber'].decode('string_escape').replace(" ","") + 
                                   input_data['SparePartNumber'].decode('string_escape') + 
                                   input_data['SoftwareVersion'].decode('string_escape').replace(" ","") + 
                                   input_data['LogicalBlockVersion'].decode('string_escape').replace(" ",""))
                
                                
    except UnicodeDecodeError:
        print "        The Compatibility Matrix data is an integer bigger than 128 [non-ASCII character], so it isn't valid." 
        return False
                                
    with open(path+target, 'r+') as fil:        
        fil.seek(int((input_data['direction']), 16))
        fil.write(input_data['Conc_Data'])
        print '       ',input_data['filename'],'edited.'
        fil.truncate(file_default_size)
        fil.close()
    return True  

def swap(s):
    lst = list(s)
    lst_aux = list(s)
    lst_aux[0] = lst[6]
    lst_aux[1] = lst[7]
    lst_aux[2] = lst[4]
    lst_aux[3] = lst[5]
    lst_aux[4] = lst[2]
    lst_aux[5] = lst[3]
    lst_aux[6] = lst[0]
    lst_aux[7] = lst[1]
    return ''.join(lst_aux)


def CRCcreation(path, file_name, file_size, signature_length):
    '''
    CRC calculation function. The function uses binascii library. Inside this library
    there's the crc32 feature which lets calculate the crc32 with an initial value.
    The file is read with 'with open' and the 'rb' argument makes reference to open 
    the file as a binary file. The second argument is the initial value of the CRC. Finally
    a bit AND is performed. 
    
    With this procedure, the result matches the one obtained with HexWorkshop and lammertbies.nl.
    One unknown thing is that the HexWorkshop config is set with an initial CRC of 0xFFFFFFFF.
    
    HexWorkshop configuration is:
        Polynomial: 04C11DB7
        Init Value: FFFFFFFF
        Reflection: In, yes; Out, yes
        XOR Out:    FFFFFFFF
    function file.read(n), reads n characters, being every character 8 bits.
    '''
    
    print '**Binascii CRC calculation beginning**'

    print '    Input file acquired from',path+file_name
    file_size_int = int(file_size)
    signature_length_int = int(signature_length)
        
    with open(path+file_name, 'rb') as CRCfile:
        CRCfile.seek(0)    #focus in the beginning of the file
        file_without_signature = CRCfile.read(file_size_int - signature_length_int)#calculate CRC of the file without the signature area
        CRCfile.close()
        
    calculated_CRC = hex(binascii.crc32(file_without_signature,0x00000000) & 0xFFFFFFFF)[2:10] #Delete '0x' and 'L'
    calculated_CRC = calculated_CRC.zfill(8)
    calculated_CRC_swapped = swap(calculated_CRC)
    print'   ',calculated_CRC,'\n'
    print'   ',calculated_CRC_swapped,'\n'
    
    with open(path+file_name, 'r+b') as CRCfile:
        CRCfile.seek(file_size_int - signature_length_int)
        CRCfile.write(binascii.unhexlify(calculated_CRC_swapped)) #Write calculated CRC, first converted from hex string to binary.


if __name__ == "__main__":
    main()
