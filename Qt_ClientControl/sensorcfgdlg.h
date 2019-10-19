#ifndef SENSORCFGDLG_H
#define SENSORCFGDLG_H

#include <QDialog>

namespace Ui {
class SensorCfgDlg;
}

class SensorCfgDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SensorCfgDlg(QWidget *parent = nullptr);
    ~SensorCfgDlg();
    void init();
    char component_name[80];
    unsigned short property_id;
    void DisplayControls();

public slots:
    void onBtnConfigPub();
    void onBtnConfigCadence();
    void on_displayControls(int i);

private:
    Ui::SensorCfgDlg *ui;
};

#endif // SENSORCFGDLG_H
