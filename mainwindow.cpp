#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int In_total_ids_find=0;
    int In_count_Item=0;
    int In_count_Id=0;
    QFile* xmlFile = new QFile("/home/genome/Downloads/SUM.xml");
            if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QMessageBox::critical(this,"Load XML File Problem",
                    "Couldn't open xmlfile.xml/home/genome/Downloads/SUM.xml to load settings for download",
                    QMessageBox::Ok);
                    return;
            }
   QXmlStreamReader* xmlReader = new QXmlStreamReader(xmlFile);
    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
            // Read next element
            QXmlStreamReader::TokenType token = xmlReader->readNext();
            //If token is just StartDocument - go to next
            if(token == QXmlStreamReader::StartDocument) {
                    continue;
            }
            //If token is StartElement - read it
            if(token == QXmlStreamReader::StartElement) {
                    if(xmlReader->name() == "eSummaryResult") {
                            continue;
                    }

                    if(xmlReader->name() == "DocSum") {
                            continue;
                    }
                    if(xmlReader->name() == "Id") {
                     In_total_ids_find++;
                    }
            }
    }

     QStandardItemModel *model = new QStandardItemModel(In_total_ids_find,6,this); //2 Rows and 3 Columns
     model->setHorizontalHeaderItem(0, new QStandardItem(QString("PMID")));
     model->setHorizontalHeaderItem(1, new QStandardItem(QString("Title")));
     model->setHorizontalHeaderItem(2, new QStandardItem(QString("PubType")));
     model->setHorizontalHeaderItem(3, new QStandardItem(QString("PubDate")));
     model->setHorizontalHeaderItem(4, new QStandardItem(QString("HasAbstract")));
     model->setHorizontalHeaderItem(5, new QStandardItem(QString("Source")));


     QFile* xmlFile2 = new QFile("/home/genome/Downloads/SUM.xml");
             if (!xmlFile2->open(QIODevice::ReadOnly | QIODevice::Text)) {
                     QMessageBox::critical(this,"Load XML File Problem",
                     "Couldn't open xmlfile.xml/home/genome/Downloads/SUM.xml to load settings for download",
                     QMessageBox::Ok);
                     return;
             }

     QXmlStreamReader* xmlReader2 = new QXmlStreamReader(xmlFile2);
     while(!xmlReader2->atEnd() && !xmlReader2->hasError()) {
             // Read next element
             QXmlStreamReader::TokenType token = xmlReader2->readNext();
             //If token is just StartDocument - go to next
             if(token == QXmlStreamReader::StartDocument) {
                     continue;
             }
             //If token is StartElement - read it
             if(token == QXmlStreamReader::StartElement) {
                     if(xmlReader2->name() == "eSummaryResult") {
                             continue;
                     }

                     if(xmlReader2->name() == "DocSum") {
                             continue;
                     }
                     if(xmlReader2->name() == "Id") {
                      xmlReader2->readNext();
                      model->setItem(In_count_Id,0,new QStandardItem(QString(xmlReader2->text().toString())));
                      In_count_Id++;
                     }


                     if(xmlReader2->name() == "Item") {

                      QXmlStreamAttributes attributes = xmlReader2->attributes();


                      if(attributes.hasAttribute("Name")) {
                          if(attributes.value("Name").toString().compare("PubDate")==0 )
                          {
                              xmlReader2->readNext();
                              model->setItem(In_count_Item,3,new QStandardItem(QString(xmlReader2->text().toString())));

                          }else
                          if(attributes.value("Name").toString().compare("Title")==0)
                          {
                              xmlReader2->readNext();
                              model->setItem(In_count_Item,1,new QStandardItem(QString(xmlReader2->text().toString())));

                          }else
                          if(attributes.value("Name").toString().compare("Source")==0 )
                          {
                              xmlReader2->readNext();
                              model->setItem(In_count_Item,5,new QStandardItem(QString(xmlReader2->text().toString())));
                          }else

                          if(attributes.value("Name").toString().compare("PubType")==0 )
                          {
                              xmlReader2->readNext();
                              model->setItem(In_count_Item,2,new QStandardItem(QString(xmlReader2->text().toString())));

                          }else
                          if(attributes.value("Name").toString().compare("HasAbstract")==0 )
                          {
                              xmlReader2->readNext();
                              model->setItem(In_count_Item,4,new QStandardItem(QString(xmlReader2->text().toString())));
                               In_count_Item++;
                          }

                         }


                     }

                     ui->tableView->setModel(model);
             }

     }

    if(xmlReader->hasError()) {
            QMessageBox::critical(this,
            "xmlFile.xml Parse Error",xmlReader->errorString(),
            QMessageBox::Ok);
            return;
    }
   QString str= QString::number(In_count_Item);
   ui->lineEdit->setText(str); // count the number of the total IDs
   ui->tableView->setModel(model);
   ui->label->setText("Find "+str+" in total");
    //QMessageBox::information(this, tr("Empty Search Field"),
     //                        "this","button" );

}
