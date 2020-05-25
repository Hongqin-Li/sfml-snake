#ifndef SRC_RESOURCE_H_
#define SRC_RESOURCE_H_

#include <cassert>
#include <iostream>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "utils/non_copyable.h"
#include "utils/non_moveable.h"

template<typename T>
struct ResourceEntry
{
  T resource;
  int ref;
};

template<typename T>
class ResourceHolder
{
 public:
  ResourceHolder() { };

  void acquire(const std::string& path)
  {
    auto& r = resource_[path];
    if (r.ref == 0) {
      assert(r.resource.loadFromFile(path));
    }
#ifdef DEBUG
    if (r.ref == 0)
      std::cout << "[Resource] acquire(first ref) " << path << std::endl;
    else
      std::cout << "[Resource] release" << path << std::endl;
#endif
  
    r.ref ++;
  };

  void release(const std::string& path)
  {
    auto it = resource_.find(path);
    assert(it != resource_.end());

    it->second.ref --;
  
#ifdef DEBUG
    if (it->second.ref == 0)
      std::cout << "[Resource] release(last ref) " << path << std::endl;
    else
      std::cout << "[Resource] release" << path << std::endl;
#endif
  
    if (it->second.ref == 0)
      resource_.erase(it);

  };
  const T& get(const std::string& path)
  {
    return resource_[path].resource;
  };

 private:
  std::unordered_map<std::string, ResourceEntry<T>> resource_;
};


// Singleton
class ResourceManager : public NonCopyable, public NonMoveable
{
 public:
  static ResourceManager& getInstance();
  
  ResourceHolder<sf::Font> fonts;
  ResourceHolder<sf::Texture> textures;
 private:
  ResourceManager() : fonts(), textures() {};
  ~ResourceManager() {};
 
};

#endif  // SRC_RESOURCE_H_
