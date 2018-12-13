#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "MyVector3.h"
#include "MyMatrix3.h"


using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void newFaceList();

	const MyVector3 m_startPoints[8];
	MyVector3 m_points[8];
	MyVector3 m_displacementVec{ 0, 0, -6 };

	GLuint index;
	Clock clock;
	Time elapsed;

	float m_scale = 1.0f;
	float m_rotationX = 0.0f;
	float m_rotationY = 0.0f;
	float m_rotationZ = 0.0f;
};