# ================================================================ #
"""                          Time                                """
# ================================================================ #

from datetime import datetime


def GetTime():
    now = datetime.now()
    return now.strftime("%H:%M:%S")


# ================================================================ #
"""        Creating Vertex Dictionary & All Triangles            """
# ================================================================ #


def CreateVertex(line_string):
    string_in_pieces = line_string.split(" ")
    return (float(string_in_pieces[0]), float(string_in_pieces[1]), float(string_in_pieces[2].strip("\n")))


def CreateVertexDictionary(lines, iterator):
    vertex_dict = dict()
    amount_of_verteces = int(lines[iterator].split(' ')[0])
    iterator += 1

    while (iterator <= amount_of_verteces):
        vertex_dict[iterator-1] = CreateVertex(lines[iterator])
        iterator += 1

    return (vertex_dict, iterator, amount_of_verteces)


def DetermineVerteces(triangle_string_list):
    return int(triangle_string_list[1]), int(triangle_string_list[2]), int(triangle_string_list[3].strip("\n"))


def ReadAllTriangles(lines, iterator, vertex_dict):
    triangles = []

    while (lines[iterator].split(" ")[0] != "b"):
        triangle_verteces = DetermineVerteces(lines[iterator].split(" "))
        triangles.append(triangle_verteces)
        iterator += 1

    return triangles


# ================================================================ #
"""            Compression Part 1 - Common Vertex                """
# ================================================================ #


def LoperCombiner(triangles, vertex_dict):
    boxes = []
    vertex_frequenty_dict = CountVertexFrequenty(triangles)
    largest_freq = GetLargestVertexCount(vertex_frequenty_dict)

    most_frequent_verteces = GetMostFrequentVerteces(
        largest_freq, vertex_frequenty_dict)

    for vertex in most_frequent_verteces:
        vertex_triangles = []
        new_triangles = []

        for triangle in triangles:
            if (vertex in triangle):
                vertex_triangles.append(triangle)
            else:
                new_triangles.append(triangle)

        vertex_combination = dict()
        vertex_combination[0] = vertex_triangles

        vertex_combination[1] = vertex_dict[vertex]

        boxes.append(vertex_combination)
        triangles = new_triangles

    return boxes, new_triangles


def StartIdea(triangles, vertex_dict):
    all_boxes = []
    count = 0

    while (len(triangles) > 0):
        new_boxes, triangles = LoperCombiner(triangles, vertex_dict)

        for box in new_boxes:
            if (len(box) > 0):
                count += 1
                all_boxes.append(box)

    return all_boxes


def CountVertexFrequenty(triangles):
    vertex_frequenty_dict = dict()
    for triangle in triangles:
        for i in range(0, 3):
            if (triangle[i] not in vertex_frequenty_dict.keys()):
                vertex_frequenty_dict[triangle[i]] = 1
            else:
                vertex_frequenty_dict[triangle[i]] += 1

    return vertex_frequenty_dict


def GetLargestVertexCount(vertex_frequenty_dict):
    counter_frequenty_dict = dict()
    for vertex in vertex_frequenty_dict.keys():
        if (vertex_frequenty_dict[vertex] not in counter_frequenty_dict.keys()):
            counter_frequenty_dict[vertex_frequenty_dict[vertex]] = 1
        else:
            counter_frequenty_dict[vertex_frequenty_dict[vertex]] += 1

    largest_freq = 0
    for freq in counter_frequenty_dict.keys():
        if (freq > largest_freq):
            largest_freq = freq

    print(largest_freq)
    return largest_freq


def GetMostFrequentVerteces(largest_freq, vertex_frequenty_dict):
    most_frequent_verteces = set()
    for vertex in vertex_frequenty_dict.keys():
        if vertex_frequenty_dict[vertex] == largest_freq:
            most_frequent_verteces.add(vertex)
    return most_frequent_verteces


# ================================================================ #
"""            Compression Part 2 - Closest Vertex               """
# ================================================================ #


def DetermineLongestAxis(triangles):
    # Returns 0 if x is the longest side, 1 for y and 2 for z

    xmin, ymin, zmin, xmax, ymax, zmax = None, None, None, None, None, None
    for triangle in triangles:
        x, y, z = triangle[1]

        if (xmin is None or xmin > x):
            xmin = x
        if (xmax is None or xmax < x):
            xmax = x

        if (ymin is None or ymin > x):
            ymin = y
        if (ymax is None or ymax < x):
            ymax = y

        if (zmin is None or zmin > x):
            zmin = z
        if (zmax is None or zmax < x):
            zmax = z

    xsize = xmax - xmin
    ysize = ymax - ymin
    zsize = zmax - zmin

    if (xsize >= ysize and xsize >= zsize):
        return 0
    if (ysize >= xsize and ysize >= zsize):
        return 1
    return 2


def OrderByLongestSide(triangles, side):
    return sorted(triangles, key=lambda k: [k[1][side]])


def RecursiveCreateBox(box_tree, factor):

    if (len(box_tree) < factor):
        return box_tree

    longest_axis = DetermineLongestAxis(box_tree)

    orderd_list = OrderByLongestSide(box_tree, longest_axis)

    box = []
    box.append(RecursiveCreateBox(orderd_list[:(len(orderd_list)//2)], factor))
    box.append(RecursiveCreateBox(orderd_list[(len(orderd_list)//2):], factor))

    return box


# ================================================================ #
"""                         Writing                              """
# ================================================================ #


def RecursiveWriteBox(tree, vertex_dict):
    result_string = ""

    if (isinstance(tree[0], list)):
        for box in tree:
            result_string += RecursiveWriteBox(box, vertex_dict)
        result_string += "b " + str(len(tree)) + "\n"

    else:
        for triangle_capsule in tree:
            for triangle in triangle_capsule[0]:
                result_string += "t " + \
                    str(triangle[0]) + " " + str(triangle[1]) + \
                    " " + str(triangle[2]) + "\n"
            result_string += "b " + str(len(triangle_capsule[0])) + "\n"
        result_string += "b " + str(len(tree)) + "\n"

    return result_string


def WriteResult(box_tree, vertex_dict, amount_of_verteces, output):

    with open(output, 'w') as file:
        file.write(str(amount_of_verteces) + " 0\n")

        for vertex_key in vertex_dict.keys():
            vertex = vertex_dict[vertex_key]
            file.write(str(vertex[0]) + " " +
                       str(vertex[1]) + " " + str(vertex[2]) + "\n")

        print(GetTime() + " - Creating finalString")
        finalString = RecursiveWriteBox(box_tree, vertex_dict)

        print(GetTime() + " - Writing finalString")
        file.write(finalString)
        file.write("end")


# ================================================================ #
"""                           Main                               """
# ================================================================ #


input = 'C:\\Users\\hendr\\OneDrive\\Documenten\\GitHub\\raytracer-coffee-addicts\\Mesh-optimizer\\LucasHendrickx\\buddha.mesh'
output = 'C:\\Users\\hendr\\OneDrive\\Documenten\\GitHub\\raytracer-coffee-addicts\\Mesh-optimizer\\LucasHendrickx\\third_result.txt'


def Optimizer(input, output):
    print(GetTime() + " - Start Optimizer")

    iterator = 0
    with open(input, 'r') as file:
        lines = file.readlines()

        vertex_dict, iterator, amount_of_verteces = CreateVertexDictionary(
            lines, iterator)

        triangles = ReadAllTriangles(lines, iterator, vertex_dict)

    print(GetTime() + " - Read Finnished")

    box_tree = StartIdea(triangles, vertex_dict)

    print(GetTime() + " - Boxes build - Part 1")

    factor = 10
    final_tree = RecursiveCreateBox(box_tree, factor)

    print(GetTime() + " - Boxes build - Part 2")

    WriteResult(final_tree, vertex_dict, amount_of_verteces, output)

    print(GetTime() + " - End")


Optimizer(input, output)
