#include "geom\Plane3.h"
#include "io\TXTReader.h"
#include "io\TXTWriter.h"

#include <algorithm> // std::shuffle
#include <iostream>
#include <random>  // std::default_random_engine
#include <chrono>  // std::chrono::system_clock

Point3 Min_XYZ(const std::vector<Point3 *> &points)
{
	Point3 result = Point3(std::numeric_limits<double>::max(),
		std::numeric_limits<double>::max(),
		std::numeric_limits<double>::max());

	for (const Point3 &p : points)
	{
		if (p.x < result.x)
			result.x = p.x;
		if (p.y < result.y)
			result.y = p.y;
		if (p.z < result.z)
			result.z = p.z;
	}

	return result;
}

int main()
{
	std::cout << std::fixed;

	std::vector<Point3 *> points_building = TXTReader::ReadPointXYZ("data\\input\\building.xyz");

	const Point3 OFFSET = Min_XYZ(points_building);
	for (Point3 *p : points_building)
	{
		p->x -= OFFSET.x;
		p->y -= OFFSET.y;
	}



	//--------------------------------------Ransac Process Start Here-----------------------------------------------//	
	std::vector<std::vector<Point3 *>> result ;
	bool Stop = false;
	while (Stop == false) {
     
		//... number of iteration
		int N = 100;
		std::vector<Point3*> temp_plane1;
		for (int i = 0; i < N; i++) {

			//...
			std::vector<Point3*> temp_plane2;

			// ... shuffle (mixed up) building points
			std::shuffle(points_building.begin(), points_building.end(), std::default_random_engine{});

			// ... pick up the first three indexes
			Point3* p1, p2, p3;
			p1 = points_building[0];
			p2 = points_building[1];
			p3 = points_building[2];

			// ... plane generation
			Plane3 gen_plane = Plane3(p1, p2, p3);

			// ...check points close to the plane
			for (Point3 *p : points_building) {
				double dist = gen_plane.Distance3D(p);

				if ((dist <= 0.15) && (p->used == false)) {

					//result.back().push_back(p);
					temp_plane2.push_back(p);

				}
			}

			if (temp_plane2.size() > temp_plane1.size()) {

				temp_plane1 = temp_plane2;
			}
			std::cout << "temp_plane2_size: " << temp_plane2.size() << std::endl;
		}

		if (temp_plane1.size() > 75) {
			//... push back temp_plane1 into result
			result.push_back(temp_plane1);

			//...set flag p.isUsed = true
			for (Point3*p : temp_plane1) {

				p->used = true;
			}
		}
		else {

			Stop = true;
		}
		
 }

	// all consensus set: task3
	for (std::vector<Point3 *> consensus_set : result)
	{
	for (Point3 *p : consensus_set)
	{
	p->x += OFFSET.x;
	p->y += OFFSET.y;
	}
	}

	 // all consensus set: task3
	for (std::vector<Point3 *> consensus_set : result)
	{
		for (Point3 *p : consensus_set)
		{
			p->x += OFFSET.x;
			p->y += OFFSET.y;
		}
	}

	// task 3
	for (unsigned int i = 0; i < result.size(); i++)
	{
	TXTWriter::WritePointXYZ("data\\output\\result_" + std::to_string(i) + ".xyz", result[i]);
	}

	std::system("PAUSE");
	return 0;
}