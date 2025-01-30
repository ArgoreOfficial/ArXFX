#include "Camera.h"

//#include <afx/Engine/Engine.h>
//#include <afx/Device/DeviceContext.h>
//#include <afx/Graphics/Graphics.h>
//#include <afx/Graphics/GPUBuffer.h>

///////////////////////////////////////////////////////////////////////////////////////

afx::iCamera::iCamera( CameraType _type, float _fov, float _near, float _far ) :
	m_type{ _type },
	fov{ _fov },
	m_near{ _near },
	m_far{ _far }
{
	/*
	iLowLevelGraphics* pGraphics = cEngine::get()->graphics;

	sGPUBufferDesc ubDesc;
	ubDesc.name  = "UbCameraData";
	ubDesc.size  = sizeof( sUbCameraData );
	ubDesc.type  = WV_BUFFER_TYPE_UNIFORM;
	ubDesc.usage = WV_BUFFER_USAGE_DYNAMIC_DRAW;

	m_uniformBufferID = pGraphics->createGPUBuffer( 0, &ubDesc );
	*/
}

///////////////////////////////////////////////////////////////////////////////////////

	/*
bool afx::iCamera::beginRender( iLowLevelGraphics* _pLowLevelGraphics, eFillMode _fillMode )
{
	if ( !_pLowLevelGraphics->m_uniformBindingNameMap.contains( "UbCameraData" ) )
		return false;

	_pLowLevelGraphics->setFillMode( _fillMode );

	sUbCameraData instanceData;
	instanceData.projection = getProjectionMatrix();
	instanceData.view       = getViewMatrix();
	instanceData.model      = afx::Matrix4x4f( 1.0f );

	/// TODO: rename UbCameraData to UbCameraData?
	BufferBindingIndex index = _pLowLevelGraphics->m_uniformBindingNameMap.at( "UbCameraData" );
	_pLowLevelGraphics->bufferSubData( m_uniformBufferID, &instanceData, sizeof( sUbCameraData ), 0 );

	return true;
}
	*/

afx::Matrix4x4f afx::iCamera::getProjectionMatrix( void )
{
	switch( m_type )
	{
	case WV_CAMERA_TYPE_PERSPECTIVE:  return getPerspectiveMatrix (); break;
	case WV_CAMERA_TYPE_ORTHOGRAPHIC: return getOrthographicMatrix(); break;
	}

	return Matrix4x4f{ 1.0f };
}

///////////////////////////////////////////////////////////////////////////////////////

afx::Matrix4x4f afx::iCamera::getPerspectiveMatrix()
{
	float aspect = m_width / m_height;
	return MatrixUtil::perspective( 
		aspect, 
		Math::radians( fov ), 
		m_near, m_far 
	);
}

///////////////////////////////////////////////////////////////////////////////////////

afx::Matrix4x4f afx::iCamera::getOrthographicMatrix()
{
	return MatrixUtil::orthographic( 
		m_width  / 2.0f, 
		m_height / 2.0f, 
		-1000.0f, 1000.0f 
	);
}

///////////////////////////////////////////////////////////////////////////////////////

afx::Matrix4x4f afx::iCamera::getViewMatrix( void )
{
	return MatrixUtil::inverse( m_transform.getMatrix() );
}

///////////////////////////////////////////////////////////////////////////////////////

afx::Vector3f afx::iCamera::getViewDirection()
{
	float yaw   = Math::radians( m_transform.rotation.y - 90.0f );
	float pitch = Math::radians( m_transform.rotation.x );

	Vector3f direction;
	direction.x = std::cos( yaw ) * std::cos( pitch );
	direction.y = std::sin( pitch );
	direction.z = std::sin( yaw ) * std::cos( pitch );
    return direction;
}
