/*!
@file    Animal_Logic.cpp
@author  irfanhidayatb.r@digipen.edu
@date    13/9/2020


This file contains the behavior for animal AI
*/
#include "Animal_Logic.h"

void AnimalLogic::stateRidden(Entity* animal) {
	Animal_Component* aComp = GET_ANIMAL_COMPONENT(animal);
	aComp->attached = true;
	aComp->wasAttached = false;
	aComp->dizzy = false;
	aComp->untolerable = false;
	aComp->speed = aComp->ridingSpeed;
	aComp->alive = true;
	aComp->setRiddenTime(0.0f);
	Transform_Component* tCompA = GET_TRANSFORM_COMPONENT(animal);
	if (aComp->attachedPlayer) {
		Player_Component* plComp = GET_PLAYER_COMPONENT(aComp->attachedPlayer);
		Transform_Component* tCompPl = GET_TRANSFORM_COMPONENT(aComp->attachedPlayer);
		tCompA->SetPosition(tCompPl->x, tCompPl->y);
		plComp->setAttachedFlag(true);
	}
}

void AnimalLogic::stateHitObstacle(Entity* animal) {
	Animal_Component* aComp = GET_ANIMAL_COMPONENT(animal);
	if (aComp->attached) {
		Transform_Component* tComp = GET_TRANSFORM_COMPONENT(animal);
		Physics_Component* pCompA = GET_PHYSICS_COMPONENT(animal);
		Animal_Component* aCompA = GET_ANIMAL_COMPONENT(animal);
		if (aComp->attachedPlayer) {
			Physics_Component* pCompPl = GET_PHYSICS_COMPONENT(aComp->attachedPlayer);
			Player_Component* plCompPl = GET_PLAYER_COMPONENT(aComp->attachedPlayer);
			plCompPl->jump();
			/*plCompPl->minusHP(1);*/
			aCompA->setDizzyFlag(true);
		}
		tComp->SetPosition(tComp->x, tComp->y - tComp->scaleY / 2);
		aCompA->setDizzyFlag(true);
		aCompA->riddenTime = 0.0f;
	}
	else {
		aComp->setDizzyFlag(true);
		Transform_Component* tComp = GET_TRANSFORM_COMPONENT(animal);
		Physics_Component* pComp = GET_PHYSICS_COMPONENT(animal);
		tComp->SetPosition(tComp->x, tComp->y - tComp->scaleY / 2);
		pComp->body.setVel(Vec2());
	}
	aComp->alive = false;
}

void AnimalLogic::stateRegular(Entity* animal) {
	Animal_Component* aComp = GET_ANIMAL_COMPONENT(animal);
	Physics_Component* pComp = GET_PHYSICS_COMPONENT(animal);
	aComp->attached = false;
	aComp->wasAttached = false;
	aComp->isRidden = false;
	aComp->riddenTime = 0.0f;
	aComp->speed = aComp->normSpeed;
	aComp->dizzy = false;
	aComp->untolerable = false;
	aComp->alive = true;
	//pComp->body.setVel(aComp->normSpeed);

}

void AnimalLogic::stateNoTolerance(Entity* animal) {
	Animal_Component* aComp = GET_ANIMAL_COMPONENT(animal);
	aComp->attached = false;
	aComp->wasAttached = true;
	aComp->dizzy = false;
	aComp->untolerable = true;
	GET_PHYSICS_COMPONENT(animal)->body.setVel({ 0.0f, -200.0f });
	if (aComp->attachedPlayer) {
		Player_Component* plComp = GET_PLAYER_COMPONENT(aComp->attachedPlayer);
		Physics_Component* pComp = GET_PHYSICS_COMPONENT(aComp->attachedPlayer);
		plComp->setAttachedFlag(false);
		pComp->body.setVel({ 0.0f, 50.0f });
		pComp->body.setAccel(Vec2());
		FORCE_OBJ yeet;
		yeet.setLifetime(1 * PhysicsEngine::fixedDT);
		yeet.setMag(pComp->body.getDir() * PhysicsEngine::charVel * 0.7f);
		yeet.setAge(0);
		yeet.ActivateForce(true);
		pComp->body.push_force(yeet);
		aComp->riddenTime = 0.0f;
	}
	aComp->alive = false;
}

void AnimalLogic::stateNotInView(Entity* animal) {
	Animal_Component* aComp = GET_ANIMAL_COMPONENT(animal);
	Physics_Component* pComp = GET_PHYSICS_COMPONENT(animal);
	aComp->attached = false;
	aComp->wasAttached = false;
	aComp->isRidden = false;
	aComp->riddenTime = 0.0f;
	aComp->speed = { 0.0f, 0.0f };
	aComp->dizzy = false;
	aComp->alive = true;
	aComp->untolerable = false;
	pComp->body.setVel(Vec2());
}