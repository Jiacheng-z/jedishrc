#include <iostream>
#include <string>

#include <jedishrc/jedishrc.h>

int main() {
    jedishrc::JedishrcConfig config{
        {"node1", 1},
        {"node2", 1},
        {"node3", 1}
    };

    jedishrc::Jedishrc pool(config);

    auto get_node = [&](const std::string& key) {
      auto node = pool.GetNode(key);
      std::cout << "Key: " << key << ", NodeName: " << node.first << ", NodeWeight: " << node.second << std::endl;
    };

    get_node("123");
    get_node("456");
    get_node("123");
}
