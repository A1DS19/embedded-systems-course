#include "oop.hpp"

#include <array>
#include <iostream>
#include <memory>

namespace {
constexpr float RECT_WIDTH = 10.0F;
constexpr float RECT_HEIGHT = 5.0F;
constexpr float CIRCLE_RADIUS = 7.0F;
constexpr float TRI_SIDE_A = 3.0F;
constexpr float TRI_SIDE_B = 4.0F;
constexpr float TRI_SIDE_C = 5.0F;
constexpr float SQUARE_SIDE = 6.0F;
constexpr float VEC_A_X = 3.0F;
constexpr float VEC_A_Y = 4.0F;
constexpr float VEC_B_X = 1.0F;
constexpr float VEC_B_Y = 2.0F;
constexpr float SCALAR_TWO = 2.0F;
} // namespace

void oop() {
    std::cout << "=== OOP Concepts Demo ===\n\n";

    // ========================================================================
    // POLYMORPHISM - Different types, same interface
    // ========================================================================
    std::cout << "1. POLYMORPHISM - Base pointer to derived objects:\n";

    // Store different shapes in base class pointers
    std::array<std::unique_ptr<Shape>, 4> shapes = {
        std::make_unique<Rectangle>(RECT_WIDTH, RECT_HEIGHT),
        std::make_unique<Circle>(CIRCLE_RADIUS),
        std::make_unique<Triangle>(TRI_SIDE_A, TRI_SIDE_B, TRI_SIDE_C),
        std::make_unique<Square>(SQUARE_SIDE)};

    // Same function call, different behavior (runtime polymorphism)
    for (const auto& shape : shapes) {
        shape->print(); // Calls correct derived class methods
    }

    // ========================================================================
    // ENCAPSULATION - Controlled access to data
    // ========================================================================
    std::cout << "\n2. ENCAPSULATION - Access through getters:\n";

    Rectangle rect(RECT_WIDTH, RECT_HEIGHT);
    std::cout << "Rectangle width: " << rect.width() << ", height: " << rect.height() << "\n";
    // rect.width_ = 100;  // ERROR: private member

    // ========================================================================
    // INHERITANCE - Code reuse and specialization
    // ========================================================================
    std::cout << "\n3. INHERITANCE - Square IS-A Rectangle:\n";

    Square square(SQUARE_SIDE);
    std::cout << "Square width: " << square.width() << ", height: " << square.height() << "\n";
    square.print(); // Inherited from Shape, uses overridden name()

    // ========================================================================
    // ABSTRACTION - Cannot instantiate abstract class
    // ========================================================================
    std::cout << "\n4. ABSTRACTION - Shape is abstract:\n";
    // Shape shape;  // ERROR: cannot instantiate abstract class
    std::cout << "Shape* ptr works, but Shape obj does not compile\n";

    // ========================================================================
    // VIRTUAL DESTRUCTOR - Proper cleanup through base pointer
    // ========================================================================
    std::cout << "\n5. VIRTUAL DESTRUCTOR - Correct destruction:\n";
    {
        std::unique_ptr<Shape> poly_shape = std::make_unique<Circle>(CIRCLE_RADIUS);
        std::cout << "Circle created via Shape pointer\n";
    } // Circle destructor called correctly due to virtual ~Shape()

    // ========================================================================
    // OPERATOR OVERLOADING - Custom operators for Vector2D
    // ========================================================================
    std::cout << "\n6. OPERATOR OVERLOADING:\n";

    Vector2D vec_a(VEC_A_X, VEC_A_Y);
    Vector2D vec_b(VEC_B_X, VEC_B_Y);

    // Arithmetic operators
    std::cout << "vec_a = " << vec_a << "\n";
    std::cout << "vec_b = " << vec_b << "\n";
    std::cout << "vec_a + vec_b = " << (vec_a + vec_b) << "\n";
    std::cout << "vec_a - vec_b = " << (vec_a - vec_b) << "\n";
    std::cout << "vec_a * 2 = " << (vec_a * SCALAR_TWO) << "\n";
    std::cout << "2 * vec_a = " << (SCALAR_TWO * vec_a) << "\n"; // Non-member operator
    std::cout << "-vec_a = " << (-vec_a) << "\n";

    // Compound assignment
    Vector2D vec_c = vec_a;
    vec_c += vec_b;
    std::cout << "vec_c (after += vec_b) = " << vec_c << "\n";

    // Comparison operators (compares by magnitude)
    std::cout << "vec_a magnitude = " << vec_a.magnitude() << "\n";
    std::cout << "vec_b magnitude = " << vec_b.magnitude() << "\n";
    std::cout << "vec_a > vec_b (by length)? " << (vec_a > vec_b ? "yes" : "no") << "\n";

    // Subscript operator
    std::cout << "vec_a[0] = " << vec_a[0] << ", vec_a[1] = " << vec_a[1] << "\n";

    // Equality
    Vector2D vec_d(VEC_A_X, VEC_A_Y);
    std::cout << "vec_a == vec_d? " << (vec_a == vec_d ? "yes" : "no") << "\n";

    std::cout << "\n=== Demo Complete ===\n";
}
