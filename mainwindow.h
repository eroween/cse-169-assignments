#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QItemSelection>
#include <QTreeWidgetItem>
namespace Ui {
class MainWindow;
}

class object;
class joint;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char *argv[], QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionTest_triggered();
    void change_select(QTreeWidgetItem*,QTreeWidgetItem*);
    void skel_change_select(QTreeWidgetItem*,QTreeWidgetItem*);

    void on_actionTube_triggered();

    void on_limitxmax_changed(double);
    void on_limitymax_changed(double);
    void on_limitzmax_changed(double);

    void on_limitxmin_changed(double);
    void on_limitymin_changed(double);
    void on_limitzmin_changed(double);

    void on_positionx_changed(double);
    void on_positiony_changed(double);
    void on_positionz_changed(double);

    void on_rotationx_changed(double);
    void on_rotationy_changed(double);
    void on_rotationz_changed(double);


    void on_pushButton_clicked();

    void on_positionx_3_valueChanged(const QString &arg1);

    void on_positionx_3_valueChanged(double arg1);

    void on_positiony_3_valueChanged(double arg1);

    void on_positionz_3_valueChanged(double arg1);

    void on_positionx_4_valueChanged(double arg1);

    void on_positiony_4_valueChanged(double arg1);

    void on_positionz_4_valueChanged(double arg1);

    void on_scalex_valueChanged(double arg1);

    void on_positionx_2_valueChanged(double arg1);

    void on_positiony_2_valueChanged(double arg1);

    void on_positionz_2_valueChanged(double arg1);

private:
    void display_obj(object *obj);
    void fill_skel_tree(QTreeWidgetItem *wi_parent, joint *parent);
public:
    Ui::MainWindow *ui;
    int ac;
    char **av;
};

#endif // MAINWINDOW_H
