#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"add_model.h"
#include"add_detetion.h"
#include <QTableWidgetItem>
#include <QTcpSocket>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_Select_pushButton_clicked();

    void on_add_pushButton_clicked();

    void on_alert_pushButton_clicked();

    void readMessage();

    void addPlaneModel_slot(QString,float,float,float,float,float);

    void addDetetion_slot(QString,QString,QString,QString,QString,QString,QString,QString,QString);

    void on_tableWidget_cellChanged(int row, int column);

    void on_Select2_pushButton_clicked();

    void on_add2_pushButton_clicked();

    void on_alert2_pushButton_clicked();

    void on_tableWidget_2_cellChanged(int row, int column);

    void on_tabWidget_currentChanged(int index);

    void recvStateModel_slot();

    void recvDetetion_slot();

    void on_Person_pushButton_clicked();

    void click_timeSlot();

    void sendMsg(QByteArray array);

    void on_connect_pushButton_clicked();

private:

    Ui::MainWindow *ui;
    Add_model addModel;    
    add_detetion addDetetion_diag;

private:
    QTableWidgetItem planeModel_Item[128];
    QTableWidgetItem wingLength_Item[128];
    QTableWidgetItem engineInner_Item[128];
    QTableWidgetItem engineOuter_Item[128];
    QTableWidgetItem planeLength_Item[128];
    QTableWidgetItem noseHeight_Item[128];

    QTableWidgetItem planeModel_Item2[128];
    QTableWidgetItem stop1_x_Item[128];
    QTableWidgetItem stop1_y_Item[128];
    QTableWidgetItem stop2_x_Item[128];
    QTableWidgetItem stop2_y_Item[128];
    QTableWidgetItem center1_x_Item[128];
    QTableWidgetItem center1_y_Item[128];
    QTableWidgetItem center2_x_Item[128];
    QTableWidgetItem center2_y_Item[128];

    QTcpSocket tcpClient;
    bool airplaneModel_Alertflag;
    bool Detection_Alertflag;
    QTimer click_timer;              //三秒钟内不允许重复点击
    bool click_flag;

    QStringList airPlaneModel_alterlist;               //要修改的 机型基本参数的列表
    QStringList Detection_alterlist;                   //要修改的检测参数的修改列表
    QStringList AllPlaneModel_list;                    //存储所有的机型
    QStringList AllDetectionModel_list;                //存储泊位检测的机型

    QByteArray m_buffer;

signals:
    void updateModel_signal(QStringList);


};

#endif // MAINWINDOW_H
