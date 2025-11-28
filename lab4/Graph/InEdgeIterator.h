#pragma once
#include "Graph.h"

template <typename T, typename Props>
class InEdgeIterator {
private:
    Graph<T, Props>* graph_;
    EdgeKey current_;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = EdgeKey;
    using difference_type = std::ptrdiff_t;

    InEdgeIterator() : graph_(nullptr), current_(-1) {}
    InEdgeIterator(Graph<T, Props>* graph, EdgeKey start) : graph_(graph), current_(start) {
        while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_in_;
    }

    EdgeKey operator*() const {
        return current_;
    }

    InEdgeIterator& operator++() {
        if (current_ != EdgeKey(-1)) {
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_in_;
            while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
                current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_in_;
        }
        return *this;
    }

    InEdgeIterator operator++(int) {
        InEdgeIterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const InEdgeIterator& other) const {
        return graph_ == other.graph_ && current_ == other.current_;
    }

    bool operator!=(const InEdgeIterator& other) const {
        return !(*this == other);
    }
};

template <typename T, typename Props>
class ConstInEdgeIterator {
private:
    const Graph<T, Props>* graph_;
    EdgeKey current_;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = EdgeKey;
    using difference_type = std::ptrdiff_t;

    ConstInEdgeIterator() : graph_(nullptr), current_(-1) {}
    ConstInEdgeIterator(const Graph<T, Props>* graph, EdgeKey start) : graph_(graph), current_(start) {
        while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_in_;
    }

    EdgeKey operator*() const {
        return current_;
    }

    ConstInEdgeIterator& operator++() {
        if (current_ != EdgeKey(-1)) {
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_in_;
            while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
                current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_in_;
        }
        return *this;
    }

    ConstInEdgeIterator operator++(int) {
        ConstInEdgeIterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const ConstInEdgeIterator& other) const {
        return graph_ == other.graph_ && current_ == other.current_;
    }

    bool operator!=(const ConstInEdgeIterator& other) const {
        return !(*this == other);
    }
};