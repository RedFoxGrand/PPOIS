#pragma once
#include "Graph.h"

template <typename T, typename Props>
class IncidentEdgeIterator {
private:
    Graph<T, Props>* graph_;
    EdgeKey current_;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = EdgeKey;
    using difference_type = std::ptrdiff_t;

    IncidentEdgeIterator() : graph_(nullptr), current_(-1) {}
    IncidentEdgeIterator(Graph<T, Props>* graph, EdgeKey start) : graph_(graph), current_(start) {
        while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
    }

    EdgeKey operator*() const {
        return current_;
    }

    IncidentEdgeIterator& operator++() {
        if (current_ != EdgeKey(-1)) {
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
            while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
                current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
        }
        return *this;
    }

    IncidentEdgeIterator operator++(int) {
        IncidentEdgeIterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const IncidentEdgeIterator& other) const {
        return graph_ == other.graph_ && current_ == other.current_;
    }

    bool operator!=(const IncidentEdgeIterator& other) const {
        return !(*this == other);
    }
};

template <typename T, typename Props>
class ConstIncidentEdgeIterator {
private:
    const Graph<T, Props>* graph_;
    EdgeKey current_;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = EdgeKey;
    using difference_type = std::ptrdiff_t;

    ConstIncidentEdgeIterator() : graph_(nullptr), current_(-1) {}
    ConstIncidentEdgeIterator(const Graph<T, Props>* graph, EdgeKey start) : graph_(graph), current_(start) {
        while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
    }

    EdgeKey operator*() const {
        return current_;
    }

    ConstIncidentEdgeIterator& operator++() {
        if (current_ != EdgeKey(-1)) {
            current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
            while (current_ != EdgeKey(-1) && !graph_->has_edge(current_))
                current_ = graph_->edges_[graph_->edge_key_map_.at(current_)].next_out_;
        }
        return *this;
    }

    ConstIncidentEdgeIterator operator++(int) {
        ConstIncidentEdgeIterator tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const ConstIncidentEdgeIterator& other) const {
        return graph_ == other.graph_ && current_ == other.current_;
    }

    bool operator!=(const ConstIncidentEdgeIterator& other) const {
        return !(*this == other);
    }
};