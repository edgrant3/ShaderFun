/********************************************************************************
** Form generated from reading UI file 'shadercontrols.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHADERCONTROLS_H
#define UI_SHADERCONTROLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShaderControls
{
public:
    QGroupBox *groupBox_2;
    QComboBox *postprocessShaderComboBox;
    QLabel *label;
    QGroupBox *groupBox;
    QComboBox *surfaceShaderComboBox;
    QGroupBox *groupBox_3;
    QComboBox *modelComboBox;
    QTabWidget *tabWidget;
    QWidget *matcapTab;
    QComboBox *matcapComboBox;
    QGroupBox *groupBox_4;
    QComboBox *postsurfaceShaderComboBox;
    QDoubleSpinBox *resSpinBox;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spacingSpinBox;
    QCheckBox *seethroughCheckBox;
    QCheckBox *shadeLambertCheckBox;
    QCheckBox *rotModelsCheckBox;

    void setupUi(QWidget *ShaderControls)
    {
        if (ShaderControls->objectName().isEmpty())
            ShaderControls->setObjectName(QString::fromUtf8("ShaderControls"));
        ShaderControls->resize(281, 614);
        ShaderControls->setAutoFillBackground(false);
        groupBox_2 = new QGroupBox(ShaderControls);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 510, 231, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Gadugi")});
        groupBox_2->setFont(font);
        postprocessShaderComboBox = new QComboBox(groupBox_2);
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->addItem(QString());
        postprocessShaderComboBox->setObjectName(QString::fromUtf8("postprocessShaderComboBox"));
        postprocessShaderComboBox->setGeometry(QRect(10, 30, 141, 22));
        postprocessShaderComboBox->setFont(font);
        label = new QLabel(ShaderControls);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 241, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gadugi")});
        font1.setPointSize(16);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(ShaderControls);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 150, 231, 61));
        groupBox->setFont(font);
        surfaceShaderComboBox = new QComboBox(groupBox);
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->setObjectName(QString::fromUtf8("surfaceShaderComboBox"));
        surfaceShaderComboBox->setGeometry(QRect(10, 30, 151, 22));
        surfaceShaderComboBox->setFont(font);
        groupBox_3 = new QGroupBox(ShaderControls);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 50, 231, 61));
        groupBox_3->setFont(font);
        modelComboBox = new QComboBox(groupBox_3);
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->setObjectName(QString::fromUtf8("modelComboBox"));
        modelComboBox->setGeometry(QRect(10, 30, 151, 22));
        modelComboBox->setFont(font);
        tabWidget = new QTabWidget(ShaderControls);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(40, 220, 211, 71));
        tabWidget->setFont(font);
        matcapTab = new QWidget();
        matcapTab->setObjectName(QString::fromUtf8("matcapTab"));
        matcapComboBox = new QComboBox(matcapTab);
        matcapComboBox->addItem(QString());
        matcapComboBox->addItem(QString());
        matcapComboBox->addItem(QString());
        matcapComboBox->addItem(QString());
        matcapComboBox->addItem(QString());
        matcapComboBox->addItem(QString());
        matcapComboBox->addItem(QString());
        matcapComboBox->addItem(QString());
        matcapComboBox->setObjectName(QString::fromUtf8("matcapComboBox"));
        matcapComboBox->setGeometry(QRect(10, 10, 141, 22));
        matcapComboBox->setFont(font);
        tabWidget->addTab(matcapTab, QString());
        groupBox_4 = new QGroupBox(ShaderControls);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 320, 241, 61));
        groupBox_4->setFont(font);
        postsurfaceShaderComboBox = new QComboBox(groupBox_4);
        postsurfaceShaderComboBox->addItem(QString());
        postsurfaceShaderComboBox->addItem(QString());
        postsurfaceShaderComboBox->addItem(QString());
        postsurfaceShaderComboBox->addItem(QString());
        postsurfaceShaderComboBox->setObjectName(QString::fromUtf8("postsurfaceShaderComboBox"));
        postsurfaceShaderComboBox->setGeometry(QRect(10, 30, 141, 22));
        postsurfaceShaderComboBox->setFont(font);
        resSpinBox = new QDoubleSpinBox(ShaderControls);
        resSpinBox->setObjectName(QString::fromUtf8("resSpinBox"));
        resSpinBox->setGeometry(QRect(200, 390, 61, 25));
        resSpinBox->setMinimum(0.050000000000000);
        resSpinBox->setMaximum(1.000000000000000);
        resSpinBox->setSingleStep(0.050000000000000);
        resSpinBox->setValue(0.150000000000000);
        label_2 = new QLabel(ShaderControls);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 390, 61, 20));
        label_3 = new QLabel(ShaderControls);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 420, 121, 20));
        spacingSpinBox = new QSpinBox(ShaderControls);
        spacingSpinBox->setObjectName(QString::fromUtf8("spacingSpinBox"));
        spacingSpinBox->setGeometry(QRect(200, 420, 61, 25));
        spacingSpinBox->setMaximum(200);
        spacingSpinBox->setSingleStep(10);
        seethroughCheckBox = new QCheckBox(ShaderControls);
        seethroughCheckBox->setObjectName(QString::fromUtf8("seethroughCheckBox"));
        seethroughCheckBox->setGeometry(QRect(130, 450, 131, 22));
        seethroughCheckBox->setCursor(QCursor(Qt::PointingHandCursor));
        seethroughCheckBox->setLayoutDirection(Qt::RightToLeft);
        seethroughCheckBox->setAutoFillBackground(false);
        shadeLambertCheckBox = new QCheckBox(ShaderControls);
        shadeLambertCheckBox->setObjectName(QString::fromUtf8("shadeLambertCheckBox"));
        shadeLambertCheckBox->setGeometry(QRect(130, 470, 131, 22));
        shadeLambertCheckBox->setCursor(QCursor(Qt::PointingHandCursor));
        shadeLambertCheckBox->setLayoutDirection(Qt::RightToLeft);
        shadeLambertCheckBox->setAutoFillBackground(false);
        rotModelsCheckBox = new QCheckBox(ShaderControls);
        rotModelsCheckBox->setObjectName(QString::fromUtf8("rotModelsCheckBox"));
        rotModelsCheckBox->setGeometry(QRect(120, 120, 131, 22));
        rotModelsCheckBox->setCursor(QCursor(Qt::PointingHandCursor));
        rotModelsCheckBox->setLayoutDirection(Qt::RightToLeft);
        rotModelsCheckBox->setAutoFillBackground(false);

        retranslateUi(ShaderControls);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ShaderControls);
    } // setupUi

    void retranslateUi(QWidget *ShaderControls)
    {
        ShaderControls->setWindowTitle(QCoreApplication::translate("ShaderControls", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ShaderControls", "Post-Process Shader", nullptr));
        postprocessShaderComboBox->setItemText(0, QCoreApplication::translate("ShaderControls", "None", nullptr));
        postprocessShaderComboBox->setItemText(1, QCoreApplication::translate("ShaderControls", "Greyscale", nullptr));
        postprocessShaderComboBox->setItemText(2, QCoreApplication::translate("ShaderControls", "Gaussian Blur", nullptr));
        postprocessShaderComboBox->setItemText(3, QCoreApplication::translate("ShaderControls", "Sobel", nullptr));
        postprocessShaderComboBox->setItemText(4, QCoreApplication::translate("ShaderControls", "Bloom", nullptr));
        postprocessShaderComboBox->setItemText(5, QCoreApplication::translate("ShaderControls", "Worley Noise", nullptr));
        postprocessShaderComboBox->setItemText(6, QCoreApplication::translate("ShaderControls", "Fast Worley", nullptr));
        postprocessShaderComboBox->setItemText(7, QCoreApplication::translate("ShaderControls", "Depth", nullptr));
        postprocessShaderComboBox->setItemText(8, QCoreApplication::translate("ShaderControls", "FBM", nullptr));
        postprocessShaderComboBox->setItemText(9, QCoreApplication::translate("ShaderControls", "Test FBM", nullptr));
        postprocessShaderComboBox->setItemText(10, QCoreApplication::translate("ShaderControls", "Perlin", nullptr));
        postprocessShaderComboBox->setItemText(11, QCoreApplication::translate("ShaderControls", "Perlin FBM", nullptr));

        label->setText(QCoreApplication::translate("ShaderControls", "Shader Options", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ShaderControls", "Surface Shader", nullptr));
        surfaceShaderComboBox->setItemText(0, QCoreApplication::translate("ShaderControls", "Lambert", nullptr));
        surfaceShaderComboBox->setItemText(1, QCoreApplication::translate("ShaderControls", "Blinn-Phong", nullptr));
        surfaceShaderComboBox->setItemText(2, QCoreApplication::translate("ShaderControls", "Matcap", nullptr));
        surfaceShaderComboBox->setItemText(3, QCoreApplication::translate("ShaderControls", "Color Gradient", nullptr));
        surfaceShaderComboBox->setItemText(4, QCoreApplication::translate("ShaderControls", "Vertex Deformation", nullptr));
        surfaceShaderComboBox->setItemText(5, QCoreApplication::translate("ShaderControls", "Instanced", nullptr));

        groupBox_3->setTitle(QCoreApplication::translate("ShaderControls", "Model", nullptr));
        modelComboBox->setItemText(0, QCoreApplication::translate("ShaderControls", "Wahoo", nullptr));
        modelComboBox->setItemText(1, QCoreApplication::translate("ShaderControls", "Moo Beast", nullptr));
        modelComboBox->setItemText(2, QCoreApplication::translate("ShaderControls", "Minecraft", nullptr));
        modelComboBox->setItemText(3, QCoreApplication::translate("ShaderControls", "Sammy", nullptr));
        modelComboBox->setItemText(4, QCoreApplication::translate("ShaderControls", "Cube", nullptr));
        modelComboBox->setItemText(5, QCoreApplication::translate("ShaderControls", "Instanced Cube", nullptr));
        modelComboBox->setItemText(6, QCoreApplication::translate("ShaderControls", "Instanced Sphere", nullptr));
        modelComboBox->setItemText(7, QCoreApplication::translate("ShaderControls", "Instanced Monkey", nullptr));

        matcapComboBox->setItemText(0, QCoreApplication::translate("ShaderControls", "Red Clay", nullptr));
        matcapComboBox->setItemText(1, QCoreApplication::translate("ShaderControls", "Red Plastic", nullptr));
        matcapComboBox->setItemText(2, QCoreApplication::translate("ShaderControls", "Chrome", nullptr));
        matcapComboBox->setItemText(3, QCoreApplication::translate("ShaderControls", "Pearl", nullptr));
        matcapComboBox->setItemText(4, QCoreApplication::translate("ShaderControls", "Orange-Green", nullptr));
        matcapComboBox->setItemText(5, QCoreApplication::translate("ShaderControls", "Blue-Purple", nullptr));
        matcapComboBox->setItemText(6, QCoreApplication::translate("ShaderControls", "Outline", nullptr));
        matcapComboBox->setItemText(7, QCoreApplication::translate("ShaderControls", "Surface Normals", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(matcapTab), QCoreApplication::translate("ShaderControls", "Matcap Options", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ShaderControls", "Post-Surface Shader ", nullptr));
        postsurfaceShaderComboBox->setItemText(0, QCoreApplication::translate("ShaderControls", "None", nullptr));
        postsurfaceShaderComboBox->setItemText(1, QCoreApplication::translate("ShaderControls", "Cube Voxels", nullptr));
        postsurfaceShaderComboBox->setItemText(2, QCoreApplication::translate("ShaderControls", "Sphere Voxels", nullptr));
        postsurfaceShaderComboBox->setItemText(3, QCoreApplication::translate("ShaderControls", "Monkey Voxels", nullptr));

        label_2->setText(QCoreApplication::translate("ShaderControls", "Voxel Size", nullptr));
        label_3->setText(QCoreApplication::translate("ShaderControls", "Voxel Grid Spacing %", nullptr));
        seethroughCheckBox->setText(QCoreApplication::translate("ShaderControls", "Active Camo   ", nullptr));
        shadeLambertCheckBox->setText(QCoreApplication::translate("ShaderControls", "Shade Lambert   ", nullptr));
        rotModelsCheckBox->setText(QCoreApplication::translate("ShaderControls", "Rotate Models   ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShaderControls: public Ui_ShaderControls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADERCONTROLS_H
