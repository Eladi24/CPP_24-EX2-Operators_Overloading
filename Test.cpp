#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <sstream>

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    ariel::Graph expectedGraph;
    vector<vector<int>> expectedMat = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    expectedGraph.loadGraph(expectedMat);
    stringstream ss;
    ss << g3;
    CHECK(ss.str() == "[0, 2, 1], \n[2, 0, 3], \n[1, 3, 0]\n\n");
    CHECK(g3 == expectedGraph);
    ariel::Graph g4 = g2 + g1;
    CHECK(g4 == expectedGraph);
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 * g2;
    ariel::Graph expectedGraph;
    vector<vector<int>> expectedMat = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    expectedGraph.loadGraph(expectedMat);
    stringstream ss;
    ss << g3;
    CHECK(ss.str() == "[1, 0, 2], \n[1, 3, 1], \n[1, 0, 2]\n\n");
    CHECK(g3 == expectedGraph);

    ariel::Graph g4 = g2 * g1;
    expectedMat = {
        {1, 1, 1},
        {0, 3, 0},
        {2, 1, 2}};
    expectedGraph.loadGraph(expectedMat);
    ss.str("");
    ss << g2 * g1;
    CHECK(ss.str() == "[1, 1, 1], \n[0, 3, 0], \n[2, 1, 2]\n\n");
    CHECK(g4 == expectedGraph);
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(g2.loadGraph(weightedGraph));
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("Adding a graph to itself")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    g1 += g2;
    ariel::Graph g3;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g3.loadGraph(expectedGraph);
    CHECK(g1 == g3);
    expectedGraph = {
        {0, 3, 2},
        {3, 0, 4},
        {2, 4, 0}};
    g3.loadGraph(expectedGraph);
    CHECK(++g1 == g3);
    CHECK(g1++ == g3);
}

TEST_CASE("Subtracting two graphs")
{
    ariel::Graph g1;
    vector<vector<int>> g1Mat = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g1.loadGraph(g1Mat);
    ariel::Graph g2;
    vector<vector<int>> g2Mat = {
        {0, 4, 0, 0},
        {4, 0, -6, -2},
        {0, -6, 0, 5},
        {0, -2, 5, 0}};
    g2.loadGraph(g2Mat);
    ariel::Graph g3 = g1 - g2;
    ariel::Graph expectedGraph;
    vector<vector<int>> expectedMat = {
        {0, -4, 0, 0},
        {0, 0, 0, 2},
        {0, 6, 0, 0},
        {0, 0, -5, 0}};
    expectedGraph.loadGraph(expectedMat);
    CHECK(g3 == expectedGraph);
    g3 = g2 - g1;
    expectedMat = {
        {0, 4, 0, 0},
        {0, 0, 0, -2},
        {0, -6, 0, 0},
        {0, 0, 5, 0}};
    expectedGraph.loadGraph(expectedMat);
    CHECK(g3 == expectedGraph);
}

TEST_CASE("Subtracting a graph from itself")
{
    ariel::Graph g1;
    vector<vector<int>> g1Mat = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g1.loadGraph(g1Mat);
    ariel::Graph g2;
    vector<vector<int>> g2Mat = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g2.loadGraph(g2Mat);
    g1 -= g2;
    ariel::Graph expectedGraph;
    vector<vector<int>> expectedMat = {
        {0, 0, -1, 0, 0},
        {0, 0, 2, 0, 0},
        {-1, 2, 0, 3, 0},
        {0, 0, 3, 0, 5},
        {0, 0, 0, 5, 0}};
    expectedGraph.loadGraph(expectedMat);
    CHECK(g1 == expectedGraph);
    -g1;
    expectedMat = {
        {0, 0, 1, 0, 0},
        {0, 0, -2, 0, 0},
        {1, -2, 0, -3, 0},
        {0, 0, -3, 0, -5},
        {0, 0, 0, -5, 0}};
    expectedGraph.loadGraph(expectedMat);
    CHECK(g1 == expectedGraph);
    expectedMat = {
        {0, 0, 0, 0, 0},
        {0, 0, -3, 0, 0},
        {0, -3, 0, -4, 0},
        {0, 0, -4, 0, -6},
        {0, 0, 0, -6, 0}};
    expectedGraph.loadGraph(expectedMat);
    CHECK(--g1 == expectedGraph);
    CHECK(g1-- == expectedGraph);
}

TEST_CASE("Multiplying a graph by a scalar")
{
    ariel::Graph g1;
    vector<vector<int>> g1Mat = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g1.loadGraph(g1Mat);
    g1 *= 2;
    ariel::Graph expectedGraph;
    vector<vector<int>> expectedMat = {
        {0, 2, 0, 0, 0},
        {2, 0, 6, 0, 0},
        {0, 6, 0, 8, 0},
        {0, 0, 8, 0, 10},
        {0, 0, 0, 10, 0}};
    expectedGraph.loadGraph(expectedMat);
    CHECK(g1 == expectedGraph);
    g1 *= -5;
    expectedMat = {
        {0, -10, 0, 0, 0},
        {-10, 0, -30, 0, 0},
        {0, -30, 0, -40, 0},
        {0, 0, -40, 0, -50},
        {0, 0, 0, -50, 0}};
    expectedGraph.loadGraph(expectedMat);
    CHECK(g1 == expectedGraph);
}

TEST_CASE("Dividing a graph by a scalar")
{
    ariel::Graph g1;
    vector<vector<int>> g4Mat = { 
        { 0, -1, 0, 1 },
        { 1, 0, 1, 0 },
        { 0, -1, 0, 1 },
        { 1, 0, 1, 0 } };
    g1.loadGraph(g4Mat);
    CHECK_THROWS(g1 /= 0);
    g1 /= 2;
    ariel::Graph expectedGraph;
    vector<vector<int>> expectedMat = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    expectedGraph.loadGraph(expectedMat);
}

TEST_CASE("Testing equality of graphs")
{
    ariel::Graph g1;
    vector<vector<int>> g1Mat = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g1.loadGraph(g1Mat);
    ariel::Graph g2;
    vector<vector<int>> g2Mat = {
        {0, 0, 0, 0},
        {-4, 0, 6, 0},
        {0, 0, 0, -5},
        {0, 2, 0, 0}};
    g2.loadGraph(g2Mat);
    CHECK(g1 != g2);
    CHECK(g2 != g1);
    CHECK((g1 == g2) == false);
    -g2;
    CHECK(g1 == g2);
    CHECK(g2 == g1);
    CHECK(g1 <= g2);
    CHECK(g2 <= g1);
    CHECK(g1 >= g2);
    CHECK(g2 >= g1);
}

TEST_CASE("Testing graph inclusion")
{
    ariel::Graph g1;
    vector<vector<int>> g1Mat = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g1.loadGraph(g1Mat);
    ariel::Graph g2;
    vector<vector<int>> g2Mat = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {1, 1, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g2.loadGraph(g2Mat);
    CHECK(g2.isSubgraph(g1));
    CHECK(g1 < g2);
    CHECK(g2 > g1);
    CHECK((g1 > g2) == false);
    ariel::Graph g3;
    vector<vector<int>> g3Mat = {
        {0,1},
        {2,0}};
    g3.loadGraph(g3Mat);
    ariel::Graph g4;
    vector<vector<int>> g4Mat = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(g4Mat);
    CHECK(g3 > g4);
    CHECK(g4 < g3); 
    ariel::Graph g5;
    vector<vector<int>> g5Mat = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 2, 0}};
    g5.loadGraph(g5Mat);
    ariel::Graph g6;
    vector<vector<int>> g6Mat = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g6.loadGraph(g6Mat);
    CHECK(g5 > g6);
    CHECK(g6 < g5);
}

TEST_CASE("Testing graph inequality")
{
    ariel::Graph g1;
    vector<vector<int>> g1Mat = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g1.loadGraph(g1Mat);
    ariel::Graph g2;
    vector<vector<int>> g2Mat = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {1, 1, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g2.loadGraph(g2Mat);
    CHECK(g1 != g2);
    CHECK((g1 == g2) == false);
    CHECK(g1 < g2);

    ariel::Graph g3;
    g3.loadGraph(g1Mat);
    CHECK((g1 < g3) == false);
    CHECK((g1 > g3) == false);
    CHECK(g1 <= g3);
    CHECK(g1 >= g3);
    ariel::Graph g4;
    vector<vector<int>> g4Mat = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}};
    g4.loadGraph(g4Mat);
    ariel::Graph g5;
    vector<vector<int>> g5Mat = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(g5Mat);
    CHECK((g4 < g5) == false);
    CHECK((g5 < g4) == false);
    CHECK((g4 > g5) == false);
    CHECK((g5 > g4) == false);
    CHECK(g4 != g5);
    CHECK(g5 != g4);
    CHECK((g4 <= g5) == false);
    CHECK((g5 <= g4) == false);
    CHECK((g4 >= g5) == false);
    CHECK((g5 >= g4) == false);

}

