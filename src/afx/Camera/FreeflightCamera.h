#pragma once

#include <afx/Camera/Camera.h>

//#include <afx/Events/Events.h>

#include <afx/Math/Transform.h>
#include <afx/Math/Vector3.h>
#include <afx/Math/Vector2.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace afx {

///////////////////////////////////////////////////////////////////////////////////////

class FreeflightCamera : public iCamera
{

public:

	FreeflightCamera( CameraType _type, float _fov = 60.0f, float _near = 0.1f, float _far = 500.0f );

	~FreeflightCamera() { }

	void onCreate() override;

	void handleInput();
	void update( double _delta_time ) override;

	void resetVelocity() { m_velocity = { 0.0f, 0.0f, 0.0f }; }

///////////////////////////////////////////////////////////////////////////////////////

private:

	//cMouseEventListener m_mouseListener;
	//cInputEventListener m_inputListener;

	afx::Vector3f m_move;
	afx::Vector2f m_rotate;
	afx::Vector3f m_velocity;

	bool m_freecam_enabled = false;

	float m_speed = 100.0f;
	float m_speed_normal = 100.0f;

};

}

