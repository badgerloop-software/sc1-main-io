# this file generates the struct used to send messages over UART

# open the file to write the struct to
structFile = open("struct.cpp", "w")
structFile.write("struct {\n")

# variable to counter number of bytes the struct will be
totalBytes = 0

# open the data format json file and read it line by line
formatFile = open("format.json", "r")
for line in formatFile:
    # get the type and the name of this variable
    typeAndName = line.split('"')
    if len(typeAndName) > 4:
        # if the type is uint8 and uint16, use the correct types in c++
        if typeAndName[3] == "uint8":
            structFile.write("  " + "uint8_t" + " " + typeAndName[1] + ";\n")
        elif typeAndName[3] == "uint16":
            structFile.write("  " + "uint16_t" + " " + typeAndName[1] + ";\n")
        else:
            structFile.write("  " + typeAndName[3] + " " + typeAndName[1] + ";\n")

    # get the number of bytes of this variable and add it to totalBytes
    numBytes = line.split("[")
    if len(numBytes) > 1:
        numBytes = numBytes[1].split(",")
        totalBytes += int(numBytes[0])

# add the closing brace and the struct variable names
structFile.write("} data_format_read, data_format_write;\n")

# write an int variable to the top of the file which contains the total number of bytes of this struct
structFile = open("struct.cpp", "r")
temp = structFile.read()
structFile = open("struct.cpp", "w")
structFile.write("#define totalBytes " + str(totalBytes) + "\n\n")
structFile = open("struct.cpp", "a")
structFile.write(temp)
