#include "Game.h"

bool updatable = false;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube"),
	m_startPoints{
		{ -1, -1, 1 },
		{ -1, 1, 1 },
		{ 1, 1, 1 },
		{ 1, -1, 1 },
		{ -1, -1, -1 },
		{ -1, 1, -1 },
		{ 1, 1, -1 },
		{ 1, -1, -1 }
	}
{
	for (int i = 0; i < 8; i++)
	{
		m_points[i] = m_startPoints[i];
	}

	index = glGenLists(1);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::W)
				{
					m_scale += 0.05f;
				}
				else if (event.key.code == Keyboard::S)
				{
					m_scale -= 0.05f;
				}

				else if (event.key.code == Keyboard::I)
				{
					m_displacementVec.y += 0.05f;
				}
				else if (event.key.code == Keyboard::K)
				{
					m_displacementVec.y -= 0.05f;
				}
				else if (event.key.code == Keyboard::J)
				{
					m_displacementVec.x -= 0.05f;
				}
				else if (event.key.code == Keyboard::L)
				{
					m_displacementVec.x += 0.05f;
				}
				
				else if (event.key.code == Keyboard::X)
				{
					m_rotationX += 0.05f;

					if (m_rotationX > 360.f)
					{
						m_rotationX -= 360.f;
					}
				}
				else if (event.key.code == Keyboard::Y)
				{
					m_rotationY += 0.05f;

					if (m_rotationY > 360.f)
					{
						m_rotationY -= 360.f;
					}
				}
				else if (event.key.code == Keyboard::Z)
				{
					m_rotationZ += 0.05f;

					if (m_rotationZ > 360.f)
					{
						m_rotationZ -= 360.f;
					}
				}
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	newFaceList();

}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}

	for (int i = 0; i < 8; i++)
	{
		m_points[i] = MyMatrix3::rotationY(m_rotationY) * m_startPoints[i];
		m_points[i] = MyMatrix3::rotationX(m_rotationX) * m_points[i];
		m_points[i] = MyMatrix3::rotationZ(m_rotationZ) * m_points[i];
		m_points[i] = MyMatrix3::scale(m_scale) * m_points[i];
		m_points[i] += m_displacementVec;
	}
}

void Game::draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	newFaceList();

	glCallList(1);

	window.display();

}

void Game::newFaceList()
{
	glDeleteLists(1, 1);

	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(m_points[4].x, m_points[4].y, m_points[4].z);
		glVertex3f(m_points[5].x, m_points[5].y, m_points[5].z);
		glVertex3f(m_points[6].x, m_points[6].y, m_points[6].z);
		glVertex3f(m_points[7].x, m_points[7].y, m_points[7].z);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(m_points[0].x, m_points[0].y, m_points[0].z);
		glVertex3f(m_points[4].x, m_points[4].y, m_points[4].z);
		glVertex3f(m_points[7].x, m_points[7].y, m_points[7].z);
		glVertex3f(m_points[3].x, m_points[3].y, m_points[3].z);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(m_points[0].x, m_points[0].y, m_points[0].z);
		glVertex3f(m_points[4].x, m_points[4].y, m_points[4].z);
		glVertex3f(m_points[5].x, m_points[5].y, m_points[5].z);
		glVertex3f(m_points[1].x, m_points[1].y, m_points[1].z);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(m_points[1].x, m_points[1].y, m_points[1].z);
		glVertex3f(m_points[5].x, m_points[5].y, m_points[5].z);
		glVertex3f(m_points[6].x, m_points[6].y, m_points[6].z);
		glVertex3f(m_points[2].x, m_points[2].y, m_points[2].z);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(m_points[2].x, m_points[2].y, m_points[2].z);
		glVertex3f(m_points[6].x, m_points[6].y, m_points[6].z);
		glVertex3f(m_points[7].x, m_points[7].y, m_points[7].z);
		glVertex3f(m_points[3].x, m_points[3].y, m_points[3].z);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(m_points[3].x, m_points[3].y, m_points[3].z);
		glVertex3f(m_points[7].x, m_points[7].y, m_points[7].z);
		glVertex3f(m_points[4].x, m_points[4].y, m_points[4].z);
		glVertex3f(m_points[0].x, m_points[0].y, m_points[0].z);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(m_points[0].x, m_points[0].y, m_points[0].z);
		glVertex3f(m_points[1].x, m_points[1].y, m_points[1].z);
		glVertex3f(m_points[2].x, m_points[2].y, m_points[2].z);
		glVertex3f(m_points[3].x, m_points[3].y, m_points[3].z);

	}
	glEnd();
	glEndList();
}

