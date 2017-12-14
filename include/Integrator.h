#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <functional>
#include <vector>

class Integrator {
public:
  Integrator(int count, std::vector<std::function<double (double, std::vector<double>)> > functions, std::vector<double> variables);
  
  std::vector<double> rk4(double t, double dt);
  std::vector<double> rk4_matsuoka(double t, double dt);
  ~Integrator();

private:
  std::vector<double> k;
  std::vector<double> l;
  std::vector<double> m;
  std::vector<double> lvariables;
  std::vector<double> mvariables;
  std::vector<double> nvariables;
  std::vector<std::function<double (double, std::vector<double>)> > functions;
  
  std::vector<double> variables;
  
  int count;
};

#endif
