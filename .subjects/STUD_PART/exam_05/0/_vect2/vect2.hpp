#pragma once

#include <iostream>

class vect2
{
    private:
        int x;
        int y;

    public:
        vect2();
        vect2(int x_value, int y_value);
        vect2(const vect2& source);
        ~vect2();

        vect2& operator=(const vect2& source);

        // Accès aux composantes
        int  operator[](int index) const; // lecture seule
        int& operator[](int index);       // lecture-écriture

        // Plus / négation unaire
        vect2 operator+() const;
        vect2 operator-() const;

        // Multiplication par un scalaire
        vect2  operator*(int scalar) const;
        vect2& operator*=(int scalar);

        // Affectation composée
        vect2& operator+=(const vect2& other);
        vect2& operator-=(const vect2& other);
        vect2& operator*=(const vect2& other);

        // Arithmétique binaire
        vect2 operator+(const vect2& other) const;
        vect2 operator-(const vect2& other) const;
        vect2 operator*(const vect2& other) const;

        // Incrémentation / Décrémentation
        vect2& operator++();    // préfixe  ++v
        vect2  operator++(int); // postfixe v++
        vect2& operator--();    // préfixe  --v
        vect2  operator--(int); // postfixe v--

        // Comparaison
        bool operator==(const vect2& other) const;
        bool operator!=(const vect2& other) const;
};

// Permet d'écrire : 3 * vec  (scalaire à gauche)
vect2 operator*(int scalar, const vect2& vec);

std::ostream& operator<<(std::ostream& stream, const vect2& vec);
