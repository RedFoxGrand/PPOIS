#include <gtest/gtest.h>
#include "Graph.h"
#include <string>

struct VertexProps {
    std::string color;
    int weight;

    bool operator==(const VertexProps& other) const {
        return color == other.color && weight == other.weight;
    }
};

struct EdgeProps {
    std::string type;
    double cost;

    bool operator==(const EdgeProps& other) const {
        return type == other.type && cost == other.cost;
    }
};

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        v1 = graph.add_vertex("A");
        v2 = graph.add_vertex("B");
        v3 = graph.add_vertex("C");
        e1 = graph.add_edge(v1, v2);
        e2 = graph.add_edge(v2, v3);
    }

    Graph<std::string, VertexProps> graph;
    VertexKey v1, v2, v3;
    EdgeKey e1, e2;
};

// Áàçîâûå òåñòû
TEST_F(GraphTest, BasicOperations) {
    EXPECT_EQ(graph.vertices_count(), 3);
    EXPECT_EQ(graph.edges_count(), 2);
    EXPECT_FALSE(graph.empty());
}

TEST_F(GraphTest, VertexOperations) {
    EXPECT_TRUE(graph.has_vertex(v1));
    EXPECT_TRUE(graph.has_vertex(v2));
    EXPECT_TRUE(graph.has_vertex(v3));
    EXPECT_FALSE(graph.has_vertex(999));

    EXPECT_EQ(graph.vertex_value(v1), "A");
    EXPECT_EQ(graph.vertex_value(v2), "B");
    EXPECT_EQ(graph.vertex_value(v3), "C");

    graph.vertex_value(v1) = "A_modified";
    EXPECT_EQ(graph.vertex_value(v1), "A_modified");
}

TEST_F(GraphTest, EdgeOperations) {
    EXPECT_TRUE(graph.has_edge(e1));
    EXPECT_TRUE(graph.has_edge(e2));
    EXPECT_FALSE(graph.has_edge(999));

    auto endpoints1 = graph.edge_endpoints(e1);
    EXPECT_EQ(endpoints1.first, v1);
    EXPECT_EQ(endpoints1.second, v2);

    auto endpoints2 = graph.edge_endpoints(e2);
    EXPECT_EQ(endpoints2.first, v2);
    EXPECT_EQ(endpoints2.second, v3);

    EdgeKey found = graph.find_edge(v1, v2);
    EXPECT_EQ(found, e1);

    EXPECT_THROW(graph.find_edge(v1, v3), std::out_of_range);
}

TEST_F(GraphTest, AddRemoveVertices) {
    VertexKey v4 = graph.add_vertex("D");
    EXPECT_EQ(graph.vertices_count(), 4);
    EXPECT_TRUE(graph.has_vertex(v4));
    EXPECT_EQ(graph.vertex_value(v4), "D");

    graph.remove_vertex(v2);
    EXPECT_EQ(graph.vertices_count(), 3);
    EXPECT_FALSE(graph.has_vertex(v2));
    EXPECT_FALSE(graph.has_edge(e1));
    EXPECT_FALSE(graph.has_edge(e2));
}

TEST_F(GraphTest, AddRemoveEdges) {
    EdgeKey e3 = graph.add_edge(v1, v3);
    EXPECT_EQ(graph.edges_count(), 3);
    EXPECT_TRUE(graph.has_edge(e3));

    graph.remove_edge(e1);
    EXPECT_EQ(graph.edges_count(), 2);
    EXPECT_FALSE(graph.has_edge(e1));
}

TEST_F(GraphTest, DegreeOperations) {
    EXPECT_EQ(graph.out_degree(v1), 1);
    EXPECT_EQ(graph.out_degree(v2), 1);
    EXPECT_EQ(graph.out_degree(v3), 0);

    EXPECT_EQ(graph.in_degree(v1), 0);
    EXPECT_EQ(graph.in_degree(v2), 1);
    EXPECT_EQ(graph.in_degree(v3), 1);

    graph.add_edge(v1, v3);
    graph.add_edge(v3, v1);

    EXPECT_EQ(graph.out_degree(v1), 2);
    EXPECT_EQ(graph.in_degree(v1), 1);
}

TEST_F(GraphTest, VertexProperties) {
    VertexProps props{ "red", 10 };
    graph.vertex_props(v1) = props;

    EXPECT_EQ(graph.vertex_props(v1).color, "red");
    EXPECT_EQ(graph.vertex_props(v1).weight, 10);

    graph.vertex_props(v1).color = "blue";
    EXPECT_EQ(graph.vertex_props(v1).color, "blue");
}

TEST(GraphEdgePropsTest, EdgeProperties) {
    Graph<std::string, DefaultProps> graph_with_edge_props;
    auto v1 = graph_with_edge_props.add_vertex("A");
    auto v2 = graph_with_edge_props.add_vertex("B");
    auto e1 = graph_with_edge_props.add_edge(v1, v2);

    auto& props = graph_with_edge_props.edge_props(e1);
    EXPECT_NO_THROW(graph_with_edge_props.edge_props(e1));
}

TEST_F(GraphTest, VertexIterators) {
    std::vector<std::string> values;
    for (auto it = graph.vertices_begin(); it != graph.vertices_end(); ++it) {
        values.push_back(*it);
    }

    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(std::find(values.begin(), values.end(), "A") != values.end(), true);
    EXPECT_EQ(std::find(values.begin(), values.end(), "B") != values.end(), true);
    EXPECT_EQ(std::find(values.begin(), values.end(), "C") != values.end(), true);
}

TEST_F(GraphTest, ConstVertexIterators) {
    const auto& const_graph = graph;
    std::vector<std::string> values;

    for (auto it = const_graph.vertices_begin(); it != const_graph.vertices_end(); it++)
        values.push_back(*it);

    EXPECT_EQ(values.size(), 3);
}

TEST_F(GraphTest, VertexIteratorKeys) {
    std::set<VertexKey> keys;
    for (auto it = graph.vertices_begin(); it != graph.vertices_end(); it++)
        keys.insert(it.key());

    EXPECT_EQ(keys.size(), 3);
    EXPECT_TRUE(keys.find(v1) != keys.end());
    EXPECT_TRUE(keys.find(v2) != keys.end());
    EXPECT_TRUE(keys.find(v3) != keys.end());
}

TEST_F(GraphTest, EdgeIterators) {
    std::vector<std::pair<VertexKey, VertexKey>> edges;
    for (auto it = graph.edges_begin(); it != graph.edges_end(); it++)
        edges.push_back(*it);

    EXPECT_EQ(edges.size(), 2);
    EXPECT_EQ(std::find(edges.begin(), edges.end(), std::make_pair(v1, v2)) != edges.end(), true);
    EXPECT_EQ(std::find(edges.begin(), edges.end(), std::make_pair(v2, v3)) != edges.end(), true);
}

TEST_F(GraphTest, IncidentEdgeIterators) {
    std::vector<EdgeKey> out_edges_v1;
    for (auto it = graph.out_edges_begin(v1); it != graph.out_edges_end(v1); it++)
        out_edges_v1.push_back(*it);

    EXPECT_EQ(out_edges_v1.size(), 1);
    EXPECT_EQ(out_edges_v1[0], e1);

    std::vector<EdgeKey> out_edges_v3;
    for (auto it = graph.out_edges_begin(v3); it != graph.out_edges_end(v3); it++)
        out_edges_v3.push_back(*it);

    EXPECT_TRUE(out_edges_v3.empty());
}

TEST_F(GraphTest, InEdgeIterators) {
    std::vector<EdgeKey> in_edges_v2;
    for (auto it = graph.in_edges_begin(v2); it != graph.in_edges_end(v2); it++)
        in_edges_v2.push_back(*it);

    EXPECT_EQ(in_edges_v2.size(), 1);
    EXPECT_EQ(in_edges_v2[0], e1);

    std::vector<EdgeKey> in_edges_v1;
    for (auto it = graph.in_edges_begin(v1); it != graph.in_edges_end(v1); it++)
        in_edges_v1.push_back(*it);

    EXPECT_TRUE(in_edges_v1.empty());
}

TEST_F(GraphTest, AdjacentVertexIterators) {
    std::vector<VertexKey> adjacent_v1;
    for (auto it = graph.adjacent_begin(v1); it != graph.adjacent_end(v1); it++)
        adjacent_v1.push_back(*it);

    EXPECT_EQ(adjacent_v1.size(), 1);
    EXPECT_EQ(adjacent_v1[0], v2);

    std::vector<VertexKey> adjacent_v3;
    for (auto it = graph.adjacent_begin(v3); it != graph.adjacent_end(v3); it++)
        adjacent_v3.push_back(*it);

    EXPECT_TRUE(adjacent_v3.empty());
}

TEST_F(GraphTest, ExceptionHandling) {
    EXPECT_THROW(graph.vertex_value(999), std::out_of_range);
    EXPECT_THROW(graph.edge_endpoints(999), std::out_of_range);
    EXPECT_THROW(graph.out_degree(999), std::out_of_range);
    EXPECT_THROW(graph.in_degree(999), std::out_of_range);
    EXPECT_THROW(graph.remove_vertex(999), std::out_of_range);
    EXPECT_THROW(graph.remove_edge(999), std::out_of_range);
    EXPECT_THROW(graph.add_edge(999, v1), std::out_of_range);
    EXPECT_THROW(graph.add_edge(v1, 999), std::out_of_range);
}

TEST_F(GraphTest, CopyConstructor) {
    Graph<std::string, VertexProps> copy(graph);

    EXPECT_EQ(copy.vertices_count(), graph.vertices_count());
    EXPECT_EQ(copy.edges_count(), graph.edges_count());
    EXPECT_TRUE(copy.has_vertex(v1));
    EXPECT_TRUE(copy.has_vertex(v2));
    EXPECT_TRUE(copy.has_edge(e1));
    EXPECT_TRUE(copy.has_edge(e2));
}

TEST_F(GraphTest, AssignmentOperator) {
    Graph<std::string, VertexProps> assigned;
    assigned = graph;

    EXPECT_EQ(assigned.vertices_count(), graph.vertices_count());
    EXPECT_EQ(assigned.edges_count(), graph.edges_count());
    EXPECT_TRUE(assigned.has_vertex(v1));
    EXPECT_TRUE(assigned.has_vertex(v2));
    EXPECT_TRUE(assigned.has_edge(e1));
    EXPECT_TRUE(assigned.has_edge(e2));
}

TEST_F(GraphTest, EqualityOperators) {
    Graph<std::string, VertexProps> same_graph;
    same_graph.add_vertex("A");
    same_graph.add_vertex("B");
    same_graph.add_vertex("C");
    same_graph.add_edge(0, 1);
    same_graph.add_edge(1, 2);

    Graph<std::string, VertexProps> different_graph;
    different_graph.add_vertex("X");
    different_graph.add_vertex("Y");
    different_graph.add_edge(0, 1);

    EXPECT_TRUE(graph == same_graph);
    EXPECT_FALSE(graph == different_graph);
    EXPECT_TRUE(graph != different_graph);
}

TEST_F(GraphTest, Clear) {
    graph.clear();

    EXPECT_TRUE(graph.empty());
    EXPECT_EQ(graph.vertices_count(), 0);
    EXPECT_EQ(graph.edges_count(), 0);

    VertexKey new_v1 = graph.add_vertex("New_A");
    EXPECT_TRUE(graph.has_vertex(new_v1));
    EXPECT_EQ(graph.vertex_value(new_v1), "New_A");
}

TEST_F(GraphTest, KeyReuse) {
    VertexKey v4 = graph.add_vertex("D");
    graph.remove_vertex(v2);

    VertexKey reused = graph.add_vertex("Reused");
    EXPECT_TRUE(graph.has_vertex(reused));
    EXPECT_EQ(graph.vertex_value(reused), "Reused");
}

TEST(GraphSamePropsTest, SamePropertiesForVerticesAndEdges) {
    Graph<std::string, VertexProps> graph_with_same_props;

    auto v1 = graph_with_same_props.add_vertex("A");
    auto v2 = graph_with_same_props.add_vertex("B");
    auto e1 = graph_with_same_props.add_edge(v1, v2);

    VertexProps vertex_props{ "blue", 5 };
    graph_with_same_props.vertex_props(v1) = vertex_props;

    EXPECT_EQ(graph_with_same_props.vertex_props(v1).color, "blue");
    EXPECT_EQ(graph_with_same_props.vertex_props(v1).weight, 5);

    graph_with_same_props.edge_props(e1) = vertex_props;
    EXPECT_EQ(graph_with_same_props.edge_props(e1).color, "blue");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
