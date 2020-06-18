#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include<fstream>
#include <random>
#include <chrono>
#include <stdio.h>
#include <math.h>
#include <cmath>

const double rcp = 3; 
double dt = 0.00001; 
double runtime = 0.2; 
long seed = 10; 
const int dump = 1000;
double K; 
double U; 
double H; 
double T =300; 
#define M_PI 3.14159265358979323846
#define N 256
const int duplicate = 4;
const int lc = 2;
double const L = duplicate * lc; 




std::random_device rd;

std::mt19937 generator(rd());




struct Atom
{
	double rx, ry, rz; 
	double px, py, pz; 
	double fx, fy, fz; 
};



double makePeriodic(double u)
{
	while (u < -0.5*L)
	{
		u = u + L;
	}

	while (u >= 0.5*L)
	{
		u = u - L;
	}

	return u;
}

void computeForces(struct Atom atoms[])
{
	int i, j;
	double dx, dy, dz;
	double r, r2, r2i, r6i;
	double fij;
	double eij;

	U = 0;

	for (i = 0; i < N; i = i + 1)
	{
		atoms[i].fx = 0;
		atoms[i].fy = 0;
		atoms[i].fz = 0;
	}

	for (i = 0; i < N - 1; i = i + 1)
	{
		for (j = i + 1; j < N; j = j + 1)
		{
			dx = makePeriodic(atoms[i].rx - atoms[j].rx);
			dy = makePeriodic(atoms[i].ry - atoms[j].ry);
			dz = makePeriodic(atoms[i].rz - atoms[j].rz);
			r2 = dx * dx + dy * dy + dz * dz;

			if (r2 < rcp*rcp)
			{
				r2i = 3.405 / r2;
				r6i = r2i * r2i*r2i;
				fij = 48 * r2i*r6i*(r6i - 0.5);
				eij = 4 * r6i*(r6i - 1);

				atoms[i].fx = atoms[i].fx + fij * dx;
				atoms[i].fy = atoms[i].fy + fij * dy;
				atoms[i].fz = atoms[i].fz + fij * dz;
				atoms[j].fx = atoms[j].fx - fij * dx;
				atoms[j].fy = atoms[j].fy - fij * dy;
				atoms[j].fz = atoms[j].fz - fij * dz;
				U = U + eij;
			}
		}
	}
}

double gaussian()
{
	static int have = 0;
	static double x2;
	double fac, y1, y2, x1;

	if (have == 1)
	{
		have = 0;
		return x2;
	}
	else
	{
	
		std::uniform_real_distribution<double> unif1(0.01,0.999999);
		std::uniform_real_distribution<double> unif2(-0.9999999, 0.99999999);
		y1 = unif1(generator);
		y2 = unif2(generator);
		fac = sqrt(-2 * log(y1));
		have = 1;
		x1 = fac * sin(2 * M_PI*y2);
		x2 = fac * cos(2 * M_PI*y2);
		return x1;
	}
}

void initialize(struct Atom atoms[])
{
	double scale;
	int i;

	double fcc[4][3] = { {0,0,0},
	{0,0.5,0.5},
	{0.5,0,0.5},
	{0.5,0.5,0}
	};
	int aa = 0;
	for (int x = 0; x < duplicate; x++) {
		for (int y = 0; y < duplicate; y++) {
			for (int z = 0; z < duplicate; z++) {
				for (int i = 0; i < 4; i++) {
					atoms[aa].rx = (fcc[i][0] + x) * lc - L / 4;
					atoms[aa].ry = (fcc[i][1] + y) * lc - L / 4;
					atoms[aa].rz = (fcc[i][2] + z) * lc - L / 4;
					aa++;
				}
			}
		}
	}


	scale = sqrt(T);
	K = 0;
	double ix = 0;
	double iy = 0;
	double iz = 0;
	for (i = 0; i < N; i = i + 1)
	{
		atoms[i].px = scale * gaussian();
		
		atoms[i].py = scale * gaussian();
		atoms[i].pz = scale * gaussian();
		ix += atoms[i].px;
		iy += atoms[i].py;
		iz += atoms[i].pz;


	}
	for (i = 0; i < N; i = i + 1) {
		atoms[i].px -= ix / N;
		atoms[i].py -= iy / N;;
		atoms[i].pz -= iz / N;;
	}



	for (i = 0; i < N; i = i + 1){
		K = K
			+ atoms[i].px*atoms[i].px
			+ atoms[i].py*atoms[i].py
			+ atoms[i].pz*atoms[i].pz;
	}

	T = K / (3 * N);
	K = K / 2;

	computeForces(atoms);

	H = U + K;

	printf("# time E U K T <[H-<H>]^2>\n");
}

void integrateStep(struct Atom atoms[], int count)
{
	int i;

	for (i = 0; i < N; i = i + 1)
	{
		atoms[i].px = atoms[i].px + 0.5*dt*atoms[i].fx;
		atoms[i].py = atoms[i].py + 0.5*dt*atoms[i].fy;
		atoms[i].pz = atoms[i].pz + 0.5*dt*atoms[i].fz;
	}
	for (i = 0; i < N; i = i + 1)
	{
		atoms[i].rx = makePeriodic(atoms[i].rx);
		atoms[i].ry = makePeriodic(atoms[i].ry);
		atoms[i].rz = makePeriodic(atoms[i].rz);
	}
	for (i = 0; i < N; i = i + 1)
	{
		atoms[i].rx = atoms[i].rx + dt * atoms[i].px;
		atoms[i].ry = atoms[i].ry + dt * atoms[i].py;
		atoms[i].rz = atoms[i].rz + dt * atoms[i].pz;
	}

	if (count % dump == 0) {
		FILE *outfile;
		char filename[50];
		snprintf(filename, sizeof(filename), "out%d.dump", count);
		outfile = fopen(filename, "w");
		fprintf(outfile, "ITEM: TIMESTEP \n");
		fprintf(outfile, "0 \n");
		fprintf(outfile, "ITEM: NUMBER OF ATOMS \n");
		fprintf(outfile, "256 \n");
		fprintf(outfile, "ITEM: BOX BOUNDS pp pp pp  \n");
		fprintf(outfile, "%.4f  %.4f \n", -0.5*L, 0.5*L);
		fprintf(outfile, "%.4f  %.4f \n", -0.5*L, 0.5*L);
		fprintf(outfile, "%.4f  %.4f \n", -0.5*L, 0.5*L);
		fprintf(outfile, "ITEM: ATOMS id type x y z vx vy vz fx fy fz \n");
		for (i = 0; i < N; i = i + 1) {
			fprintf(outfile, "%d 0 %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f\n", i + 1, atoms[i].rx, atoms[i].ry, atoms[i].rz
			, atoms[i].px, atoms[i].py, atoms[i].pz
			, atoms[i].fx, atoms[i].fy, atoms[i].fz);
		}
		fclose(outfile);
	}
	computeForces(atoms);
	K = 0;
	for (i = 0; i < N; i = i + 1)
	{
		atoms[i].px = atoms[i].px + 0.5*dt*atoms[i].fx;
		atoms[i].py = atoms[i].py + 0.5*dt*atoms[i].fy;
		atoms[i].pz = atoms[i].pz + 0.5*dt*atoms[i].fz;
		K = K
			+ atoms[i].px*atoms[i].px
			+ atoms[i].py*atoms[i].py
			+ atoms[i].pz*atoms[i].pz;
	}
	T = K / (3 * N);
	K = K / 2;
	H = U + K;
}

void run()
{
	struct Atom atoms[N];
	int numSteps = (int)(runtime / dt + 0.5);
	int count;
	int numPoints = 0;
	double sumH = 0;
	double sumH2 = 0;
	double avgH, avgH2, fluctH;

	initialize(atoms);
	for (count = 0; count < numSteps; count = count + 1)
	{
		integrateStep(atoms, count);
		sumH = sumH + H;
		sumH2 = sumH2 + H * H;
		numPoints = numPoints + 1;
		avgH = sumH / numPoints;
		avgH2 = sumH2 / numPoints;
		fluctH = sqrt(avgH2 - avgH * avgH);

		
		FILE *outfile;

		outfile = fopen("history.log", "a");

		fprintf(outfile, "%8.6f %8.6f %8.6f \n",
			count*dt, U / N, K / N);
		fclose(outfile);
		
		printf("%8.6f %8.6f %8.6f %8.6f %8.6f %8.6f\n",
			count*dt, H / N, U / N, K / N, T, fluctH / N);
	}
}

int main()
{

	printf("\n#N=%d L=%lf T=%lf runtime=%lf dt=%lf ",
		N, L, T, runtime, dt);
	FILE *outfile;

	outfile = fopen("history.log", "w");
	fprintf(outfile,"");
	fclose(outfile);
	run();
	return 0;
}