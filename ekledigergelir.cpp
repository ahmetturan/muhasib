#include "ekledigergelir.h"
#include "ui_ekledigergelir.h"

ekledigergelir::ekledigergelir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ekledigergelir)
{
    ui->setupUi(this);
    ilkYukleme();
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void ekledigergelir::ilkYukleme()
{
    dgSutunSil=0;
    dgSutunTarih=1;
    dgSutunIsim=2;
    dgSutunKimden=3;
    dgSutunTutar=4;
    dgSutunAciklama=5;
    dgSutunHesap=6;

    QStringList baslik=(QStringList()<<"Sil"<<"Tarih"<<"İsim"<<"Kimden"<<"Tutar"<<"Açıklama"<<"Hesap");
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(dgSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(dgSutunSil, 32);
    this->setWindowTitle("Gelir Ekle");
    cal=new QCalendarWidget();

    //listeCbFaturaTur<<"Gelen"<<"Giden";
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(GELİR EKLEME PENCERESİ HER AÇILDIĞINDA)
void ekledigergelir::ontanimliAyarlar()
{
    toplamTutar=0;//hiçbir şey girmeden kapata tıklanırsa sıfır döndürsün

    ui->tableWidget->setRowCount(0);
    takvimAcik=false;
    ui->btnTamam->setEnabled(false);
    listeDigerGelir.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz
    ui->lblToplamTutar->setText("0");

    //fatura ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,dgSutunSil,btnSil);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    QTableWidgetItem *itm3=new QTableWidgetItem();
    QTableWidgetItem *itm4=new QTableWidgetItem();
    QTableWidgetItem *itm5=new QTableWidgetItem();
    itm1->setFlags(Qt::ItemIsEnabled);//tarih sutunu klavye ile değişmesin
    ui->tableWidget->setItem(0,dgSutunTarih,itm1);
    ui->tableWidget->setItem(0,dgSutunTutar,itm2);
    ui->tableWidget->setItem(0,dgSutunIsim,itm3);
    ui->tableWidget->setItem(0,dgSutunAciklama,itm4);
    ui->tableWidget->setItem(0,dgSutunKimden,itm5);

    QComboBox *cmbHesap=new QComboBox();
    cmbHesap->addItems(listeHesap);
    cmbHesap->setEnabled(false);
    ui->tableWidget->setCellWidget(0,dgSutunHesap,cmbHesap);
    ////////////////////////////////////////
}

ekledigergelir::~ekledigergelir()
{
    delete ui;
}
