#include "chunk.hpp"

#include <stdexcept>

namespace world {
    Chunk::Chunk() : m_storage(Chunk::volume) {}
    Chunk::~Chunk() {}

    block::NID Chunk::get_block_at(glm::i32vec3 offset) {
        // if (offset.x < 0 || offset.x > size - 1 || offset.y < 0 || offset.y > size - 1 || offset.z < 0 || offset.z > size - 1)
        //     throw std::out_of_range("Block offset is out of chunk's range");
        
        return m_storage.get_block(util::coords_to_index<Chunk::size>(offset.x, offset.y, offset.z));
    }

    void Chunk::set_block_at(glm::i32vec3 offset, block::NID block_nid) {
        // if (offset.x < 0 || offset.x > size - 1 || offset.y < 0 || offset.y > size - 1 || offset.z < 0 || offset.z > size - 1)
        //     throw std::out_of_range("Block offset is out of chunk's range");
        
        uint index = util::coords_to_index<Chunk::size>(offset.x, offset.y, offset.z);

        if (block::get_block_data(block_nid)->m_top_transparent)
            m_light_map[index] = ~(u16)0; // set full light
        else
            m_light_map[index] = (u16)0; // set no light

        m_storage.set_block(index, block_nid);
    }
}
