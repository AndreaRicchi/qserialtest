#include <QCoreApplication>
#include <QSerialPort>
#include <QSocketNotifier>
#include <QStringList>
#include <QTextStream>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    const int argumentCount = QCoreApplication::arguments().size();
    const QStringList argumentList = QCoreApplication::arguments();

    QTextStream standardOutput(stdout);
    QTextStream standardInput(stdin);

    if (argumentCount == 1) {
        standardOutput << QObject::tr("Usage: %1 <serialportname> [baudrate]")
                              .arg(argumentList.first())
                       << endl;
        return 1;
    }

    QSerialPort serialPort;
    const QString serialPortName = argumentList.at(1);
    serialPort.setPortName(serialPortName);

    const int serialPortBaudRate = (argumentCount > 2)
        ? argumentList.at(2).toInt()
        : QSerialPort::Baud9600;
    serialPort.setBaudRate(serialPortBaudRate);

    if (!serialPort.open(QIODevice::ReadWrite)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")
                              .arg(serialPortName)
                              .arg(serialPort.error())
                       << endl;
        return 1;
    }

    QObject::connect(&serialPort, &QSerialPort::readyRead, [&]() {
        standardOutput << "Recieved: " << serialPort.readAll() << endl;
    });

    QSocketNotifier sn(fileno(stdin), QSocketNotifier::Read);
    QObject::connect(&sn, &QSocketNotifier::activated, [&](int) {
        QString line;
        standardInput.readLineInto(&line);
        serialPort.write(line.toUtf8());
    });

    return a.exec();
}
