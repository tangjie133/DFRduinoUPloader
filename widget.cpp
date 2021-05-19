#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString filename(QCoreApplication::applicationDirPath()+ "/DFRobotlogo.jpeg");
    qDebug()<<filename;
    QImage* img=new QImage;
        if(! ( img->load(filename) ) ) //加载图像
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }
    ui->imglabel->setPixmap(QPixmap::fromImage(*img));
    myProcess = new QProcess(this);
    ui->portComboBox->clear();
    timer = new QTimer;//定时扫描
    timer->start(100);//每100ms定时检测串口
    serialPort = new QSerialPort;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        portStringList += (info.portName() + " " +info.description());
        qDebug()<<info.description();
    }
    ui->portComboBox->addItems(portStringList);
    ui->pathButton_2->setEnabled(false);
    ui->partitionPath->setEnabled(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(showValidPort()));
    connect(ui->pathButton_1,SIGNAL(clicked()),this,SLOT(importFromFile()));
    connect(ui->pathButton_2,SIGNAL(clicked()),this,SLOT(espimportFromFile()));
    connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(exitProgram()));
    connect(ui->uploadButton,SIGNAL(clicked()),this,SLOT(upload()));
    connect(myProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(printReturnData()));
    connect(ui->boardComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(motherboardsChange()));
    setWindowTitle(tr("DFRduinoUploader V0.6"));
    this->setAcceptDrops(true);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::showValidPort()
{
    QStringList newPortStringList;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        newPortStringList += (info.portName() + " " +info.description());
    }
    if(newPortStringList.size() != portStringList.size()){
        portStringList = newPortStringList;
        ui->portComboBox->clear();
        ui->portComboBox->addItems(portStringList);
    }

}

void Widget::importFromFile(){
    QString path;
    QString fileName = QCoreApplication::applicationDirPath();//获取应用程序路径
    if(burnerTools == AVRDUDE||burnerTools == AVRDUDE_M0||burnerTools == ESPTOOL_ESP32||burnerTools == ESPTOOL_ESP8266||burnerTools ==AVRDUDE_M3){
        path = QFileDialog::getOpenFileName(this,tr("Import a hex file"),
                                                     fileName+"/test",
                                                     "*.hex;;ALL files(*)");
    }else if(burnerTools == ESPTOOL_ESP32|| burnerTools == ESPTOOL_ESP8266){
        path = QFileDialog::getOpenFileName(this,tr("Import a hex file"),
                                                     fileName+"/test",
                                                     "*.bin;;ALL files(*)");
    }

    ui->flashPath->setText(path);

}

void Widget::espimportFromFile(){
    QString fileName = QCoreApplication::applicationDirPath();//获取应用程序路径
    QString path = QFileDialog::getOpenFileName(this,tr("Import a hex file"),
                                                 fileName+"/test",
                                                 "*.bin;;ALL files(*)");
     ui->partitionPath->setText(path);
}

void Widget::exitProgram(){
   qApp->exit(0);
}

void Widget::upload(){
    myProcess->setProcessChannelMode(QProcess::MergedChannels);
    QString fileName = QCoreApplication::applicationDirPath();//获取应用程序路径
    port = (ui->portComboBox->currentText()).split(" ");//字符串截取，按特定方式截取
    QStringList aqstrList;
    if(burnerTools == AVRDUDE){ //AVR系列板卡烧录方式
        killProcess("avrdude.exe");
        aqstrList<<"-C"<<fileName+"/avrtool/avrdude.conf"<<"-v"<< "-p"+model<<"-c"+agreement<<
                   "-P"+port[0]<<"-b"+baud<<"-D"<<"-Uflash:w:"+ui->flashPath->text()+":i";
        qDebug()<<aqstrList;
        myProcess->start(fileName+"/avrtool/avrdude.exe",aqstrList);
        if(!myProcess->waitForStarted()){
            qDebug()<<"Make failed:"<<myProcess->errorString();
        }else{
            qDebug()<<"Child Prpcess Started."<<myProcess->readAll();
        }
    }else if(burnerTools == ESPTOOL_ESP32){//ESP32烧录方式
        killProcess("esptool.exe");
        aqstrList<<"--chip"<<"esp32"<<"--port"<<port[0]<<"--baud"<<baud<<
                   "--before"<<"default_reset"<<"--after"<<"hard_reset"<<"write_flash"<<"-z"<<"--flash_mode"<<
                   "dio"<<"--flash_freq"<<frequency<<"--flash_size"<<"detect"<<"0xe000"<<fileName+"/esptool/boot_app0.bin"<<
                   "0x1000"<<fileName+"/esptool/"+bootloader<<"0x10000"<<ui->flashPath->text()<<"0x8000"<<ui->partitionPath->text();

        myProcess->start(fileName+"/esptool/esptool.exe",aqstrList);
        if(!myProcess->waitForStarted()){
            qDebug()<<"Make failed:"<<myProcess->errorString();
        }else{
            qDebug()<<"Child Prpcess Started."<<myProcess->readAll();
        }
    }else if (burnerTools == ESPTOOL_ESP8266){//ESP8266烧录方式
        killProcess("esptool1.exe");
        aqstrList<<"-vv"<<"-cd"<<"nodemcu"<<"-cb"<<"921600"<<"-cp"<<port[0]<<"-ca"<<"0x00000"<<"-cf"<<ui->flashPath->text();

        myProcess->start(fileName+"/esptool/esptool1.exe",aqstrList);//execute
        if(!myProcess->waitForStarted()){
            qDebug()<<"Make failed:"<<myProcess->errorString();
        }else{
            qDebug()<<"Child Prpcess Started."<<myProcess->readAll();
        }
    }else if (burnerTools == AVRDUDE_M0){//M0烧录方式
        killProcess("avrdude.exe");
        qint8 size = portStringList.size();
        resetSerial();
        QStringList newPortStringList;
        while(true){
            foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
                newPortStringList += info.portName();
                qDebug()<<info.portName();
            }
            if(newPortStringList.size() == size){
                newPortStringList[(newPortStringList.size()-1)] != port[0];
                break;
            }
        }

        qDebug()<<newPortStringList[0];
        aqstrList<<"-C"<<fileName+"/avrtool/avrdude.conf"<<"-v"<<"-v"<<"-p"+model<<"-c"+agreement<<
                   "-P"+newPortStringList[(newPortStringList.size()-1)]<<"-b57600"<<"-Uflash:w:"+ui->flashPath->text()+":i";
        qDebug()<<aqstrList;
        myProcess->start(fileName+"/avrtool/avrdude.exe",aqstrList);
        if(!myProcess->waitForStarted()){
            qDebug()<<"Make failed:"<<myProcess->errorString();
        }else{
            qDebug()<<"Child Prpcess Started."<<myProcess->readAll();
        }
    }else if (burnerTools == AVRDUDE_M3){//M3烧录方式
        killProcess("avrdude.exe");
        qint8 size = portStringList.size();
        resetSerial();
        QStringList newPortStringList;
        while(true){
            foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
                newPortStringList += info.portName();
                qDebug()<<newPortStringList;
            }
            if(newPortStringList.size() == size){
                newPortStringList[(newPortStringList.size()-1)] != port[0];
                break;
            }
        }
        aqstrList<<"-C"<<fileName+"\\avrtool\\avrdude.conf"<<"-v"<<"-p"+model<<"-c"+agreement<<
                   "-P"+newPortStringList[(newPortStringList.size()-1)]<<"-b57600"<<"-D"<<"-Uflash:w:"+ui->flashPath->text()+":i";
        qDebug()<<aqstrList;
        myProcess->start(fileName+"\\avrtool\\avrdude.exe",aqstrList);
        if(!myProcess->waitForStarted()){
            qDebug()<<"Make failed:"<<myProcess->errorString();
        }else{
            qDebug()<<"Child Prpcess Started."<<myProcess->readAll();
        }
    }
}

void Widget::printReturnData(){
    QString returnData;
    returnData=myProcess->read(500);
    QTextCursor tc = ui->informationEdit->textCursor();
    tc.insertText(returnData);
    ui->informationEdit->moveCursor(QTextCursor::End);
}

void Widget::killProcess(const QString &processName)
{
    QString c = "taskkill /im " + processName + " /f";
    myProcess->execute(c);
    myProcess->close();
}

void Widget::motherboardsChange(){
    switch(ui->boardComboBox->currentIndex()){
        case UNO:
            burnerTools = AVRDUDE;
            model = "atmega328p";
            agreement = "arduino";
            baud  = "115200";
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        case MEAG2560:
            burnerTools = AVRDUDE;
            model = "atmega2560";
            agreement = "wiring";
            baud  = "115200";
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        case ESP32:
            burnerTools = ESPTOOL_ESP32;
            bootloader ="bootloader_dio_80m.bin";
            baud="921600";
            frequency  = "80m";
            ui->pathButton_2->setEnabled(true);
            ui->partitionPath->setEnabled(true);
        break;
        case ESP8266:
            burnerTools = ESPTOOL_ESP8266;
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        case M0:
            burnerTools = AVRDUDE_M0;
            model = "atmega2560";
            agreement = "stk500v2";
            baud  = "115200";
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        case TINKERNODE:
            burnerTools = ESPTOOL_ESP32;
            bootloader ="bootloader_dio_40m.bin";
            baud="512000";
            frequency  = "40m";
            ui->pathButton_2->setEnabled(true);
            ui->partitionPath->setEnabled(true);
        break;
        case CURIENANO:
            burnerTools = AVRDUDE_M3;
            model = "atmega32u4";
            agreement = "avr109";
            baud  = "57600";
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        case BLUNOM3:
            burnerTools = AVRDUDE;
            model = "ATmega2560";
            agreement = "wiring";
            baud  = "115200";
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        case LEONARDO:
            burnerTools = AVRDUDE_M3;
            model = "atmega32u4";
            agreement = "avr109";
            baud  = "57600";
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        case NANO:
            burnerTools = AVRDUDE_M3;
            model = "atmega328p";
            agreement = "arduino";
            baud  = "57600";
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        case BEETLE:
            burnerTools = AVRDUDE_M3;
            model = "atmega32u4";
            agreement = "avr109";
            baud  = "57600";
            ui->pathButton_2->setEnabled(false);
            ui->partitionPath->setEnabled(false);
        break;
        default:
            break;

    }

}
void Widget::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Widget::resetSerial()
{
    serialPort->setPortName(port[0]);

    serialPort->setBaudRate(QSerialPort::Baud1200);//设置波特率
    serialPort->setDataBits(QSerialPort::Data8);//设置数据位
    serialPort->setParity(QSerialPort::NoParity);//设置校验位
    serialPort->setFlowControl(QSerialPort::NoFlowControl);//设置流控制
    serialPort->setStopBits(QSerialPort::OneStop);//设置停止位
    serialPort->open(QIODevice::ReadWrite);

    sleep(1000);
    serialPort->close();
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent *event)
{
    QString name = event->mimeData()->urls().first().toString();
    qDebug()<<name;
     QString headName = name.mid(0, 8);
     if(QString::compare(headName,"file:///") == 0){
        QStringList filePath =(name).split("///");
        QFileInfo fileinfo;
        fileinfo = QFileInfo(filePath[1]);
        QStringList trailer = (fileinfo.fileName()).split(".");
        if(QString::compare(trailer[2],"partitions") == 0){
            ui->partitionPath->setText(filePath[1]);
        }else{
            ui->flashPath->setText(filePath[1]);
            qDebug()<<ui->flashPath->text();
        }
     }else{
     QString networkfile = name.mid(5, -1);
        ui->flashPath->setText(networkfile);
        QFileInfo fileinfo;
        fileinfo = QFileInfo(networkfile);
        QStringList trailer = (fileinfo.fileName()).split(".");
        if(QString::compare(trailer[2],"partitions") == 0){
            ui->partitionPath->setText(networkfile);
        }else{
            ui->flashPath->setText(networkfile);
            qDebug()<<ui->flashPath->text();
        }
     }


}
