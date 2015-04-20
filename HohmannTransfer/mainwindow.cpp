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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "celestialbody.h"
#include <QMessageBox>
#include <QtCore/qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Lock the window to the size it's set to in the designer
    setFixedSize(this->geometry().width(),this->geometry().height());

    // Create the data for the celestial bodies
    celestialBodies.append(CelestialBody(tr("Kerbol"), 1.7565670e+28, 2.616e+8));
    celestialBodies.append(CelestialBody(tr(" - Moho"), 2.5263617e+21, 2.500e+5));
    celestialBodies.append(CelestialBody(tr(" - Eve"), 1.2244127e+23, 7.000e+5));
    celestialBodies.append(CelestialBody(tr(" - - Gilly"), 1.2420512e+17, 1.300e+4));
    celestialBodies.append(CelestialBody(tr(" - Kerbin"), 5.2915793e+22, 6.000e+5));
    celestialBodies.append(CelestialBody(tr(" - - Mun"), 9.7600236e+20, 2.000e+5));
    celestialBodies.append(CelestialBody(tr(" - - Minmus"), 2.6457897e+19, 6.000e+4));
    celestialBodies.append(CelestialBody(tr(" - Duna"), 4.5154812e+21, 3.200e+5));
    celestialBodies.append(CelestialBody(tr(" - - Ike"), 2.7821949e+20, 1.300e+5));
    celestialBodies.append(CelestialBody(tr(" - Dres"), 3.2191322e+20, 1.380e+5));
    celestialBodies.append(CelestialBody(tr(" - Jool"), 4.2332635e+24, 6.000e+6));
    celestialBodies.append(CelestialBody(tr(" - - Laythe"), 2.9397663e+22, 5.000e+5));
    celestialBodies.append(CelestialBody(tr(" - - Vall"), 3.1088028e+21, 3.000e+5));
    celestialBodies.append(CelestialBody(tr(" - - Tylo"), 4.2332635e+22, 6.000e+5));
    celestialBodies.append(CelestialBody(tr(" - - Bop"), 3.7261536e+19, 6.500e+4));
    celestialBodies.append(CelestialBody(tr(" - - Pol"), 1.0813636e+19, 4.400e+4));
    celestialBodies.append(CelestialBody(tr(" - Eeloo"), 1.1149358e+21, 2.100e+5));

    // Populate the combo box with celestial body data
    for (auto it = celestialBodies.begin(); it != celestialBodies.end(); ++it)
    {
        ui->comboBox_body->addItem(it->name);
    }

    // Select Kerbin
    ui->comboBox_body->setCurrentIndex(4);

}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_calculate_clicked()
{
    // Read input
    bool r1IsNumeric, r2IsNumeric;
    qreal r1 = ui->lineEdit_initialOrbit->text().toDouble(&r1IsNumeric);
    qreal r2 = ui->lineEdit_finalOrbit->text().toDouble(&r2IsNumeric);
    CelestialBody selectedBody =  celestialBodies[ui->comboBox_body->currentIndex()];

    // Check input was numeric
    if (!r1IsNumeric){
        QMessageBox::warning(this, tr("Hohmann Transfer Calculator"), tr("Initial Orbit must be a number"), QMessageBox::Ok);
        return;
    }
    if (!r2IsNumeric){
        QMessageBox::warning(this, tr("Hohmann Transfer Calculator"), tr("Final orbit must be a number"), QMessageBox::Ok);
        return;
    }

    // Convert orbit heights from km to m and from height above sea level to distance from focus
    r1 = selectedBody.SeaHeightToFocusDistance(r1 * 1000);
    r2 = selectedBody.SeaHeightToFocusDistance(r2 * 1000);

    // Check the distances are greater than 0
    if (r1 <= 0){
        QMessageBox::warning(this, tr("Hohmann Transfer Calculator"),
                             tr("Initial orbit must be greater than ")+QString::number(selectedBody.radius / -1000, 'f', 0)+tr("km"),
                             QMessageBox::Ok);
        return;
    }
    if (r2 <= 0){
        QMessageBox::warning(this, tr("Hohmann Transfer Calculator"),
                             tr("Final orbit must be greater than ")+QString::number(selectedBody.radius / -1000, 'f', 0)+tr("km"),
                             QMessageBox::Ok);
        return;
    }

    // Calculate v1 and v2 delta-v changes (and make them absolute)
    qreal u = selectedBody.StandardGravityParamter();
    qreal v1 = qSqrt(u / r1) * (qSqrt((2 * r2) / (r1 + r2)) - 1);
    qreal v2 = qSqrt(u / r2) * (1 - qSqrt((2 * r1) / (r1 + r2)));


    // Output results
    ui->lineEdit_firstBurn->setText(QString::number(qFabs(v1), 'f', 2));
    ui->lineEdit_secondBurn->setText(QString::number(qFabs(v2), 'f', 2));
    ui->lineEdit_totalBurn->setText(QString::number(qFabs(v1+v2), 'f', 2));
}

