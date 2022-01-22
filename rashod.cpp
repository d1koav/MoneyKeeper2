#include "rashod.h"
#include "ui_rashod.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QMessageBox>
rashod::rashod(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::rashod)
{
  ui->setupUi(this);
  parse_serv();
}

rashod::~rashod()
{
  delete ui;
}

void rashod::on_pushButton_clicked()
{
    QSqlQuery query;
    float price = ui->lineEdit->text().toFloat();
    QString categ = ui->comboBox->currentText();
    QSqlQuery ins;
    ins.prepare("SELECT id FROM Category WHERE name = :n");
    ins.bindValue(":n", categ);
    ins.exec();
    ins.first();
    query.prepare("INSERT INTO Rashod (cost, category_id) VALUES (:cost, :ct_id)");
    query.bindValue(":cost",price);
    query.bindValue(":ct_id", ins.value(0).toInt());
    query.exec();
    query.finish();
}

void rashod::parse_serv(){
    QSqlQuery query;
    query.exec("SELECT * FROM Category;");
    while(query.next())
    {
        QString name = query.value(1).toString();
        ui->comboBox->addItem(name);
    }
     query.finish();
}
