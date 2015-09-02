#ifndef ZIPPROC_H
#define ZIPPROC_H
#include <QObject>
#include <QDialog>
class ZipProc: public QObject
{
public:

    static QString prepairAndCompress(QStringList fileNames);
    static QString prepairAndCompress2(QString dir);
    static bool decompress(const QString& file, const QString& out, const QString& pwd);

    static bool listFiles(const QString& file, const QString& pwd);
     static  bool verifyArchive(const QString& file, const QString& pwd);
private:
explicit ZipProc(QObject *parent = 0){}
~ZipProc(){}
      bool compress(const QString& zip, const QString& dir, const QString& pwd);
      bool compress2(const QString& zip, const QStringList& files, const QString& pwd);
};

#endif // ZIPPROC_H
