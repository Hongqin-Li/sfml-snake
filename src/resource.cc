#include "resource.h"

ResourceManager& ResourceManager::getInstance()
{
  static ResourceManager r;
  return r;
}
