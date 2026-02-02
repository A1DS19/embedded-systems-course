#pragma once

#include <cmath>
#include <compare>
#include <cstddef>
#include <iostream>
#include <numbers>
#include <string>

namespace {
constexpr float HALF_DIVISOR = 2.0F;
} // namespace

// ============================================================================
// 4. OPERATOR OVERLOADING - Custom operators for user-defined types
// ============================================================================
// WHAT: Allows using operators (+, -, *, ==, <<, etc.) with your own classes
// WHY:  Makes code more intuitive: vec1 + vec2 instead of vec1.add(vec2)
// WHEN: When operators have natural meaning for your type (math types, iterators)
//
// TWO WAYS TO OVERLOAD:
//   1. Member function:   Vector2D operator+(const Vector2D& other) const;
//   2. Non-member (friend): friend Vector2D operator+(const Vector2D& a, const Vector2D& b);
//
// RULE OF THUMB:
//   - Arithmetic (+, -, *, /) -> can be member or non-member
//   - Comparison (==, <, <=>) -> prefer non-member or use = default
//   - Stream (<<, >>) -> MUST be non-member (friend)
//   - Assignment (=, +=, -=) -> MUST be member
// ============================================================================

class Vector2D {
public:
    float x;
    float y;

    // Constructors
    constexpr Vector2D() : x(0.0F), y(0.0F) {}
    constexpr Vector2D(const float x_val, const float y_val) : x(x_val), y(y_val) {}

    // ========================================================================
    // ARITHMETIC OPERATORS (member functions)
    // ========================================================================

    // operator+ : Addition
    // WHAT: Creates new vector from sum of two vectors
    // USAGE: Vector2D result = vec1 + vec2;
    // WHY CONST: Doesn't modify either operand, returns new object
    [[nodiscard]] constexpr Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // operator- : Subtraction
    // WHAT: Creates new vector from difference of two vectors
    // USAGE: Vector2D result = vec1 - vec2;
    [[nodiscard]] constexpr Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // operator* : Scalar multiplication
    // WHAT: Scales vector by a number
    // USAGE: Vector2D result = vec * 2.0F;
    [[nodiscard]] constexpr Vector2D operator*(const float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // operator/ : Scalar division
    // WHAT: Divides vector by a number
    // USAGE: Vector2D result = vec / 2.0F;
    [[nodiscard]] constexpr Vector2D operator/(const float scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    // Unary operator- : Negation
    // WHAT: Returns vector pointing in opposite direction
    // USAGE: Vector2D opposite = -vec;
    [[nodiscard]] constexpr Vector2D operator-() const { return Vector2D(-x, -y); }

    // ========================================================================
    // COMPOUND ASSIGNMENT OPERATORS (must be members, modify this)
    // ========================================================================

    // operator+= : Add and assign
    // WHAT: Adds other vector to this one IN PLACE
    // USAGE: vec1 += vec2;  // vec1 is modified
    // RETURNS: Reference to *this for chaining: (a += b) += c;
    constexpr Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // operator-= : Subtract and assign
    // WHAT: Subtracts other vector from this one IN PLACE
    // USAGE: vec1 -= vec2;
    constexpr Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // operator*= : Multiply and assign
    // WHAT: Scales this vector IN PLACE
    // USAGE: vec *= 2.0F;
    constexpr Vector2D& operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // ========================================================================
    // COMPARISON OPERATORS (C++20 spaceship operator)
    // ========================================================================

    // operator== : Equality comparison
    // WHAT: Checks if two vectors are equal
    // USAGE: if (vec1 == vec2) { ... }
    // = default: Compiler generates member-wise comparison
    [[nodiscard]] constexpr bool operator==(const Vector2D& other) const = default;

    // operator<=> : Three-way comparison (spaceship operator, C++20)
    // WHAT: Compares by magnitude (length) for ordering
    // USAGE: if (vec1 < vec2) means vec1 is shorter than vec2
    // RETURNS: std::partial_ordering because floats can be NaN
    // NOTE: This auto-generates <, >, <=, >= operators!
    [[nodiscard]] std::partial_ordering operator<=>(const Vector2D& other) const {
        return magnitude() <=> other.magnitude();
    }

    // ========================================================================
    // SUBSCRIPT OPERATOR (array-like access)
    // ========================================================================

    // operator[] : Index access
    // WHAT: Access x (index 0) or y (index 1) by index
    // USAGE: float val = vec[0];  // gets x
    // TWO VERSIONS: const and non-const for read and write access
    [[nodiscard]] constexpr float& operator[](const std::size_t index) {
        return (index == 0) ? x : y;
    }
    [[nodiscard]] constexpr float operator[](const std::size_t index) const {
        return (index == 0) ? x : y;
    }

    // ========================================================================
    // UTILITY METHODS
    // ========================================================================

    [[nodiscard]] float magnitude() const { return std::sqrt(x * x + y * y); }

    [[nodiscard]] float dot(const Vector2D& other) const { return x * other.x + y * other.y; }

    [[nodiscard]] Vector2D normalized() const {
        float mag = magnitude();
        return (mag > 0.0F) ? (*this / mag) : Vector2D();
    }
};

// ============================================================================
// NON-MEMBER OPERATORS (friend functions)
// ============================================================================

// operator* : Scalar * Vector (reversed order)
// WHAT: Allows writing 2.0F * vec instead of only vec * 2.0F
// WHY NON-MEMBER: Left operand is float, not Vector2D
// USAGE: Vector2D result = 2.0F * vec;
[[nodiscard]] inline constexpr Vector2D operator*(const float scalar, const Vector2D& vec) {
    return vec * scalar;
}

// operator<< : Stream insertion
// WHAT: Enables printing with std::cout
// WHY NON-MEMBER: Left operand is std::ostream, not Vector2D
// WHY FRIEND: Needs access to private members (x, y are public here, but good practice)
// USAGE: std::cout << vec << std::endl;
inline std::ostream& operator<<(std::ostream& out, const Vector2D& vec) {
    out << "(" << vec.x << ", " << vec.y << ")";
    return out; // Return stream for chaining: cout << v1 << v2;
}

// ============================================================================
// 1. ABSTRACTION - Abstract base class (interface)
// ============================================================================
class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default; // Virtual destructor for proper cleanup

    // Pure virtual functions - derived classes MUST implement
    [[nodiscard]] virtual float area() const = 0;
    [[nodiscard]] virtual float perimeter() const = 0;
    [[nodiscard]] virtual std::string name() const = 0;

    // Non-virtual function - same for all shapes
    void print() const {
        std::cout << name() << " - Area: " << area() << ", Perimeter: " << perimeter() << "\n";
    }

    // ========================================================================
    // RULE OF FIVE - Delete copy/move for polymorphic base class
    // ========================================================================
    // WHY: Prevents "object slicing" - a bug where derived class data is lost
    //      when copying/moving through a base class type.
    //
    // EXAMPLE OF THE BUG (if not deleted):
    //      Circle circle(5.0F);      // Circle has radius_ = 5.0
    //      Shape shape = circle;     // SLICING: only Shape part copied
    //                                // Circle's radius_ is lost!
    //
    // WHEN TO USE = delete:
    //   - Polymorphic base classes (classes with virtual functions)
    //   - Classes managing unique resources (files, sockets, hardware)
    //   - Singletons or classes that should never be copied
    //
    // SAFE ALTERNATIVES (use these instead):
    //   - Pointers:    std::unique_ptr<Shape> s = std::make_unique<Circle>(5.0F);
    //   - References:  Shape& ref = circle;
    // ========================================================================

    // Copy constructor: Shape s2(s1) or Shape s2 = s1
    // WHAT: Creates new object as copy of existing object
    // WHY DELETE: Would slice off derived class data (Circle -> Shape loses radius)
    Shape(const Shape&) = delete;

    // Copy assignment: s2 = s1
    // WHAT: Replaces existing object's data with copy of another
    // WHY DELETE: Same slicing problem as copy constructor
    Shape& operator=(const Shape&) = delete;

    // Move constructor: Shape s2(std::move(s1))
    // WHAT: Creates new object by "stealing" resources from temporary/moved object
    // WHY DELETE: Slicing still occurs even when moving
    Shape(Shape&&) = delete;

    // Move assignment: s2 = std::move(s1)
    // WHAT: Replaces existing object by "stealing" from another
    // WHY DELETE: Same slicing problem as move constructor
    Shape& operator=(Shape&&) = delete;
};

// ============================================================================
// 2. INHERITANCE & ENCAPSULATION - Derived classes
// ============================================================================
class Rectangle : public Shape {
public:
    Rectangle(const float width, const float height) : width_(width), height_(height) {}

    // Override virtual functions (POLYMORPHISM)
    [[nodiscard]] float area() const override { return width_ * height_; }
    [[nodiscard]] float perimeter() const override { return HALF_DIVISOR * (width_ + height_); }
    [[nodiscard]] std::string name() const override { return "Rectangle"; }

    // Encapsulation - getters
    [[nodiscard]] float width() const { return width_; }
    [[nodiscard]] float height() const { return height_; }

private:
    float width_;
    float height_;
};

class Circle : public Shape {
public:
    explicit Circle(const float radius) : radius_(radius) {}

    [[nodiscard]] float area() const override {
        return std::numbers::pi_v<float> * radius_ * radius_;
    }
    [[nodiscard]] float perimeter() const override {
        return HALF_DIVISOR * std::numbers::pi_v<float> * radius_;
    }
    [[nodiscard]] std::string name() const override { return "Circle"; }

    [[nodiscard]] float radius() const { return radius_; }

private:
    float radius_;
};

class Triangle : public Shape {
public:
    Triangle(const float side_a, const float side_b, const float side_c)
        : side_a_(side_a), side_b_(side_b), side_c_(side_c) {}

    [[nodiscard]] float area() const override {
        // Heron's formula
        float semi = perimeter() / HALF_DIVISOR;
        return std::sqrt(semi * (semi - side_a_) * (semi - side_b_) * (semi - side_c_));
    }
    [[nodiscard]] float perimeter() const override { return side_a_ + side_b_ + side_c_; }
    [[nodiscard]] std::string name() const override { return "Triangle"; }

private:
    float side_a_;
    float side_b_;
    float side_c_;
};

// ============================================================================
// 3. INHERITANCE HIERARCHY - Multi-level inheritance
// ============================================================================
class Square : public Rectangle {
public:
    explicit Square(const float side) : Rectangle(side, side) {}

    [[nodiscard]] std::string name() const override { return "Square"; }
};

void oop();
