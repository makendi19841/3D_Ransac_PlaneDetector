#pragma once
#include<iostream>
#include "Point3.h";

class Plane3
{

public:
	double a, b, c, d;

// ---------------------------------------------------------------------------------------------------- //

public:

	inline Plane3()
	{
		a = b = c = d = 0.0;
	}

	inline Plane3(double a, double b, double c, double d) 
		: a(a), b(b), c(c), d(d) {}

	Plane3(const Point3 &p1, const Point3 &p2, const Point3 &p3)
	{
		// ... define two vectors
		Vector3 v1, v2, normV;
		v1.x = (p2.x - p1.x);
		v1.y = (p2.y - p1.y);
		v1.z = (p2.z - p1.z);

		v2.x = (p3.x - p1.x);
		v2.y = (p3.y - p1.y);
		v2.z = (p3.z - p1.z);
		
		// ... define normal vector
		normV = CrossProduct(v1, v2);

		// ... normalize norla vector
		normV.Normalize();

		// ... normal parameters
		a = normV.x;
		b = normV.y;
		c = normV.z;

		//std::cout << "normV.x: " << normV.x <<  "normV.y: " << normV.y << "normV.z: " << normV.z << std::endl;

		// ... distance to plane
		d = -(a * p1.x + b * p1.y + c * p1.z);

		//std::cout << "distance:" << d << std::endl;
	}

	Plane3(const Vector3 &normal, const Point3 &point)
	{
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -(a * point.x + b * point.y + c * point.z);
	}

	// Copy Constructor
	Plane3(const Plane3 &other)
	{
		a = other.a;
		b = other.b;
		c = other.c;
		d = other.d;
	}

// ---------------------------------------------------------------------------------------------------- //

	Plane3 & operator=(const Plane3 &p)
	{
		a = p.a;
		b = p.b;
		c = p.c;
		d = p.d;
		return *this;
	}

	inline Plane3 operator-() const
	{
		return Plane3(-a, -b, -c, -d);
	}

// ---------------------------------------------------------------------------------------------------- //

	double Distance3D(const Point3 &point)
	{
		return abs(a*point.x + b*point.y + c*point.z + d);
	}

	Vector3 Normal() const
	{
		return Vector3(a, b, c);
	}
	
};

// ---------------------------------------------------------------------------------------------------- //

// Writes Plane3 p to output stream os.
inline std::ostream & operator<<(std::ostream &os, const Plane3 &p)
{
	os << p.a << " " << p.b << " " << p.c << " " << p.d;
	return os;
}