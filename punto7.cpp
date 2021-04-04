#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

class Particle
{
    private:

		double x,y;
		double t;

		double vx,vy;
		double ax,ay;
		double Fx,Fy;

		double m,r;

		int ID;

		std::ofstream *File;

		double K = 100.;

    public:
		Particle(){}
		Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_)
        {
            x=x_;
            y=y_;
            vx=vx_;
            vy=vy_;
            m=m_;
            r=r_;
            ID=ID_;
            ax=0.;
            ay=0.;
        }
		~Particle(){}

        double getX()
        {
            return x;
        }
        double getY()
        {
            return y;
        }
        double getVx()
        {
            return vx;
        }
        double getVy()
        {
            return vy;
        }
        double getM()
        {
            return m;
        }
        double getR()
        {
            return r;
        }
        void updateAcceleration(double Fx_, double Fy_)
        {
            ax = Fx_/m;
            ay = Fy_/m;
        }
        
		void CheckCollision(Particle* p2)
        {
            double dist= sqrt(pow(x-p2->x,2)+pow(y-p2->y,2));
            if( dist< r + p2->r) 
            {
                double F=K*pow(dist,5);
                Fx=(-F*y/dist);//Ver si es + o -
                Fy=(-F*x/dist);
            }
            else
            {
                Fx=0.;
                Fy=0.;
            }
            updateAcceleration(Fx,Fy);
            p2->updateAcceleration(-Fx,-Fy);
            
        }
		void Print()
        {
            cout << "ID: " << ID << " , x: " << x << " , y: " << y << " , vx: " << vx << " , vy: " << vy << " , ax: " << ax << " , ay: " << ay << " , p: " << calculateMomentum() << endl;
        }

		void Move(double t_, double deltat, int it)
        {
            t=t_;
            x += (vx*deltat)+(0.5*ax*pow(deltat,2));
	        y += (vy*deltat)+(0.5*ay*pow(deltat,2));
            vx += ax*deltat;
	        vy += ay*deltat;
        }

        double calculateMomentum()
        {
            return m*sqrt(pow(vx,2)+pow(vy,2));
        }


};

int main()
{
    Particle *p1 = new Particle(-10.,4.,40.,0.,10.,5.,0);
    Particle *p2 = new Particle(0.,0.,0.,0.,10.,5.,1);

    double deltat = 0.001;
    int it = 0;
    double tmax = 0.03;
    double time = 0.;

    double p0=p1->calculateMomentum()+p2->calculateMomentum();
    double pf;

    while( time < tmax)
    {
        cout << "t: " << time << endl;
        p1->Move(time,deltat,it);
        p2->Move(time,deltat,it);

        p1->CheckCollision(p2);

        p1->Print();
        p2->Print();
        
        pf=sqrt(pow(p1->getM()*p1->getVx() + p2->getM()*p2->getVx(),2)+pow(p1->getM()*p1->getVy() + p2->getM()*p2->getVy(),2));
        
        if(p0==pf) cout << "El momento se conserva. P0: " << p0 << " ,Pf: " << pf << endl;
        else cout << "El momento no se conserva. P0: " << p0 << " ,Pf: " << pf << endl;

        time += deltat;
	    it ++;
    }

    return 0;
}