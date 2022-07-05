/*!
@file    Shape.cpp
@author  irfanhidayatb.r@digipen.edu
@date    13/9/2020


This file contains the definitions of shape structs
*/
#include "Shape.h"

Circle::Circle(float rad, Vec2 pos) : radius{rad}, center{pos} {
	setName("Circle");
}

std::string Circle::getName() {
	return name;
}

void Circle::setName(std::string name_) {
	name = name_;
}

Rectangle::Rectangle(Vec2 pos, Vec2 scale) {
	min = pos - scale;
	max = pos + scale;
	height = scale.y + scale.y;
	width = scale.x + scale.x;
	setName("Rectangle");
}

Rectangle::Rectangle(Vec2 pos, float scaleX, float scaleY) {
	Vec2 scale = { scaleX, scaleY };
	min = pos - scale;
	max = pos + scale;
	height = scale.y + scale.y;
	width = scale.x + scale.x;
	setName("Rectangle");
}

std::string Rectangle::getName() {
	return name;
}
void Rectangle::setName(std::string name_) {
	name = name_;
}

Triangle::Triangle(Vec2 v1, Vec2 v2, Vec2 v3) : vertex1{ v1 }, vertex2{ v2 }, vertex3{ v3 }{
	setName("Triangle");
}

std::string Triangle::getName() {
	return name;
}

void Triangle::setName(std::string name_) {
	name = name_;
}

LineSegment::LineSegment(Vec2& pos, float scale, float dir) {
	pt0.x = pos.x + (scale * 0.5f * cosf(dir));
	pt0.y = pos.y + (scale * 0.5f * sinf(dir));
	pt1.x = pos.x - (scale * 0.5f * cosf(dir));
	pt1.y = pos.y - (scale * 0.5f * sinf(dir));

	//vector to calculate normal
	Vec2 temp;
	temp.x = pt1.x - pt0.x;
	temp.y = pt1.y - pt0.y;

	//normal based off vector
	Vec2 normal_{ temp.y, -temp.x };

	//normalize normal and set in output
	Vector2DNormalize(normal_, normal_);
	normal = normal_;

	name = "LineSegment";
}

std::string LineSegment::getName() {
	return name;
}

void LineSegment::setName(std::string name_) {
	name = name_;
}

Ray::Ray(Vec2 point, Vec2 direction) : pt{ point }, dir{ direction } {
	name = "Ray";
}

std::string Ray::getName() {
	return name;
}

void Ray::setName(std::string name_) {
	name = name_;
}