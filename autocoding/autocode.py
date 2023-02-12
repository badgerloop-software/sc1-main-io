import os
import json
import generators
import re

from pathlib import Path

from config import Config


class AutoGeneratedFile:

    directoryPath = os.path.dirname(Path(__file__).resolve().parent)

    def __init__(
        self, template_file: str, output_file: str, json_file_path: str
    ) -> None:
        self.template_file = (
            Path(__file__).resolve().parent / "templates" / template_file
        )
        self.output_file = Path(__file__).resolve().parent / output_file
        # convert the input path to json file to a python json file object
        f = open(json_file_path, "r")
        self.json_file = json.load(f)

    def _fill_template(self, placeholder) -> str:
        """
        Reads the template file into a buffer and ensures placeholder is present
        """
        template_buffer: str = ""
        template_buffer += self.template_file.read_text()
        if placeholder not in template_buffer:
            raise ValueError("File does not include placeholder")
        if template_buffer.count(placeholder) > 1:
            raise ValueError(
                "File has more than one placeholder \n\t The program only supports one generator per placeholder"
            )
        return template_buffer

    def _get_indentation(self, placeholder):
        """
        Gets the indentation of the placeholder
        """
        marker: str = f"/*{placeholder}*/"
        # Turn the code into an array of lines
        code = self.template_file.read_text().split("\n")
        idx: int = code.index(marker)
        starting_line: str = code[idx]
        # Get number of spaces
        print(len(starting_line) - len(starting_line.lstrip()))
        return len(starting_line) - len(starting_line.lstrip())

    def _get_generated_code(self, generator, indentation: int) -> str:
        """
        Creates a buffer of autogenerated code
        """
        generated_buffer: str = Config.begin_autocode_comment
        generated_buffer = generator(self.json_file).strip()
        generated_buffer = generated_buffer.replace("\n", ("\n" + " " * indentation))
        generated_buffer += Config.end_autocode_comment
        print(generated_buffer)
        return generated_buffer

    def _output_buffer_to_file(self, buffer) -> None:
        """
        Writes a string to the output file
        """
        if not self.output_file.exists():
            os.makedirs(str(self.output_file.parent))
        print(self.output_file)
        self.output_file.write_text(buffer)

    def autocode(self, placeholder: str, generator) -> Path:
        """
        Autocodes the file and writes to output file
        """
        output_buffer: str = Config.header_comment
        output_buffer += self._fill_template(placeholder)
        generated_code = self._get_generated_code(
            generator, self._get_indentation(placeholder)
        )
        output_buffer = output_buffer.replace(f"/*{placeholder}*/", generated_code)
        self._output_buffer_to_file(output_buffer)
        print(f"Successfuly autocoded  {str(self.output_file)}")


###
##  AUTO-CODER CALLS GO HERE
###

default_placeholder = "!!AUTO-GENERATE HERE!!"

uartApp_template_h = "uartApp.template.h"
uartApp_h_output = "../applications/uartApp.h"
# create new AutoGeneratedFile object
uartApp_h = AutoGeneratedFile(
    uartApp_template_h, uartApp_h_output, "autocoding/format.json"
)
# pass in the placeholder text and the auto generation method
uartApp_h.autocode(default_placeholder, generators.uartApp_h_generator)

# TODO change .txt to .cpp
uartApp_template_cpp = "uartApp.template.txt"
uartApp_cpp_output = "../applications/uartApp.txt"
uartApp_cpp = AutoGeneratedFile(
    uartApp_template_cpp, uartApp_cpp_output, "autocoding/format.json"
)
uartApp_cpp.autocode(default_placeholder, generators.uartApp_cpp_generator)

# EXAMPLE AUTOCODER CALL
# # data.h file
# data_h_template = "data.template.h"
# data_h_output = "../embedded/data/include/data.h"

# data_h = AutoGeneratedFile(data_h_template, data_h_output, data_file)
# data_h.autocode(default_placeholder, generators.generateDataHeader)
