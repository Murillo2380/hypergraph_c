#ifndef _HGRAPH_H /* INCLUDE GUARD */

#include <stddef.h>

/**
 * Include guard
 */
#define _HGRAPH_H


#ifndef VERTEX_WEIGHT_DATATYPE

	/**
	 * Definition that defines the data type of
	 * the weight on vertices. Default: <b>unsigned int</b>.
	 */
	#define VERTEX_WEIGHT_DATATYPE unsigned int
	
#endif


#ifndef HEDGE_WEIGHT_DATATYPE

	/**
	 * Definition that defines the data type of
	 * the weight on hyper-edges. Default: <b>unsigned int</b>.
	 */
	#define HEDGE_WEIGHT_DATATYPE unsigned int
	
#endif


typedef VERTEX_WEIGHT_DATATYPE wvertex_t;
typedef HEDGE_WEIGHT_DATATYPE whedge_t;


/**
 * Structure that holds information of a hyper-graph.
 */
typedef struct hgraph_s{

	// TODO reorder data from highest size to lowest size in order to optimize memory alloc
	
	/**
	 * Number of vertices in this graph;
	 */
	size_t numVertices;
	
	/**
	 * Number of hyper-edges of this graph;
	 */
	size_t numHedges;
	
	/**
	 * Max of vertices currently supported.
	 * Updated manually when TODO "put name" and
	 * TODO "put name" is called. Should NOT be changed manually.
	 */
	size_t maxVertices;
	
	/**
	 * Max of hyper-edges currently supported.
	 * Updated manually when TODO "put name" and
	 * TODO "put name" is called. Should NOT be changed manually.
	 */
	size_t maxHedges;

	/**
	 * Identifier of any kind. Can be {@code NULL}.
	 */
	char *tag;
	
	/**
	 * Array of edges, holding the weight of the i-th edge.
	 */
	whedge_t *whedges;
	
	/**
	 * Array holding the weight of the i-th vertex of the graph.
	 */
	wvertex_t *wvertices;
	
	/**
	 * <p>Boolean array representing the relationship among vertices.
	 * links[i][j] = 0 says that the vertex j does not belong to the hyper-edge i.</p>
	 * <p>Self linking is not possible.</p> 
	 */
	unsigned char **links;
	
	
	

}hgraph_t;


/**
 * Creates a new graph with default values.
 * @param tag Name of the graph. Can be {@code NULL}
 */
hgraph_t* newhgraph(char *tag);

/**
 * Releases all the resources allocated to the given hyper-graph.
 * The {@code *g} param should not be used after the call of this this function.
 * @param g Hyper-graph to be freed. Cannot be {@code NULL}
 * @param isToReleaseTag {@code 0} if the {@code tag} field of the
 * hypergraph should <b>not</b> be freed.
 */
void freehgraph(hgraph_t *g, char isToReleaseTag);

/**
 *
 * Adds a new vertex to the given graph, increasing the capacity if necessary.
 *
 * @param g Hyper-graph in which the vertex will be added. Cannot be {@code NULL}.
 * @param w Weight of the vertex.
 *
 * @return Index of the vertex that has been just created.
 *
 */
size_t addVertex(hgraph_t *g, wvertex_t w);

/**
 *
 * Javadoc
 *
 * @param param1 Doc of param1
 * @param param2 Doc of param2
 *
 * @return Return doc if needed
 *
 */
char groupVertex(hgraph_t *g, size_t i, size_t j);

/**
 *
 * Updates the weight of the given vertex.
 *
 * @param g Hyper-graph to be updated. Cannot be NULL.
 * @param i Index of the vertex. Must be in {@code [0, g -> numVertices)}.
 * @param w Weight of the vertex.
 *
 */
void setVertexWeight(hgraph_t *g, size_t i, wvertex_t w);

/**
 *
 * Updates the weight of the given hyper-edge.
 *
 * @param g Hyper-graph to be updated. Cannot be NULL.
 * @param i Index of the hyper-edge. Must be in {@code [0, g -> numHedges)}.
 * @param w Weight of the hyper-edge.
 *
 */
void setHedgeWeight(hgraph_t *g, size_t i, whedge_t w);


/**
 *
 * Link the vertices from the given pointer.
 *
 * @param g Hyper-graph holding the vertices to be linked
 * @param v Array containing the indexes of each vertex that will be linked to the same edge.
 * @param s Size of the array
 * @param w Weight of the hyper-edge that will connect all the given vertices.
 *
 * @return Index of the edge that connects all the given vertices.
 *
 * @see TODO link other link methods
 */
size_t linkVertices(hgraph_t *g, size_t *v, size_t s, whedge_t w);

/**
 *
 * Link vertex to the given hyper-edge.
 *
 * @param i Index of the vertex to be linked. Must be in {@code [0, g -> numVertices).
 * @param j Index of the hyper-edge to be linked. Must be in {@code [0, g -> numHedges).
 *
 * @see TODO link other link methods
 */
void linkVertex(hgraph_t *g, size_t i, size_t j);


/**
 *
 * <p>Creates a file with the DOT sintax for the given hyper-graph.
 * The following will be done: each hyper-edge will be outputted as an vertex prefixed by E, 
 * each vertex will be outputted as an vertex prefixed by V.</p>
 * <p>Vertex format: V%zu_%u</p>
 * <p>Hyper-edge format: E%zu_%u</p>
 * <p>Where: %zu = index, %u = given weight, assuming it is an {@code unsigned int} value./p>
 *
 * <p>NOTE: If the data type of the vertex and edge has not been manually changed, use this
 * function to print the given hyper-graph, otherwise, check the related functions at <b>see</b>
 * section.</p>
 * 
 * @param param1 Doc of param1
 * @param param2 Doc of param2
 *
 * @return Return doc if needed
 *
 * @see #printHgraphu(hgraph_t *)
 * @see #printHgraphf(hgraph_t *)
 * @see #printHgrapht(hgraph_t *, void (*)(char *, wvertex_t), void (*)(char *, whedge_t)))
 */
void printHgraphu(hgraph_t *g);

/**
 *
 * <p>Creates a file with the DOT sintax for the given hyper-graph.
 * The following will be done: each hyper-edge will be outputted as an vertex prefixed by E, 
 * each vertex will be outputted as an vertex prefixed by V.</p>
 * <p>Vertex format: V%zu_%f</p>
 * <p>Hyper-edge format: E%zu_%f</p>
 * <p>Where: %zu = index, %f = given weight, assuming it is a {@code float} value./p>
 *
 * <p>NOTE: If the data type of the vertex and edge has not been manually changed, use {@link #printHgraphu(hgraph_t *)}
 * function to print the given hyper-graph, otherwise, check the related functions at <b>see</b>
 * section.</p>
 *
 * @param param1 Doc of param1
 * @param param2 Doc of param2
 *
 * @return Return doc if needed
 *
 * @see #printHgraphu(hgraph_t *)
 * @see #printHgraphlf(hgraph_t *)
 * @see #printHgrapht(hgraph_t *, void (*)(char *, wvertex_t), void (*)(char *, whedge_t)))
 */
void printHgraphf(hgraph_t *g);

/**
 *
 * <p>Creates a file with the DOT sintax for the given hyper-graph.
 * The following will be done: each hyper-edge will be outputted as an vertex prefixed by E, 
 * each vertex will be outputted as an vertex prefixed by V.</p>
 * <p>Vertex format: V%zu_%lf</p>
 * <p>Hyper-edge format: E%zu_%lf</p>
 * <p>Where: %zu = index, %lf = given weight, assuming it is a {@code double} value./p>
 *
 * <p>NOTE: If the data type of the vertex and edge has not been manually changed, use {@link #printHgraphu(hgraph_t *)}
 * function to print the given hyper-graph, otherwise, check the related functions at <b>see</b>
 * section.</p>
 *
 * @param param1 Doc of param1
 * @param param2 Doc of param2
 *
 * @return Return doc if needed
 *
 * @see #printHgraphu(hgraph_t *)
 * @see #printHgraphf(hgraph_t *)
 * @see #printHgrapht(hgraph_t *, void (*)(char *, wvertex_t), void (*)(char *, whedge_t)))
 *
 */
void printHgraphlf(hgraph_t *g);

/**
 *
 * <p>Creates a file with the DOT sintax for the given hyper-graph.
 * The following will be done: each hyper-edge will be outputted as an vertex prefixed by E, 
 * each vertex will be outputted as an vertex prefixed by V.</p>
 * <p>Vertex format: V%zu_%s</p>
 * <p>Hyper-edge format: E%zu_%s</p>
 * <p>Where: %zu = index, %s = given weight (arbitrary data)./p>
 *
 * <p>NOTE: If the data type of the vertex and edge has not been manually changed, use {@link #printHgraphu(hgraph_t *)}
 * function to print the given hyper-graph, otherwise, check the related functions at <b>see</b>
 * section.</p>
 *
 * @param g Hyper-graph to be printed
 * @param transwv Pointer to a function that will receive the given vertex weight
 * and will translate its value for a string representation, writing the translation at {@code buffer}.
 * @param transhew Pointer to a function that will receive the given hyper-edge weight
 * and will translate its value for a string representation, writing the translation at {@code buffer}.
 *
 * @return Return doc if needed
 *
 * @see #printHgraphu(hgraph_t *g)
 * @see #printHgraphf(hgraph_t *g)
 * @see #printHgraphlf(hgraph_t *g)
 *
 */
void printHgrapht(hgraph_t *g, void (*transvw)(char *buffer, wvertex_t w), void (*transhew)(char *buffer, whedge_t w));

#endif



