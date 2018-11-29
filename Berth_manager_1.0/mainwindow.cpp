#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<QMessageBox>
#include<QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    airplaneModel_Alertflag = false;  //�ؼ���ʼ��ʱ�������޸ĺ���
    Detection_Alertflag = false;      //ͬ��
    click_flag = true;                //��ʼ��������




   connect(ui->lineEdit_9, SIGNAL(returnPressed()), ui->connect_pushButton, SIGNAL(clicked()), Qt::UniqueConnection);


    QRegExpValidator *validator = new QRegExpValidator(QRegExp("^[0-9 | .]*$"), this);

    ui->lineEdit->setValidator(validator);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setValidator(validator);
    ui->lineEdit_4->setValidator(validator);
    ui->lineEdit_5->setValidator(validator);
    ui->lineEdit_6->setValidator(validator);
    ui->lineEdit_7->setValidator(validator);
    ui->lineEdit_8->setValidator(validator);
    ui->lineEdit_9->setValidator(validator);



    //���ÿؼ����еĿ��
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,150);

    ui->tableWidget->setRowCount(128);
    ui->tableWidget_2->setRowCount(128);


    for(int i=0; i<128; i++)
    {
        planeModel_Item[i].setTextAlignment(Qt::AlignCenter);
        wingLength_Item[i].setTextAlignment(Qt::AlignCenter);
        engineInner_Item[i].setTextAlignment(Qt::AlignCenter);
        engineOuter_Item[i].setTextAlignment(Qt::AlignCenter);
        planeLength_Item[i].setTextAlignment(Qt::AlignCenter);
        noseHeight_Item[i].setTextAlignment(Qt::AlignCenter);

        planeModel_Item[i].setFlags(Qt::NoItemFlags);

        ui->tableWidget->setItem(i,0,&planeModel_Item[i]);
        ui->tableWidget->setItem(i,1,&wingLength_Item[i]);
        ui->tableWidget->setItem(i,2,&engineInner_Item[i]);
        ui->tableWidget->setItem(i,3,&engineOuter_Item[i]);
        ui->tableWidget->setItem(i,4,&planeLength_Item[i]);
        ui->tableWidget->setItem(i,5,&noseHeight_Item[i]);
        ui->tableWidget->hideRow(i);

        /********************************************************************/

        planeModel_Item2[i].setTextAlignment(Qt::AlignCenter);
        stop1_x_Item[i].setTextAlignment(Qt::AlignCenter);
        stop1_y_Item[i].setTextAlignment(Qt::AlignCenter);
        stop2_x_Item[i].setTextAlignment(Qt::AlignCenter);
        stop2_y_Item[i].setTextAlignment(Qt::AlignCenter);
        center1_x_Item[i].setTextAlignment(Qt::AlignCenter);
        center1_y_Item[i].setTextAlignment(Qt::AlignCenter);
        center2_x_Item[i].setTextAlignment(Qt::AlignCenter);
        center2_y_Item[i].setTextAlignment(Qt::AlignCenter);

        planeModel_Item2[i].setFlags(Qt::NoItemFlags);

        ui->tableWidget_2->setItem(i,0,&planeModel_Item2[i]);
        ui->tableWidget_2->setItem(i,1,&stop1_x_Item[i]);
        ui->tableWidget_2->setItem(i,2,&stop1_y_Item[i]);
        ui->tableWidget_2->setItem(i,3,&stop2_x_Item[i]);
        ui->tableWidget_2->setItem(i,4,&stop2_y_Item[i]);
        ui->tableWidget_2->setItem(i,5,&center1_x_Item[i]);
        ui->tableWidget_2->setItem(i,6,&center1_y_Item[i]);
        ui->tableWidget_2->setItem(i,7,&center2_x_Item[i]);
        ui->tableWidget_2->setItem(i,8,&center2_y_Item[i]);
        ui->tableWidget_2->hideRow(i);

    }
//    tcpClient.connectToHost("192.168.1.101",6665);
    connect(&tcpClient,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(&addModel,SIGNAL(addPlane_signal(QString,float,float,float,float,float)),this,SLOT(addPlaneModel_slot(QString,float,float,float,float,float)));
    connect(&addDetetion_diag,SIGNAL(addDetectionPlane_signal(QString,QString,QString,QString,QString,QString,QString,QString,QString)),
            this,SLOT(addDetetion_slot(QString,QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(&addModel,SIGNAL(cancel_signal()),this,SLOT(recvStateModel_slot()));
    connect(&addDetetion_diag,SIGNAL(cancel_signal()),this,SLOT(recvDetetion_slot()));

    connect(this,SIGNAL(updateModel_signal(QStringList)),&addDetetion_diag,SLOT(updateModel_slot(QStringList)));

    connect(&click_timer,SIGNAL(timeout()),this,SLOT(click_timeSlot()));

    on_Select_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMsg(QByteArray array)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setByteOrder(QDataStream::BigEndian);

//  out<<quint32(0)<<sendByte;
    out<<array;
    out.device()->seek(0);
    out<<quint8(170);
    out<<quint8(170);
    out << (quint16)(block.size() - sizeof(quint32));
    tcpClient.write(block);

    qDebug()<<QString::fromLocal8Bit("Ҫ���͵�����Ϊ��")<<block;
}




//���ͻ�����������
void MainWindow::on_Select_pushButton_clicked()
{
    if(!click_flag)
    {
        QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���Ժ�����..."),NULL);
        return;
    }
    click_flag = false;
    click_timer.start(3000);


//    tcpClient.write(sendMsg);

    QByteArray sendArray = "{\"@table\":5,\"@src\":\"qt\"}";
    sendMsg(sendArray);
}

//��ӻ���
void MainWindow::on_add_pushButton_clicked()
{
    if(!click_flag)
    {
        QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���Ժ�����..."),NULL);
        return;
    }
    click_flag = false;
    click_timer.start(3000);


    airplaneModel_Alertflag = false;
    addModel.setModal(true);
    addModel.show();
}

//������ӻ�������
void MainWindow::addPlaneModel_slot(QString model, float wingLen, float eng_Inner, float eng_Outer, float plane_Len, float nose_Hei)
{
    qDebug()<<QString::fromLocal8Bit("��������յ�����")<< model<<"  "<<nose_Hei;

    //�жϻ����Ƿ��Ѿ�����
    int len  = AllPlaneModel_list.length();
    for(int i=0;  i<len; i++)
    {
        if(AllPlaneModel_list[i] == model)
        {
            QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("�����Ѿ����ڣ����ʧ�ܣ�"),NULL);
            return;
        }
    }

    // ��ǰ�˷������ָ��
    QJsonObject add_json;
    QJsonObject msg_json;
    msg_json.insert("CFTP",model);
    msg_json.insert("wing",QString::number(wingLen));
    msg_json.insert("engineInner",QString::number(eng_Inner));
    msg_json.insert("engineOuter",QString::number(eng_Outer));
    msg_json.insert("length",QString::number(plane_Len));
    msg_json.insert("noseheight",QString::number(nose_Hei));

    add_json.insert("@table",6);
    add_json.insert("@src","qt");
    add_json.insert("msg",msg_json);

    QJsonDocument document;
    document.setObject(add_json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);

    sendMsg(byteArray);
//    tcpClient.write(byteArray);



    //���½���(����һ��)
    ui->tableWidget->showRow(len);
    planeModel_Item[len].setText(model);
    wingLength_Item[len].setText(QString::number(wingLen));
    engineInner_Item[len].setText(QString::number(eng_Inner));
    engineOuter_Item[len].setText(QString::number(eng_Outer));
    planeLength_Item[len].setText(QString::number(plane_Len));
    noseHeight_Item[len].setText(QString::number(nose_Hei));

    AllPlaneModel_list.append(model);    //���ʹ洢������ҲҪ����һ��

    airplaneModel_Alertflag = true;
}

//�޸Ļ�����Ϣ
void MainWindow::on_alert_pushButton_clicked()
{
    if(!click_flag)
    {
        QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���Ժ�����..."),NULL);
        return;
    }
    click_flag = false;
    click_timer.start(3000);


    QJsonObject alert_json;
    QJsonArray msgArray_json;
    for(int i=0; i<airPlaneModel_alterlist.length(); i+=6)
    {
        QJsonObject single_json;
        single_json.insert("CFTP",airPlaneModel_alterlist[i]);
        single_json.insert("wing",airPlaneModel_alterlist[i+1]);
        single_json.insert("engineInner",airPlaneModel_alterlist[i+2]);
        single_json.insert("engineOuter",airPlaneModel_alterlist[i+3]);
        single_json.insert("length",airPlaneModel_alterlist[i+4]);
        single_json.insert("noseheight",airPlaneModel_alterlist[i+5]);
        msgArray_json.append(single_json);
    }

    alert_json.insert("@table",7);
    alert_json.insert("@src","qt");
    alert_json.insert("msg",msgArray_json);

    QJsonDocument document;
    document.setObject(alert_json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);

    sendMsg(byteArray);

    airPlaneModel_alterlist.clear();

}


//���ͻ��������޸�
void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    if(airplaneModel_Alertflag == false  || row<0)
        return;

      qDebug()<<"the row  = "<<row<<"  the coloum = "<<column;

      //У��
      QRegExp reg("^[0-9 | .]*$");
      QRegExpValidator validator(reg,0);
      int pos = 0;
      if(QValidator::Acceptable!=validator.validate(wingLength_Item[row].text(),pos) ||
              QValidator::Acceptable!=validator.validate(engineInner_Item[row].text(),pos)  ||
              QValidator::Acceptable!=validator.validate(engineOuter_Item[row].text(),pos)  ||
              QValidator::Acceptable!=validator.validate(planeLength_Item[row].text(),pos)  ||
              QValidator::Acceptable!=validator.validate(noseHeight_Item[row].text(),pos)
              )
         {
              QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���ͻ��������в����������֣�"),NULL);
              return;
         }




    if(airPlaneModel_alterlist.empty())
    {

        airPlaneModel_alterlist.append(planeModel_Item[row].text());
        airPlaneModel_alterlist.append(wingLength_Item[row].text());
        airPlaneModel_alterlist.append(engineInner_Item[row].text());
        airPlaneModel_alterlist.append(engineOuter_Item[row].text());
        airPlaneModel_alterlist.append(planeLength_Item[row].text());
        airPlaneModel_alterlist.append(noseHeight_Item[row].text());

        qDebug()<<"the list is empty";
//        on_alert_pushButton_clicked();


    }else
    {
        QString planeModel = planeModel_Item[row].text();

        for(int i=0; i<airPlaneModel_alterlist.length(); i+=6)
        {
            if(planeModel == airPlaneModel_alterlist[i])
            {
                //����Ѿ����� �������еĲ���
                airPlaneModel_alterlist[i+1] = wingLength_Item[row].text();
                airPlaneModel_alterlist[i+2] = engineInner_Item[row].text();
                airPlaneModel_alterlist[i+3] = engineOuter_Item[row].text();
                airPlaneModel_alterlist[i+4] = planeLength_Item[row].text();
                airPlaneModel_alterlist[i+5] = noseHeight_Item[row].text();

                qDebug()<<"the list is update "<<wingLength_Item[row].text()<<engineInner_Item[row].text()<<engineOuter_Item[row].text();
//                on_alert_pushButton_clicked();
                return;
            }
        }

        //��ӻ��͵Ļ�������
        airPlaneModel_alterlist.append(planeModel_Item[row].text());
        airPlaneModel_alterlist.append(wingLength_Item[row].text());
        airPlaneModel_alterlist.append(engineInner_Item[row].text());
        airPlaneModel_alterlist.append(engineOuter_Item[row].text());
        airPlaneModel_alterlist.append(planeLength_Item[row].text());
        airPlaneModel_alterlist.append(noseHeight_Item[row].text());

    }
}



/*********************************************
 * ���ݽ��ղ���
 * *****************************************/

//          packet.setByteOrder(QDataStream::BigEndian);


void MainWindow::readMessage()
{
        quint32   mesg_len=0;
        qint64 readbyte=tcpClient.bytesAvailable();
        if(readbyte<=0)
        {
            qDebug()<<QString::fromLocal8Bit("���յ������ݳ���Ϊ�� reqthread()��")<<endl;
            return;
        }
        QByteArray buffer;
        quint16 flag,len;
        buffer =tcpClient.readAll();
        m_buffer.append(buffer);
        int totallen = m_buffer.size();



        while(totallen)
        {
            qDebug()<<QString::fromLocal8Bit("m_buffer�ĳ���Ϊ")<<m_buffer.length()<<"  "<<QString::fromLocal8Bit("m_buffer������Ϊ��")<<m_buffer<<endl;

            if(totallen < 4)    //�����ĸ��ֽڣ�ͷ����
            {
                qDebug()<<QString::fromLocal8Bit("ͷ�������ĸ��ֽ�");
                break;
            }

            QDataStream packet(m_buffer);


            packet>>flag>>len;       //��ȡ���� len  ��Ϣͷ��ʱ����

            qDebug()<<QString::fromLocal8Bit("���ݲ��ֵĳ���")<<len  ;

            QByteArray json_Array;
            if(totallen<len)         //˵�����Ȳ���������
            {
                break;
            }else                    //�������ݲ��ֳ��ȴ��� ���ߵ��� ָ�����ȣ�˵�������������������
            {
                json_Array = m_buffer.mid(4,len);

                if(totallen-4>=len)
                {
                    m_buffer.clear();
                    totallen = 0 ;
                    qDebug()<<QString::fromLocal8Bit("���ݽ������û���ˣ�");
                }
                else
                {
                    qDebug()<<QString::fromLocal8Bit("���ݽ��ղ��㣡");
                    break;
                }
            }
            qDebug()<<QString::fromLocal8Bit("���ͷΪ��")<<flag<<"len = "<<len <<" all len ="<<json_Array;
            QJsonParseError jsonError;
            QJsonDocument doucment = QJsonDocument::fromJson(json_Array, &jsonError);                     // ת��Ϊ JSON �ĵ�
            if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
            {                                                                                            // ����δ��������
                if (doucment.isObject()) {
                    QJsonObject object = doucment.object();                                              // ת��Ϊ����
                    if (object.contains("@table"))
                    {                                                                                    // ����ָ���� key
                        QJsonValue val_flag = object.value("@table");                                    // ��ȡָ�� key ��Ӧ�� value
                        int flag = val_flag.toInt();
                        qDebug() << "@table " << flag;
                        if(5 == flag)              //���ͻ����������ر�
                        {
                          QJsonValue value_msg = object.value("msg");
                          if(value_msg.isArray())
                          {
                              QJsonArray msgArr = value_msg.toArray();
                                int size_ = msgArr.size();

                                AllPlaneModel_list.clear();

                              for(int i=0; i<msgArr.size(); i++)
                              {
                                  ui->tableWidget->showRow(i);

                                  QJsonObject airModelObject =  msgArr[i].toObject();
                                  if (airModelObject.contains("CFTP"))
                                  {                                                                   // ����ָ���� key
                                      QJsonValue val_cftp = airModelObject.value("CFTP");             // ��ȡָ�� key ��Ӧ�� value
                                      QString str_CFTP = val_cftp.toString();
                                      planeModel_Item[i].setText(str_CFTP);


                                      AllPlaneModel_list.append(str_CFTP);                            //�洢���еĻ���
                                  }
                                  if (airModelObject.contains("wing"))
                                  {                                                                                      // ����ָ���� key
                                      QJsonValue val_wing = airModelObject.value("wing");                                // ��ȡָ�� key ��Ӧ�� value
                                      double wing_ = val_wing.toDouble();
                                      wingLength_Item[i].setText(QString::number(wing_));
                                  }
                                  if (airModelObject.contains("engineInner"))
                                  {                                                                                      // ����ָ���� key
                                      QJsonValue val_engineInner = airModelObject.value("engineInner");                  // ��ȡָ�� key ��Ӧ�� value
                                      double engineInner_ = val_engineInner.toDouble();
                                      engineInner_Item[i].setText(QString::number(engineInner_));

                                  }
                                  if (airModelObject.contains("engineOuter"))
                                  {                                                                                      // ����ָ���� key
                                      QJsonValue val_engineOuter = airModelObject.value("engineOuter");                 // ��ȡָ�� key ��Ӧ�� value
                                      double engineOuter_ = val_engineOuter.toDouble();
                                      engineOuter_Item[i].setText(QString::number(engineOuter_));

                                  }
                                  if (airModelObject.contains("length"))
                                  {                                                                                      // ����ָ���� key
                                      QJsonValue val_cftp = airModelObject.value("length");                              // ��ȡָ�� key ��Ӧ�� value
                                      double length_ = val_cftp.toDouble();
                                      planeLength_Item[i].setText(QString::number(length_));

                                  }
                                  if (airModelObject.contains("noseheight"))
                                  {                                                                                      // ����ָ���� key
                                      QJsonValue val_cftp = airModelObject.value("noseheight");                         // ��ȡָ�� key ��Ӧ�� value
                                      double noseHeight_ = val_cftp.toDouble();
                                      noseHeight_Item[i].setText(QString::number(noseHeight_));

                                  }

                              }
                          }

                          airplaneModel_Alertflag = true;    //��ʾ��ɺ󣬿��Ա��޸���

                        }else if(8 == flag)
                        {
                            QJsonValue value_msg = object.value("msg");
                            if(value_msg.isArray())
                            {

                                QJsonArray msgArr = value_msg.toArray();
                                int size_ = msgArr.size();

                                AllDetectionModel_list.clear();

                                for(int i=0; i<msgArr.size(); i++)
                                {
                                    ui->tableWidget_2->showRow(i);

                                    QJsonObject airModelObject =  msgArr[i].toObject();
                                    if (airModelObject.contains("CFTP"))
                                    {                                                                   // ����ָ���� key
                                        QJsonValue val_cftp = airModelObject.value("CFTP");             // ��ȡָ�� key ��Ӧ�� value
                                        QString str_CFTP = val_cftp.toString();
                                        planeModel_Item2[i].setText(str_CFTP);
                                        AllDetectionModel_list.append(str_CFTP);
                                    }
                                    if (airModelObject.contains("stop1x"))
                                    {                                                                                      // ����ָ���� key
                                        QJsonValue val_stop1x = airModelObject.value("stop1x");                                // ��ȡָ�� key ��Ӧ�� value
                                        double stop1_x = val_stop1x.toDouble();
                                        stop1_x_Item[i].setText(QString::number(stop1_x));
                                    }
                                    if (airModelObject.contains("stop1y"))
                                    {                                                                                      // ����ָ���� key
                                        QJsonValue val_stop1y = airModelObject.value("stop1y");                  // ��ȡָ�� key ��Ӧ�� value
                                        double stop1_y = val_stop1y.toDouble();
                                        stop1_y_Item[i].setText(QString::number(stop1_y));

                                    }
                                    if (airModelObject.contains("stop2x"))
                                    {                                                                                      // ����ָ���� key
                                        QJsonValue val_stop2x = airModelObject.value("stop2x");                 // ��ȡָ�� key ��Ӧ�� value
                                        double stop2_x = val_stop2x.toDouble();
                                        stop2_x_Item[i].setText(QString::number(stop2_x));

                                    }
                                    if (airModelObject.contains("stop2y"))
                                    {                                                                                      // ����ָ���� key
                                        QJsonValue val_stop2y = airModelObject.value("stop2y");                              // ��ȡָ�� key ��Ӧ�� value
                                        double stop2_y = val_stop2y.toDouble();
                                        stop2_y_Item[i].setText(QString::number(stop2_y));

                                    }
                                    if (airModelObject.contains("middle1x"))
                                    {                                                                                      // ����ָ���� key
                                        QJsonValue val_middle1x = airModelObject.value("middle1x");                         // ��ȡָ�� key ��Ӧ�� value
                                        double middle1_x = val_middle1x.toDouble();
                                        center1_x_Item[i].setText(QString::number(middle1_x));
                                    }
                                    if (airModelObject.contains("middle1y"))
                                    {                                                                                      // ����ָ���� key
                                        QJsonValue val_middle1y = airModelObject.value("middle1y");                         // ��ȡָ�� key ��Ӧ�� value
                                        double middle1_y = val_middle1y.toDouble();
                                        center1_y_Item[i].setText(QString::number(middle1_y));
                                    }
                                    if (airModelObject.contains("middle2x"))
                                    {                                                                                      // ����ָ���� key
                                        QJsonValue val_middle2x = airModelObject.value("middle2x");                         // ��ȡָ�� key ��Ӧ�� value
                                        double middle2_x = val_middle2x.toDouble();
                                        center2_x_Item[i].setText(QString::number(middle2_x));
                                    }
                                    if (airModelObject.contains("middle2y"))
                                    {                                                                                      // ����ָ���� key
                                        QJsonValue val_middle2y = airModelObject.value("middle2y");                         // ��ȡָ�� key ��Ӧ�� value
                                        double middle2_y = val_middle2y.toDouble();
                                        center2_y_Item[i].setText(QString::number(middle2_y));
                                    }
                                }

                                Detection_Alertflag = true;
                            }
                        }else if(6 == flag)   //������ӳɹ�
                        {
                            QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("�����ɹ���"),NULL);
                        }else if(7 == flag)   //�����޸ĳɹ�
                        {
                            QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("�����ɹ���"),NULL);
                        }else if(9 == flag)   //���ͼ�������ӳɹ�
                        {
                            QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("�����ɹ���"),NULL);
                        }else if(10 == flag)   //���ͼ������޸ĳɹ�
                        {
                            QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("�����ɹ���"),NULL);
                        }else if(11 ==flag)    //�������˵ļ�����
                        {
                            QJsonValue val_clustermin = object.value("clustermin");                         // ��ȡָ�� key ��Ӧ�� value
                            double clustermin_ = val_clustermin.toDouble();
                            ui->lineEdit->setText(QString::number(clustermin_));

                            QJsonValue val_clustermax = object.value("clustermax");                         // ��ȡָ�� key ��Ӧ�� value
                            double clustermax_ = val_clustermax.toDouble();
                            ui->lineEdit_2->setText(QString::number(clustermax_));

                            QJsonValue val_tolerance = object.value("tolerance");                         // ��ȡָ�� key ��Ӧ�� value
                            double tolerance_ = val_tolerance.toDouble();
                            ui->lineEdit_3->setText(QString::number(tolerance_));

                            QJsonValue val_clipmin = object.value("clipmin");                         // ��ȡָ�� key ��Ӧ�� value
                            double clipmin_ = val_clipmin.toDouble();
                            ui->lineEdit_4->setText(QString::number(clipmin_));

                            QJsonValue val_clipmax = object.value("clipmax");
                            double clipmax_ = val_clipmax.toDouble();
                            ui->lineEdit_5->setText(QString::number(clipmax_));

                            QJsonValue val_clipleft = object.value("clipleft");
                            double clipleft_ = val_clipleft.toDouble();
                            ui->lineEdit_6->setText(QString::number(clipleft_));

                            QJsonValue val_clipright = object.value("clipright");
                            double clipright_ = val_clipright.toDouble();
                            ui->lineEdit_7->setText(QString::number(clipright_));

                            QJsonValue val_angular = object.value("angular");
                            double angular_ = val_angular.toDouble();
                            ui->lineEdit_7->setText(QString::number(angular_));



                        }
                    }

                }else     //����Json����
                {
                    qDebug()<<QString::fromLocal8Bit("����json����");

                    break;
                }
            }else        //documnt is not null
            {
                qDebug()<<QString::fromLocal8Bit("���ݽ���ʧ��");
                break;
            }

        }//while
}





void MainWindow::on_Select2_pushButton_clicked()
{
    if(!click_flag)
    {
        QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���Ժ�����..."),NULL);
        return;
    }
    click_flag = false;
    click_timer.start(3000);


    QByteArray byteArray = "{\"@table\":8,\"@src\":\"qt\"}" ;
    sendMsg(byteArray);
//  tcpClient.write();
}

void MainWindow::on_add2_pushButton_clicked()
{
    if(!click_flag)
    {
        QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���Ժ�����..."),NULL);
        return;
    }
    click_flag = false;
    click_timer.start(3000);


    Detection_Alertflag = false;
     addDetetion_diag.show();
}


//��Ӽ���ͺ������
void MainWindow::addDetetion_slot(QString planeMod,QString stop1x_,QString stop1y_,QString stop2x_,QString stop2y_,QString mid1x_,QString mid1y_,QString mid2x_,QString mid2y_)
{

    //�ж��Ƿ����ظ�
    for(int i=0; i<AllDetectionModel_list.length(); i++)
    {
        if(planeMod == AllDetectionModel_list[i])
        {
            QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("�û����Ѵ��ڣ����ʧ��!"));
            return ;
        }
    }

    //��ǰ�˷��������Ϣ
    QJsonObject addDetection_json;
    QJsonObject single_json;
    single_json.insert("CFTP",planeMod);
    single_json.insert("stop1x",stop1x_);
    single_json.insert("stop1y",stop1y_);
    single_json.insert("stop2x",stop2x_);
    single_json.insert("stop2y",stop2y_);
    single_json.insert("middle1x",mid1x_);
    single_json.insert("middle1y",mid1y_);
    single_json.insert("middle2x",mid2x_);
    single_json.insert("middle2y",mid2y_);

    addDetection_json.insert("@table",9);
    addDetection_json.insert("@src","qt");
    addDetection_json.insert("msg",single_json);

    QJsonDocument document;
    document.setObject(addDetection_json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    sendMsg(byteArray);


//    tcpClient.write(byteArray);
//    qDebug()<<QString::fromLocal8Bit("���͸�ǰ�˵����Ӽ����Ϣ������Ϊ:")<<byteArray;


    //ˢ�½�����ʾ
    int len  = AllDetectionModel_list.length();
    planeModel_Item2[len].setText(planeMod);
    stop1_x_Item[len].setText(stop1x_);
    stop1_y_Item[len].setText(stop1y_);
    stop2_x_Item[len].setText(stop2x_);
    stop2_y_Item[len].setText(stop2y_);
    center1_x_Item[len].setText(mid1x_);
    center1_y_Item[len].setText(mid1y_);
    center2_x_Item[len].setText(mid2x_);
    center2_y_Item[len].setText(mid2y_);
    ui->tableWidget_2->showRow(len);

    AllDetectionModel_list.append(planeMod);

    Detection_Alertflag = true;
}

void MainWindow::on_alert2_pushButton_clicked()
{
    if(!click_flag)
    {
        QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���Ժ�����..."),NULL);
        return;
    }
    click_flag = false;
    click_timer.start(3000);



    QJsonObject alert_json;
    QJsonArray msgArray;

    for(int i=0; i<Detection_alterlist.length(); i += 9)
    {
        QJsonObject single_json;
        single_json.insert("CFTP",Detection_alterlist[i]);
        single_json.insert("stop1x",Detection_alterlist[i+1]);
        single_json.insert("stop1y",Detection_alterlist[i+2]);
        single_json.insert("stop2x",Detection_alterlist[i+3]);
        single_json.insert("stop2y",Detection_alterlist[i+4]);
        single_json.insert("middle1x",Detection_alterlist[i+5]);
        single_json.insert("middle1y",Detection_alterlist[i+6]);
        single_json.insert("middle2x",Detection_alterlist[i+7]);
        single_json.insert("middle2y",Detection_alterlist[i+8]);

        msgArray.append(single_json);
    }
    alert_json.insert("@table",10);
    alert_json.insert("@src","qt");
    alert_json.insert("msg",msgArray);


    QJsonDocument document;
    document.setObject(alert_json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    sendMsg(byteArray);

//    tcpClient.write(byteArray);
//    qDebug()<<QString::fromLocal8Bit("���͸�ǰ�˵��޸ļ����Ϣ������Ϊ:")<<byteArray;



    Detection_alterlist.clear();
}

void MainWindow::on_tableWidget_2_cellChanged(int row, int column)
{
    if(row<0 || Detection_Alertflag == false)
    {
        return ;
    }

    qDebug()<<"the row  = "<<row<<"  the coloum = "<<column;

    QRegExp reg("^[0-9 | .]*$");
    QRegExpValidator validator(reg,0);
    int pos = 0;

    if(QValidator::Acceptable!=validator.validate(stop1_x_Item[row].text(),pos) ||
            QValidator::Acceptable!=validator.validate(stop1_y_Item[row].text(),pos)  ||
            QValidator::Acceptable!=validator.validate(stop2_x_Item[row].text(),pos)  ||
            QValidator::Acceptable!=validator.validate(stop2_y_Item[row].text(),pos)  ||
            QValidator::Acceptable!=validator.validate(center1_x_Item[row].text(),pos)   ||
            QValidator::Acceptable!=validator.validate(center1_y_Item[row].text(),pos)   ||
            QValidator::Acceptable!=validator.validate(center2_x_Item[row].text(),pos)   ||
            QValidator::Acceptable!=validator.validate(center2_y_Item[row].text(),pos)

            )
       {
            QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���ͼ������в����������֣�"),NULL);
            return;
       }



    if(Detection_alterlist.empty())
    {

        Detection_alterlist.append(planeModel_Item2[row].text());
        Detection_alterlist.append(stop1_x_Item[row].text());
        Detection_alterlist.append(stop1_y_Item[row].text());
        Detection_alterlist.append(stop2_x_Item[row].text());
        Detection_alterlist.append(stop2_y_Item[row].text());
        Detection_alterlist.append(center1_x_Item[row].text());
        Detection_alterlist.append(center1_y_Item[row].text());
        Detection_alterlist.append(center2_x_Item[row].text());
        Detection_alterlist.append(center2_y_Item[row].text());

        qDebug()<<"the list is empty";
    }else
    {
        QString planeModel = planeModel_Item2[row].text();

        for(int i=0; i<Detection_alterlist.length(); i+=6)
        {
            if(planeModel == Detection_alterlist[i])
            {
                //����Ѿ����� �������еĲ���
                Detection_alterlist[i+1] = stop1_x_Item[row].text();
                Detection_alterlist[i+2] = stop1_y_Item[row].text();
                Detection_alterlist[i+3] = stop2_x_Item[row].text();
                Detection_alterlist[i+4] = stop2_y_Item[row].text();
                Detection_alterlist[i+5] = center1_x_Item[row].text();
                Detection_alterlist[i+6] = center1_y_Item[row].text();
                Detection_alterlist[i+7] = center2_x_Item[row].text();
                Detection_alterlist[i+8] = center2_y_Item[row].text();

                qDebug()<<"the list is update "<<stop1_x_Item[row].text()<<stop1_y_Item[row].text()<<center2_y_Item[row].text();
                return;
            }
        }
        //��ӻ��͵Ļ�������
        Detection_alterlist.append(planeModel_Item2[row].text());
        Detection_alterlist.append(stop1_x_Item[row].text());
        Detection_alterlist.append(stop1_y_Item[row].text());
        Detection_alterlist.append(stop2_x_Item[row].text());
        Detection_alterlist.append(stop2_y_Item[row].text());
        Detection_alterlist.append(center1_x_Item[row].text());
        Detection_alterlist.append(center1_y_Item[row].text());
        Detection_alterlist.append(center2_x_Item[row].text());
        Detection_alterlist.append(center2_y_Item[row].text());
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
//   qDebug()<<QString::fromLocal8Bit("��ǰ��ҳ��Ϊ->")<<index;
    if(0 == index)       //��ѯ����
    {
        QByteArray sendArray = "{\"@table\":5,\"@src\":\"qt\"}";
        sendMsg(sendArray);

    }else if(1 == index)  //��ѯ������
    {
        emit updateModel_signal(AllPlaneModel_list);
        QByteArray sendArray = "{\"@table\":8,\"@src\":\"qt\"}";
        sendMsg(sendArray);

    }else if(2 == index)  //��ѯ���˼�����
    {
        QByteArray snedArray = "{\"@table\":11,\"@src\":\"qt\"}";
        sendMsg(snedArray);

        qDebug()<<QString::fromLocal8Bit("��ѯ���˼������Ѿ�������");
    }
}

void MainWindow::recvStateModel_slot()
{
    airplaneModel_Alertflag = true;
}

void MainWindow::recvDetetion_slot()
{
    Detection_Alertflag = true;
}




//�޸����˵ļ�����
void MainWindow::on_Person_pushButton_clicked()
{
    if(!click_flag)
    {
        QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("���Ժ�����..."),NULL);
        return;
    }
    click_flag = false;
    click_timer.start(3000);


    QJsonObject alert_json;

    QString clu_min_ = ui->lineEdit->text();
    QString clu_max_ = ui->lineEdit_2->text();
    QString toleran_ = ui->lineEdit_3->text();
    QString clipmin_ = ui->lineEdit_4->text();
    QString clipmax_ = ui->lineEdit_5->text();
    QString clipleft_ = ui->lineEdit_6->text();
    QString clipright_ = ui->lineEdit_7->text();
    QString angular_ = ui->lineEdit_10->text();


    if(clu_min_.isEmpty() || clu_max_.isEmpty() || toleran_.isEmpty() || clipmin_.isEmpty() || clipmax_.isEmpty() || clipleft_.isEmpty() || clipright_.isEmpty()|| angular_.isEmpty())
    {
        QMessageBox::information(NULL,NULL,QString::fromLocal8Bit("�������ֵ������������"),NULL);
        return ;
    }

    alert_json.insert("@table",12);
    alert_json.insert("@src","qt");
    alert_json.insert("clustermin",clu_min_);
    alert_json.insert("clustermax",clu_max_);
    alert_json.insert("tolerance",toleran_);
    alert_json.insert("clipmin",clipmin_);
    alert_json.insert("clipmmax",clipmax_);
    alert_json.insert("clipleft",clipleft_);
    alert_json.insert("clipright",clipright_);
    alert_json.insert("angular",angular_);

    QJsonDocument document;
    document.setObject(alert_json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);


    sendMsg(byteArray);

//    tcpClient.write(byteArray);
//    qDebug()<<QString::fromLocal8Bit("���͸�ǰ�˵��޸����˼����Ϣ������Ϊ:")<<byteArray;
}


void MainWindow::click_timeSlot()
{
    click_flag = true;
}



//����������Ӳۺ���
void MainWindow::on_connect_pushButton_clicked()
{
    if((ui->lineEdit_8->text().isEmpty()) || (ui->lineEdit_9->text().isEmpty()))
    {
        QMessageBox::information(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���벻��Ϊ��!"));
        return ;
    }


    QString ipAddress = ui->lineEdit_8->text();
    int port = ui->lineEdit_9->text().toInt();


    tcpClient.abort();


    tcpClient.connectToHost(ipAddress,port);

    if(tcpClient.waitForConnected(1000))
    {
        QMessageBox::information(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("���ӳɹ�^_^ !!"));
    }
    else
    {
        QMessageBox::information(NULL,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("����ʧ��v_v !!"));
    }

}
