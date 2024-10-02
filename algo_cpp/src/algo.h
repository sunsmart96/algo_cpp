#ifndef ALGO_H
#define ALGO_H
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

template <typename T> void swap(T &a, T &b) {
  T c = a;
  a = b;
  b = c;
}

struct Search_Res {
  Search_Res(size_t index_in, bool is_found_in) {
    index = index_in;
    is_found = is_found_in;
  }

  size_t index;
  bool is_found;
};

uint64_t gcd(uint64_t p, uint64_t q);

// vector v is ascending order
Search_Res binary_search(std::vector<int> v, int target_value);

// Bag data structure
template <typename T> class Bag {
public:
  Bag();

  void add(T data);

  bool is_empty();

  size_t size();

  auto begin() { return this->v.begin(); }

  auto end() { return this->v.end(); }

private:
  std::vector<T> v;
};

template <typename T> struct Node {

  Node(T n) {
    this->p_backward = nullptr;
    this->value = n;
  }

  ~Node() { this->p_backward = nullptr; }
  std::shared_ptr<Node<T>> p_backward;
  T value;
};

template <typename T> class FIFO_QUEUE {
public:
  FIFO_QUEUE() {
    n = 0;
    p_head = nullptr;
  }
  void enqueue(std::shared_ptr<T> node) {

    std::shared_ptr<T> new_node = std::make_shared<T>(node.get()->value);

    if (p_head == nullptr)
      p_head = new_node;
    else {
      std::shared_ptr<T> p = p_head;
      while (p.get()->p_backward != nullptr) {
        p = p.get()->p_backward;
      }
      p.get()->p_backward = new_node;
    }

    n = n + 1;
  }

  bool is_empty() { return n == 0 ? true : false; }
  size_t size() { return n; }

  std::shared_ptr<T> dequeue() {
    if (this->is_empty())
      return nullptr;
    else if (n > 1) {

      std::shared_ptr<T> res = p_head;
      p_head = p_head.get()->p_backward;
      res.get()->p_backward = nullptr;
      n = n - 1;
      return res;
    } else if (n == 1) {
      std::shared_ptr<T> res = this->p_head;
      p_head = nullptr;
      n = n - 1;
      return res;
    } else
      return nullptr;
  }

  void print() const {
    std::shared_ptr<T> p = p_head;
    for (size_t i = 0; i < n; i++) {
      std::cout << p.get()->value << std::endl;
      p = p.get()->p_backward;
    }
  }

private:
  size_t n;
  std::shared_ptr<T> p_head;
};

template <typename T> class LIFO_STACK {
public:
  LIFO_STACK() {
    n = 0;
    p_head = nullptr;
  }

  void push(std::shared_ptr<T> node) {

    std::shared_ptr<T> new_node = std::make_shared<T>(node.get()->value);

    if (p_head == nullptr)
      p_head = new_node;
    else {
      std::shared_ptr<T> p = p_head;
      while (p.get()->p_backward != nullptr) {
        p = p.get()->p_backward;
      }
      p.get()->p_backward = new_node;
    }

    n = n + 1;
  }

  std::shared_ptr<T> pop() {

    if (this->is_empty())
      return nullptr;
    else if (n > 1) {
      std::shared_ptr<T> p = p_head;
      for (int i = 0; i < n - 2; i++)
        p = p.get()->p_backward;
      std::shared_ptr<T> res = p.get()->p_backward;
      p.get()->p_backward = nullptr;
      n = n - 1;
      return res;
    } else if (n == 1) {
      std::shared_ptr<T> res = this->p_head;
      p_head = nullptr;
      n = n - 1;
      return res;
    } else
      return nullptr;
  }

  bool is_empty() { return n == 0 ? true : false; }
  size_t size() { return n; }

private:
  size_t n;
  std::shared_ptr<T> p_head;
};
#endif