#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <cstdlib>

#define MEMORY_POOL_SIZE 1024 * 1024  // 1 MB pool

class MemoryManager {
private:
    // Simulate a large block of memory
    char* pool;
    bool* freeBlocks;  // A simple free block tracker
    size_t blockSize;
    size_t numBlocks;

public:
    MemoryManager(size_t block_size, size_t num_blocks) 
        : blockSize(block_size), numBlocks(num_blocks) {
        pool = (char*)malloc(blockSize * numBlocks);  // Allocate the memory pool
        assert(pool && "Failed to allocate memory pool!");

        freeBlocks = new bool[numBlocks];  // Free block tracker
        std::memset(freeBlocks, true, sizeof(bool) * numBlocks);  // Initially, all blocks are free
    }

    ~MemoryManager() {
        free(pool);
        delete[] freeBlocks;
    }

    // Allocate memory block
    void* allocate() {
        for (size_t i = 0; i < numBlocks; i++) {
            if (freeBlocks[i]) {
                freeBlocks[i] = false;
                return pool + (i * blockSize);  // Return the pointer to the allocated memory
            }
        }

        std::cerr << "Out of memory! No free blocks available!" << std::endl;
        return nullptr;  // Return nullptr if no free block is available
    }

    // Deallocate memory block
    void deallocate(void* ptr) {
        size_t blockIndex = (static_cast<char*>(ptr) - pool) / blockSize;

        if (blockIndex < numBlocks) {
            freeBlocks[blockIndex] = true;
        } else {
            std::cerr << "Invalid memory deallocation!" << std::endl;
        }
    }

    // Print current status of memory
    void printStatus() {
        std::cout << "Memory Pool Status:\n";
        for (size_t i = 0; i < numBlocks; i++) {
            std::cout << "Block " << i << ": " << (freeBlocks[i] ? "Free" : "Occupied") << "\n";
        }
    }
};

int main() {
    // Initialize a memory manager with 64 blocks of size 16 bytes
    MemoryManager memoryManager(16, 64);

    // Allocate some memory
    void* ptr1 = memoryManager.allocate();
    void* ptr2 = memoryManager.allocate();
    void* ptr3 = memoryManager.allocate();

    memoryManager.printStatus();

    // Deallocate some memory
    memoryManager.deallocate(ptr2);

    memoryManager.printStatus();

    // Allocate more memory
    void* ptr4 = memoryManager.allocate();
    memoryManager.printStatus();

    // Forcefully deallocate an invalid block
    memoryManager.deallocate(reinterpret_cast<void*>(0xdeadbeef));

    // Simulate a memory overflow (dangerous, don't do this in production)
    char* overflow = (char*)ptr1;
    overflow[1024] = 'A';  // Access out of bounds! Dangerous!

    return 0;
}

