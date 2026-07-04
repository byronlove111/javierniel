#include "vect2.hpp"

// ─── Constructeurs / Destructeur ─────────────────────────────────────────────

vect2::vect2()
{
    this->x = 0;
    this->y = 0;
}

vect2::vect2(int x_value, int y_value)
{
    this->x = x_value;
    this->y = y_value;
}

vect2::vect2(const vect2& source)
{
    *this = source;
}

vect2::~vect2()
{
}

vect2& vect2::operator=(const vect2& source)
{
    if (this != &source)
    {
        this->x = source.x;
        this->y = source.y;
    }
    return *this;
}

// ─── Accès aux composantes ────────────────────────────────────────────────────

// Lecture seule : retourne la valeur par copie
int vect2::operator[](int index) const
{
    if (index == 0)
        return this->x;
    return this->y;
}

// Lecture-écriture : retourne une référence pour pouvoir assigner dans la composante
int& vect2::operator[](int index)
{
    if (index == 0)
        return this->x;
    return this->y;
}

// ─── Plus / Négation unaire ───────────────────────────────────────────────────

// Retourne une copie du vecteur sans modification (opérateur unaire +)
vect2 vect2::operator+() const
{
    vect2 copy = *this;
    return copy;
}

vect2 vect2::operator-() const
{
    vect2 negated;
    negated.x = -(this->x);
    negated.y = -(this->y);
    return negated;
}

// ─── Multiplication par un scalaire ──────────────────────────────────────────

vect2 vect2::operator*(int scalar) const
{
    vect2 result;
    result.x = this->x * scalar;
    result.y = this->y * scalar;
    return result;
}

vect2& vect2::operator*=(int scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

// ─── Affectation composée ─────────────────────────────────────────────────────

vect2& vect2::operator+=(const vect2& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

vect2& vect2::operator-=(const vect2& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

vect2& vect2::operator*=(const vect2& other)
{
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

// ─── Arithmétique binaire ─────────────────────────────────────────────────────

vect2 vect2::operator+(const vect2& other) const
{
    vect2 result = *this;
    result += other;
    return result;
}

vect2 vect2::operator-(const vect2& other) const
{
    vect2 result = *this;
    result -= other;
    return result;
}

vect2 vect2::operator*(const vect2& other) const
{
    vect2 result = *this;
    result *= other;
    return result;
}

// ─── Incrémentation / Décrémentation ─────────────────────────────────────────

vect2& vect2::operator++()
{
    this->x += 1;
    this->y += 1;
    return *this;
}

vect2 vect2::operator++(int)
{
    vect2 value_before = *this;
    ++(*this);
    return value_before;
}

vect2& vect2::operator--()
{
    this->x -= 1;
    this->y -= 1;
    return *this;
}

vect2 vect2::operator--(int)
{
    vect2 value_before = *this;
    --(*this);
    return value_before;
}

// ─── Opérateurs de comparaison ────────────────────────────────────────────────

bool vect2::operator==(const vect2& other) const
{
    bool x_equal    = (this->x == other.x);
    bool y_equal    = (this->y == other.y);
    bool both_equal = (x_equal && y_equal);
    return both_equal;
}

bool vect2::operator!=(const vect2& other) const
{
    bool are_equal = (*this == other);
    bool are_different;
    if (are_equal)
        are_different = false;
    else
        are_different = true;
    return are_different;
}

// ─── Opérateurs non-membres ───────────────────────────────────────────────────

// Permet d'écrire : 3 * vec  (scalaire à gauche)
vect2 operator*(int scalar, const vect2& vec)
{
    vect2 result = vec * scalar;
    return result;
}

std::ostream& operator<<(std::ostream& stream, const vect2& vec)
{
    stream << "{" << vec[0] << ", " << vec[1] << "}";
    return stream;
}
