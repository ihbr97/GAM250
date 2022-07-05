/*!
@file    Shape.h
@author  irfanhidayatb.r@digipen.edu
@date    13/9/2020


This file contains the declarations of shape structs
*/
#pragma once
#include <iostream>
#include <string>
#include "Math/MathLibrary.h"

struct Shape {
	std::string name;
	virtual std::string getName() = 0;
	virtual void setName(std::string) = 0;
	~Shape() = default;
};

struct Circle : public Shape {
	float radius;
	Vec2 center;
	Circle(float rad, Vec2 pos);
	virtual std::string getName() override;
	virtual void setName(std::string) override;
};

struct Rectangle : public Shape {
	float height;
	float width;
	Vec2 min;
	Vec2 max;
	Rectangle(Vec2 pos, Vec2 scale);
	Rectangle(Vec2 pos, float scaleX, float scaleY);
	virtual std::string getName() override;
	virtual void setName(std::string) override;
};

struct Triangle : public Shape {
	Vec2 vertex1;
	Vec2 vertex2;
	Vec2 vertex3;
	Triangle(Vec2 v1, Vec2 v2, Vec2 v3);
	virtual std::string getName() override;
	virtual void setName(std::string) override;
};

struct LineSegment: public Shape {
	Vec2 pt0;
	Vec2 pt1;
	Vec2 normal;

	LineSegment(Vec2& pos, float scale, float dir);
	virtual std::string getName() override;
	virtual void setName(std::string) override;
};

struct Ray : public Shape {
	Vec2 pt;
	Vec2 dir;

	Ray(Vec2 point, Vec2 direction);
	virtual std::string getName() override;
	virtual void setName(std::string) override;
};