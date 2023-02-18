import util

# EXAMPLE DATA_H GENERATOR
#
# # Generates the data.h file
# def generateDataHeader(data):
#     headers = ""
#     out = ""
#     # Generate initializers
#     for field in data.iter("struct"):
#         if "init" not in field.attrib:
#             continue
#         out += "int " + field.attrib["init"] + "(void);\n"

#     out += "\n"
#     # Generate data structures
#     for struct in data.iter("struct"):
#         if "comment" in struct.attrib:
#             out += util.generateComment(struct.attrib["comment"], 100)
#         out += "typedef struct " + struct.attrib["id"] + "_t {\n"

#         # Semaphores
#         out += "\tpthread_mutex_t " + struct.attrib["id"] + "Mutex;\n"

#         for field in struct:
#             if "comment" in field.attrib:
#                 out += util.generateComment(field.attrib["comment"], 100, "\t")
#             fieldId = (
#                 "*"
#                 if ("pointer" in field.attrib and field.attrib["pointer"] == "true")
#                 else ""
#             ) + field.attrib["id"]
#             if field.tag == "struct":
#                 out += "\tstruct " + field.attrib["id"] + "_t " + fieldId + ";\n"
#             elif field.tag == "field":
#                 fieldType = field.attrib["type"]
#                 # Deal with arrays
#                 if field.attrib["type"].endswith("]"):
#                     fieldId += "[" + field.attrib["type"].split("[")[1]
#                     fieldType = field.attrib["type"].split("[")[0]
#                 out += "\t" + fieldType + " " + fieldId + ";\n"

#                 # Create getter and setter headers
#                 headers += util.generateComment("Getter and setter for " + struct.attrib["id"] + "->" + field.attrib["id"], 100)
#                 fieldType = field.attrib["type"]
#                 isArray = False
#                 if "[" in field.attrib["type"]:
#                     fieldType = fieldType.split("[")[0]
#                     isArray = True
#                 headers += fieldType + " get" + util.capitalize(struct.attrib["id"]) + util.capitalize(field.attrib["id"]) + "();\n"
#                 headers += "void set" + util.capitalize(struct.attrib["id"]) + util.capitalize(field.attrib["id"]) + "(" + fieldType + " val);\n\n"

#                 headers += (
#                     fieldType
#                     + " "
#                     + util.getGetReference(struct, field)
#                     + "("
#                     + ("int index" if isArray else "")
#                     + ");\n"
#                 )
#                 headers += (
#                     "void "
#                     + util.getSetReference(struct, field)
#                     + "("
#                     + fieldType
#                     + " val"
#                     + (", int index" if isArray else "")
#                     + ");\n\n"
#                 )
#         out += "} " + struct.attrib["id"] + "_t;\n\n"
#     return out + "\n" + headers + "\n\n\n"


def uartApp_h_generator(json_file):
    # define macros for readability
    data_type_column = 1
    num_bytes_column = 0

    outputStruct = "typedef struct {\n"
    getterSetterMethods = ""

    # variable to counter number of bytes the struct will be
    totalBytes = 0

    # open the data format json file and read it line by line
    # key is the name
    for key in json_file.keys():
        valueType = json_file[key][data_type_column]
        # if the type is uint8 and uint16, use the correct types in c++
        if valueType == "uint8" or valueType == "uint16":
            outputStruct += "  " + valueType + "_t" + " " + key + ";\n"
            getterSetterMethods += valueType + "_t get_" + key + "();\n"
            getterSetterMethods += (
                "void set_" + key + "(" + valueType + "_t " + "val);\n\n"
            )
        else:
            outputStruct += "  " + valueType + " " + key + ";\n"
            getterSetterMethods += valueType + " get_" + key + "();\n"
            getterSetterMethods += (
                "void set_" + key + "(" + valueType + " " + "val);\n\n"
            )
        # get the number of bytes of this variable and add it to totalBytes
        totalBytes += json_file[key][num_bytes_column]

    # add a keep alive signal (which will always be true) and add 1 to totalBytes
    outputStruct += "  bool keep_alive;\n"
    totalBytes += 1
    # add a getter method for the keep alive signal
    getterSetterMethods += "bool get_keep_alive();\n"
    # add the closing brace
    outputStruct += "} data_format;\n\n"
    # at the top, add a macro for total number of bytes of this struct
    outputStruct = "#define totalBytes " + str(totalBytes) + "\n\n" + outputStruct
    return "\n" + outputStruct + getterSetterMethods


def uartApp_cpp_generator(json_file):
    # define macros for readability
    data_type_column = 1

    mutexes = ""
    getterSetterMethods = ""
    copyStructMethod = "void copyDataStructToWriteStruct(){\n"

    # open the data format json file and read it line by line
    # key is the name
    for key in json_file.keys():
        valueType = json_file[key][data_type_column]
        mutexName = key + "_mutex"
        # create a mutex for the variable
        mutexes += "Mutex " + mutexName + ";\n"
        # add to the copy struct method
        copyStructMethod += "  dfwrite." + key + " = get_" + key + "();\n"
        # if the type is uint8 and uint16, use the correct types in c++
        if valueType == "uint8" or valueType == "uint16":
            getterSetterMethods += (
                valueType
                + "_t get_"
                + key
                + "() {\n  "
                + mutexName
                + ".lock();\n  "
                + valueType
                + " val = dfdata."
                + key
                + ";\n  "
                + mutexName
                + ".unlock();\n  return val;\n}\n"
            )
            getterSetterMethods += (
                "void set_"
                + key
                + "("
                + valueType
                + "_t "
                + "val) {\n  "
                + mutexName
                + ".lock();\n  dfdata."
                + key
                + " = val;\n  "
                + mutexName
                + ".unlock();\n}\n\n"
            )
        else:
            getterSetterMethods += (
                valueType
                + " get_"
                + key
                + "() {\n  "
                + mutexName
                + ".lock();\n  "
                + valueType
                + " val = dfdata."
                + key
                + ";\n  "
                + mutexName
                + ".unlock();\n  return val;\n}\n"
            )
            getterSetterMethods += (
                "void set_"
                + key
                + "("
                + valueType
                + " val) {\n  "
                + mutexName
                + ".lock();\n  dfdata."
                + key
                + " = val;\n  "
                + mutexName
                + ".unlock();\n}\n\n"
            )

    # add closing brace to copy struct method
    copyStructMethod += "}\n"
    return "\n" + mutexes + "\n" + copyStructMethod + "\n" + getterSetterMethods
