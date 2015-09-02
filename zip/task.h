#ifndef TASK_H
#define TASK_H
#include <QtGui>
#include <QtCore>





class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) {


    }
    QFileDialog* d;
     QPushButton *button;


   public slots:
       void setDialogMode()
       {
       //  d.close();
           if (d->fileMode()==QFileDialog::ExistingFiles)
           {


                 d->setFileMode(QFileDialog::DirectoryOnly);
                 d->setLabelText( QFileDialog::LookIn, tr("Открыть") );
                  d->setLabelText( QFileDialog::Accept, tr("Открыть") );

                    d->setLabelText( QFileDialog::FileName, tr("Дирректория") );
                  button->setChecked(true);
                  button->setEnabled(false);
           }
           else
           {
         d->setFileMode(QFileDialog::ExistingFiles);
         button->setChecked(false);
         button->setEnabled(true);
         d->setLabelText( QFileDialog::Accept, tr("Открыть") );
           d->setLabelText( QFileDialog::FileName, tr("Имя файла") );


           }
       //  d.open();
       };
 void run();
 /*   {
        // Do processing here
         //получить в командной строке имя конфигурационного файла из которого необходимо считать название архива

               //trying to get the arguments into a list
              // QStringList cmdline_args = a.arguments();
      // QString ConfigFileName=cmdline_args[1];
        if(SystemShellQt::isUnderSystemShell())
        {
               QStringList filesList=SystemShellQt::downloadFiles();

               for (int i=0;i<filesList.size();i++)
               {
                   QFileInfo fi(filesList[i]);
                   //extract all archieves found
                   if(fi.suffix()=="zip")
                   {
                   QZipReader reader(filesList[i]);
                   if(reader.exists()){


                       QDir baseDir(fi.absolutePath());
                      if( baseDir.mkdir(fi.baseName()))
                      {
                       QString path=fi.absolutePath()+QString("/")+fi.baseName();
                       reader.extractAll(path);
                      }
                      else

                      reader.extractAll(fi.absolutePath());


                       reader.close();
                   }
                   }
               }


}
        emit finished();
    }
*/
signals:
    void finished();
};

//#include "main.moc"
#endif // TASK_H
