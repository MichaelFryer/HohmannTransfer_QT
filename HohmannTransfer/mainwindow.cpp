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
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_calculate_clicked()
{
    qreal r1, r2;
    qreal v1, v2;
    qreal u;

    bool r1IsNumeric, r2IsNumeric;
    CelestialBody selectedBody(tr("Test"), 5.2915793e+22, 6.000e+5);
    u = selectedBody.StandardGravityParamter();

    // Read input
    r1 = ui->lineEdit_initialOrbit->text().toDouble(&r1IsNumeric);
    r2 = ui->lineEdit_finalOrbit->text().toDouble(&r2IsNumeric);

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
    v1 = qSqrt(u / r1) * (qSqrt((2 * r2) / (r1 + r2)) - 1);
    v2 = qSqrt(u / r2) * (1 - qSqrt((2 * r1) / (r1 + r2)));


    // Output results
    ui->lineEdit_firstBurn->setText(QString::number(qFabs(v1), 'f', 2));
    ui->lineEdit_secondBurn->setText(QString::number(qFabs(v2), 'f', 2));
    ui->lineEdit_totalBurn->setText(QString::number(qFabs(v1+v2), 'f', 2));
}

