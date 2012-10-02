#include "kistascalisan.h"
#include "ui_kistascalisan.h"

kistascalisan::kistascalisan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kistascalisan)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnIptal,SIGNAL(clicked()),this,SLOT(iptal()));
    connect(ui->cbTarih,SIGNAL(clicked()),this,SLOT(tarihEtkin()));
    connect(ui->cbKonum,SIGNAL(clicked()),this,SLOT(konumEtkin()));
    connect(ui->cbMaas,SIGNAL(clicked()),this,SLOT(maasEtkin()));
    ilkYukleme();
}

QDate kistascalisan::getBaslangicTarih()
{
    return ui->dtBaslangic->date();
}

QDate kistascalisan::getBitisTarih()
{
    return ui->dtBitis->date();
}

int kistascalisan::getBaslangicMaas()
{
    return ui->spMaasBaslangic->value();
}

int kistascalisan::getBitisMaas()
{
    return ui->spMaasBitis->value();
}

bool kistascalisan::getKonumEtkinMi()
{
    return konumEtkinMi;
}

bool kistascalisan::getTarihEtkinMi()
{
    return tarihEtkinMi;
}

bool kistascalisan::getMaasEtkinMi()
{
    return maasEtkinMi;
}

//TUR CB LERİNDE SEÇİLMİŞ OLANLARI LİSTE YAPIYOR
QStringList kistascalisan::getKonumSecim()
{
    QStringList listeSeciliTurler;
    if(ui->cbKonumIsci->isChecked())
    {
        listeSeciliTurler.append("İşçi");
    }
    if(ui->cbKonumMudur->isChecked() )
    {
        listeSeciliTurler.append("Müdür");
    }
    if(ui->cbKonumSef->isChecked() )
    {
        listeSeciliTurler.append("Şef");
    }
    return listeSeciliTurler;
}

void kistascalisan::tamam()
{
    if(ui->dtBaslangic->date()>ui->dtBitis->date())
    {
        QMessageBox::warning(this,"hata","Başlangıç tarihi bitiş tarihinden sonra olamaz","Tamam");
    }
    else if(ui->spMaasBaslangic->value()>ui->spMaasBitis->value())
    {
        QMessageBox::warning(this,"hata","Başlangıç bitişten büyük olamaz","Tamam");
    }
    else
    {
        secim=true;
        close();
    }
}

void kistascalisan::iptal()
{
    secim=false;
    close();
}

void kistascalisan::tarihEtkin()
{
    if(ui->cbTarih->isChecked())
    {
        ui->lblTarihBaslangic->setEnabled(true);
        ui->lblTarihBitis->setEnabled(true);
        ui->dtBaslangic->setEnabled(true);
        ui->dtBitis->setEnabled(true);
        tarihEtkinMi=true;
    }
    else
    {
        ui->lblTarihBaslangic->setEnabled(false);
        ui->lblTarihBitis->setEnabled(false);
        ui->dtBaslangic->setEnabled(false);
        ui->dtBitis->setEnabled(false);
        tarihEtkinMi=false;
    }
}

void kistascalisan::konumEtkin()
{
    if(ui->cbKonum->isChecked())
    {
        ui->cbKonumIsci->setEnabled(true);
        ui->cbKonumMudur->setEnabled(true);
        ui->cbKonumSef->setEnabled(true);
        konumEtkinMi=true;
    }
    else
    {
        ui->cbKonumIsci->setEnabled(false);
        ui->cbKonumMudur->setEnabled(false);
        ui->cbKonumSef->setEnabled(false);
        konumEtkinMi=false;
    }
}

void kistascalisan::maasEtkin()
{
    if(ui->cbMaas->isChecked())
    {
        ui->lblMaasBaslangic->setEnabled(true);
        ui->lblMaasBitis->setEnabled(true);
        ui->spMaasBaslangic->setEnabled(true);
        ui->spMaasBitis->setEnabled(true);
        maasEtkinMi=true;
    }
    else
    {
        ui->lblMaasBaslangic->setEnabled(false);
        ui->lblMaasBitis->setEnabled(false);
        ui->spMaasBaslangic->setEnabled(false);
        ui->spMaasBitis->setEnabled(false);
        maasEtkinMi=false;
    }
}

//TAMAM VEYA İPTAL DÜĞMELERİNDEN HANGİSİNE BASILDI
bool kistascalisan::getSecim()
{
    return secim;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void kistascalisan::ilkYukleme()
{
    setWindowFlags(Qt::Window);
    ui->dtBaslangic->setDate(QDate::currentDate());
    ui->dtBitis->setDate(QDate::currentDate());

    ui->cbTarih->setChecked(false);
    ui->lblTarihBaslangic->setEnabled(false);
    ui->lblTarihBitis->setEnabled(false);
    ui->dtBaslangic->setEnabled(false);
    ui->dtBitis->setEnabled(false);

    ui->cbKonum->setChecked(false);
    ui->cbKonumIsci->setEnabled(false);
    ui->cbKonumMudur->setEnabled(false);
    ui->cbKonumSef->setEnabled(false);

    ui->lblMaasBaslangic->setEnabled(false);
    ui->lblMaasBitis->setEnabled(false);
    ui->spMaasBaslangic->setEnabled(false);
    ui->spMaasBitis->setEnabled(false);

    tarihEtkinMi=false;
    konumEtkinMi=false;
    tarihEtkinMi=false;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(MAAŞ EKLEME PENCERESİ HER AÇILDIĞINDA)
void kistascalisan::ontanimliAyarlar()
{
    secim=false;
}

kistascalisan::~kistascalisan()
{
    delete ui;
}
