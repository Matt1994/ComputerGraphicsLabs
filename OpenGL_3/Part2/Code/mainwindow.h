#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ResetRotationButton_clicked(bool checked);
    void on_RotationDialX_sliderMoved(int value);
    void on_RotationDialY_sliderMoved(int value);
    void on_RotationDialZ_sliderMoved(int value);

    void on_ResetTimeSpeedButton_clicked(bool checked);
    void on_TimeSpeedSlider_sliderMoved(int value);

    void on_PhongButton_toggled(bool checked);
    void on_WaveButton_toggled(bool checked);

    void on_materialIntensity1_valueChanged(double d);
    void on_materialIntensity2_valueChanged(double d);
    void on_materialIntensity3_valueChanged(double d);

    void on_lp1_valueChanged(double d);
    void on_lp2_valueChanged(double d);
    void on_lp3_valueChanged(double d);

    void on_phongExponent_valueChanged(int i);

};

#endif // MAINWINDOW_H
