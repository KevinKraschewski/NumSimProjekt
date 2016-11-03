/*
 * Copyright (C) 2015   Malte Brunn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "typedef.hpp"
#include "parameter.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

  /// Constructs a new Parameter set with default values
  // Driven Cavity parameters; see exercise sheet 1
  Parameter(){
	  // MUSS NOCH WAS GEANDERT WERDEN
  }

  /// Loads the parameter values from a file
  /// Nur den Inhalt aus der config_parser Datei rein kopiert...
  void Parameter::Load(const char *file){
	  FILE* handle = fopen(file,"r");
	  double inval[2];

	  char name[20];
	  while (!feof(handle)) {
	  	if (!fscanf(handle, "%s =", name)) continue;
	  	if (strcmp(name,"size") == 0) {
	  		if (fscanf(handle," %lf %lf\n",&inval[0],&inval[1])) {
	  			_size[0] = inval[0];
	  			_size[1] = inval[1];
	  		}
	  		continue;
	  	}
	  	if (strcmp(name,"length") == 0) {
	  		if (fscanf(handle," %lf %lf\n",&inval[0],&inval[1])) {
	  			_length[0] = inval[0];
	  			_length[1] = inval[1];
	  		}
	  		continue;
	  	}
	  	if (strcmp(name,"velocity") == 0) {
	  		if (fscanf(handle," %lf %lf\n",&inval[0],&inval[1])) {
	  			_velocity[0] = inval[0];
	  			_velocity[1] = inval[1];
	  		}
	  		continue;
	  	}
	  	if (strcmp(name,"pressure") == 0) {
	  		if (fscanf(handle," %lf\n",&inval[0]))
	  			_pressure = inval[0];
	  		continue;
	  	}
	  }
	  fclose(handle);

	  FILE* handle = fopen(file,"r");
	  double inval;
	  char name[20];
	  while (!feof(handle)) {
	  	if (!fscanf(handle, "%s = %lf\n", name, &inval)) continue;
	  	if (strcmp(name,"re") == 0) _re = inval;
	  	else if (strcmp(name,"omg") == 0) _omega = inval;
	  	else if (strcmp(name,"alpha") == 0) _alpha = inval;
	  	else if (strcmp(name,"dt") == 0) _dt = inval;
	  	else if (strcmp(name,"tend") == 0) _tend = inval;
	  	else if (strcmp(name,"iter") == 0) _itermax = inval;
	  	else if (strcmp(name,"eps") == 0) _eps = inval;
	  	else if (strcmp(name,"tau") == 0) _tau = inval;
	  	else printf("Unknown parameter %s\n",name);
	  }
	  fclose(handle);
  }

  /// Getter functions for all parameters
  /// Nur ueber return. Bessere Moeglichkeit existiert wohl :)
  
  /// Reynoldszahl, fuer Charakteristik der Stroemung
  const real_t Parameter::&Re() const{
	  return _Re;
  }
  
  /// Relaxationsfaktor fuer den Loeser
  const real_t Parameter::&Omega() const{
	  return _omega;
  }
  
  ///  Alpha aus dem Donor-Cell Scheme
  const real_t Parameter::&Alpha() const{
	  return _alpha;
  }
  
  /// Zeitschrittweite
  const real_t Parameter::&Dt() const{
	  return _dt;
  }
  
  /// Endzeitpunkt
  const real_t Parameter::&Tend() const{
	  return _tend;
  }
  
  /// Zahl der maximalen Iterationen, fuer Abbruchbedingung
  const index_t Parameter::&IterMax() const{
	  return _itermax;
  }
  
  /// Epsilon fuer die Abbruchbedingung bei der Iteration fuer den Druck
  const real_t Parameter::&Eps() const{
	  return _eps;
  }
  
  /// Tau fuer die Stabilitaetsbedingung in der Zeit ( anstatt \leq RS -> < tau*RS)
  const real_t Parameter::&Tau() const{
	  return _tau;
  }
