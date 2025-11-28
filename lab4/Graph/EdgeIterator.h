#pragma once
#include "Graph.h"

template <typename T, typename Props>
class EdgeIterator {
private:
    Graph<T, Props>* graph_;
    size_t index_;

    void advance_to_valid() {
        while (index_ < graph_->edges_.size() && !graph_->has_edge(graph_->edges_[index_].key_)) index_++;
    }

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair<VertexKey, VertexKey>;
    using difference_type = std::ptrdiff_t;

    EdgeIterator() : graph_(nullptr), index_(0) {}
    EdgeIterator(Graph<T, Props>* graph, size_t index) : graph_(graph), index_(index) {
        advance_to_valid();
    }

    value_type operator*() const {
        const auto& e = graph_->edges_[index_];
        return { e.from_, e.to_ };
    }

    EdgeIterator& operator++() {
        ++index_;
        advance_to_valid();
        return *this;
    }

    EdgeIterator operator++(int) {
        EdgeIterator tmp = *this;
        ++*this;
        return tmp;
    }

    EdgeIterator& operator--() {
        --index_;
        while (index_ > 0 && !graph_->has_edge(graph_->edges_[index_].key_)) --index_;
        return *this;
    }

    EdgeIterator operator--(int) {
        EdgeIterator tmp = *this;
        --*this;
        return tmp;
    }

    bool operator==(const EdgeIterator& other) const {
        return graph_ == other.graph_ && index_ == other.index_;
    }

    bool operator!=(const EdgeIterator& other) const {
        return !(*this == other);
    }

    EdgeKey key() const {
        return graph_->edges_[index_].key_;
    }
};

template <typename T, typename Props>
class ConstEdgeIterator {
private:
    const Graph<T, Props>* graph_;
    size_t index_;

    void advance_to_valid() {
        while (index_ < graph_->edges_.size() && !graph_->has_edge(graph_->edges_[index_].key_)) index_++;
    }

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair<VertexKey, VertexKey>;
    using difference_type = std::ptrdiff_t;

    ConstEdgeIterator() : graph_(nullptr), index_(0) {}
    ConstEdgeIterator(const Graph<T, Props>* graph, size_t index) : graph_(graph), index_(index) {
        advance_to_valid();
    }

    value_type operator*() const {
        const auto& e = graph_->edges_[index_];
        return { e.from_, e.to_ };
    }

    ConstEdgeIterator& operator++() {
        ++index_;
        advance_to_valid();
        return *this;
    }

    ConstEdgeIterator operator++(int) {
        ConstEdgeIterator tmp = *this;
        ++*this;
        return tmp;
    }

    ConstEdgeIterator& operator--() {
        --index_;
        while (index_ > 0 && !graph_->has_edge(graph_->edges_[index_].key_)) --index_;
        return *this;
    }

    ConstEdgeIterator operator--(int) {
        ConstEdgeIterator tmp = *this;
        --*this;
        return tmp;
    }

    bool operator==(const ConstEdgeIterator& other) const {
        return graph_ == other.graph_ && index_ == other.index_;
    }

    bool operator!=(const ConstEdgeIterator& other) const {
        return !(*this == other);
    }

    EdgeKey key() const {
        return graph_->edges_[index_].key_;
    }
};