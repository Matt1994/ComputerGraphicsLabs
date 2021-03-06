#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "math.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- Functions that listen for widget events
// forewards to the mainview

void MainWindow::on_ResetRotationButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->RotationDialX->setValue(0);
    ui->RotationDialY->setValue(0);
    ui->RotationDialZ->setValue(0);
    ui->mainView->setRotation(0, 0, 0);
}

void MainWindow::on_RotationDialX_sliderMoved(int value)
{
    ui->mainView->setRotation(value,
                              ui->RotationDialY->value(),
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialY_sliderMoved(int value)
{
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              value,
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialZ_sliderMoved(int value)
{
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              ui->RotationDialY->value(),
                              value);
}

void MainWindow::on_ResetTimeSpeedButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->mainView->setTimeSpeed(1);
    ui->TimeSpeedSlider->setValue(1);
}

void MainWindow::on_TimeSpeedSlider_sliderMoved(int value)
{
    ui->mainView->setTimeSpeed(value);
}

void MainWindow::on_PhongButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::PHONG);
        ui->mainView->update();
    }
}

void MainWindow::on_WaveButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::WAVE);
        ui->mainView->update();
    }
}

void MainWindow::on_materialIntensity1_valueChanged(double d)
{
    ui->mainView->setMaterialIntensity(d, ui->materialIntensity2->value(), ui->materialIntensity3->value());
}

void MainWindow::on_materialIntensity2_valueChanged(double d)
{
    ui->mainView->setMaterialIntensity(ui->materialIntensity1->value(), d, ui->materialIntensity3->value());
}

void MainWindow::on_materialIntensity3_valueChanged(double d)
{
    ui->mainView->setMaterialIntensity(ui->materialIntensity1->value(), ui->materialIntensity2->value(), d);
}

void MainWindow::on_lp1_valueChanged(double d)
{
    ui->mainView->setLightPosition(d, ui->lp2->value(), ui->lp3->value());
}

void MainWindow::on_lp2_valueChanged(double d)
{
    ui->mainView->setLightPosition(ui->lp1->value(), d, ui->lp3->value());
}

void MainWindow::on_lp3_valueChanged(double d)
{
    ui->mainView->setLightPosition(ui->lp1->value(), ui->lp2->value(), d);
}

void MainWindow::on_phongExponent_valueChanged(int i)
{
    ui->mainView->setPhongExponent(i);
}
