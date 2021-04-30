#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QCheckBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //------------------------------
    //table1 基礎のテーブル（全列　入力値は文字列。）
    QStringList labels_1;
    ui->tableWidget_1->setColumnCount(3);
    labels_1 << "A" << "B" << "C";
    ui->tableWidget_1->setHorizontalHeaderLabels(labels_1);
    ui->tableWidget_1->QTableWidget::horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_1->setSelectionBehavior(QAbstractItemView::SelectRows); //tableセルクリックで1行すべて選択
    ui->tableWidget_1->setEditTriggers(QAbstractItemView::NoEditTriggers);  //Tableセル直接編集禁止
    ui->tableWidget_1->setColumnWidth(0, 40); //0列目　幅40
    ui->tableWidget_1->setColumnWidth(1, 80); //1列目　幅80
    connect(ui->tableWidget_1,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(input_table1));

    //[DEBUG] -start- table1
    for(int row=0; row<5; row++){
        ui->tableWidget_1->insertRow(ui->tableWidget_1->rowCount());
        for(int col=0; col<ui->tableWidget_1->horizontalHeader()->count(); col++){
            QString tmpStr = QString::number(row) + "_" + QString::number(col) ;
            ui->tableWidget_1->setItem(row, col, new QTableWidgetItem(tmpStr));
        }
    }
    //[DEBUG] -end-

    //------------------------------
    //table2 1列目　チェックボックス。その他の列の入力値は文字列。
    QStringList labels_2;
    ui->tableWidget_2->setColumnCount(3);
    labels_1 << "A" << "B" << "C";
    ui->tableWidget_2->setHorizontalHeaderLabels(labels_1);
    ui->tableWidget_2->QTableWidget::horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows); //tableセルクリックで1行すべて選択
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //Tableセル直接編集禁止
    ui->tableWidget_2->setColumnWidth(0, 40); //0列目　幅40
    ui->tableWidget_2->setColumnWidth(1, 80); //1列目　幅80
    //connect(ui->tableWidget_2,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(input_table1));
    //[DEBUG] -start- table2
    for(int row=0; row<3; row++){
        on_pushButton_add_2_clicked();
        for(int col=1; col<ui->tableWidget_2->horizontalHeader()->count(); col++){
            QString tmpStr = QString::number(row) + "_" + QString::number(col) ;
            ui->tableWidget_2->setItem(row, col, new QTableWidgetItem(tmpStr));
        }
    }
    //[DEBUG] -end- table2

    //------------------------------
    //table2 1列目　チェックボックス。その他の列の入力値は文字列。
    ui->label_3->setVisible(false); //本番時はコメントアウト解除する。//設定未　一時的に表示しない
    ui->pushButton_add_3->setVisible(false); //本番時はコメントアウト解除する。//設定未　一時的に表示しない
    ui->pushButton_delete_3->setVisible(false); //本番時はコメントアウト解除する。//設定未　一時的に表示しない
    ui->tableWidget_3->setVisible(false); //本番時はコメントアウト解除する。//設定未　一時的に表示しない

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input_table1(){
    qDebug() << "test";
//    ui->groupBox_1_show;
//    ui->minx
}

void MainWindow::on_pushButton_add_clicked()
{
    ui->tableWidget_1->insertRow(ui->tableWidget_1->rowCount());
    for(int n=0; n<3; n++){
        ui->tableWidget_1->setItem(ui->tableWidget_1->rowCount()-1, n, new QTableWidgetItem(""));
    }
}

void MainWindow::on_pushButton_delete_clicked()
{
    QModelIndexList selection = ui->tableWidget_1->selectionModel()->selectedRows();

    int max_row = ui->tableWidget_1->rowCount();
    //　動的配列　tmp_ary
    int* tmp_ary = new int[max_row]; //値の参照　&tmp_ary[max_row]
    int cnt = 0;
    // テーブル全行参照し、選択された行番号は記録する。（ここで削除までするとずれが生じるため先に最後までチェックする）
    int tmp_cnt = ui->tableWidget_1->rowCount();
    for(int m=0; m < ui->tableWidget_1->rowCount(); m++){
        if(ui->tableWidget_1->item(m,0)->isSelected()){
            tmp_ary[cnt] = m;
            cnt++;
        }
    }
    cnt--;

    // 選択された行の削除
    int del_cnt = 0;
    int row_new = 0;
    for(int i=0; i<=cnt; i++){
        row_new = tmp_ary[i];
        if(i > 0){
            row_new = row_new - del_cnt;
        }
        ui->tableWidget_1->removeRow(row_new);
        del_cnt = del_cnt + 1;
    }

    //動的配列解放
    delete []  tmp_ary;
}

void MainWindow::on_pushButton_up_clicked()
{
        QModelIndexList selection = ui->tableWidget_1->selectionModel()->selectedRows();

        ui->tableWidget_1->insertRow(selection[0].row() + selection.size());
        for(int col=0; col < ui->tableWidget_1->horizontalHeader()->count(); col++){
            QString tmpstr = ui->tableWidget_1->item(selection[0].row()-1, col)->text(); //選択行の1つ上行を、選択行の下の段にコピーする。
            ui->tableWidget_1->setItem(selection[0].row() + selection.size(), col,  new QTableWidgetItem(tmpstr));
        }
        ui->tableWidget_1->removeRow(selection[0].row()-1);

        ui->tableWidget_1->setVisible(false); //コピー後の表示　行ズレ対策
        ui->tableWidget_1->setVisible(true);  //コピー後の表示　行ズレ対策
}

void MainWindow::on_pushButton_down_clicked()
{
    QModelIndexList selection = ui->tableWidget_1->selectionModel()->selectedRows();

    ui->tableWidget_1->insertRow(selection[0].row() + selection.size()+1);
    //if(selection[0].row() < ui->tableWidget_1->rowCount()){
        for(int col=0; col < ui->tableWidget_1->horizontalHeader()->count(); col++){
            QString tmpstr = ui->tableWidget_1->item(selection[0].row(), col)->text(); //選択行の1つ下行を、選択行の下の段にコピーする。※前処理での行挿入で2段下になっている。
            ui->tableWidget_1->setItem(selection[0].row() + selection.size() +1 , col,  new QTableWidgetItem(tmpstr));
        }
    //}
    ui->tableWidget_1->removeRow(selection[0].row());

    ui->tableWidget_1->setVisible(false); //コピー後の表示　行ズレ対策
    ui->tableWidget_1->setVisible(true);  //コピー後の表示　行ズレ対策
}

//---------------------------------------------------------
//Table2 チェックボタンあり
void MainWindow::on_pushButton_add_2_clicked()
{
    ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
    //0列目　チェックボックス配置
    QCheckBox *pItemCheck0 = new QCheckBox();
    QWidget *pWidget0 = new QWidget();
    QHBoxLayout *pLayout0 = new QHBoxLayout();
    pItemCheck0->setCheckState(Qt::Checked);
    pLayout0->setAlignment(Qt::AlignCenter);
    pLayout0->addWidget(pItemCheck0);
    pWidget0->setLayout(pLayout0);
    ui->tableWidget_2->setCellWidget(ui->tableWidget_2->rowCount()-1, 0, pWidget0);
    //チェックボックスON/OFF切り替え時のアクション
    // int はチェック状態　引数はOFF=0 ON=2. 何行目がチェックされたか送りたいが、自分で指定した値は送れないのでグローバル変数で渡す
    g_rowChecked_tableWidget_01 = ui->tableWidget_2->rowCount() - 1;
    connect(pItemCheck0, SIGNAL(stateChanged(int)), this, SLOT(func_table2ckbox_changed(int)));

    //1, 2列目セット
    for(int n=1; n<2; n++){
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, n, new QTableWidgetItem(""));
    }
}

void MainWindow::func_table2ckbox_changed(int input_num_checked){
    QString str_onoff = "OFF";
    if(input_num_checked==0){
        str_onoff = "OFF";
    } else {
        str_onoff = "ON";
    }
    QString msg = "[DEBUG]checked row=" + QString::number(input_num_checked);
    //QMessageBox::information(this, "notice", msg);
}

void MainWindow::on_pushButton_Run_2_clicked()
{
    //テーブル2 全行のチェックボックス状態を表示する
    QString msg="";
    for(int row=0; row < ui->tableWidget_2->rowCount(); row++){
        QWidget *pWidget = ui->tableWidget_2->cellWidget(row,0);
        QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
        QString str_onoff = "OFF";
        if(checkbox->isChecked()){
            str_onoff = "ON";
        } else {
            str_onoff = "OFF";
        }
        msg += "\n checked row=" + QString::number(row) + " checked=" + str_onoff;
    }
    QMessageBox::information(this, "notice", msg);
}

void MainWindow::on_pushButton_delete_2_clicked()
{
    QModelIndexList selection = ui->tableWidget_2->selectionModel()->selectedRows();

    int max_row = ui->tableWidget_2->rowCount();
    //　動的配列　tmp_ary
    int* tmp_ary = new int[max_row]; //値の参照　&tmp_ary[max_row]
    int cnt = 0;
    // テーブル全行参照し、選択された行番号は記録する。（ここで削除までするとずれが生じるため先に最後までチェックする）
    int tmp_cnt = ui->tableWidget_2->rowCount();
    for(int m=0; m < ui->tableWidget_2->rowCount(); m++){
        if(ui->tableWidget_2->item(m,1)->isSelected()){
            tmp_ary[cnt] = m;
            cnt++;
        }
    }
    cnt--;

    // 選択された行の削除
    int del_cnt = 0;
    int row_new = 0;
    for(int i=0; i<=cnt; i++){
        row_new = tmp_ary[i];
        if(i > 0){
            row_new = row_new - del_cnt;
        }
        ui->tableWidget_2->removeRow(row_new);
        del_cnt = del_cnt + 1;
    }

    //動的配列解放
    delete []  tmp_ary;
}
