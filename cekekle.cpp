#include "cekekle.h"
#include "ui_cekekle.h"
#include <QDebug>

cekekle::cekekle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cekekle)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnKapat,SIGNAL(clicked()),this,SLOT(kapat()));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(takvimiAc(int,int)));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(hucreyeTiklandi(int,int)));
    ilkYukleme();
}

QStringList cekekle::getListeCbCekTur()
{
    return listeCbCekTur;
}

void cekekle::takvimAcikIseKapat()
{
    if(takvimAcik==true)
    {
        cal->close();
        takvimAcik=false;
    }
}

void cekekle::hucreyeTiklandi(int a, int b)
{
    if(b!=ckSutunTarih)
    {
        takvimAcikIseKapat();
    }
}

void cekekle::takvimiAc(int a, int b)
{
    if(b==ckSutunTarih)
    {
        takvimAcikIseKapat();
        cal->setFirstDayOfWeek(Qt::Monday);
        cal->setLocale(QLocale::Turkish);
        cal->setParent(this);
        cal->setGeometry(50,50,280,250);
        cal->show();
        takvimAcik=true;
        satir=a;
        sutun=b;
        connect(cal,SIGNAL(activated(QDate)),this,SLOT(tarihiAl()));
    }
}

void cekekle::tarihiAl()
{
    ui->tableWidget->item(satir,sutun)->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    cal->close();
    takvimAcik=false;
}

void cekekle::satirEkle(int a,int b)
{
    if(a==ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,b)->text()!="")//eğer değiştirilen satır son satır ise ve hücre boş bırakılmamışsa
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itm1=new QTableWidgetItem();
        QTableWidgetItem *itm2=new QTableWidgetItem();
        QTableWidgetItem *itm3=new QTableWidgetItem();
        QTableWidgetItem *itm4=new QTableWidgetItem();
        QTableWidgetItem *itm5=new QTableWidgetItem();
        QTableWidgetItem *itm6=new QTableWidgetItem();
        QTableWidgetItem *itm7=new QTableWidgetItem();
        itm1->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ckSutunTarih,itm1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ckSutunIsim,itm2);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ckSutunBanka,itm3);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ckSutunTutar,itm4);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ckSutunMuhatap,itm5);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ckSutunCekNo,itm6);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ckSutunAciklama,itm7);

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        btnSil->setEnabled(false);
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,ckSutunSil,btnSil);

        QComboBox *cmb=new QComboBox();
        cmb->addItems(listeCbCekTur);
        cmb->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,ckSutunTur,cmb);
        ///////////////
        //ikinci satır eklendikten sonra etkin olmayan tamam düğmesi etkinleşiyor
        if(ui->btnTamam->isEnabled()==false)
        {
            ui->btnTamam->setEnabled(true);
        }
        ////////////////
        //son satırdan bir üsteki satırın sil düğmesi ve combobox'u etkinleştiriliyor
        QPushButton* btn2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,ckSutunSil));
        btn2->setEnabled(true);

        QComboBox* cmb2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,ckSutunTur));
        cmb2->setEnabled(true);
        /////////////////

        /*
        toplamTutar=ui->lblToplamTutar->text().toDouble();
        toplamTutar=toplamTutar+ui->tableWidget->item(ui->tableWidget->rowCount()-2,ftrSutunTutar)->text().toDouble();
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
        */
    }
    if(b==ckSutunTutar && a<ui->tableWidget->rowCount()-1)
    {
        toplamTutar=0;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            toplamTutar=toplamTutar+ui->tableWidget->item(i,ckSutunTutar)->text().toDouble();
        }
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
    }
}

void cekekle::tamam()
{
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)//son satır sürekli boş olduğu için son satırı gözardı ediyoruz
    {
        for(int j=1;j<ui->tableWidget->columnCount()-1;j++)//son sutun combobox olduğu için gözardı ediyoruz
        {
            listeCek.append(ui->tableWidget->item(i,j)->text());
        }
        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,ckSutunTur));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeCek.append(cmb->currentText());
    }
    cal->close();
    close();
}

void cekekle::kapat()
{
    takvimAcikIseKapat();
    close();
    toplamTutar=0;
}

QStringList cekekle::getListeCek()
{
    return listeCek;
}

double cekekle::getToplamTutar()
{
    return toplamTutar;
}

void cekekle::satirSil()
{
    QObject* obj = sender();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
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

    //eğer tablewidget'ta bir satır varsa sil butonu ve combobo'ı etkisiz olsun
    if(ui->tableWidget->rowCount()==1)
    {
        QPushButton* btn=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(0,ckSutunSil));
        btn->setEnabled(false);

        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,ckSutunTur));
        cmb->setEnabled(false);
    }
    ////////////////////////
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void cekekle::ilkYukleme()
{
    ckSutunSil=0;
    ckSutunTarih=1;
    ckSutunIsim=2;
    ckSutunBanka=3;
    ckSutunTutar=4;
    ckSutunMuhatap=5;
    ckSutunCekNo=6;
    ckSutunAciklama=7;
    ckSutunTur=8;

    QStringList baslik=(QStringList()<<"Sil"<<"Tarih"<<"İsim"<<"Banka"<<"Tutar"<<"Muhatap"<<"No"<<"Açıklama"<<"Tür");
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(ckSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(ckSutunSil, 32);
    ui->tableWidget->horizontalHeader()->setResizeMode(ckSutunTarih,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(ckSutunTarih, 80);
    this->setWindowTitle("Çek Ekle");
    cal=new QCalendarWidget();

    listeCbCekTur<<"Alınan"<<"Verilen";
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(CEK EKLEME PENCERESİ HER AÇILDIĞINDA)
void cekekle::ontanimliAyarlar()
{
    toplamTutar=0;
    ui->tableWidget->setRowCount(0);
    takvimAcik=false;
    ui->btnTamam->setEnabled(false);
    listeCek.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz
    ui->lblToplamTutar->setText("0");

    //fatura ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,ckSutunSil,btnSil);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    QTableWidgetItem *itm3=new QTableWidgetItem();
    QTableWidgetItem *itm4=new QTableWidgetItem();
    QTableWidgetItem *itm5=new QTableWidgetItem();
    QTableWidgetItem *itm6=new QTableWidgetItem();
    QTableWidgetItem *itm7=new QTableWidgetItem();
    itm1->setFlags(Qt::ItemIsEnabled);
    ui->tableWidget->setItem(0,ckSutunTarih,itm1);
    ui->tableWidget->setItem(0,ckSutunIsim,itm2);
    ui->tableWidget->setItem(0,ckSutunBanka,itm3);
    ui->tableWidget->setItem(0,ckSutunTutar,itm4);
    ui->tableWidget->setItem(0,ckSutunMuhatap,itm5);
    ui->tableWidget->setItem(0,ckSutunCekNo,itm6);
    ui->tableWidget->setItem(0,ckSutunAciklama,itm7);

    QComboBox *cmb=new QComboBox();
    cmb->addItems(listeCbCekTur);
    cmb->setEnabled(false);
    ui->tableWidget->setCellWidget(0,ckSutunTur,cmb);
    ////////////////////////////////////////
}

cekekle::~cekekle()
{
    delete ui;
}
