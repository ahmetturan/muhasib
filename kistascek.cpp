#include "kistascek.h"
#include "ui_kistascek.h"

kistasCek::kistasCek(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kistasCek)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnIptal,SIGNAL(clicked()),this,SLOT(iptal()));
    connect(ui->cbTarih,SIGNAL(clicked()),this,SLOT(tarihEtkin()));
    connect(ui->cbTur,SIGNAL(clicked()),this,SLOT(turEtkin()));
    ilkYukleme();
}

void kistasCek::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {}
}

void kistasCek::closeEvent(QCloseEvent *event)
{
    iptal();
    event->accept();
}

QDate kistasCek::getBaslangicTarih()
{
    return ui->dtBaslangic->date();
}

QDate kistasCek::getBitisTarih()
{
    return ui->dtBitis->date();
}

bool kistasCek::getTurEtkinMi()
{
    return turEtkinMi;
}

bool kistasCek::getTarihEtkinMi()
{
    return tarihEtkinMi;
}

//TUR CB LERİNDE SEÇİLMİŞ OLANLARI LİSTE YAPIYOR
QStringList kistasCek::getTurSecim()
{
    QStringList listeSeciliTurler;
    if(ui->cbTurAlinan->isChecked())
    {
        listeSeciliTurler.append("Alınan");
    }
    if(ui->cbTurVerilen->isChecked() )
    {
        listeSeciliTurler.append("Verilen");
    }
    return listeSeciliTurler;
}

void kistasCek::tamam()
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

void kistasCek::iptal()
{
    secim=false;
    close();
}

void kistasCek::tarihEtkin()
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

void kistasCek::turEtkin()
{
    if(ui->cbTur->isChecked())
    {
        ui->cbTurAlinan->setEnabled(true);
        ui->cbTurVerilen->setEnabled(true);
        turEtkinMi=true;
    }
    else
    {
        ui->cbTurAlinan->setEnabled(false);
        ui->cbTurVerilen->setEnabled(false);
        turEtkinMi=false;
    }
}

//TAMAM VEYA İPTAL DÜĞMELERİNDEN HANGİSİNE BASILDI
bool kistasCek::getSecim()
{
    return secim;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void kistasCek::ilkYukleme()
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
    ui->cbTurAlinan->setEnabled(false);
    ui->cbTurVerilen->setEnabled(false);

    turEtkinMi=false;
    tarihEtkinMi=false;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(MAAŞ EKLEME PENCERESİ HER AÇILDIĞINDA)
void kistasCek::ontanimliAyarlar()
{
    secim=false;
}

kistasCek::~kistasCek()
{
    delete ui;
}
