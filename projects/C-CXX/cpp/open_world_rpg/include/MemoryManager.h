// MemoryManager.h
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>

class MemoryManager {
private:
  size_t poolSize;
  char *memoryPool;
  bool *memoryBlockStatus;
  size_t blockSize;
  size_t numBlocks;

public:
  MemoryManager(size_t block_size, size_t num_blocks);
  ~MemoryManager();

  void *allocate();
  void deallocate(void *ptr);
  void printStatus() const;
};

#endif
