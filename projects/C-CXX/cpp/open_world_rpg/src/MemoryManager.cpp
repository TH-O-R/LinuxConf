// MemoryManager.cpp
#include "../include/MemoryManager.h"
#include <iostream>

MemoryManager::MemoryManager(size_t block_size, size_t num_blocks)
    : blockSize(block_size), numBlocks(num_blocks) {
  poolSize = blockSize * numBlocks;
  memoryPool = (char *)malloc(poolSize);
  assert(memoryPool && "Memory allocation failed");

  memoryBlockStatus = new bool[numBlocks];
  for (size_t i = 0; i < numBlocks; ++i) {
    memoryBlockStatus[i] = true; // means it's free
  }
}

MemoryManager::~MemoryManager() {
  free(memoryPool);
  delete[] memoryBlockStatus;
}

void *MemoryManager::allocate() {
  for (size_t i = 0; i < numBlocks; ++i) {
    if (memoryBlockStatus[i]) {
      memoryBlockStatus[i] = false;
      return memoryPool + i * blockSize;
    }
  }
  std::cerr << "Out of memory!" << std::endl;
  return nullptr;
}

void MemoryManager::deallocate(void *ptr) {
  size_t blockIndex = (static_cast<char *>(ptr) - memoryPool) / blockSize;
  if (blockIndex < numBlocks) {
    memoryBlockStatus[blockIndex] = true;
  } else {
    std::cerr << "Invalid pointer deallocation!" << std::endl;
  }
}

void MemoryManager::printStatus() const {
  for (size_t i = 0; i < numBlocks; i++) {
    std::cout << "Block " << i << ": "
              << (memoryBlockStatus[i] ? "Free" : "Used") << std::endl;
  }
}
