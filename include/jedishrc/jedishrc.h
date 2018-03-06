/**
 * @file jedishrc.h
 * @brief A Hash Ring like Jedis.
 * @author jiacheng
 * @date 2018-03-06
 */
#ifndef JEDISHASH_JEDISHRC_H
#define JEDISHASH_JEDISHRC_H

#include "config.h"
#include "murmurhash/murmurhash.h"

#include <cstdint>
#include <map>

namespace jedishrc {

using Index = unsigned long;

class Jedishrc {
 public:

  /**
   * Init hash ring with JedishrcConfig.
   * @param config
   */
  explicit Jedishrc(JedishrcConfig config) {
      for (const auto &node: config.Nodes()) {
          AddNodeToHashRing(node);
      }
  };

  /**
   * Find which node the redis key falls on
   *
   * Typical usage:
   * @code
   * JedishrcConfig config{...};
   * Jedishrc hash_ring(config);
   *
   * //find key
   * auto node = hash_ring.GetNode("redis key");
   * std::cout << node.first << std::endl;
   *
   * ...Find the node name corresponding redis connection...
   * ...Get value from redis connection...
   * @endcode
   *
   * @param key redis key.
   * @return
   */
  Node GetNode(const std::string &key) {
      auto iter = ring_hash_.upper_bound(Hash(key));
      if (iter == ring_hash_.end()) {
          iter = ring_hash_.begin();
      }
      return indexes_.find(iter->second)->second;
  }

 private:

  /**
   * Use murmurhash
   *
   * seed 0x1234ABCD is Jedis seed.
   * If your Jedis uses other seeds, you need to change here.
   *
   * @param key
   * @return
   */
  uint64_t Hash(const std::string &key) {
      return MurmurHash64A(key.data(), static_cast<int>(key.size()), 0x1234ABCD); //seed is same to jedis
  }

  /**
   * Add node to hash ring with Jedis algorithm.
   * @param node
   */
  void AddNodeToHashRing(const Node &node) {
      Index index = indexes_.size();
      indexes_.insert({index, node});

      // 一致性哈希算法（虚拟节点hash值 -> 分片节点）
      int weight = 160 * node.second; // 放大160倍

      for (int n = 0; n < weight; n++) {
          // 2. shardInfo.getName() + "*" + shardInfo.getWeight() + n
          // 坑："节点名称+权重"必须是唯一的，否则节点会出现重叠覆盖！
          // 同时，"节点名称+权重"不能被中途改变！
          // 【优点】这样设计避免了上面"因节点顺序调整而引发rehash"的问题
          auto hash = Hash(node.first + "*" + std::to_string(node.second) + std::to_string(n));
          ring_hash_.insert({hash, index});
      }
  }

  std::map<Index, Node> indexes_{};
  std::map<uint64_t, Index> ring_hash_{};
};

} // namespace jedishrc

#endif //JEDISHASH_JEDISHRC_H
