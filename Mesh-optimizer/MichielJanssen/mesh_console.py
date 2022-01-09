import sys
from mesh_reader import read_file
from mesh_optimizer import optimize_mesh
from mesh_writer import write_to_file


fileName = input("Filename: ")
output =  read_file(fileName)
vertices = output[0]
allPrimitives = output[1]
optimize = optimize_mesh(vertices, allPrimitives)
outputFile = input("Output: ")
write_to_file(outputFile, allPrimitives, vertices) # allPrimitives -> optimize

