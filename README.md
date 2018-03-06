[中文版](https://github.com/Jiacheng-z/jedishrc/blob/master/README_ZH.md)

# jedishrc
Resolved Java(use Jedis) and C++ projects need to use same redis cluster.

### Feature
- Realize the Jedis hash ring. Use same consisten hash.

### Usage
Example: [example/simple.cpp](https://github.com/Jiacheng-z/jedishrc/blob/master/example/simple.cpp)

```
//Create Redis cluster nodes, {node_name, node_weight}.
jedishrc::JedishrcConfig config{
  {"Node1:8000", 1}, {"Node2:8001", 1}, {"Node3:8002", 1}
};

//Create hash ring with config.
jedishrc::Jedishrc pool(config);
auto node = pool.GetNode(key);
```

### Depend on
- C++11
