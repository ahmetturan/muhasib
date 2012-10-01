#include "kistasmaas.h"
#include "ui_kistasmaas.h"

kistasmaas::kistasmaas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kistasmaas)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnIptal,SIGNAL(clicked()),this,SLOT(iptal()));
    connect(ui->cbTarih,SIGNAL(clicked()),this,SLOT(tarihEtkin()));
    connect(ui->cbTur,SIGNAL(clicked()),this,SLOT(turEtkin()));
    ilkYukleme();
}

QDate kistasmaas::getBaslangicTarih()
{
    return ui->dtBaslangic->date();
}

QDate kistasmaas::getBitisTarih()
{
    return ui->dtBitis->date();
}

bool kistasmaas::getTurEtkinMi()
{
    return turEtkinMi;
}

bool kistasmaas::getTarihEtkinMi()
{
    return tarihEtkinMi;
}

//TUR CB LERİNDE SEÇİLMİŞ OLANLARI LİSTE YAPIYOR
QStringList kistasmaas::getTurSecim()
{
    QStringList listeSeciliTurler;
    if(ui->cbTurAvans->isChecked())
    {
        listeSeciliTurler.append("Avans");
    }
    if(ui->cbTurIkramiye->isChecked() )
    {
        listeSeciliTurler.append("İkramiye");
    }
    if(ui->cbTurMaas->isChecked())
    {
        listeSeciliTurler.append("Maaş");
    }
    if(ui->cbTurMesai->isChecked())
    {
        listeSeciliTurler.append("Mesai");
    }
    if(ui->cbTurTazminat->isChecked())
    {
        listeSeciliTurler.append("Tazminat");
    }
    return listeSeciliTurler;
}

void kistasmaas::tamam()
{
    if(ui->dtBaslangic->date()>ui->dtBitis->date())
    {
        QMessageBox::warning(this,"hata","Başlangıç tarihi bitiş tarihinden sonra olamaz","Tamam");
    }
    else
    {
        secim=true;
        close();
    }
}

void kistasmaas::iptal()
{
    secim=false;
    close();
}

void kistasmaas::tarihEtkin()
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

void kistasmaas::turEtkin()
{
    if(ui->cbTur->isChecked())
    {
        ui->cbTurAvans->setEnabled(true);
        ui->cbTurIkramiye->setEnabled(true);
        ui->cbTurMaas->setEnabled(true);
        ui->cbTurMesai->setEnabled(true);
        ui->cbTurTazminat->setEnabled(true);
        turEtkinMi=true;
    }
    else
    {
        ui->cbTurAvans->setEnabled(false);
        ui->cbTurIkramiye->setEnabled(false);
        ui->cbTurMaas->setEnabled(false);
        ui->cbTurMesai->setEnabled(false);
        ui->cbTurTazminat->setEnabled(false);
        turEtkinMi=false;
    }
}

//TAMAM VEYA İPTAL DÜĞMELERİNDEN HANGİSİNE BASILDI
bool kistasmaas::getSecim()
{
    return secim;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void kistasmaas::ilkYukleme()
{
    setWindowFlags(Qt::Window);
    ui->dtBaslangic->setDate(QDate::currentDate());
    ui->dtBitis->setDate(QDate::currentDate());

    ui->cbTarih->setChecked(false);
    ui->lblTarihBaslangic->setEnabled(false);
    ui->lblTarihBitis->setEnabled(false);
    ui->dtBaslangic->setEnabled(false);
    ui->dtBitis->setEnabled(false);

    ui->cbTur->setChecked(false);
    ui->cbTurAvans->setEnabled(false);
    ui->cbTurIkramiye->setEnabled(false);
    ui->cbTurMaas->setEnabled(false);
    ui->cbTurMesai->setEnabled(false);
    ui->cbTurTazminat->setEnabled(false);

    turEtkinMi=false;
    tarihEtkinMi=false;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(MAAŞ EKLEME PENCERESİ HER AÇILDIĞINDA)
void kistasmaas::ontanimliAyarlar()
{
    secim=false;
}

kistasmaas::~kistasmaas()
{
    delete ui;
}
