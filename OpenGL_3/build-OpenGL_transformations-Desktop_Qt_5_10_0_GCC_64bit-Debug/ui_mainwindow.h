/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mainview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *settingsBox;
    QFormLayout *formLayout;
    QGroupBox *rotationBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QDial *RotationDialX;
    QDial *RotationDialY;
    QDial *RotationDialZ;
    QPushButton *ResetRotationButton;
    QGroupBox *zoomBox;
    QVBoxLayout *verticalLayout_4;
    QSlider *ZoomSlider;
    QPushButton *ResetZoomButton;
    QHBoxLayout *RotationSpeed;
    QLabel *RotationSpeed_2;
    QGroupBox *shadingBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *PhongButton;
    QRadioButton *NormalButton;
    QRadioButton *GouraudButton;
    QGroupBox *uniformsBox;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *materialIntensity;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *materialIntensity1;
    QDoubleSpinBox *materialIntensity2;
    QDoubleSpinBox *materialIntensity3;
    QVBoxLayout *lightPosition;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *lp1;
    QDoubleSpinBox *lp2;
    QDoubleSpinBox *lp3;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *phongExponent;
    QSpinBox *rotationSpeed;
    MainView *mainView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1048, 681);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        settingsBox = new QGroupBox(centralWidget);
        settingsBox->setObjectName(QStringLiteral("settingsBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settingsBox->sizePolicy().hasHeightForWidth());
        settingsBox->setSizePolicy(sizePolicy);
        settingsBox->setMinimumSize(QSize(220, 0));
        settingsBox->setMaximumSize(QSize(220, 16777215));
        formLayout = new QFormLayout(settingsBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        rotationBox = new QGroupBox(settingsBox);
        rotationBox->setObjectName(QStringLiteral("rotationBox"));
        sizePolicy.setHeightForWidth(rotationBox->sizePolicy().hasHeightForWidth());
        rotationBox->setSizePolicy(sizePolicy);
        rotationBox->setMinimumSize(QSize(205, 0));
        rotationBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout = new QVBoxLayout(rotationBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        RotationDialX = new QDial(rotationBox);
        RotationDialX->setObjectName(QStringLiteral("RotationDialX"));
        RotationDialX->setMaximum(359);
        RotationDialX->setWrapping(true);
        RotationDialX->setNotchTarget(12);
        RotationDialX->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialX);

        RotationDialY = new QDial(rotationBox);
        RotationDialY->setObjectName(QStringLiteral("RotationDialY"));
        RotationDialY->setMaximum(359);
        RotationDialY->setWrapping(true);
        RotationDialY->setNotchTarget(12);
        RotationDialY->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialY);

        RotationDialZ = new QDial(rotationBox);
        RotationDialZ->setObjectName(QStringLiteral("RotationDialZ"));
        RotationDialZ->setMaximum(359);
        RotationDialZ->setWrapping(true);
        RotationDialZ->setNotchTarget(12);
        RotationDialZ->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialZ);


        verticalLayout->addLayout(horizontalLayout_2);

        ResetRotationButton = new QPushButton(rotationBox);
        ResetRotationButton->setObjectName(QStringLiteral("ResetRotationButton"));

        verticalLayout->addWidget(ResetRotationButton);


        formLayout->setWidget(0, QFormLayout::LabelRole, rotationBox);

        zoomBox = new QGroupBox(settingsBox);
        zoomBox->setObjectName(QStringLiteral("zoomBox"));
        sizePolicy.setHeightForWidth(zoomBox->sizePolicy().hasHeightForWidth());
        zoomBox->setSizePolicy(sizePolicy);
        zoomBox->setMinimumSize(QSize(205, 0));
        zoomBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout_4 = new QVBoxLayout(zoomBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        ZoomSlider = new QSlider(zoomBox);
        ZoomSlider->setObjectName(QStringLiteral("ZoomSlider"));
        ZoomSlider->setMinimum(1);
        ZoomSlider->setMaximum(100);
        ZoomSlider->setValue(50);
        ZoomSlider->setSliderPosition(50);
        ZoomSlider->setOrientation(Qt::Horizontal);
        ZoomSlider->setInvertedAppearance(false);
        ZoomSlider->setInvertedControls(false);
        ZoomSlider->setTickPosition(QSlider::NoTicks);

        verticalLayout_4->addWidget(ZoomSlider);

        ResetZoomButton = new QPushButton(zoomBox);
        ResetZoomButton->setObjectName(QStringLiteral("ResetZoomButton"));

        verticalLayout_4->addWidget(ResetZoomButton);


        formLayout->setWidget(1, QFormLayout::LabelRole, zoomBox);

        RotationSpeed = new QHBoxLayout();
        RotationSpeed->setSpacing(6);
        RotationSpeed->setObjectName(QStringLiteral("RotationSpeed"));
        RotationSpeed_2 = new QLabel(settingsBox);
        RotationSpeed_2->setObjectName(QStringLiteral("RotationSpeed_2"));

        RotationSpeed->addWidget(RotationSpeed_2);


        formLayout->setLayout(2, QFormLayout::LabelRole, RotationSpeed);

        shadingBox = new QGroupBox(settingsBox);
        shadingBox->setObjectName(QStringLiteral("shadingBox"));
        sizePolicy.setHeightForWidth(shadingBox->sizePolicy().hasHeightForWidth());
        shadingBox->setSizePolicy(sizePolicy);
        shadingBox->setMinimumSize(QSize(205, 0));
        shadingBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout_2 = new QVBoxLayout(shadingBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        PhongButton = new QRadioButton(shadingBox);
        PhongButton->setObjectName(QStringLiteral("PhongButton"));
        PhongButton->setChecked(true);

        verticalLayout_2->addWidget(PhongButton);

        NormalButton = new QRadioButton(shadingBox);
        NormalButton->setObjectName(QStringLiteral("NormalButton"));

        verticalLayout_2->addWidget(NormalButton);

        GouraudButton = new QRadioButton(shadingBox);
        GouraudButton->setObjectName(QStringLiteral("GouraudButton"));

        verticalLayout_2->addWidget(GouraudButton);


        formLayout->setWidget(3, QFormLayout::LabelRole, shadingBox);

        uniformsBox = new QGroupBox(settingsBox);
        uniformsBox->setObjectName(QStringLiteral("uniformsBox"));
        verticalLayout_5 = new QVBoxLayout(uniformsBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        materialIntensity = new QVBoxLayout();
        materialIntensity->setSpacing(6);
        materialIntensity->setObjectName(QStringLiteral("materialIntensity"));
        label = new QLabel(uniformsBox);
        label->setObjectName(QStringLiteral("label"));

        materialIntensity->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        materialIntensity1 = new QDoubleSpinBox(uniformsBox);
        materialIntensity1->setObjectName(QStringLiteral("materialIntensity1"));
        materialIntensity1->setDecimals(1);
        materialIntensity1->setMaximum(1);
        materialIntensity1->setSingleStep(0.1);
        materialIntensity1->setValue(0.2);

        horizontalLayout_3->addWidget(materialIntensity1);

        materialIntensity2 = new QDoubleSpinBox(uniformsBox);
        materialIntensity2->setObjectName(QStringLiteral("materialIntensity2"));
        materialIntensity2->setDecimals(1);
        materialIntensity2->setMaximum(1);
        materialIntensity2->setSingleStep(0.1);
        materialIntensity2->setValue(0.8);

        horizontalLayout_3->addWidget(materialIntensity2);

        materialIntensity3 = new QDoubleSpinBox(uniformsBox);
        materialIntensity3->setObjectName(QStringLiteral("materialIntensity3"));
        materialIntensity3->setDecimals(1);
        materialIntensity3->setMaximum(1);
        materialIntensity3->setSingleStep(0.1);
        materialIntensity3->setValue(0.5);

        horizontalLayout_3->addWidget(materialIntensity3);


        materialIntensity->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(materialIntensity);

        lightPosition = new QVBoxLayout();
        lightPosition->setSpacing(6);
        lightPosition->setObjectName(QStringLiteral("lightPosition"));
        label_2 = new QLabel(uniformsBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        lightPosition->addWidget(label_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lp1 = new QDoubleSpinBox(uniformsBox);
        lp1->setObjectName(QStringLiteral("lp1"));
        lp1->setDecimals(1);
        lp1->setMinimum(-20);
        lp1->setMaximum(20);
        lp1->setValue(0);

        horizontalLayout_4->addWidget(lp1);

        lp2 = new QDoubleSpinBox(uniformsBox);
        lp2->setObjectName(QStringLiteral("lp2"));
        lp2->setDecimals(1);
        lp2->setMinimum(-20);
        lp2->setMaximum(20);
        lp2->setValue(0);

        horizontalLayout_4->addWidget(lp2);

        lp3 = new QDoubleSpinBox(uniformsBox);
        lp3->setObjectName(QStringLiteral("lp3"));
        lp3->setDecimals(1);
        lp3->setMinimum(-20);
        lp3->setMaximum(20);
        lp3->setValue(10);

        horizontalLayout_4->addWidget(lp3);


        lightPosition->addLayout(horizontalLayout_4);


        verticalLayout_5->addLayout(lightPosition);


        formLayout->setWidget(4, QFormLayout::SpanningRole, uniformsBox);

        label_3 = new QLabel(settingsBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        phongExponent = new QSpinBox(settingsBox);
        phongExponent->setObjectName(QStringLiteral("phongExponent"));
        phongExponent->setMaximum(10000);
        phongExponent->setValue(16);

        horizontalLayout_5->addWidget(phongExponent);


        formLayout->setLayout(7, QFormLayout::FieldRole, horizontalLayout_5);

        rotationSpeed = new QSpinBox(settingsBox);
        rotationSpeed->setObjectName(QStringLiteral("rotationSpeed"));
        rotationSpeed->setValue(1);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotationSpeed);


        horizontalLayout->addWidget(settingsBox);

        mainView = new MainView(centralWidget);
        mainView->setObjectName(QStringLiteral("mainView"));

        horizontalLayout->addWidget(mainView);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        settingsBox->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        rotationBox->setTitle(QApplication::translate("MainWindow", "Rotation", nullptr));
#ifndef QT_NO_TOOLTIP
        RotationDialX->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the X-axis</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialY->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Y-axis</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialZ->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Z-axis</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ResetRotationButton->setText(QApplication::translate("MainWindow", "Reset Rotation", nullptr));
        zoomBox->setTitle(QApplication::translate("MainWindow", "Zoom", nullptr));
        ResetZoomButton->setText(QApplication::translate("MainWindow", "Reset Zoom", nullptr));
        RotationSpeed_2->setText(QApplication::translate("MainWindow", "Rotation Speed", nullptr));
        shadingBox->setTitle(QApplication::translate("MainWindow", "Shading", nullptr));
        PhongButton->setText(QApplication::translate("MainWindow", "Pho&ng", nullptr));
        NormalButton->setText(QApplication::translate("MainWindow", "Nor&mal", nullptr));
        GouraudButton->setText(QApplication::translate("MainWindow", "&Gouraud", nullptr));
        uniformsBox->setTitle(QApplication::translate("MainWindow", "Uniforms", nullptr));
        label->setText(QApplication::translate("MainWindow", "Material Intensity", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Light Position", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Phong Exponent", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
