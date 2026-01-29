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
// File			: gzVertexInterp.h
// Module		: 
// Description	: Class definition of the interpolation types
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
// AMO	021010	Created file 	
//
//******************************************************************************
#ifndef __GZ_VERTEX_INTERP_H__
#define __GZ_VERTEX_INTERP_H__

/*!	\file 
	\brief Vertex interpolations

*/

#include "gzNodeAction.h"

// --------------------- Vertex position ---------------------------------------

//******************************************************************************
// Class	: gzFrameCoordinate
//									
// Purpose  : Container for interpolated vertices
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021016	Created 
//									
//******************************************************************************
class gzFrameCoordinate : public gzReference
{
public:

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	GZ_GRAPH_EXPORT virtual ~gzFrameCoordinate();

private:

	gzFrameCoordinate();

	friend class gzCoordinateInterpolator;

	gzUInt32				m_frame;
	gzArray<gzVec3>		m_data;
};

//******************************************************************************
// Class	: gzCoordinateInterpolator
//									
// Purpose  : Interpolates coordinate arrayers for a gzGeometry based on frame
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021016	Created 
//									
//******************************************************************************
class gzCoordinateInterpolator : public gzNodeAction
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzCoordinateInterpolator(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzCoordinateInterpolator();

	GZ_GRAPH_EXPORT gzCoordinateInterpolator(const gzCoordinateInterpolator &copy);

	GZ_GRAPH_EXPORT gzCoordinateInterpolator & operator=(const gzCoordinateInterpolator &copy);

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass,gzVoid *userdata) override;


	// ---------- gzCoordinateInterpolator Interface ----------------------------

	GZ_GRAPH_EXPORT gzVoid	setNumberOfFrames( gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getNumberOfFrames();

	GZ_GRAPH_EXPORT gzVoid	setStartFrameOffset( gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getStartFrameOffset();

	//! Set the coordinate array for a certian frame
	GZ_GRAPH_EXPORT gzVoid setFrameArray(gzUInt32 frame , const gzArray<gzVec3> & array ); 

	//! Returns TRUE if frame value found
	GZ_GRAPH_EXPORT gzBool getFrameArray(gzUInt32 frame , gzArray<gzVec3> & array ); 

	//! Must do this to update boundary after you have changed the frame array data
	GZ_GRAPH_EXPORT gzVoid	calculateBoundary();


private:

	gzUInt32	m_startFrameOffset;		// start frame number
	gzUInt32	m_numberOfFrames;		// default 1 frame active

	gzRefDList< gzFrameCoordinate >			m_keyListArray;

	gzDListIterator< gzFrameCoordinate >	m_currentKeyArray;

	gzDListIterator< gzFrameCoordinate >	m_currentNextKeyArray;

	gzFrameCoordinate						*getKeyArray(gzUInt32 frame);
	gzFrameCoordinate						*getNextKeyArray(gzUInt32 frame);

	gzBoundary								m_boundary;

};

// --------------------- Vertex color ------------------------------------------

//******************************************************************************
// Class	: gzFrameColor
//									
// Purpose  : Container for interpolated vertice colors
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021016	Created 
//									
//******************************************************************************
class gzFrameColor : public gzReference
{
public:

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	GZ_GRAPH_EXPORT virtual ~gzFrameColor();

private:

	gzFrameColor();

	friend class gzColorInterpolator;

	gzUInt32				m_frame;
	gzArray<gzVec4>		m_data;
};

//******************************************************************************
// Class	: gzColorInterpolator
//									
// Purpose  : Interpolates color arrays for a gzGeometry based on frame
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021016	Created 
//									
//******************************************************************************
class gzColorInterpolator : public gzNodeAction
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzColorInterpolator(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzColorInterpolator();

	GZ_GRAPH_EXPORT gzColorInterpolator(const gzColorInterpolator &copy);

	GZ_GRAPH_EXPORT gzColorInterpolator & operator=(const gzColorInterpolator &copy);

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass,gzVoid *userdata) override;


	// ---------- gzColorInterpolator Interface ----------------------------

	GZ_GRAPH_EXPORT gzVoid	setNumberOfFrames( gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getNumberOfFrames();

	GZ_GRAPH_EXPORT gzVoid	setStartFrameOffset( gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getStartFrameOffset();

	//! Set the coordinate array for a certian frame
	GZ_GRAPH_EXPORT gzVoid setFrameArray(gzUInt32 frame , const gzArray<gzVec4> & array ); 

	//! Returns TRUE if frame value found
	GZ_GRAPH_EXPORT gzBool getFrameArray(gzUInt32 frame , gzArray<gzVec4> & array ); 


private:

	gzUInt32	m_startFrameOffset;			// start frame number
	gzUInt32	m_numberOfFrames;			// default 1 frame active

	gzRefDList< gzFrameColor >			m_keyListArray;

	gzDListIterator< gzFrameColor >		m_currentKeyArray;

	gzDListIterator< gzFrameColor >		m_currentNextKeyArray;

	gzFrameColor						*getKeyArray(gzUInt32 frame);
	gzFrameColor						*getNextKeyArray(gzUInt32 frame);
};

// --------------------- Vertex texcoord ------------------------------------------

//******************************************************************************
// Class	: gzFrameTexCoord
//									
// Purpose  : Container for interpolated vertice texture coordinates
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021016	Created 
//									
//******************************************************************************
class gzFrameTexCoord : public gzReference
{
public:

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	GZ_GRAPH_EXPORT virtual ~gzFrameTexCoord();

private:

	gzFrameTexCoord();

	friend class gzTexCoordInterpolator;

	gzUInt32				m_frame;
	gzArray<gzVec2>		m_data;
};

//******************************************************************************
// Class	: gzTexCoordInterpolator
//									
// Purpose  : Interpolates tex coord arrays for a gzGeometry based on frame
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021016	Created 
//									
//******************************************************************************
class gzTexCoordInterpolator : public gzNodeAction
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzTexCoordInterpolator(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzTexCoordInterpolator();

	GZ_GRAPH_EXPORT gzTexCoordInterpolator(const gzTexCoordInterpolator &copy);

	GZ_GRAPH_EXPORT gzTexCoordInterpolator & operator=(const gzTexCoordInterpolator &copy);

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass,gzVoid *userdata) override;


	// ---------- gzTexCoordInterpolator Interface ----------------------------

	GZ_GRAPH_EXPORT gzVoid	setNumberOfFrames( gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getNumberOfFrames();

	GZ_GRAPH_EXPORT gzVoid	setStartFrameOffset( gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getStartFrameOffset();

	//! Set the coordinate array for a certian frame
	GZ_GRAPH_EXPORT gzVoid setFrameArray(gzUInt32 frame , const gzArray<gzVec2> & array ); 

	//! Returns TRUE if frame value found
	GZ_GRAPH_EXPORT gzBool getFrameArray(gzUInt32 frame , gzArray<gzVec2> & array ); 


private:

	gzUInt32	m_startFrameOffset;			// start frame number
	gzUInt32	m_numberOfFrames;			// default 1 frame active

	gzRefDList< gzFrameTexCoord >			m_keyListArray;

	gzDListIterator< gzFrameTexCoord >		m_currentKeyArray;

	gzDListIterator< gzFrameTexCoord >		m_currentNextKeyArray;

	gzFrameTexCoord							*getKeyArray(gzUInt32 frame);
	gzFrameTexCoord							*getNextKeyArray(gzUInt32 frame);
};

// --------------------- Vertex normals ------------------------------------------

//******************************************************************************
// Class	: gzFrameNormal
//									
// Purpose  : Container for interpolated vertice normals 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021016	Created 
//									
//******************************************************************************
class gzFrameNormal : public gzReference
{
public:

	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	GZ_GRAPH_EXPORT virtual ~gzFrameNormal();

private:

	gzFrameNormal();

	friend class gzNormalInterpolator;

	gzUInt32				m_frame;
	gzArray<gzVec3>		m_data;
};

//******************************************************************************
// Class	: gzNormalInterpolator
//									
// Purpose  : Interpolates normal arrays for a gzGeometry based on frame
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	021016	Created 
//									
//******************************************************************************
class gzNormalInterpolator : public gzNodeAction
{
public:
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface

	GZ_GRAPH_EXPORT gzNormalInterpolator(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzNormalInterpolator();

	GZ_GRAPH_EXPORT gzNormalInterpolator(const gzNormalInterpolator &copy);

	GZ_GRAPH_EXPORT gzNormalInterpolator & operator=(const gzNormalInterpolator &copy);

	GZ_GRAPH_EXPORT	virtual gzVoid onAction(gzNodeActionEvent action , gzContext *context , gzNodeActionProvider *trigger ,gzTraverseAction *actionclass,gzVoid *userdata) override;


	// ---------- gzTexCoordInterpolator Interface ----------------------------

	GZ_GRAPH_EXPORT gzVoid	setNumberOfFrames( gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getNumberOfFrames();

	GZ_GRAPH_EXPORT gzVoid	setStartFrameOffset( gzUInt32 count);
	GZ_GRAPH_EXPORT gzUInt32 getStartFrameOffset();

	//! Set the coordinate array for a certian frame
	GZ_GRAPH_EXPORT gzVoid setFrameArray(gzUInt32 frame , const gzArray<gzVec3> & array ); 

	//! Returns TRUE if frame value found
	GZ_GRAPH_EXPORT gzBool getFrameArray(gzUInt32 frame , gzArray<gzVec3> & array ); 


private:

	gzUInt32	m_startFrameOffset;			// start frame number
	gzUInt32	m_numberOfFrames;			// default 1 frame active

	gzRefDList< gzFrameNormal >			m_keyListArray;

	gzDListIterator< gzFrameNormal >	m_currentKeyArray;
	gzDListIterator< gzFrameNormal >	m_currentNextKeyArray;

	gzFrameNormal						*getKeyArray(gzUInt32 frame);
	gzFrameNormal						*getNextKeyArray(gzUInt32 frame);
};

#endif

