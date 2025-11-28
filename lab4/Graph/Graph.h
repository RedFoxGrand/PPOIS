#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

template<typename T, typename Props> class VertexIterator;
template<typename T, typename Props> class EdgeIterator;
template<typename T, typename Props> class IncidentEdgeIterator;
template<typename T, typename Props> class AdjacentVertexIterator;
template<typename T, typename Props> class InEdgeIterator;
template<typename T, typename Props> class ConstVertexIterator;
template<typename T, typename Props> class ConstEdgeIterator;
template<typename T, typename Props> class ConstIncidentEdgeIterator;
template<typename T, typename Props> class ConstAdjacentVertexIterator;
template<typename T, typename Props> class ConstInEdgeIterator;
template<typename T, typename Props> class ReverseVertexIterator;
template<typename T, typename Props> class ReverseEdgeIterator;
template<typename T, typename Props> class ReverseIncidentEdgeIterator;
template<typename T, typename Props> class ReverseAdjacentVertexIterator;
template<typename T, typename Props> class ReverseInEdgeIterator;
template<typename T, typename Props> class ConstReverseVertexIterator;
template<typename T, typename Props> class ConstReverseEdgeIterator;
template<typename T, typename Props> class ConstReverseIncidentEdgeIterator;
template<typename T, typename Props> class ConstReverseAdjacentVertexIterator;
template<typename T, typename Props> class ConstReverseInEdgeIterator;

struct DefaultProps {};

using VertexKey = std::size_t;
using EdgeKey = std::size_t;

template <typename T, typename Props>
class Graph {
public:
    using value_type = T;
    using props_type = Props;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    using VertexIterator = ::VertexIterator<T, Props>;
    using EdgeIterator = ::EdgeIterator<T, Props>;
    using IncidentEdgeIterator = ::IncidentEdgeIterator<T, Props>;
    using AdjacentVertexIterator = ::AdjacentVertexIterator<T, Props>;
    using InEdgeIterator = ::InEdgeIterator<T, Props>;
    using ConstVertexIterator = ::ConstVertexIterator<T, Props>;
    using ConstEdgeIterator = ::ConstEdgeIterator<T, Props>;
    using ConstIncidentEdgeIterator = ::ConstIncidentEdgeIterator<T, Props>;
    using ConstAdjacentVertexIterator = ::ConstAdjacentVertexIterator<T, Props>;
    using ConstInEdgeIterator = ::ConstInEdgeIterator<T, Props>;
    using ReverseVertexIterator = ::ReverseVertexIterator<T, Props>;
    using ReverseEdgeIterator = ::ReverseEdgeIterator<T, Props>;
    using ReverseIncidentEdgeIterator = ::ReverseIncidentEdgeIterator<T, Props>;
    using ReverseAdjacentVertexIterator = ::ReverseAdjacentVertexIterator<T, Props>;
    using ReverseInEdgeIterator = ::ReverseInEdgeIterator<T, Props>;
    using ConstReverseVertexIterator = ::ConstReverseVertexIterator<T, Props>;
    using ConstReverseEdgeIterator = ::ConstReverseEdgeIterator<T, Props>;
    using ConstReverseIncidentEdgeIterator = ::ConstReverseIncidentEdgeIterator<T, Props>;
    using ConstReverseAdjacentVertexIterator = ::ConstReverseAdjacentVertexIterator<T, Props>;
    using ConstReverseInEdgeIterator = ::ConstReverseInEdgeIterator<T, Props>;

    friend class ::VertexIterator<T, Props>;
    friend class ::EdgeIterator<T, Props>;
    friend class ::IncidentEdgeIterator<T, Props>;
    friend class ::AdjacentVertexIterator<T, Props>;
    friend class ::InEdgeIterator<T, Props>;
    friend class ::ConstVertexIterator<T, Props>;
    friend class ::ConstEdgeIterator<T, Props>;
    friend class ::ConstIncidentEdgeIterator<T, Props>;
    friend class ::ConstAdjacentVertexIterator<T, Props>;
    friend class ::ConstInEdgeIterator<T, Props>;
    friend class ::ReverseVertexIterator<T, Props>;
    friend class ::ReverseEdgeIterator<T, Props>;
    friend class ::ReverseIncidentEdgeIterator<T, Props>;
    friend class ::ReverseAdjacentVertexIterator<T, Props>;
    friend class ::ReverseInEdgeIterator<T, Props>;
    friend class ::ConstReverseVertexIterator<T, Props>;
    friend class ::ConstReverseEdgeIterator<T, Props>;
    friend class ::ConstReverseIncidentEdgeIterator<T, Props>;
    friend class ::ConstReverseAdjacentVertexIterator<T, Props>;
    friend class ::ConstReverseInEdgeIterator<T, Props>;

private:
    struct Vertex {
        T value_;
        VertexKey key_;
        Props props_;
        EdgeKey first_out_edge_;
        EdgeKey first_in_edge_;
        VertexKey next_free_;

        Vertex(const T& val, VertexKey k, const Props& p = Props{}) :
            value_(val), key_(k), props_(p), first_out_edge_(-1), first_in_edge_(-1), next_free_(-1) {
        }
    };

    struct Edge {
        VertexKey from_;
        VertexKey to_;
        EdgeKey key_;
        Props props_;
        EdgeKey next_out_;
        EdgeKey next_in_;
        EdgeKey next_free_;

        Edge(VertexKey from, VertexKey to, EdgeKey key, const Props& p = Props{}) :
            from_(from), to_(to), key_(key), props_(p), next_out_(-1), next_in_(-1), next_free_(-1) {
        }
    };

    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;
    std::map<VertexKey, size_t> vertex_key_map_;
    std::map<EdgeKey, size_t> edge_key_map_;
    VertexKey next_vertex_key_ = 0;
    EdgeKey next_edge_key_ = 0;
    VertexKey free_vertex_head_ = -1;
    EdgeKey free_edge_head_ = -1;

    void add_to_out_list(VertexKey from, EdgeKey edge_key) {
        size_t vertex_index = vertex_key_map_[from];
        EdgeKey old_first = vertices_[vertex_index].first_out_edge_;

        vertices_[vertex_index].first_out_edge_ = edge_key;

        size_t edge_index = edge_key_map_[edge_key];
        edges_[edge_index].next_out_ = old_first;
    }

    void add_to_in_list(VertexKey to, EdgeKey edge_key) {
        size_t vertex_index = vertex_key_map_[to];
        EdgeKey old_first = vertices_[vertex_index].first_in_edge_;

        vertices_[vertex_index].first_in_edge_ = edge_key;

        size_t edge_index = edge_key_map_[edge_key];
        edges_[edge_index].next_in_ = old_first;
    }

    void remove_from_out_list(VertexKey from, EdgeKey edge_key) {
        size_t vertex_index = vertex_key_map_[from];
        EdgeKey current = vertices_[vertex_index].first_out_edge_;
        EdgeKey prev = -1;

        while (current != EdgeKey(-1)) {
            size_t current_index = edge_key_map_[current];
            if (current == edge_key) {
                if (prev == EdgeKey(-1)) {
                    vertices_[vertex_index].first_out_edge_ = edges_[current_index].next_out_;
                }
                else {
                    size_t prev_index = edge_key_map_[prev];
                    edges_[prev_index].next_out_ = edges_[current_index].next_out_;
                }
                break;
            }
            prev = current;
            current = edges_[current_index].next_out_;
        }
    }

    void remove_from_in_list(VertexKey to, EdgeKey edge_key) {
        size_t vertex_index = vertex_key_map_[to];
        EdgeKey current = vertices_[vertex_index].first_in_edge_;
        EdgeKey prev = -1;

        while (current != EdgeKey(-1)) {
            size_t current_index = edge_key_map_[current];
            if (current == edge_key) {
                if (prev == EdgeKey(-1)) {
                    vertices_[vertex_index].first_in_edge_ = edges_[current_index].next_in_;
                }
                else {
                    size_t prev_index = edge_key_map_[prev];
                    edges_[prev_index].next_in_ = edges_[current_index].next_in_;
                }
                break;
            }
            prev = current;
            current = edges_[current_index].next_in_;
        }
    }

    VertexKey get_free_vertex() {
        if (free_vertex_head_ != VertexKey(-1)) {
            VertexKey free_key = free_vertex_head_;
            size_t index = vertex_key_map_[free_key];
            free_vertex_head_ = vertices_[index].next_free_;
            vertices_[index].next_free_ = -1;
            return free_key;
        }
        return next_vertex_key_++;
    }

    EdgeKey get_free_edge() {
        if (free_edge_head_ != EdgeKey(-1)) {
            EdgeKey free_key = free_edge_head_;
            size_t index = edge_key_map_[free_key];
            free_edge_head_ = edges_[index].next_free_;
            edges_[index].next_free_ = -1;
            return free_key;
        }
        return next_edge_key_++;
    }

    void add_to_free_vertices(VertexKey vertex_key) {
        size_t index = vertex_key_map_[vertex_key];
        vertices_[index].next_free_ = free_vertex_head_;
        free_vertex_head_ = vertex_key;
    }

    void add_to_free_edges(EdgeKey edge_key) {
        size_t index = edge_key_map_[edge_key];
        edges_[index].next_free_ = free_edge_head_;
        free_edge_head_ = edge_key;
    }

public:
    Graph() = default;

    Graph(const Graph& other) {
        *this = other;
    }

    ~Graph() = default;
    
    Graph& operator=(const Graph& other) {
        if (this != &other) {
            vertices_ = other.vertices_;
            edges_ = other.edges_;
            vertex_key_map_ = other.vertex_key_map_;
            edge_key_map_ = other.edge_key_map_;
            next_vertex_key_ = other.next_vertex_key_;
            next_edge_key_ = other.next_edge_key_;
            free_vertex_head_ = other.free_vertex_head_;
            free_edge_head_ = other.free_edge_head_;
        }
        return *this;
    }

    bool empty() const {
        return vertices_count() == 0;
    }

    void clear() {
        vertices_.clear();
        edges_.clear();
        vertex_key_map_.clear();
        edge_key_map_.clear();
        next_vertex_key_ = 0;
        next_edge_key_ = 0;
        free_vertex_head_ = -1;
        free_edge_head_ = -1;
    }

    VertexKey add_vertex(const T& value, const Props& props = Props{}) {
        VertexKey key = get_free_vertex();

        if (vertex_key_map_.find(key) != vertex_key_map_.end()) {
            size_t index = vertex_key_map_[key];
            vertices_[index] = Vertex(value, key, props);
        }
        else {
            vertices_.emplace_back(value, key, props);
            vertex_key_map_[key] = vertices_.size() - 1;
        }

        return key;
    }

    void remove_vertex(VertexKey vertex_key) {
        if (!has_vertex(vertex_key)) throw std::out_of_range("Îøèáêà óäàëåíèÿ âåðøèíû");

        EdgeKey out_edge = vertices_[vertex_key_map_[vertex_key]].first_out_edge_;
        while (out_edge != EdgeKey(-1)) {
            EdgeKey next_out = edges_[edge_key_map_[out_edge]].next_out_;
            remove_edge(out_edge);
            out_edge = next_out;
        }

        EdgeKey in_edge = vertices_[vertex_key_map_[vertex_key]].first_in_edge_;
        while (in_edge != EdgeKey(-1)) {
            EdgeKey next_in = edges_[edge_key_map_[in_edge]].next_in_;
            remove_edge(in_edge);
            in_edge = next_in;
        }

        add_to_free_vertices(vertex_key);

        size_t index = vertex_key_map_[vertex_key];
        vertices_[index].first_out_edge_ = -1;
        vertices_[index].first_in_edge_ = -1;
    }

    EdgeKey add_edge(VertexKey from, VertexKey to, const Props& props = Props{}) {
        if (!has_vertex(from) || !has_vertex(to)) throw std::out_of_range("Îøèáêà äîáàâëåíèÿ ðåáðà");

        EdgeKey key = get_free_edge();

        if (edge_key_map_.find(key) != edge_key_map_.end()) {
            size_t index = edge_key_map_[key];
            edges_[index] = Edge(from, to, key, props);
        }
        else {
            edges_.emplace_back(from, to, key, props);
            edge_key_map_[key] = edges_.size() - 1;
        }

        add_to_out_list(from, key);
        add_to_in_list(to, key);

        return key;
    }

    void remove_edge(EdgeKey edge_key) {
        if (!has_edge(edge_key)) throw std::out_of_range("Îøèáêà óäàëåíèÿ ðåáðà");

        size_t index = edge_key_map_[edge_key];
        Edge& edge = edges_[index];

        remove_from_out_list(edge.from_, edge_key);
        remove_from_in_list(edge.to_, edge_key);

        add_to_free_edges(edge_key);

        edges_[index].next_out_ = -1;
        edges_[index].next_in_ = -1;
        edges_[index].from_ = -1;
        edges_[index].to_ = -1;
    }

    void remove_vertex(VertexIterator it) {
        remove_vertex(it.key());
    }

    void remove_edge(EdgeIterator it) {
        remove_edge(it.key());
    }

    bool has_vertex(VertexKey vertex_key) const {
        auto it = vertex_key_map_.find(vertex_key);
        if (it == vertex_key_map_.end()) return false;

        VertexKey current = free_vertex_head_;
        while (current != VertexKey(-1)) {
            if (current == vertex_key) return false;
            size_t index = vertex_key_map_.at(current);
            current = vertices_[index].next_free_;
        }
        return true;
    }

    bool has_edge(EdgeKey edge_key) const {
        auto it = edge_key_map_.find(edge_key);
        if (it == edge_key_map_.end()) return false;

        EdgeKey current = free_edge_head_;
        while (current != EdgeKey(-1)) {
            if (current == edge_key) return false;
            size_t index = edge_key_map_.at(current);
            current = edges_[index].next_free_;
        }
        return true;
    }

    size_type vertices_count() const {
        size_type count = 0;
        for (VertexKey vertex_key = 0; vertex_key < next_vertex_key_; vertex_key++) 
            if (has_vertex(vertex_key)) count++;
        return count;
    }

    size_type edges_count() const {
        size_type count = 0;
        for (EdgeKey edge_key = 0; edge_key < next_edge_key_; edge_key++) 
            if (has_edge(edge_key)) count++;
        return count;
    }

    size_type out_degree(VertexKey vertex_key) const {
        if (!has_vertex(vertex_key)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");

        size_t count = 0;
        EdgeKey current = vertices_[vertex_key_map_.at(vertex_key)].first_out_edge_;
        while (current != EdgeKey(-1)) {
            if (has_edge(current)) count++;
            current = edges_[edge_key_map_.at(current)].next_out_;
        }
        return count;
    }

    size_type in_degree(VertexKey vertex_key) const {
        if (!has_vertex(vertex_key)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");

        size_t count = 0;
        EdgeKey current = vertices_[vertex_key_map_.at(vertex_key)].first_in_edge_;
        while (current != EdgeKey(-1)) {
            if (has_edge(current)) count++;
            current = edges_[edge_key_map_.at(current)].next_in_;
        }
        return count;
    }

    reference vertex_value(VertexKey vertex_key) {
        if (!has_vertex(vertex_key)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(vertex_key);
        return vertices_[index].value_;
    }

    const_reference vertex_value(VertexKey vertex_key) const {
        if (!has_vertex(vertex_key)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(vertex_key);
        return vertices_[index].value_;
    }

    Props& vertex_props(VertexKey vertex_key) {
        if (!has_vertex(vertex_key)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(vertex_key);
        return vertices_[index].props_;
    }

    const Props& vertex_props(VertexKey vertex_key) const {
        if (!has_vertex(vertex_key)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(vertex_key);
        return vertices_[index].props_;
    }

    std::pair<VertexKey, VertexKey> edge_endpoints(EdgeKey edge_key) const {
        if (!has_edge(edge_key)) throw std::out_of_range("Ðåáðî íåêîððåêòíî");
        size_t index = edge_key_map_.at(edge_key);
        const Edge& edge = edges_[index];
        return { edge.from_, edge.to_ };
    }

    Props& edge_props(EdgeKey edge_key) {
        if (!has_edge(edge_key)) throw std::out_of_range("Ðåáðî íåêîððåêòíî");
        size_t index = edge_key_map_.at(edge_key);
        return edges_[index].props_;
    }

    const Props& edge_props(EdgeKey edge_key) const {
        if (!has_edge(edge_key)) throw std::out_of_range("Ðåáðî íåêîððåêòíî");
        size_t index = edge_key_map_.at(edge_key);
        return edges_[index].props_;
    }

    EdgeKey find_edge(VertexKey from, VertexKey to) const {
        if (!has_vertex(from) || !has_vertex(to)) throw std::out_of_range("Îäíà èëè îáå âåðøèíû íå íàéäåíû");

        EdgeKey current = vertices_[vertex_key_map_.at(from)].first_out_edge_;
        while (current != EdgeKey(-1)) {
            if (has_edge(current)) {
                size_t edge_index = edge_key_map_.at(current);
                if (edges_[edge_index].to_ == to) return current;
            }
            current = edges_[edge_key_map_.at(current)].next_out_;
        }
        throw std::out_of_range("Ðåáðî íå íàéäåíî");
    }

    VertexIterator vertices_begin() {
        return VertexIterator(this, 0);
    }

    VertexIterator vertices_end() {
        return VertexIterator(this, vertices_.size());
    }

    EdgeIterator edges_begin() {
        return EdgeIterator(this, 0);
    }

    EdgeIterator edges_end() {
        return EdgeIterator(this, edges_.size());
    }

    IncidentEdgeIterator out_edges_begin(VertexKey v) {
        if (!has_vertex(v)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(v);
        return IncidentEdgeIterator(this, vertices_[index].first_out_edge_);
    }

    IncidentEdgeIterator out_edges_end(VertexKey v) {
        return IncidentEdgeIterator(this, EdgeKey(-1));
    }

    InEdgeIterator in_edges_begin(VertexKey v) {
        if (!has_vertex(v)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(v);
        return InEdgeIterator(this, vertices_[index].first_in_edge_);
    }

    InEdgeIterator in_edges_end(VertexKey v) {
        return InEdgeIterator(this, EdgeKey(-1));
    }

    AdjacentVertexIterator adjacent_begin(VertexKey v) {
        if (!has_vertex(v)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(v);
        return AdjacentVertexIterator(this, vertices_[index].first_out_edge_);
    }

    AdjacentVertexIterator adjacent_end(VertexKey v) {
        return AdjacentVertexIterator(this, EdgeKey(-1));
    }

    ReverseVertexIterator vertices_rbegin() {
        return ReverseVertexIterator(vertices_end());
    }

    ReverseVertexIterator vertices_rend() {
        return ReverseVertexIterator(vertices_begin());
    }

    ReverseEdgeIterator edges_rbegin() {
        return ReverseEdgeIterator(edges_end());
    }

    ReverseEdgeIterator edges_rend() {
        return ReverseEdgeIterator(edges_begin());
    }

    ReverseIncidentEdgeIterator out_edges_rbegin(VertexKey v) {
        return ReverseIncidentEdgeIterator(out_edges_end(v));
    }

    ReverseIncidentEdgeIterator out_edges_rend(VertexKey v) {
        return ReverseIncidentEdgeIterator(out_edges_begin(v));
    }

    ReverseInEdgeIterator in_edges_rbegin(VertexKey v) {
        return ReverseInEdgeIterator(in_edges_end(v));
    }

    ReverseInEdgeIterator in_edges_rend(VertexKey v) {
        return ReverseInEdgeIterator(in_edges_begin(v));
    }

    ReverseAdjacentVertexIterator adjacent_rbegin(VertexKey v) {
        return ReverseAdjacentVertexIterator(adjacent_end(v));
    }

    ReverseAdjacentVertexIterator adjacent_rend(VertexKey v) {
        return ReverseAdjacentVertexIterator(adjacent_begin(v));
    }

    ConstVertexIterator vertices_begin() const {
        return ConstVertexIterator(this, 0);
    }

    ConstVertexIterator vertices_end() const {
        return ConstVertexIterator(this, vertices_.size());
    }

    ConstEdgeIterator edges_begin() const {
        return ConstEdgeIterator(this, 0);
    }

    ConstEdgeIterator edges_end() const {
        return ConstEdgeIterator(this, edges_.size());
    }

    ConstIncidentEdgeIterator out_edges_begin(VertexKey v) const {
        if (!has_vertex(v)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(v);
        return ConstIncidentEdgeIterator(this, vertices_[index].first_out_edge_);
    }

    ConstIncidentEdgeIterator out_edges_end(VertexKey v) const {
        return ConstIncidentEdgeIterator(this, EdgeKey(-1));
    }

    ConstInEdgeIterator in_edges_begin(VertexKey v) const {
        if (!has_vertex(v)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(v);
        return ConstInEdgeIterator(this, vertices_[index].first_in_edge_);
    }

    ConstInEdgeIterator in_edges_end(VertexKey v) const {
        return ConstInEdgeIterator(this, EdgeKey(-1));
    }

    ConstAdjacentVertexIterator adjacent_begin(VertexKey v) const {
        if (!has_vertex(v)) throw std::out_of_range("Âåðøèíà íåêîððåêòíà");
        size_t index = vertex_key_map_.at(v);
        return ConstAdjacentVertexIterator(this, vertices_[index].first_out_edge_);
    }

    ConstAdjacentVertexIterator adjacent_end(VertexKey v) const {
        return ConstAdjacentVertexIterator(this, EdgeKey(-1));
    }

    ConstReverseVertexIterator vertices_rbegin() const {
        return ConstReverseVertexIterator(vertices_end());
    }

    ConstReverseVertexIterator vertices_rend() const {
        return ConstReverseVertexIterator(vertices_begin());
    }

    ConstReverseEdgeIterator edges_rbegin() const {
        return ConstReverseEdgeIterator(edges_end());
    }

    ConstReverseEdgeIterator edges_rend() const {
        return ConstReverseEdgeIterator(edges_begin());
    }

    ConstReverseIncidentEdgeIterator out_edges_rbegin(VertexKey v) const {
        return ConstReverseIncidentEdgeIterator(out_edges_end(v));
    }

    ConstReverseIncidentEdgeIterator out_edges_rend(VertexKey v) const {
        return ConstReverseIncidentEdgeIterator(out_edges_begin(v));
    }

    ConstReverseInEdgeIterator in_edges_rbegin(VertexKey v) const {
        return ConstReverseInEdgeIterator(in_edges_end(v));
    }

    ConstReverseInEdgeIterator in_edges_rend(VertexKey v) const {
        return ConstReverseInEdgeIterator(in_edges_begin(v));
    }

    ConstReverseAdjacentVertexIterator adjacent_rbegin(VertexKey v) const {
        return ConstReverseAdjacentVertexIterator(adjacent_end(v));
    }

    ConstReverseAdjacentVertexIterator adjacent_rend(VertexKey v) const {
        return ConstReverseAdjacentVertexIterator(adjacent_begin(v));
    }

    bool operator==(const Graph& other) const {
        if (vertices_count() != other.vertices_count() || edges_count() != other.edges_count()) {
            return false;
        }

        auto vit1 = vertices_begin();
        auto vit2 = other.vertices_begin();
        while (vit1 != vertices_end() && vit2 != other.vertices_end()) {
            if (!(*vit1 == *vit2)) return false;
            ++vit1;
            ++vit2;
        }

        auto eit1 = edges_begin();
        auto eit2 = other.edges_begin();
        while (eit1 != edges_end() && eit2 != other.edges_end()) {
            if (*eit1 != *eit2) return false;
            ++eit1;
            ++eit2;
        }

        return true;
    }

    bool operator!=(const Graph& other) const {
        return !(*this == other);
    }

    bool operator<(const Graph& other) const {
        return vertices_count() < other.vertices_count();
    }

    bool operator>(const Graph& other) const {
        return other < *this;
    }

    bool operator<=(const Graph& other) const {
        return !(*this > other);
    }

    bool operator>=(const Graph& other) const {
        return !(*this < other);
    }

    friend std::ostream& operator<<(std::ostream& out, const Graph& graph) {
        out << "Âåðøèíû (" << graph.vertices_count() << "):\n";
        for (auto vit = graph.vertices_begin(); vit != graph.vertices_end(); ++vit) {
            out << "  v" << vit.key() << ": " << *vit << "\n";
        }

        out << "Ð¸áðà (" << graph.edges_count() << "):\n";
        for (auto eit = graph.edges_begin(); eit != graph.edges_end(); ++eit) {
            auto endpoints = graph.edge_endpoints(eit.key());
            out << "  e" << eit.key() << ": v" << endpoints.first << " -> v" << endpoints.second << "\n";
        }

        return out;
    }
};

#include "VertexIterator.h"
#include "EdgeIterator.h"
#include "IncidentEdgeIterator.h"
#include "AdjacentVertexIterator.h"
#include "InEdgeIterator.h"
