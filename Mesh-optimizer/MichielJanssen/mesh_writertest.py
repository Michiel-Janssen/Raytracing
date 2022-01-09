from box import Box
from triangle import Triangle
from mesh_reader import read_file

#box = Box([])

#box.children.append(Triangle(1,5,36))
#box.children.append(Triangle(2,6,37))

output = read_file("bunny.mesh")
vertices = output[0]
all_primitives = output[1]
print (all_primitives)
box = all_primitives[0]


def create_file(filename):
    openFile = open(filename, "x")
    return write_to_file(openFile)

def write_to_file(openFile):
    openFile.write(str(len(vertices)) + " 0\n")
    write_vertices(openFile)

def write_vertices(openFile):
    if(len(vertices) != 0):
        openFile.write(str(vertices[-1]) + "\n")
        vertices.pop()
        return write_vertices(openFile)
    return write_triangles(openFile)


def write_triangles(openFile):
    if(len(box.children) != 0):
        openFile.write("t " + str(box.children[-1].x) + " " + str(box.children[-1].y) + " " + str(box.children[-1].z) + "\n")
        box.children.pop()
        return write_triangles(openFile)
#t 116 959 1515
#b children.len()

#create_file("WriteTest.mesh")