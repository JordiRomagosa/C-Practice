#include <iostream>
#include "vec3.h"

int main()
{
	Vec3<int> a = Vec3<int>();
	Vec3<int> b(1, 0, 1);
	Vec3<int> c(b);
	Vec3<int> d = b + c;

	std::cout << "a: " << a.x << ", " << a.y << ", " << a.z << "\n";
	std::cout << "b: " << b.x << ", " << b.y << ", " << b.z << "\n";
	std::cout << "c: " << c.x << ", " << c.y << ", " << c.z << "\n";
	std::cout << "d: " << d.x << ", " << d.y << ", " << d.z << "\n";

	d.Normalize();
	std::cout << "\n" << "Normalized d: " << d.x << ", " << d.y << ", " << d.z << "\n";

	std::cout << "\n" << "Distance between d and b: " << d.distance_to(b);

	while (1) {};
}