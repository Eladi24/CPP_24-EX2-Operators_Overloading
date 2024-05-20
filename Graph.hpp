// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <vector>
#include <iostream>
using namespace std;
namespace ariel
{

    class Graph
    {
    private:
        vector<vector<int>> adjancencyMatrix;
        size_t vertices;
        size_t edges;
        bool directed;

    public:
        // Constructor
        Graph();
        // Destructor
        ~Graph();

        /*
        * @brief
        * This function loads the graph from a 2D vector.
        * The graph is represented as an adjacency matrix.
        * The graph can be directed or undirected.
        * The graph can be weighted or unweighted.
        * @param graph - 2D vector representing the graph.
        * @return void
        */

        void loadGraph(vector<vector<int>> graph);
        
        /*
        * @brief
        * This function prints the graph.
        * @return void        
        */
        
        void printGraph();

        /*
        * @brief
        * This function returns the number of vertices in the graph.
        * @return size_t - number of vertices in the graph.
        */

        size_t getVertices();

        /*
        * @brief
        * This function returns the number of edges in the graph.
        * @return size_t - number of edges in the graph.
        */

        size_t getEdges();

        /*
        * @brief
        * This function checks if the graph is directed.
        * @return bool - true if the graph is directed, false otherwise.
        */
        bool isDirected();

        /*
        * @brief
        * This counts the number of edges in the graph.
        * @return size_t - number of edges in the graph.
        */
        size_t countEdges();

        /*
        * @brief
        * This function returns the edges of the graph as a set of pairs.
        * @return vector<pair<int, int>> - set of pairs representing the edges of the graph.
        */
        vector<pair<int, int>> getEdgesSet();

        /*
        * @brief
        * This function returns the vertices of the graph as a set of integers.
        * @return vector<int> - set of integers representing the vertices of the graph.
        */
        vector<int> getVerticesSet();

        /*
        * @brief
        * This function checks if a given graph is a subgraph of the current graph.
        * @param g - graph to check if it is a subgraph.
        * @return bool - true if the graph is a subgraph, false otherwise.
        */
        
        
        /*
        * @brief
        * This function returns the adjacency matrix of the graph.
        * @return vector<vector<int>> - adjacency matrix of the graph.
        */
        vector<vector<int>> getAdjacencyMatrix();

        /*
        * @brief
        * This function returns the transpose of the adjacency matrix.
        * @return vector<vector<int>> - transpose of the adjacency matrix.
        */
        vector<vector<int>> getTranspose();

        /*
        * @brief
        * This function overloads the << operator to print the graph.
        * @param os - output stream.
        * @param g - graph to print.
        * @return ostream - output stream.
        */

        friend ostream &operator<<(ostream &os, const Graph &g);

        /*
        * @brief
        * This function overloads the + operator to sum two graphs.
        * @param g1 - first graph.
        * @param g2 - second graph.
        * @return Graph - the sum of the two graphs.
        */

        friend Graph operator+(const Graph &g1, const Graph &g2);

        /*
        * @brief
        * This function overloads the += operator to add a graph to the current graph.
        * @param g - graph to add.
        * 
        */

        Graph operator+=(Graph &g);

        /*
        * @brief
        * This function overloads the unary + operator to return the graph.
        */

        Graph operator+();

        /*
        * @brief
        * This function overloads the ++ operator to increment the graph by 1.
        * This is the prefix version of the operator.
        * @return Graph - the incremented graph.
        */

        Graph operator++();

        /*
        * @brief
        * This function overloads the ++ operator to increment the graph by 1.
        * This is the postfix version of the operator.
        * @return Graph - the pre-incremented graph.
        */

        Graph operator++(int);

        /*
        * @brief
        * This function overloads the - operator to subtract two graphs.
        * @param g1 - first graph.
        * @param g2 - second graph.
        */

        friend Graph operator-(const Graph &g1, const Graph &g2);

        /*
        * @brief
        * This function overloads the -= operator to subtract a graph from the current graph.
        * @param g - graph to subtract.
        * @return Graph - the subtracted graph.
        */

        Graph operator-=(Graph &g);

        /*
        * @brief
        * This function overloads the unary - operator to return the negative of the graph.
        * @return Graph - the negative of the graph.
        */

        Graph operator-();

        /*
        * @brief
        * This function overloads the -- operator to decrement the graph by 1.
        * This is the prefix version of the operator.
        * @return Graph - the decremented graph.
        */

        Graph operator--();

        /*
        * @brief
        * This function overloads the -- operator to decrement the graph by 1.
        * This is the postfix version of the operator.
        * @return Graph - the decremented graph.
        */

        Graph operator--(int);

        /*
        * @brief
        * This function overloads the * operator to multiply two graphs.
        * @param g1 - first graph.
        * @param g2 - second graph.
        * @return Graph - the multiplication of the two graphs.
        */

        friend Graph operator*(const Graph &g1, const Graph &g2);

        /*
        * @brief
        * This function overloads the *= operator to multiply the current graph by some scalar.
        * @param scalar - scalar to multiply the graph by.
        * @return Graph - the multiplied graph.
        */

        Graph operator*=(int scalar);

        /*
        * @brief
        * This function overloads the /= operator to divide the current graph by some scalar.
        * @param scalar - scalar to divide the graph by.
        * @return Graph - the divided graph.
        * @throw invalid_argument - if the scalar is 0.
        */

        Graph operator/=(int scalar);

        /*
        * @brief
        * This function overloads the == operator to check if two graphs are equal.
        * @param g1 - first graph.
        * @param g2 - second graph.
        * @return bool - true if the graphs are equal, false otherwise.
        */

        friend bool operator==(const Graph &g1, const Graph &g2);

        /*
        * @brief
        * This function overloads the != operator to check if two graphs are not equal.
        * @param g1 - first graph.
        * @param g2 - second graph.
        * @return bool - true if the graphs are not equal, false otherwise.
        */

        friend bool operator!=(const Graph &g1, const Graph &g2);

        /*
        * @brief
        * This function overloads the < operator to check if the first graph is less than the second graph.
        * @param g1 - first graph.
        * @param g2 - second graph.
        * @return bool - true if the first graph is less than the second graph, false otherwise.
        */

        friend bool operator<(const Graph &g1, const Graph &g2);

         /*
        * @brief
        * This function overloads the <= operator to check if the first graph is less than or equal to the second graph.
        * @param g1 - first graph.
        * @param g2 - second graph.
        * @return bool - true if the first graph is less than or equal to the second graph, false otherwise.
        */

        friend bool operator<=(const Graph &g1, const Graph &g2);

        /*
        * @brief
        * This function overloads the > operator to check if the first graph is greater than the second graph.
        * @param g1 - first graph.
        * @param g2 - second graph.
        * @return bool - true if the first graph is greater than the second graph, false otherwise.
        */

        friend bool operator>(const Graph &g1, const Graph &g2);

        /*
        * @brief
        * This function overloads the >= operator to check if the first graph is greater than or equal to the second graph.
        * @param g1 - first graph.
        * @param g2 - second graph.
        * @return bool - true if the first graph is greater than or equal to the second graph, false otherwise.
        */

        friend bool operator>=(const Graph &g1, const Graph &g2);

       

        
    };
}

#endif