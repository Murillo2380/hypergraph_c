#include <stdio.h>
#include <stddef.h>

#include "hgraph.h"

int main(){

	hgraph_t *g = newhgraph("testgraph");
	
	addVertex(g, 50);
	addVertex(g, 0); 
	addVertex(g, 0); 
	
	addVertex(g, 5);
	addVertex(g, 10);
	
	size_t hedge1[] = {0, 1, 2};
	size_t hedge2[] = {2, 3};
	size_t hedge3[] = {3, 4};
	
	linkVertices(g, hedge1, 3, 240);
	linkVertices(g, hedge2, 2, 180);
	linkVertices(g, hedge3, 2, 120);
	
	printHgraphu(g);
	freehgraph(g, 1);
	
}

