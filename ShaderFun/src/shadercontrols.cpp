#include "shadercontrols.h"
#include "ui_shadercontrols.h"


ShaderControls::ShaderControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShaderControls)
{
    ui->setupUi(this);

    connect(ui->modelComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_setCurrentModel(int)));
    connect(ui->surfaceShaderComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_setCurrentSurfaceShaderProgram(int)));
    connect(ui->postprocessShaderComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_setCurrentPostprocessShaderProgram(int)));
    connect(ui->postsurfaceShaderComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_setCurrentPostSurfaceShaderProgram(int)));
    connect(ui->matcapComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_setCurrentMatcapTexture(int)));

    connect(ui->resSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_setInstancedGridRes(double)));
    connect(ui->spacingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slot_setInstancedGridSpacing(int)));

    connect(ui->seethroughCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slot_makeIGridSeethrough(int)));
    connect(ui->shadeLambertCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slot_shadeIGridLambert(int)));
    connect(ui->rotModelsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slot_setModelRotationFLag(int)));
}


ShaderControls::~ShaderControls()
{
    delete ui;
}

void ShaderControls::slot_setCurrentModel(int i)
{
    emit sig_setCurrentModel(i);
}

void ShaderControls::slot_setCurrentSurfaceShaderProgram(int i)
{
    emit sig_setCurrentSurfaceShaderProgram(i);
}

void ShaderControls::slot_setCurrentPostprocessShaderProgram(int i)
{
    emit sig_setCurrentPostprocessShaderProgram(i);
}

void ShaderControls::slot_setCurrentPostSurfaceShaderProgram(int i)
{
    emit sig_setCurrentPostSurfaceShaderProgram(i);
}

void ShaderControls::slot_setCurrentMatcapTexture(int i)
{
    emit sig_setCurrentMatcapTexture(i);
}

void ShaderControls::slot_setInstancedGridRes(double d)
{
    emit sig_setInstancedGridRes(d);
}

void ShaderControls::slot_setInstancedGridSpacing(int s)
{
    emit sig_setInstancedGridSpacing(s);
}

void ShaderControls::slot_makeIGridSeethrough(int s)
{
    emit sig_makeIGridSeethrough(s);
}

void ShaderControls::slot_shadeIGridLambert(int s)
{
    emit sig_shadeIGridLambert(s);
}

void ShaderControls::slot_setModelRotationFLag(int s)
{
    emit sig_setModelRotationFLag(s);
}
