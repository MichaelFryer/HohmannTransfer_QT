//HohmannTransfer Calculator
//Copyright (C) 2015 Michael Fryer
//
//HohmannTransfer Calculator is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//HohmannTransfer Calculator is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with HohmannTransfer Calculator.  If not, see <http://www.gnu.org/licenses/>.

#include "celestialbody.h"

CelestialBody::CelestialBody(QString name, qreal mass, qreal radius)
{
    this->name = name;
    this->mass = mass;
    this->radius = radius;
}

qreal CelestialBody::SeaHeightToFocusDistance(qreal height){
    return height + radius;
}

qreal CelestialBody::FocusDistanceToSeaHeight(qreal distance){
    return distance - radius;
}

qreal CelestialBody::StandardGravityParamter(){
    return mass * 6.673e-11;
}

