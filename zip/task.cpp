#include "task.h"
#include "zipproc.h"
#include "vtkdialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QtGui>
#include "SimpleView.h"

void Task::run()
{
    /*
bool open=false;
if(open)
{


    SimpleView* mySimpleView=new SimpleView;
    mySimpleView->show();
}
    else*/


    {
       // QFileDialog d;
        d=new QFileDialog();
        d->setAcceptMode (QFileDialog::AcceptOpen);
     //   d.setFileMode(QFileDialog::AnyFile);


      //d.setFilter(selfilter);
      d->setDirectory(QDir::homePath());
      d->setWindowTitle(QObject::tr("Открыть файлы Hyperfun"));
     d->setFileMode(QFileDialog::ExistingFiles);
      d->setViewMode(QFileDialog::Detail);
     button = new QPushButton(d);
      button->setCheckable(true);
           button->setText("Zip");
           button->setMaximumWidth(30);
           button->setObjectName("pbDelRight");


         /*  button->setStyleSheet("background-color: rgb(224, 255, 0);"
                       " :pressed { background-color: rgb(224, 0, 0);  }  "
                                 ":hover { background-color:yellow; }"
                                 ":active{ background-color: rgb(224, 0, 0);");
                       "QPushButton#pushButton {background-color:yellow}"
                              " QPushButton#pushButton:pressed { background-color: rgb(224, 0, 0);  }"

                                " QPushButton#pushButton:hover {background-color: rgb(224, 255, 0); }"
                                 );*/


      /*     QCheckBox *button2 = new QCheckBox(d);
                     // button2->setCheckable(false);
                           button2->setText(tr("Выбрать дирректорию/файлы"));
                           button2->setMinimumWidth(250);

*/

           QRadioButton *dirs = new QRadioButton(tr ("Дирректория") );
             QRadioButton *files = new QRadioButton(tr ( "Файлы"));
              QButtonGroup *button2 = new QButtonGroup(d );
              button2->addButton(dirs);
               button2->addButton(files);


                      QGridLayout *layout = (QGridLayout*)d->layout();

                      QLayoutItem* Ok=layout->itemAtPosition(2,2);
                      QLayoutItem* Cancel=layout->itemAtPosition(3,2);


                     layout->removeItem(Ok);
                      layout->addItem(Ok,1,3,Qt::AlignRight);
                      layout->removeItem(Cancel);
                      layout->addItem(Cancel,2,3,Qt::AlignRight);


                      layout->addWidget(button, 2, 2,Qt::AlignRight);


                           QLayoutItem* unused=layout->itemAtPosition(3,1);
                           layout->removeItem(unused);
                            layout->addItem(unused,4,1,Qt::AlignRight);
                           unused->widget()->hide();
                          //delete unused;
                           QLayoutItem* unused2=layout->itemAtPosition(3,0);
                           layout->removeItem(unused2);
                            layout->addItem(unused2,4,0,Qt::AlignRight);
                            unused2->widget()->hide();

                            //layout->addWidget(button2, 3, 1,Qt::AlignRight);
                            layout->addWidget(dirs, 3, 1,Qt::AlignRight);
                             layout->addWidget(files, 3, 1,Qt::AlignLeft);
                              files->setChecked(true);
                            //  QObject::connect(button2, SIGNAL(clicked()), this , SLOT(setDialogMode()));
                              QObject::connect(files, SIGNAL(clicked()), this , SLOT(setDialogMode()));
                               QObject::connect(dirs, SIGNAL(clicked()), this , SLOT(setDialogMode()));
                          //delete unused2;
                           // layout->removeItem(unused);
                               d->setLabelText( QFileDialog::Reject, tr("Отмена") );

                               d->setFileMode(QFileDialog::DirectoryOnly);
                                 d->setLabelText( QFileDialog::LookIn, tr("Открыть") );
                                  d->setLabelText( QFileDialog::Accept, tr("Открыть") );
                                 // d->setLabelText( QFileDialog::FileType, tr("Дирректория") );

                             d->setFileMode(QFileDialog::ExistingFiles);
                             d->setLabelText( QFileDialog::Accept, tr("Открыть") );
                             d->setLabelText( QFileDialog::FileName, tr("Имя файла") );
      if (d->exec() == QDialog::Rejected)
          return;

        /*  QString fileNames = QFileDialog::getSaveFileNames(this, "Сохранить Файл",
                                      path,
                                     "Модель GeRa (*.grm)");*/
      QStringList fileNames=d->selectedFiles();


      if(fileNames.isEmpty()) return;
       //if(fileNames.isNull()) return;
      if (d->fileMode()==QFileDialog::DirectoryOnly)
          button->setChecked(true);

      if(button->isChecked())
      {
          QString Zfile;
          if (d->fileMode()==QFileDialog::ExistingFiles)

          Zfile= ZipProc::prepairAndCompress(fileNames);
          else
          Zfile= ZipProc::prepairAndCompress2(fileNames[0]);

          /*
           * SomeCode
           */
      }else
      {
      /*Some other code
       * */
      }

    }
    emit finished();
}

