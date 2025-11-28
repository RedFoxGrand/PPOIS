#pragma once
#include "Graph.h"

template <typename T, typename Props>
class AdjacentVertexIterator {
private:
    Graph<T, Props>* graph_;
    EdgeKey current_;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = VertexKey;
    using difference_type = std::ptrdiff_t;

    AdjacentVertexIterator() : graph_(nullptr), current_(-1) {}
    AdjacentVertexIterator(Graph<T, Props>* graph, EdgeKey start) : graph_(graph), current_(start) {
        while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
    }

    VertexKey operator*() const {
        return graph_->edges_[graph_->edge_key_map_.at(current_)].to_;
    }

    AdjacentVertexIterator& operator++() {
        if (current_ != EdgeKey(-1)) {
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
            while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
                current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
        }
        return *this;
    }

    AdjacentVertexIterator operator++(int) {
        AdjacentVertexIterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const AdjacentVertexIterator& other) const {
        return graph_ == other.graph_ && current_ == other.current_;
    }

    bool operator!=(const AdjacentVertexIterator& other) const {
        return !(*this == other);
    }
};

template <typename T, typename Props>
class ConstAdjacentVertexIterator {
private:
    const Graph<T, Props>* graph_;
    EdgeKey current_;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = VertexKey;
    using difference_type = std::ptrdiff_t;

    ConstAdjacentVertexIterator() : graph_(nullptr), current_(-1) {}
    ConstAdjacentVertexIterator(const Graph<T, Props>* graph, EdgeKey start) : graph_(graph), current_(start) {
        while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
    }

    VertexKey operator*() const {
        return graph_->edges_[graph_->edge_key_map_.at(current_)].to_;
    }

    ConstAdjacentVertexIterator& operator++() {
        if (current_ != EdgeKey(-1)) {
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
            while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
                current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
        }
        return *this;
    }

    ConstAdjacentVertexIterator operator++(int) {
        ConstAdjacentVertexIterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const ConstAdjacentVertexIterator& other) const {
        return graph_ == other.graph_ && current_ == other.current_;
    }

    bool operator!=(const ConstAdjacentVertexIterator& other) const {
        return !(*this == other);
    }
};