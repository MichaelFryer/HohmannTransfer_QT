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

#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <QString>


class CelestialBody
{
public:
    CelestialBody(QString name, qreal mass, qreal radius);

    // Data
    QString name;
    qreal mass; // in grams
    qreal radius; // in meters

    // Convert a height above sea level to a distance from the body focus (meters)
    qreal SeaHeightToFocusDistance(qreal height);

    //Convert a distance from the body focus to a height above sea level (meters)
    qreal FocusDistanceToSeaHeight(qreal distance);

    // Convert the mass to a standard gravity parameter
    qreal StandardGravityParamter();
};

#endif // CELESTIALBODY_H
