- Programi calismasi icin 'egavga.bgi' dosyasinin 'ee642.exe' dosyasi ile 
ayni directory'de olmasi gerekmektedir.
-'ee642.exe dosyasini calistirdiginizda program calisacaktir
- Menulere girebilmek icin bazen mouse'a birden fazla basmak gerekebilir
- Plane Curves;
	* Circle cizmek icin origin icin x ve y degerleri ile radius bilgilerini girmek
	  gerekmektedir.
	* Ellipse cizmek icin origin icin x ve y degerlerini, x radius ve y radius
	  degerlerini, ve ellipse x symmetri ekseninin x ekseni ile yaptigi aciyi
	  girmek gerekmektedir. 

- Cubic Spline;
	* Cubic spline cizmek icin mouse ile 6 nokta belirlenmesi gerekir.
	* 6 point'tan olusan path cizildikten sonra degisik cubic spline'lar 
	  ayni path icin cizdirilebilinir veya yeniden path tanimlanabilir.
	* Clamped end cubic spline icin 6 noktaya ek olarak baslangic ve bitis 
	  noktalarindaki derivative'in x ve y koordinatlarinin da girilmesi gerekir.

- Parabolic Blending
	*  Parabolic Blending icin mouse ile 4 nofta tanimlanmasi gerekir. 
	   Program, tanimlanan 2. ve 3. noktalar arasindaki parabolik egriyi hesaplar ve 
	   cizer.

- Bezier
	* Bezier polygonu icin mouse ile 6 nokta tanimlanmasi gerekir. 
	* Cubic Spline icin secilen 6 nokta ayni zamanda bezier curve cizdirmek 
	  icin de kullanilabilir.

-B-Spline
	* B-spline cizdirmek icin once vertex sayisinin ve degree of Bspline 
	  parametrelerinin girilmesi gerekmektedir.
	* Vertex sayisi en fazla 10 olabilir
	* k minimum 2 olmalidir. Bundan kucuk bir deger girilirse program k=2 alir
	* Noktalar mouse ile secildikten sonra istenen B-spline ekranda gorulecektir


--PLANE SURFACES--
-------------------

-Bilinear
	*Mesh tanimlamak icin mouse ile 4 adet nokta secilmelidir.
	*(-150,150),(-100,150),(-25,25),(-200,25) ve
	 (50,175),(150,150),(25,25),(225,50) noktalari ornek mesh tanimi olarak 
	kullanilabilir (Bu noktalarla tanimlanmis meshler icin anlasilmasi kolay sekiller
	olusmaktadir)
	*Rastgele secilecek noktalar icin de algoritma denenebilir.
-Lofted
	*Mesh tanimi icin kenarlari olusturan cubic splinelar icin baslangic ve bitis 
	 noktalarinin tanimlanmasi gerekmektedir (toplam 4 adet nokta)
	*(-200,-50),(-100,-50),(-150,-150),(-50,-150) ve
	 (50,-25),(25,-175),(175,-25),(175,-150) noktalari ornek mesh tanimi olarak 
	kullanilabilir (Bu noktalarla tanimlanmis meshler icin anlasilmasi kolay sekiller
	olusmaktadir)
	*Rastgele secilecek noktalar icin de algoritma denenebilir.
-BiCubic
	*Mesh Noktalarinin 'bicubic.txt' adli dosyaya yazilmasi gerekmektedir.
	Ornek dosya verilmistir. Bu dosyanin programin calistigi dizinin altinda olmasi
	gerekmektedir. Bu dosyanin ilk dort satiri yorum satiri olarak kullanilmaktadir.
	Ilk sutunda noktalari tanimlamakta kullanilmaktadir. Yazilan degerler arasinda 'tab' 
	karakterinin olmasi gerekmektedir.Dosya degistirildikten sonra BiCubic Surface 
	tusuna basilarak yeni grafik programdan cikmadan cizdirilebilir.
-Bezier
	*Defining polygon matrisinin elemenlarinin 'bezier.txt' adli dosyaya girilmesi
	 gerekmektedir. Bu dosyanin ilk iki elemani olarak matrisin boyutlarinin girilmesi
	beklenmektedir. Daha sonraki iki satir yorum satiridir ve parametrelerin girilmesini
	kolaylastirmak amaciyla konulmustur. Verilen ornek dosya uzerinde degisikler yapilarak
	farkli yuzeyler cizdirilebilir. En fazla 10x10'luk bir matrisin girilmesi gerekmektedir.
	Dosya degistirildikten sonra Bezier Surface tusuna basilarak yeni grafik 
	programdan cikmadan cizdirilebilir. 