#ifndef ADD_MODEL_H
#define ADD_MODEL_H

#include <QDialog>

namespace Ui {
class Add_model;
}

class Add_model : public QDialog
{
    Q_OBJECT

public:
    explicit Add_model(QWidget *parent = 0);
    ~Add_model();

private slots:
    void on_ok_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::Add_model *ui;

signals:
    void addPlane_signal(QString,float,float,float,float,float);
    void cancel_signal();
};

#endif // ADD_MODEL_H
