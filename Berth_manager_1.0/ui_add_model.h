/********************************************************************************
** Form generated from reading UI file 'add_model.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_MODEL_H
#define UI_ADD_MODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add_model
{
public:
    QPushButton *ok_pushButton;
    QPushButton *cancel_pushButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lineEdit_6;

    void setupUi(QDialog *Add_model)
    {
        if (Add_model->objectName().isEmpty())
            Add_model->setObjectName(QStringLiteral("Add_model"));
        Add_model->resize(327, 300);
        ok_pushButton = new QPushButton(Add_model);
        ok_pushButton->setObjectName(QStringLiteral("ok_pushButton"));
        ok_pushButton->setGeometry(QRect(170, 230, 75, 23));
        cancel_pushButton = new QPushButton(Add_model);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));
        cancel_pushButton->setGeometry(QRect(60, 230, 75, 23));
        widget = new QWidget(Add_model);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 40, 215, 164));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_3->addWidget(lineEdit_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        horizontalLayout_4->addWidget(lineEdit_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        lineEdit_5 = new QLineEdit(widget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        horizontalLayout_5->addWidget(lineEdit_5);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        lineEdit_6 = new QLineEdit(widget);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        horizontalLayout_6->addWidget(lineEdit_6);


        verticalLayout->addLayout(horizontalLayout_6);


        retranslateUi(Add_model);

        QMetaObject::connectSlotsByName(Add_model);
    } // setupUi

    void retranslateUi(QDialog *Add_model)
    {
        Add_model->setWindowTitle(QApplication::translate("Add_model", "\346\267\273\345\212\240\346\234\272\345\236\213\347\225\214\351\235\242", Q_NULLPTR));
        ok_pushButton->setText(QApplication::translate("Add_model", "\347\241\256\345\256\232", Q_NULLPTR));
        cancel_pushButton->setText(QApplication::translate("Add_model", "\345\217\226\346\266\210", Q_NULLPTR));
        label->setText(QApplication::translate("Add_model", "\346\234\272\345\236\213\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("Add_model", "\347\277\274\345\261\225\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("Add_model", "\345\274\225\346\223\216\345\206\205\351\227\264\350\267\235\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("Add_model", "\345\274\225\346\223\216\345\244\226\351\227\264\350\267\235\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("Add_model", "\346\234\272\350\272\253\351\225\277\345\272\246\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("Add_model", "\346\234\272\351\274\273\351\253\230\345\272\246\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Add_model: public Ui_Add_model {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_MODEL_H
