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

#include "iterator.hpp"

/// Constructs a new Iterator depending on a geometry
Iterator::Iterator(const Geometry *geom){
	*_geom = geom;
	_value = 1;
	_valid = true;
}

/// Constructs a new Iterator on a geometry with a defined starting value
Iterator::Iterator(const Geometry *geom, const index_t &value){
	*_geom = geom;
	_value = value;
	if (value <= (_geom.size[0]+2)*(_geom.size[1]+2))
		_valid = true;
	else _valid = false;
}

/// Returns the current position value
const index_t& Iterator::Value() const{
  return _value;
}

/// Returns the position coordinates
multi_index_t Iterator::Pos() const{
  // hier fehlt noch was
  return 0; // falsch
}

/// Sets the iterator to the first element
void Iterator::First(){
  // hier fehlt noch was
}

/// Goes to the next element of the iterator, disables it if position is end
void Iterator::Next(){
  // hier fehlt noch was
}

/// Checks if the iterator still has a valid value
bool Iterator::Valid() const{
  // hier fehlt noch was
  return true; // falsch
}

/// Returns an Iterator that is located left from this one.
// if we are at the left boundary, the cell sees itself
Iterator Iterator::Left() const{
  // hier fehlt noch was
  return 0; // falsch
}

/// Returns an Iterator that is located right from this one
// If we are at the right boundary, the cell sees itself
Iterator Iterator::Right() const{
  // hier fehlt noch was
  return 0; // falsch
}

/// Returns an Iterator that is located above this one
// If we are at the upper domain boundary, the cell sees itself
Iterator Iterator::Top() const{
  // hier fehlt noch was
  return 0; // falsch
}

/// Returns an Iterator that is located below this one
// If we are at the lower domain boundary, the cell sees itself
Iterator Iterator::Down() const{
  // hier fehlt noch was
  return 0; // falsch
}


  //const Geometry *_geom;
  //index_t _value;
  //bool _valid;

/// Construct a new InteriorIterator
// Konstruktor von Iterator wird zu Beginn schon aufgerufen, da es keine Konstructor für Iterator ohne Argumente gibt.
InteriorIterator::InteriorIterator(const Geometry *geom) : Iterator::Iterator(geom) {  
  // hier fehlt noch was
}

/// Sets the iterator to the first element
void InteriorIterator::First(){
  // hier fehlt noch was
}

/// Goes to the next element of the iterator, disables it if position is end
void InteriorIterator::Next(){
  // hier fehlt noch was
}

/// Constructs a new BoundaryIterator
BoundaryIterator::BoundaryIterator(const Geometry *geom) : Iterator::Iterator(geom) {
  // hier fehlt noch was
}

/// Sets the boundary to iterate
void BoundaryIterator::SetBoundary(const index_t &boundary){
  // hier fehlt noch was
}

/// Sets the iterator to the first element
void BoundaryIterator::First(){
  // hier fehlt noch was
}

/// Goes to the next element of the iterator, disables it if position is end
void BoundaryIterator::Next(){
  // hier fehlt noch was
}


  //index_t _boundary;
