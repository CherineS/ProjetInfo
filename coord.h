#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED

class Coord
{
    public :
        Coord(double x, double y);
        Coord();

        void afficher() const;
        void saisir();

        double getX() const;
        double getY() const;

    private :
        double m_x;
        double m_y;
};

#endif // COORD_H_INCLUDED
