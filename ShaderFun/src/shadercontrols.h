#ifndef SHADERCONTROLS_H
#define SHADERCONTROLS_H

#include <QWidget>

namespace Ui {
class ShaderControls;
}

class ShaderControls : public QWidget
{
    Q_OBJECT

public:
    explicit ShaderControls(QWidget *parent = 0);
    ~ShaderControls();

    Ui::ShaderControls *ui;

public slots:
    void slot_setCurrentModel(int);
    void slot_setCurrentSurfaceShaderProgram(int);
    void slot_setCurrentPostprocessShaderProgram(int);
    void slot_setCurrentPostSurfaceShaderProgram(int);
    void slot_setCurrentMatcapTexture(int);
    void slot_setInstancedGridRes(double);
    void slot_setInstancedGridSpacing(int);
    void slot_makeIGridSeethrough(int);
    void slot_shadeIGridLambert(int);
    void slot_setModelRotationFLag(int);

signals:
    void sig_setCurrentModel(int);
    void sig_setCurrentSurfaceShaderProgram(int);
    void sig_setCurrentPostprocessShaderProgram(int);
    void sig_setCurrentPostSurfaceShaderProgram(int);
    void sig_setCurrentMatcapTexture(int);
    void sig_setInstancedGridRes(double);
    void sig_setInstancedGridSpacing(int);
    void sig_makeIGridSeethrough(int);
    void sig_shadeIGridLambert(int);
    void sig_setModelRotationFLag(int);
};

#endif // SHADERCONTROLS_H
