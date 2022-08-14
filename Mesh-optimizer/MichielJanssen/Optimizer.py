#
# Classes
#

    # triangleList.sort(key = lambda x : (vertices[x.v1][0] + vertices[x.v1][1] + vertices[x.v1][2]) / 3 + 
    #                                   (vertices[x.v2][0] + vertices[x.v2][1] + vertices[x.v2][2]) / 3 +
    #                                   (vertices[x.v3][0] + vertices[x.v3][1] + vertices[x.v3][2]) / 3)

from datetime import datetime


def GetTime():
    now = datetime.now()
    return now.strftime("%H:%M:%S")

from sys import maxsize
from turtle import st


class Triangle:
    def __init__(self, v1, v2, v3):
        self.v1 = v1
        self.v2 = v2
        self.v3 = v3

class Box:
    def __init__(self, children):
        self.children = children

#
# Reader
#

def read_input(file):
    print(GetTime() + "Start reading!")
    openfile = open(file, 'r')
    return [read_vertices(openfile), read_hierarchy(openfile)]

def read_mesh(file):
    vertices = read_vertices(file)
    return read_hierarchy(file, vertices)

def read_hierarchy(file):
    stack = []

    while True:
        line = file.readline()

        if line.startswith('t'):
            indices = [int(s) for s in line.split(' ')[1:]]
            stack.append(Triangle(indices[0], indices[1], indices[2]))

        elif line.startswith('b'):
            nchildren = int(line.split(' ')[1])

            children = stack[-nchildren:]
            stack = stack[:-nchildren]

            stack.append(Box(children))

        elif line.startswith('end'):
            return stack

def read_vertices(file):
    nvertices = int(file.readline().split(' ')[0])
    return [read_vertex(file) for _ in range(nvertices)]

def read_vertex(file):
    return tuple(float(c) for c in file.readline().split(' '))

#
# Optimizer
#

def build_hierarchy(triangleList, vertices):
    if len(triangleList) > 8 :
        triangleList.sort(key = lambda x : (calculateMiddlepoint(x, vertices)[0]))
        # triangleListA, triangleListB = triangleList.split(len(triangleList)/2)
        triangleListA = triangleList[:round(len(triangleList)/2)]
        triangleListB = triangleList[round(len(triangleList)/2):]

        triangleListA.sort(key = lambda x : (calculateMiddlepoint(x, vertices)[1]))
        triangleListB.sort(key = lambda x : (calculateMiddlepoint(x, vertices)[1]))

        # triangleListAA, triangleListAB = triangleList.split(len(triangleList)/2)
        # triangleListBA, triangleListBB = triangleList.split(len(triangleList)/2)

        triangleListAA = triangleListA[:round(len(triangleListA)/2)]
        triangleListAB = triangleListA[round(len(triangleListA)/2):]
        triangleListBA = triangleListB[:round(len(triangleListB)/2)]
        triangleListBB = triangleListB[round(len(triangleListB)/2):]

        triangleListAA.sort(key = lambda x : (calculateMiddlepoint(x, vertices)[2]))
        triangleListAB.sort(key = lambda x : (calculateMiddlepoint(x, vertices)[2]))
        triangleListBA.sort(key = lambda x : (calculateMiddlepoint(x, vertices)[2]))
        triangleListBB.sort(key = lambda x : (calculateMiddlepoint(x, vertices)[2]))

        # triangleListAAA, triangleListAAB = triangleList.split(len(triangleList)/2)
        # triangleListABA, triangleListABB = triangleList.split(len(triangleList)/2)
        # triangleListBAA, triangleListBAB = triangleList.split(len(triangleList)/2)
        # triangleListBBA, triangleListBBB = triangleList.split(len(triangleList)/2)

        triangleListAAA = triangleListAA[:round(len(triangleListAA)/2)]
        triangleListAAB = triangleListAA[round(len(triangleListAA)/2):]
        triangleListABA = triangleListAB[:round(len(triangleListAB)/2)] 
        triangleListABB = triangleListAB[round(len(triangleListAB)/2):]
        triangleListBAA = triangleListBA[:round(len(triangleListBA)/2)]
        triangleListBAB = triangleListBA[round(len(triangleListBA)/2):]
        triangleListBBA = triangleListBB[:round(len(triangleListBB)/2)]
        triangleListBBB = triangleListBB[round(len(triangleListBB)/2):]

        print(len(triangleList))
        return Box([build_hierarchy(triangleListAAA, vertices), build_hierarchy(triangleListAAB, vertices), build_hierarchy(triangleListABA, vertices), build_hierarchy(triangleListABB, vertices), build_hierarchy(triangleListBAA, vertices), build_hierarchy(triangleListBAB, vertices), build_hierarchy(triangleListBBA, vertices), build_hierarchy(triangleListBBB, vertices)])

    else:
        return Box(triangleList)


def calculateMiddlepoint(triangle, vertices):
    return ((vertices[triangle.v1][0] + vertices[triangle.v2][0] + vertices[triangle.v3][0]) / 3, (vertices[triangle.v1][1] + vertices[triangle.v2][1] + vertices[triangle.v3][1]) / 3, (vertices[triangle.v1][2] + vertices[triangle.v2][2] + vertices[triangle.v3][2]) / 3)

#
# Writer
#

def write_output(file, stack, vertices):
    print(GetTime() + "Start writing")
    openfile = open(file, 'w')

    openfile.write(str(len(vertices)) + " 0")
    for vertice in vertices:
        openfile.write('\n' + ','.join([str(ver) for ver in vertice]).replace(",", " "))

    write_hierarchy(openfile, stack)

    openfile.write("\nend")

def write_hierarchy(openfile, topBox):
    for child in topBox.children:
        if isinstance(child, Box):
            write_hierarchy(openfile, child)

        elif isinstance(child, Triangle):
             openfile.write('\n' + "t " + str(child.v1) + " " + str(child.v2) + " " + str(child.v3))
    
    openfile.write('\n' + "b " + str(len(topBox.children)))