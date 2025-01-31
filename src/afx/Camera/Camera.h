#pragma once

#include <afx/Math/Transform.h>
#include <afx/Math/Vector3.h>
#include <afx/Math/Vector2.h>

//#include <wv/Decl.h>
#include <afx/Common.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace arc {

///////////////////////////////////////////////////////////////////////////////////////

class iLowLevelGraphics;

///////////////////////////////////////////////////////////////////////////////////////

class iCamera
{

//ARC_DECLARE_INTERFACE( iCamera )

public:

	enum CameraType
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	iCamera( CameraType _type, float _fov = 60.0f, float _near = 0.01f, float _far = 10000.0f );

	virtual void onCreate() { }
	virtual void update( double _delta_time ) { m_transform.update( nullptr ); }

	//bool beginRender( iLowLevelGraphics* _pLowLevelGraphics, eFillMode _fillMode );

	Matrix4x4f getProjectionMatrix( void );
	Matrix4x4f getViewMatrix( void );

	Transformf& getTransform( void ) { return m_transform; }
	Vector3f getViewDirection();

	BufferID getBufferID() { return m_uniformBufferID; }

///////////////////////////////////////////////////////////////////////////////////////

	float fov = 60.0f;

	float width = 1;
	float height = 1;

///////////////////////////////////////////////////////////////////////////////////////

protected:

	Matrix4x4f getPerspectiveMatrix();
	Matrix4x4f getOrthographicMatrix();

///////////////////////////////////////////////////////////////////////////////////////

	BufferID m_uniformBufferID;

	float m_near = 0.01f;
	float m_far = 100.0f;

	Transformf m_transform;
	CameraType m_type = PERSPECTIVE;
};

}

