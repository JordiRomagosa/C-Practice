#include <math.h>

template <typename T>
class Vec3
{
public:
	
	T x, y, z;

	Vec3() : x(0), y(0), z(0) {};
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {};
	Vec3(const Vec3<T> & v) : x(v.x), y(v.y), z(v.z) {};
	virtual ~Vec3() {};

	Vec3<T> operator +(const Vec3<T> & v) const {
		return Vec3(x + v.x, y + v.y, z + v.z);
	};

	Vec3<T> normalize() const {
		double length = sqrt((x * x) + (y * y) + (z * z));
		T newx = x / length;
		T newy = y / length;
		T newz = z / length;

		return Vec3(newx, newy, newz);
	};

	double distance_to(const Vec3<T> & v) const {
		return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2) + pow(z - v.z, 2));
	};
};

