#include <QCoreApplication>
#include "zip/task.h"

#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QCleanlooksStyle>
#include "SimpleView.h"
#include "include/hfinterpreter.h"
 #include <QScopedPointer>
#include "hf/mainApp.h"

#define clientmode
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //получение аргументов строки
    //QTextCodec::setCodecForTr(QTextCodec::codecForTr());
    QTextCodec *langcodec=QTextCodec::codecForName("CP1251");
        QTextCodec::setCodecForTr(langcodec);
#ifdef clientmode // start probram in client mode
    QScopedPointer<SimpleView> mySimpleView(new SimpleView());
    mySimpleView->initMain(argc, argv);
    mySimpleView->show();



#else  //no code written at all - only dialog for sanding files to server opens
    Task *task = new Task(&a);

//StyleLoader::attach("myStyle.qss");
    QFile styleF;

    styleF.setFileName(":/qss/style.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    a.setStyleSheet(qssStr);
  //  QApplication::setStyle(new QCleanlooksStyle);


        // This will cause the application to exit when
        // the task signals finished.
        QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));

        // This will run the task from the application event loop.
        QTimer::singleShot(0, task, SLOT(run()));

#endif

    return a.exec();
}
