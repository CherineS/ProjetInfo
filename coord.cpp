#include "coord.h"
#include <iostream>

Coord::Coord(double x, double y)
    : m_x{x}, m_y{y}
{ }

Coord::Coord()
    : m_x{0}, m_y{0}
{ }

void Coord::afficher() const
{
    std::cout << "(" << m_x << ", " << m_y << ")";
}

void Coord::saisir()
{
    std::cout << "Veuillez saisir x et y SVP : ";
    std::cin >> m_x >> m_y;
}

double Coord::getX() const
{
    return m_x;
}

double Coord::getY() const
{
    return m_y;
}
