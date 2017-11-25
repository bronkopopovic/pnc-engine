import os
import sys
import glob
import itertools

class Polygon:
	def __init__(self, name):
		self.name = name
		self.vertices = []

def routine():
	roomName = raw_input("Room name: ")
	#inputFile = raw_input("Input file: ")
	inputFile = "studio_polys.svg"
	outputFile = roomName+".room"

	_in = open(inputFile, "r")
	lines = _in.readlines()
	_in.close()

	_out = open(outputFile, "w+")

	# first comment indicating nav-mesh
	_out.write("// NAV-MESH\n")

	polyNames = []

	# generate poly names
	for i, line in enumerate(lines):
		polyNames.append("poly" + str(i+1))

	# dictionary of Polygon objects
	polys = {name: Polygon(name=name) for name in polyNames}

	for i, line in enumerate(lines):
		splitLine = line.split('"')
		rawPoints = splitLine[3]
		rawVertices = rawPoints.split(" ")
		rawVertices.pop()
		for rawVertex in rawVertices:
			vertexL = rawVertex.split(",")
			# tuple for x, y coords
			vertexT = (vertexL[0], vertexL[1])
			polys[polyNames[i]].vertices.append(vertexT)

	pointCounter = 0

	for poly in polyNames:
		# Comment
		_out.write("\n// " + poly + "\n")
		# ConvexShape
		_out.write("sf::ConvexShape " + poly + ";\n")
		# Point Count
		_out.write(poly+".setPointCount("+str(len(polys[poly].vertices))+");\n")
		# Points
		for i, vertex in enumerate(polys[poly].vertices):
			pointCounter += 1
			# declare vertices
			_out.write("sf::Vector2f point"+str(pointCounter)+" = sf::Vector2f("+polys[poly].vertices[i][0]+" * game.resMultiplier, "+polys[poly].vertices[i][1]+" * game.resMultiplier);\n")
			# assign vertices
			_out.write(poly + ".setPoint("+str(i)+", point"+str(pointCounter)+");\n")


routine()