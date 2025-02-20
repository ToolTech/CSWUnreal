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
// File			: gzCamera.h
// Module		: 
// Description	: Class definition of the gzCamera class
// Author		: Anders Modén		
// Product		: Gizmo3D 2.12.222
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
// AMO	990101	Created file 	
//
//******************************************************************************
#ifndef __GZ_CAMERA_H__
#define __GZ_CAMERA_H__

/*!	\file 
	\brief Base definitions for cameras

*/


#include "gzObject.h"
#include "gzScene.h"
#include "gzMutex.h"

class gzCamera : public gzObject , public gzNameInterface ,public gzMutex
{
public:

	//! Default constructor
	/*!
	The camera is an abstract class. You need to specify a camera type when instantiating the camera.

	If is possible to set a name for the camera.
	*/
	GZ_GRAPH_EXPORT gzCamera( const gzString &name=GZ_EMPTY_STRING);
	
	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzCamera();

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_THREADSAFE_REF((*this));							// thread safe ref/unref when camera is locked

	// ------------------- default positioning ------------------------------------
	//!Sets the heading, pitch and roll value for the camera.
	/*!
	Default values are heading = 0, pitch = 0 and roll = 0.

	Each value is given in degrees.
	*/
	GZ_GRAPH_EXPORT gzVoid	setHPR( gzFloat heading , gzFloat pitch , gzFloat roll );
	//!	Sets the heading, pitch and roll using a gzVec3 with the new HPR values. 
	/*!
	Default values are heading = 0, pitch = 0 and roll = 0.

	The values are given in degrees.
	*/
	GZ_GRAPH_EXPORT gzVoid	setHPR( const gzVec3 &hpr );
	
	//!Gets the current HPR for the camera.
	/*!
	The current heading value for the camera is stored in the variable heading, 
	the current pitch is stored in variable pitch and the current roll is stored in variable roll.
	*/
	GZ_GRAPH_EXPORT gzVoid	getHPR( gzFloat &heading , gzFloat &pitch , gzFloat &roll );
	//!Returns the current HPR for the camera.
	GZ_GRAPH_EXPORT gzVec3	getHPR();

	//!	Sets the camera position.
	/*!
	Default position is (0, 0, 1).
	*/
	GZ_GRAPH_EXPORT gzVoid	setPosition( gzDouble x , gzDouble y , gzDouble z );
	
	//!Defines the point the camera looks at. 
	/*!
	When using this method the HPR is influenced. To get more control it is possible to set a custom value for the roll. 
	The vector which indicates what is up for the camera can also be specified. 
	*/
	GZ_GRAPH_EXPORT gzVoid	lookAt( gzDouble x , gzDouble y , gzDouble z , gzDouble roll=0 , const gzVec3 &up=gzVec3(0,1,0));

	//!	Sets the camera position.
	/*!
	Default position is (0, 0, 1).
	*/
	GZ_GRAPH_EXPORT gzVoid	setPosition( const gzVec3D &position );
	
	//!Defines the point the camera looks at. 
	/*!
	When using this method the HPR is influenced. To get more control it is possible to set a custom value for the roll. 
	The vector which indicates what is up for the camera can also be specified. 
	*/
	GZ_GRAPH_EXPORT gzVoid	lookAt( const gzVec3D &position , gzDouble roll=0 , const gzVec3 &up=gzVec3(0,1,0));

	GZ_GRAPH_EXPORT	gzVoid	useRoiPosition(gzBool on);
	GZ_GRAPH_EXPORT gzBool	useRoiPosition();

	// ------------------- distance and scene viewbox management ------------------
	//!Sets distance from camera to near clip plane.
	/*!
	The distance specify the distance from the camera to the near clip plane.
	Everything in front of the near clip plane is ignored when rendering the scene. 
	
	Default distance is 1.
	*/

	GZ_PROPERTY_EXPORT_V(gzFloat,	NearClipPlane,	GZ_GRAPH_EXPORT);

	//!Sets distance from camera to far clip plane.
	/*!
	The distance specify the distance from the camera to the far clip plane.
	Everything behind the near clip plane is ignored when rendering the scene. 

	Default distance is 500.
	*/

	GZ_PROPERTY_EXPORT_V(gzFloat,	FarClipPlane,	GZ_GRAPH_EXPORT);


	GZ_GRAPH_EXPORT gzVoid	flipVerticalView(gzBool on);
	GZ_GRAPH_EXPORT gzVoid	flipHorizontalView(gzBool on);

	//!Sets the scene the camera will observe.
	/*!
	One camera can only observe one scene, but a scene can be observed by several cameras.
	*/
	GZ_GRAPH_EXPORT gzVoid	setScene( gzScene *scene );
	
	//!Returns the scene connected to the camera.
	GZ_GRAPH_EXPORT gzScene *getScene() { return m_scene.get(); }

	//!Returns the camera position given in world coordinates.
	GZ_GRAPH_EXPORT const gzVec3D &getPosition() { return m_eye; }

	GZ_GRAPH_EXPORT gzVec3  getLocalPosition(); 

	//!Returns the viewing direction for the camera
	GZ_GRAPH_EXPORT gzVec3	getDirection();
	GZ_GRAPH_EXPORT gzVec3	getNormal();

	// ------------------- pure transform control ---------------------------------

	//!Sets the camera transform.
	GZ_GRAPH_EXPORT gzVoid	setTransform( const gzMatrix4 &transform);

	//!Returns the camera transform.
	GZ_GRAPH_EXPORT const gzMatrix4 &getTransform() const;

	//!Returns the camera projection transforms
	/*!
	Note that this function need to be specifyed if you create a custom camera type.
	*/
	GZ_GRAPH_EXPORT virtual gzMatrix4 getProjectionTransform() const =0;

	// ------------------- utility methods used by external renderers -----------------

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzVoid render(gzContext *context , gzUInt32 size_x , gzUInt32 size_y, gzUInt32 screen_width,gzTraverseAction *action);

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzBool isVisible( gzContext *context , gzNode *node  )=0;

	//! Utility to calculate distance from camera to node center
	GZ_GRAPH_EXPORT gzFloat distance( gzContext *context , gzNode *node  );

	//!Utility methods used by external renderers.
	/*!
	Controls if the node is further away than the far plane.

	Returns true if the node is behind the far plane otherwise false.
	*/
	GZ_GRAPH_EXPORT virtual gzBool isBeyondFarPlane( gzContext *context , gzNode *node  )=0;


	GZ_GRAPH_EXPORT gzVoid getScreenVectors(gzInt32 mouse_x, gzInt32 mouse_y, gzUInt32XY screen_size, gzVec3D &position, gzVec3 &direction) const;

	GZ_GRAPH_EXPORT static gzCamera* findCamera(gzString name, gzCamera* parent = NULL);

protected:
	
	GZ_GRAPH_EXPORT gzVoid	calculateTransform();

	gzVec3D					m_eye;

	gzFloat					m_eye_heading;
	gzFloat					m_eye_pitch;
	gzFloat					m_eye_roll;

	gzMatrix4				m_cameraMatrix;

	gzMatrix4				m_invCameraMatrix;

	gzRefPointer<gzScene>	m_scene;

	gzBool					m_useRoiPosition:1;
	gzBool					m_flipHorizontal:1;
	gzBool					m_flipVertical:1;
	
private:

	static gzMutex								  s_cameraLocker;
	static gzMemCheck<gzDict<gzString, gzCamera>> s_cameraDictionary;

};

GZ_DECLARE_REFPTR(gzCamera);

class gzPerspCamera : public gzCamera
{
public:

	//! Default constructor for a perspective camera
	/*!
	With a perspective camera objects far away seems to be smaller than objects near the camera.
	This is the way we experience things in real life. A long road seems to narrow off, trees near you
	seems to be higher than trees far away even if they have the same size. 
	
	An advantage with this camera is that it is easy to see which objects that are near the camera
	and which are far away. Relative dimensions are not preserved.

	If is possible to set a name for the perspective camera.
	*/	
	GZ_GRAPH_EXPORT gzPerspCamera(const gzString &name=GZ_EMPTY_STRING);

	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzPerspCamera(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface	
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzVoid render(gzContext *context , gzUInt32 size_x , gzUInt32 size_y, gzUInt32 screen_width, gzTraverseAction *action) override;

	//!Sets the vertical field of view for the camera.
	/*!
	The field of view is specified with an angle in degrees. 
	The fov value must be in the range of [0.0, 180,0]. 
	*/
	GZ_GRAPH_EXPORT gzVoid setVerticalFOV( gzFloat fov );	
	//!Sets the horizontal field of view for the camera.
	/*!
	The field of view is specified with an angle in degrees. 
	The fov value must be in the range of [0.0, 180,0]. 
	*/
	GZ_GRAPH_EXPORT gzVoid setHorizontalFOV( gzFloat fov );

	//!Returns the vertical field of view angle.
	GZ_GRAPH_EXPORT gzFloat getVerticalFOV();	
	//!Returns the horizontal field of view angle.
	GZ_GRAPH_EXPORT gzFloat getHorizontalFOV();

	//!Sets the side width of the view plane (half of total width).
	GZ_GRAPH_EXPORT gzVoid setWidth( gzFloat width );

	//!Sets the top height of the view plane. (half of the toal height)
	GZ_GRAPH_EXPORT gzVoid setHeight( gzFloat height );

	GZ_GRAPH_EXPORT const gzFloat &getWidth() const;
	GZ_GRAPH_EXPORT const gzFloat &getHeight() const;

	GZ_GRAPH_EXPORT const gzFloat &getWidthFactor() const;
	GZ_GRAPH_EXPORT const gzFloat &getHeightFactor() const;
	
	//!Utility methods used by external renderers.
	/*!
	Controls if the node is visible for the camera.
	
	A test is performed to see if the node is within the viewing frustrum.

	Returns true if the node is behind the far plane, in front of the near plane and 
	withing the field of view. Otherwise false is returned. 
	*/
	GZ_GRAPH_EXPORT virtual gzBool isVisible( gzContext *context , gzNode *node ) override;

	//!Utility methods used by external renderers.
	/*!
	Controls if the node is further away than the far plane.

	Returns true if the node is behind the far plane otherwise false.
	*/
	GZ_GRAPH_EXPORT virtual gzBool isBeyondFarPlane( gzContext *context , gzNode *node  ) override;

	//!Activates a far plane infinite far away.
	/*!
	The infinite far plane is disabled by default.
	*/
	GZ_GRAPH_EXPORT gzVoid	useInfiniteFarPlane(gzBool on);

	//!Returns the camera projection transform.
	/*!
	The projection transform transforms all coordinates from world space to clip space.
	*/
	GZ_GRAPH_EXPORT virtual gzMatrix4 getProjectionTransform() const override;

	GZ_GRAPH_EXPORT gzVoid setNearClipPlane(const gzFloat &near) override;


protected:
	
	gzFloat		m_width;
	gzFloat		m_height;

	gzFloat		m_vertical_FOV;
	gzFloat		m_horizontal_FOV;

	gzFloat		m_widthFactor;
	gzFloat		m_heightFactor;

	gzBool		m_useInfiniteFarPlane;
};

GZ_DECLARE_REFPTR(gzPerspCamera);

//------------------------------------------------------------------------------------

class gzScewCamera : public gzCamera
{
public:

	GZ_GRAPH_EXPORT gzScewCamera(const gzString &name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzScewCamera(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzVoid render(gzContext *context , gzUInt32 size_x , gzUInt32 size_y, gzUInt32 screen_width, gzTraverseAction *action) override;

	GZ_GRAPH_EXPORT virtual gzBool isVisible( gzContext *context , gzNode *node ) override;

	GZ_GRAPH_EXPORT virtual gzBool isBeyondFarPlane( gzContext *context , gzNode *node  ) override;

	GZ_GRAPH_EXPORT virtual gzMatrix4 getProjectionTransform() const override;

	GZ_PROPERTY_EXPORT_(gzFloat,	VerticalFOV,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT_(gzFloat,	HorizontalFOV,	GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,		Width,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,		Height,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzFloat,		Focus,			GZ_GRAPH_EXPORT);
	GZ_PROPERTY_EXPORT(gzVec3,		Displacement,	GZ_GRAPH_EXPORT);

protected:
	
	gzVec3		m_n1,m_n2,m_n3,m_n4;
	gzFloat		m_d1,m_d2,m_d3,m_d4;

};

GZ_DECLARE_REFPTR(gzScewCamera);

//----------------------------------------------------------------------------------

class gzOrthoCamera : public gzCamera
{
public:

	//! Default constructor
	/*!
	With this camera relative dimensions are preserved. This is useful when you want to 
	compare the size of two objects.

	If is possible to set a name for the orthographic camera.
	*/
	GZ_GRAPH_EXPORT gzOrthoCamera(const gzString &name=GZ_EMPTY_STRING);

	//! Destructor
	GZ_GRAPH_EXPORT virtual ~gzOrthoCamera(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface	
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzVoid render(gzContext *context , gzUInt32 size_x , gzUInt32 size_y, gzUInt32 screen_width, gzTraverseAction *action) override;

	//!Utility methods used by external renderers.
	/*!
	Controls if the node is visible for the camera.
	
	A test is performed to see if the node is within the viewing frustrum.

	Returns true if the node is behind the far plane, in front of the near plane and 
	withing the field of view. Otherwise false is returned. 
	*/
	GZ_GRAPH_EXPORT virtual gzBool isVisible( gzContext *context , gzNode *node ) override;

	//!Utility methods used by external renderers.
	/*!
	Controls if the node is further away than the far plane.
	
	Returns true if the node is behind the far plane otherwise false.
	*/
	GZ_GRAPH_EXPORT virtual gzBool isBeyondFarPlane( gzContext *context , gzNode *node  ) override;

	//!Sets the width for the near clipping plane.
	GZ_GRAPH_EXPORT gzVoid setWidth( gzFloat width );	
	//!Sets the height for the near clipping plane.
	GZ_GRAPH_EXPORT gzVoid setHeight( gzFloat height );

	//!Sets the magnification factor for the camera view.
	GZ_GRAPH_EXPORT gzVoid setMagnification( gzFloat mag );

	//!Returns the camera projection transform.
	/*!
	The projection transform transforms all coordinates from world space to clip space.
	*/
	GZ_GRAPH_EXPORT virtual gzMatrix4 getProjectionTransform() const override;

protected:

	gzFloat	m_width;
	gzFloat	m_height;

	gzFloat m_mag;

};

GZ_DECLARE_REFPTR(gzOrthoCamera);

// ---------------- gzGenericCamera ------------------

class gzGenericCamera : public gzCamera
{
public:

	//! Default constructor for a generic camera.
	/*!
	Define your own projection method for the camera.

	If is possible to set a name for the generic camera.
	*/
	GZ_GRAPH_EXPORT gzGenericCamera(const gzString &name=GZ_EMPTY_STRING);

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface	
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzVoid render(gzContext *context , gzUInt32 size_x , gzUInt32 size_y, gzUInt32 screen_width, gzTraverseAction *action) override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzBool isVisible( gzContext *context , gzNode *node ) override;

	//!Utility methods used by external renderers.
	/*!
	Controls if the node is further away than the far plane.

	Returns true if the node is behind the far plane otherwise false.
	*/
	GZ_GRAPH_EXPORT virtual gzBool isBeyondFarPlane( gzContext *context , gzNode *node  ) override;

    //!Sets projMat as projection transform for the camera.
	GZ_GRAPH_EXPORT virtual gzVoid setProjectionTransform( const gzMatrix4 &projMat );

	//!Returns the camera projection transform.
	/*!
	The projection transform transforms all coordinates from world space to clip space.
	*/
	GZ_GRAPH_EXPORT virtual gzMatrix4 getProjectionTransform() const override;

protected:

	gzMatrix4	m_projectionMatrix;
};

GZ_DECLARE_REFPTR(gzGenericCamera);

// ---------------- gzStereoCamera ------------------

class gzStereoCamera : public gzCamera
{
public:

	//! Default constructor
	/*!
	If is possible to set a name for the stereo camera.
	*/
	GZ_GRAPH_EXPORT gzStereoCamera(const gzString &name=GZ_EMPTY_STRING);

	//! Destructor	
	GZ_GRAPH_EXPORT virtual ~gzStereoCamera(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface	
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzVoid render(gzContext *context , gzUInt32 size_x , gzUInt32 size_y, gzUInt32 screen_width, gzTraverseAction *action) override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzBool isVisible( gzContext *context , gzNode *node ) override;

	//!Utility methods used by external renderers.
	/*!
	Controls if the node is further away than the far plane.

	Returns true if the node is behind the far plane otherwise false.
	*/
	GZ_GRAPH_EXPORT virtual gzBool isBeyondFarPlane( gzContext *context , gzNode *node  ) override;

	// ---------- Stereo specific methods -------------------------------

	//!Returns the left eye camera.
	GZ_GRAPH_EXPORT gzCamera *getLeftEyeCamera();
	//!Returns the right eye camera.
	GZ_GRAPH_EXPORT gzCamera *getRightEyeCamera();

	//!Sets a camera to be used as the left eye in stereo vision.
	GZ_GRAPH_EXPORT gzVoid	setLeftEyeCamera(gzCamera *camera);
	//!Sets a camera to be used as the right eye in stereo vision.
	GZ_GRAPH_EXPORT gzVoid	setRightEyeCamera(gzCamera *camera);

	//!Sets the camera as left and right camera.
	/*!
	The same camera is used as left and right eye.
	*/
	GZ_GRAPH_EXPORT gzVoid	setCamera(gzCamera *camera);

	//!Sets the distance between the two cameras.
	GZ_GRAPH_EXPORT	gzVoid	setEyeDistance(gzFloat dist);
	//!Sets the distance to the point of focus.
	GZ_GRAPH_EXPORT	gzVoid	setFocusDistance(gzFloat dist);

	//!Returns the camera projection transform.
	/*!
	The projection transform transforms all coordinates from world space to clip space.
	*/
	GZ_GRAPH_EXPORT virtual gzMatrix4 getProjectionTransform() const override;

	GZ_PROPERTY_EXPORT(gzBool,	UseDualDesktop,		GZ_GRAPH_EXPORT);

protected:

	gzRefPointer<gzCamera>		m_leftEyeCamera;
	gzRefPointer<gzCamera>		m_rightEyeCamera;

	gzFloat						m_eyeDistance;
	gzFloat						m_focusDistance;

private:

	gzCamera	*m_currentRenderCamera;
};

GZ_DECLARE_REFPTR(gzStereoCamera);

// ---------------- gzMultiLayerCamera ------------------

class gzMultiLayerInfo
{
public:

	gzMultiLayerInfo():	size(GZ_FLOAT_ONE,GZ_FLOAT_ONE),
						offset(GZ_FLOAT_ZERO,GZ_FLOAT_ZERO),
						clearStencil(TRUE),
						clearDepth(TRUE),
						clearColor(FALSE){}

	gzFloatXY				size;
	gzFloatXY				offset;
	gzBool					clearStencil;
	gzBool					clearDepth;
	gzBool					clearColor;

	gzRefPointer<gzCamera>	camera;
};

class gzMultiLayerCamera : public gzCamera
{
public:

	GZ_GRAPH_EXPORT gzMultiLayerCamera(const gzString &name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzMultiLayerCamera(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	// ---------- Clone interface ---------------------------------------
	//!Clone interface	
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzVoid render(gzContext *context , gzUInt32 size_x , gzUInt32 size_y, gzUInt32 screen_width, gzTraverseAction *action) override;

	//!Utility methods used by external renderers.
	GZ_GRAPH_EXPORT virtual gzBool isVisible( gzContext *context , gzNode *node ) override;

	GZ_GRAPH_EXPORT virtual gzBool isBeyondFarPlane( gzContext *context , gzNode *node  ) override;

	GZ_GRAPH_EXPORT virtual gzMatrix4 getProjectionTransform() const override;

	// ---------- gzMultiLayerCamera specific methods -------------------------------

	GZ_GRAPH_EXPORT gzVoid		setLayerCamera(gzUInt32 layer,gzCamera *camera);
	GZ_GRAPH_EXPORT gzCamera*	getLayerCamera(gzUInt32 layer);

	//! Relative offset of viewport -1 to +1. Larger numbers are treated as absolute pixel values
	GZ_GRAPH_EXPORT gzVoid		setLayerViewportOffset(gzUInt32 layer,gzFloat x , gzFloat y);

	//! Relative scale of viewport 0 to +1. Larger numbers are treated as absolute pixel values
	GZ_GRAPH_EXPORT gzVoid		setLayerViewportScale(gzUInt32 layer,gzFloat sx , gzFloat sy);

	GZ_GRAPH_EXPORT gzVoid		clearLayerDepthBuffer(gzUInt32 layer,gzBool on);
	GZ_GRAPH_EXPORT gzVoid		clearLayerStencilBuffer(gzUInt32 layer,gzBool on);
	GZ_GRAPH_EXPORT gzVoid		clearLayerColorBuffer(gzUInt32 layer,gzBool on);

protected:

	gzDynamicArray<gzMultiLayerInfo>		m_layerInfo;

private:

	gzCamera	*m_currentRenderCamera;
};

GZ_DECLARE_REFPTR(gzMultiLayerCamera);

#endif
