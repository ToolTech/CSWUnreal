//*****************************************************************************
//
// Copyright (C) SAAB AB
//
// All rights, including the copyright, to the computer program(s)
// herein belong to SAAB AB. The program(s) may be used and/or
// copied only with the written permission of SAAB AB, or in
// accordance with the terms and conditions stipulated in the
// agreement/contract under which the program(s) have been
// supplied.
//
//
// Information Class:	COMPANY UNCLASSIFIED
// Defence Secrecy:		NOT CLASSIFIED
// Export Control:		NOT EXPORT CONTROLLED
//
//
// File			: gzParticles.h
// Module		: 
// Description	: Class definition of the particle simulation classes
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.306
//		
//
//			
// NOTE:	Gizmo3D is a high performance 3D Scene Graph and effect visualisation 
//			C++ toolkit for Linux, Mac OS X, Windows, Android, iOS and HoloLens for  
//			usage in Game or VisSim development.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080125	Created file 	
// AMO	130816	Added global scale factor for fuzzy depth in smoke simulations
//
//******************************************************************************
#ifndef __GZ_PARTICLES_H__
#define __GZ_PARTICLES_H__

/*!	\file 
	\brief Definitions of Particle Simulations

*/

// Includes
#include "gzCuller.h"
#include "gzGeometry.h"
#include "gzNodeAction.h"

GZ_DECLARE_MEMBASE_EXPORT(gzParticleData,GZ_GRAPH_EXPORT);

//! All different types of particles
enum gzParticleType
{
	GZ_PARTICLE_TYPE_SMOKE,
};

//******************************************************************************
// Class	: gzParticleData
//									
// Purpose  : Base class for a particle definition
//			  gzParticleData is the actual particle that carries data in sims	
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080122	Created 
//									
//******************************************************************************
class gzParticleData : public gzReference , public GZ_MEMBASE(gzParticleData)
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_MEMBASE_IMP(gzParticleData);

	GZ_GRAPH_EXPORT	gzParticleData();
	GZ_GRAPH_EXPORT	virtual ~gzParticleData();

	// ----------- properties ----------------

	GZ_PROPERTY_EXPORT(gzVec3,			Position,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,			Velocity,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,			Acceleration,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,			Scale,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,			Energy,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,			Mass,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzDouble,		TimeStamp,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,			Initialised,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzMatrix4,		WorldTransform,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzParticleType,	ParticleType,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,			ParticleColor,  GZ_GRAPH_EXPORT);
};

GZ_DECLARE_REFPTR(gzParticleData);

// Forwards
class gzParticleEmitter;
class gzParticleSpace;
class gzParticleSystem;
class gzParticleSimulationAction;

//******************************************************************************
// Class	: gzParticleSystem
//									
// Purpose  : Create, Destroy, Render etc of a certain type of particles
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080122	Created 
//									
//******************************************************************************
class gzParticleSystem :	public gzObject , 
							public gzBoundary
{
public:

	GZ_GRAPH_EXPORT gzParticleSystem();

	GZ_GRAPH_EXPORT virtual ~gzParticleSystem();

	GZ_GRAPH_EXPORT gzParticleSystem(const gzParticleSystem &right);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override =0;

	// ---------- The control API ---------------------------------------

	GZ_GRAPH_EXPORT gzBool canAddParticle();
	GZ_GRAPH_EXPORT gzVoid addParticle(gzParticleData *particle);
	GZ_GRAPH_EXPORT gzVoid removeParticle(gzParticleData *particle);

	GZ_GRAPH_EXPORT virtual gzVoid renderParticles(gzContext *context)=0;
	GZ_GRAPH_EXPORT virtual gzVoid updateSimulation(gzDouble &timeStamp);

	GZ_GRAPH_EXPORT gzVoid attachSceneSimulationTrigger(gzScene *scene);

	GZ_GRAPH_EXPORT static gzParticleSystem *findParticleSystem( const gzString &name , gzParticleSystem *parent=nullptr);
	GZ_GRAPH_EXPORT static gzVoid unregisterAllParticleSystems();
	GZ_GRAPH_EXPORT gzVoid registerParticleSystem( const gzString &name );
	GZ_GRAPH_EXPORT gzVoid unregisterParticleSystem( const gzString &name );

	// ---------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT(gzUInt32,		MaxNumberOfParticles,		GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Release actions before destroy -----------------------
	GZ_GRAPH_EXPORT	virtual gzBool	releaseRefs() override;

protected:

	// Lets be friends
	friend class gzParticleEmitter;
	friend class gzParticleSpace;

	gzRefList<gzParticleData>				m_particles;

	gzParticleSpace *						m_space;

	gzParticleSimulationAction *			m_simAction;

private:

	static gzMutex								s_particleSystemLocker;
	static gzRefDict<gzString,gzParticleSystem> s_particleSystemDictionary;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzParticleSystem);

//******************************************************************************
// Class	: gzParticleSystemSmoke
//									
// Purpose  : Create, Destroy, Render Smoke. Travels in air
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080122	Created 
//									
//******************************************************************************
class gzParticleSystemSmoke : public gzParticleSystem
{
public:

	GZ_GRAPH_EXPORT gzParticleSystemSmoke();

	GZ_GRAPH_EXPORT virtual ~gzParticleSystemSmoke();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Cloning ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- The control API ---------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid renderParticles(gzContext *context) override;
	GZ_GRAPH_EXPORT virtual gzVoid updateSimulation(gzDouble &timeStamp) override;

	// ---------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT(gzVec3,  LocalGravity,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,  LocalWindSpeed,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat, FuzzyDepth,		GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ----------- Global control ---------------------------------------

	GZ_GRAPH_EXPORT static gzVoid setGlobalFuzzyDepthScale(gzContext *context,gzFloat scale=1.0f);

private:

	gzVoid					setUpState();

	gzStatePtr				m_smokeState;
	gzGFXProgramPtr			m_theParticleVertexShader;
	gzGFXProgramPtr			m_theParticleGeometryShader;
	gzGFXProgramPtr			m_theParticleFragmentShader;

	gzDynamicArray<gzUByte>	m_data;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzParticleSystemSmoke);

//******************************************************************************
// Class	: gzParticleEmitter
//									
// Purpose  : Base class for emitting particles into particle system
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080122	Created 
//									
//******************************************************************************
class gzParticleEmitter : public gzNode
{
public:
	GZ_GRAPH_EXPORT gzParticleEmitter(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzParticleEmitter();

	GZ_GRAPH_EXPORT gzParticleEmitter(const gzParticleEmitter & right);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override = 0;

	// ---------- The control API ---------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid emitParticles(const gzDouble &timeStamp)=0;	//!< The required emitter function

	GZ_GRAPH_EXPORT gzVoid	addParticleSystem(gzParticleSystem *system);
	GZ_GRAPH_EXPORT gzVoid	removeParticleSystem(gzParticleSystem *system);
	GZ_GRAPH_EXPORT gzRefList<gzParticleSystem> &getParticleSystems();

	// ---------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT_(gzBool,			IsRunning,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzMatrix4,		CurrentTransform,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzParticleType,	ParticleType,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,			ParticleColor,		GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Release actions before destroy -----------------------
	GZ_GRAPH_EXPORT	virtual gzBool	releaseRefs() override;

protected:

	gzRefList<gzParticleSystem>		m_particleSystems;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzParticleEmitter);

//******************************************************************************
// Class	: gzParticlePointEmitter
//									
// Purpose  : A point shaped emitter
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080122	Created 
//									
//******************************************************************************
class gzParticlePointEmitter : public gzParticleEmitter
{
public:
	GZ_GRAPH_EXPORT gzParticlePointEmitter(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzParticlePointEmitter();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone ------------------------------------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- The control API --------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid emitParticles(const gzDouble &timeStamp) override;	//!< The required emitter function

	// ---------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT(gzVec3,		Position,				GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,		ParticlesPerSecond,		GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,		ParticleEnergy,			GZ_GRAPH_EXPORT);
	
	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

private:

	gzDouble m_lastEmitTime;
};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzParticlePointEmitter);

//******************************************************************************
// Class	: gzParticleSpace
//									
// Purpose  : Local space definition for particle simulations
//			  Geometric position in scene graph
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	080122	Created 
//									
//******************************************************************************
class gzParticleSpace : public gzNode
{
public:
	GZ_GRAPH_EXPORT gzParticleSpace(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzParticleSpace();

	GZ_GRAPH_EXPORT gzParticleSpace(const gzParticleSpace & right);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Common graph functions --------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	GZ_GRAPH_EXPORT virtual gzActionStage useActionStage( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- No cloning of base - pure virtual ---------------------

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- The control API ---------------------------------------

	GZ_GRAPH_EXPORT gzVoid	addParticleSystem(gzParticleSystem *system);
	GZ_GRAPH_EXPORT gzVoid	removeParticleSystem(gzParticleSystem *system);
	GZ_GRAPH_EXPORT gzRefList<gzParticleSystem> &getParticleSystems();

	GZ_GRAPH_EXPORT gzVoid	addEmitter(gzParticleEmitter *emitter);

	GZ_GRAPH_EXPORT static gzVoid attachSceneSimulationTrigger(gzScene *scene,gzNode *node);
	GZ_GRAPH_EXPORT static gzBool rebindParticleSpaces(gzNode *node,gzParticleSpace *topSpace=nullptr);

	// ---------- Properties -------------------------------------------

	GZ_PROPERTY_EXPORT(gzMatrix4,	CurrentTransform,	GZ_GRAPH_EXPORT);

	// ---------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid		write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid		read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Release actions before destroy -----------------------
	GZ_GRAPH_EXPORT	virtual gzBool	releaseRefs() override;

private:

	gzRefList<gzParticleSystem>		m_particleSystems;

};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzParticleEmitter);

#endif // __GZ_PARTICLES_H__

