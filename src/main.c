#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "siparis.h"
#include "fields.h"
#include <ctype.h>

char *trimwhitespace(char *str)
{
  char *end;
  while(isspace((unsigned char)*str)) str++;//baştaki boşluğu temizle

  if(*str == 0)  //hepsi boşluk
    return str;

  end = str + strlen(str);
  while(end > str && isspace((unsigned char)*end)) end--;//sondaki boşluğu temizle

  *(end+1) = 0;//son satır

  return str;
}
int RedBlackTreeyeSiparisEkle(JRB agac, char* veri){
    char * temp = strtok(veri, "|");
    int key;
    if (sscanf(temp,"%d",&key) == 0 )
        return 0;
    char * ad = strtok(NULL,"|");
    char * malzeme = strtok(NULL,"|");
    char * renk = strtok(NULL,"|");
    if (ad == NULL || malzeme == NULL || renk == NULL)
        return 0;
    
    siparis sip = TanimlaYeniSiparis(key, ad, malzeme, renk);
    jrb_insert_int(agac, key, new_jval_v((void *) sip));
    return 1;
}
int main()
{
    JRB agac = make_jrb();
    IS is = new_inputstruct(NULL);

    printf(">");
    while(get_line(is) >= 0)
    {        
        if (strcmp(is->fields[0], "quit")==0){
            break;//döngüden çık program bitsin
        }  else if (strchr(is->text1,'<') != NULL) {// pro komutu

            char * temp = strtok(is->text1, "<");// pro komutunu okur
            char * dosyaYolu = trimwhitespace(strtok(NULL, "<"));// dosya yolunu okur boşlukları trim yapar
            dosyaYolu[strlen(dosyaYolu)-1]='\0';

            IS okunacakDosya = new_inputstruct(dosyaYolu);
            if (okunacakDosya == NULL)
            {
                printf("Okumaya çalıştığınız dosya bulunamadi\n>");
                continue;
            }
            while(get_line(okunacakDosya)>=0){

                char * kalanVeri = strchr(okunacakDosya->text1,'|')+1;
                kalanVeri[strlen(kalanVeri)-1]='\0';

                okunacakDosya->text1[strchr(okunacakDosya->text1,'|') - okunacakDosya->text1] = '\0';

                if (strcmp(okunacakDosya->text1, "add")!=0 || !RedBlackTreeyeSiparisEkle(agac,kalanVeri)) {
                    printf("%d. satirda uygun olmayan bicimde veri. Ekleme Durduruldu.(Bu satira kadar ki ekleme islemi tamamlandı) .\n",okunacakDosya->line);
                    break;
                }
            }

            jettison_inputstruct(okunacakDosya);
            printf(">");
            continue;

        }else if (strcmp(is->fields[0], "print")==0) {
            JRB temp;
            jrb_traverse(temp, agac){
                siparis aranan = (siparis) jval_v(temp->val);
                printf("%d, %s, %s, %s\n",aranan->sKey,aranan->Ad,aranan->Malzeme,aranan->Renk);
            }
            printf(">");
            continue;
        } else if (strchr(is->text1,'|') != NULL){ // | içeren methodlar add , search ve write

            char * kalanVeri = strchr(is->text1,'|')+1;
            kalanVeri[strlen(kalanVeri)-1]='\0';
            is->text1[strchr(is->text1,'|') - is->text1] = '\0'; 
            
            if (strcmp(is->text1, "add")==0 ) {
                if(RedBlackTreeyeSiparisEkle(agac,kalanVeri)){
                    printf(">");
                    continue;
                }
            }else if (strcmp(is->text1, "write") == 0) {
                FILE * fo = fopen(kalanVeri, "w");
                JRB temp;
                jrb_traverse(temp, agac){
                    siparis aranan = (siparis) jval_v(temp->val);
                    fprintf(fo,"%d, %s, %s, %s\n",aranan->sKey,aranan->Ad,aranan->Malzeme,aranan->Renk );
                }
                fclose(fo);
                printf(">");
                continue;
            } else if (strcmp(is->text1, "search") == 0) {
                int key;
                if (sscanf(kalanVeri,"%d",&key) != 0) {
                    JRB result = jrb_find_int(agac, key);//int key ile ara

                    if (result == NULL)                    
                        printf("Agacta kayit bulunamadi.\n>");                    
                    else
                    {
                        siparis aranan = (siparis) jval_v(result->val);
                        printf("%d, %s, %s, %s\n>",aranan->sKey,aranan->Ad,aranan->Malzeme,aranan->Renk );
                    }
                    continue;
                }   
            } 
        }
        printf("Bicim uygun degil\n>");
    }
    jrb_free_tree(agac);
    jettison_inputstruct(is);
    return 0;
}
