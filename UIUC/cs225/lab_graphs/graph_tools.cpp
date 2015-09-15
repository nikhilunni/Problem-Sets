/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <stack>
#include <map>
#include <iostream>
/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */



int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{

	clearGraph(graph);
	return shortestPath_helper(graph,start,end);
}

void GraphTools::clearGraph(Graph & graph)
{
   
	queue<Vertex> BFS;
	BFS.push(graph.getStartingVertex());
	while(!BFS.empty())
	{
		Vertex current = BFS.front(); BFS.pop();
		graph.setVertexLabel(current,"UNVISITED");
		vector<Vertex> neighbors = graph.getAdjacent(current);
		for(int i = 0; i < neighbors.size(); i++)
		{
			Vertex next = neighbors[i];
			if(graph.getVertexLabel(next).compare("UNVISITED") != 0)
			{
				graph.setVertexLabel(next,"UNVISITED");
				graph.setEdgeLabel(current,next,"UNVISITED");
				BFS.push(next);
			}
			else if(graph.getEdgeLabel(current,next).compare("UNVISITED") != 0)
				graph.setEdgeLabel(current,next,"UNVISITED");
		}
	}

}

int GraphTools::shortestPath_helper(Graph & graph, Vertex & start, Vertex & end)
{
	int out = 10234432; //Really large number... LOL
	vector<Vertex> adjacent = graph.getAdjacent(start);
	graph.setVertexLabel(start,"VISITED");
	for(int i = 0; i < adjacent.size(); i++)
	{
		Vertex current = adjacent[i];
		if(current == end)
		{
			graph.setEdgeLabel(start,end,"MINPATH");
			graph.setVertexLabel(start,"MIN"); 
			return 1;
		}
		if(graph.getVertexLabel(current).compare("UNVISITED") == 0)
		{
			int smallestPath = shortestPath_helper(graph,current,end);
			out = //(out < 0 ? smallestPath :
				 (smallestPath < out ? smallestPath : out);
			if(graph.getVertexLabel(current) == "MIN")
				graph.setEdgeLabel(start,current,"MINPATH");
		}
	}
	std::cout << "From: " << graph.getVertexName(start) << " to " << graph.getVertexName(end) << " is : " << (1+out) << std::endl;
	return 1+out;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
	clearGraph(graph);	
	Vertex start = graph.getStartingVertex();
	queue<Vertex> BFS; BFS.push(start);
	int out = graph.getEdgeWeight(start,graph.getAdjacent(start)[0]);
	Vertex winnerA = start, winnerB = graph.getAdjacent(start)[0];
	while(!BFS.empty())
	{
		Vertex current = BFS.front(); BFS.pop();
		vector<Vertex> neighbors = graph.getAdjacent(current);
		for(int i = 0; i < neighbors.size(); i++)
		{
			Vertex next = neighbors[i];
			if(graph.getEdgeLabel(current,next).compare("VISITED") != 0)
			{
				graph.setEdgeLabel(current,next,"VISITED");
				BFS.push(next);
			}
			if(graph.getEdgeWeight(current,next) < out)
			{
				out = graph.getEdgeWeight(current,next);
				winnerA = current, winnerB = next;
			}
		}
	}
	clearGraph(graph);
	graph.setEdgeLabel(winnerA,winnerB,"MIN");
	return out;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	vector<Edge> edges = graph.getEdges();
	std::sort(edges.begin(),edges.end(),comparitor);
	DisjointSets vertices; vertices.addelements(graph.getVertices().size());
	for(int i = 0; i < edges.size(); i++) 
	{
		if(vertices.find(edges[i].source) != vertices.find(edges[i].dest)) //If vertices are part of different sets, merge em
		{
			vertices.setunion(edges[i].source,edges[i].dest);
			graph.setEdgeLabel(edges[i].source,edges[i].dest,"MST");
		}
	}
}

bool GraphTools::comparitor(Edge a, Edge b)
{
	return (a.weight < b.weight);
}
