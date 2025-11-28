#pragma once
#include "Graph.h"

template <typename T, typename Props>
class VertexIterator {
private:
    Graph<T, Props>* graph_;
    size_t index_;

    void advance_to_valid() {
        while (index_ < graph_->vertices_.size() && !graph_->has_vertex(graph_->vertices_[index_].key_)) index_++;
    }

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    VertexIterator() : graph_(nullptr), index_(0) {}
    VertexIterator(Graph<T, Props>* graph, size_t index) : graph_(graph), index_(index) {
        advance_to_valid();
    }

    reference operator*() {
        return graph_->vertices_[index_].value_;
    }

    pointer operator->() {
        return &graph_->vertices_[index_].value_;
    }

    VertexIterator& operator++() {
        ++index_;
        advance_to_valid();
        return *this;
    }

    VertexIterator operator++(int) {
        VertexIterator tmp = *this;
        ++*this;
        return tmp;
    }

    VertexIterator& operator--() {
        --index_;
        while (index_ > 0 && !graph_->has_vertex(graph_->vertices_[index_].key_)) --index_;
        return *this;
    }

    VertexIterator operator--(int) {
        VertexIterator tmp = *this;
        --*this;
        return tmp;
    }

    bool operator==(const VertexIterator& other) const {
        return graph_ == other.graph_ && index_ == other.index_;
    }

    bool operator!=(const VertexIterator& other) const {
        return !(*this == other);
    }

    VertexKey key() const {
        return graph_->vertices_[index_].key_;
    }
};

template <typename T, typename Props>
class ConstVertexIterator {
private:
    const Graph<T, Props>* graph_;
    size_t index_;

    void advance_to_valid() {
        while (index_ < graph_->vertices_.size() && !graph_->has_vertex(graph_->vertices_[index_].key_)) index_++;
    }

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    ConstVertexIterator() : graph_(nullptr), index_(0) {}
    ConstVertexIterator(const Graph<T, Props>* graph, size_t index) : graph_(graph), index_(index) {
        advance_to_valid();
    }

    reference operator*() const {
        return graph_->vertices_[index_].value_;
    }

    pointer operator->() const {
        return &graph_->vertices_[index_].value_;
    }

    ConstVertexIterator& operator++() {
        ++index_;
        advance_to_valid();
        return *this;
    }

    ConstVertexIterator operator++(int) {
        ConstVertexIterator tmp = *this;
        ++*this;
        return tmp;
    }

    ConstVertexIterator& operator--() {
        --index_;
        while (index_ > 0 && !graph_->has_vertex(graph_->vertices_[index_].key_)) --index_;
        return *this;
    }

    ConstVertexIterator operator--(int) {
        ConstVertexIterator tmp = *this;
        --*this;
        return tmp;
    }

    bool operator==(const ConstVertexIterator& other) const {
        return graph_ == other.graph_ && index_ == other.index_;
    }

    bool operator!=(const ConstVertexIterator& other) const {
        return !(*this == other);
    }

    VertexKey key() const {
        return graph_->vertices_[index_].key_;
    }
};