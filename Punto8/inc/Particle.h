#ifndef Particle_H
#define Particle_H


#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <cmath>
// Random

#include <random>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;

class Particle{
	
	public:
		Particle();
		Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_);
		~Particle();

		double getX();
		double getY();
		double getVx();
		double getVy();
		double getM();

		void updateAcceleration(double Fx_, double Fy_);
		void CheckCollision(Particle* p2);
		double calculateMomentum();
		void Print1();

		void SetWallLimits(double Wxmin_, double Wxmax_, double Wymin_, double Wymax_);
		void CheckWallLimits();
		void Print();

		void Move(double t_, double deltat, int it);

		void ChangeWallLimits(double deltat, double v, double lim_);

	private:

		double x,y;
		double t;

		double vx,vy;
		double ax,ay;
		double Fx,Fy;

		double m,r;

		int ID;

		std::ofstream *File;

		double Wxmin,Wxmax;
		double Wymin,Wymax;

		double K = 100.;

	protected:


};

#endif
