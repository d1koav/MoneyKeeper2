#include "dohod.h"
#include "ui_dohod.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QMessageBox>

#include <QSqlQueryModel>
dohod::dohod(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::dohod)
{
  ui->setupUi(this);
  parse_serv();

}
dohod::~dohod()
{
  delete ui;
}

void dohod::parse_serv(){
    QSqlQuery query;
    query.exec("SELECT * FROM Category;");
    while(query.next())
    {
        QString name = query.value(1).toString();
        ui->comboBox->addItem(name);
    }
     query.finish();

}

void dohod::on_add_dohod_clicked()
{

    float price = ui->lineEdit->text().toFloat();
    QString categ = ui->comboBox->currentText();
    QSqlQuery ins;
    ins.prepare("SELECT id FROM Category WHERE name = :n");
    ins.bindValue(":n", categ);
    ins.exec();
    ins.first();

    QSqlQuery query;
    query.prepare("INSERT INTO Dohod (cost, category_id) VALUES (:cost, :ct_id)");
    query.bindValue(":cost",price);
    query.bindValue(":ct_id", ins.value(0).toInt());
    query.exec();

    query.finish();
    ins.finish();
}

