# jedishrc
解决Java(使用Jedis)和C++项目需要使用同一个Redis集群时一致性哈希的问题.

### 功能
- 实现Jedis hash ring. 可让C++与Java产生相同的哈希环, 保证数据正常存取.

### 使用
例子: [example/simple.cpp](https://github.com/Jiacheng-z/jedishrc/blob/master/example/simple.cpp)

```
//创建redis集群配置, {节点名称, 节点权重}
jedishrc::JedishrcConfig config{
  {"Node1:8000", 1}, {"Node2:8001", 1}, {"Node3:8002", 1}
};

//生成对应的hash ring
jedishrc::Jedishrc pool(config);
auto node = pool.GetNode(key);
```

### 依赖
- C++11
