#include "bigint.hpp"

// ─── Constructeurs / Destructeur ─────────────────────────────────────────────

bigint::bigint()
{
    this->digits = "0";
}

bigint::bigint(unsigned int number)
{
    std::stringstream stream;
    stream << number;
    this->digits = stream.str();
}

bigint::bigint(const bigint& source)
{
    *this = source;
}

bigint& bigint::operator=(const bigint& source)
{
    if (this == &source)
        return *this;
    this->digits = source.digits;
    return *this;
}

std::string bigint::get_digits() const
{
    return this->digits;
}

// ─── Fonctions internes ───────────────────────────────────────────────────────

static std::string reverse_string(const std::string& input)
{
    std::string reversed;
    int last_index = (int)input.length() - 1;

    for (int i = last_index; i >= 0; i--)
        reversed.push_back(input[i]);
    return reversed;
}

// Additionne deux grands nombres représentés comme chaînes de chiffres.
static std::string add_digit_strings(const std::string& left, const std::string& right)
{
    // On travaille du chiffre le moins significatif au plus significatif
    std::string reversed_left  = reverse_string(left);
    std::string reversed_right = reverse_string(right);

    // On complète la chaîne la plus courte avec des zéros
    while (reversed_left.length() < reversed_right.length())
        reversed_left.push_back('0');
    while (reversed_right.length() < reversed_left.length())
        reversed_right.push_back('0');

    std::string result;
    int carry = 0;

    for (size_t i = 0; i < reversed_left.length(); i++)
    {
        int digit_left   = reversed_left[i]  - '0';
        int digit_right  = reversed_right[i] - '0';
        int column_sum   = digit_left + digit_right + carry;

        if (column_sum > 9)
        {
            carry = column_sum / 10;
            result.push_back((column_sum % 10) + '0');
        }
        else
        {
            carry = 0;
            result.push_back(column_sum + '0');
        }
    }
    if (carry != 0)
        result.push_back(carry + '0');

    std::string final_sum = reverse_string(result);
    return final_sum;
}

static unsigned int convert_string_to_uint(const std::string& str)
{
    std::stringstream stream(str);
    unsigned int value;
    stream >> value;
    return value;
}

// ─── Opérateurs d'addition ───────────────────────────────────────────────────

bigint bigint::operator+(const bigint& other) const
{
    bigint result;
    result.digits = add_digit_strings(this->digits, other.digits);
    return result;
}

bigint& bigint::operator+=(const bigint& other)
{
    *this = *this + other;
    return *this;
}

// ─── Opérateurs d'incrémentation ─────────────────────────────────────────────

bigint& bigint::operator++()
{
    bigint one(1);
    *this = *this + one;
    return *this;
}

bigint bigint::operator++(int)
{
    bigint value_before = *this;
    bigint one(1);
    *this = *this + one;
    return value_before;
}

// ─── Décalage de chiffres par entier ─────────────────────────────────────────

bigint bigint::operator<<(unsigned int shift_amount) const
{
    bigint result = *this;
    for (unsigned int i = 0; i < shift_amount; i++)
        result.digits.push_back('0');
    return result;
}

bigint bigint::operator>>(unsigned int shift_amount) const
{
    bigint result = *this;
    size_t total = result.digits.length();

    if (shift_amount >= (unsigned int)total)
    {
        result.digits = "0";
    }
    else
    {
        size_t erase_start = total - shift_amount;
        result.digits.erase(erase_start, shift_amount);
    }
    return result;
}

bigint& bigint::operator<<=(unsigned int shift_amount)
{
    *this = *this << shift_amount;
    return *this;
}

bigint& bigint::operator>>=(unsigned int shift_amount)
{
    *this = *this >> shift_amount;
    return *this;
}

// ─── Décalage de chiffres par bigint ─────────────────────────────────────────

bigint bigint::operator<<(const bigint& other) const
{
    unsigned int shift_amount = convert_string_to_uint(other.digits);
    bigint result = *this << shift_amount;
    return result;
}

bigint bigint::operator>>(const bigint& other) const
{
    unsigned int shift_amount = convert_string_to_uint(other.digits);
    bigint result = *this >> shift_amount;
    return result;
}

bigint& bigint::operator<<=(const bigint& other)
{
    unsigned int shift_amount = convert_string_to_uint(other.digits);
    *this = *this << shift_amount;
    return *this;
}

bigint& bigint::operator>>=(const bigint& other)
{
    unsigned int shift_amount = convert_string_to_uint(other.digits);
    *this = *this >> shift_amount;
    return *this;
}

// ─── Opérateurs de comparaison ────────────────────────────────────────────────

bool bigint::operator==(const bigint& other) const
{
    bool are_equal = (this->digits == other.digits);
    return are_equal;
}

bool bigint::operator!=(const bigint& other) const
{
    bool are_equal = (*this == other);
    bool are_different;
    if (are_equal)
        are_different = false;
    else
        are_different = true;
    return are_different;
}

bool bigint::operator<(const bigint& other) const
{
    size_t my_length    = this->digits.length();
    size_t other_length = other.digits.length();

    // Un nombre avec moins de chiffres est toujours plus petit
    if (my_length != other_length)
    {
        bool shorter = (my_length < other_length);
        return shorter;
    }

    // Même longueur : la comparaison lexicographique fonctionne car les chiffres sont entre '0' et '9'
    bool is_lexicographically_less = (this->digits < other.digits);
    return is_lexicographically_less;
}

bool bigint::operator>(const bigint& other) const
{
    bool is_less   = (*this < other);
    bool is_equal  = (*this == other);
    bool not_less  = !is_less;
    bool not_equal = !is_equal;
    bool is_greater = (not_less && not_equal);
    return is_greater;
}

bool bigint::operator<=(const bigint& other) const
{
    bool is_less          = (*this < other);
    bool is_equal         = (*this == other);
    bool is_less_or_equal = (is_less || is_equal);
    return is_less_or_equal;
}

bool bigint::operator>=(const bigint& other) const
{
    bool is_greater          = (*this > other);
    bool is_equal            = (*this == other);
    bool is_greater_or_equal = (is_greater || is_equal);
    return is_greater_or_equal;
}

// ─── Affichage dans un flux ───────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& stream, const bigint& number)
{
    stream << number.get_digits();
    return stream;
}
