#ifndef CLOUDDIALOG_H
#define CLOUDDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include "model/Cloud.h"
#include "visual/CloudVis.h"

namespace Ui {
class CloudDialog;
}

class CloudDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloudDialog(QWidget *parent = 0);
    ~CloudDialog();
    void linkCloud (Cloud *cloudLinked, CloudVis *cloudVisLinked);
    void setDisableAllWidgets(bool disable);

private slots:
    void autoUpdate();

    void on_dial_Overlap_valueChanged(int value);

    void on_doubleSpinBox_Overlap_valueChanged(double arg1);

    void on_dial_Grains_valueChanged(int value);

    void on_doubleSpinBox_Grains_valueChanged(double arg1);

    void on_doubleSpinBox_Y_valueChanged(double arg1);

    void on_dial_Y_valueChanged(int value);

    void on_doubleSpinBox_X_valueChanged(double arg1);

    void on_dial_X_valueChanged(int value);

    void on_dial_X_Extent_valueChanged(int value);

    void on_doubleSpinBox_X_Extent_valueChanged(double arg1);

    void on_dial_Y_Extent_valueChanged(int value);

    void on_doubleSpinBox_Y_Extent_valueChanged(double arg1);

    void on_dial_LFO_Freq_valueChanged(int value);

    void on_doubleSpinBox_LFO_Freq_valueChanged(double arg1);

    void on_dial_LFO_Amp_valueChanged(int value);

    void on_doubleSpinBox_LFO_Amp_valueChanged(double arg1);

    void on_dial_Duration_valueChanged(int value);

    void on_doubleSpinBox_Duration_valueChanged(double arg1);

    void on_dial_Pitch_valueChanged(int value);

    void on_doubleSpinBox_Pitch_valueChanged(double arg1);

    void on_verticalSlider_Volume_valueChanged(int value);

    void on_doubleSpinBox_Volume_valueChanged(double arg1);

    void on_doubleSpinBox_Midi_Note_valueChanged(double arg1);

    void on_doubleSpinBox_Midi_Channel_valueChanged(double arg1);

    void on_checkBox_Active_toggled(bool checked);

    void on_radioButton_Window_Hanning_toggled(bool checked);

    void on_radioButton_Window_Triangle_toggled(bool checked);

    void on_radioButton_Window_Expdec_toggled(bool checked);

    void on_radioButton_Window_Rexpdec_toggled(bool checked);

    void on_radioButton_Window_Sinc_toggled(bool checked);

    void on_radioButton_Window_Random_toggled(bool checked);

    void on_radioButton_Balance_Unity_toggled(bool checked);

    void on_radioButton_Balance_Stereo_toggled(bool checked);

    void on_radioButton_Balance_Around_toggled(bool checked);

    void on_radioButton_Direction_Forward_clicked(bool checked);

    void on_radioButton_Direction_Backward_clicked(bool checked);

    void on_radioButton_Direction_Random_clicked(bool checked);

    void on_checkBox_Locked_toggled(bool checked);

    void on_pushButton_Envelope_clicked();

    void on_lineEdit_Name_textEdited(const QString &arg1);

private:
    Ui::CloudDialog *ui;
    bool linking = false;
    Cloud *cloudRef;
    CloudVis *cloudVisRef;
};

#endif // CLOUDDIALOG_H
