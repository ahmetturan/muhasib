#include "eklecalisankonum.h"
#include "ui_eklecalisankonum.h"

ekleCalisanKonum::ekleCalisanKonum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ekleCalisanKonum)
{
    ui->setupUi(this);
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnIptal,SIGNAL(clicked()),this,SLOT(iptal()));
    ilkYukleme();
}

void ekleCalisanKonum::keyPressEvent(QKeyEvent *e)
{
}

void ekleCalisanKonum::kaydet()
{
    QSqlQuery query;
    query.exec("delete from calisankonum");
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)
    {
        query.exec(QString("insert into calisankonum (clk_isim) values ('%1')").arg(ui->tableWidget->item(i,clskSutunIsim)->text()));
    }
}

void ekleCalisanKonum::tamam()
{
    kaydet();
    close();
}

void ekleCalisanKonum::iptal()
{
    close();
}

void ekleCalisanKonum::satirEkle(int a, int b)
{
    if(a==ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,b)->text()!="" && degisiklikIzle==true)//eğer değiştirilen satır son satır ise ve hücre boş bırakılmamışsa
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itmIsim=new QTableWidgetItem();
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,clskSutunIsim,itmIsim);

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        btnSil->setEnabled(false);
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,clskSutunSil,btnSil);

        //son satırdan bir üsteki satırın sil düğmesi etkinleştiriliyor
        QPushButton* btnSil2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,clskSutunSil));
        btnSil2->setEnabled(true);
        /////////////////
    }
}

void ekleCalisanKonum::satirSil()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    QList<QPushButton *> allPButtons = ui->tableWidget->findChildren<QPushButton *>();

    int silinecekSatir=-1;
    for(int i=0;i<allPButtons.count();i++)
    {
        if(allPButtons.at(i)==btn)
        {
            silinecekSatir=i;
            break;
        }
    }
    ui->tableWidget->removeRow(silinecekSatir);
}

//VERİTABANINDAKİ KAYITLARI LİSTEYE EKLİYOR
void ekleCalisanKonum::veritabanindanYukle()
{
    degisiklikIzle=false;
    QSqlQuery query;
    query.exec("select clk_id, clk_isim from calisankonum");
    while (query.next())
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itmIsim=new QTableWidgetItem(query.value(1).toString());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,clskSutunIsim,itmIsim);

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,clskSutunSil,btnSil);
    }
    degisiklikIzle=true;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(PENCERE HER AÇILDIĞINDA)
void ekleCalisanKonum::ontanimliAyarlar()
{
    ui->tableWidget->setRowCount(0);
    veritabanindanYukle();

    //fatura ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,clskSutunSil,btnSil);

    QTableWidgetItem *itmIsim=new QTableWidgetItem();
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,clskSutunIsim,itmIsim);
    ////////////////////////////////////////////////////
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(UYGULAMA HER AÇILDIĞINDA)
void ekleCalisanKonum::ilkYukleme()
{
    clskSutunSil=0;
    clskSutunIsim=1;

    QStringList baslik=(QStringList()<<"Sil"<<"İsim");
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(clskSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(clskSutunSil, 32);
}

ekleCalisanKonum::~ekleCalisanKonum()
{
    delete ui;
}
