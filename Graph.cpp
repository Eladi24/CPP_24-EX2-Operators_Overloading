// ID: 205739907
// Email: eladima66@gmail.com

#include <iostream>
#include <vector>
#include <set>
#include "Graph.hpp"
using ariel::Graph;
using namespace std;

Graph::Graph()
{
    this->vertices = 0;
    this->edges = 0;
    this->directed = false;
}

Graph::~Graph()
{
    
}

void Graph::loadGraph(vector<vector<int>> graph)
{
    this->adjancencyMatrix = graph;
    this->vertices = graph.size();
    size_t n = graph.size();
    size_t m = graph[0].size();

    // If the graph is not a square matrix, throw an exception.
    if (n != m)
    {
        throw invalid_argument("Invalid graph");
    }
    this->directed = this->isDirected();
    this->edges = this->countEdges();

}

void Graph::printGraph()
{
    cout << "Graph with " << this->vertices << " vertices and " << this->countEdges() << " edges." << endl;

}

size_t Graph::getVertices()
{
    return this->vertices;
}

size_t Graph::getEdges()
{
    return this->edges;
}

bool Graph::isDirected()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    // Iterate over the matrix and check if the graph is directed.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {   
            // If the graph is directed, the adjacency matrix is not symmetric.
            if (this->adjancencyMatrix[i][j] != this->adjancencyMatrix[j][i])
            {
                return true;
            }
        }
    }
    return false;
}

size_t Graph::countEdges()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();
    size_t count = 0;

    // Iterate over the matrix and count the number of edges.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            // If the value is not 0, then there is an edge.
            if (this->adjancencyMatrix[i][j] != 0)
            {
                count++;
            }
        }
    }
    // If the graph is directed, return the count, if the graph is undirected, then every edge is counted twice.
    return this->directed ? count : count / 2;
}

vector<vector<int>> Graph::getAdjacencyMatrix() 
{
    return this->adjancencyMatrix;
}

vector<vector<int>> Graph::getTranspose()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();
    vector<vector<int>> transpose(n, vector<int>(m, 0));

    for (size_t i = 0; i < n; i++)
    {
        
        for (size_t j = 0; j < m; j++)
        {
            transpose[j][i] = this->adjancencyMatrix[i][j];
        }
    }
    return transpose;
}

set<pair<int, int>> Graph::getEdgesSet() const
{
        size_t n = this->adjancencyMatrix.size();
        size_t m = this->adjancencyMatrix[0].size();
        set<pair<int, int>> edges;

    if (this->directed)
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
            {
                if (this->adjancencyMatrix[i][j] != 0)
                {
                    
                    edges.emplace(i, j);
                }
            }
        }
    } 
    else 
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = i; j < m; j++)
            {
                if (this->adjancencyMatrix[i][j] != 0)
                {
                    edges.emplace(i, j);
                }
            }
        }
    }
    return edges;
}

vector<int> Graph::getVerticesSet()
{
    size_t n = this->adjancencyMatrix.size();
    vector<int> vertices;

    for (size_t i = 0; i < n; i++)
    {
        vertices.push_back(i);
    }
    return vertices;
}

bool Graph::isSubgraph(const Graph &g) const
{
    size_t n1 = this->adjancencyMatrix.size();
    size_t m1 = this->adjancencyMatrix[0].size();
    size_t n2 = g.adjancencyMatrix.size();
    size_t m2 = g.adjancencyMatrix[0].size();

    set<pair<int, int>> edges1 = this->getEdgesSet();
    set<pair<int, int>> edges2 = g.getEdgesSet();

    if (n1 < n2 || m1 < m2)
    {
        return false;
    }

    if (edges1.size() <= edges2.size())
    {
        return false;
    }

    for (auto edge2 : edges2)
    {
        // If the edge is not in the first graph, return false.
        if (edges1.find(edge2) == edges1.end())
        {
            return false;
        }
    }

    return true;
}

ostream &ariel::operator<<(ostream &os, const Graph &g)
{
    size_t n = g.adjancencyMatrix.size();
    size_t m = g.adjancencyMatrix[0].size();

    for (size_t i = 0; i < n; i++)
    {
        os << "[";
        for (size_t j = 0; j < m; j++)
        {
            os << g.adjancencyMatrix[i][j];
            if (j != m - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        if (i != n - 1)
        {
            os << ", ";
        }
        os << endl;
    }
    os << endl;
    return os;
}

Graph ariel::operator+(const Graph &g1, const Graph &g2)
{
    size_t n1 = g1.adjancencyMatrix.size();
    size_t m1 = g1.adjancencyMatrix[0].size();
    size_t n2 = g2.adjancencyMatrix.size();
    size_t m2 = g2.adjancencyMatrix[0].size();

    // If the matrices are not the same size, throw an exception.
    if (n1 != n2 || m1 != m2)
    {
        throw invalid_argument("The matrices must be the same size.");
    }
    vector<vector<int>> sum(n1, vector<int>(m1, 0));

    // Iterate over the matrices and add the values.
    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m1; j++)
        {
            sum[i][j] = g1.adjancencyMatrix[i][j] + g2.adjancencyMatrix[i][j];
        }
    }
    Graph g;
    g.loadGraph(sum);
    return g;
}

Graph Graph::operator+=(Graph &g)
{
    size_t n1 = this->adjancencyMatrix.size();
    size_t m1 = this->adjancencyMatrix[0].size();
    size_t n2 = g.adjancencyMatrix.size();
    size_t m2 = g.adjancencyMatrix[0].size();

    // If the matrices are not the same size, throw an exception.
    if (n1 != n2 || m1 != m2)
    {
        throw invalid_argument("The matrices must be the same size.");
    }

    // Iterate over the matrices and add the values.
    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m1; j++)
        {
            this->adjancencyMatrix[i][j] += g.adjancencyMatrix[i][j];
        }
    }
    this->edges = this->countEdges();
    return *this;
}

Graph Graph::operator+()
{
    return *this;
}

Graph Graph::operator++()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    // Iterate over the matrix and increment the values.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (this->adjancencyMatrix[i][j] != 0 && this->adjancencyMatrix[i][j] != -1)
            {
                this->adjancencyMatrix[i][j]++;
            }

            else if (this->adjancencyMatrix[i][j] == -1)
            {
                this->adjancencyMatrix[i][j] = 1;
            }
        }
    }
    this->edges = this->countEdges();
    return *this;
}

Graph Graph::operator++(int)
{
    Graph g = *this;
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    // Iterate over the matrix and increment the values.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (this->adjancencyMatrix[i][j] != 0 && this->adjancencyMatrix[i][j] != -1)
            {
                this->adjancencyMatrix[i][j]++;
            }

            else if (this->adjancencyMatrix[i][j] == -1)
            {
                this->adjancencyMatrix[i][j] = 1;
            }
        }
    }
    this->edges = this->countEdges();
    return g;
}

Graph ariel::operator-(const Graph &g1, const Graph &g2)
{
    size_t n1 = g1.adjancencyMatrix.size();
    size_t m1 = g1.adjancencyMatrix[0].size();
    size_t n2 = g2.adjancencyMatrix.size();
    size_t m2 = g2.adjancencyMatrix[0].size();

    // If the matrices are not the same size, throw an exception.
    if (n1 != n2 || m1 != m2)
    {
        throw invalid_argument("The matrices must be the same size.");
    }
    vector<vector<int>> diff(n1, vector<int>(m1, 0));

    // Iterate over the matrices and subtract the values.
    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m1; j++)
        {
            diff[i][j] = g1.adjancencyMatrix[i][j] - g2.adjancencyMatrix[i][j];
        }
    }
    Graph g;
    g.loadGraph(diff);
    return g;
}

Graph Graph::operator-=(Graph &g)
{
    size_t n1 = this->adjancencyMatrix.size();
    size_t m1 = this->adjancencyMatrix[0].size();
    size_t n2 = g.adjancencyMatrix.size();
    size_t m2 = g.adjancencyMatrix[0].size();

    // If the matrices are not the same size, throw an exception.
    if (n1 != n2 || m1 != m2)
    {
        throw invalid_argument("The matrices must be the same size.");
    }

    // Iterate over the matrices and subtract the values.
    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m1; j++)
        {
            this->adjancencyMatrix[i][j] -= g.adjancencyMatrix[i][j];
        }
    }
    this->edges = this->countEdges();
    return *this;
}

Graph Graph::operator-()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    // Iterate over the matrix and negate the values.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (this->adjancencyMatrix[i][j] != 0)
            {
                this->adjancencyMatrix[i][j] = -this->adjancencyMatrix[i][j];
            }
        }
    }
    return *this;
}

Graph Graph::operator--()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    // Iterate over the matrix and decrement the values.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (this->adjancencyMatrix[i][j] != 0 && this->adjancencyMatrix[i][j] != 1)
            {
                this->adjancencyMatrix[i][j]--;
            }

            else if (this->adjancencyMatrix[i][j] == 1)
            {
                this->adjancencyMatrix[i][j] = -1;
            }
        }
    }
    this->edges = this->countEdges();
    return *this;
}

Graph Graph::operator--(int)
{
    Graph g = *this;
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    // Iterate over the matrix and decrement the values.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (this->adjancencyMatrix[i][j] != 0 && this->adjancencyMatrix[i][j] != 1)
            {
                this->adjancencyMatrix[i][j]--;
            }

            else if (this->adjancencyMatrix[i][j] == 1)
            {
                this->adjancencyMatrix[i][j] = -1;
            }
        }
    }
    this->edges = this->countEdges();
    return g;
}

Graph ariel::operator*(const Graph &g1, const Graph &g2)
{
    size_t n1 = g1.adjancencyMatrix.size();
    size_t m1 = g1.adjancencyMatrix[0].size();
    size_t n2 = g2.adjancencyMatrix.size();
    size_t m2 = g2.adjancencyMatrix[0].size();

    if ((n1 != m2) || (m1 != n2))
    {
        throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix");
    }

    vector<vector<int>> diff(n1, vector<int>(m2, 0));

    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m2; j++)
        {
            for (size_t k = 0; k < m1; k++)
            {
                diff[i][j] += g1.adjancencyMatrix[i][k] * g2.adjancencyMatrix[k][j];
            }
        }
    }

    Graph g;
    g.loadGraph(diff);
    return g;

}

Graph Graph::operator*=(int scalar)
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            this->adjancencyMatrix[i][j] *= scalar;
        }
    }
    this->edges = this->countEdges();
    return *this;
}

Graph Graph::operator/=(int scalar)
{
    if (scalar == 0)
    {
        throw invalid_argument("Cannot divide by 0.");
    }
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            this->adjancencyMatrix[i][j] /= scalar;
        }
    }
    this->edges = this->countEdges();
    return *this;
}

bool ariel::operator==(const Graph &g1, const Graph &g2)
{
    size_t n1 = g1.adjancencyMatrix.size();
    size_t m1 = g1.adjancencyMatrix[0].size();
    size_t n2 = g2.adjancencyMatrix.size();
    size_t m2 = g2.adjancencyMatrix[0].size();
    bool flag = false;
    if (n1 != n2 || m1 != m2)
    {
        return flag;
    }

    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m1; j++)
        {
            if (g1.adjancencyMatrix[i][j] != g2.adjancencyMatrix[i][j])
            {
                return flag;
            }
        }
    }
    flag = true;
    return flag;
}

bool ariel::operator!=(const Graph &g1, const Graph &g2)
{
    return !((g1 == g2) && !(g1 < g2) && !(g2 < g1));
}

bool ariel::operator<(const Graph &g1, const Graph &g2)
{
    size_t n1 = g1.adjancencyMatrix.size();
    size_t m1 = g1.adjancencyMatrix[0].size();
    size_t n2 = g2.adjancencyMatrix.size();
    size_t m2 = g2.adjancencyMatrix[0].size();
    size_t edges1 = g1.edges;
    size_t edges2 = g2.edges;
    bool flag = false;
    if (g2.isSubgraph(g1))
    {
        return true;
    }
    else if (!g2.isSubgraph(g1))
    {
        flag =  edges1 < edges2;
    }

    else if (edges1 == edges2)
    {
        flag = (n1 < n2) || (m1 < m2);
    }
    return flag;
}

bool ariel::operator<=(const Graph &g1, const Graph &g2)
{
    return (g1 < g2) || (g1 == g2);
}

bool ariel::operator>(const Graph &g1, const Graph &g2)
{
    size_t n1 = g1.adjancencyMatrix.size();
    size_t m1 = g1.adjancencyMatrix[0].size();
    size_t n2 = g2.adjancencyMatrix.size();
    size_t m2 = g2.adjancencyMatrix[0].size();
    size_t edges1 = g1.edges;
    size_t edges2 = g2.edges;
    bool flag = false;
    if (g1.isSubgraph(g2))
    {
        return true;
    }
    else if (!g1.isSubgraph(g2))
    {
        flag =  edges1 > edges2;
    }

    else if (edges1 == edges2)
    {
        flag = (n1 > n2) || (m1 > m2);
    }
    return flag;
}

bool ariel::operator>=(const Graph &g1, const Graph &g2)
{
    return (g1 > g2) || (g1 == g2);
}



