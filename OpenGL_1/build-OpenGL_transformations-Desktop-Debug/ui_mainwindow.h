/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
    QGroupBox *scalingBox;
    QVBoxLayout *verticalLayout_4;
    QSlider *ScaleSlider;
    QPushButton *ResetScaleButton;
    QGroupBox *shadingBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *PhongButton;
    QRadioButton *NormalButton;
    QRadioButton *GouraudButton;
    QGroupBox *uniformsBox;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *materialColor;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *materialColor1;
    QDoubleSpinBox *materialColor2;
    QDoubleSpinBox *materialColor3;
    QVBoxLayout *lightPosition;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *lp1;
    QDoubleSpinBox *lp2;
    QDoubleSpinBox *lp3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *phongExponent;
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

        scalingBox = new QGroupBox(settingsBox);
        scalingBox->setObjectName(QStringLiteral("scalingBox"));
        sizePolicy.setHeightForWidth(scalingBox->sizePolicy().hasHeightForWidth());
        scalingBox->setSizePolicy(sizePolicy);
        scalingBox->setMinimumSize(QSize(205, 0));
        scalingBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout_4 = new QVBoxLayout(scalingBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        ScaleSlider = new QSlider(scalingBox);
        ScaleSlider->setObjectName(QStringLiteral("ScaleSlider"));
        ScaleSlider->setMinimum(1);
        ScaleSlider->setMaximum(200);
        ScaleSlider->setValue(100);
        ScaleSlider->setOrientation(Qt::Horizontal);
        ScaleSlider->setInvertedAppearance(false);
        ScaleSlider->setInvertedControls(false);
        ScaleSlider->setTickPosition(QSlider::NoTicks);

        verticalLayout_4->addWidget(ScaleSlider);

        ResetScaleButton = new QPushButton(scalingBox);
        ResetScaleButton->setObjectName(QStringLiteral("ResetScaleButton"));

        verticalLayout_4->addWidget(ResetScaleButton);


        formLayout->setWidget(1, QFormLayout::LabelRole, scalingBox);

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


        formLayout->setWidget(2, QFormLayout::LabelRole, shadingBox);

        uniformsBox = new QGroupBox(settingsBox);
        uniformsBox->setObjectName(QStringLiteral("uniformsBox"));
        verticalLayout_5 = new QVBoxLayout(uniformsBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        materialColor = new QVBoxLayout();
        materialColor->setSpacing(6);
        materialColor->setObjectName(QStringLiteral("materialColor"));
        label = new QLabel(uniformsBox);
        label->setObjectName(QStringLiteral("label"));

        materialColor->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        materialColor1 = new QDoubleSpinBox(uniformsBox);
        materialColor1->setObjectName(QStringLiteral("materialColor1"));
        materialColor1->setDecimals(1);
        materialColor1->setMaximum(1);
        materialColor1->setSingleStep(0.1);

        horizontalLayout_3->addWidget(materialColor1);

        materialColor2 = new QDoubleSpinBox(uniformsBox);
        materialColor2->setObjectName(QStringLiteral("materialColor2"));
        materialColor2->setDecimals(1);
        materialColor2->setMaximum(1);
        materialColor2->setSingleStep(0.1);

        horizontalLayout_3->addWidget(materialColor2);

        materialColor3 = new QDoubleSpinBox(uniformsBox);
        materialColor3->setObjectName(QStringLiteral("materialColor3"));
        materialColor3->setDecimals(1);
        materialColor3->setMaximum(1);
        materialColor3->setSingleStep(0.1);

        horizontalLayout_3->addWidget(materialColor3);


        materialColor->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(materialColor);

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
        lp1->setValue(10);

        horizontalLayout_4->addWidget(lp1);

        lp2 = new QDoubleSpinBox(uniformsBox);
        lp2->setObjectName(QStringLiteral("lp2"));
        lp2->setDecimals(1);
        lp2->setMinimum(-20);
        lp2->setMaximum(20);
        lp2->setValue(10);

        horizontalLayout_4->addWidget(lp2);

        lp3 = new QDoubleSpinBox(uniformsBox);
        lp3->setObjectName(QStringLiteral("lp3"));
        lp3->setDecimals(1);
        lp3->setMinimum(-20);
        lp3->setMaximum(20);
        lp3->setValue(0);

        horizontalLayout_4->addWidget(lp3);


        lightPosition->addLayout(horizontalLayout_4);


        verticalLayout_5->addLayout(lightPosition);


        formLayout->setWidget(3, QFormLayout::SpanningRole, uniformsBox);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        label_3 = new QLabel(settingsBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        phongExponent = new QSpinBox(settingsBox);
        phongExponent->setObjectName(QStringLiteral("phongExponent"));
        phongExponent->setMaximum(10000);
        phongExponent->setValue(16);

        horizontalLayout_5->addWidget(phongExponent);


        formLayout->setLayout(6, QFormLayout::FieldRole, horizontalLayout_5);


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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        settingsBox->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        rotationBox->setTitle(QApplication::translate("MainWindow", "Rotation", 0));
#ifndef QT_NO_TOOLTIP
        RotationDialX->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the X-axis</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialY->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Y-axis</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialZ->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Z-axis</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        ResetRotationButton->setText(QApplication::translate("MainWindow", "Reset Rotation", 0));
        scalingBox->setTitle(QApplication::translate("MainWindow", "Scaling", 0));
        ResetScaleButton->setText(QApplication::translate("MainWindow", "Reset Scaling", 0));
        shadingBox->setTitle(QApplication::translate("MainWindow", "Shading", 0));
        PhongButton->setText(QApplication::translate("MainWindow", "Pho&ng", 0));
        NormalButton->setText(QApplication::translate("MainWindow", "Nor&mal", 0));
        GouraudButton->setText(QApplication::translate("MainWindow", "&Gouraud", 0));
        uniformsBox->setTitle(QApplication::translate("MainWindow", "Uniforms", 0));
        label->setText(QApplication::translate("MainWindow", "Material Color", 0));
        label_2->setText(QApplication::translate("MainWindow", "Light Position", 0));
        label_3->setText(QApplication::translate("MainWindow", "Phong Exponent", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
