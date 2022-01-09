from triangle import Triangle
from box import Box

def read_file(fileName):
    openFile = open(fileName, "r")
    return read_mesh(openFile)


def read_mesh(openFile):
    allPrimitives = []
    verticesList = []

    amountVertices = int(openFile.readline().split(' ')[0])
    for _ in range(amountVertices):
        verticesList.append(tuple(float(i) for i in openFile.readline().split(' ')))

    lines = openFile.readlines()
    for line in lines:
        if (line.startswith("t")):         #Triangle https://stackoverflow.com/questions/11354544/read-lines-containing-integers-from-a-file-in-python
            #arrayOfTrianglePoints = [int(trianglePoints) for trianglePoints in line.split(' ')[1:]] 
            #print(arrayOfTrianglePoints)
            x, y, z = [int(i) for i in line.split(' ')[1:]]
            triangle = Triangle(x,y,z)
            allPrimitives.append(triangle)
        elif (line.startswith("b")):        #Box
            amount = int(line.split(' ')[1])
            boxList = []
            for _ in range(amount):
                boxList.append(allPrimitives.pop())
            box = Box(boxList)
            allPrimitives.append(box)
        elif (line.startswith("end")):      #End
            return [verticesList, allPrimitives]



#read_file("bunny.mesh")