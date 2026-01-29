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
// File			: gzTransform.h
// Module		: 
// Description	: Class definition of the gzTransform class
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
// AMO	981122	Created file 	
// LJH	041019	Added online comments
// AMO	231206	Changed from HPR orientation to quaternion rotation	(2.12.125)
//
//******************************************************************************
#ifndef __GZ_TRANSFORM_H__
#define __GZ_TRANSFORM_H__

/*!	\file 
	\brief Base definitions for transform related nodes

*/


#include "gzGroup.h"

//******************************************************************************
// Class	: gzTransform
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981209	Created 
//									
//******************************************************************************
//!The gzTransform class is a gzGroup node that transforms all the sibling children.
class gzTransform : public gzGroup 
{
public:
	//! Default constructor
	/*! It is possible to set a name on the transform. */
	GZ_GRAPH_EXPORT gzTransform(const gzString & name=GZ_EMPTY_STRING);
	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzTransform(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface.
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Common Transform functions ----------------------------

	//!Updates the boundary for the transform. 
	/*!
	The boundary surrounds the transform and all its children.
	It is usually called by the system when the scene graph needs an update.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	//!Resets all values to unit. 
	/*!
	Default resets transform but keeps head axis.
	*/
	GZ_GRAPH_EXPORT gzVoid	reset(gzBool resetTransform=TRUE,gzBool resetAxis=FALSE);	

	
	//!Returns true if the transform is active, otherwise false.
	/*!
	If the transform is non unit then the transform is active.
	*/
	GZ_GRAPH_EXPORT gzBool	isActive();

	//!Default behavior is to accumulate the transform. 
	/*!
	The result of the scene graph transforms along a tree branch is m1*m2*m3 
	etc. where m3 is the last transform in the branch and m1 is the top transform in the scene.
	*/
	GZ_GRAPH_EXPORT gzVoid	useAccumulatedTransform(gzBool on);

	//!	Returns true if accumulated transform is used, otherwise false.
	GZ_GRAPH_EXPORT gzBool	useAccumulatedTransform() const;

	/*!
	Used to set identity ID to a transform so it can be used with a gzTransformBase to 
	enumerate a number of identified transforms under the base. E.g. Used to locally 
	define transform id for matrix weights in a gzGeometry (Skinning).
	Set to zero (0) to disable transform id.
	*/
	GZ_GRAPH_EXPORT gzVoid	setBaseID(gzUInt32 id=0);
	/*!
	Returns the current transform ID (Default 0)
	*/
	GZ_GRAPH_EXPORT gzUInt32	getBaseID();

	GZ_GRAPH_EXPORT gzVoid		setPreMultTransform(const gzMatrix4 &preMult);
	GZ_GRAPH_EXPORT gzMatrix4	getPreMultTransform();
	GZ_GRAPH_EXPORT gzBool		hasPreMultTransform();

	// ---------- additive commands -------------------------------------

	// Note that additive commands are reset by absolute commands

	//! Rotation about the vector specified in degrees
	/*! This is the relative method for rotation. The order of transformations is important.
	*/
	GZ_GRAPH_EXPORT gzVoid	rotate(const gzVec3 &vector , gzFloat rotation);	

	//! Heading = rot around y in degrees. Pitch = rot around x in degrees. Roll = rotation around z (not negative z) in degrees
	GZ_GRAPH_EXPORT gzVoid	rotateHPR(gzFloat heading , gzFloat pitch , gzFloat roll);

	/*!
	The translation step in each direction is specified. 

	This is the relative method for translation. The order of transformations is important.
	*/
	GZ_GRAPH_EXPORT gzVoid	translate( gzFloat dx , gzFloat dy , gzFloat dz ); 
	/*!
	The size of scaling in each direction is specified. 

	This is the relative method for scaling. The order of transformations is important.
	*/
	GZ_GRAPH_EXPORT gzVoid	scale( gzFloat sx , gzFloat sy , gzFloat sz ); 
	/*!
	A scaling size is specified. The same scaling factor is applied in the x, y and z direction. 

	This is the relative method for scaling. The order of transformations is important.
	*/
	GZ_GRAPH_EXPORT gzVoid	scale( gzFloat s); 
	/*
	Scale the transform to the unit 1. The bounding sphere gets a radius of size SQRT(2).
	*/
	GZ_GRAPH_EXPORT gzVoid	unitScale();

	// ---------- absolute commands -------------------------------------
	
	//! Set the transform out of a direction
	/*!
	Set the transform with z axis aligned in the targetvector direction and adds a roll tilt 
	in degrees around the targetvector axis. The up vector is used to identify head up.
	*/
	GZ_GRAPH_EXPORT gzVoid	setDirection(const gzVec3 &targetvector, gzFloat roll , const gzVec3 &up=gzVec3(0,1,0));

	//! Rotates in degress about the targetvector.
	/*!	This is the absolute command for rotation. The transforms are performed in an absolute order.
	First the scaling is performed, than the rotation and finally the translation. 
	
	If you want to use another order of transforms you need to use the relative transforms.
	Note that absolute transforms reset the relative transforms. If you want to use 
	a relative transform you have to use it after the absolute.
	*/
	GZ_GRAPH_EXPORT gzVoid	setRotation(const gzVec3 &targetvector, gzFloat rotation_in_degrees);

	GZ_GRAPH_EXPORT gzVoid	setRotation(const gzQuaternion& quat);

	//! Set the transform from heading,pitch and roll
	/*!
	Sets the transform with a rotation around the Y axis in heading degress clockwise, elevates the z axis in pitch degrees 
	and tilts the head roll degress.
	*/
	GZ_GRAPH_EXPORT gzVoid	setHPR( gzFloat heading , gzFloat pitch , gzFloat roll);

	//! Translates the transform and its children the specified step in each direction.
	/*!	This is the absolute command for translation. The transforms are performed in an absolute order.
	First the scaling is performed, than the rotation and finally the translation. 
	
	If you want to use another order of transforms you need to use the relative transforms.
	Note that absolute transforms reset the relative transforms. If you want to use 
	a relative transform you have to use it after the absolute.
	*/
	GZ_GRAPH_EXPORT gzVoid	setTranslation( gzFloat dx , gzFloat dy , gzFloat dz );
	//! Scale the transform and its children the specified size in each direction.
	/*!	This is the absolute command for scaling. The transforms are performed in an absolute order.
	First the scaling is performed, than the rotation and finally the translation. 
	
	If you want to use another order of transforms you need to use the relative transforms.
	Note that absolute transforms reset the relative transforms. If you want to use 
	a relative transform you have to use it after the absolute.
	*/
	GZ_GRAPH_EXPORT gzVoid	setScale( gzFloat sx , gzFloat sy , gzFloat sz );

	//! setScale(s) is equal to setScale(s,s,s)
	GZ_GRAPH_EXPORT gzVoid	setScale( gzFloat s );

	//! Change transform origin
	/*!
	Sets the position of origin. All transforms are executed relative the new origin so there is a 
	ON base change to the new origin.
	*/
	GZ_GRAPH_EXPORT gzVoid	setOrigin( gzFloat ox , gzFloat oy , gzFloat oz , gzBool updateAbsolute=TRUE);

	//!Set transform axis.
	/*!
	Used to change the transform axis to a non ON base axis where x,y,z are defined by the new axes.
	*/
	GZ_GRAPH_EXPORT gzVoid	setBaseAxis( const gzVec3 &x_axis , const gzVec3 &y_axis , const gzVec3 &z_axis , gzBool updateAbsolute=TRUE);

	
	// ---------- vector variants ---------------------------------------
	
	//! Translates the transform and its children the step specified by the vector.
	/*!	This is the absolute command for translation. The transforms are performed in an absolute order.
	First the scaling is performed, than the rotation and finally the translation. 
	
	If you want to use another order of transforms you need to use the relative transforms.
	Note that absolute transforms reset the relative transforms. If you want to use 
	a relative transform you have to use it after the absolute.
	*/
	GZ_GRAPH_EXPORT gzVoid	setTranslation( const gzVec3 &xyz_trans );
	//! Scale the transform and its children the specified size in each direction. The size is specified as a gzVec3.
	/*!	This is the absolute command for scaling. The transforms are performed in an absolute order.
	First the scaling is performed, than the rotation and finally the translation. 
	
	If you want to use another order of transforms you need to use the relative transforms.
	Note that absolute transforms reset the relative transforms. If you want to use 
	a relative transform you have to use it after the absolute.
	*/
	GZ_GRAPH_EXPORT gzVoid	setScale(		const gzVec3 &xyz_scale );

	//! Change transform origin
	/*!
	Sets the position of origin using a vector. All transforms are executed relative the new origin so there is a 
	ON base change to the new origin.
	*/
	GZ_GRAPH_EXPORT gzVoid	setOrigin(		const gzVec3 &xyz_origin , gzBool updateAbsolute=TRUE);

	//! Set the transform from the hpr-vector.
	/*!
	Sets the transform with a rotation around the Y axis in xyz_hpr.v1 degress clockwise, elevates the z axis in 
	xyz_hpr.v2 degrees and tilts the head xyz_hpr.v3 degrees.
	*/
	GZ_GRAPH_EXPORT gzVoid	setHPR(			const gzVec3 &xyz_hpr );

	// ---------- get data commands -------------------------------------

	/*!
	The scale for the transform is stored in the variables sx, sy and sx.
	
	Returns true if successful, otherwise false.
	*/
	GZ_GRAPH_EXPORT gzBool	getScale( gzFloat &sx , gzFloat &sy , gzFloat &sz );
	
	/*!
	Returns true if the transform has been assigned an absolute scale value.
	*/
	GZ_GRAPH_EXPORT gzBool	hasScale();

	/*!
	The heading, pitch and rool for the transform is stored in the variables heading, pitch and roll.
	Returns true if successful, otherwise false.
	*/
	GZ_GRAPH_EXPORT gzBool	getHPR(gzFloat &heading , gzFloat &pitch , gzFloat &roll);
	
	GZ_GRAPH_EXPORT gzBool  getRotation(gzQuaternion& rotation);
	/*!
	Returns true if the heading, pitch and roll have been assigned values.
	*/
	GZ_GRAPH_EXPORT gzBool	hasRotation();

	/*!
	The translation for the transform is stored in the variables dx, dy and dx.
	
	Returns true if successful, otherwise false.
	*/
	GZ_GRAPH_EXPORT gzBool	getTranslation( gzFloat &dx , gzFloat &dy , gzFloat &dz );
	/*!
	Returns true if the transform has been assigned a translation value.
	*/
	GZ_GRAPH_EXPORT gzBool	hasTranslation();

	GZ_GRAPH_EXPORT gzBool	getOrigin( gzFloat &ox , gzFloat &oy , gzFloat &oz );
	GZ_GRAPH_EXPORT gzBool	hasOrigin();

	GZ_GRAPH_EXPORT gzBool	getBaseAxis( gzVec3 &x_axis , gzVec3 &y_axis , gzVec3 &z_axis );
	GZ_GRAPH_EXPORT gzBool	hasBaseAxis();

	// ---------- vector variants ---------------------------------------

	/*!
	The translation for the transform is stored in the translation vector.
	
	Returns true if successful, otherwise false.
	*/

	GZ_GRAPH_EXPORT const gzVec3 &getTranslation(gzBool *isBound=nullptr);

	GZ_GRAPH_EXPORT const gzQuaternion& getRotation(gzBool* isBound = NULL);

	GZ_GRAPH_EXPORT gzBool	getTranslation( gzVec3 &translation );

	GZ_GRAPH_EXPORT gzBool	getScale( gzVec3 &scale );

	GZ_GRAPH_EXPORT gzBool	getHPR( gzVec3 &hpr );

	GZ_GRAPH_EXPORT gzBool	getOrigin( gzVec3 &origin );

	// ---------- direct transform manipulation ------------------------

	GZ_GRAPH_EXPORT gzBool hasTransform();
	//! Get compound transform matrix.
	GZ_GRAPH_EXPORT gzMatrix4 &	getTransform();
	//! Reset the transform to a user defined transform. 
	/*! 
	Replaces all previous setXXX commands. 
	*/
	GZ_GRAPH_EXPORT gzVoid		setTransform(const gzMatrix4 &transform);

	//! Multiply current transform with mulTransform
	GZ_GRAPH_EXPORT gzVoid		accumulate(const gzMatrix4 &mulTransform);


	// ----------- tweak the scale radius for bounding spheres

	/*!
	Set the maximum scale value for the transform.

	When scaling is performed the maximum scale factor is stored in a maximum scale variable.
	This maximum scale variable contains the maximum scale factor for the transform.
	A bounding sphere with this maximum scale value as radius is guaranteed to surround the node.
	The actual size may be smaller, this is the maximum size.
	*/
	GZ_GRAPH_EXPORT gzVoid		setMaxScale(const gzFloat &maxScale);
	
	//!Returns the maximum scale value for the transform. 
	GZ_GRAPH_EXPORT gzFloat		getMaxScale();

		//!Set the currentMaxScale for the context to the scale value.
	/*!
	Is updated by the traversal process so normally you don't need to use this function.
	*/
	GZ_GRAPH_EXPORT static gzVoid	setCurrentMaxScale( gzContext *context , gzFloat scale );

	//!Returns the current inverted transform during the traversal.
	/*!
	If you derive your own node you can use this function to get the inverted transform in 
	pre and post traversal calls.
	*/
	GZ_GRAPH_EXPORT static gzMatrix4 & getCurrentInvertedTransform(gzContext *context);
	
	//!Used by the traversal process to reset all traversal transform info.
	/*!
	No need to use this in your normal application.
	*/
	GZ_GRAPH_EXPORT static gzVoid	resetIndex(gzContext *context);

	//! Used by the traversal process to post reset all traversal transform info.
	/*!
	No need to normally use this function.
	*/
	GZ_GRAPH_EXPORT static gzVoid	resetPostIndex( gzContext *context );

	//! Used by the traversal process to activate a certain transform.
	/*!
	No need to normally use this function. The transform connected to index is activated.
	*/
	GZ_GRAPH_EXPORT static gzVoid	activateIndex(gzContext *context , gzUInt32 index);

	//! Use by the traversal process.
	/*!
	No need to normally use this function. Activates a compiled set of transform info for a given index.
	*/
	GZ_GRAPH_EXPORT static gzVoid	activateCompiledIndex(gzContext *context , gzUInt32 index);

	//! Needed to be called by external touch on matrix
	GZ_GRAPH_EXPORT gzVoid calculateTransform(gzBool updateDirty = TRUE);

	GZ_GRAPH_EXPORT gzVoid getBaseTransform(gzMatrix4 &result,gzBool *isActive=nullptr);

	//! Needed to be called by external touch on matrix
	GZ_GRAPH_EXPORT	gzVoid calculateMaxScale();

	// ---------- Action Interface --------------------------------------
	
	//!Called in the traversal process.
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;
	
	//!Called in the traversal process.
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Serializing -------------------------------------------

	//!Writes the gzTransform data to the adapter.
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	
	//!Reads the gzTransform data from the adapter.
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	
	//!Returns the size of the gzTransform data.
	/*!
	The size if given in bytes.
	*/
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Debug function ----------------------------------------
	//!Prints debug information about the class.
	/*!
	Prints to the console by default. Uses gzMessage mechanism.
	*/
	GZ_GRAPH_EXPORT virtual	gzVoid	debugOutput(gzString base , gzString anchor , gzDebugFlags features) override;

	// --------- Utilties -----------------------------------------------
	//!Get first occurence of parent transform.
	/*!
	Use this to get hold of a parent transform somewhere in the parent tree.
	*/
	GZ_GRAPH_EXPORT static gzTransform * getClosestTransform(gzNode *node);
	
	//!Returns the accumulated transform for the node. 
	/*!
	This matrix transforms the node coordinates into world space coordinates. 

	Note that a shared transform only returns the first path of parent transforms.
	*/
	GZ_GRAPH_EXPORT static gzMatrix4 getAccumTransform(gzNode *node);

	// -------------- Node visibility extent -----------------------------
	//! Returns false if visibility extent not defined or infinite
	GZ_GRAPH_EXPORT virtual gzBool getVisibilityExtent(gzVec3 &min,gzVec3 &max) const override;


protected:

	gzMatrix4						m_currentTransformMatrix;
	gzFloat							m_maxScale;

	gzLateBindData<gzQuaternion>	m_rotation;
	gzLateBindData<gzVec3>			m_scale;
	gzLateBindData<gzVec3>			m_translation;
	gzLateBindData<gzVec3>			m_origo;
	gzLateBindData<gzMatrix3>		m_base;
	gzLateBindData<gzMatrix4>		m_transform;
	gzLateBindData<gzMatrix4>		m_preMultTransform;

	gzUInt32						m_baseID;

	gzUByte							m_accum;
	gzBool							m_isActive;

};

// Declare smart pointer type
GZ_DECLARE_REFPTR(gzTransform);

//******************************************************************************
// Class	: gzFrameTransformKeyTranslation
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981209	Created 
//									
//******************************************************************************
//!Used to store internal translation information for key frame animations.
class gzFrameTransformKeyTranslation : public gzReference , public gzSerializeData
{
public:
	//! Default constructor
	GZ_GRAPH_EXPORT gzFrameTransformKeyTranslation();

	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzFrameTransformKeyTranslation();
	
	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// --------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

private:
	friend class gzFrameTransform;

	gzUInt32	m_frame;
	gzVec3		m_position;
};

//******************************************************************************
// Class	: gzFrameTransformKeyScale
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981209	Created 
//									
//******************************************************************************
//!Used to store internal scale information for key frame animations.
class gzFrameTransformKeyScale : public gzReference
{
public:

	//! Default constructor
	GZ_GRAPH_EXPORT gzFrameTransformKeyScale();

	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzFrameTransformKeyScale();

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// --------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

private:
	friend class gzFrameTransform;

	gzUInt32	m_frame;
	gzVec3		m_scale;
};

//******************************************************************************
// Class	: gzFrameTransformKeyRotation
//									
// Purpose  : -
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981209	Created 
//									
//******************************************************************************
//!Used to store internal rotation information for key frame animations.
class gzFrameTransformKeyRotation : public gzReference
{
public:
	//! Default constructor
	GZ_GRAPH_EXPORT gzFrameTransformKeyRotation();

	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzFrameTransformKeyRotation();

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// --------- Serializing -------------------------------------------

	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT virtual gzVoid pushBack(gzSerializeAdapter *adapter);
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const;

private:
	friend class gzFrameTransform;

	gzUInt32		m_frame;
	gzQuaternion	m_rotation;
};

//! Diffenrent types of interpolation between frames

enum gzFrameTransformInterpolation
{
	GZ_FRAME_TRANSFORM_INTERPOLATION_STEP,
	GZ_FRAME_TRANSFORM_INTERPOLATION_LINEAR,
	GZ_FRAME_TRANSFORM_INTERPOLATION_CUBIC,
};

//******************************************************************************
// Class	: gzFrameTransform
//									
// Purpose  : Frame programmable transforms
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	981209	Created 
//									
//******************************************************************************
//!Key frame based transform. 
/*!
The gzFrameTransform class interpolates a gzTransform from a set om key frame parameters such
as scale, rotation and translation.
*/
class gzFrameTransform : public gzTransform
{
public:
	//! Default constructor
	/*!
	The frame transform is used to setup key framed transforms.
	The frame transforms interpolates between two frames and calculates the correct transform 
	based on quaternions.

	If is possible to set a name for the frame transform.
	*/
	GZ_GRAPH_EXPORT gzFrameTransform(const gzString & name=GZ_EMPTY_STRING);
	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzFrameTransform(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	//!Copy constructor. 
	GZ_GRAPH_EXPORT gzFrameTransform(const gzFrameTransform &copy);
	
	//!Assignment operator.
	GZ_GRAPH_EXPORT gzFrameTransform & operator=(const gzFrameTransform &copy);

	// ---------- Common graph functions --------------------------------

	//!Updates the boundary for the frame transform. 
	/*!
	The boundary surrounds the frame transform and all its children.
	It is usually called by the system when the scene graph needs an update.
	*/
	GZ_GRAPH_EXPORT virtual gzVoid updateNode() override;

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Action Interface --------------------------------------

	//!Called by the traversal process.
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- gzFrameTransform Interface ----------------------------
	
	//!Returns the start frame of the key animation.
	GZ_GRAPH_EXPORT gzUInt32 getStartFrame();
	//!Returns the last frame of the key animation.
	GZ_GRAPH_EXPORT gzUInt32 getLastFrame();
	//!Returns true if there are active key frames.
	GZ_GRAPH_EXPORT gzBool	hasFrames();

	//!Returns the transform for the frame transform. 
	/*!
	If the frame transform is missing it returns the transform of the previous defined transform.
	*/
	GZ_GRAPH_EXPORT gzMatrix4 getFrameTransform(gzUInt32 frame );

	//!Sets translation for a specific frame to x, y, z.
	GZ_GRAPH_EXPORT gzVoid setFrameTranslation(gzUInt32 frame , gzFloat x , gzFloat y , gzFloat z ); 

	//!Sets translation for a specific frame to gzVec3(x, y, z).
	GZ_GRAPH_EXPORT gzVoid setFrameTranslation(gzUInt32 frame, const gzVec3 &translation);
	
	//!Scales a specific frame to sx, sy, sz.
	GZ_GRAPH_EXPORT gzVoid setFrameScale(gzUInt32 frame , gzFloat sx , gzFloat sy , gzFloat sz ); 

	//!Scales a specific frame to gzVec3(sx, sy, sz).
	GZ_GRAPH_EXPORT gzVoid setFrameScale(gzUInt32 frame, const gzVec3& scale);
	
	//!Rotates a specific frame angle degrees around the vector.
	GZ_GRAPH_EXPORT gzVoid setFrameRotation(gzUInt32 frame , const gzVec3 &vector , gzFloat angle); 

	//!	Sets the heading, pitch roll for the frame. 
	/*!
	Sets the transform with a rotation around the Y axis in heading degress clockwise, elevates the z axis in 
	pitch degrees and tilts the head roll degrees.

	XXX The base vector is used for ? 
	*/
	GZ_GRAPH_EXPORT gzVoid setFrameHPR(gzUInt32 frame , gzFloat heading , gzFloat pitch , gzFloat roll , const gzVec3 &base=GZ_ONE_VEC3);
	
	//! Reset the transform for a specific fram to a user defined transform. 
	/*!
	Replaces all previous setFrameXXX commands. 
	*/
	GZ_GRAPH_EXPORT gzVoid setFrameRotateTransform(gzUInt32 frame , const gzMatrix4 & transform);

	GZ_GRAPH_EXPORT gzVoid setFrameRotation(gzUInt32 frame, const gzQuaternion& rotation);

	//! Returns TRUE if frame value is found
	GZ_GRAPH_EXPORT gzBool getFrameTranslation(gzUInt32 frame , gzFloat &x , gzFloat &y , gzFloat &z ); 
	
	//! Returns TRUE if frame value is found
	GZ_GRAPH_EXPORT gzBool getFrameScale(gzUInt32 frame , gzFloat &x , gzFloat &y , gzFloat &z ); 
	
	//! Returns TRUE if frame value is found
	GZ_GRAPH_EXPORT gzBool getFrameRotation(gzUInt32 frame , gzVec3 &vector , gzFloat &angle); 

	//! Returns TRUE if frame value is found
	GZ_GRAPH_EXPORT gzBool getFrameRotation(gzUInt32 frame, gzQuaternion& rotation);

	//!Returns the index of the start translation frame.
	GZ_GRAPH_EXPORT gzUInt32 getStartTranslationFrame();

	//!Returns the index of the next translation frame.
	GZ_GRAPH_EXPORT gzUInt32 getNextTranslationFrame(gzUInt32 current);
	
	//!Returns the index of the last translation frame
	GZ_GRAPH_EXPORT gzUInt32 getLastTranslationFrame();
	
	//!Returns TRUE if translation frames exist, otherwise FALSE:
	GZ_GRAPH_EXPORT gzBool	hasTranslationFrames();


	//!Returns the index of the start scaling frame.
	GZ_GRAPH_EXPORT gzUInt32 getStartScaleFrame();
	
	//!Returns the index of the next scale frame.
	GZ_GRAPH_EXPORT gzUInt32 getNextScaleFrame(gzUInt32 current);

	//!Returns the index of the last scaling frame.
	GZ_GRAPH_EXPORT gzUInt32 getLastScaleFrame();
	
	//!Returns TRUE if scaling frames exist, otherwise FALSE.
	GZ_GRAPH_EXPORT gzBool	hasScaleFrames();


	//!Returns the index of the start rotation frame.
	GZ_GRAPH_EXPORT gzUInt32 getStartRotationFrame();
	
	//!Returns the index of the next rotation frame.
	GZ_GRAPH_EXPORT gzUInt32 getNextRotationFrame(gzUInt32 current);

	//!Returns the index of the last rotation frame.
	GZ_GRAPH_EXPORT gzUInt32 getLastRotationFrame();
	
	//!Returns TRUE if rotation frames exist, otherwise FALSE.
	GZ_GRAPH_EXPORT gzBool	hasRotationFrames();
	
	//!Sets the mode for various interpolations
	GZ_PROPERTY_EXPORT(gzFrameTransformInterpolation, Interpolation, GZ_GRAPH_EXPORT);

	//!Sets the mode shortest path interp between quats
	GZ_PROPERTY_EXPORT(gzBool, UseShortestPath, GZ_GRAPH_EXPORT);

	//! Must be called to enable accumulated rotations.
	GZ_GRAPH_EXPORT gzVoid calculateAccumulatedRotations();

	//! Enable/Disable frame control
	GZ_GRAPH_EXPORT gzVoid enableFrameUpdates(gzBool on=TRUE);

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;


private:

	gzBoundary getFrameBoundary(gzUInt32 frame);

	gzRefDList<gzFrameTransformKeyTranslation>	m_keyListTranslation;
	gzRefDList<gzFrameTransformKeyScale>		m_keyListScale;
	gzRefDList<gzFrameTransformKeyRotation>		m_keyListRotation;

	gzDListIterator<gzFrameTransformKeyTranslation>	m_currentKeyTranslation;
	gzDListIterator<gzFrameTransformKeyScale>		m_currentKeyScale;
	gzDListIterator<gzFrameTransformKeyRotation>	m_currentKeyRotation;

	gzDListIterator<gzFrameTransformKeyTranslation>	m_currentNextKeyTranslation;
	gzDListIterator<gzFrameTransformKeyScale>		m_currentNextKeyScale;
	gzDListIterator<gzFrameTransformKeyRotation>	m_currentNextKeyRotation;


	gzFrameTransformKeyTranslation	*getKeyTranslation(gzUInt32 frame);
	gzFrameTransformKeyScale		*getKeyScale(gzUInt32 frame);
	gzFrameTransformKeyRotation		*getKeyRotation(gzUInt32 frame);

	gzFrameTransformKeyTranslation	*getNextKeyTranslation(gzUInt32 frame);
	gzFrameTransformKeyScale		*getNextKeyScale(gzUInt32 frame);
	gzFrameTransformKeyRotation		*getNextKeyRotation(gzUInt32 frame);

	gzBool	m_isFrameUpdateEnabled;
};

GZ_DECLARE_REFPTR(gzFrameTransform);


//******************************************************************************
// Class	: gzTransformBase
//									
// Purpose  : reset the base id and the base id count for transforms
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040803	Created 
//									
//******************************************************************************
//! Set the base transform index for skinning etc.
/*!
Transforms can be index by a ID under a gzTransformBase. 
All transforms under a gzBaseTransform are related to each other.
*/
class gzTransformBase : public gzGroup
{
public:
	//! Default constructor
	/*!
	If is possible to set a name for the transform base.
	*/
	GZ_GRAPH_EXPORT gzTransformBase(const gzString & name=GZ_EMPTY_STRING);
	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzTransformBase(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- Action Interface --------------------------------------

	//!Called in the traversal process.
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	//!Called in the traversal process.
	GZ_GRAPH_EXPORT virtual gzVoid postTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Render control -----------------------------------------------
	//! Used by the traversal process to activate a certain transform base.
	/*!
	No need to normally use this function. The transform base connected to index is activated.
	*/
	GZ_GRAPH_EXPORT	static gzVoid activateIndex( gzContext *context , gzUInt32 index);

	//!Used by the traversal process to reset all traversal transform base info.
	/*!
	No need to use this in your normal application.
	*/
	GZ_GRAPH_EXPORT static gzVoid resetIndex( gzContext *context );


	// ---------- Interface ----------------------------------------------------

	//!Sets the number of based indexed transforms that can be used under the base transform.
	GZ_GRAPH_EXPORT gzVoid	setNumberOfBases(gzUInt32 count=0);

	//!Returns the number of based indexed transforms that can be used under the base transform.
	GZ_GRAPH_EXPORT gzUInt32 getNumberOfBases();

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;


private:

	gzUInt32		m_numberOfBases;
};


//******************************************************************************
// Class	: gzTransformID
//									
// Purpose  : Used by the gzBaseTransform to keep track of transform IDs
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040803	Created 
//									
//******************************************************************************
//!Used by the gzBaseTransform to keep track of transform IDs
class gzTransformID
{
public:

	gzTransformID():currentTransformIndex(0),
					numberOfBases(0),
					accumTransformChecksum(0),
					transformChecksum(0),
					currentTransformChecksum(0),
					changedMatrix(TRUE),
					hasNormal(FALSE){};
	
	gzUInt32		currentTransformIndex;
	gzUInt32		numberOfBases;
	gzUInt32		accumTransformChecksum;
	gzUInt32		transformChecksum;
	gzUInt32		currentTransformChecksum;

	gzBool		changedMatrix;
	gzBool		hasNormal;
	

	gzMatrix4	mat;
	gzMatrix4	norm;
};

// ------------------------ gzRotor --------------------------------------

//******************************************************************************
// Class	: gzRotor
//									
// Purpose  : Performs a basic rotation depending on gzFrame
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	140819	Created 
//									
//******************************************************************************
//!Simple rotation engine
class gzRotor : public gzTransform
{
public:
	//! Default constructor
	/*!
		If is possible to set a name for the rotor
	*/
	GZ_GRAPH_EXPORT gzRotor(const gzString & name=GZ_EMPTY_STRING);
	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzRotor(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Called in the traversal process.
	GZ_GRAPH_EXPORT virtual gzVoid preTraverseAction( gzTraverseAction *actionclass , gzContext *context) override;

	// ---------- Serializing -------------------------------------------
	GZ_GRAPH_EXPORT virtual gzVoid write(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzVoid read(gzSerializeAdapter *adapter) override;
	GZ_GRAPH_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter *adapter) const override;

	// ---------- Properties --------------------------------------------

	GZ_PROPERTY_EXPORT(gzVec3,	RotationAxis,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,	Speed,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzBool,	Running,		GZ_GRAPH_EXPORT);
};


#endif
