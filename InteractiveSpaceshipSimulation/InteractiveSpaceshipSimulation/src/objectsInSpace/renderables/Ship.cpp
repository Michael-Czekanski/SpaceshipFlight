#include "objectsInSpace/renderables/Ship.h"


void Ship::destroyed()
{
	// TODO
	isDestroyed = true;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "Ship destroyed" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	Game::gameover();
}

Ship::Ship(glm::vec3 position, const RenderData& renderData, ShipLight shipLight, float shipSpeed, glm::vec3 scale, GLuint programDraw, TextureData textureData,
	float pitchSpeed, float yawSpeed, float rollSpeed, float slowDownSpeed):
	slowDownSpeed(slowDownSpeed), RenderableObject(position, renderData, scale, programDraw, textureData)
{
	maxHp = 5;
	hp = maxHp;
	this->speed = shipSpeed;
	this->pitchSpeed = pitchSpeed;
	this->yawSpeed = yawSpeed;
	this->rollSpeed = rollSpeed;

	this->shipLight = shipLight;
	this->shipLight.update(this->position, this->getVectorForward());

	rigidActor = RigidbodyFactory::createShipRigidbody(position, rotationQuat, this);

	ShipPointer::shipPointer = this;
}

void Ship::moveForward()
{
	if (rigidActor)
	{
		getRigidDynamic()->addForce(PhysxGLMConverter::vec3ToPxVec3(vectorForward * speed * Time::getDeltaTimeSec()));
	}
}

void Ship::moveBackwards()
{
	if (rigidActor)
	{
		getRigidDynamic()->addForce(PhysxGLMConverter::vec3ToPxVec3(-vectorForward * speed * Time::getDeltaTimeSec()));
	}
}

void Ship::rotateShip(float pitch, float yaw, float roll)
{
	pitch = glm::clamp(pitch, -1.0f, 1.0f);
	yaw = glm::clamp(yaw, -1.0f, 1.0f);
	roll = glm::clamp(roll, -1.0f, 1.0f);

	float rotationAngleX = pitchSpeed * pitch * Time::getDeltaTimeSec();
	float rotationAngleY = yawSpeed * (-yaw) * Time::getDeltaTimeSec();
	float rotationAngleZ = rollSpeed * roll * Time::getDeltaTimeSec();

	if (rigidActor)
	{
		getRigidDynamic()->setAngularVelocity(PhysxGLMConverter::vec3ToPxVec3(
			vectorForward * rotationAngleZ + vectorRight * rotationAngleX + vectorTop * rotationAngleY));
	}
	
}

ShipLight Ship::getShipLight()
{
	return this->shipLight;
}

PxRigidDynamic* Ship::getRigidDynamic()
{
	return (PxRigidDynamic*)rigidActor;
}

void Ship::physicsUpdate(RenderableUpdateData& update)
{
	RenderableObject::physicsUpdate(update);
	shipLight.update(position, vectorForward);
}

void Ship::slowDown()
{
	getRigidDynamic()->setLinearVelocity(getRigidDynamic()->getLinearVelocity() / slowDownSpeed);
}

void Ship::hit()
{
	if (hp > 0)
	{
		hp--;
		if (hp == 0) {
			destroyed();
		}
		else {
			std::cout << "-------------------------------------------------" << std::endl;
			std::cout << "Ship hit, HP = " << hp << std::endl;
			std::cout << "-------------------------------------------------" << std::endl;
			if (engineSmokeParticleGenerator)
			{
				if (!engineSmokeParticleGenerator->generating())
					engineSmokeParticleGenerator->startGeneration();
				engineSmokeParticleGenerator->minParticleSize *= 1.6f;
				engineSmokeParticleGenerator->maxParticleSize *= 1.6f;
			}
		}
	}
}

int Ship::getHp()
{
	return hp;
}

void Ship::updateModelMatrix()
{
	this->modelMatrix = this->positionMat * this->rotationMat * this->scaleMat;
}




