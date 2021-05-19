#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QStringList>
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QComboBox>
#include <QDragEnterEvent>
#include <QMimeData>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

#define AVRDUDE         0 //avrdude烧录
#define ESPTOOL_ESP32   1 //ESP32烧录
#define ESPTOOL_ESP8266 2 //ESP8266烧录
#define AVRDUDE_M0      3 //M0烧录
#define AVRDUDE_M3      4 //M3烧录


#define UNO          0
#define MEAG2560     1
#define LEONARDO     2
#define BEETLE       3
#define NANO         4
#define ESP32        5
#define ESP8266      6
#define M0           7
#define TINKERNODE   8
#define CURIENANO  9
#define BLUNOM3      10

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


public slots:
    /**
     * @brief showValidPort 动态检测串口的槽函数
     */
    void showValidPort();
    /**
     * @brief importFromFile 选择flash文件按钮执行获取烧录文件路径的槽函数
     */
    void importFromFile();
    /**
     * @brief exitProgram 退出按钮执行的槽函数
     */
    void exitProgram();
    /**
     * @brief upload 烧录按钮点击执行的槽函数
     */
    void upload();
    /**
     * @brief printReturnData 在文本框中打印进程执行返回数据的槽函数
     */
    void printReturnData();
    /**
     * @brief motherboardsChange 当主板发生改变时修改相应数据的槽函数
     */
    void motherboardsChange();
    /**
     * @brief espimportFromFile 选择Partition按键执行的槽函数
     */
    void espimportFromFile();


private:
    Ui::Widget *ui;
    QSerialPort *serialPort;
    QTimer *timer;
    QStringList portStringList;
    QString currentCOM = "";
    QProcess *myProcess;
    qint8 burnerTools  = AVRDUDE;
    QString model    = "atmega328p";
    QString agreement  = "arduino";
    QString baud       = "115200";
    QString bootloader = "bootloader_dio_80m.bin";
    QString frequency  = "80m";
    QStringList  port;
    /**
     * @brief killProcess 终止执行的进程
     * @param processName 需要终止进程的名称
     */
    void killProcess(const QString &processName);//终止进程
    /**
     * @brief sleep 延时函数
     * @param msec  延时多少毫秒
     */
    void sleep(int msec);
    /**
     * @brief resetSerial 重置串口
     */
    void  resetSerial(void);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

};

#endif // WIDGET_H
