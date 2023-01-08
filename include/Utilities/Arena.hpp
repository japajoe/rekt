#ifndef ARENA_HPP
#define ARENA_HPP

#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <new>
#include <type_traits>

class Arena
{
public:
    // The default chunk size is 256KB.
    static constexpr std::size_t kChunkSize = 256 * 1024;

    // The maximum alignment needed for any type.
    static constexpr std::size_t kMaxAlignment = alignof(std::max_align_t);

    // Deallocates all memory allocated by this arena.
    ~Arena()
    {
        // Deallocate all chunks.
        Chunk *chunk = chunk_list_;
        while (chunk != nullptr)
        {
            Chunk *next = chunk->next;
            std::free(chunk->data);
            std::free(chunk);
            chunk = next;
        }
    }

    // Allocates a new chunk of memory.
    template <typename T>
    T *Allocate()
    {
        // Allocate enough memory from the arena to hold an object of type T.
        void* ptr = Allocate(sizeof(T));

        // Use std::aligned_storage to create a type with the proper alignment for T.
        using AlignedStorage = typename std::aligned_storage<sizeof(T), kMaxAlignment>::type;

        // Cast the allocated memory to the aligned storage type.
        AlignedStorage* storage = static_cast<AlignedStorage*>(ptr);

        // Construct an object of type T in the aligned storage.
        new (storage) T();

        // Return a pointer to the constructed object.
        return reinterpret_cast<T*>(storage);
    }

    // Allocates a chunk of memory of size `size`.
    void *Allocate(std::size_t size)
    {
        // Round up `size` to the next multiple of 8 to ensure that the returned
        // memory is properly aligned for any type.
        size = (size + 7) & ~7;

        if (current_chunk_ == nullptr || current_position_ + size > current_chunk_->size)
        {
            // Allocate a new chunk if there is no current chunk or if there is not
            // enough space in the current chunk to satisfy the allocation request.
            AllocateChunk();
        }

        // Allocate memory from the current chunk.
        void *result = current_chunk_->data + current_position_;
        current_position_ += size;
        return result;
    }

    void Deallocate(void *ptr)
    {
        // Iterate through the linked list of chunks.
        Chunk *chunk = chunk_list_;
        while (chunk != nullptr)
        {
            if (ptr >= chunk->data && ptr < chunk->data + chunk->size)
            {
                // The block of memory being deallocated is in this chunk.
                std::size_t offset = static_cast<std::uint8_t *>(ptr) - chunk->data;
                if (offset + sizeof(void *) <= chunk->size)
                {
                    // Save the size of the block being deallocated in the first 4 bytes
                    // of the block.
                    std::size_t *size_ptr = static_cast<std::size_t *>(ptr);
                    *size_ptr = *size_ptr - offset - sizeof(void *);

                    // Set the pointer in the previous chunk to the next chunk.
                    *static_cast<Chunk **>(ptr) = chunk->next;
                }
                return;
            }
            chunk = chunk->next;
        }
        // The block of memory being deallocated was not found.
        throw std::invalid_argument("ptr");
    }

    void Reset()
    {
        // Deallocate all chunks except the first one.
        Chunk *chunk = chunk_list_->next;
        while (chunk != nullptr)
        {
            Chunk *next = chunk->next;
            std::free(chunk->data);
            std::free(chunk);
            chunk = next;
        }

        // Reset the first chunk.
        chunk_list_->next = nullptr;
        current_chunk_ = chunk_list_;
        current_position_ = 0;
    }

private:
    // A linked list of chunks.
    struct Chunk
    {
        std::uint8_t *data;
        std::size_t size;
        Chunk *next;
    };
    Chunk *chunk_list_ = nullptr;

    // The current chunk being allocated from.
    Chunk *current_chunk_ = nullptr;

    // The current position in the current chunk being allocated from.
    std::size_t current_position_ = 0;

    // Allocates a new chunk of memory.
    void AllocateChunk()
    {
        // Allocate a new chunk of memory.
        std::uint8_t *data = static_cast<std::uint8_t *>(std::malloc(kChunkSize));
        std::size_t size = kChunkSize;
        if (data == nullptr)
        {
            // If the allocation failed, try allocating a smaller chunk.
            size = 1024;
            data = static_cast<std::uint8_t *>(std::malloc(size));
        }
        if (data == nullptr)
        {
            throw std::bad_alloc();
        }

        // Create a new chunk and add it to the front of the linked list.
        Chunk *chunk = static_cast<Chunk *>(std::malloc(sizeof(Chunk)));
        chunk->data = data;
        chunk->size = size;
        chunk->next = chunk_list_;
        chunk_list_ = chunk;

        // Set the current chunk to the new chunk.
        current_chunk_ = chunk;
        current_position_ = 0;
    }
};

#endif