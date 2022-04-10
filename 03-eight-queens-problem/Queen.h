#pragma once

#include <cstddef>

class Queen
{
public:
    Queen(int id) { m_id = id; }

    int GetId() const { return m_id; }

private:
    int m_id;
};
