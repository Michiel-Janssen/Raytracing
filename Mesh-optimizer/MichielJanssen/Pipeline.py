import sys
from Optimizer import read_input, write_output, build_hierarchy


#inputFilename = input("Enter your input file: ")
#outputFilename = input("Enter your output file: ")
read_input_result = read_input('buddha.mesh')
vertices = read_input_result[0]
stack = read_input_result[1]
print("Start optimizing!")
optimizedStack = build_hierarchy(stack[0].children, vertices)
write_output = write_output('result.mesh', optimizedStack, vertices)