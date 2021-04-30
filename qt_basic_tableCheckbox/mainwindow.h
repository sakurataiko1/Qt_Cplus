#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void input_table1();

    void func_table2ckbox_changed(int num_checked); //table2に配置されたチェックボックスON/OFF切り替え時のアクション

    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();

    void on_pushButton_add_2_clicked();
    void on_pushButton_Run_2_clicked();
    void on_pushButton_delete_2_clicked();

private:
    Ui::MainWindow *ui;

    int g_rowChecked_tableWidget_01; // テーブルに配置された何行目のチェックボックスがチェックON/OFFされたか　をシグナルとして送るための変数。
};
#endif // MAINWINDOW_H
