import os
import xml.etree.ElementTree as XMLElementTree
import generators
import re

from pathlib import Path

from config import Config


class AutoGeneratedFile:

    directoryPath = os.path.dirname(Path(__file__).resolve().parent)
    data = XMLElementTree.parse(Config.xml_target).getroot()

    def __init__(self, template_file: str, output_file: str) -> None:
        self.template_file = (
            Path(__file__).resolve().parent / "templates" / template_file
        )
        self.output_file = Path(__file__).resolve().parent / output_file

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
        generated_buffer = generator(self.data).strip()
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


# EXAMPLE AUTOCODER CALL
# # data.h file
# data_h_template = "data.template.h"
# data_h_output = "../embedded/data/include/data.h"

# data_h = AutoGeneratedFile(data_h_template, data_h_output)
# data_h.autocode(default_placeholder, generators.generateDataHeader)
