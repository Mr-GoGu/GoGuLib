
#pragma once

#include <random>

namespace GGL
{

class Randomizer
{
    public:
        Randomizer()
        {
            this->_seed = nullptr;
            UnsetSeed();
        }

        Randomizer(size_t seed)
        {
            SetSeed(seed);
        }

        ~Randomizer() = default;

        void UnsetSeed()
        {
            this->_gen.seed(this->_rd());
            this->_seed.reset();
        }

        void SetSeed(size_t seed)
        {
            if (this->_seed == nullptr) {
                this->_seed = std::make_unique<size_t>(seed);
            } else {
                *this->_seed = seed;
            }
            this->_gen.seed(*this->_seed);
        }

        size_t GetSeed() const
        {
            return *this->_seed;
        }

        template <typename T>
        T GetRandomInRange(T min, T max)
        {
            static_assert(std::is_integral<T>::value, "T must be an integral");

            if (min > max) {
                std::swap(min, max);
            }

            std::uniform_int_distribution<T> dist(min, max);
            return dist(this->_gen);
        }

        template <typename T>
        T GetRandom(T max)
        {
            static_assert(std::is_integral<T>::value, "T must be an integral");

            std::uniform_int_distribution<T> dist;
            return dist(this->_gen) % max;
        }

    private:
        std::mt19937_64 _gen;
        std::random_device _rd;
        std::unique_ptr<size_t> _seed;
};

} // namespace GGL
