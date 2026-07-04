#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>

class bigint
{
    private:
        std::string digits;

    public:
        bigint();
        bigint(unsigned int number);
        bigint(const bigint& source);

        std::string get_digits() const;

        bigint& operator=(const bigint& source);

        // Addition
        bigint  operator+(const bigint& other) const;
        bigint& operator+=(const bigint& other);

        // Incrémentation
        bigint& operator++();    // préfixe :  ++x
        bigint  operator++(int); // postfixe : x++

        // Décalage de chiffres par entier
        bigint  operator<<(unsigned int shift_amount) const;
        bigint  operator>>(unsigned int shift_amount) const;
        bigint& operator<<=(unsigned int shift_amount);
        bigint& operator>>=(unsigned int shift_amount);

        // Décalage de chiffres par bigint
        bigint  operator<<(const bigint& other) const;
        bigint  operator>>(const bigint& other) const;
        bigint& operator<<=(const bigint& other);
        bigint& operator>>=(const bigint& other);

        // Comparaisons
        bool operator==(const bigint& other) const;
        bool operator!=(const bigint& other) const;
        bool operator<(const bigint& other) const;
        bool operator>(const bigint& other) const;
        bool operator<=(const bigint& other) const;
        bool operator>=(const bigint& other) const;
};

std::ostream& operator<<(std::ostream& stream, const bigint& number);
