/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**		  BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				  PROGRAMLAMAYA GİRİS DERSİ
**					2022-2023 GUZ DÖNEMİ
**
**				ÖDEV NUMARASI..........: Proje-1
**				ÖĞRENCİ ADI............: Omer Faruk Kocaman
**				ÖĞRENCİ NUMARASI.......: G221210377
**              DERSİN ALINDIĞI GRUP...: 2-B
****************************************************************************/



#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Depo
{
	string urunAdi;
	float Stok;
	float urunFiyat;
};
Depo urun[99];
struct Malzeme
{
	string malzemeAdi;
	float miktar;
	float maliyet;
};
struct Yemekler
{
	int malzemeAdet;
	string yemekAdi;
	struct Malzeme icindekiler[99];
	float satisFiyati;
	float yemekMaliyet;
	int gunlukUretim;
};
Yemekler yemek[99];


int main()
{

	//her donusun 1 gune denk geldigi sonsuz dongu
	while (true)
	{
		int satilan[99] = { 0 };
		int guncelIndex = 0;
		int yemekIndex = 0;
		int depoIndex = 0;
		char devam;
		fstream depoOku;
		fstream yemekOku;
		fstream malzemeOku;
		depoOku.open("depo.txt", ios::app | ios::in);
		yemekOku.open("yemekcesidi.txt", ios::app | ios::in);
		malzemeOku.open("malzeme.txt", ios::app | ios::in);

		//depodaki bilgileri programdaki struct a aktaran dongu
		for (int k = 0; depoOku; k++)
		{
			depoOku >> urun[k].urunAdi;
			depoOku >> urun[k].Stok;
			depoOku >> urun[k].urunFiyat;
			depoIndex++;
		};

		//yemek listesi ve malzeme listesini programdaki structlara aktaran dongu
		for (int i = 0; yemekOku; i++)
		{
			yemek[i].yemekMaliyet = 0;
			yemek[i].gunlukUretim = 0;
			yemekOku >> yemek[i].yemekAdi;
			yemekOku >> yemek[i].malzemeAdet;
			yemekOku >> yemek[i].satisFiyati;
			yemekOku >> yemek[i].gunlukUretim;

			//her yemegin malzeme listesini ayri ayri alan dongu
			for (int j = 0; j < yemek[i].malzemeAdet; j++)
			{
				malzemeOku >> yemek[i].icindekiler[j].malzemeAdi;
				malzemeOku >> yemek[i].icindekiler[j].miktar;

				//malzemelerin ve yemegin maliyetini cikartan dongu
				for (int k = 0; k < depoIndex; k++)
				{
					//malzemenin birim fiyatini alan kosul ifadesi
					if (yemek[i].icindekiler[j].malzemeAdi == urun[k].urunAdi)
						yemek[i].icindekiler[j].maliyet = yemek[i].icindekiler[j].miktar * urun[k].urunFiyat;
				};
				yemek[i].yemekMaliyet = yemek[i].yemekMaliyet + yemek[i].icindekiler[j].maliyet;
			};
			yemekIndex++;
		};
		guncelIndex = yemekIndex;
		malzemeOku.close();
		yemekOku.close();
		depoOku.close();
		float gunlukMaliyet = 0;
		float gunlukSatis = 0;
		cout << "GUNLUK URETIM PLANI" << endl;

		//gunluk uretim planini yazdiran ve bunun maliyetini hesaplayan dongu
		for (int i = 0; i < yemekIndex - 1; i++)
		{
			gunlukMaliyet = gunlukMaliyet + yemek[i].yemekMaliyet * yemek[i].gunlukUretim;
			cout << "*" << yemek[i].gunlukUretim << " Kisilik " << yemek[i].yemekAdi << endl;

		};
		cout << "Gunluk garanti maliyet: " << gunlukMaliyet << endl << endl;
		cout << "Gunu baslatmak icin herhangi bir tusa basiniz." << endl;
		cin >> devam;

		//gunluk uretim planinda kullanilan malzemeleri stoktan eksilten dongu
		for (int i = 0; i < yemekIndex - 1; i++)
		{
			//yemegin malzemelerini alan dongu
			for (int j = 0; j < yemek[i].malzemeAdet; j++)
			{
				//depodaki malzemeleri tarayan dongu
				for (int k = 0; k < depoIndex; k++)
				{
					//kullanilan malzemeyi bulan kosul ifadesi
					if (yemek[i].icindekiler[j].malzemeAdi == urun[k].urunAdi)
					{
						urun[k].Stok = urun[k].Stok - (yemek[i].gunlukUretim * yemek[i].icindekiler[j].miktar);

					};
				};

			};
		};

		//menu icin kullanilan dongu
		while (true)
		{
			system("cls");
			char menu;
			cout << "-MENU-" << endl;
			cout << "a-Yemek Listesi Yazdir" << endl;
			cout << "b-Stok Listesi Yazdir" << endl;
			cout << "c-Yemek Girisi Yap" << endl;
			cout << "d-Yemek Cikisi Yap" << endl;
			cout << "e-Siparis Listesi Olustur ve Stok Gir" << endl;
			cout << "f-Gunluk Satilan Yemekleri Gir" << endl;
			cout << "g-Guncelle, Gunu Bitir ve Gun Sonu Raporu Al" << endl;
			cin >> menu;
			system("cls");

			//menu icin kullanilan kosul ifadeleri
			if (menu == 'a')
			{
				//yemek listesi yazdirmak icin yemekleri tarayan dongu
				for (int i = 0; i < guncelIndex - 1; i++)
				{
					cout << i + 1 << "." << yemek[i].yemekAdi << endl;
				};
				cout << "Devam etmek icin herhangi bir tusa basiniz.";
				cin >> devam;
				system("cls");
			}
			else if (menu == 'b')
			{
				//stok listesi yazdirmak icin depoyu tarayan dongu
				for (int i = 0; i < depoIndex - 1; i++)
				{
					cout << setw(15) << left << urun[i].urunAdi << urun[i].Stok << "(kg/l/adet)" << endl;
				};
				cout << "Devam etmek icin herhangi bir tusa basiniz.";
				cin >> devam;
				system("cls");
			}
			else if (menu == 'c')
			{
				cout << "yemek adini giriniz: ";
				cin >> yemek[guncelIndex + 1].yemekAdi;
				cout << "Yemekteki malzeme sayisini giriniz: ";
				cin >> yemek[guncelIndex + 1].malzemeAdet;

				//girilen yemegin malzemelerini alan dongu
				for (int i = 0; i < yemek[guncelIndex + 1].malzemeAdet; i++)
				{
					cout << i + 1 << ". urunu giriniz: ";
					cin >> yemek[guncelIndex + 1].icindekiler[i].malzemeAdi;

					//girilen malzeme icin depoyu tarayan dongu
					for (int j = 0; j < 99; j++)
					{
						//girilen malzemenin depoda olup olmadigini kontrol eden kosul ifadeleri
						if (yemek[guncelIndex + 1].icindekiler[i].malzemeAdi == urun[j].urunAdi)
							break;
						else if (urun[j].urunFiyat == 0)
						{
							urun[j].urunAdi = yemek[guncelIndex + 1].icindekiler[i].malzemeAdi;
							cout << "Urunun birim fiyatini giriniz: ";
							cin >> urun[j].urunFiyat;
							urun[j].Stok = 0;
							cout << "Urun icin siparis olusturmayi unutmayiniz." << endl;
							depoIndex++;
							break;
						}
						else
							continue;
					};
					cout << "Kullanilacak miktari giriniz: ";
					cin >> yemek[guncelIndex + 1].icindekiler[i].miktar;
				};
				cout << "Yemek satis fiyati giriniz: ";
				cin >> yemek[guncelIndex + 1].satisFiyati;
				cout << "Gunluk planlanan uretim miktarini giriniz: ";
				cin >> yemek[guncelIndex + 1].gunlukUretim;
				guncelIndex++;
				cout << "Devam etmek icin herhangi bir tusa basiniz.";
				cin >> devam;
				system("cls");
			}
			else if (menu == 'd')
			{
				string yemekIsmi;
				cout << "Yemek adini giriniz: ";
				cin >> yemekIsmi;
				//yemekleri tarayan dongu
				for (int i = 0; i < yemekIndex; i++)
				{
					//silinecek yemegi kontrol eden kosul ifadesi
					if (yemekIsmi == yemek[i].yemekAdi)
					{
						yemek[i] = {};
					};
				};
				cout << "Devam etmek icin herhangi bir tusa basiniz.";
				cin >> devam;
				system("cls");
			}
			else if (menu == 'e')
			{
				int urunAdet;
				string urunIsmi;
				float miktar;
				cout << "Kac urun siparisi olusturacaginizi girin: ";
				cin >> urunAdet;

				//siparis icin kullanilan dongu
				for (int i = 0; i < urunAdet; i++)
				{
					cout << "Urunun ismini giriniz: ";
					cin >> urunIsmi;

					//urunleri tarayan dongu
					for (int i = 0; i < depoIndex; i++)
					{
						//urunu karsilastiran kosul ifadesi
						if (urunIsmi == urun[i].urunAdi)
						{
							cout << "Eklenecek miktari giriniz: ";
							cin >> miktar;
							urun[i].Stok = urun[i].Stok + miktar;
						};
					};
				};
				cout << "Devam etmek icin herhangi bir tusa basiniz.";
				cin >> devam;
				system("cls");
			}
			else if (menu == 'f')
			{
				//yemekleri tarayan dongu
				for (int i = 0; i < yemekIndex - 1; i++)
				{
					//silinen yemegi atlayan kosul ifadesi
					if (yemek[i].satisFiyati != 0)
					{

						cout << "Kac kisilik " << yemek[i].yemekAdi << " satildi: ";
						cin >> satilan[i];

						//yemek icin gunluk planin ustune cikilmasini kontrol eden kosul ifadesi
						if (satilan[i] > yemek[i].gunlukUretim)
						{
							gunlukMaliyet = gunlukMaliyet + ((satilan[i] - yemek[i].gunlukUretim) * yemek[i].yemekMaliyet);

							//ekstra yemekler icin kullanilan malzemeleri stokdan eksilten ic ice donguler
							for (int j = 0; j < yemek[i].malzemeAdet; j++)
							{
								for (int k = 0; k < depoIndex; k++)
								{
									if (yemek[i].icindekiler[j].malzemeAdi == urun[k].urunAdi)
									{
										urun[k].Stok = urun[k].Stok - ((satilan[i] - yemek[i].gunlukUretim) * yemek[i].icindekiler[j].miktar);

									};
								};

							};
						};
						gunlukSatis = gunlukSatis + satilan[i] * yemek[i].satisFiyati;
					};
				};
				cout << "Devam etmek icin herhangi bir tusa basiniz.";
				cin >> devam;
				system("cls");
			}
			else if (menu == 'g')
			{
				depoOku.open("depo.txt", ios::out);
				yemekOku.open("yemekcesidi.txt", ios::out);
				malzemeOku.open("malzeme.txt", ios::out);
				//guncel durumu depo listesine yazan dongu
				for (int i = 0; i < depoIndex - 1; i++)
				{
					depoOku << urun[i].urunAdi << " " << urun[i].Stok << " " << urun[i].urunFiyat << "\n";
				};
				//guncel durumu yemek listesi ve malzeme listesine yazan dongu
				for (int i = 0; i < guncelIndex + 1; i++)
				{
					//struct in bos olma durumunu kontrol eden kosul ifadesi
					if (yemek[i].malzemeAdet)
					{
						yemekOku << yemek[i].yemekAdi << " " << yemek[i].malzemeAdet << " " << yemek[i].satisFiyati << " " << yemek[i].gunlukUretim << "\n";
						//guncel malzeme durumunu malzeme listesine yazzan dongu
						for (int j = 0; j < yemek[i].malzemeAdet; j++)
						{
							malzemeOku << yemek[i].icindekiler[j].malzemeAdi << " " << yemek[i].icindekiler[j].miktar << " ";
						};
						malzemeOku << "\n";
					}
				};
				cout << "URETILEN, ELDE KALAN VE SATILAN" << endl;

				//uretim, satis vb. raporunu yazdiran dongu
				for (int i = 0; i < yemekIndex - 1; i++)
				{
					if (yemek[i].satisFiyati != 0)
					{
						if (yemek[i].satisFiyati)
							if (satilan[i] == yemek[i].gunlukUretim)
							{

								cout << "* " << yemek[i].gunlukUretim << " kisilik " << yemek[i].yemekAdi << " uretildi." << endl;

							}
							else if (satilan[i] > yemek[i].gunlukUretim)
							{
								cout << "* " << satilan[i] << " kisilik " << yemek[i].yemekAdi << " uretildi." << endl;
							}
							else
							{
								cout << "* " << yemek[i].gunlukUretim << " kisilik " << yemek[i].yemekAdi << " uretildi." << endl;
								cout << "! " << yemek[i].gunlukUretim - satilan[i] << " kisilik " << yemek[i].yemekAdi << " elde kaldi." << endl;
							}
						cout << "+ " << satilan[i] << " kisilik " << yemek[i].yemekAdi << " satildi" << endl;
					};
				};
				cout << "KAR/ZARAR" << endl;
				cout << "Gunluk Maliyet: " << gunlukMaliyet << "$" << endl;
				cout << "Gunluk Satis: " << gunlukSatis << "$" << endl;
				cout << "Kar/Zarar: " << gunlukSatis - gunlukMaliyet << "$" << endl;
				malzemeOku.close();
				yemekOku.close();
				depoOku.close();
				cout << "Restorani kapatmak icin herhangi bir tusa basiniz.";
				cin >> devam;
				system("cls");
				break;
			}
			else
			{
				cout << "hatali giris yaptiniz anamenuye donmek icin herhangi bir tusa basiniz" << endl;
				cin >> devam;
				system("cls");
			}



		};
	};

}

