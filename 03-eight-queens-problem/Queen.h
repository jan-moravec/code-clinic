#pragma once

#include <cstddef>

class Queen
{
public:
    Queen(std::size_t id) { m_id = id; }

    std::size_t GetId() const { return m_id; }

private:
    std::size_t m_id;
};
