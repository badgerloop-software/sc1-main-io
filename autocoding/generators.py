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
