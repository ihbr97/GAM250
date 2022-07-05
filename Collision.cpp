/*!
@file    Collision.cpp
@author  irfanhidayatb.r@digipen.edu
@date    13/9/2020


This file implements functionality useful and necessary for collision.

*/

#include "Collision.h"
#include "../Math/MathLibrary.h"
namespace Collision {

	bool CollisionIntersection_RectRect(AABB& aabb1, const Vec2& vel1,
		AABB& aabb2, const Vec2& vel2)
	{
		if (aabb1.min.x > aabb2.max.x || aabb2.min.x > aabb1.max.x ||
			aabb1.max.y < aabb2.min.y || aabb2.max.y < aabb1.min.y)
			return false;
		
		// step 2
		// finding the velocity
		float DiffVelocityX = vel2.getx() - vel1.getx();
		float DiffVelocityY = vel2.gety() - vel1.gety();
		Vec2 Vb = { DiffVelocityX, DiffVelocityY };

		if (Vb.x == 0 && Vb.y == 0) return 0;
		float dt = PhysicsEngine::fixedDT;
		float xtFirst = 0;
		float xtLast = dt;
		float ytFirst = 0;
		float ytLast = dt;
		float biggerFirst = 0;
		float smallerLast = 0;

		if (Vb.x < 0)//left
		{
			if (aabb1.min.x > aabb2.max.x) return 0;
			else if (aabb1.max.x < aabb2.min.x)
			{
				if ((aabb1.max.x - aabb2.min.x) / Vb.x > xtFirst)
					xtFirst = (aabb1.max.x - aabb2.min.x) / Vb.x;
			}
			else if (aabb1.min.x < aabb2.max.x)
			{
				if ((aabb1.min.x - aabb2.max.x) / Vb.x < xtLast)
					xtLast = (aabb1.min.x - aabb2.max.x) / Vb.x;
			}

		}
		else if (Vb.x > 0)//right
		{
			if (aabb1.max.x < aabb2.min.x) return 0;
			else if (aabb1.min.x > aabb2.max.x)
			{
				if ((aabb1.min.x - aabb2.max.x) / Vb.x > xtFirst)
					xtFirst = (aabb1.min.x - aabb2.max.x) / Vb.x;
			}
			else if (aabb1.max.x > aabb2.min.x)
			{
				if ((aabb1.max.x - aabb2.min.x) / Vb.x < xtLast)
					xtLast = (aabb1.max.x - aabb2.min.x) / Vb.x;
			}
		}

		if (Vb.y < 0)//top
		{
			if (aabb1.min.y > aabb2.max.y) return 0;

			else if (aabb1.max.y < aabb2.min.y)
			{
				if ((aabb1.max.y - aabb2.min.y) / Vb.y > ytFirst)
					ytFirst = (aabb1.max.y - aabb2.min.y) / Vb.y;
			}
			else if (aabb1.min.y < aabb2.max.y)
			{
				if ((aabb1.min.y - aabb2.max.y) / Vb.y < ytLast)
					ytLast = (aabb1.min.y - aabb2.max.y) / Vb.y;
			}
		}
		else if (Vb.y > 0)//bot
		{
			if (aabb1.max.y < aabb2.min.y) return 0;
			else if (aabb1.min.y > aabb2.max.y)
			{
				if ((aabb1.min.y - aabb2.max.y) / Vb.y > ytFirst)
					ytFirst = (aabb1.min.y - aabb2.max.y) / Vb.y;
			}
			else if (aabb1.max.y > aabb2.min.y)
			{
				if ((aabb1.max.y - aabb2.min.y) / Vb.y < ytLast)
					ytLast = (aabb1.max.y - aabb2.min.y) / Vb.y;
			}
		}

		if (xtFirst > ytFirst)
		{
			biggerFirst = xtFirst;
		}
		else
		{
			biggerFirst = ytFirst;
		}
		if (xtLast < ytLast)
		{
			smallerLast = xtLast;
		}
		else
		{
			smallerLast = ytLast;
		}

		if (biggerFirst > smallerLast) return 0;
		// step 5
		////check direction of collision before returning true

		float left = 1000.0f;
		float right = 1000.0f;
		float up = 1000.0f;
		float down = 1000.0f;
		bool intersecting = false;

		//updated as of 11.10.20
		//all references is with regards to aabb2 aka left would refer to aabb2 being hit on the left
		//aabb1 colliding left of aabb2
		if ((aabb2.min.x > aabb1.min.x) && (aabb2.max.x > aabb1.max.x)) {
			left = abs(aabb1.max.x - aabb2.min.x);
			intersecting = true;
		}
		//aabb1 colliding right of aabb2
		if ((aabb2.min.x < aabb1.min.x) && (aabb2.max.x < aabb1.max.x)) {
			right = abs(aabb2.max.x - aabb1.min.x);
			intersecting = true;
		}
		//aabb1 colliding below aabb2
		if ((aabb2.min.y > aabb1.min.y) && (aabb2.max.y > aabb1.max.y)) {
			down = abs(aabb1.max.y - aabb2.min.y);
			intersecting = true;
		}
		//aabb1 colliding on top of aabb2
		if ((aabb2.min.y < aabb1.min.y) && (aabb2.max.y < aabb1.max.y)) {
			up = abs(aabb2.max.y - aabb1.min.y);
			intersecting = true;
		}

		if (intersecting) {
			if (left < right && left < down && left < up) {
				aabb1.direction = dir::RIGHT;
				aabb2.direction = dir::LEFT;
			}
			else if (right < left && right < down && right < up) {
				aabb1.direction = dir::LEFT;
				aabb2.direction = dir::RIGHT;
			}
			else if (up < right && up < down && up < left) {
				aabb1.direction = dir::BOTTOM;
				aabb2.direction = dir::TOP;
			}
			else if (down < right && down < up && down < left){
				aabb1.direction = dir::TOP;
				aabb2.direction = dir::BOTTOM;
			}
			else {
				aabb1.direction = dir::NONE;
				aabb2.direction = dir::NONE;
			}
		}
		//if not intersecting, its literally at the side
		else {
			if (aabb1.min.x < aabb2.min.x) {
				aabb1.direction = dir::RIGHT;
				aabb2.direction = dir::LEFT;
			}
			else if (aabb1.max.x > aabb2.max.x) {
				aabb1.direction = dir::LEFT;
				aabb2.direction = dir::RIGHT;
			}
			else if (aabb1.min.y < aabb2.min.y) {
				aabb1.direction = dir::TOP;
				aabb2.direction = dir::BOTTOM;
			}
			else if (aabb1.max.y > aabb2.max.y) {
				aabb1.direction = dir::BOTTOM;
				aabb2.direction = dir::TOP;
			}
			else {
				aabb1.direction = dir::NONE;
				aabb2.direction = dir::NONE;
			}
		}

		//// step 1
		//if (aabb1.max.getx() > aabb2.min.getx() && aabb1.min.getx() < aabb2.max.getx() &&
		//	aabb1.max.gety() > aabb2.min.gety() && aabb1.min.gety() < aabb2.max.gety())
		//	return true;

		return true;
	}

	///OBB
	OBB::OBB(const Vec2& center, const double w, const double h, double angle) {
		Vec2 X((float)cos(angle), (float)sin(angle));
		Vec2 Y((float)-sin(angle), (float)cos(angle));

		X *= (float)w / 2;
		Y *= (float)h / 2;

		corner[0] = center - X - Y;
		corner[1] = center + X - Y;
		corner[2] = center + X + Y;
		corner[3] = center - X + Y;

		computeAxes();
	}

	bool OBB::overlaps1Way(const OBB& other) const {
		for (int a = 0; a < 2; ++a) {

			//double t = other.corner[0].dot(axis[a]);
			double t = MathEng::Vector2DDotProduct(other.corner[0], axis[a]);

			// Find the extent of box 2 on axis a
			double tMin = t;
			double tMax = t;

			for (int c = 1; c < 4; ++c) {
				//t = other.corner[c].dot(axis[a]);
				t = MathEng::Vector2DDotProduct(other.corner[c], axis[a]);

				if (t < tMin) {
					tMin = t;
				}
				else if (t > tMax) {
					tMax = t;
				}
			}

			// We have to subtract off the origin

			// See if [tMin, tMax] intersects [0, 1]
			if ((tMin > 1 + origin[a]) || (tMax < origin[a])) {
				// There was no intersection along this dimension;
				// the boxes cannot possibly overlap.
				return false;
			}
		}

		// There was no dimension along which there is no intersection.
		// Therefore the boxes overlap.
		return true;
	}

	void OBB::computeAxes() {
		axis[0] = corner[1] - corner[0];
		axis[1] = corner[3] - corner[0];

		// Make the length of each axis 1/edge length so we know any
		// dot product must be less than 1 to fall within the edge.

		for (int a = 0; a < 2; ++a) {
			//axis[a] /= axis[a].squaredLength();
			axis[a] /= MathEng::Vector2DSquareLength(axis[a]);
			//origin[a] = corner[0].dot(axis[a]);
			origin[a] = MathEng::Vector2DDotProduct(corner[0], axis[a]);
		}
	}

	void OBB::moveTo(const Vec2& center) {
		Vec2 centroid = (corner[0] + corner[1] + corner[2] + corner[3]) / 4;

		Vec2 translation = center - centroid;

		for (int c = 0; c < 4; ++c) {
			corner[c] += translation;
		}

		computeAxes();
	}

	bool OBB::overlaps(const OBB& other) const {
		return overlaps1Way(other) && other.overlaps1Way(*this);
	}

	int CollisionIntersection_CircleLineSegment(const Circle& circle,
		const Vec2& ptEnd,
		const LineSegment& lineSeg,
		Vec2& interPt,
		Vec2& normalAtCollision,
		float& interTime,
		bool& checkLineEdges) {
		if ((Vector2DDotProduct(lineSeg.normal, circle.center) - Vector2DDotProduct(lineSeg.normal, lineSeg.pt0)) <= (circle.radius * -1.0f))
		{
			Vec2 vel;
			vel = ptEnd - circle.center;
			Vec2 velnorm{ vel.y, -vel.x };
			Vec2 p0Prime = lineSeg.pt0 - (circle.radius * lineSeg.normal);
			Vec2 p1Prime = lineSeg.pt1 - (circle.radius * lineSeg.normal);
			if ((Vector2DDotProduct(velnorm, p0Prime - circle.center) * Vector2DDotProduct(velnorm, p1Prime - circle.center)) < 0.0f)
			{
				interTime = ((Vector2DDotProduct(lineSeg.normal, lineSeg.pt0) - Vector2DDotProduct(lineSeg.normal, circle.center) - circle.radius) / (Vector2DDotProduct(lineSeg.normal, vel)));
				if (interTime >= 0.0f && interTime <= 1.0f)
				{
					interPt = circle.center + (vel * interTime);
					normalAtCollision = lineSeg.normal * -1.0f;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		else if ((Vector2DDotProduct(lineSeg.normal, circle.center) - Vector2DDotProduct(lineSeg.normal, lineSeg.pt0)) >= circle.radius)
		{
			Vec2 vel;
			vel = ptEnd - circle.center;
			Vec2 velnorm{ vel.y, -vel.x };
			Vec2 p0Prime = lineSeg.pt0 + (circle.radius * lineSeg.normal);
			Vec2 p1Prime = lineSeg.pt1 + (circle.radius * lineSeg.normal);
			if ((Vector2DDotProduct(velnorm, p0Prime - circle. center) * Vector2DDotProduct(velnorm, p1Prime - circle. center)) < 0.0f)
			{
				interTime = ((Vector2DDotProduct(lineSeg. normal, lineSeg. pt0) - Vector2DDotProduct(lineSeg. normal, circle. center) + circle.radius) / (Vector2DDotProduct(lineSeg. normal, vel)));
				if (interTime >= 0.0f && interTime <= 1.0f)
				{
					interPt = circle. center + vel * interTime;
					normalAtCollision = lineSeg.normal;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		else
		{
			return false;
		}
	}

	int CollisionIntersection_CircleCircle(const Circle& circleA,
		const Vec2& velA,
		const Circle& circleB,
		const Vec2& velB,
		Vec2& interPtA,
		Vec2& interPtB,
		float& interTime) {
		// set one circle to be relatively stationary
		Ray ray = { circleA.center, (velA - velB) };

		// set the other to be the circle with combined radius
		Circle circle = { (circleA.radius + circleB.radius), circleB.center};

		// use ray circle collision to check
		if (CollisionIntersection_RayCircle(ray, circle, interTime))
		{
			interPtA = circleA.center + interTime * velA;
			interPtB = circleB.center + interTime * velB;

			return true;
		}
		else
		{
			return false;
		}
	}

	int CollisionIntersection_RayCircle(const Ray& ray,
		const Circle& circle,
		float& interTime) {
		float a; //a, b and c are the coefficients
		float b; //for the quadratic equation at^2 + bt + c
		float c; //that will be used for collision calculation

		// v . v
		a = Vector2DDotProduct(ray.dir, ray.dir);
		// -2(BsC) . v
		b = -2.0f * Vector2DDotProduct((circle.center - ray.pt), ray.dir);
		// (BsC) . (BsC) - r^2
		c = Vector2DDotProduct(circle.center - ray.pt, circle.center - ray.pt) - (circle.radius * circle.radius);

		//used for checking
		float discriminant = (b * b) - (4.0f * a * c);

		if (discriminant < 0) //ray misses circle
		{
			return 0;
		}
		else if (discriminant == 0) //ray grazes circle
		{
			float ti = (-1.0f * b) / (2 * a);
			if (ti >= 0 && ti <= 1)
			{
				interTime = ti;
				return 1;
			}
			else
			{
				return 0;
			}
		}
		float ti0 = ((-1.0f * b) - sqrt(discriminant)) / (2 * a);
		float ti1 = ((-1.0f * b) + sqrt(discriminant)) / (2 * a);
		float ti = std::min(ti0, ti1);
		if (ti >= 0 && ti <= 1) //ray intersects circle at 2 points
		{
			interTime = ti;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	void CollisionResponse_CircleLineSegment(const Vec2& ptInter,
		const Vec2& normal,
		Vec2& ptEnd,
		Vec2& reflected) {
		//return Bi + penetration - 2(penetration . normal) * normal;
		Vec2 i = ptEnd - ptInter;
		reflected = i - (2 * Vector2DDotProduct(i, normal) * normal);
		Vector2DNormalize(reflected, reflected);
		ptEnd = ptInter + reflected;
	}

	void CollisionResponse_CirclePillar(const Vec2& normal,
		const float& interTime,
		const Vec2& ptStart,
		const Vec2& ptInter,
		Vec2& ptEnd,
		Vec2& reflectedVectorNormalized) {
		Vec2 m = ptStart - ptInter;
		reflectedVectorNormalized = 2.0f * Vector2DDotProduct(m, normal) * normal - m;
		ptEnd = ptInter + reflectedVectorNormalized * (1.0f - interTime);
		Vector2DNormalize(reflectedVectorNormalized, reflectedVectorNormalized);
	}

	void CollisionResponse_CircleCircle(Vec2& normal,
		const float interTime,
		Vec2& velA,
		const float& massA,
		Vec2& interPtA,
		Vec2& velB,
		const float& massB,
		Vec2& interPtB,
		Vec2& reflectedVectorA,
		Vec2& ptEndA,
		Vec2& reflectedVectorB,
		Vec2& ptEndB) {
		//length of Va along N
		float aA = Vector2DDotProduct(velA, normal);
		//length of Vb along N
		float aB = Vector2DDotProduct(velB, normal);

		//compute reflected vector Va'
		reflectedVectorA = velA - ((2.0f * (aA - aB)) / (massA + massB)) * massB * normal;
		//compute reflected vector Vb'
		reflectedVectorB = velB + ((2.0f * (aA - aB)) / (massA + massB)) * massA * normal;

		//compute position Cae after reflection
		ptEndA = interPtA + (1.0f - interTime) * reflectedVectorA;
		//compute position Cbe after reflection
		ptEndB = interPtB + (1.0f - interTime) * reflectedVectorB;
	}
}
