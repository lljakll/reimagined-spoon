#include <iostream>

class Fraction {
private:
  int numerator, denominator;
public:
  Fraction() {}
  Fraction(int top, int bottom) {
    if (bottom == 0) {
      std::invalid_argument("The denominator can not be zero.");
    }
    this->numerator = top;
    this->denominator = bottom;
  }
  ~Fraction() {}

  // function finds the greatest common denominator
  int gcd(int a, int b) {
    if (b == 0) {
      return a;
    }
    return gcd(b, a%b);
  }

  // function reduces the numerator and denominator on the Fraction
  Fraction reduce() {
    int den = gcd(numerator, denominator);
    this->numerator /= den;
    this->denominator /= den;
    return *this;
  }

  // function finds a denominator that can be used when adding or subtracting Fractions
  int find_denominator(const Fraction& rhs) const {
    if (denominator != rhs.denominator) {
      // determine if they are factors of each other
      int div1, div2;
      div1 = denominator / rhs.denominator;
      div2 = rhs.denominator / denominator;
      if (rhs.denominator*div1 == denominator) {
        // if the rhs's denominator is factor of the lhs
        return denominator;
      }
      else if (denominator*div2 == rhs.denominator) {
        // if the lhs's denominator is factor of the rhs
        return rhs.denominator;
      }
      else {
        // if neither is a factor of the other
        return denominator * rhs.denominator;
      }
    }
    return denominator;
  }

  // Addition Operator
  Fraction operator+(const Fraction& rhs) const {
    int bottom, left, right;
    bottom = find_denominator(rhs);
    left = bottom / denominator*numerator;
    right = bottom / rhs.denominator*rhs.numerator;
    return Fraction(left + right, bottom);

  }
  Fraction& operator+=(const Fraction& rhs) {
    *this = *this + rhs;
    return *this;
  }

  // Subtraction Operator
  Fraction operator-(const Fraction& rhs) const {
    int bottom, left, right;
    bottom = find_denominator(rhs);
    left = bottom / denominator*numerator;
    right = bottom / rhs.denominator*rhs.numerator;
    return Fraction(left - right, bottom);

  }
  Fraction& operator-=(const Fraction& rhs) {
    *this = *this - rhs;
    return *this;
  }

  // Multiplication Operator
  Fraction operator*(const Fraction& rhs) const {
    return Fraction(numerator * rhs.numerator, denominator * rhs.denominator);
  }
  Fraction& operator*=(const Fraction& rhs) {
    *this = *this * rhs;
    return *this;
  }

  // Division Operator
  Fraction operator/(const Fraction& rhs) const {
    return Fraction(numerator * rhs.denominator, denominator * rhs.numerator);
  }
  Fraction& operator/=(const Fraction rhs) {
    *this = *this / rhs;
    return *this;
  }

  // Output operator
  friend std::ostream& operator<< (std::ostream& output, const Fraction rhs) {
    output << rhs.numerator << '/' << rhs.denominator;
    return output;
  }
  // Input operator
  friend std::istream &operator>>(std::istream &input, Fraction &rhs) {
    char temp;
    input >> rhs.numerator;
    input >> temp;
    input >> rhs.denominator;
    return input;
  }
};

int main() {
  char cont;
  do {
    // request two fractions
    Fraction fract1, fract2, fract3;
    std::cout << "Please enter two Fractions\nFraction 1: ";
    std::cin >> fract1;
    std::cout << "Fraction 2: ";
    std::cin >> fract2;
    std::cout << "You entered " << fract1 << " and " << fract2 << "\n\n";

    // demonstrate Fraction class operators
    // addition
    fract3 = fract1 + fract2;
    std::cout << fract1 << " + " << fract2 << " = " << fract3 << " = " << fract3.reduce() << std::endl;
    // subtraction
    fract3 = fract1 - fract2;
    std::cout << fract1 << " - " << fract2 << " = " << fract3 << " = " << fract3.reduce() << std::endl;
    fract3 = fract2 - fract1;
    std::cout << fract2 << " - " << fract1 << " = " << fract3 << " = " << fract3.reduce() << std::endl;
    // multiplication
    fract3 = fract1 * fract2;
    std::cout << fract1 << " * " << fract2 << " = " << fract3 << " = " << fract3.reduce() << std::endl;
    // division
    fract3 = fract1 / fract2;
    std::cout << fract1 << " / " << fract2 << " = " << fract3 << " = " << fract3.reduce() << std::endl;
    fract3 = fract2 / fract1;
    std::cout << fract2 << " / " << fract1 << " = " << fract3 << " = " << fract3.reduce() << std::endl;

    // ask to continue
    std::cout << "\nContinue? (y/n): ";
    std::cin >> cont;
  } while (cont == 'y');


}