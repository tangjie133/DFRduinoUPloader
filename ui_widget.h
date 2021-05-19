/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *imglabel;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *flashPath;
    QPushButton *pathButton_1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *partitionPath;
    QPushButton *pathButton_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *portComboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QComboBox *boardComboBox;
    QTextEdit *informationEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *uploadButton;
    QPushButton *exitButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(484, 450);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        imglabel = new QLabel(Widget);
        imglabel->setObjectName(QStringLiteral("imglabel"));

        horizontalLayout_6->addWidget(imglabel);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        flashPath = new QLineEdit(Widget);
        flashPath->setObjectName(QStringLiteral("flashPath"));
        flashPath->setDragEnabled(false);

        horizontalLayout_2->addWidget(flashPath);

        pathButton_1 = new QPushButton(Widget);
        pathButton_1->setObjectName(QStringLiteral("pathButton_1"));
        QFont font1;
        font1.setPointSize(11);
        pathButton_1->setFont(font1);
        pathButton_1->setCheckable(false);
        pathButton_1->setAutoRepeatDelay(300);

        horizontalLayout_2->addWidget(pathButton_1);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        partitionPath = new QLineEdit(Widget);
        partitionPath->setObjectName(QStringLiteral("partitionPath"));

        horizontalLayout_3->addWidget(partitionPath);

        pathButton_2 = new QPushButton(Widget);
        pathButton_2->setObjectName(QStringLiteral("pathButton_2"));
        pathButton_2->setFont(font1);

        horizontalLayout_3->addWidget(pathButton_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setWeight(50);
        label_5->setFont(font2);

        horizontalLayout_4->addWidget(label_5);

        portComboBox = new QComboBox(Widget);
        portComboBox->setObjectName(QStringLiteral("portComboBox"));

        horizontalLayout_4->addWidget(portComboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font2);

        horizontalLayout_5->addWidget(label_4);

        boardComboBox = new QComboBox(Widget);
        boardComboBox->setObjectName(QStringLiteral("boardComboBox"));

        horizontalLayout_5->addWidget(boardComboBox);


        verticalLayout->addLayout(horizontalLayout_5);

        informationEdit = new QTextEdit(Widget);
        informationEdit->setObjectName(QStringLiteral("informationEdit"));
        informationEdit->setReadOnly(true);

        verticalLayout->addWidget(informationEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        uploadButton = new QPushButton(Widget);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        uploadButton->setFont(font3);

        horizontalLayout->addWidget(uploadButton);

        exitButton = new QPushButton(Widget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setFont(font3);

        horizontalLayout->addWidget(exitButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        imglabel->setText(QString());
        label->setText(QApplication::translate("Widget", "\346\254\242\350\277\216\344\275\277\347\224\250\347\203\247\345\275\225\345\267\245\345\205\267\357\274\201\357\274\201\357\274\201\357\274\201\357\274\201\357\274\201\357\274\201", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "Flash:", Q_NULLPTR));
        pathButton_1->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "Partition:", Q_NULLPTR));
        pathButton_2->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "\344\270\262\345\217\243\351\200\211\346\213\251\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "\344\270\273\346\216\247\351\200\211\346\213\251\357\274\232", Q_NULLPTR));
        boardComboBox->clear();
        boardComboBox->insertItems(0, QStringList()
         << QApplication::translate("Widget", "DFRduino UNO/Arduino Uno", Q_NULLPTR)
         << QApplication::translate("Widget", "DFRduino Mega2560/Arduino Mega2560", Q_NULLPTR)
         << QApplication::translate("Widget", "DFRobot Leonardo/Arduino Leonardo", Q_NULLPTR)
         << QApplication::translate("Widget", "DFRobot  Beetle Leonardo", Q_NULLPTR)
         << QApplication::translate("Widget", "DFRduino Nano", Q_NULLPTR)
         << QApplication::translate("Widget", "FireBeetle-ESP32", Q_NULLPTR)
         << QApplication::translate("Widget", "FireBeetle-ESP8266", Q_NULLPTR)
         << QApplication::translate("Widget", "Firebeetle M0", Q_NULLPTR)
         << QApplication::translate("Widget", "TinkerNode", Q_NULLPTR)
         << QApplication::translate("Widget", "CurieNano ", Q_NULLPTR)
         << QApplication::translate("Widget", "Bluno M3", Q_NULLPTR)
        );
        uploadButton->setText(QApplication::translate("Widget", "\347\203\247\345\275\225", Q_NULLPTR));
        exitButton->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
