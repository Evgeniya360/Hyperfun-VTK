#include "zipproc.h"

#include "zip.h"
#include "unzip.h"

#include <QtCore/QFile>
#include <QProgressDialog>
#include <QTimer>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QtCore/QFileInfo>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
 #include <QDir>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
 //#include "MyProgDialog.cpp"
using namespace std;
QString ZipProc::prepairAndCompress(QStringList fileNames)
{
    //Creation of directory and copying files

  /*  QString ZfileDir=QFileInfo(fileNames[0]).absolutePath()+QString("/")+QFileInfo(fileNames[0]).baseName();
    QString Zfile=ZfileDir+QString(".zip");

    QFileInfo DirInfo(fileNames[0]);
    QDir baseD(DirInfo.absolutePath());
    baseD.mkdir(DirInfo.baseName());


    for (int i=0;i<fileNames.size();i++)
    {
    QString filen=fileNames[i];
     QFileInfo fi(filen);
    QFile::copy(fi.absoluteFilePath(), ZfileDir+"/"+fi.fileName());
    }*/

    //archivation of files
    QString ZfileDir=QFileInfo(fileNames[0]).absolutePath();//+QString("/")+QFileInfo(fileNames[0]).baseName();
       QString Zfile=ZfileDir+QString("/")+QFileInfo(fileNames[0]).baseName()+QString(".zip");
    for (int i=0;i<fileNames.size();i++)
    {
    QString filen=fileNames[i];
     QFileInfo fi(filen);
    QFile::copy(fi.absoluteFilePath(), ZfileDir+"/"+fi.fileName());
    }
      ZipProc zip;
   // QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(compress()));
  //  timer->start(1000);

      QDialog *mbox = new QDialog;


  //  QMessageBox *mbox = new   QMessageBox();
     mbox->setWindowTitle(tr("Archivation"));
      mbox->setMinimumWidth(150);
       mbox->setMaximumHeight(150);
     // mbox->setInformativeText(tr("Archivation .."));
     // mbox->setText(tr("Archivation .."));
      mbox->setModal(false);
   //   mbox->setCancelButton(0) ;//setCancelable(false);
    //  mbox->sets
   //   mbox->setStandardButtons(QMessageBox::NoButton);
   Qt::WindowFlags wFlags = mbox->windowFlags();
      if(Qt::WindowCloseButtonHint == (wFlags & Qt::WindowCloseButtonHint))
      {
      wFlags = wFlags ^ Qt::WindowCloseButtonHint;
      mbox->setWindowFlags(wFlags);
      }
      mbox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowTitleHint);
      mbox->setWindowIcon(QIcon(":/icons/icons/13B3.GIF"));
     // mbox->setWindowFlags(mbox->windowFlags() ^ Qt::WindowCloseButtonHint);
  //    mbox->setIcon(QMessageBox::NoIcon);
      //mbox->sh/* */
    //  mBox->
     // mbox->setWindowFlags(Qt::WindowTitleHint | Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);


      QLabel* label = new QLabel(mbox);
      //  QLabel* label2 = new QLabel(mbox);

      label->setText("         Zip file creation ... ");
    //  label->setAlignment(Qt::AlignRight);
   //   label2->setMovie(status_gif);
   //    label2->setAlignment(Qt::AlignLeft);
  //     status_gif->start();
       QApplication::processEvents();

       //status_gif->dynamicPropertyNames()

 //     label2->setFixedSize(20,20);

    //  mbox->add>addAction(status_layout->addWidget(_status_animation);

      mbox->show();
      //QTimer::oneShot(2000, mbox, SLOT(hide()));
/**/

   //   QProgressDialog* pd = new QProgressDialog("Task in progress.", "Cancel", 0, 100000);
    //   connect(pd, SIGNAL(canceled()), this, SLOT(cancel()));
   //   QTimer* t = new QTimer(pd);
   //   connect(t, SIGNAL(timeout()), this, SLOT(perform()));
    //   t->start(0);

//MyProgressDialog* pd = new MyProgressDialog();
//pd->show();
//mbox->raise();
QCoreApplication::processEvents();
    // zip.compress(Zfile,  ZfileDir, 0);
zip.compress2(Zfile, fileNames, 0);
//pd->hide();
//pd->setResult(QDialog::Accepted);
      mbox->hide();
      mbox->setResult(QDialog::Accepted);
      //cleaning after directory
   /* for (int i=0;i<fileNames.size();i++)
    {
    QString filen=fileNames[i];
     QFileInfo fi(filen);
     baseD.remove (ZfileDir+"/"+fi.fileName());
    }

    baseD.rmdir(DirInfo.baseName());
*/
      return Zfile;
}




QString ZipProc::prepairAndCompress2(QString ZfileDir)
{
    //Creation of directory and copying files

  /*  QString ZfileDir=QFileInfo(fileNames[0]).absolutePath()+QString("/")+QFileInfo(fileNames[0]).baseName();
    QString Zfile=ZfileDir+QString(".zip");

    QFileInfo DirInfo(fileNames[0]);
    QDir baseD(DirInfo.absolutePath());
    baseD.mkdir(DirInfo.baseName());


    for (int i=0;i<fileNames.size();i++)
    {
    QString filen=fileNames[i];
     QFileInfo fi(filen);
    QFile::copy(fi.absoluteFilePath(), ZfileDir+"/"+fi.fileName());
    }*/

    //archivation of files
 //   QString ZfileDir=QFileInfo(dir).absolutePath();//+QString("/")+QFileInfo(fileNames[0]).baseName();
       QString Zfile=ZfileDir+QString(".zip");

      ZipProc zip;
   // QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(compress()));
  //  timer->start(1000);

      QDialog *mbox = new QDialog;


  //  QMessageBox *mbox = new   QMessageBox();
     mbox->setWindowTitle(tr("Archivation"));
      mbox->setMinimumWidth(150);
       mbox->setMaximumHeight(150);
     // mbox->setInformativeText(tr("Archivation .."));
     // mbox->setText(tr("Archivation .."));
      mbox->setModal(false);
   //   mbox->setCancelButton(0) ;//setCancelable(false);
    //  mbox->sets
   //   mbox->setStandardButtons(QMessageBox::NoButton);
   Qt::WindowFlags wFlags = mbox->windowFlags();
      if(Qt::WindowCloseButtonHint == (wFlags & Qt::WindowCloseButtonHint))
      {
      wFlags = wFlags ^ Qt::WindowCloseButtonHint;
      mbox->setWindowFlags(wFlags);
      }
      mbox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowTitleHint);
      mbox->setWindowIcon(QIcon(":/icons/icons/13B3.GIF"));
     // mbox->setWindowFlags(mbox->windowFlags() ^ Qt::WindowCloseButtonHint);
  //    mbox->setIcon(QMessageBox::NoIcon);
      //mbox->sh/* */
    //  mBox->
     // mbox->setWindowFlags(Qt::WindowTitleHint | Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);


      QLabel* label = new QLabel(mbox);
      //  QLabel* label2 = new QLabel(mbox);

      label->setText("         Zip file creation ... ");
    //  label->setAlignment(Qt::AlignRight);
   //   label2->setMovie(status_gif);
   //    label2->setAlignment(Qt::AlignLeft);
  //     status_gif->start();
       QApplication::processEvents();

       //status_gif->dynamicPropertyNames()

 //     label2->setFixedSize(20,20);

    //  mbox->add>addAction(status_layout->addWidget(_status_animation);

      mbox->show();
      //QTimer::oneShot(2000, mbox, SLOT(hide()));
/**/

   //   QProgressDialog* pd = new QProgressDialog("Task in progress.", "Cancel", 0, 100000);
    //   connect(pd, SIGNAL(canceled()), this, SLOT(cancel()));
   //   QTimer* t = new QTimer(pd);
   //   connect(t, SIGNAL(timeout()), this, SLOT(perform()));
    //   t->start(0);

//MyProgressDialog* pd = new MyProgressDialog();
//pd->show();
//mbox->raise();
QCoreApplication::processEvents();
    zip.compress(Zfile,  ZfileDir, 0);

      mbox->hide();
      mbox->setResult(QDialog::Accepted);
      //cleaning after directory
   /* for (int i=0;i<fileNames.size();i++)
    {
    QString filen=fileNames[i];
     QFileInfo fi(filen);
     baseD.remove (ZfileDir+"/"+fi.fileName());
    }

    baseD.rmdir(DirInfo.baseName());
*/
      return Zfile;
}

bool ZipProc::decompress(const QString& file, const QString& out, const QString& pwd)
{

    if (!QFile::exists(file)) {
        cout << "File does not exist." << endl << endl;
        return false;
    }

    UnZip::ErrorCode ec;
    UnZip uz;

    if (!pwd.isEmpty())
        uz.setPassword(pwd);

    //create directory
    QFileInfo fi(file);
    QDir baseD(out);
    baseD.mkdir(fi.baseName());

    QString dir=QString(out)+QString("/")+QString(fi.baseName());

    ec = uz.openArchive(file);
    if (ec != UnZip::Ok) {
        cout << "Failed to open archive: " << uz.formatError(ec).toLatin1().data() << endl << endl;
        return false;
    }

    ec = uz.extractAll(dir);
    if (ec != UnZip::Ok) {
        cout << "Extraction failed: " << uz.formatError(ec).toLatin1().data() << endl << endl;
        uz.closeArchive();
        return false;
    }

    return true;
}

bool ZipProc::compress2(const QString& zip, const QStringList& files, const QString& pwd)
{
   for(int i=0;i<files.size();i++)
   {
       QFileInfo fi(files[i]);
    if (!fi.isFile()) {
        cout << "File does not exist." << endl << endl;
        return false;
    }
   }

    Zip::ErrorCode ec;
    Zip uz;

    ec = uz.createArchive(zip);
    if (ec != Zip::Ok) {
        cout << "Unable to create archive: " << uz.formatError(ec).toLatin1().data() << endl << endl;
        return false;
    }

    uz.setPassword(pwd);
    ec = uz.addFiles(files);
    if (ec != Zip::Ok) {
        cout << "Unable to add directory: " << uz.formatError(ec).toLatin1().data() << endl << endl;
    }

    uz.setArchiveComment("This archive has been created using OSDaB Zip (http://osdab.42cows.org/).");

    if (uz.closeArchive() != Zip::Ok) {
        cout << "Unable to close the archive: " << uz.formatError(ec).toLatin1().data() << endl << endl;
    }

    return ec == Zip::Ok;
}

bool ZipProc::compress(const QString& zip, const QString& dir, const QString& pwd)
{
    QFileInfo fi(dir);
    if (!fi.isDir()) {
        cout << "Directory does not exist." << endl << endl;
        return false;
    }

    Zip::ErrorCode ec;
    Zip uz;

    ec = uz.createArchive(zip);
    if (ec != Zip::Ok) {
        cout << "Unable to create archive: " << uz.formatError(ec).toLatin1().data() << endl << endl;
        return false;
    }

    uz.setPassword(pwd);
    ec = uz.addDirectory(dir);
    if (ec != Zip::Ok) {
        cout << "Unable to add directory: " << uz.formatError(ec).toLatin1().data() << endl << endl;
    }

    uz.setArchiveComment("This archive has been created using OSDaB Zip (http://osdab.42cows.org/).");

    if (uz.closeArchive() != Zip::Ok) {
        cout << "Unable to close the archive: " << uz.formatError(ec).toLatin1().data() << endl << endl;
    }

    return ec == Zip::Ok;
}

bool ZipProc::listFiles(const QString& file, const QString& pwd)
{
    if (!QFile::exists(file)) {
        cout << "File does not exist." << endl << endl;
        return false;
    }

    UnZip::ErrorCode ec;
    UnZip uz;

    if (!pwd.isEmpty())
        uz.setPassword(pwd);

    ec = uz.openArchive(file);
    if (ec != UnZip::Ok) {
        cout << "Unable to open archive: " << uz.formatError(ec).toLatin1().data() << endl << endl;
        return false;
    }

    QString comment = uz.archiveComment();
    if (!comment.isEmpty())
        cout << "Archive comment: " << comment.toLatin1().data() << endl << endl;

    QList<UnZip::ZipEntry> list = uz.entryList();
    if (list.isEmpty()) {
        cout << "Empty archive.";
    } else {
        cout.setf(ios::left);
        cout << setw(40) << "Filename";
        cout.unsetf(ios::left);
        cout << setw(10) << "Size" << setw(10) << "Ratio" << setw(10) << "CRC32" << endl;
        cout.setf(ios::left);
        cout << setw(40) << "--------";
        cout.unsetf(ios::left);
        cout << setw(10) << "----" << setw(10) << "-----" << setw(10) << "-----" << endl;

        for (int i = 0; i < list.size(); ++i) {
            const UnZip::ZipEntry& entry = list.at(i);

            double ratio = entry.uncompressedSize == 0 ? 0 : 100 - (double) entry.compressedSize * 100 / (double) entry.uncompressedSize;

            QString ratioS = QString::number(ratio, 'f', 2).append("%");
            QString crc;
            crc = crc.sprintf("%X", entry.crc32).rightJustified(8, '0');
            QString file = entry.filename;
            int idx = file.lastIndexOf("/");
            if (idx >= 0 && idx != file.length()-1)
                file = file.right(file.length() - idx - 1);
            file = file.leftJustified(40, ' ', true);

            if (entry.encrypted)
                file.append("*");

            cout << setw(40) << file.toLatin1().data() << setw(10) << entry.uncompressedSize << setw(10) << ratioS.toLatin1().data() << setw(10) << crc.toLatin1().data() << endl;
        }
    }

    uz.closeArchive();
    return true;
}

bool ZipProc::verifyArchive(const QString& file, const QString& pwd)
{
    if (!QFile::exists(file)) {
        cout << "File does not exist." << endl << endl;
        return false;
    }

    UnZip uz;
    UnZip::ErrorCode ec =UnZip::Ok;

    if (!pwd.isEmpty())
        uz.setPassword(pwd);

    ec = uz.openArchive(file);
    if (ec != UnZip::Ok) {
        cout << "Unable to open archive: " << uz.formatError(ec).toLatin1().data() << endl << endl;
        return false;
    }

    ec = uz.verifyArchive();
    switch (ec) {
    case UnZip::WrongPassword:
        cout << "Wrong password." << endl << endl;
        break;
    case UnZip::PartiallyCorrupted:
        cout << "Corrupted entries found." << endl << endl;
        break;
    case UnZip::Corrupted:
        cout << "Corrupted archive." << endl << endl;
        break;
    case UnZip::Ok:
        cout << "No problem found." << endl << endl;
        break;
    default:
        cout << "An error occurred: " << (int)ec << endl << endl;
    }

    uz.closeArchive();
    return ec == UnZip::Ok;
}
