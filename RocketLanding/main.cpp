#include <SFML/Graphics.hpp>
#include<iostream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace sf;
using namespace std;

const int LANDING_FIELD_LENGTH = 50;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 500;
const float GRAVITY_ACCELERATION = 0.091;
const float AIR_RESISTANCE = 0.02;


struct Rocket 
{

	float x, y, fuel,
		velocityX, velocityY,
		sidePower, centralPower;

	Rocket(float x_ = 0, float y_ = 0, float fuel_ = 50) :
		x(x_), y(y_), fuel(fuel_), 
		velocityX(0), velocityY(0), 
		sidePower(0), centralPower(0) {}

	float getX() 
	{
		return x;
	}
	float getY() 
	{
		return y;
	}

	void setX(float coordinate) 
	{
		x = coordinate;
	}
	void setY(float coordinate) 
	{
		y = coordinate;
	}

	float getVelocityX() 
	{
		return velocityX;
	}

	float getVelocityY()
	{
		return velocityY;
	}

	void setVelocityX(float velocity) 
	{
		velocityX = velocity;
	}

	void setVelocityY(float velocity) 
	{
		velocityY = velocity;
	}

	float getFuel() 
	{
		return fuel;
	}
	void setFuel(float fuel_) 
	{
		fuel = fuel_;
	}

	float getSidePower() 
	{
		return sidePower;
	}

	float getCentralPower() 
	{
		return centralPower;
	}

	void setCentralPower(float power) 
	{
		centralPower = power;
	}

	void setSidePower(float power)
	{
		sidePower = power;
	}

};

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window( VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "RocketLanding");

	srand(static_cast<unsigned>(time(0)));
	int landingFieldPosition = rand() % ( WINDOW_WIDTH - LANDING_FIELD_LENGTH );


	Rocket rocket( WINDOW_WIDTH / 2 - 10, 10 );

	Texture RocketTexture;

	RocketTexture.loadFromFile("C:\\Users\\zarmm\\source\\repos\\RocketLanding\\images\\Rocket.png");
	RocketTexture.setSmooth(true);

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		rocket.velocityX += rocket.sidePower - AIR_RESISTANCE;
		rocket.velocityY += rocket.centralPower + GRAVITY_ACCELERATION;

		rocket.x += rocket.velocityX;
		rocket.y += rocket.velocityY;

		if (rocket.x < 0 || rocket.x > WINDOW_WIDTH 
			|| rocket.y < 0 || rocket.y > WINDOW_HEIGHT - 20 
			|| (rocket.x >= landingFieldPosition && rocket.x <= LANDING_FIELD_LENGTH + 100 
				&& rocket.y > 460 && (rocket.velocityX * rocket.velocityX + rocket.velocityY * rocket.velocityY > 30))) 
		{
			cout << "Sorry, you lose! \n";
			break;

		}
		else if (rocket.x >= landingFieldPosition && rocket.x <= landingFieldPosition + LANDING_FIELD_LENGTH 
			&& rocket.y > 460 
			&& (rocket.velocityX * rocket.velocityX + rocket.velocityY * rocket.velocityY <= 25)) 
		{
			cout << "Congratulations, you win! \n";
			break;
		}
		else 
		{
			window.clear(Color::White);

			if (rocket.sidePower > 0)
			{
				rocket.fuel -= rocket.sidePower;
			}
			else if (rocket.sidePower < 0)
			{
				rocket.fuel += rocket.sidePower;
			}

			if (rocket.centralPower < 0)
			{
				rocket.fuel += rocket.centralPower;
				rocket.centralPower = 0;
				rocket.sidePower = 0;
			}

			// Обрабатываем очередь событий в цикле
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::KeyPressed) 
				{
					if (event.key.code == Keyboard::A)
						if (rocket.fuel > 0)rocket.sidePower = -2 * GRAVITY_ACCELERATION;
					if (event.key.code == Keyboard::D)
						if (rocket.fuel > 0) rocket.sidePower = 2 * GRAVITY_ACCELERATION;
					if (event.key.code == Keyboard::W)
						if (rocket.fuel > 0)rocket.centralPower = -2 * GRAVITY_ACCELERATION;
					if (event.key.code == Keyboard::S)
						rocket.centralPower = 2 * GRAVITY_ACCELERATION;
				}
			}


			RectangleShape ground(Vector2f(WINDOW_WIDTH, 19.f));
			ground.setOutlineThickness(1.f);
			ground.setOutlineColor(Color::Black);
			ground.setFillColor(Color::White);
			ground.setPosition(0, WINDOW_HEIGHT - 19);
			window.draw(ground);

			RectangleShape landingField(Vector2f(LANDING_FIELD_LENGTH, 19.f));
			landingField.setFillColor(Color(250, 250, 250));
			landingField.setOutlineThickness(1.f);
			landingField.setOutlineColor(Color::Black);
			landingField.setPosition(landingFieldPosition, WINDOW_HEIGHT - 30);
			window.draw(landingField);

			Sprite RocketSprite(RocketTexture);
			RocketSprite.setPosition(rocket.x, rocket.y - 60);
			RocketSprite.scale(1, 1);
			window.draw(RocketSprite);
		}
		std::cout << "fuel: " << rocket.fuel << "\nX: " << rocket.x << " Y: " << rocket.y << "\n vx: " << rocket.velocityX <<
			" vy: " << rocket.velocityY << "\nax: " << rocket.sidePower << " ay: " << rocket.centralPower + GRAVITY_ACCELERATION;

		system("cls");


		// Отрисовка окна	
		window.display();
	}

	system("pause");
	return 0;
}