#include "../include/Integrator.h"

Integrator::Integrator(int count, std::vector<std::function<double (double, std::vector<double>)> > functions, std::vector<double> variables) {
  this->count = count;
  this->functions = functions;
  this->variables = variables;
  
  k = std::vector<double>(count, 0.0);
  l = std::vector<double>(count, 0.0);
  m = std::vector<double>(count, 0.0);
  lvariables = std::vector<double>(count, 0.0);
  mvariables = std::vector<double>(count, 0.0);
  nvariables = std::vector<double>(count, 0.0);
}

Integrator::~Integrator() {
}

std::vector<double> Integrator::rk4(double t, double dt) {
  for (int i = 0; i < count; i++) {
    k[i] = dt * functions[i](t, variables);
    lvariables[i] = variables[i] + k[i] / 2.0;
  }
  for (int i = 0; i < count; i++) {
    l[i] = dt * functions[i](t, lvariables);
    mvariables[i] = variables[i] + l[i] / 2.0;
  }
  for (int i = 0; i < count; i++) {
    m[i] = dt * functions[i](t, mvariables);
    nvariables[i] = variables[i] + m[i];
  }
  for (int i = 0; i < count; i++) {
    variables[i] = variables[i] + (k[i] + 2.0*l[i] + 2.0*m[i] + dt*functions[i](t, nvariables)) / 6.0;
  }

  return variables;
}

