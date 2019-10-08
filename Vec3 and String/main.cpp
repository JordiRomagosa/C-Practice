#include <iostream>
#include "vec3.h"
#include "cstring.h"

int main()
{
	Vec3<double> a = Vec3<double>();
	Vec3<double> b(1, 0, 1);
	Vec3<double> c(b);
	Vec3<double> d = b + c;

	std::cout << "a: " << a.x << ", " << a.y << ", " << a.z << "\n";
	std::cout << "b: " << b.x << ", " << b.y << ", " << b.z << "\n";
	std::cout << "c: " << c.x << ", " << c.y << ", " << c.z << "\n";
	std::cout << "d: " << d.x << ", " << d.y << ", " << d.z << "\n";

	Vec3<double> normalized = d.normalize();
	std::cout << "\n" << "Normalized d: " << normalized.x << ", " << normalized.y << ", " << normalized.z << "\n";

	std::cout << "\n" << "Distance between d and b: " << d.distance_to(b) << "\n\n";

	String e("hello");
	String f(e);
	String g = e + f;
	String h = " world";

	std::cout << "\n" << "String e: " << e;
	std::cout << "\n" << "String f: " << f;
	std::cout << "\n" << "String g: " << g;
	std::cout << "\n" << "String h: " << h;

	if (g == "hellohello")
		std::cout << "\n\n" << "String comparison to literal is correct" << "\n";
	else
		std::cout << "\n\n" << "String comparison to literal isnt correct" << "\n";

	if (e == f)
		std::cout << "String comparison to string is correct" << "\n";
	else
		std::cout << "String comparison to string isnt correct" << "\n";

	std::cout << "\n" << "Length of g: " << g.length();

	g.clear();
	std::cout << "\n" << "Length of g after clear: " << g.length();

	while (1) {};
}

