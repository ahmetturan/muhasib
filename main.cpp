#include <QtGui/QApplication>
#include "muhasib.h"

//VERİTABANI DOSYASI MEVCUT MU DİYE BAKIYOR
bool veritabaniDosyasiMevcut()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("muhasib.db");
    if (!db.open())
    {
        QMessageBox::warning(0, QObject::tr("Veritabanı Dosyası Açılamıyor"),db.lastError().text());
        return false;
    }
    return true;
}

//BOŞ VERİTABANI DOSYASI OLUŞTURUYOR
void veritabaniOlustur()
{
    QSqlQuery query;
    query.exec("create table fatura(f_id integer primary key not null, f_kayitno varchar, f_tarih varchar, f_isim varchar, f_matrah varchar, f_kdvorani varchar, f_kdvtutari varchar, f_tutar varchar, f_aciklama varchar, f_tur varchar, f_hesap varchar)");
    query.exec("create table cek(c_id integer primary key not null, c_tarih varchar,  c_isim varchar, c_banka varchar, c_tutar varchar, c_muhatap varchar, c_cekno varchar, c_aciklama varchar, c_tur varchar)");
    query.exec("create table maas(m_id integer primary key not null, m_tarih varchar,  m_calisan varchar, m_maas varchar,m_ay varchar, m_tur varchar, m_hesap varchar)");
    query.exec("create table calisan(cl_id integer primary key not null, cl_isim varchar,  cl_konum varchar, cl_isegiris varchar, cl_maas varchar, cl_aciklama varchar)");
    query.exec("create table hesap(h_id integer primary key not null, h_isim varchar, h_baslangicmeblagi varchar, h_guncelmeblag varchar, h_tur varchar)");
    query.exec("create table boyut(b_id integer primary key not null, b_x varchar, b_y varchar, b_w varchar, b_h varchar, b_tamekran varchar)");
    query.exec("create table sonkayit(sk_id integer primary key not null, sk_fatura varchar, sk_cek varchar, sk_maas varchar)");
    query.exec("insert into boyut values(1,20,20,800,400,0)");


}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool veritabaniMevcut = !QFile::exists("muhasib.db");
    if (!veritabaniDosyasiMevcut())
    {
        return 1;
    }
    if (veritabaniMevcut)
    {
        veritabaniOlustur();
    }

    muhasib w;
    w.show();
    
    return a.exec();
}
