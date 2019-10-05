#include <math.h>

template <typename T>
class Vec3
{
public:
	
	T x, y, z;

	Vec3() : x(0), y(0), z(0) {};
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {};

	Vec3 operator +(Vec3 v) {
		return Vec3(x + v.x, y + v.y, z + v.z);
	};

	void Normalize() {
		double length = sqrt((x * x) + (y * y) + (z * z));
		x = x / length;
		y = y / length;
		z = z / length;
	};

	double distance_to(Vec3 v) {
		return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2) + pow(z - v.z, 2));
	};
};

