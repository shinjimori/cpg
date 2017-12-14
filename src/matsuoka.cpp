#include <cmath>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <random>

#include "../include/MeasureFile.h"
#include "../include/Integrator.h"

// Matsuoka oscillator
#define A 2.5
#define bi 3.52
#define TAU_R 0.05 // time constant
#define TAU_A 0.75 //time constant
#define Si 1 // s_0 affects only the output amplitude.

// Pendulum system
#define G 9.81  // gravitational accelaration m*s^(-2)
#define D 0.005 // damping constant kg*m^2*s^(-1)
#define L 0.2   // pendulum length
#define M 0.2   // pendulum weight
#define M0 0.03

#define Oi 1
#define Hz 1.0
#define PI 3.1415926
#define TIME 100


// Pendulum dynamics
// angular velocity
#define _PEQ1(omega, theta, input, length,gain)(- G*sin(theta)/length - D*omega/(M*pow(length,2)) + gain*tanh(7*input)/(M*pow(length,2)))
// angular
#define _PEQ2(omega)(omega)

// Matsuoka oscillator
// x
#define _MEQ1(x, y_other, v, input,gain)((- x - A * y_other - bi * v + gain*input + Si)/TAU_R )
// v
#define _MEQ2(v, y)((- v + y )/TAU_A)

double PF(double Vi) {
    return 1.0 / (1.0 + exp(-Vi));
}

int main()
{
  //double y = 0.0;   // y is output of oscillator,
  double t = 0.0;   // time step
  double dt = 0.01; // time variation

  double ye = 0.0;  
  double yf = 0.0;  
  double y = 0.0;   // matsuoka output
  
  double length = 0.2;
  double input_gain = 0.0;  //0.2 input gain from oscillator to pendulum
  double pf_gain = 0.0; // 0.03 from pendulum to oscillator feedback gain
  
  auto functions = std::vector<std::function<double (double, std::vector<double>)>>(6, NULL);

  //                        p_omega, p_theta, m_xe, m_ve m_xf, m_vf
  std::vector<double> variables{0.1, 0.0, 0.01, 0.008, 0.002, 0.006};

  functions[0] = [&y, &length,&input_gain](double t, std::vector<double> args)->double {
    return _PEQ1(args[0], args[1], y, length, input_gain);
  };
  functions[1] = [](double t, std::vector<double> args)->double {
    return _PEQ2(args[0]);
  };
  functions[2] = [&yf, &pf_gain](double t, std::vector<double> args)->double {
    return _MEQ1(args[2], yf, args[3], args[1], pf_gain);
  };
  functions[3] = [&ye](double t, std::vector<double> args)->double {
    return _MEQ2(args[3], ye);
  };
  functions[4] = [&ye, &pf_gain](double t, std::vector<double> args)->double {
    return _MEQ1(args[4], ye, args[5], -args[1], pf_gain);
  };
  functions[5] = [&yf](double t, std::vector<double> args)->double {
    return _MEQ2(args[5], yf);
  };

  Integrator runge = Integrator(6, functions, variables);


  std::string fname ("out_pendulum_matsu.dat");
  std::string header ("A bi TAU_R TAU_A Si G D L M\n"
                      + std::to_string(Hz) + " "
                      + std::to_string(A) + " "
                      + std::to_string(bi) + " "
                      + std::to_string(TAU_R) +  " "
                      + std::to_string(TAU_A) +  " "
                      + std::to_string(Si) +  " "
                      + std::to_string(G) +  " "
                      + std::to_string(D) +  " "
                      + std::to_string(L) +  " "
                      + std::to_string(M) +  " "
                      "\n" +
                      "t omega theta xe ve xf vf ye yf y");
  
  MeasureFile measures(fname, header);

  std::cout << "START Rowat-Selveston model simulation!! " << "\n";

  while(t < TIME){

	variables = runge.rk4(t, dt);
    ye = std::max(variables[2],0.0);
    yf = std::max(variables[4],0.0);
    y = Oi*(ye - yf);
	
    std::vector<double> output_record{ye, yf, y};
    std::vector<double> record = std::vector<double>(variables);
	
    record.insert(record.begin(), t);
    record.insert(record.end(), output_record.begin(), output_record.end());
    measures.writeMeasure(record);
	
    t += dt;
    if(t >= 10 && t <10.1) {pf_gain = 1; input_gain=0.03;}
    if(t >= 30 && t <30.1) length = 0.4;
    if(t >= 50 && t <50.1) length = 0.2;
    if(t >= 70 && t <70.1) {pf_gain = 0.0; input_gain=0.0;}
  }
  std::cout << "FINISH simulation... " << "\n"
            << "Please check output... " << "\n";

  return 0;
}

