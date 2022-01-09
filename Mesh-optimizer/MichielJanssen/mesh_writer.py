from box import Box
from triangle import Triangle
from mesh_reader import read_file

def write_to_file(outputFile, allPrimitive, vertices):
    openFile = open(outputFile, "x")
    return write(openFile, allPrimitive, vertices)
def write(openFile, allPrimitive, vertices):
    for boxObject in allPrimitive:
        if boxObject == Box:
	        write(openFile, allPrimitive, vertices)
	    else:
	        for children in 
    






#write_to_file("kaas.mesh", "", "")
