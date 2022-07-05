/*!
@file    Animal_Logic.h
@author  irfanhidayatb.r@digipen.edu
@date    13/9/2020


This file contains the behavior for animal AI
*/
#pragma once
#include "../Math/MathLibrary.h"
#include "../CE_Types.h"
#include "../Includes.h"
#include "Animal/Animal_Component.h"

namespace AnimalLogic {
	void stateRidden(Entity* animal);
	void stateHitObstacle(Entity* animal);
	void stateRegular(Entity* animal);
	void stateNoTolerance(Entity* animal);
	void stateNotInView(Entity* animal);
}