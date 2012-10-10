#include "eklehesap.h"
#include "ui_eklehesap.h"

hesapekle::hesapekle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hesapekle)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    ilkYukleme();
}

QStringList hesapekle::getListeCbHesapTur()
{
    return listeCbHesapTur;
}

void hesapekle::tamam()
{
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)//son satır sürekli boş olduğu için son satırı gözardı ediyoruz
    {
        for(int j=1;j<ui->tableWidget->columnCount()-1;j++)//son sutun combobox olduğu için gözardı ediyoruz
        {
            listeHesaplar.append(ui->tableWidget->item(i,j)->text());
        }
        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,hspSutunTur));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeHesaplar.append(cmb->currentText());
    }
    close();
    qDebug()<<"listeHesaplar:"<<listeHesaplar;
}

QStringList hesapekle::getListeHesap()
{
    return listeHesaplar;
}

void hesapekle::satirSil()
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

    /*
    //eğer tablewidget'ta bir satır varsa sil butonu ve combobo'ı etkisiz olsun
    if(ui->tableWidget->rowCount()==1)
    {
        QPushButton* btn=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(0,hspSutunSil));
        btn->setEnabled(false);

        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,hspSutunTur));
        cmb->setEnabled(false);
    }
    ////////////////////////
    */
}

void hesapekle::satirEkle(int a, int b)
{
    if(a==ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,b)->text()!="")//eğer değiştirilen satır son satır ise ve hücre boş bırakılmamışsa
    {
        if(listeMevcutHesaplar.contains(ui->tableWidget->item(a,hspSutunIsim)->text()))
        {
            QMessageBox::warning(this,"","Bu hesap zaten var","Tamam");
            ui->tableWidget->item(a,hspSutunIsim)->setText("");
        }
        else if(ui->tableWidget->item(a,hspSutunIsim)->text()=="")
        {
            QMessageBox::warning(this,"","Hesap ismi boş olamaz","Tamam");
        }
        else
        {
            listeMevcutHesaplar.append(ui->tableWidget->item(a,hspSutunIsim)->text());//eklenen hesap ismi bir daha eklenemesin diye

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            QTableWidgetItem *itm1=new QTableWidgetItem();
            QTableWidgetItem *itm2=new QTableWidgetItem();
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,hspSutunIsim,itm1);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,hspSutunBaslangicMeblagi,itm2);

            QPushButton *btnSil=new QPushButton();
            btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
            btnSil->setToolTip("Sil");
            btnSil->setEnabled(false);
            connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,hspSutunSil,btnSil);

            QComboBox *cmb=new QComboBox();
            cmb->addItems(listeCbHesapTur);
            cmb->setEnabled(false);
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,hspSutunTur,cmb);
            ///////////////
            //ikinci satır eklendikten sonra etkin olmayan tamam düğmesi etkinleşiyor
            if(ui->btnTamam->isEnabled()==false)
            {
                ui->btnTamam->setEnabled(true);
            }
            ////////////////
            //son satırdan bir üsteki satırın sil düğmesi ve combobox'u etkinleştiriliyor
            QPushButton* btn2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,hspSutunSil));
            btn2->setEnabled(true);

            QComboBox* cmb2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,hspSutunTur));
            cmb2->setEnabled(true);
            /////////////////

            /*
        toplamTutar=ui->lblToplamTutar->text().toDouble();
        toplamTutar=toplamTutar+ui->tableWidget->item(ui->tableWidget->rowCount()-2,ftrSutunTutar)->text().toDouble();
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
        */
        }
    }
    /*
    if(b==sutunTutar && a<ui->tableWidget->rowCount()-1)
    {
        toplamTutar=0;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            toplamTutar=toplamTutar+ui->tableWidget->item(i,sutunTutar)->text().toDouble();
        }
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
    }
    */
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void hesapekle::ilkYukleme()
{
    hspSutunSil=0;
    hspSutunIsim=1;
    hspSutunBaslangicMeblagi=2;
    hspSutunTur=3;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    QStringList baslik=(QStringList()<<""<<"İsim"<<"Başlangıç Meblağı"<<"Tür");
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(hspSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(hspSutunSil, 32);
    this->setWindowTitle("Hesap Ekle");

    listeCbHesapTur<<"Banka"<<"Nakit";
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(FATURA EKLEME PENCERESİ HER AÇILDIĞINDA)
void hesapekle::ontanimliAyarlar(QStringList mevcutHesaplar)
{
    ui->tableWidget->setRowCount(0);
    ui->btnTamam->setEnabled(false);
    listeHesaplar.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz

    //hesap ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,hspSutunSil,btnSil);

    QComboBox *cmbTur=new QComboBox();
    cmbTur->addItems(listeCbHesapTur);
    cmbTur->setEnabled(false);
    ui->tableWidget->setCellWidget(0,hspSutunTur,cmbTur);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    ui->tableWidget->setItem(0,hspSutunIsim,itm1);
    ui->tableWidget->setItem(0,hspSutunBaslangicMeblagi,itm2);

    listeMevcutHesaplar=mevcutHesaplar;
}

hesapekle::~hesapekle()
{
    delete ui;
}
