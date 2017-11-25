import os
import sys
import glob
import itertools

class Polygon:
	def __init__(self, name):
		self.name = name
		self.vertices = []
		self.center = (0, 0)
		self.adjacencyList = []

def routine():
	roomName = raw_input("Room name: ")
	inputFile = raw_input("Input file: ")
	#inputFile = "studio_polys.svg"
	outputFile = roomName+".navmesh"

	_in = open(inputFile, "r")
	lines = _in.readlines()
	_in.close()

	_out = open(outputFile, "w+")

	# first comment indicating nav-mesh
	_out.write("//---------------------\n// NAV-MESH\n//---------------------\n")
	_out.write("BRO::NavMesh "+roomName+"_navMesh;\n")

	polyNames = []

	# generate poly names
	for i, line in enumerate(lines):
		polyNames.append("poly" + str(i+1))

	# dictionary of Polygon objects
	polys = {name: Polygon(name=name) for name in polyNames}

	# add vertices to polygons
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

	# add polygon centers
	for poly in polyNames:
		centerX = 0
		centerY = 0
		for vertex in polys[poly].vertices:
			x = int(vertex[0])
			y = int(vertex[1])
			centerX += x
			centerY += y
		centerX = centerX / len(polys[poly].vertices)
		centerY = centerY / len(polys[poly].vertices)
		
		polys[poly].center = (centerX, centerY)
	
	# add adjacenecy list
	def checkAdjacency(poly1, poly2):
		counter = 0
		for vertex_p1 in poly1.vertices:
			for vertex_p2 in poly2.vertices:
				if vertex_p1[0] == vertex_p2[0] and vertex_p1[1] == vertex_p2[1]:
					counter += 1
		if counter == 2:
			return 1
		else:
			return 0

	for poly1 in polyNames:
		for poly2 in polyNames:
			if checkAdjacency(polys[poly1], polys[poly2]) == 1:
				polys[poly1].adjacencyList.append(poly2)
		print polys[poly1].adjacencyList



	pointCounter = 0

	for poly in polyNames:
		# Comment
		_out.write("\n\n//-----------------\n// " + poly.replace("poly", "") + "\n//-----------------\n")
		# ConvexShape
		_out.write("sf::ConvexShape "+ roomName + "_" + poly + ";\n")
		# Point Count
		_out.write(roomName+"_"+poly+".setPointCount("+str(len(polys[poly].vertices))+");\n\n")
		# Points
		for i, vertex in enumerate(polys[poly].vertices):
			pointCounter += 1
			# declare vertices
			_out.write("sf::Vector2f "+ roomName + "_point"+str(pointCounter)+" = sf::Vector2f("+polys[poly].vertices[i][0]+" * game.resMultiplier, "+polys[poly].vertices[i][1]+" * game.resMultiplier);\n")
			# assign vertices
			_out.write(roomName + "_" + poly + ".setPoint("+str(i)+", "+roomName+"_point"+str(pointCounter)+");\n")

		_out.write("\nBRO::Node "+roomName+"_"+poly.replace("poly", "node")+";\n")
		_out.write(roomName+"_"+poly.replace("poly", "node")+".setCoords("+str(polys[poly].center[0])+", "+str(polys[poly].center[1])+");\n\n")

		_out.write("BRO::Polygon "+roomName+"_"+poly.replace("poly", "polygon")+";\n")
		_out.write(roomName+"_"+poly.replace("poly", "polygon")+".assign("+roomName+"_"+poly+", "+roomName+"_"+poly.replace("poly", "node")+");\n\n")

		_out.write(roomName+"_navMesh.addShape("+roomName+"_"+poly+");\n")
		_out.write(roomName+"_navMesh.addPoly("+roomName+"_"+poly.replace("poly", "polygon")+");\n")

	_out.write("\n\n//------------------------\n// ADJACENCY SETUP\n//------------------------\n")

	for poly in polyNames:
		for adj in polys[poly].adjacencyList:
			_out.write(roomName+"_"+poly.replace("poly", "node")+".addAdjacency("+roomName+"_"+adj.replace("poly", "node")+");\n")

routine()