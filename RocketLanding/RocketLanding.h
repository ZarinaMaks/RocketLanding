class Rocket {

	float x, y, velocityX, velocityY, fuel, sidePower, centralPower;

public:
	Rocket(float x_ = 0, float y_ = 0, float fuel_ = 100) :
		x(x_), y(y_), velocityX(0), velocityY(0), fuel(fuel_), sidePower(0), centralPower(0) {}

	float getX() {
		return x;
	}
	void setX(float coordinate) {
		x = coordinate;
	}

	float getY() {
		return y;
	}
	void setY(float coordinate) {
		y = coordinate;
	}

	float getVelocityX() {
		return velocityX;
	}
	void setVelocityX(float velocity) {
		velocityX = velocity;
	}

	float getVelocityY() {
		return velocityY;
	}
	void setVelocityY(float velocity) {
		velocityY = velocity;
	}

	float getFuel() {
		return fuel;
	}
	void setFuel(float fuel_) {
		fuel = fuel_;
	}

	float getSidePower() {
		return sidePower;
	}
	void setSidePower(float power) {
		sidePower = power;
	}

	float getCentralPower() {
		return centralPower;
	}
	void setCentralPower(float power) {
		centralPower = power;
	}

	void move() {
		setVelocityX(getVelocityX() + getSidePower() + WIND);
		setVelocityY(getVelocityY() + getCentralPower() + GRAVITY);
		setX(getX() + getVelocityX());
		setY(getY() + getVelocityY());
		setFuel(getFuel() - getCentralPower() - getSidePower());
	}

};