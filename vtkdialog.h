#ifndef VTKDIALOG
#define VTKDIALOG

#include <QDialog>
#include <QStandardItemModel>
#include <vtkImageData.h>
#include <vtkRenderer.h>


class VTKDialog : public QDialog
{
    Q_OBJECT
    
public:
   // explicit VTKDialog(vtkImageData *map, QWidget *parent = 0);
    VTKDialog(QWidget *parent = 0);
    ~VTKDialog();



public slots:

private:
    enum { MAX_POINTS = 2 };

    //Ui::vtkDialog *ui;
    QStandardItemModel *model;
    vtkRenderer *renderer;

    int counter;
};

#endif // VTKDIALOG
