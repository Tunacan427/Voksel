#pragma once

#include <random>
#include <unordered_map>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <FastNoise/FastNoise.h>

#include "chunk.hpp"

namespace world {
    class World {
        u64 m_seed;
        std::mt19937 m_world_rng;

        FastNoise::SmartNode<FastNoise::Simplex> m_ridged_simplex_noise;
        FastNoise::SmartNode<FastNoise::FractalRidged> m_ridged_noise;
        FastNoise::SmartNode<FastNoise::Simplex> m_simplex_noise;
        FastNoise::SmartNode<FastNoise::FractalFBm> m_fractal_noise;
        FastNoise::SmartNode<FastNoise::MaxSmooth> m_max_smooth;

        FastNoise::SmartNode<> m_cave_noise;
        
        std::unordered_map<glm::i32vec3, std::shared_ptr<Chunk>> m_chunks;

        std::shared_ptr<Chunk> generate_chunk(glm::i32vec3 chunk_pos);
        void decorate_chunk(glm::i32vec3 chunk_pos);
        
    public:
        World();
        ~World();

        std::shared_ptr<Chunk> get_chunk(glm::i32vec3 chunk_pos);
        std::shared_ptr<Chunk> get_or_generate_chunk(glm::i32vec3 chunk_pos);
        block::NID get_block_at(glm::i32vec3 pos);
        void set_block_at(glm::i32vec3 pos, block::NID block_nid);

        struct RayCastResult {
            bool hit;
            glm::i32vec3 block_pos;
            glm::i32vec3 block_normal;
        };

        // Casts a continuous ray through the world using the DDA method (max distance 32 blocks)
        RayCastResult cast_ray(glm::vec3 start_pos, glm::vec3 end_pos);
        
        bool is_position_valid(glm::vec3 pos, glm::vec3 min_bounds, glm::vec3 max_bounds);
    };
}
