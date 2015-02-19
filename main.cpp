#include "View.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>

int main()
{
	::srand((unsigned)::time(nullptr));

	sf::RenderWindow window(sf::VideoMode(1024, 768, 32), "Wombedit");
	window.setFramerateLimit(30);

	View view;
	sf::Clock clock;

	glEnable(GL_DEPTH_TEST);

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
			       window.close();
				else 
					view.OnKeyPressed(event.key.code);
        }

	    float tDelta = clock.restart().asSeconds();

		view.Update(tDelta);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto sz = window.getSize();
		glViewport(0, 0, sz.x, sz.y);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, sz.x / (double)sz.y, 1, 1000);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		view.Draw(window);

		window.display();
    }

    return EXIT_SUCCESS;
}
