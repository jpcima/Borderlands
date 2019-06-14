#include "interface/CloudDialog.h"
#include "ui_CloudDialog.h"
#include "model/ParamCloud.h"
#include <iostream>
#include <stdio.h>

extern ValueMin g_cloudValueMin;
extern ValueMax g_cloudValueMax;
extern CloudParams g_defaultCloudParams;

CloudDialog::CloudDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloudDialog)
{
    setModal(false);
    ui->setupUi(this);

    ui->doubleSpinBox_Volume->setMinimum(g_cloudValueMin.volumeDB);
    ui->doubleSpinBox_Volume->setMaximum(g_cloudValueMax.volumeDB);
    ui->verticalSlider_Volume->setMinimum(g_cloudValueMin.volumeDB * 1000);
    ui->verticalSlider_Volume->setMaximum(g_cloudValueMax.volumeDB * 1000);

    ui->doubleSpinBox_Grains->setMinimum(g_cloudValueMin.numGrains);
    ui->doubleSpinBox_Grains->setMaximum(g_cloudValueMax.numGrains);
    ui->dial_Grains->setMinimum(g_cloudValueMin.numGrains);
    ui->dial_Grains->setMaximum(g_cloudValueMax.numGrains);

    ui->doubleSpinBox_Duration->setMinimum(g_cloudValueMin.duration);
    ui->doubleSpinBox_Duration->setMaximum(g_cloudValueMax.duration);
    ui->dial_Duration->setMinimum(g_cloudValueMin.duration);
    ui->dial_Duration->setMaximum(g_cloudValueMax.duration);

    ui->doubleSpinBox_Overlap->setMinimum(g_cloudValueMin.overlap);
    ui->doubleSpinBox_Overlap->setMaximum(g_cloudValueMax.overlap);
    ui->dial_Overlap->setMaximum(g_cloudValueMax.overlap * 100);
    ui->dial_Overlap->setMinimum(g_cloudValueMin.overlap * 100);

    ui->doubleSpinBox_Pitch->setMinimum(g_cloudValueMin.pitch);
    ui->doubleSpinBox_Pitch->setMaximum(g_cloudValueMax.pitch);
    ui->dial_Pitch->setMaximum(g_cloudValueMax.pitch * 100);
    ui->dial_Pitch->setMinimum(g_cloudValueMin.pitch * 100);

    ui->doubleSpinBox_LFO_Freq->setMinimum(g_cloudValueMin.pitchLFOFreq);
    ui->doubleSpinBox_LFO_Freq->setMaximum(g_cloudValueMax.pitchLFOFreq);
    ui->dial_LFO_Freq->setMaximum(g_cloudValueMax.pitchLFOFreq * 100);
    ui->dial_LFO_Freq->setMinimum(g_cloudValueMin.pitchLFOFreq * 100);

    ui->doubleSpinBox_LFO_Amp->setMinimum(g_cloudValueMin.pitchLFOAmount);
    ui->doubleSpinBox_LFO_Amp->setMaximum(g_cloudValueMax.pitchLFOAmount);
    ui->dial_LFO_Amp->setMaximum(g_cloudValueMax.pitchLFOAmount * 1000);
    ui->dial_LFO_Amp->setMinimum(g_cloudValueMin.pitchLFOAmount * 1000);

    ui->doubleSpinBox_X->setMinimum(g_cloudValueMin.x);
    ui->doubleSpinBox_X->setMaximum(g_cloudValueMax.x);
    ui->dial_X->setMaximum(g_cloudValueMax.x);
    ui->dial_X->setMinimum(g_cloudValueMin.x);

    ui->doubleSpinBox_Y->setMinimum(g_cloudValueMin.y);
    ui->doubleSpinBox_Y->setMaximum(g_cloudValueMax.y);
    ui->dial_Y->setMaximum(g_cloudValueMax.y);
    ui->dial_Y->setMinimum(g_cloudValueMin.y);

    ui->doubleSpinBox_X_Extent->setMinimum(g_cloudValueMin.xRandExtent);
    ui->doubleSpinBox_X_Extent->setMaximum(g_cloudValueMax.xRandExtent);
    ui->dial_X_Extent->setMaximum(g_cloudValueMax.xRandExtent);
    ui->dial_X_Extent->setMinimum(g_cloudValueMin.xRandExtent);

    ui->doubleSpinBox_Y_Extent->setMinimum(g_cloudValueMin.yRandExtent);
    ui->doubleSpinBox_Y_Extent->setMaximum(g_cloudValueMax.yRandExtent);
    ui->dial_Y_Extent->setMaximum(g_cloudValueMax.yRandExtent);
    ui->dial_X_Extent->setMinimum(g_cloudValueMin.yRandExtent);

    ui->doubleSpinBox_Angle->setMinimum(g_cloudValueMin.angle);
    ui->doubleSpinBox_Angle->setMaximum(g_cloudValueMax.angle);
    ui->dial_Angle->setMaximum(g_cloudValueMax.angle);
    ui->dial_Angle->setMinimum(g_cloudValueMin.angle);

    ui->doubleSpinBox_Strech->setMinimum(g_cloudValueMin.strech);
    ui->doubleSpinBox_Strech->setMaximum(g_cloudValueMax.strech);
    ui->dial_Strech->setMaximum(g_cloudValueMax.strech);
    ui->dial_Strech->setMinimum(g_cloudValueMin.strech);

    ui->doubleSpinBox_Speed->setMinimum(g_cloudValueMin.speed);
    ui->doubleSpinBox_Speed->setMaximum(g_cloudValueMax.speed);
    ui->dial_Speed->setMaximum(g_cloudValueMax.speed);
    ui->dial_Speed->setMinimum(g_cloudValueMin.speed);

    ui->doubleSpinBox_Radius->setMinimum(g_cloudValueMin.radius);
    ui->doubleSpinBox_Radius->setMaximum(g_cloudValueMax.radius);
    ui->dial_Radius->setMaximum(g_cloudValueMax.radius);
    ui->dial_Radius->setMinimum(g_cloudValueMin.radius);

    ui->doubleSpinBox_RadiusInt->setMinimum(g_cloudValueMin.radiusInt);
    ui->doubleSpinBox_RadiusInt->setMaximum(g_cloudValueMax.radiusInt);
    ui->dial_RadiusInt->setMaximum(g_cloudValueMax.radiusInt);
    ui->dial_RadiusInt->setMinimum(g_cloudValueMin.radiusInt);

    ui->doubleSpinBox_Expansion->setMinimum(g_cloudValueMin.radiusInt);
    ui->doubleSpinBox_Expansion->setMaximum(g_cloudValueMax.radiusInt);
    ui->dial_Expansion->setMaximum(g_cloudValueMax.expansion);
    ui->dial_Expansion->setMinimum(g_cloudValueMin.expansion);

    ui->doubleSpinBox_Output_First->setMinimum(0);
    ui->doubleSpinBox_Output_Last->setMinimum(0);
    ui->doubleSpinBox_Output_First->setMaximum(theChannelCount - 1);
    ui->doubleSpinBox_Output_Last->setMaximum(theChannelCount - 1);

    QTimer *tmAutoUpdate = new QTimer(this);
    connect(tmAutoUpdate, &QTimer::timeout, this, &CloudDialog::autoUpdate);
    tmAutoUpdate->start(500);
}

CloudDialog::~CloudDialog()
{
    delete ui;
}

void CloudDialog::autoUpdate()
{
    autoUpdating = true;
    if (cloudRef && cloudVisRef)
        linkCloud(cloudRef, cloudVisRef);
    autoUpdating = false;
}

void CloudDialog::linkCloud(Cloud *cloudLinked, CloudVis *cloudVisLinked)
{
    if (editing == true)
        return;
    linking = true;
    cloudRef = cloudLinked;
    cloudVisRef = cloudVisLinked;
    if (cloudLinked->changedDurationMs())
        ui->doubleSpinBox_Duration->setValue(cloudLinked->getDurationMs());
    if (cloudLinked->changedNumGrains())
        ui->doubleSpinBox_Grains ->setValue(cloudLinked->getNumGrains());
    if (cloudLinked->changedPitchLFOAmount())
        ui->doubleSpinBox_LFO_Amp->setValue(cloudLinked->getPitchLFOAmount());
    if (cloudLinked->changedPitchLFOFreq())
        ui->doubleSpinBox_LFO_Freq->setValue(cloudLinked->getPitchLFOFreq());
    if (cloudLinked->changedOverlap())
        ui->doubleSpinBox_Overlap->setValue(cloudLinked->getOverlap());
    if (cloudLinked->changedVolumeDb())
        ui->doubleSpinBox_Volume->setValue(cloudLinked->getVolumeDb());
    if (cloudLinked->changedPitch())
        //ui->doubleSpinBox_Pitch->setValue(12*log2(cloudLinked->getPitch()));
        ui->doubleSpinBox_Pitch->setValue(cloudLinked->getPitch());
    if (cloudVisLinked->changedXRandExtent())
        ui->doubleSpinBox_X_Extent->setValue(cloudVisLinked->getXRandExtent());
    if (cloudVisLinked->changedYRandExtent())
        ui->doubleSpinBox_Y_Extent->setValue(cloudVisLinked->getYRandExtent());
    if (cloudVisLinked->changedGcX())
        ui->doubleSpinBox_X->setValue(cloudVisLinked->getOriginX());
    if (cloudVisLinked->changedGcY())
        ui->doubleSpinBox_Y->setValue(cloudVisLinked->getOriginY());
    if (cloudLinked->changedMidiNote())
        ui->doubleSpinBox_Midi_Note->setValue(cloudLinked->getMidiNote());
    ui->label_Id_Value->setText(QString::number(cloudLinked->getId()));
  //  if (cloudLinked->changedName())
    if (autoUpdating == false)
        ui->lineEdit_Name->setText(cloudLinked->getName());
    ui->checkBox_Active->setChecked(cloudLinked->getActiveState());
    ui->checkBox_Locked->setChecked(cloudLinked->getLockedState());
    if (cloudLinked->changedDirection())
        switch (cloudLinked->getDirection()) {
        case FORWARD:
            ui->radioButton_Direction_Forward->setChecked(true);
            break;
        case BACKWARD:
            ui->radioButton_Direction_Backward->setChecked(true);
            break;
        case RANDOM_DIR:
            ui->radioButton_Direction_Random->setChecked(true);
            break;
        default :
            break;
        }
    if (cloudLinked->changedSpatialMode()) {
        switch (cloudLinked->getSpatialMode()) {
        case UNITY:
            ui->radioButton_Balance_Unity->setChecked(true);
            break;
        case STEREO:
            ui->radioButton_Balance_Stereo->setChecked(true);
            break;
        case AROUND:
            ui->radioButton_Balance_Around->setChecked(true);
            break;
        default :
            break;
        }
        ui->doubleSpinBox_Output_First->setValue(cloudLinked->getOutputFirst());
        ui->doubleSpinBox_Output_Last->setValue(cloudLinked->getOutputLast());
    }
    if (cloudLinked->changedWindowType())
        switch (cloudLinked->getWindowType()) {
        case HANNING:
            ui->radioButton_Window_Hanning->setChecked(true);
            break;
        case TRIANGLE:
            ui->radioButton_Window_Triangle->setChecked(true);
            break;
        case EXPDEC:
            ui->radioButton_Window_Expdec->setChecked(true);
            break;
        case REXPDEC:
            ui->radioButton_Window_Rexpdec->setChecked(true);
            break;
        case SINC:
            ui->radioButton_Window_Sinc->setChecked(true);
            break;
        case RANDOM_WIN:
            ui->radioButton_Window_Random->setChecked(true);
            break;
        default :
            break;
        }
    if (cloudLinked->changedTrajectoryType())
        switch (cloudLinked->getTrajectoryType()) {
        case STATIC:
            ui->radioButton_Trajectory_Static->setChecked(true);
            ui->doubleSpinBox_Speed->setDisabled(true);
            ui->doubleSpinBox_Radius->setDisabled(true);
            ui->doubleSpinBox_RadiusInt->setDisabled(true);
            ui->doubleSpinBox_Angle->setDisabled(true);
            ui->doubleSpinBox_Strech->setDisabled(true);
            ui->doubleSpinBox_Expansion->setDisabled(true);
            ui->dial_Speed->setDisabled(true);
            ui->dial_Radius->setDisabled(true);
            ui->dial_RadiusInt->setDisabled(true);
            ui->dial_Angle->setDisabled(true);
            ui->dial_Strech->setDisabled(true);
            ui->dial_Expansion->setDisabled(true);
            break;
        case BOUNCING:
        {
            ui->radioButton_Trajectory_Bouncing->setChecked(true);
            ui->doubleSpinBox_Speed->setDisabled(false);
            ui->doubleSpinBox_Radius->setDisabled(false);
            ui->doubleSpinBox_RadiusInt->setDisabled(true);
            ui->doubleSpinBox_Angle->setDisabled(false);
            ui->doubleSpinBox_Strech->setDisabled(true);
            ui->doubleSpinBox_Expansion->setDisabled(true);
            ui->dial_Speed->setDisabled(false);
            ui->dial_Radius->setDisabled(false);
            ui->dial_RadiusInt->setDisabled(true);
            ui->dial_Angle->setDisabled(false);
            ui->dial_Strech->setDisabled(true);
            ui->dial_Expansion->setDisabled(true);
            ui->doubleSpinBox_Speed->setValue(cloudVisLinked->getTrajectory()->getSpeed());
            Circular *b_Traj = dynamic_cast<Circular*>(cloudVisLinked->getTrajectory());
            ui->doubleSpinBox_Radius->setValue(b_Traj->getRadius());
            ui->doubleSpinBox_Angle->setValue(b_Traj->getAngle());
            have_trajectory_bouncing = true;
            break;
        }
        case CIRCULAR:
        {
            ui->radioButton_Trajectory_Circular->setChecked(true);
            ui->doubleSpinBox_Speed->setDisabled(false);
            ui->doubleSpinBox_Radius->setDisabled(false);
            ui->doubleSpinBox_RadiusInt->setDisabled(true);
            ui->doubleSpinBox_Angle->setDisabled(false);
            ui->doubleSpinBox_Strech->setDisabled(false);
            ui->doubleSpinBox_Expansion->setDisabled(true);
            ui->dial_Speed->setDisabled(false);
            ui->dial_Radius->setDisabled(false);
            ui->dial_RadiusInt->setDisabled(true);
            ui->dial_Angle->setDisabled(false);
            ui->dial_Strech->setDisabled(false);
            ui->dial_Expansion->setDisabled(true);
            ui->doubleSpinBox_Speed->setValue(cloudVisLinked->getTrajectory()->getSpeed());
            Circular *c_Traj=dynamic_cast<Circular*>(cloudVisLinked->getTrajectory());
            ui->doubleSpinBox_Radius->setValue(c_Traj->getRadius());
            ui->doubleSpinBox_Angle->setValue(c_Traj->getAngle());
            ui->doubleSpinBox_Strech->setValue(c_Traj->getStrech());
            have_trajectory_circular = true;
            break;
        }
        case HYPOTROCHOID:
        {
            ui->radioButton_Trajectory_Hypotrochoid->setChecked(true);
            ui->doubleSpinBox_Speed->setDisabled(false);
            ui->doubleSpinBox_Radius->setDisabled(false);
            ui->doubleSpinBox_RadiusInt->setDisabled(false);
            ui->doubleSpinBox_Angle->setDisabled(true);
            ui->doubleSpinBox_Strech->setDisabled(true);
            ui->doubleSpinBox_Expansion->setDisabled(false);
            ui->dial_Speed->setDisabled(false);
            ui->dial_Radius->setDisabled(false);
            ui->dial_RadiusInt->setDisabled(false);
            ui->dial_Angle->setDisabled(true);
            ui->dial_Strech->setDisabled(true);
            ui->dial_Expansion->setDisabled(false);
            ui->doubleSpinBox_Speed->setValue(cloudVisLinked->getTrajectory()->getSpeed());
            Hypotrochoid *h_Traj=dynamic_cast<Hypotrochoid*>(cloudVisLinked->getTrajectory());
            ui->doubleSpinBox_Radius->setValue(h_Traj->getRadius());
            ui->doubleSpinBox_RadiusInt->setValue(h_Traj->getRadiusInt());
            //ui->doubleSpinBox_Angle->setValue(h_Traj->getAngle());
            ui->doubleSpinBox_Expansion->setValue(h_Traj->getExpansion());
            have_trajectory_hypotrochoid = true;
            break;
        }
        default :
            break;
        }

    cloudRef->changesDone(false);
    linking = false;
}

void CloudDialog::setDisableAllWidgets(bool disabled)
{
    ui->lineEdit_Name->setDisabled(disabled);
    ui->checkBox_Active->setDisabled(disabled);
    ui->dial_Duration->setDisabled(disabled);
    ui->dial_Grains->setDisabled(disabled);
    ui->dial_LFO_Amp->setDisabled(disabled);
    ui->dial_LFO_Freq->setDisabled(disabled);
    ui->dial_Overlap->setDisabled(disabled);
    ui->dial_Pitch->setDisabled(disabled);
    ui->dial_X->setDisabled(disabled);
    ui->dial_X_Extent->setDisabled(disabled);
    ui->dial_Y->setDisabled(disabled);
    ui->dial_Y_Extent->setDisabled(disabled);
    ui->doubleSpinBox_Duration->setDisabled(disabled);
    ui->doubleSpinBox_Grains->setDisabled(disabled);
    ui->doubleSpinBox_LFO_Amp->setDisabled(disabled);
    ui->doubleSpinBox_LFO_Freq->setDisabled(disabled);
    ui->doubleSpinBox_Midi_Note->setDisabled(disabled);
    ui->doubleSpinBox_Overlap->setDisabled(disabled);
    ui->doubleSpinBox_Pitch->setDisabled(disabled);
    ui->doubleSpinBox_Volume->setDisabled(disabled);
    ui->doubleSpinBox_X->setDisabled(disabled);
    ui->doubleSpinBox_X_Extent->setDisabled(disabled);
    ui->doubleSpinBox_Y->setDisabled(disabled);
    ui->doubleSpinBox_Y_Extent->setDisabled(disabled);
    ui->groupBox_Balance->setDisabled(disabled);
    ui->doubleSpinBox_Output_First->setDisabled(disabled);
    ui->doubleSpinBox_Output_Last->setDisabled(disabled);
    ui->groupBox_Direction->setDisabled(disabled);
    ui->groupBox_Window->setDisabled(disabled);
    ui->pushButton_Envelope->setDisabled(disabled);
    ui->verticalSlider_Volume->setDisabled(disabled);
}

void CloudDialog::on_dial_Overlap_valueChanged(int value)
{
    ui->doubleSpinBox_Overlap->setValue((double) value / 100);
}

void CloudDialog::on_doubleSpinBox_Overlap_valueChanged(double arg1)
{
    ui->dial_Overlap->setValue(arg1 * 100);
    if (!linking)
        cloudRef->setOverlap(arg1);
}

void CloudDialog::on_doubleSpinBox_Grains_valueChanged(double arg1)
{
    ui->dial_Grains->setValue((int) arg1);
    if (!linking)
        cloudRef->setNumGrains((int) arg1);
}

void CloudDialog::on_dial_Grains_valueChanged(int value)
{
    ui->doubleSpinBox_Grains->setValue(value);
}

void CloudDialog::on_doubleSpinBox_Y_valueChanged(double arg1)
{
    ui->dial_Y->setValue((int) arg1);
    if (!linking){
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::on_dial_Y_valueChanged(int value)
{
    ui->doubleSpinBox_Y->setValue(value);
    update_Y();
}

void CloudDialog::on_doubleSpinBox_Y_editingFinished()
{
    update_Y();
}

void CloudDialog::update_Y()
{
    if (!linking){
        cloudVisRef->setOriginY((int) passageValue);
        editing = false;
    }
}

void CloudDialog::on_doubleSpinBox_X_valueChanged(double arg1)
{
    ui->dial_X->setValue((int) arg1);
    if (!linking) {
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::on_dial_X_valueChanged(int value)
{
    ui->doubleSpinBox_X->setValue(value);
    update_X();
}

void CloudDialog::on_doubleSpinBox_X_editingFinished()
{
    update_X();
}

void CloudDialog::update_X()
{
    if (!linking){
        cloudVisRef->setOriginX((int) passageValue);
        editing = false;
    }
}

void CloudDialog::on_dial_X_Extent_valueChanged(int value)
{
    ui->doubleSpinBox_X_Extent->setValue(value);
    update_X_Extent();
}

void CloudDialog::on_doubleSpinBox_X_Extent_valueChanged(double arg1)
{
    ui->dial_X_Extent->setValue((int) arg1);
    if (!linking){
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::on_doubleSpinBox_X_Extent_editingFinished()
{
    update_X_Extent();
}

void CloudDialog::update_X_Extent()
{
    if (!linking){
        cloudVisRef->setFixedXRandExtent((int) passageValue);
        editing = false;
    }
}

void CloudDialog::on_dial_Y_Extent_valueChanged(int value)
{
    ui->doubleSpinBox_Y_Extent->setValue(value);
    update_Y_Extent();
}

void CloudDialog::on_doubleSpinBox_Y_Extent_valueChanged(double arg1)
{
    ui->dial_Y_Extent->setValue((int) arg1);
    if (!linking){
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::update_Y_Extent()
{
    if (!linking){
        cloudVisRef->setFixedYRandExtent((int) passageValue);
        editing = false;
    }
}

void CloudDialog::on_doubleSpinBox_Y_Extent_editingFinished()
{
    update_Y_Extent();
}

void CloudDialog::on_dial_LFO_Freq_valueChanged(int value)
{
    ui->doubleSpinBox_LFO_Freq->setValue((double) value / 100);
}

void CloudDialog::on_doubleSpinBox_LFO_Freq_valueChanged(double arg1)
{
    ui->dial_LFO_Freq->setValue(arg1 * 100);
    if (!linking)
        cloudRef->setPitchLFOFreq(arg1);
}

void CloudDialog::on_dial_LFO_Amp_valueChanged(int value)
{
    ui->doubleSpinBox_LFO_Amp->setValue((double) value / 1000);
}

void CloudDialog::on_doubleSpinBox_LFO_Amp_valueChanged(double arg1)
{
    ui->dial_LFO_Amp->setValue(arg1 * 1000);
    if (!linking)
        cloudRef->setPitchLFOAmount(arg1);
}

void CloudDialog::on_dial_Duration_valueChanged(int value)
{
    ui->doubleSpinBox_Duration->setValue((double) value);
}

void CloudDialog::on_doubleSpinBox_Duration_valueChanged(double arg1)
{
    ui->dial_Duration->setValue((int) arg1);
    if (!linking)
        cloudRef->setDurationMs(arg1);
}

void CloudDialog::on_dial_Pitch_valueChanged(int value)
{
    ui->doubleSpinBox_Pitch->setValue((double) value / 100);
}

void CloudDialog::on_doubleSpinBox_Pitch_valueChanged(double arg1)
{
    ui->dial_Pitch->setValue(arg1 * 100);
    if (!linking)
        //cloudRef->setPitch(pow(2, (float) (arg1 / 12)));
        cloudRef->setPitch(arg1);
}

void CloudDialog::on_verticalSlider_Volume_valueChanged(int value)
{
    ui->doubleSpinBox_Volume->setValue((double) value / 1000);
}

void CloudDialog::on_doubleSpinBox_Volume_valueChanged(double arg1)
{
    ui->verticalSlider_Volume->setValue(arg1 * 1000);
    if (!linking)
        cloudRef->setVolumeDb(arg1);
}

void CloudDialog::on_doubleSpinBox_Midi_Note_valueChanged(double arg1)
{
    if (!linking)
        cloudRef->setMidiNote((int) arg1);
}

void CloudDialog::on_doubleSpinBox_Midi_Channel_valueChanged(double arg1)
{
    if (!linking)
        cloudRef->setMidiChannel((int) arg1);
}

void CloudDialog::on_checkBox_Active_toggled(bool checked)
{
    if (!linking)
        cloudRef->setActiveState(checked);
}

void CloudDialog::on_checkBox_Locked_toggled(bool checked)
{
    cloudRef->setLockedState(checked);
    setDisableAllWidgets(checked);
}

void CloudDialog::on_radioButton_Window_Hanning_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setWindowType(HANNING);
}

void CloudDialog::on_radioButton_Window_Triangle_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setWindowType(TRIANGLE);
}

void CloudDialog::on_radioButton_Window_Expdec_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setWindowType(EXPDEC);
}

void CloudDialog::on_radioButton_Window_Rexpdec_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setWindowType(REXPDEC);
}

void CloudDialog::on_radioButton_Window_Sinc_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setWindowType(SINC);
}

void CloudDialog::on_radioButton_Window_Random_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setWindowType(RANDOM_WIN);
}

void CloudDialog::on_radioButton_Balance_Unity_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setSpatialMode(UNITY, -1);
}

void CloudDialog::on_radioButton_Balance_Stereo_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setSpatialMode(STEREO, -1);
}

void CloudDialog::on_radioButton_Balance_Around_toggled(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setSpatialMode(AROUND, -1);
}

void CloudDialog::on_radioButton_Direction_Forward_clicked(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setDirection(FORWARD);
}

void CloudDialog::on_radioButton_Direction_Backward_clicked(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setDirection(BACKWARD);
}

void CloudDialog::on_radioButton_Direction_Random_clicked(bool checked)
{
    if ((!linking) & (checked))
        cloudRef->setDirection(RANDOM_DIR);
}

void CloudDialog::on_pushButton_Envelope_clicked()
{
    ParamEnv localParamEnv;
    localParamEnv = cloudRef->getEnvelopeVolumeParam();
    cloudRef->getEnvelopeVolume().envDialogShow(localParamEnv);
    cloudRef->setEnvelopeVolumeParam(localParamEnv);
}

void CloudDialog::on_lineEdit_Name_textEdited(const QString &arg1)
{
    if (!linking)
        cloudRef->setName(arg1);
}

void CloudDialog::on_doubleSpinBox_Output_First_valueChanged(double arg1)
{
    if (!linking)
        if (ui->doubleSpinBox_Output_Last->value() >= arg1)
            cloudRef->setOutputFirst(arg1);
        else {
            ui->doubleSpinBox_Output_First->setValue(ui->doubleSpinBox_Output_Last->value());
            cloudRef->setOutputFirst(ui->doubleSpinBox_Output_Last->value());
        }
}

void CloudDialog::on_doubleSpinBox_Output_Last_valueChanged(double arg1)
{
    if (!linking)
        if (ui->doubleSpinBox_Output_First->value() <= arg1)
            cloudRef->setOutputLast(arg1);
        else {
            ui->doubleSpinBox_Output_Last->setValue(ui->doubleSpinBox_Output_First->value());
            cloudRef->setOutputLast(ui->doubleSpinBox_Output_First->value());
        }
}

void CloudDialog::on_dial_Speed_valueChanged(int value)
{
    ui->doubleSpinBox_Speed->setValue((double) value);
    update_Speed();
}

void CloudDialog::on_doubleSpinBox_Speed_valueChanged(double arg1)
{
    ui->dial_Speed->setValue((int) arg1);
    if (!linking) {
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::on_doubleSpinBox_Speed_editingFinished()
{
    update_Speed();
}

void CloudDialog::update_Speed()
{
    if (!linking){
        if (cloudVisRef->getTrajectory() != nullptr)
            cloudVisRef->getTrajectory()->setSpeed(passageValue);
        editing = false;
    }
}

void CloudDialog::on_dial_Radius_valueChanged(int value)
{
    ui->doubleSpinBox_Radius->setValue((double) value);
    update_Radius();
}

void CloudDialog::on_doubleSpinBox_Radius_valueChanged(double arg1)
{
    ui->dial_Radius->setValue((int) arg1);
    if (!linking) {
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::on_doubleSpinBox_Radius_editingFinished()
{
    update_Radius();
}

void CloudDialog::update_Radius()
{
    if (!linking) {
        switch (cloudRef->getTrajectoryType()) {
        case BOUNCING:{
            Circular *b_Traj = dynamic_cast<Circular*>(cloudVisRef->getTrajectory());
            b_Traj->setRadius(passageValue);
            break;
            }
        case CIRCULAR:{
            Circular *c_Traj=dynamic_cast<Circular*>(cloudVisRef->getTrajectory());
            c_Traj->setRadius(passageValue);
            break;
            }
        case HYPOTROCHOID:{
            Hypotrochoid *h_Traj=dynamic_cast<Hypotrochoid*>(cloudVisRef->getTrajectory());
            h_Traj->setRadius(passageValue);
            break;
            }
        default :
            break;
        }
        editing = false;
    }

}

void CloudDialog::on_dial_Angle_valueChanged(int value)
{
    ui->doubleSpinBox_Angle->setValue(value);
    update_Angle();
}

void CloudDialog::on_doubleSpinBox_Angle_valueChanged(double arg1)
{
    ui->dial_Angle->setValue((int) arg1);
    if (!linking) {
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::on_doubleSpinBox_Angle_editingFinished()
{
    update_Angle();
}

void CloudDialog::update_Angle()
{
    if (!linking){
        switch (cloudRef->getTrajectoryType()) {
        case BOUNCING:{
            Circular *b_Traj = dynamic_cast<Circular*>(cloudVisRef->getTrajectory());
            b_Traj->setAngle(passageValue);
            break;
            }
        case CIRCULAR:{
            Circular *c_Traj=dynamic_cast<Circular*>(cloudVisRef->getTrajectory());
            c_Traj->setAngle(passageValue);
            break;
            }
        case HYPOTROCHOID:{
            Hypotrochoid *h_Traj=dynamic_cast<Hypotrochoid*>(cloudVisRef->getTrajectory());
            h_Traj->setAngle(passageValue);
            break;
            }
        default :
            break;
        }
        editing = false;
    }
}

void CloudDialog::on_doubleSpinBox_Strech_editingFinished()
{
    update_Strech();
}

void CloudDialog::on_dial_Strech_valueChanged(int value)
{
    ui->doubleSpinBox_Strech->setValue(value);
    update_Strech();
}

void CloudDialog::on_doubleSpinBox_Strech_valueChanged(double arg1)
{
    ui->dial_Strech->setValue((int) arg1);
    if (!linking) {
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::update_Strech()
{
    if (!linking){
        Circular *c_Traj=dynamic_cast<Circular*>(cloudVisRef->getTrajectory());
        c_Traj->setStrech(passageValue);
        editing = false;
    }
}

void CloudDialog::on_radioButton_Trajectory_Bouncing_toggled(bool checked)
{
    Trajectory *tr=nullptr;
    if ((cloudVisRef->getTrajectory() != nullptr) & (have_trajectory_bouncing)) {
        tr=new Circular(ui->doubleSpinBox_Speed->value(),ui->doubleSpinBox_X->value(),ui->doubleSpinBox_Y->value(),ui->doubleSpinBox_Radius->value(),
                        ui->doubleSpinBox_Angle->value(),0);

    }
    else {
        tr=new Circular(g_defaultCloudParams.speed,ui->doubleSpinBox_X->value(),ui->doubleSpinBox_Y->value(),g_defaultCloudParams.radius,g_defaultCloudParams.angle,0);
    }
    cloudRef->setTrajectoryType(BOUNCING);
    cloudVisRef->setTrajectory(tr);
    cloudVisRef->startTrajectory();
    have_trajectory_bouncing = true;
}

void CloudDialog::on_radioButton_Trajectory_Circular_toggled(bool checked)
{
    Trajectory *tr=nullptr;
    if ((cloudVisRef->getTrajectory() != nullptr) & (have_trajectory_circular))
        tr=new Circular(ui->doubleSpinBox_Speed->value(),ui->doubleSpinBox_X->value(),ui->doubleSpinBox_Y->value(),
                        ui->doubleSpinBox_Radius->value(), ui->doubleSpinBox_Angle->value(),ui->doubleSpinBox_Strech->value());
    else
        tr=new Circular(g_defaultCloudParams.speed,ui->doubleSpinBox_X->value(),ui->doubleSpinBox_Y->value(),
                        g_defaultCloudParams.radius, g_defaultCloudParams.angle,g_defaultCloudParams.strech);
    cloudRef->setTrajectoryType(CIRCULAR);
    cloudVisRef->setTrajectory(tr);
    cloudVisRef->startTrajectory();
    have_trajectory_circular = true;
}

void CloudDialog::on_radioButton_Trajectory_Static_toggled(bool checked)
{
    Trajectory *tr = nullptr;
    cloudRef->setTrajectoryType(STATIC);
    cloudVisRef->setTrajectory(tr);
    cloudVisRef->updateCloudPosition(ui->doubleSpinBox_X->value(),ui->doubleSpinBox_Y->value());
}

void CloudDialog::on_doubleSpinBox_RadiusInt_valueChanged(double arg1)
{
    ui->dial_RadiusInt->setValue((int) arg1);
    if (!linking) {
        editing = true;
        passageValue = (double) arg1;
    }
}

void CloudDialog::on_dial_RadiusInt_valueChanged(int value)
{
    ui->doubleSpinBox_RadiusInt->setValue(value);
    update_RadiusInt();
}

void CloudDialog::on_doubleSpinBox_RadiusInt_editingFinished()
{
    update_RadiusInt();
}


void CloudDialog::update_RadiusInt()
{
    if (!linking){
        Hypotrochoid *h_Traj=dynamic_cast<Hypotrochoid*>(cloudVisRef->getTrajectory());
        h_Traj->setRadiusInt(passageValue);
        editing = false;
    }
}

void CloudDialog::on_dial_Expansion_valueChanged(int value)
{
    ui->doubleSpinBox_Expansion->setValue(value);
    update_Expansion();
}

void CloudDialog::on_doubleSpinBox_Expansion_valueChanged(double arg1)
{
    //ui->dial_Expansion->setValue((int) arg1);
    if (!linking) {
        editing = true;
        passageValue = (double) arg1;
    }
    ui->dial_Expansion->setValue((int) arg1);
}

void CloudDialog::on_doubleSpinBox_Expansion_editingFinished()
{
    update_Expansion();
}

void CloudDialog::update_Expansion()
{
    if (!linking){
        Hypotrochoid *h_Traj=dynamic_cast<Hypotrochoid*>(cloudVisRef->getTrajectory());
        h_Traj->setExpansion(passageValue);
        editing = false;
    }
}

void CloudDialog::on_radioButton_Trajectory_Hypotrochoid_toggled(bool checked)
{
    Trajectory *tr=nullptr;
    if ((cloudVisRef->getTrajectory() != nullptr) and (have_trajectory_hypotrochoid))
        tr=new Hypotrochoid(ui->doubleSpinBox_Speed->value(), ui->doubleSpinBox_X->value(),ui->doubleSpinBox_Y->value(),ui->doubleSpinBox_Radius->value(),
                            ui->doubleSpinBox_RadiusInt->value(), ui->doubleSpinBox_Expansion->value(), ui->doubleSpinBox_Angle->value());
    else {
        tr=new Hypotrochoid(g_defaultCloudParams.speed, ui->doubleSpinBox_X->value(),ui->doubleSpinBox_Y->value(),g_defaultCloudParams.radius,
                            g_defaultCloudParams.radiusInt, g_defaultCloudParams.expansion, g_defaultCloudParams.angle);
    }
    cloudRef->setTrajectoryType(HYPOTROCHOID);
    cloudVisRef->setTrajectory(tr);
    cloudVisRef->startTrajectory();
    have_trajectory_hypotrochoid = true;
}
