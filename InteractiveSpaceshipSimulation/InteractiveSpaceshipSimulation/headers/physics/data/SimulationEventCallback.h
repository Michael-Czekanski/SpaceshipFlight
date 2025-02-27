#pragma once

#include "PxPhysicsAPI.h"
#include <iostream>
#include <typeinfo>
#include "utils/ShipPointer.h"

class Ship;

using namespace physx;

/// <summary>
/// Simulation events processor
/// </summary>
class SimulationEventCallback :
    public PxSimulationEventCallback
{
    // Inherited via PxSimulationEventCallback
    virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override;
    virtual void onWake(PxActor** actors, PxU32 count) override;
    virtual void onSleep(PxActor** actors, PxU32 count) override;
    virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;
    virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) override;
    virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override;
};

