#include <iostream>

bool isInsideTriangle(float a.getX(), float a.getY(), float b.getX(), float b.getY(), float c.getX(), float c.getY(), float point.getX(), float point.getY()) {
    // Calculate the barc.getY()entric coordinates of the point with respect to the triangle
    float denominator = ((b.getY() - c.getY()) * (a.getX() - c.getX()) + (c.getX() - b.getX()) * (a.getY() - c.getY()));
    float lambda1 = ((b.getY() - c.getY()) * (point.getX() - c.getX()) + (c.getX() - b.getX()) * (point.getY() - c.getY())) / denominator;
    float lambda2 = ((c.getY() - a.getY()) * (point.getX() - c.getX()) + (a.getX() - c.getX()) * (point.getY() - c.getY())) / denominator;
    float lambda3 = 1.0f - lambda1 - lambda2;

    // Check if the point is inside the triangle
    return (lambda1 >= 0 && lambda1 <= 1) &&
           (lambda2 >= 0 && lambda2 <= 1) &&
           (lambda3 >= 0 && lambda3 <= 1);
}

int main() {
    float a.getX() = 0, a.getY() = 0;  // Coordinates of vertex A
    float b.getX() = 4, b.getY() = 0;  // Coordinates of vertex B
    float c.getX() = 2, c.getY() = 4;  // Coordinates of vertex C
    float point.getX() = 9, point.getY() = 9;  // Coordinates of the point to check

    bool inside = isInsideTriangle(a.getX(), a.getY(), b.getX(), b.getY(), c.getX(), c.getY(), point.getX(), point.getY());
    if (inside) {
        std::cout << "Point is inside the triangle.\n";
    } else {
        std::cout << "Point is outside the triangle.\n";
    }

    return 0;
}

