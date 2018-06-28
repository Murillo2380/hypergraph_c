
/*
 * Check the documentation of functions at hgraph.h
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "hgraph.h"

/**
 * Parameter for {@link #increaseCapacity(hgraph_t *, char)
 */
#define INC_VERTICES_CAP 1

/**
 * Parameter for {@link #increaseCapacity(hgraph_t *, char)
 */
#define INC_HEDGES_CAP 0

/**
 * Initial big capacity of any array.
 */
#define INITIAL_CAPACITY 128

/**
 * Line breaker for the current Operational System.
 */
#define LINE_BRK "\n"


/**
 * <p>Increases the capacity of the given array by doubleing the current max capacity.</p>
 * <p>NOTE: this code is not protected against integer overflow</p>
 * @param v Address of the array to be expanded. If {@code NULL}, a new array will be 
 * created with an initial capacity.
 * @param size Size of each member of the given array.
 * @param capacity Pointer to the max number of members in the given array. This value will be updated
 * as follows: {@code capacity * 2} if {@code *v} does not point to {@code NULL},
 * {@link #INITIAL_CAPACITY} otherwise.
 * @return Pointer to the expanded location. Can the the same location as {@code v} or a different
 * one. If the address has changed, there is no need to free the old address, this
 * will be done automatically, recalling the behaviour of the function {@code realloc(void *, size_t)}
 * in {@code stdlib.h}
 */
static void* doubleCapacity(void *v, size_t size, size_t *capacity);

/**
 *
 * Creates a new hyper-edge in the given hyper-graph.
 *
 * @param g Hyper-graph to be used. Cannot be NULL
 * @param w Weight of the new hyper-edge.
 *
 * @return Index of the new hyper-edge.
 *
 */
static size_t addHedge(hgraph_t *g, whedge_t w);

/**
 *
 * Updates the size of the link matrix NxM, where {@code N = g -> maxHedges} 
 * and {code M = g -> maxVertices}
 *
 * @param g Hyper-graph to be updated.
 * 
 */
static void updateLinkMatrix(hgraph_t *g);

/**
 *
 * Gets the string representation of {@code w} assuming it is
 * a {@code unsigned int} data type. 
 *
 * @param buffer Buffer which will hold the translation. No line break is appended.
 * @param w Value to be translated.
 *
 * @return Return doc if needed
 *
 */
static void translateu(char *buffer, wvertex_t w);

/**
 *
 * Gets the string representation of {@code w} assuming it is
 * a {@code float} data type. 
 *
 * @param buffer Buffer which will hold the translation. No line break is appended.
 * @param w Value to be translated.
 *
 * @return Return doc if needed
 *
 */
static void translatef(char *buffer, wvertex_t w);

/**
 *
 * Gets the string representation of {@code w} assuming it is
 * a {@code double} data type. 
 *
 * @param buffer Buffer which will hold the translation. No line break is appended.
 * @param w Value to be translated.
 *
 * @return Return doc if needed
 *
 */
static void translated(char *buffer, wvertex_t w);

hgraph_t* newhgraph(char *tag){

	hgraph_t *g = calloc(1, sizeof *g);
	assert(g != NULL);
	
	if(tag != NULL)
		g -> tag = strdup(tag);

}


void freehgraph(hgraph_t *g, char isToReleaseTag){

	assert(g != NULL);

	if(isToReleaseTag && g -> tag != NULL)
		free(g -> tag);
	
	if(g -> whedges != NULL)
		free(g -> whedges);

	if(g -> wvertices != NULL)
		free(g -> wvertices);
		
	if(g -> links != NULL){
	
		int i;
		for(i = 0; i < g -> numHedges; i++)
			free(g -> links[i]); // Supposed to not be NULL
	
		free(g -> links);
	}			
				
		
	free(g);

}


size_t addVertex(hgraph_t *g, wvertex_t w){

	assert(g != NULL);
	
	if(g -> numVertices == g -> maxVertices){
		g -> wvertices = doubleCapacity(g -> wvertices, sizeof *(g -> wvertices), &(g -> maxVertices));
		updateLinkMatrix(g);
	}
	
	g -> wvertices[g -> numVertices] = w;
	
	return (g -> numVertices)++;

}

static void* doubleCapacity(void *v, size_t size, size_t *capacity){	

	if(v == NULL){
		*capacity = INITIAL_CAPACITY;
		v = malloc(size * INITIAL_CAPACITY);
		assert(v != NULL);

		return v;
	}
	
	*capacity *= 2;

	v = realloc(v, *capacity * size);
	assert(v != NULL);
	
	return v;

}

void setVertexWeight(hgraph_t *g, size_t i, wvertex_t w){

	assert(g != NULL);
	assert(i < g -> numVertices);
	
	g -> wvertices[i] = w;

}

void setHedgeWeight(hgraph_t *g, size_t i, whedge_t w){

	assert(g != NULL);
	assert(i < g -> numHedges);
	
	g -> whedges[i] = w;

}

size_t linkVertices(hgraph_t *g, size_t *v, size_t s, whedge_t w){

	assert(g != NULL);
	assert(v != NULL);
	
	int i;
	int j = addHedge(g, w);
	
	for(i = 0; i < s; i++){

		assert(v[i] < g -> numVertices); // Should be an existing vertex
		linkVertex(g, v[i], j);

	}

}

static size_t addHedge(hgraph_t *g, whedge_t w){

	assert(g != NULL);
	
	if(g -> numHedges == g -> maxHedges){
			
		g -> whedges = doubleCapacity(g -> whedges, sizeof *(g -> whedges), &(g -> maxHedges));
		updateLinkMatrix(g);

	}
	
	g -> whedges[g -> numHedges] = w;
	
	return (g -> numHedges)++;

}


void linkVertex(hgraph_t *g, size_t i, size_t j){

	assert(g != NULL);
	assert(g -> links != NULL);
	assert(g -> links[j] != NULL);
	
	g ->  links[j][i] = 1;
	
}

static void updateLinkMatrix(hgraph_t *g){

	assert(g != NULL);

	if(g -> links == NULL) // Check if exists or needs to be expanded
		g -> links = calloc(g -> maxHedges, sizeof *(g -> links) );	
	else
		g -> links = realloc(g -> links, g -> maxVertices * sizeof *(g -> links));
				
	assert(g -> links != NULL);
	
	int i;
	
	for(i = 0; i < g -> maxHedges; i++){
	
		if(g -> links[i] == NULL) // Initialize an zero-valued array
			g -> links[i] = calloc(g -> maxVertices, sizeof *(g -> links[i]));
		else // Just expand the existing array.
			g -> links[i] = realloc(g -> links[i], g -> maxVertices * sizeof *(g -> links[i]));
			
		assert(g -> links[i] != NULL);
	
	}

}

void printHgraphu(hgraph_t *g){
	printHgrapht(g, translateu, translateu);
}

static void translateu(char *buffer, wvertex_t w){

	assert(buffer != NULL);
	sprintf(buffer, "%u", w);

}

void printHgraphf(hgraph_t *g){
	printHgrapht(g, translatef, translatef);
}

static void translatef(char *buffer, wvertex_t w){

	assert(buffer != NULL);
	sprintf(buffer, "%f", (float) w); // Cast to avoid compile warning

}

void printHgraphd(hgraph_t *g){
	printHgrapht(g, translated, translated);
}

static void translated(char *buffer, wvertex_t w){

	assert(buffer != NULL);
	sprintf(buffer, "%lf", (double) w); // Cast to avoid compile warning

}

void printHgrapht(hgraph_t *g, void (*transvw)(char *buffer, wvertex_t w), void (*transhew)(char *buffer, whedge_t w)){

	assert(g != NULL);
	assert(g -> links != NULL);	
	
	FILE *fp = fopen("hgraph.dot", "w"); // TODO use g -> tag".dot" as a file name
	assert(fp != NULL);
	
	// Buffers to hold the translation of the vertex weight.
	char *bvw = malloc(sizeof *bvw * 1024);
	char *bhew = malloc(sizeof *bhew * 1024);
	assert(bvw != NULL);
	assert(bhew != NULL);
	
	size_t i;
	size_t j;
	size_t found = 0;
	size_t *verticesFound = malloc(sizeof *verticesFound * g -> numVertices);
	assert(verticesFound != NULL);
	
	fprintf(fp, "graph {");
	fprintf(fp, LINE_BRK);
	
	for(i = 0; i < g -> numHedges; i++){ // Lookup for vertices in the i-th hyper-edge.
	
		for(j = 0; j < g -> numVertices; j++){
		
			if(g -> links[i][j] != 0) // j-th vertex belongs to the i-th hyper-edge
				verticesFound[found++] = j;
		
		}
		
		if(found == 0) // Empty Hyper-edge, continue the loop
			continue;

		for(j = 0; j < found; j++){
			// TODO change %u to %s to allow arbitrary data to be printed: V_%zu_%s
			size_t vi = verticesFound[j]; // As a short only 

			transvw(bvw, g -> wvertices[vi]); // Translate vertex weight to string
			transhew(bhew, g -> whedges[i]); // Translate hyper-edge weight to string

			fprintf(fp, "\tV%zu_%s -- E%zu_%s;", vi, bvw, i, bhew);
			fprintf(fp, LINE_BRK);
		}
		
		found = 0; // clears the verticesFound queue.
	
	}	
	
	fprintf(fp, "}");
	
	free(bvw);
	free(bhew);
	free(verticesFound);

}
