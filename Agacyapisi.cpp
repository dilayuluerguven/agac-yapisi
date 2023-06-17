#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct dugum 
{
    int veri;
    struct dugum* sol;
    struct dugum* sag;
};

struct dugum* dugumekle(int veri) 
{
    struct dugum* yenidugum = (struct dugum*)malloc(sizeof(struct dugum));
    yenidugum->veri = veri;
    yenidugum->sol = NULL;
    yenidugum->sag = NULL;
    return yenidugum;
}

struct dugum* ekle(struct dugum* kok, int veri)
{
    if (kok == NULL)
    {
        return dugumekle(veri);
    }

    if (veri < kok->veri)
    {
        kok->sol = ekle(kok->sol, veri);
    }
    else if (veri > kok->veri)
    {
        kok->sag = ekle(kok->sag, veri);
    }

    return kok;
}

void sirala(struct dugum* kok)
{
    if (kok == NULL)
    {
        return;
    }

    sirala(kok->sol);
    printf("%d ", kok->veri);
    sirala(kok->sag);
}

void siralama(struct dugum* kok, float ortalama)
{
    if (kok == NULL)
    {
        return;
    }

    if (kok->veri > ortalama)
    {
        siralama(kok->sol, ortalama);
        printf("%d ", kok->veri);
        siralama(kok->sag, ortalama);
    }
}

void ekfonksiyon(struct dugum* kok, float ortalama)
{
    if (kok == NULL)
    {
        return;
    }

    if (kok->veri > ortalama)
    {
        ekfonksiyon(kok->sol, ortalama);
        printf("%d ", kok->veri);
        ekfonksiyon(kok->sag, ortalama);
    }
    else
    {
        ekfonksiyon(kok->sag, ortalama);
    }
}

int dugumsayisi(struct dugum* kok)
{
    if (kok == NULL)
    {
        return 0;
    }

    return 1 + dugumsayisi(kok->sol) + dugumsayisi(kok->sag);
}

float ortalamabul(struct dugum* kok, int toplam, int sayac)
{
    if (kok == NULL)
    {
        return 0;
    }

    toplam =toplam + kok->veri;
    sayac++;
    float solortalama;
    solortalama = ortalamabul(kok->sol, toplam, sayac);
    float sagortalama= ortalamabul(kok->sag, toplam, sayac);

    return (solortalama + sagortalama+ kok->veri) / (sayac + 1);
}

int main() 
{
    int n;
    printf("Kac sayi istersiniz: ");
    scanf("%d", &n);

    srand(time(NULL));

    struct dugum* agac = NULL;
    int i;
    int sayi;
    float ortalama=0;
    printf("Sayilar: ");
    for (i = 0; i < n; i++)
    {
        sayi = 10 + rand() % 41; 
        printf("%d ", sayi);
        agac = ekle(agac, sayi);
    }

    int toplam = 0;
    int sayac = 0;
    ortalama = ortalamabul(agac, toplam, sayac);
    printf("\nOrtalama: %.2f\n", ortalama);

    printf("Ortalamadan buyuk sayilar: ");
    siralama(agac, ortalama);

    printf("\nOrtalamadan buyuk sayilarin siralanmis hali: ");
    ekfonksiyon(agac, ortalama);

    return 0;
}

