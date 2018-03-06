/**
 * @file config.h
 * @brief Init node name and weight.
 * @author jiacheng
 * @date 2018-03-06
 */
#ifndef JEDISHASH_CONFIG_H
#define JEDISHASH_CONFIG_H

#include <vector>
#include <string>
#include <utility>
#include <initializer_list>

namespace jedishrc {

/**
 * Node Name is globally unique
 */
using NodeName = std::string;
using NodeWeight = int;
using Node = std::pair<NodeName, NodeWeight>;

/**
 * Cluster node name and weight.
 */
class JedishrcConfig {
 public:
  JedishrcConfig() = default;

  /**
   * Init with vector<Node>
   *
   * Typical usage:
   * @code
   * std::vector<Node> nodes{ {"node1", 1}, {"node2", 1}, ...};
   * JedishrcConfig config(nodes);
   * @endcode
   *
   * @param nodes
   */
  explicit JedishrcConfig(std::vector<Node> nodes) : redis_nodes_(std::move(nodes)) {};

  /**
   * Init with initializer list.
   *
   * Typical usage:
   * @code
   * JedishrcConfig config{ {"node1", 1}, {"node2", 1}, ...};
   * @endcode
   *
   * @param nodes
   */
  explicit JedishrcConfig(std::initializer_list<Node> nodes) {
    for(const auto& node: nodes) {
        AddNode(node);
    }
  }

  /**
   * Add a new node to nodes config.
   *
   * @param n
   */
  void AddNode(Node n) {
      redis_nodes_.push_back(std::move(n));
  }

  /**
   * Get var.
   * @return
   */
  std::vector<Node> Nodes() {
      return redis_nodes_;
  }

 private:
  std::vector<Node> redis_nodes_;
};

} // namespace jedishrc

#endif //JEDISHASH_CONFIG_H
