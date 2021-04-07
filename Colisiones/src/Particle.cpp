#include <../inc/Particle.h>

Particle::Particle(){
}

Particle::Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_): x(x_), y(y_), vx(vx_), vy(vy_), m(m_), r(r_), ID(ID_){
 
}

Particle::~Particle(){
}

// Methods

double Particle::getX(){
	return x;
}
double Particle::getY(){
	return y;
}
double Particle::getVx(){
	return vx;
}
double Particle::getVy(){
	return vy;
}
double Particle::getM(){
	return m;
}

void Particle::updateAcceleration(double Fx_, double Fy_)
{
	ax = Fx_/m;
	ay = Fy_/m;
}

void Particle::CheckCollision(Particle* p2)
{
	double dist= sqrt(pow(x-p2->x,2)+pow(y-p2->y,2));
	if( dist< r + p2->r) 
	{
		double F=K*pow(dist,5);
		Fx=(-F*y/dist);
		Fy=(-F*x/dist);
	}
	else
	{
		Fx=0.;
		Fy=0.;
	}
	ax = Fx/m;
	ay = Fy/m;
	//p2->updateAcceleration(-Fx,-Fy);
	
}

void Particle::Print1()
{
	std::cout << "ID: " << ID << " , x: " << x << " , y: " << y << " , vx: " << vx << " , vy: " << vy << " , ax: " << ax << " , ay: " << ay << std::endl;
}


double Particle::calculateMomentum()
{
	return m*sqrt(pow(vx,2)+pow(vy,2));
}

void Particle::SetWallLimits(double Wxmin_, double Wxmax_, double Wymin_, double Wymax_){
Wxmin = Wxmin_;
Wxmax = Wxmax_;
Wymin = Wymin_;
Wymax = Wymax_;
}

void Particle::ChangeWallLimits(double deltat, double v, double lim_){

	if(Wxmax >= lim_)
		Wxmax += v*deltat;
}

void Particle::CheckWallLimits(){

	if( (x+r) >= Wxmax || (x-r) <= Wxmin ) vx = -vx;
	if( (y+r) >= Wymax || (y-r) <= Wymin ) vy = -vy;


}

void Particle::Print(){
 std::cout <<" , "<<x<<"+"<<r<<"*cos(t),"<<y<<"+"<<r<<"*sin(t)";
}

void Particle::Move(double t_, double deltat, int it){


	t=t_;
	x += (vx*deltat)+(0.5*ax*pow(deltat,2));
	y += (vy*deltat)+(0.5*ay*pow(deltat,2));
	vx += ax*deltat;
	vy += ay*deltat;

}

