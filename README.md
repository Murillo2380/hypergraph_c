# HyperGraph in C

This project has the goal to allow a representation of any hyper-graph in C.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

## Important files

* **hgraph.c**: File holding the implementation of the functions declared at the header file;
* **hgraph.h**: Header file containing the declaration of functions and the documentation of each one.

### Prerequisites

GCC or any other C compiler. Compiled with GCC 5.4.0.

In order to show the graph, it will be needed any software capable to generate an image from a `.dot` file, such as [Graphviz](https://www.graphviz.org/download/ "Graphviz's Homepage").

```
apt-get install graphviz
```

### Installing

Just clone the repository:

```shell
git clone https://github.com/Murillo2380/hypergraph_c.git
```

## Running the demo

Files that need to be compiled:
* demo.c 
* hgraph.c

Use the **Makefile** to compile the source code (if using **GCC**):

```shell
make
```

Then just run the file to generate the `.dot` file to be displayed.

### Generating an image from dot file

To generate the image from **dot** program (available if you have installed graphviz):

```shell
dot -Tpng hgraph.dot > anyname.png
```

## How to use

There is a demo file that shows how to create a single HyperGraph. All functions and variables are documented in the header file.

## Contributing

To be added.

## Authors

* **Murillo Henrique Pedroso Ferreira**

See also the list of [contributors](https://github.com/Murillo2380/hypergraph_c/graphs/contributors) who participated in this project.

## License

This project is licensed under the GNU GPL3.0 License - see the [LICENSE.md](LICENSE) file for details

## Acknowledgments

* **Billie Thompson** for his [README template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2).
