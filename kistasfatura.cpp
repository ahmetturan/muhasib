#include "kistasfatura.h"
#include "ui_kistasfatura.h"
#include <QDebug>

kistasfatura::kistasfatura(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kistasfatura)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnIptal,SIGNAL(clicked()),this,SLOT(iptal()));
    connect(ui->cbTarih,SIGNAL(clicked()),this,SLOT(tarihEtkin()));
    connect(ui->cbTur,SIGNAL(clicked()),this,SLOT(turEtkin()));
    ilkYukleme();
}

void kistasfatura::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {}
}

void kistasfatura::closeEvent(QCloseEvent *event)
{
    iptal();
    event->accept();
}

QDate kistasfatura::getBaslangicTarih()
{
    return ui->dtBaslangic->date();
}

QDate kistasfatura::getBitisTarih()
{
    return ui->dtBitis->date();
}

bool kistasfatura::getTurEtkinMi()
{
    return turEtkinMi;
}

bool kistasfatura::getTarihEtkinMi()
{
    return tarihEtkinMi;
}

int kistasfatura::getTurSecim()
{
    if(ui->cbTurGelen->isChecked() && ui->cbTurGiden->isChecked())
    {
        return 0;
    }
    else if(ui->cbTurGelen->isChecked())
    {
        return 1;
    }
    else if(ui->cbTurGiden->isChecked())
    {
        return 2;
    }
}

void kistasfatura::tarihEtkin()
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

void kistasfatura::turEtkin()
{
    if(ui->cbTur->isChecked())
    {
        ui->cbTurGelen->setEnabled(true);
        ui->cbTurGiden->setEnabled(true);
        turEtkinMi=true;
    }
    else
    {
        ui->cbTurGelen->setEnabled(false);
        ui->cbTurGiden->setEnabled(false);
        turEtkinMi=false;
    }
}

void kistasfatura::tamam()
{
    if(ui->dtBaslangic->date()>ui->dtBitis->date())
    {
        QMessageBox::warning(this,"hata","Başlangıç tarihi bitiş tarihinden sonra olamaz","Tamam");
    }
    else
    {
        close();
        secim=true;
    }
}

void kistasfatura::iptal()
{
    close();
    secim=false;
}

//TAMAM VEYA İPTAL DÜĞMELERİNDEN HANGİSİNE BASILDI
bool kistasfatura::getSecim()
{
    return secim;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void kistasfatura::ilkYukleme()
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
    ui->cbTurGelen->setEnabled(false);
    ui->cbTurGiden->setEnabled(false);

    turEtkinMi=false;
    tarihEtkinMi=false;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(FATURA EKLEME PENCERESİ HER AÇILDIĞINDA)
void kistasfatura::ontanimliAyarlar()
{
    secim=false;
}

kistasfatura::~kistasfatura()
{
    delete ui;
}
