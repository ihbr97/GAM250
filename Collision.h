/*!
@file    Collision.h
@author  irfanhidayatb.r@digipen.edu
@date    13/9/2020


This file implements functionality useful and necessary for collision.

*/
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "../Math/MathLibrary.h"
#include "../Physics/Physics.h"
#include "../Shape.h"
#include <algorithm>
using Vec2 = MathEng::Vector2D;
namespace Collision {
	enum CollisionDirection {
		TOP = 0,
		RIGHT,
		BOTTOM,
		LEFT,
		NONE
	}; using dir = CollisionDirection;

	struct AABB //bounding box aligned to axis, for collision
	{
		Vec2	min;
		Vec2	max;
		dir		direction = NONE;
		bool top = 0;
		bool right = 0;
		bool bottom = 0;
		bool left = 0;
	};

	struct OBB {
		Vec2	corner[4];
		Vec2	axis[2];
		/*
		[3] * * * * * [2]
			* * * * *
	axis[1]	* * * * *
			* * * * *
		[0] * * * * * [1]
			  axis[0]
		*/
		double origin[2];
		OBB() {
			for (int i = 0; i < 4; i++)
				corner[i] = { 0,0 };
			for (int i = 0; i < 2; i++)
				axis[i] = { 0,0 };
		}
		OBB(const Vec2& center, const double w, const double h, double angle);
		bool overlaps1Way(const OBB& other) const;
		void computeAxes();
		void moveTo(const Vec2& center);
		bool overlaps(const OBB& other) const;
	};

	bool CollisionIntersection_RectRect(AABB& aabb1, const Vec2& vel1,
		AABB& aabb2, const Vec2& vel2);

	int CollisionIntersection_CircleLineSegment(const Circle& circle,
		const Vec2& ptEnd,
		const LineSegment& lineSeg,
		Vec2& interPt,
		Vec2& normalAtCollision,
		float& interTime,
		bool& checkLineEdges);

	int CollisionIntersection_CircleCircle(const Circle& circleA,
		const Vec2& velA,
		const Circle& circleB,
		const Vec2& velB,
		Vec2& interPtA,
		Vec2& interPtB,
		float& interTime);

	int CollisionIntersection_RayCircle(const Ray& ray,
		const Circle& circle,
		float& interTime);

	void CollisionResponse_CircleLineSegment(const Vec2& ptInter,
		const Vec2& normal,
		Vec2& ptEnd,
		Vec2& reflected);

	void CollisionResponse_CirclePillar(const Vec2& normal,
		const float& interTime,
		const Vec2& ptStart,
		const Vec2& ptInter,
		Vec2& ptEnd,
		Vec2& reflectedVectorNormalized);

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
		Vec2& ptEndB);
}
#endif