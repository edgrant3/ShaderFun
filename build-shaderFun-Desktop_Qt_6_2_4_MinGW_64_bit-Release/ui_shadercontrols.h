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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
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

    void setupUi(QWidget *ShaderControls)
    {
        if (ShaderControls->objectName().isEmpty())
            ShaderControls->setObjectName(QString::fromUtf8("ShaderControls"));
        ShaderControls->resize(250, 377);
        groupBox_2 = new QGroupBox(ShaderControls);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 201, 61));
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
        groupBox->setGeometry(QRect(10, 50, 201, 61));
        groupBox->setFont(font);
        surfaceShaderComboBox = new QComboBox(groupBox);
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->addItem(QString());
        surfaceShaderComboBox->setObjectName(QString::fromUtf8("surfaceShaderComboBox"));
        surfaceShaderComboBox->setGeometry(QRect(10, 30, 141, 22));
        surfaceShaderComboBox->setFont(font);
        groupBox_3 = new QGroupBox(ShaderControls);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 190, 201, 61));
        groupBox_3->setFont(font);
        modelComboBox = new QComboBox(groupBox_3);
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->setObjectName(QString::fromUtf8("modelComboBox"));
        modelComboBox->setGeometry(QRect(10, 30, 141, 22));
        modelComboBox->setFont(font);
        tabWidget = new QTabWidget(ShaderControls);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 270, 201, 81));
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
        postprocessShaderComboBox->setItemText(7, QCoreApplication::translate("ShaderControls", "FBM", nullptr));
        postprocessShaderComboBox->setItemText(8, QCoreApplication::translate("ShaderControls", "Test FBM", nullptr));
        postprocessShaderComboBox->setItemText(9, QCoreApplication::translate("ShaderControls", "Perlin", nullptr));
        postprocessShaderComboBox->setItemText(10, QCoreApplication::translate("ShaderControls", "Perlin FBM", nullptr));

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
        modelComboBox->setItemText(2, QCoreApplication::translate("ShaderControls", "Cube", nullptr));
        modelComboBox->setItemText(3, QCoreApplication::translate("ShaderControls", "Instanced Cubes", nullptr));

        matcapComboBox->setItemText(0, QCoreApplication::translate("ShaderControls", "Red Clay", nullptr));
        matcapComboBox->setItemText(1, QCoreApplication::translate("ShaderControls", "Red Plastic", nullptr));
        matcapComboBox->setItemText(2, QCoreApplication::translate("ShaderControls", "Chrome", nullptr));
        matcapComboBox->setItemText(3, QCoreApplication::translate("ShaderControls", "Pearl", nullptr));
        matcapComboBox->setItemText(4, QCoreApplication::translate("ShaderControls", "Orange-Green", nullptr));
        matcapComboBox->setItemText(5, QCoreApplication::translate("ShaderControls", "Blue-Purple", nullptr));
        matcapComboBox->setItemText(6, QCoreApplication::translate("ShaderControls", "Outline", nullptr));
        matcapComboBox->setItemText(7, QCoreApplication::translate("ShaderControls", "Surface Normals", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(matcapTab), QCoreApplication::translate("ShaderControls", "Matcap Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShaderControls: public Ui_ShaderControls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADERCONTROLS_H
