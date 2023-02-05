# this file generates the struct used to send messages over UART

# open the file to write the struct to
structFile = open("struct.cpp", "w")
structFile.write("typedef struct {\n")

# variable to counter number of bytes the struct will be (initialize to 1 because of the keep_alive bool)
totalBytes = 1

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
formatFile.close()

# add a keep alive signal (which will always be true)
structFile.write("  bool keep_alive;\n")
# add the closing brace and declare 3 structs
structFile.write(
    "} data_format;\n\n data_format dfwrite;\n data_format dfread;\n data_format emptyStruct;\n"
)


# write an int variable to the top of the file which contains the total number of bytes of this struct
structFile.close()
structFile = open("struct.cpp", "r")
temp = structFile.read()  # get the contents of struct.cpp
structFile.close()
structFile = open("struct.cpp", "w")
structFile.write(
    "#define totalBytes " + str(totalBytes) + "\n\n"
)  # overwrite struct.cpp with the totalBytes int
structFile.close()
structFile = open("struct.cpp", "a")
structFile.write(temp)  # append the rest of struct.cpp
structFile.close()
